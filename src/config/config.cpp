#include "config.hpp"
#include <QString>
#include <QSettings>
#include "environnement.hpp"
#include "../logging.hpp"
#include "../util/directory_manager.hpp"

Config::Config(){
}

void Config::save(){
    std::string s = CONFIG_FILE;
    QString path = QString::fromStdString(s);
    QSettings settings(path, QSettings::IniFormat);
    
     
    
    settings.setValue("code_source", m_code_source);
    settings.setValue("m_gps", m_gps);
    settings.setValue("m_fullscreen", m_fullscreen);
    
    settings.setValue("m_bineuse_src_run", m_fullscreen);
    settings.setValue("m_bineuse_src_update", m_fullscreen);
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
    if(settings.contains("m_bineuse_src_run")){
        m_bineuse_src_run = settings.value("m_bineuse_src_run").toString().toUtf8().constData();
    }
    
    if(settings.contains("m_bineuse_src_update")){
        m_bineuse_src_update = settings.value("m_bineuse_src_update").toString().toUtf8().constData();
    }
}
