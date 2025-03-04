#ifndef GPS_FRAMEWORK_H
#define GPS_FRAMEWORK_H

#include "gui/qt/my_qt_serial_port.hpp"
#include "config/config.hpp"
#include <chrono>
#include <QThread>
#include <time.h>
#include <math.h>
#include "util/log.hpp"
#include "util/stat.hpp"
#include "cameras_modules.hpp"

class IGpsObserver {
public:
    virtual void onNewPoint() = 0;
};

class Categorie {
public:
    std::string m_begin;
    int m_count = 0;
    bool m_enable = true;
    std::string m_last = "";
};

class Framework {
    Framework();
    
    void saveInfoFile();
public:
    static Framework & Instance();
    ~Framework();
    void initOrLoadConfig();
    
    CamerasModules m_cameras_module;

    std::string m_messages_errors;
    void addError(std::string s);

    Config m_config;
    
    MyQTSerialPorts m_serial_port;
    
    int m_session = 0;
    std::string m_session_str;
private:
    void readFile();
    
    
private:

public:
    FILE * m_pipe = NULL;
    std::string m_command_to_execute;
    std::string m_command_result;
    std::string m_command_to_execute2;
    bool m_command_to_execute2_end;
    bool m_is_f_call = false;
    
    bool m_cmd_interrupt = false;
    std::vector<std::string> m_cmd_buffer;
    bool m_cmd_end = false;
    bool m_cmd_abort = false;
    
    int m_cmd_return = 0;
    
    std::vector<std::string> m_cmd_remote_buffer;
    int m_remote_connection_ok = 0;
    std::string m_remote_error = "";
    int m_remote_nbr_error = 0;
    
    void abortCurrentRun();

};

class RemoteConsumer : public QThread
{
    bool m_stop = false;
    Q_OBJECT

    RemoteConsumer(QObject *parent = NULL) : QThread(parent)
    {
    }
public:
    static RemoteConsumer & instance();
    ~RemoteConsumer();

    void run() override;
};

#endif // GPS_FRAMEWORK_H
