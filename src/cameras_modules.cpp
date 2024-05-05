#include "framework.hpp"
#include "cameras_modules.hpp"
#include "gui/qt/my_qt_network.hpp"

#include <QDateTime>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
CamerasModules::CamerasModules(){
    m_url_cam1_1 = "http://192.168.1.30/cgi-bin/control/connectinfo.cgi?id=admin&passwd=admin&action=getconnect&stream=all";
    m_url_cam1_2 = "http://192.168.1.30/cgi-bin/control/serverinfo3.cgi?id=admin&passwd=admin&action=getsysinfo3";
    m_url_cam1_3 = "http://192.168.1.30/cgi-bin/control/camwdr.cgi?id=admin&passwd=admin&action=getdnr&stream=all";
    
    m_url_cam2_1 = "http://192.168.1.31/cgi-bin/control/connectinfo.cgi?id=admin&passwd=admin&action=getconnect&stream=all";
    m_url_cam2_2 = "http://192.168.1.31/cgi-bin/control/serverinfo3.cgi?id=admin&passwd=admin&action=getsysinfo3";
    m_url_cam2_3 = "http://192.168.1.31/cgi-bin/control/camwdr.cgi?id=admin&passwd=admin&action=getdnr&stream=all";
    
}

CamerasModules::~CamerasModules(){
}

void CamerasModules::refresCam1(){
    m_cam1.clear();
    MyQTNetwork * m_qt_network = MyQTNetwork::Instance_ptr();
    m_qt_network->callUrl(m_url_cam1_1);
    m_qt_network->callUrl(m_url_cam1_2);
    m_qt_network->callUrl(m_url_cam1_3);
}

void CamerasModules::refresCam2(){
    m_cam2.clear();
    MyQTNetwork * m_qt_network = MyQTNetwork::Instance_ptr();
    m_qt_network->callUrl(m_url_cam2_1);
    m_qt_network->callUrl(m_url_cam2_2);
    m_qt_network->callUrl(m_url_cam2_3);
}

void CamerasModules::handleReply(const std::string & url, const std::string &data){
    if(url == m_url_cam1_1 || url == m_url_cam1_2 || url == m_url_cam1_3){
        QStringList list1 = QString::fromStdString(data).split(QLatin1Char('\n'));
        for(auto s3 : list1){
            if(s3.size()>5){
                m_cam1.push_back(s3.toUtf8().constData());
            }
        }
    } else if(url == m_url_cam2_1 || url == m_url_cam2_2 || url == m_url_cam2_3){
        QStringList list1 = QString::fromStdString(data).split(QLatin1Char('\n'));
        for(auto s3 : list1){
            if(s3.size()>5){
                m_cam2.push_back(s3.toUtf8().constData());
            }
        }
    }
    
}
