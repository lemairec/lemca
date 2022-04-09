#ifndef NETWORK_QT_H
#define NETWORK_QT_H

#include <QtSerialPort/QSerialPort>

#include "../../config/config.hpp"
#include <QTextStream>
#include <QByteArray>
#include <QObject>
#include <QTimer>
#include <QtNetwork>

QT_USE_NAMESPACE

class MyQTNetwork : public QObject{
    Q_OBJECT
    
    QString m_host_url;
public:
    bool m_is_connected = false;
    MyQTNetwork();
    
    void initOrLoad(Config & config);
    void closeAll();
    
    void test();
private slots:
    void handleNetwork(QNetworkReply *reply);
    void handleErrorGps(QSerialPort::SerialPortError error);
};


#endif
