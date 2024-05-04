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
        int port = 5900;
        std::string name = "lemca";
        bool view_only = true;
        if(f.m_session){
            if(f.m_config.m_constructor == 3){
                port = 5910 + f.m_session;
                name = "binnove_"+std::to_string(f.m_session);
            } else {
                port = 5900 + f.m_session;
                name = "lemca_"+std::to_string(f.m_session);
            }
            f.m_session_str = name;
            view_only = f.m_config.m_control_view_only;
            
        } else if(f.m_config.m_port_remote){
            view_only = false;
            port = 5930 + f.m_config.m_port_remote;
            name = "robot_" + std::to_string(f.m_config.m_port_remote);
            f.m_session_str = name;
            INFO("port");
        }
        
        
        f.m_remote_error = "";
       
        std::string s2 = "sh " + DirectoryManager::instance().getSourceDirectory() + "/src/sh/ssh-key-gen.sh;";
        char buffer[128];
        FILE * my_pipe = popen(s2.c_str(), "r");
        if (!my_pipe) {
            INFO("error3");
        }
        std::string error0 = "";
        INFO("launch");
        while (fgets(buffer, 128, my_pipe) != nullptr) {
            INFO("result1 " <<buffer);
            error0 = buffer;
            f.mutex.lock();
            f.m_cmd_remote_buffer.push_back(buffer);
            f.mutex.unlock();
        }
        
        
        
        s2 = "sh " + DirectoryManager::instance().getSourceDirectory() + "/src/sh/remote_update.sh;";
        my_pipe = popen(s2.c_str(), "r");
        if (!my_pipe) {
            INFO("error3");
        }
        std::string error1 = "";
        INFO("launch");
        while (fgets(buffer, 128, my_pipe) != nullptr) {
            INFO("result1 " <<buffer);
            error1 = buffer;
            f.mutex.lock();
            f.m_cmd_remote_buffer.push_back(buffer);
            f.mutex.unlock();
        }
        
        
        f.m_remote_connection_ok = false;
        s2 = "ssh -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com \"sh new_connection.sh "+name+"\";";
        my_pipe = popen(s2.c_str(), "r");
        if (!my_pipe) {
            INFO("error3");
        }
        std::string error2 = "";
        INFO("launch");
        while (fgets(buffer, 128, my_pipe) != nullptr) {
            INFO("result " <<buffer);
            std::string buffer2(buffer);
            if(buffer2.find("connection_ok")){
                f.m_remote_connection_ok = true;
            }
            error2 = buffer;
            f.mutex.lock();
            f.m_cmd_remote_buffer.push_back(buffer);
            f.mutex.unlock();
        }
        
        if(f.m_remote_connection_ok){
            std::string s;
            s = s + " x11vnc ";
            if(view_only){
                s = s + "-viewonly ";
            }
            s = s + "-forever -ssh 5chmlLEM1cale26@remote.lemcavision.com:"+std::to_string(port);
            s += " 2>&1";
            INFO(s);
            
            my_pipe = popen(s.c_str(), "r");
            if (!my_pipe) {
                INFO("error3");
            }
            
            std::string error3 = "";
            INFO("launch");
            while (fgets(buffer, 128, my_pipe) != nullptr) {
                INFO("result " <<buffer);
                error3 = buffer;
                f.mutex.lock();
                f.m_cmd_remote_buffer.push_back(buffer);
                f.mutex.unlock();
            }
            f.m_remote_error = "0 " + error0;
            f.m_remote_error += "1 " + error1;
            f.m_remote_error += "\n2 " + error2;
            f.m_remote_error += "\n3 " + error3;
            INFO("error" << f.m_remote_error);
            
        }
        mySleep(5000);
    }
   
}
