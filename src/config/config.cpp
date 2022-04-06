#include "config.hpp"
#include <QString>
#include <QSettings>
#include "environnement.hpp"
#include "../util/log.hpp"
#include "../util/directory_manager.hpp"

Config::Config(){
    m_bineuse_run = "~/bineuse/bineuse";
    m_bineuse_src_run = "~/bineuse_src/build/bineuse";
    m_gps_run = "~/agrigpspi/build/agri_gps_pi";
    m_serie_run = "~/serie/build/serie";
    m_robot_inrows_run = "~/inrows/build/inrows";
    m_make_archive = "cd ~/bineuse_src; git pull; sh make_archive.sh";
}


void Config::work(QSettings & settings, bool save){
    saveLoadBool(settings, "code_source", m_code_source, save);
    saveLoadBool(settings, "wifi", m_wifi, save);
    saveLoadBool(settings, "m_gps", m_gps, save);
    saveLoadBool(settings, "m_fullscreen", m_fullscreen, save);
    saveLoadInt(settings, "m_robot", m_robot, save);
    saveLoadBool(settings, "m_serial", m_serial, save);
    
    
    
    saveLoadString(settings, "m_bineuse_src_run", m_bineuse_src_run, save);
    saveLoadString(settings, "m_bineuse_run", m_bineuse_run, save);
    saveLoadString(settings, "m_gps_run", m_gps_run, save);
    saveLoadString(settings, "m_serie_run", m_serie_run, save);
    saveLoadString(settings, "m_robot_inrows_run", m_robot_inrows_run, save);
    saveLoadString(settings, "m_make_archive", m_make_archive, save);
}

void Config::validate(){
}

/**
 COMMON
 */

void Config::save(){
    std::string s = DirectoryManager::Instance().getBinDirectory() + "/lemca.ini";
    QString path = QString::fromStdString(s);
    QSettings settings(path, QSettings::IniFormat);

    work(settings, true);
}

void Config::load(){
    std::string s = DirectoryManager::Instance().getBinDirectory() + "/lemca.ini";
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

