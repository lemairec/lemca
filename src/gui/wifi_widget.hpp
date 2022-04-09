#ifndef WIFI_WIDGET_H
#define WIFI_WIDGET_H

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"

class WifiWidget : public BaseWidget {
    QPixmap * m_imgClose;
    
    ButtonGui m_button_close;
    
    
public:
    WifiWidget();
    
    SelectWidget m_select_widget;
    
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    
    SelectButtonGui m_select_wifi;
    ValueGuiKeyBoard m_password;
    ButtonGui m_connect;
    
    void resizePage1();
    void onMousePage1(int x, int y);
    void drawPage1();
    
    void open();
    void call(const std::string & s);
    void call2(const std::string & s);
    
    void addWifis();
    
};

#endif
