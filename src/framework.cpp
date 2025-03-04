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
