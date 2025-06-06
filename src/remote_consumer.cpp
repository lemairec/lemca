#include "remote_consumer.hpp"
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
    f.m_remote_nbr_error = 0;
    f.m_cmd_remote_buffer.push_back("*******");
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
            } else if(f.m_config.m_constructor == 7){
                port = 5920 + f.m_session;
                name = "oliver_"+std::to_string(f.m_session);
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
        f.m_remote_connection_ok = 0;
        std::string s2 = "ssh -o NumberOfPasswordPrompts=0 -o StrictHostKeyChecking=no 5chmlLEM1cale26@remote.lemcavision.com \"sh new_connection.sh "+name+"_"+f.m_config.m_panel+"\";";
        char buffer[128];
        FILE * my_pipe = popen(s2.c_str(), "r");
        if (!my_pipe) {
            f.m_cmd_remote_buffer.push_back("error pipe 2");
        }
        std::string error2 = "";
        f.m_cmd_remote_buffer.push_back("=====");
        f.m_cmd_remote_buffer.push_back("launch 1");
        f.m_cmd_remote_buffer.push_back(s2);
        f.m_cmd_remote_buffer.push_back("---");
        while (fgets(buffer, 128, my_pipe) != nullptr) {
            std::string buffer2(buffer);
            if(buffer2.find("connection_ok") == 0){
                f.m_remote_connection_ok = 1;
                f.m_cmd_remote_buffer.push_back("conn ok");
            }
            f.m_cmd_remote_buffer.push_back(buffer);
        }
        f.m_cmd_remote_buffer.push_back("---");
        f.m_cmd_remote_buffer.push_back("");
        
        if(f.m_remote_connection_ok == 1){
            std::string s;
            s = s + " x11vnc ";
            if(view_only){
                s = s + "-viewonly ";
            }
            s = s + "-ssh 5chmlLEM1cale26@remote.lemcavision.com:"+std::to_string(port);
            s += " 2>&1";
            
            f.m_cmd_remote_buffer.push_back("=====");
            f.m_cmd_remote_buffer.push_back("launch");
            f.m_cmd_remote_buffer.push_back(s);
            f.m_cmd_remote_buffer.push_back("---");
            
            my_pipe = popen(s.c_str(), "r");
            if (!my_pipe) {
                f.m_cmd_remote_buffer.push_back("error pipe 3");
            }
            
            std::string error3 = "";
            while (fgets(buffer, 128, my_pipe) != nullptr) {
                error3 = buffer;
                f.m_cmd_remote_buffer.push_back(buffer);
            }
            f.m_cmd_remote_buffer.push_back("---");
            f.m_cmd_remote_buffer.push_back("");
           
        } else {
            std::string s2 = "sh " + DirectoryManager::instance().getSourceDirectory() + "/src/sh/ssh-key-gen.sh;";
            char buffer[128];
            FILE * my_pipe = popen(s2.c_str(), "r");
            if (!my_pipe) {
                INFO("error3");
            }
            std::string error0 = "";
            f.m_cmd_remote_buffer.push_back("=====");
            f.m_cmd_remote_buffer.push_back("launch 3");
            f.m_cmd_remote_buffer.push_back(s2);
            f.m_cmd_remote_buffer.push_back("---");
            
            while (fgets(buffer, 128, my_pipe) != nullptr) {
                INFO("result1 " <<buffer);
                error0 = buffer;
                f.m_cmd_remote_buffer.push_back(buffer);
            }
            f.m_cmd_remote_buffer.push_back("---");
            f.m_cmd_remote_buffer.push_back("");
           
            s2 = "sh " + DirectoryManager::instance().getSourceDirectory() + "/src/sh/remote_update.sh;";
            f.m_cmd_remote_buffer.push_back("=====");
            f.m_cmd_remote_buffer.push_back("launch 4");
            f.m_cmd_remote_buffer.push_back(s2);
            f.m_cmd_remote_buffer.push_back("---");
            my_pipe = popen(s2.c_str(), "r");
            if (!my_pipe) {
                f.m_cmd_remote_buffer.push_back("error pipe 1");
            }
            std::string error1 = "";
            while (fgets(buffer, 128, my_pipe) != nullptr) {
                error1 = buffer;
                f.m_cmd_remote_buffer.push_back(buffer);
            }
            f.m_cmd_remote_buffer.push_back("---");
            f.m_cmd_remote_buffer.push_back("");
           
        }
        f.m_remote_nbr_error++;
        mySleep(5000);
    }
   
}
