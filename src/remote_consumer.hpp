#ifndef REMOTE_CONSUMER_H
#define REMOTE_CONSUMER_H


#include <QThread>

class RemoteConsumer : public QThread
{
    bool m_stop = false;
    Q_OBJECT

    RemoteConsumer(QObject *parent = NULL) : QThread(parent)
    {
    }
public:
    static RemoteConsumer & instance();
    ~RemoteConsumer();

    void run() override;
};

#endif // GPS_FRAMEWORK_H
