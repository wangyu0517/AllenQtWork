#include "messageboxcell.h"
#include <QDebug>

MeessageBoxCell::MeessageBoxCell(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::Popup | Qt::Dialog);
    setAttribute(Qt::WA_DeleteOnClose);


    m_text = "";
    m_keyBtn = MeessageBoxCell::EnterKeyButton::No_Btn;
//    connect(ui->MessageBox_yesBtn, &QPushButton::clicked, [this](){
//        this->hide();
//        this->m_callback(MessageBoxReply::Yes);
//        this->close();
//    });


}

MeessageBoxCell::~MeessageBoxCell()
{
}

void MeessageBoxCell::reSetText()
{

}

void MeessageBoxCell::setEnterKeyButton(MeessageBoxCell::EnterKeyButton keyBtn)
{
    m_keyBtn = keyBtn;

    switch (m_keyBtn) {
    case EnterKeyButton::Yes_Btn:
        break;
    case EnterKeyButton::No_Btn:
        break;
    }
}

void MeessageBoxCell::setText(const QString& text)
{
    m_text = text;
}

void MeessageBoxCell::setTipsLabelPicture(MsgboxType type)
{
}

void MeessageBoxCell::setInformationBtn()
{

}

void MeessageBoxCell::setQuestionBtn()
{
}

void MeessageBoxCell::setCallback(MessageBoxCallback callback)
{
    m_callback = callback;
}

void MeessageBoxCell::setOkText(QString text)
{
}

void MeessageBoxCell::setCancelText(QString text)
{
}

int MeessageBoxCell::exec()
{
    setEnterKeyButton(m_keyBtn);
    return QDialog::exec();
}

void MeessageBoxCell::keyPressEvent(QKeyEvent *evt)
{
    qDebug() << "msg " << evt;
    if(evt->key() == Qt::Key_Enter || evt->key() == Qt::Key_Return){
        switch (m_keyBtn) {
        case EnterKeyButton::Yes_Btn:
            break;
        case EnterKeyButton::No_Btn:
            break;
        }
        return;
    }

    if (evt->key() == Qt::Key_Escape) {
        return;
    }

    QDialog::keyPressEvent(evt);
}
