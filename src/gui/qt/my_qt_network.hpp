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
    
    MyQTNetwork();
   
    
public:
    static MyQTNetwork * Instance_ptr();
    
    bool m_is_connected = false;
    
    void initOrLoad(Config & config);
    void closeAll();
    
    void test();
    bool m_test_camera = false;
    void testCamera();
    
    void callUrl(const std::string & url);
    
    QString m_cam1_url;
    bool m_cam1_connected = false;
    QString m_cam2_url;
    bool m_cam2_connected = false;
    
    void sendStats();
signals:
    void testSignal();
private:
    QTimer m_timerPilot;
private slots:
    
    void handlePilot();
    void testSlot();
    
    void handleNetwork(QNetworkReply *reply);
    void handleErrorGps(QSerialPort::SerialPortError error);
    
    

};


#endif
