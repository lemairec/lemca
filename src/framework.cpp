#include "framework.hpp"
#include "config/config.hpp"
#include "environnement.hpp"
#include "util/util.hpp"
#include "util/directory_manager.hpp"

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
    
}


Framework & Framework::Instance(){
    static Framework gf;
    return gf;
}

Framework::~Framework(){
    m_serial_port.closeAll();
}

void Framework::initOrLoadConfig(){
    m_config.save();
    
    m_serial_port.initOrLoad(m_config);
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
        if(f.m_session){
            f.m_session_str = "lemca_"+std::to_string(f.m_session);
            std::string s = "x11vnc -viewonly -forever -ssh debian@remote.lemcavision.com:590"+std::to_string(f.m_session);
            INFO("session");
            INFO(s);
            //s = "ping google.com";
            system(s.c_str());
        } else if(f.m_config.m_port_remote){
            f.m_session_str = "port_"+std::to_string(f.m_config.m_port_remote);
            std::string s = "x11vnc -forever -ssh debian@51.38.190.75:"+std::to_string(f.m_config.m_port_remote);
            INFO("port");
            INFO(s);
            //s = "ping google.com";
            system(s.c_str());
        }
        mySleep(2000);
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
            FILE* pipe(popen(cmd.c_str(), "r"));
            if (!pipe) {
                throw std::runtime_error("popen() failed!");
            }
            INFO("read");
            f.m_cmd_buffer.clear();
            f.m_cmd_buffer.push_back(cmd);
            f.m_cmd_end = false;
            while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
                INFO("result " <<buffer.data());
                f.mutex.lock();
                f.m_command_result2 += buffer.data();
                
                f.m_cmd_buffer.push_back(buffer.data());
                f.mutex.unlock();
            }
            f.m_cmd_return = pclose(pipe);
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

