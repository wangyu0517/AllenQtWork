#include "singnalguard.h"

//QObject* SingnalGuard::distoryMonitor = nullptr;
SingnalGuard::SingnalGuard()
{

}

SingnalGuard::~SingnalGuard()
{
    std::for_each(infos.begin(), infos.end(), std::mem_fn(&SignalerInfo::disconnect));
}

void SingnalGuard::establish(const QObject *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType type)
{
    SignalerInfo info(sender, signal, receiver, member, type);
    info.connect();
    infos.push_back(info);
}

SignalerInfo::SignalerInfo()
    : sender(sender), signal(signal),
      receiver(receiver), member(member),
      type(type), init(true)
{

}

SignalerInfo::SignalerInfo(const QObject *sender, const char *signal, const QObject *receiver, const char *member, Qt::ConnectionType type)
{

}

void SignalerInfo::connect()
{
    if (! init) {   return; }
    receiver->connect(sender, signal, receiver, member, type);
}

void SignalerInfo::disconnect()
{
    if (! init) {   return; }
    receiver->disconnect(sender, signal, receiver, member);
}
