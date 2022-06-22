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


#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


#define READ   0
#define WRITE  1
FILE * popen2(std::string command, std::string type, int & pid)
{
    pid_t child_pid;
    int fd[2];
    pipe(fd);

    if((child_pid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    /* child process */
    if (child_pid == 0)
    {
        if (type == "r")
        {
            close(fd[READ]);    //Close the READ end of the pipe since the child's fd is write-only
            dup2(fd[WRITE], 1); //Redirect stdout to pipe
        }
        else
        {
            close(fd[WRITE]);    //Close the WRITE end of the pipe since the child's fd is read-only
            dup2(fd[READ], 0);   //Redirect stdin to pipe
        }

        setpgid(child_pid, child_pid); //Needed so negative PIDs can kill children of /bin/sh
        execl("/bin/sh", "/bin/sh", "-c", command.c_str(), NULL);
        exit(0);
    }
    else
    {
        if (type == "r")
        {
            close(fd[WRITE]); //Close the WRITE end of the pipe since parent's fd is read-only
        }
        else
        {
            close(fd[READ]); //Close the READ end of the pipe since parent's fd is write-only
        }
    }

    pid = child_pid;

    if (type == "r")
    {
        return fdopen(fd[READ], "r");
    }

    return fdopen(fd[WRITE], "w");
}

#include <sys/wait.h>

int pclose2(FILE * fp, pid_t pid)
{
    int stat;

    fclose(fp);
    while (waitpid(pid, &stat, 0) == -1)
    {
        if (errno != EINTR)
        {
            stat = -1;
            break;
        }
    }

    return stat;
}




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
            int pid;
            std::string command = f.m_command_to_execute2;
            FILE * fp = popen2(command, "r", pid);
            INFO("COMMAND: "<< command);
            INFO("PID: "<< pid);
            
            f.m_cmd_end = false;
            f.m_cmd_pid = pid;
            f.m_cmd_buffer.clear();
            f.m_cmd_buffer.push_back("COMMAND: "+command);
            f.m_cmd_buffer.push_back("PID: "+std::to_string(pid));
            f.m_cmd_buffer.push_back("");
            
            char command_out[100] = {0};
            std::stringstream output;

            //Using read() so that I have the option of using select() if I want non-blocking flow
            while (read(fileno(fp), command_out, sizeof(command_out)-1) != 0)
            {
                f.m_cmd_buffer.push_back(command_out);
                output << std::string(command_out);
                //kill(-pid, 9);
                memset(&command_out, 0, sizeof(command_out));
            }

            INFO("end");
            
            f.m_cmd_return = pclose2(fp, pid);
            INFO("end2");
            f.m_cmd_end = true;
            f.m_cmd_pid = 0;
            f.m_session = 0;
            f.m_session_str = "";
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

