#ifndef WIFI_WIDGET_H
#define WIFI_WIDGET_H

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"
#include "qt/my_qt_network.hpp"

class WifiWidget : public BaseWidget {
    QPixmap * m_imgClose;
    
    ButtonGui m_button_close;
    
    
public:
    WifiWidget();
    
    SelectWidget m_select_widget;
    
    MyQTNetwork * m_qt_network;
    
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    
    ButtonGui m_refresh;
    SelectButtonGui m_select_wifi;
    ValueGuiKeyBoard m_password;
    ButtonGui m_connect;
    
    void resizePage1();
    void onMousePage1(int x, int y);
    void drawPage1();
    
    void open();
    void call(const std::string & s);
    void call2(const std::string & s);
    
    int m_search_wifi = 0;
    void addWifis();
    
};

#endif
