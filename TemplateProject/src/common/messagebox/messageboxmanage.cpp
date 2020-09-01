#include "messageboxmanage.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QtCore/qdebug.h>
#include <utils/focuser.h>

MessageboxManage* MessageboxManage::s_instance = nullptr;
MessageboxManage::MessageboxManage(QObject *parent) : QObject(parent)
{
    m_listMessagebox.clear();
}

MessageboxManage *MessageboxManage::instance()
{
    if(nullptr == s_instance){
        s_instance = new MessageboxManage();
    }

    return s_instance;
}

void MessageboxManage::clearAll()
{
    foreach (ST_MESSAGEBOX_DETAIL messageBoxDetail, m_listMessagebox) {
        messageBoxDetail.messagebox->close();
    }
}

void MessageboxManage::sortList()
{
    std::sort(m_listMessagebox.begin(),m_listMessagebox.end(),[](ST_MESSAGEBOX_DETAIL _left, ST_MESSAGEBOX_DETAIL _right){
        return _left.level < _right.level;
    });
}

void MessageboxManage::hideAllWidget()
{
    foreach (ST_MESSAGEBOX_DETAIL messageBoxDetail, m_listMessagebox) {
        messageBoxDetail.messagebox->hide();
    }
}

void MessageboxManage::showWidget()
{
    //通知托盘

    if(m_listMessagebox.count() <= 0 ){
        return;
    }

    //排序依次show
    sortList();
    hideAllWidget();

    if(m_listMessagebox.count() <= 0 )
        return;

    ST_MESSAGEBOX_DETAIL messageboxDetail = m_listMessagebox.at(0);

    if(messageboxDetail.parent) {
        QPoint p = messageboxDetail.parent->mapToGlobal(messageboxDetail.parent->rect().center());
        QSize size =  messageboxDetail.messagebox->size();
        messageboxDetail.messagebox->move(p.x()-size.width()/2,p.y()-size.width()/2);
    } else if(messageboxDetail.parentGolbalCenter != QPoint()) {
        messageboxDetail.messagebox->move(messageboxDetail.parentGolbalCenter
                                          - messageboxDetail.messagebox->rect().center());
    } else {
#ifdef WIN32
        QDesktopWidget* desktop = qApp->desktop();
        QSize size =  desktop->screen(desktop->primaryScreen())->size();
        messageboxDetail.messagebox->move(size.width()/2 - messageboxDetail.messagebox->width()/2,
                        size.height()/2 - messageboxDetail.messagebox->height()/2);
#else
        messageboxDetail.messagebox->move(qApp->desktop()->availableGeometry().center()
                                          - messageboxDetail.messagebox->rect().center());
#endif
    }
    qDebug() << "messagebox pos:" << messageboxDetail.messagebox->pos();

    messageboxDetail.messagebox->setCallback(messageboxDetail.callback);
    messageboxDetail.messagebox->setModal(true);

    Focuser focuser(messageboxDetail.messagebox);
    focuser.show();
}



void MessageboxManage::infomation(EN_MESSAGEBOX_LEVEL level,
                                  MessageBoxCallback callback,
                                  const QString &title,
                                  const QString &text,
                                  MeessageBoxCell::EnterKeyButton enterDefault /*= EnterKeyButton::Yes_Btn*/,
                                  QWidget *parent /*= nullptr*/,
                                  MsgboxType msgType /*= QUESTION*/,
                                  QPoint parentGolbalCenter/*= QPoint()*/)
{
    MeessageBoxCell *messagebox = new MeessageBoxCell();//(parent);

    messagebox->setWindowTitle(title);
    messagebox->setText(text);
    messagebox->setEnterKeyButton(enterDefault);
    messagebox->setTipsLabelPicture(msgType);
    connect(messagebox,SIGNAL(destroyed(QObject*)),this,SLOT(onMessageBoxClosed(QObject*)));

    messagebox->setInformationBtn();

    ST_MESSAGEBOX_DETAIL messageBoxDetail;
    messageBoxDetail.level = level;
    messageBoxDetail.messagebox = messagebox;
    messageBoxDetail.parent = parent;
    messageBoxDetail.callback = callback;
    messageBoxDetail.parentGolbalCenter = parentGolbalCenter;
    m_listMessagebox.push_back(messageBoxDetail);

    showWidget();
}

void MessageboxManage::question(EN_MESSAGEBOX_LEVEL level,
                                MessageBoxCallback callback,
                                const QString &title,
                                const QString &text,
                                MeessageBoxCell::EnterKeyButton enterDefault /*= EnterKeyButton::No_Btn*/,
                                QWidget *parent /*= nullptr*/,
                                MsgboxType msgType /*= QUESTION*/,
                                QPoint parentGolbalCenter/*= QPoint()*/)
{
    MeessageBoxCell *messagebox = new MeessageBoxCell();//(parent);

    messagebox->setWindowTitle(title);
    messagebox->setText(text);
    messagebox->setEnterKeyButton(enterDefault);
    messagebox->setTipsLabelPicture(msgType);
    connect(messagebox,SIGNAL(destroyed(QObject*)),this,SLOT(onMessageBoxClosed(QObject*)));

    messagebox->setQuestionBtn();

    ST_MESSAGEBOX_DETAIL messageBoxDetail;
    messageBoxDetail.level = level;
    messageBoxDetail.messagebox = messagebox;
    messageBoxDetail.parent = parent;
    messageBoxDetail.callback = callback;
    messageBoxDetail.parentGolbalCenter = parentGolbalCenter;

    m_listMessagebox.push_back(messageBoxDetail);
    showWidget();
}

void MessageboxManage::questionDIY(EN_MESSAGEBOX_LEVEL level,
                                   MessageBoxCallback callback,
                                   const QString &title,
                                   const QString &text,
                                   const QString &okText,
                                   const QString &cancelText,
                                   MeessageBoxCell::EnterKeyButton enterDefault,
                                   QWidget *parent,
                                   MsgboxType msgType,
                                   QPoint parentGolbalCenter/*= QPoint()*/)
{
    MeessageBoxCell *messagebox = new MeessageBoxCell();//(parent);

    messagebox->setWindowTitle(title);
    messagebox->setText(text);
    messagebox->setEnterKeyButton(enterDefault);
    messagebox->setTipsLabelPicture(msgType);
    messagebox->setOkText(okText);
    messagebox->setCancelText(cancelText);
    connect(messagebox,SIGNAL(destroyed(QObject*)),this,SLOT(onMessageBoxClosed(QObject*)));

    messagebox->setQuestionBtn();

    ST_MESSAGEBOX_DETAIL messageBoxDetail;
    messageBoxDetail.level = level;
    messageBoxDetail.messagebox = messagebox;
    messageBoxDetail.parent = parent;
    messageBoxDetail.callback = callback;
    messageBoxDetail.parentGolbalCenter = parentGolbalCenter;

    m_listMessagebox.push_back(messageBoxDetail);
    showWidget();
}

void MessageboxManage::onMessageBoxClosed(QObject* obj)
{
    MeessageBoxCell *messagebox = static_cast<MeessageBoxCell*>(obj);

    for(int i=0; i<m_listMessagebox.count(); i++)
    {
        ST_MESSAGEBOX_DETAIL messageDetail = m_listMessagebox.at(i);
        if(messageDetail.messagebox == messagebox)
        {
            m_listMessagebox.removeAt(i);
            break;
        }
    }

    showWidget();
}
