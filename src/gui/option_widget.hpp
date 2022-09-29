#ifndef OPTION_WIDGET_H
#define OPTION_WIDGET_H

#include "base/base_widget.hpp"
#include "file_widget.hpp"
#include "qt/my_qt_network.hpp"

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
    QPixmap * m_img_return;
    
    ButtonGui m_button_return;
    
    ButtonGui m_button_p1;
    ButtonGui m_button_p2;
    ButtonGui m_button_p3;
    ButtonGui m_button_p4;
    ButtonGui m_button_p5;
    ButtonGui m_button_p6;
    
    int m_page = 1;
    
    
    
    void drawPart2(double y, double h, std::string title);
    void drawPart1(double y, double h, std::string title);

public:
    SelectWidget m_select_widget;
    
    FileWidget m_file_widget;
    
    OptionWidget();
    
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    
    ButtonGui m_update_bineuse_usb;
    ButtonGui m_update_bineuse;
    ButtonGui m_update_gps;
    ButtonGui m_update_robot;
    ButtonGui m_serial;
    
    SelectButtonGui m_langage;
    SelectButtonGui m_unity;
    
    
    void setSizePage1();
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
    void setSizePage2();
    void onMousePage2(int x, int y);
    void drawPage2();
    
    //page3
    ButtonGui m_button_gps;
    ButtonGui m_button_robot;
    ButtonGui m_button_serial;
    ButtonGui m_button_wifi;
    ButtonGui m_button_usb;
    
    ButtonGui m_update_lemca;
    ButtonGui m_update_deps;
    
    
    void setSizePage3();
    void onMousePage3(int x, int y);
    void drawPage3();
    
    //page4
    ButtonGui m_button_full_screen;
    ButtonGui m_clear_data;
    
    ButtonGui m_make_archive;
    ButtonGui m_button_code_source;
    ButtonGui m_quit_full_screen;
    ButtonGui m_run_cmd;
    
    void setSizePage4();
    void onMousePage4(int x, int y);
    void drawPage4();
    
    MyQTNetwork * m_qt_network;
    ButtonGui m_refresh;
    
    
    ButtonGui m_camera30;
    ButtonGui m_camera31;
    ButtonGui m_reseau;
    
    void setSizePage5();
    void onMousePage5(int x, int y);
    void drawPage5();
    
    ValueGui m_port;
    ButtonGui m_auto_launch;
    void setSizePage6();
    void onMousePage6(int x, int y);
    void drawPage6();
    
    void open();
    void call(const std::string & s);
    void call2(const std::string & s);
    
    /*
     BASE
     */
    
    int m_width2, m_height2, m_x2, m_y2;
    int m_width3, m_y_title, m_y_begin, m_y_inter;
    int m_part_1_x, m_part_1_w, m_part_1_m, m_part_1_x2, m_part_1_x3, m_part_2_m, m_part_2_x, m_part_2_w, m_part_2_x2, m_part_2_x3;
    
    void drawButtonOption(ButtonGui & button, QPixmap * image, bool check, double scale);
    void drawPart1Title(double y, double h, const std::string & title, bool separateur = false);
    void drawPart2Title(double y, double h, const std::string & title, bool separateur = false);
    void drawPart2(double y, double h, bool separateur = false);
    void drawSeparateurH();
    void drawSeparateurV1(double y);
    void drawSeparateurV2(double y);
};

#endif
