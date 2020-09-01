#ifndef SINGNALGUARD_H
#define SINGNALGUARD_H

#include <QObject>
#include <vector>
#include <functional>
/**
 * @brief The SingnalGuard class
 * 以组合的形式，提供信号连接功能
 * 应用于private class ，内部信号连接到public class
 */
class SignalerInfo;
class SingnalGuard
{
public:
    explicit SingnalGuard();
    ~SingnalGuard();
public:
    void establish(const QObject* sender, const char* signal,
                const QObject* receiver, const char* member,
                Qt::ConnectionType type = Qt::AutoConnection);

private:
    std::vector<SignalerInfo> infos;
//    static QObject* distoryMonitor;
};

/**
 * @brief The SignalerInfo class
 * 保存信号连接信息
 */
class SignalerInfo{
public:
    bool init = false;

    const QObject* sender = nullptr;
    const char* signal = nullptr;
    const QObject* receiver = nullptr;
    const char* member = nullptr;
    const Qt::ConnectionType type = Qt::AutoConnection;

public:
    SignalerInfo();
    SignalerInfo(const QObject* sender, const char* signal,
                   const QObject* receiver, const char* member,
                   Qt::ConnectionType type = Qt::AutoConnection);

    void connect();
    void disconnect();
};

#endif // SINGNALGUARD_H
