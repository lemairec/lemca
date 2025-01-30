#ifndef REMOTE_WIDGET_H
#define REMOTE_WIDGET_H

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"
#include "qt/my_qt_network.hpp"

class RemoteWidget : public BaseWidget {
    QPixmap * m_img_return;
    
    ButtonGui m_button_close;
    std::string m_reseau;
    
    int m_width2, m_height2, m_x2, m_y2;
public:
    RemoteWidget();
    
    std::chrono::time_point<std::chrono::system_clock> m_time_open;
    int m_last_s = 10;
    SelectWidget m_select_widget;
    
    MyQTNetwork * m_qt_network;
    
    void loadImages();
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    virtual void open();
    
    ButtonGui m_button_open_connection;
    ButtonGui m_button_close_connection;
    ButtonGui m_button_open_wifi;
    ButtonGui m_button_detail;
    
    bool m_detail = false;
    
    ButtonGui m_control_panel;
    
    int m_page = 1;
    void resizePage1();
    void onMousePage1(int x, int y);
    void drawPage1();
};

#endif
