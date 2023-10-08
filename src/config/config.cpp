#include "config.hpp"
#include <QString>
#include <QSettings>
#include "environnement.hpp"
#include "../util/log.hpp"
#include "../util/directory_manager.hpp"

Config::Config(){
    m_bineuse_run = "~/bineuse/bineuse";
    m_gps_run = "~/lemca_gps/lemca_gps";
    m_serie_run = "~/serie/build/serie";
    m_robot_inrows_run = "~/inrows/build/inrows";
}


void Config::work(QSettings & settings, bool save){
    saveLoadBool(settings, "code_source", m_code_source, save);
    saveLoadInt(settings, "constructor", m_constructor, save);
    saveLoadString(settings, "panel", m_panel, save);
   
    
    saveLoadBool(settings, "wifi", m_wifi2, save);
    saveLoadBool(settings, "update_usb2", m_update_usb, save);
    saveLoadBool(settings, "update_wifi", m_update_wifi, save);
    saveLoadBool(settings, "remote", m_remote, save);
    saveLoadBool(settings, "gps", m_gps, save);
    saveLoadBool(settings, "fullscreen", m_fullscreen, save);
    saveLoadInt(settings, "robot", m_robot, save);
    saveLoadBool(settings, "serial", m_serial, save);
    
    
    saveLoadString(settings, "langage", m_langage, save);
    saveLoadString(settings, "version_selected", m_version_selected, save);

    saveLoadInt(settings, "port_remote", m_port_remote, save);
    saveLoadEnum(settings, "auto_launch", m_auto_launch, save);
    
}

void Config::validate(){
    m_wifi2 = (m_remote || m_update_wifi);
}

/**
 COMMON
 */

void Config::save(){
    std::string s = DirectoryManager::Instance().m_config_file;
    QString path = QString::fromStdString(s);
    QSettings settings(path, QSettings::IniFormat);

    work(settings, true);
}

void Config::load(){
    std::string s = DirectoryManager::Instance().m_config_file;
    QString qpath = QString::fromStdString(s);
    QSettings settings(qpath, QSettings::IniFormat);
    
    work(settings, false);
}


void Config::saveLoadDouble(QSettings & settings, const QString & name, double & ref, bool save){
    if(save){
        settings.setValue(name, ref);
    } else {
        if(settings.contains(name)){
            ref = settings.value(name).toDouble();
        }
    }
}

void Config::saveLoadInt(QSettings & settings, const QString & name, int & ref, bool save){
    if(save){
        settings.setValue(name, ref);
    } else {
        if(settings.contains(name)){
            ref = settings.value(name).toInt();
        }
    }
}

void Config::saveLoadBool(QSettings & settings, const QString & name, bool & ref, bool save){
    if(save){
        settings.setValue(name, ref);
    } else {
        if(settings.contains(name)){
            ref = settings.value(name).toBool();
        }
    }
}

void Config::saveLoadString(QSettings &settings, const QString &name, std::string &ref, bool save){
    if(save){
        QString ref2 = QString::fromStdString(ref);
        settings.setValue(name, ref2);
    } else {
        if(settings.contains(name)){
            ref = settings.value(name).toString().toUtf8().constData();
        }
    }
}

template<typename T> void Config::saveLoadEnum(QSettings &settings, const QString &name, T &ref, bool save){
    if(save){
        settings.setValue(name, ref);
    } else {
        if(settings.contains(name)){
            ref = (T)settings.value(name).toInt();
        }
    }
}

