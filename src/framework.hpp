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
#include <QWaitCondition>
#include <QMutex>

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

    std::string m_messages_errors;
    void addError(std::string s);

    Config m_config;
    
    MyQTSerialPorts m_serial_port;
    
    QMutex mutex;
    std::string m_command_to_execute;
    std::string m_command_result;
    std::string m_command_to_execute2;
    std::string m_command_result2;
    bool m_command_to_execute2_end;
    QWaitCondition bufferNotEmpty;
    bool m_is_f_call = false;
    
    bool m_cmd_interrupt = false;
    int m_cmd_pid = 0;
    FILE* m_cmd_process;
    std::vector<std::string> m_cmd_buffer;
    bool m_cmd_end = false;
    
    int m_cmd_return = 0;
private:
    void readFile();
};

class Consumer : public QThread
{
    bool m_stop = false;
    Q_OBJECT

    Consumer(QObject *parent = NULL) : QThread(parent)
    {
    }
public:
    static Consumer & instance();
    ~Consumer();

    void run() override;

signals:
    void stringConsumed(const QString &text);
};


#endif // GPS_FRAMEWORK_H
