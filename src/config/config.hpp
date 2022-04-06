#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <QString>
#include <QSettings>

class Config  {
public:
    bool m_fullscreen = true;
    bool m_technicien = false;
    bool m_code_source = false;
    bool m_wifi = true;
    bool m_usb = false;
    bool m_gps = false;
    int m_robot = 0; //1INROWS //2GPS
    bool m_serial = false;
    
    
    std::string m_bineuse_src_run;
    std::string m_bineuse_run;
    std::string m_gps_run;
    std::string m_make_archive;
    std::string m_robot_inrows_run;
    std::string m_serie_run;
    
    Config();
    
    void work(QSettings & settings, bool save);
    void validate();
    
    void save();
    void load();
    
    void saveLoadBool(QSettings & settings, const QString & name, bool & ref, bool save);
    void saveLoadDouble(QSettings & settings, const QString & name, double & ref, bool save);
    void saveLoadInt(QSettings & settings, const QString & name, int & ref, bool save);
    void saveLoadString(QSettings & settings, const QString & name, std::string & ref, bool save);
    template<typename T> void saveLoadEnum(QSettings & settings, const QString & name, T & ref, bool save);
};

//-500 =>

#endif // CONFIG_H
