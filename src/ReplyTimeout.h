#ifndef REPLYTIMEOUT_H
#define REPLYTIMEOUT_H

#include <QtNetwork/QNetworkReply>
#include <QTimerEvent>
#include <QBasicTimer>

// https://codereview.stackexchange.com/questions/30031/qnetworkreply-network-reply-timeout-helper
class ReplyTimeout : public QObject
{
    Q_OBJECT
    QBasicTimer m_timer;
public:
    ReplyTimeout(QNetworkReply* reply, const int timeout) : QObject(reply)
    {
        Q_ASSERT(reply);

        if (reply && reply->isRunning())
        {
            m_timer.start(timeout, this);
        }
    }
    static void set(QNetworkReply* reply, const int timeout)
    {
        new ReplyTimeout(reply, timeout);
    }
protected:
    void timerEvent(QTimerEvent * ev)
    {
        if (!m_timer.isActive() || ev->timerId() != m_timer.timerId())
        {
            return;
        }

        auto reply = static_cast<QNetworkReply*>(parent());

        if (reply->isRunning())
        {
            reply->close();
        }

        m_timer.stop();
    }
};

#endif // REPLYTIMEOUT_H
