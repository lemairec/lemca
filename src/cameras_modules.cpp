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
}

CamerasModules::~CamerasModules(){
}

void CamerasModules::refresCam1(){
    m_cam1.clear();
    MyQTNetwork * m_qt_network = MyQTNetwork::Instance_ptr();
    
    m_url_cam1_1 = "http://192.168.1.30/cgi-bin/control/connectinfo.cgi?id=admin&passwd=admin &action=getconnect&stream=all";
    m_qt_network->callUrl(m_url_cam1_1);
}

void CamerasModules::handleReply(const std::string & url, const std::string &data){
    m_cam1.push_back(data);
}
