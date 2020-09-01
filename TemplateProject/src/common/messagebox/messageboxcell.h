#ifndef MEESSAGEBOXCELL_H
#define MEESSAGEBOXCELL_H

#include <QWidget>
#include <QDialog>
#include "messagebox.h"
#include <QKeyEvent>
#include <functional>

enum MessageBoxReply
{
    Yes,
    No
};

//回调
typedef std::function<void (MessageBoxReply)> MessageBoxCallback;

class MeessageBoxCell : public QDialog
{
    Q_OBJECT

public:
    explicit MeessageBoxCell(QWidget *parent = 0);
    ~MeessageBoxCell();

public:
    enum EnterKeyButton{
        Yes_Btn,
        No_Btn
    };

public:
    //  回车键响应按钮
    void setEnterKeyButton(EnterKeyButton keyBtn);
    void setText(const QString& text);
    void setTipsLabelPicture(MsgboxType type);

    void setInformationBtn();
    void setQuestionBtn();
    void setCallback(MessageBoxCallback callback);

    void setOkText(QString text);
    void setCancelText(QString text);

    virtual int exec();

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *evt);

private:
    MessageBoxCallback m_callback;
    QString     m_text;
    MeessageBoxCell::EnterKeyButton m_keyBtn;

    void reSetText();
};

#endif // MEESSAGEBOXCELL_H
