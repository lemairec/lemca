#include "my_qt_network.hpp"
#include "include_qt.hpp"
#include "../../framework.hpp"
#include <sstream>
#include <QMetaEnum>
#include <QSerialPortInfo>

#include "environnement.hpp"
#include "../../util/directory_manager.hpp"

MyQTNetwork * MyQTNetwork::Instance_ptr(){
    static MyQTNetwork gf;
    return &gf;
}

QNetworkAccessManager * manager;
MyQTNetwork::MyQTNetwork(){
    manager = new QNetworkAccessManager();
    
    QObject::connect(manager, &QNetworkAccessManager::finished, this,&MyQTNetwork::handleNetwork);
    connect(this, SIGNAL(testSignal()), this, SLOT(testSlot()));
    connect(&m_timerPilot, SIGNAL(timeout()), this, SLOT(handlePilot()));
    
    m_host_url = "https://cloud.lemcavision.com/ping";
    
    m_cam1_url = "http://192.168.1.30";
    m_cam2_url = "http://192.168.1.31";
    
    m_timerPilot.stop();
    m_timerPilot.start(1000); //1s
}
void MyQTNetwork::initOrLoad(Config & config){
    //m_host_url = "http://localhost:4000";
};

void MyQTNetwork::closeAll(){
    INFO("###close all");
}

std::string m_name;
void MyQTNetwork::handleNetwork(QNetworkReply *reply) {
    if (reply->error()) {
        std::string error = reply->errorString().toUtf8().constData();
        if(reply->url() == m_host_url){
            m_is_connected = false;
        } else if (reply->url() == m_cam1_url){
            m_cam1_connected = false;
        } else if (reply->url() == m_cam2_url){
            m_cam2_connected = false;
        } else {
            WARN("pas bien error");
        }
        return;
    } else {
        std::string s = reply->readAll().toStdString();
        if(reply->url() == m_host_url){
            m_is_connected = true;
        } else if (reply->url() == m_cam1_url){
            m_cam1_connected = true;
        } else if (reply->url() == m_cam2_url){
            m_cam2_connected = true;
        } else {
            WARN("pas bien");
        }
    }
};



void MyQTNetwork::handleErrorGps(QSerialPort::SerialPortError error){
    
}

void MyQTNetwork::test(){
    emit testSignal();
}

void MyQTNetwork::testSlot(){
    QNetworkRequest request;

    QString url = m_host_url;
    INFO(url.toUtf8().constData());
    QUrl serviceUrl = QUrl(url);
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

    manager->get(networkRequest);
    
}

void MyQTNetwork::testCamera(){
    {
        QNetworkRequest request;

        QString url = m_cam1_url;
        //INFO(url.toUtf8().constData());
        QUrl serviceUrl = QUrl(url);
        QNetworkRequest networkRequest(serviceUrl);
        networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

        manager->get(networkRequest);
    }
    {
        QNetworkRequest request;

        QString url = m_cam2_url;
        //INFO(url.toUtf8().constData());
        QUrl serviceUrl = QUrl(url);
        QNetworkRequest networkRequest(serviceUrl);
        networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

        manager->get(networkRequest);
    }
}

void MyQTNetwork::handlePilot(){
    if(m_test_camera){
        testCamera();
    } else {
        //INFO("la");
    }
    
}

void MyQTNetwork::sendStats(){
    Framework & f = Framework::Instance();
    QString url = "https://cloud.lemcavision.com/panel/post_stats";
    
    QJsonObject obj;
    obj["panel"] = QString::fromStdString(f.m_config.m_panel);
    obj["gps_enable"] = QString::number(f.m_config.m_gps);
    obj["langage"] = QString::fromStdString(f.m_config.m_langage);
    obj["constructor"] = QString::number(f.m_config.m_constructor);
    obj["remote"] = QString::number(f.m_config.m_remote);
    
    
    std::string path_bineuse = DirectoryManager::instance().getHome()+"/lemca_data/bineuse/stat.txt";
    INFO(path_bineuse);
    QString s3 = QString::fromStdString(path_bineuse);
    QFile file(s3);
    file.open(QIODevice::ReadOnly);
    QTextStream s(&file);
    QJsonDocument jsonResponse = QJsonDocument::fromJson(s.readAll().toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    obj["bineuse"] = jsonObject;
    
    
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();
    
    QUrl serviceUrl = QUrl(url);
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    manager->post(networkRequest, data);
}
