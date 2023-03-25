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

Consumer & Consumer::instance(){
    static Consumer gf;
    return gf;
}

Consumer::~Consumer()
{
    m_stop = true;
    INFO("destructor Consumer");
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
        if(f.m_config.m_port_remote){
            f.m_session_str = "port_593"+std::to_string(f.m_config.m_port_remote);
            std::string s = "x11vnc -forever -ssh 5chmlLEM1cale26@remote.lemcavision.com:593"+std::to_string(f.m_config.m_port_remote);
            INFO("port");
            INFO(s);
        } else if(f.m_session){
            f.m_session_str = "lemca_"+std::to_string(f.m_session);
            s = "x11vnc ";
            if(f.m_config.m_control_view_only){
                s = s + "-viewonly ";
            }
            s = s + "-forever -ssh 5chmlLEM1cale26@remote.lemcavision.com:590"+std::to_string(f.m_session);
            INFO("session");
            INFO(s);
        }
        s += " 2>&1";
        
        
        char buffer[128];
        FILE * my_pipe = popen(s.c_str(), "r");
        if (!my_pipe) {
            throw std::runtime_error("popen() failed!");
        }
        std::string error = "";
        f.m_remote_error = "";
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



#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

void Consumer::run(){
    while(!m_stop){
        Framework & f = Framework::Instance();
        if(f.m_command_to_execute.size()>0){
                
            f.mutex.lock();
            std::string s = f.m_command_to_execute;
            f.mutex.unlock();
            system(s.c_str());
            
            f.mutex.lock();
            f.m_is_f_call = false;
            f.m_command_to_execute.clear();
            f.mutex.unlock();
        } else if(f.m_command_to_execute2.size()>0){
            std::array<char, 128> buffer;
            f.mutex.lock();
            f.m_command_result2 = "";
            std::string cmd = f.m_command_to_execute2;
            INFO("exec " << cmd);
            f.mutex.unlock();
            f.m_pipe = popen(cmd.c_str(), "r");
            if (!f.m_pipe) {
                throw std::runtime_error("popen() failed!");
            }
            INFO("read");
            f.m_cmd_buffer.clear();
            f.m_cmd_buffer.push_back(cmd);
            f.m_cmd_end = false;
            f.m_cmd_abort = false;
            while (!f.m_cmd_abort && fgets(buffer.data(), buffer.size(), f.m_pipe) != nullptr) {
                INFO("result " <<buffer.data());
                f.mutex.lock();
                f.m_command_result2 += buffer.data();
                
                f.m_cmd_buffer.push_back(buffer.data());
                f.m_cmd_buffer.push_back("----");
                f.mutex.unlock();
            }
            f.m_cmd_return = pclose(f.m_pipe);
            INFO("returnCode " << f.m_cmd_return);
            
            f.m_cmd_end = true;
            INFO("end read");
            f.m_command_to_execute2 = "";
            
        }
        {
            INFO("wait");
            f.mutex.lock();
            f.bufferNotEmpty.wait(&f.mutex);
            f.mutex.unlock();
            INFO("wait end");
            
        }
    }
    INFO("stop");
}

