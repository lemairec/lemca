#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <QString>
#include <QSettings>

enum AutoLaunch {
    AutoLaunch_None = 0,
    AutoLaunch_Robot = 1
};

class Config  {
public:
    std::string m_langage = "EN";
    
    bool m_fullscreen = true;
    int m_user_mode = 0;
    bool m_code_source = false;
    bool m_update_wifi = true;
    bool m_update_usb = true;
    bool m_remote = false;
    bool m_wifi2 = false;
    bool m_gps = false;
    int m_robot = 0; //1INROWS //2GPS
    bool m_serial = false;
    
    int m_constructor = 0; //0 Lemca
    
    std::string m_bineuse_run;
    std::string m_gps_run;
    std::string m_robot_inrows_run;
    std::string m_serie_run;
    
    std::string m_version_selected = "prod";
    
    
    int m_port_remote = 0;
    AutoLaunch m_auto_launch = AutoLaunch_None;
    
    Config();
    
    bool isDeveloppeur(){
        return m_user_mode > 1;
    }
    
    bool isTechnicien(){
        return m_user_mode > 0;
    }
    
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
