#include "config.hpp"
#include <QString>
#include <QSettings>
#include "environnement.hpp"
#include "../logging.hpp"
#include "../util/directory_manager.hpp"

Config::Config(){
    m_bineuse_run = "~/bineuse/bineuse";
    m_bineuse_update = "rm -rf ~/bineuse.tar.gz && wget -c https://maplaine.fr/lemca/bineuse.tar.gz && rm -rf bineuse && tar -xzvf bineuse.tar.gz";
    m_bineuse_src_run = "~/bineuse_src/build/bineuse";
    m_bineuse_src_update = "cd ~/bineuse_src && mkdir -p build && git pull && cd build && cmake .. && make -j4; read";
    m_gps_run = "~/agrigpspi/build/agri_gps_pi";
    m_gps_update = "cd ~/agrigpspi && mkdir -p build && git pull && cd build && cmake .. && make -j4; read";
    m_serie_run = "~/serie/build/serie";
    m_serie_update = "cd ~/serie && mkdir -p build && git pull && cd build && cmake .. && make -j4; read";
    m_robot_run = "~/robot/build/robot";
    m_robot_update = "cd ~/robot && mkdir -p build && git pull && cd build && cmake .. && make -j4; read";
    m_make_archive = "cd ~/bineuse_src; git pull; sh make_archive.sh && read";
    m_update_lemca = "cd ~/lemca && git pull && rm -rf build_old && mv build build_old && mkdir build && cd build && cmake .. && make -j4; read";
    
}

void Config::save(){
    std::string s = CONFIG_FILE;
    QString path = QString::fromStdString(s);
    QSettings settings(path, QSettings::IniFormat);
    
     
    
    settings.setValue("code_source", m_code_source);
    settings.setValue("m_gps", m_gps);
    settings.setValue("m_fullscreen", m_fullscreen);
    settings.setValue("m_robot", m_robot);
    settings.setValue("m_serial", m_serial);
    
    
    
    settings.setValue("m_bineuse_src_run", QString::fromStdString(m_bineuse_src_run));
    settings.setValue("m_bineuse_src_update", QString::fromStdString(m_bineuse_src_update));
    settings.setValue("m_bineuse_run", QString::fromStdString(m_bineuse_run));
    settings.setValue("m_bineuse_update", QString::fromStdString(m_bineuse_update));
    settings.setValue("m_gps_run", QString::fromStdString(m_gps_run));
    settings.setValue("m_gps_update", QString::fromStdString(m_gps_update));
    settings.setValue("m_serie_run", QString::fromStdString(m_serie_run));
    settings.setValue("m_serie_update", QString::fromStdString(m_serie_update));
    settings.setValue("m_robot_run", QString::fromStdString(m_robot_run));
    settings.setValue("m_robot_update", QString::fromStdString(m_robot_update));
    settings.setValue("m_make_archive", QString::fromStdString(m_make_archive));
    settings.setValue("m_update_lemca", QString::fromStdString(m_update_lemca));
}

void Config::load(){
    std::string s = CONFIG_FILE;
    QString qpath = QString::fromStdString(s);
    QSettings settings(qpath, QSettings::IniFormat);
    
    if(settings.contains("code_source")){
        m_code_source = settings.value("code_source").toBool();
        //m_code_source = settings.value("code_source").toString().toUtf8().constData();
    }
    if(settings.contains("m_gps")){
        m_gps = settings.value("m_gps").toBool();
    }
    if(settings.contains("m_fullscreen")){
        m_fullscreen = settings.value("m_fullscreen").toBool();
    }
    if(settings.contains("m_robot")){
        m_robot = settings.value("m_robot").toBool();
    }
    if(settings.contains("m_serial")){
        m_serial = settings.value("m_serial").toBool();
    }
    
    if(settings.contains("m_bineuse_src_run")){
        m_bineuse_src_run = settings.value("m_bineuse_src_run").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_bineuse_src_update")){
        m_bineuse_src_update = settings.value("m_bineuse_src_update").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_bineuse_run")){
        m_bineuse_run = settings.value("m_bineuse_run").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_bineuse_update")){
        m_bineuse_update = settings.value("m_bineuse_update").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_gps_run")){
        m_gps_run = settings.value("m_gps_run").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_gps_update")){
        m_gps_update = settings.value("m_gps_update").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_serie_run")){
        m_serie_run = settings.value("m_serie_run").toString().toUtf8().constData();
    }
    if(settings.contains("m_serie_run")){
        m_serie_run = settings.value("m_serie_run").toString().toUtf8().constData();
    }
    if(settings.contains("m_serie_update")){
        m_serie_update = settings.value("m_serie_update").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_robot_run")){
        m_robot_run = settings.value("m_robot_run").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_robot_update")){
        m_robot_update = settings.value("m_robot_update").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_make_archive")){
        m_make_archive = settings.value("m_make_archive").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_update_lemca")){
        m_update_lemca = settings.value("m_update_lemca").toString().toUtf8().constData();
    }
}
