#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define PILOT_LANGAGE_ARDUINO 0
#define PILOT_LANGAGE_HADRIEN 1

enum LissageGpsMode{
    LissageGpsMode_None = 0,
    LissageGpsMode_Ekf = 1
};

enum CapMode{
    CapMode_Custom = 0,
    CapMode_Ekf = 1,
    CapMode_Rmc = 2
};

enum LissageImuMode{
    LissageImuMode_None = 0,
    LissageImuMode_Ekf = 1
};

class Config  {
public:
    bool m_fullscreen = true;
    bool m_technicien = false;
    bool m_code_source = false;
    bool m_gps = false;
    int m_robot = 0; //1GPS //2INROWS
    bool m_serial = false;
    
    
    std::string m_bineuse_src_run;
    std::string m_bineuse_src_update;
    std::string m_bineuse_run;
    std::string m_bineuse_update;
    std::string m_bineuse_update_wifi;
    std::string m_gps_run;
    std::string m_gps_update;
    std::string m_make_archive;
    std::string m_robot_gps_run;
    std::string m_robot_gps_update;
    std::string m_robot_inrows_run;
    std::string m_robot_inrows_update;
    std::string m_serie_run;
    std::string m_serie_update;
    std::string m_update_lemca;
    
    Config();
    
    void save();
    void load();
};

//-500 =>

#endif // CONFIG_H
