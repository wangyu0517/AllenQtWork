#include "mainapp.h"
#include <QDateTime>
#include <QDebug>
#include <utils/singnalguard.h>
#include <utils/variant.h>
class MainAppPrivate
{
    AL_DECLARE_PUBLIC(MainApp)
public:
    MainAppPrivate(MainApp *q);
    virtual ~MainAppPrivate();
private:
    SingnalGuard sigguard;
};

MainAppPrivate::MainAppPrivate(MainApp *q) : q_ptr(q)
{

}

MainAppPrivate::~MainAppPrivate()
{

}

MainApp::MainApp(int &argc, char **argv)
    : QtSingleApplication(argc, argv, true),
      d_ptr(new MainAppPrivate(this))
{
    qsrand(QDateTime::currentMSecsSinceEpoch());//为随机值设定一个seed

}

MainApp *MainApp::Instance()
{
    return static_cast<MainApp*>(QCoreApplication::instance());
}

bool MainApp::initApp()
{
//    setActivationWindow();
    registerTypes();
    qDebug() << "start success!";
    test();
    return true;
}

void MainApp::test()
{
    Variant var;
    t_VariantTest testInfo{QString("test")};
    var.setValueR<t_VariantTest>(testInfo);
    connect(this, &MainApp::sigTest, this, [](Variant var)
    {
        if(var.getUserType() == "t_VariantTest") {
            t_VariantTest info = var.value<t_VariantTest>();
            qDebug()<<info.str;
        }
    });
    connect(this, &MainApp::sigError, this, [](t_Error er){
        qDebug() << er.str;
    });
    emit sigTest(var);
    emit sigError(t_Error{QString("error")});
}

void MainApp::registerTypes()
{
#if USING_MACROS_REG==0
    Variant::resgisterUserTypes();
#endif
}
