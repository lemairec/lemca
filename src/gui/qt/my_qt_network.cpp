#include "my_qt_network.hpp"
#include "include_qt.hpp"
#include "../../framework.hpp"
#include <sstream>
#include <QMetaEnum>
#include <QSerialPortInfo>

#include "../gps_widget.hpp"

#include "environnement.hpp"
#include "../../util/directory_manager.hpp"

QNetworkAccessManager * manager;
MyQTNetwork::MyQTNetwork(){
    manager = new QNetworkAccessManager();
    
    QObject::connect(manager, &QNetworkAccessManager::finished, this,&MyQTNetwork::handleNetwork);
}
void MyQTNetwork::initOrLoad(Config & config){
    m_host_url = "https://maplaine.fr";
    //m_host_url = "http://localhost:4000";//QString::fromStdString(config.m_host_url);
    m_company = QString::fromStdString(config.m_company);
};

void MyQTNetwork::closeAll(){
    INFO("###close all");
}

std::string m_name;
void MyQTNetwork::handleNetwork(QNetworkReply *reply) {
    if (reply->error()) {
        std::string error = reply->errorString().toUtf8().constData();
        WARN(error);
        //Framework::Instance().addError(error);
        Framework::Instance().m_parcelles.erreurSynchro(error);
        return;
    } else {
        std::string s = reply->readAll().toStdString();
        INFO(m_name);
        if(m_name == "parcelles"){
            Framework::Instance().m_parcelles.onParcellesResponse(s);
        } else {
            Framework::Instance().m_parcelles.onParcelleResponse(m_name, s);
        }
    }
};



void MyQTNetwork::handleErrorGps(QSerialPort::SerialPortError error){
    
}

void MyQTNetwork::getParcelles(){
    m_name = "parcelles";
    QNetworkRequest request;

    QString url = m_host_url + "/api/autosteer/parcelles?company=" + m_company;
    INFO(url.toUtf8().constData());
    QUrl serviceUrl = QUrl(url);
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

    manager->get(networkRequest);
    
}

void MyQTNetwork::getParcelle(const std::string & name){
    m_name = name;
    
    
    QString url = m_host_url + "/api/autosteer/parcelle/" + QString::fromStdString(name) + "?company=" + m_company;
    
    INFO(url.toUtf8().constData());
    QNetworkRequest request;
    QUrl serviceUrl = QUrl(url);
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ServerHeader, "application/json");

    manager->get(networkRequest);
}

void MyQTNetwork::saveParcelle(const std::string & name, const std::string & json){
    m_name = name;
    QNetworkRequest request;

    QString url = m_host_url + "/api/autosteer/parcelle?company=" + m_company;
    QUrl serviceUrl = QUrl(url);
    QByteArray postData;

    QUrlQuery query;
    
    INFO("save " << name);
    query.addQueryItem("parcelle", QString::fromStdString(json));
    
    postData = query.toString(QUrl::FullyEncoded).toUtf8();

    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    
    manager->post(networkRequest,postData);
}
