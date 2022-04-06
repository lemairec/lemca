#include "config.hpp"
#include <QString>
#include <QSettings>
#include "environnement.hpp"
#include "../util/log.hpp"
#include "../util/directory_manager.hpp"

Config::Config(){
    m_bineuse_run = "~/bineuse/bineuse";
    m_bineuse_update = "rm -rf bineuse && tar -xzvf bineuse.tar.gz";
    m_bineuse_update_wifi = "rm -rf ~/bineuse.tar.gz && wget -c https://maplaine.fr/lemca/bineuse.tar.gz && "+m_bineuse_update;
    m_bineuse_src_run = "~/bineuse_src/build/bineuse";
    m_gps_run = "~/agrigpspi/build/agri_gps_pi";
    m_serie_run = "~/serie/build/serie";
    m_robot_inrows_run = "~/inrows/build/inrows";
    m_make_archive = "cd ~/bineuse_src; git pull; sh make_archive.sh";
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
    settings.setValue("m_bineuse_run", QString::fromStdString(m_bineuse_run));
    settings.setValue("m_bineuse_update", QString::fromStdString(m_bineuse_update));
    settings.setValue("m_bineuse_update_wifi", QString::fromStdString(m_bineuse_update_wifi));
    settings.setValue("m_gps_run", QString::fromStdString(m_gps_run));
    settings.setValue("m_serie_run", QString::fromStdString(m_serie_run));
    settings.setValue("m_robot_inrows_run", QString::fromStdString(m_robot_inrows_run));
    settings.setValue("m_make_archive", QString::fromStdString(m_make_archive));
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
        m_robot = settings.value("m_robot").toInt();
    }
    if(settings.contains("m_serial")){
        m_serial = settings.value("m_serial").toBool();
    }
    
    if(settings.contains("m_bineuse_src_run")){
        m_bineuse_src_run = settings.value("m_bineuse_src_run").toString().toUtf8().constData();
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
    
    
    if(settings.contains("m_serie_run")){
        m_serie_run = settings.value("m_serie_run").toString().toUtf8().constData();
    }
    if(settings.contains("m_serie_run")){
        m_serie_run = settings.value("m_serie_run").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_robot_inrows_run")){
        m_robot_inrows_run = settings.value("m_robot_inrows_run").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_make_archive")){
        m_make_archive = settings.value("m_make_archive").toString().toUtf8().constData();
    }
}
