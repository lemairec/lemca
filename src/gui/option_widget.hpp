#ifndef OPTION_WIDGET_H
#define OPTION_WIDGET_H

#include "base_widget.hpp"

class OptionWidget : public BaseWidget {
    QPixmap * m_imgClose;
    QPixmap * m_imgPlus;
    QPixmap * m_imgMinus;
    
    QPixmap * m_imgSatBlanc;
    QPixmap * m_imgSatGris;
    QPixmap * m_imgVolantBlanc;
    QPixmap * m_imgVolantGris;
    QPixmap * m_imgOutilBlanc;
    QPixmap * m_imgOutilGris;
    QPixmap * m_imgOptionBlanc;
    QPixmap * m_imgOptionGris;
    QPixmap * m_imgImuBlanc;
    QPixmap * m_imgImuGris;
    
    ButtonGui m_button_close;
    
    ButtonGui m_button_p1;
    ButtonGui m_button_p2;
    ButtonGui m_button_p3;
    ButtonGui m_button_p4;
    ButtonGui m_button_p5;
    ButtonGui m_button_p6;
    
    int m_page = 1;
    
    void addSerials();
    
    void drawPart2(double y, double h, std::string title);
    void drawPart1(double y, double h, std::string title);

public:
    OptionWidget();
    
    void setSize(int width, int height);
    
    virtual void draw();
    virtual void onMouse(int x, int y);
    
    ButtonGui m_update_bineuse;
    ButtonGui m_update_gps;
    
    void resizePage1();
    void onMousePage1(int x, int y);
    void drawPage1();
    
    //page2
    ButtonGui m_button_technicien;
    ButtonGui m_button1;
    ButtonGui m_button2;
    ButtonGui m_button3;
    ButtonGui m_button4;
    ButtonGui m_button5;
    ButtonGui m_button6;
    ButtonGui m_button7;
    ButtonGui m_button8;
    ButtonGui m_button9;
     
    void myDrawButton(ButtonGui * b, QString s);
    void resizePage2();
    void onMousePage2(int x, int y);
    void drawPage2();
    
    //page3
    ButtonGui m_button_code_source;
    ButtonGui m_button_full_screen;
    ButtonGui m_button_gps;
    
    
    void resizePage3();
    void onMousePage3(int x, int y);
    void drawPage3();
    
    //page4
    ButtonGui m_button_sens;
    ButtonGui m_button_debug;
    ButtonGui m_button_auto;
    ButtonGui m_button_debug_file;
    ButtonGui m_button_menu_vertical;
    
    void resizePage4();
    void onMousePage4(int x, int y);
    void drawPage4();
    
    //page5
    ButtonGui m_button_encoder_inverse;
    ButtonGui m_button_motor_inverse;
     
    ValueGui m_motor_vitesse_agressivite;
    ValueGui m_motor_vitesse_max;
    
    ValueGui m_volant_pas_by_tour;
    ValueGui m_volant_angle_by_tour;
    ValueGui m_volant_derive;
    
    ValueGui m_volant_frequence;
    ValueGui m_virtual_point;
    
    ValueGui m_button_auto_deactive;
    ValueGui m_button_auto_active;
       
    
    void resizePage5();
    void onMousePage5(int x, int y);
    void drawPage5();
    
    
    
    //page_imu
    
    void resizePage6();
    void onMousePage6(int x, int y);
    void drawPage6();
    
    void open();
    void call(const std::string & s);
    
};

#endif
