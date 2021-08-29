#include "framework.hpp"
#include "logging.hpp"
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

void makedir(std::string dir2){
    std::string dir = DirectoryManager::Instance().getBinDirectory() + dir2;
    std::string s2 = "mkdir -p "+ dir + ";";
    INFO(s2);
    if(system( s2.c_str() )){
        WARN("can not execute : " << s2);
    };
}

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


void Consumer::run(){
    while(true){
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
        } else {
            INFO("wait");
            f.mutex.lock();
            f.bufferNotEmpty.wait(&f.mutex);
            f.mutex.unlock();
            INFO("wait end");
            
        }
    }
}

