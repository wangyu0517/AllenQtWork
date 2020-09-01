#ifndef MESSAGEBOXMANAGE_H
#define MESSAGEBOXMANAGE_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QVector>
#include <messagebox/messageboxcell.h>

typedef enum EN_MESSAGEBOX_LEVEL{
    MESSAGEBOX_LEVEL_UNKOWN = -1,
    MESSAGEBOX_LEVEL_QUITAPP = 1,
    MESSAGEBOX_LEVEL_LOGOOUT,
    MESSAGEBOX_LEVEL_QUITMEETING,
    MESSAGEBOX_LEVEL_NETWORK,
    MESSAGEBOX_LEVEL_UI,
}EN_MESSAGEBOX_LEVEL;

typedef struct ST_MESSAGEBOX_DETAIL{
    EN_MESSAGEBOX_LEVEL level;       //消息等级
    MeessageBoxCell*    messagebox;  //消息框
    QWidget*            parent;      //消息框父类
    MessageBoxCallback  callback;     //用户操作过后的回调
    QPoint parentGolbalCenter;	//	父类的global center point
}ST_MESSAGEBOX_DETAIL;

class MessageboxManage : public QObject
{
    Q_OBJECT
signals:

public:
    static MessageboxManage* instance();


    void showWidget();

    void clearAll();

    void infomation( EN_MESSAGEBOX_LEVEL level,
                     MessageBoxCallback callback,
                     const QString& title,
                     const QString& text,
                     MeessageBoxCell::EnterKeyButton enterDefault = MeessageBoxCell::EnterKeyButton::Yes_Btn,
                     QWidget *parent = nullptr,
                     MsgboxType msgType = QUESTION,
                     QPoint parentGolbalCenter= QPoint());
    void question( EN_MESSAGEBOX_LEVEL level,
                   MessageBoxCallback callback,
                   const QString& title,
                   const QString& text,
                   MeessageBoxCell::EnterKeyButton enterDefault = MeessageBoxCell::EnterKeyButton::No_Btn,
                   QWidget *parent = nullptr,
                   MsgboxType msgType = QUESTION,
                   QPoint parentGolbalCenter= QPoint());

    void questionDIY( EN_MESSAGEBOX_LEVEL level,
                      MessageBoxCallback callback,
                      const QString& title,
                      const QString& text,
                      const QString& okText,
                      const QString& cancelText,
                      MeessageBoxCell::EnterKeyButton enterDefault = MeessageBoxCell::EnterKeyButton::No_Btn,
                      QWidget *parent = nullptr,
                      MsgboxType msgType = QUESTION,
                      QPoint parentGolbalCenter= QPoint());

private slots:
    void onMessageBoxClosed(QObject* obj);

private:
    MessageboxManage(QObject *parent = 0);
    static MessageboxManage* s_instance;

    void sortList();
    void hideAllWidget();

    QVector<ST_MESSAGEBOX_DETAIL> m_listMessagebox;
};

#endif // MESSAGEBOXMANAGE_H
