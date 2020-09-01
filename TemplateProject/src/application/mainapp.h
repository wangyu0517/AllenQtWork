#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>
#include <utils/global_macros.h>
#include <qglobal.h>
#include <qtsingleapplication/qtsingleapplication.h>
#include "mystructs.h"
#define MyApp MainApp::Instance();//global

/**
 * @brief The MainApp class.
 *
 */
class MainAppPrivate;
class MainApp : public QtSingleApplication
{
    Q_OBJECT   
    AL_NONEQOBJECT_DECLARE_PRIVATE(MainApp)
public:
    explicit MainApp(int &argc, char** argv);
    static MainApp* Instance();
    bool initApp();

    //test
    void test();
signals:
    void sigTest(Variant var);
    void sigError(t_Error error);

private:
    void registerTypes();


signals:

public slots:
};
#endif // MAINAPP_H
