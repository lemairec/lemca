#include "my_qt_network.hpp"
#include "include_qt.hpp"
#include "../../framework.hpp"
#include <sstream>
#include <QMetaEnum>
#include <QSerialPortInfo>

#include "environnement.hpp"
#include "../../util/directory_manager.hpp"

QNetworkAccessManager * manager;
MyQTNetwork::MyQTNetwork(){
    manager = new QNetworkAccessManager();
    
    QObject::connect(manager, &QNetworkAccessManager::finished, this,&MyQTNetwork::handleNetwork);
    
    m_host_url = "https://maplaine.fr/lemca/ping";
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
        WARN(error);
        m_is_connected = false;
        return;
    } else {
        std::string s = reply->readAll().toStdString();
        m_is_connected = true;
        /*INFO(m_name);
        if(m_name == "parcelles"){
            Framework::Instance().m_parcelles.onParcellesResponse(s);
        } else {
            Framework::Instance().m_parcelles.onParcelleResponse(m_name, s);
        }*/
    }
};



void MyQTNetwork::handleErrorGps(QSerialPort::SerialPortError error){
    
}

void MyQTNetwork::test(){
    QNetworkRequest request;

    QString url = m_host_url;
    INFO(url.toUtf8().constData());
    QUrl serviceUrl = QUrl(url);
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

    manager->get(networkRequest);
    
}
