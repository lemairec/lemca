#ifndef WIFI_WIDGET_H
#define WIFI_WIDGET_H

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"
#include "qt/my_qt_network.hpp"

class WifiWidget : public BaseWidget {
    QPixmap * m_img_return;
    
    ButtonGui m_button_close;
    
    int m_width2, m_height2, m_x2, m_y2;
public:
    WifiWidget();
    
    SelectWidget m_select_widget;
    
    MyQTNetwork * m_qt_network;
    
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    
    SelectButtonGui m_select_wifi;
    ValueGuiKeyBoard m_password;
    ButtonGui m_connect;
    
    void resizePage1();
    void onMousePage1(int x, int y);
    void drawPage1();
    
    std::chrono::time_point<std::chrono::system_clock> m_time_open;
    void open();
    
    void call(const std::string & s);
    void call2(const std::string & s);
    
    void addWifis();
    
};

#endif
