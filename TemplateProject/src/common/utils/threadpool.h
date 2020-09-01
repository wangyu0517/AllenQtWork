#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <queue>
#include <vector>
#include <condition_variable>
#include <atomic>
#include <future>

class ThreadPool
{
    using Task = std::function<void()>;
public:
    ThreadPool(unsigned short nThreadNum = 4)
        : m_bStop(false)
    {
        m_nIdlThreadNum = nThreadNum < 1 ? 1 : nThreadNum;
        CreatePool(nThreadNum);
    }

    ~ThreadPool()
    {
        m_bStop.store(true);
        m_cvTask.notify_all(); // 唤醒所有线程执行
        for (std::thread& t : m_pool)
        {
            if (t.joinable())
                t.join();
        }
    }

    template<class F, class... Args>
    auto Commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
    {
        using RetType = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<RetType()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );
        std::future<RetType> future;
        // 添加任务到队列
        if (!m_bStop)
        {
            future = task->get_future();
            std::lock_guard<std::mutex> lock{ m_lock };
            m_tasks.emplace(
                [task]()
                {
                    (*task)();
                }
            );
        }
        m_cvTask.notify_one(); // 唤醒一个线程执行

        return future;
    }

    int GetIdlThreadNum() { return m_nIdlThreadNum; }

private:
    void CreatePool(unsigned short nThreadNum)
    {
        for (decltype(nThreadNum) size = 0; size < nThreadNum; ++size)
        {
            m_pool.emplace_back(
                // 工作线程函数
                [this]
                {
                    while(!m_bStop)
                    {
                        Task task;
                        // 获取一个待执行的 task，大括号模块是为了锁的有效期
                        {
                            std::unique_lock<std::mutex> lock{ m_lock };
                            m_cvTask.wait(lock,
                                [this]
                                {
                                    return m_bStop.load() || !m_tasks.empty();
                                }
                            );
                            if (m_bStop && m_tasks.empty())
                                return;
                            task = std::move(m_tasks.front()); // 取一个 task
                            m_tasks.pop();
                        }
                        --m_nIdlThreadNum;
                        task();
                        ++m_nIdlThreadNum;
                    }
                }
            );
        }
    }

private:
    // 线程池
    std::vector<std::thread> m_pool;
    // 任务队列
    std::queue<Task> m_tasks;
    // 同步
    std::mutex m_lock;
    // 条件阻塞
    std::condition_variable m_cvTask;
    // 是否关闭提交
    std::atomic<bool> m_bStop;
    //空闲线程数量
    std::atomic<unsigned short> m_nIdlThreadNum;
};

#endif // THREADPOOL_H
