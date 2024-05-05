#ifndef CAMERAS_MODULE_H
#define CAMERAS_MODULE_H

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

class CamerasModules {
public:
    CamerasModules();
    ~CamerasModules();

    std::string m_url_cam1_1;
    std::string m_url_cam1_2;
    std::string m_url_cam1_3;
    std::string m_url_cam2_1;
    std::string m_url_cam2_2;
    std::string m_url_cam2_3;
    std::vector<std::string> m_cam1;
    std::vector<std::string> m_cam2;
    
    
    void refresCams();
    
    void setCam(int i);
    void setCam1();
    void setCam2();
    
    void setPhareCam(int i);
    void setPhareCam1();
    void setPhareCam2();
    
    void handleReply(const std::string & url, const std::string &data);
};

#endif // GPS_FRAMEWORK_H
