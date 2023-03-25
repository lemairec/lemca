#ifndef REMOTE_WIDGET_H
#define REMOTE_WIDGET_H

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"
#include "qt/my_qt_network.hpp"

class RemoteWidget : public BaseWidget {
    QPixmap * m_imgClose;
    
    ButtonGui m_button_close;
    std::string m_reseau;
    
public:
    RemoteWidget();
    
    SelectWidget m_select_widget;
    
    MyQTNetwork * m_qt_network;
    
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    virtual void open();
    
    ButtonGui m_button_open_connection;
    ButtonGui m_button_interrupt;
    
    ButtonGui m_control_panel;
    
    int m_page = 1;
    void resizePage1();
    void onMousePage1(int x, int y);
    void drawPage1();
};

#endif
