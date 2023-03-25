#include "framework.hpp"
#include "config/config.hpp"
#include "config/langage.hpp"
#include "environnement.hpp"
#include "util/util.hpp"
#include "util/directory_manager.hpp"
#include "gui/qt/my_qt_network.hpp"

#include <QDateTime>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string file_info;
std::ofstream file_job_stream;
std::ofstream file_debug_stream;
std::string date_str;

Framework::Framework(){
    QDateTime date = QDateTime::currentDateTime();
    QString s = date.toString("yyyyMMddThhmm");
    date_str = s.toUtf8().constData();
    
    int y = date.date().year();
    if(y>(1011+1011)){
    //    exit(0);
    }
    
    m_config.load();
    Langage::setLangage(m_config.m_langage);
    
}


Framework & Framework::Instance(){
    static Framework gf;
    return gf;
}

Framework::~Framework(){
    m_serial_port.closeAll();
}

void Framework::initOrLoadConfig(){
    m_config.validate();
    m_config.save();
    
    m_serial_port.initOrLoad(m_config);
    Langage::setLangage(m_config.m_langage);
}


void Framework::abortCurrentRun(){
    Framework & f = Framework::Instance();
    f.m_cmd_return = pclose(f.m_pipe);
}


RemoteConsumer & RemoteConsumer::instance(){
    static RemoteConsumer gf;
    return gf;
}

RemoteConsumer::~RemoteConsumer()
{
    m_stop = true;
    INFO("destructor Consumer");
}


void RemoteConsumer::run(){
    Framework & f = Framework::Instance();
    while(true){
        MyQTNetwork *q = MyQTNetwork::Instance_ptr();
        q->test();
        std::string s;
        if(f.m_session){
            f.m_session_str = "lemca_"+std::to_string(f.m_session);
            s = "x11vnc ";
            if(f.m_config.m_control_view_only){
                s = s + "-viewonly ";
            }
            s = s + "-forever -ssh 5chmlLEM1cale26@remote.lemcavision.com:590"+std::to_string(f.m_session);
            INFO("session");
        } else if(f.m_config.m_port_remote){
            f.m_session_str = "port_593"+std::to_string(f.m_config.m_port_remote);
            std::string s = "x11vnc -forever -ssh 5chmlLEM1cale26@remote.lemcavision.com:593"+std::to_string(f.m_config.m_port_remote);
            INFO("port");
        }
        s += " 2>&1";
        INFO(s);
        
        char buffer[128];
        FILE * my_pipe = popen(s.c_str(), "r");
        if (!my_pipe) {
            INFO("error3");
        }
        std::string error = "";
        f.m_remote_error = "";
        INFO("launch");
        while (fgets(buffer, 128, my_pipe) != nullptr) {
            INFO("result " <<buffer);
            error = buffer;
            f.mutex.lock();
            f.m_command_result2 += buffer;
            
            f.m_cmd_buffer.push_back(buffer);
            f.mutex.unlock();
        }
        f.m_remote_error = error;
        INFO("error" << error);
        mySleep(5000);
    }
   
}
