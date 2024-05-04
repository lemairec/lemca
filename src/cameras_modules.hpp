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
    std::vector<std::string> m_cam1;
    
    
    void refresCam1();
    
    void handleReply(const std::string & url, const std::string &data);
};

#endif // GPS_FRAMEWORK_H
