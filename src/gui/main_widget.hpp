#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include "base/base_widget.hpp"
#include "option_widget.hpp"
#include "remote_widget.hpp"
#include "base/keyboard_widget.hpp"
#include "wifi_widget.hpp"
#include "cmd_widget.hpp"
#include "init_widget.hpp"

class MainWidget : public BaseWidget {
    MainWidget();
public:
    static MainWidget * instancePtr();
    
    OptionWidget m_option_widget;
    WifiWidget m_wifi_widget;
    RemoteWidget m_remote_widget;
    CmdWidget m_cmd_widget;
    InitWidget m_init_widget;
    
    std::vector<BaseWidget *> m_widgets;
    
    KeyPadWidget m_key_pad_widget;
    KeyBoardWidget m_key_board_widget;
    
    std::vector<ButtonGui *> m_categories;
    
    int m_widthMax;
    int m_heightMax;
    
    QPixmap * m_logo_lemca;
    QPixmap * m_logo_marechalle;
    QPixmap * m_logo_vanhoucke;
    QPixmap * m_logo_binnove;
    QPixmap * m_logo_agronomic;
    QPixmap * m_logo_agrivaux;
    
    
    QPixmap * m_imgBineuse;
    QPixmap * m_imgGPS;
    QPixmap * m_imgExit;
    QPixmap * m_imgOption;
    QPixmap * m_imgWifi;
    QPixmap * m_img_remote;
    
    
    ButtonGui m_buttonBineuse;
    ButtonGui m_buttonGps;
    ButtonGui m_buttonExcavator;
    ButtonGui m_buttonRobot;
    ButtonGui m_buttonExit;
    ButtonGui m_buttonWifi;
    ButtonGui m_button_remote;
    ButtonGui m_buttonSerial;
    ButtonGui m_buttonOption;
    ButtonGui m_buttonSendMessage;
    
    bool m_debug = false;
    bool m_is_bineuse_call = false;
    
    void loadImages();
    void setPainter(QPainter * p);
    void setSize(int width, int height);
    
    void draw();
    void draw_force();
    
    void drawButton(ButtonGui & button, QPixmap * pixmap, const std::string & s, double scale = 1.0);
    void drawButtonOff(ButtonGui & button, QPixmap * pixmap, const std::string & s, double scale = 1.0);
    void drawButtons();
    void drawMain();
    
    void call(const std::string & s);
    
    int onMouse(int x, int y);
};


#endif // GPS_WIDGET_H
