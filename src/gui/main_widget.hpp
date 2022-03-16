#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include "base/base_widget.hpp"
#include "option_widget.hpp"
#include "menu_widget.hpp"
#include "base/keyboard_widget.hpp"
#include "wifi_widget.hpp"

class MainWidget : public BaseWidget {
    MainWidget();
public:
    static MainWidget * instance();
    
    MenuWidget m_menuWidget;
    OptionWidget m_option_widget;
    WifiWidget m_wifi_widget;
    
    std::vector<BaseWidget *> m_widgets;
    
    KeyPadWidget m_key_pad_widget;
    KeyBoardWidget m_key_board_widget;
    
    std::vector<ButtonGui *> m_categories;
    
    int m_widthMax;
    int m_heightMax;
    
    
    QPixmap * m_logoImg;
    QPixmap * m_imgBineuse;
    QPixmap * m_imgGPS;
    QPixmap * m_imgExit;
    QPixmap * m_imgOption;
    QPixmap * m_imgWifi;
    
    
    ButtonGui m_buttonBineuse;
    ButtonGui m_buttonGps;
    ButtonGui m_buttonRobot;
    ButtonGui m_buttonExit;
    ButtonGui m_buttonWifi;
    ButtonGui m_buttonSerial;
    ButtonGui m_buttonOption;
    ButtonGui m_buttonSendMessage;
    
    bool m_debug = false;
    bool m_is_bineuse_call = false;
    
    void setPainter(QPainter * s);
    
    void draw();
    void draw_force();
    void drawButtons();
    void drawMain();
    
    void call(const std::string & s);

    
    void setSize(int width, int height);
    
    
    int onMouse(int x, int y);
};


#endif // GPS_WIDGET_H
