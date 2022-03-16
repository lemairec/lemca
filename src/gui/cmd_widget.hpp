#ifndef CMD_WIDGET_H
#define CMD_WIDGET_H

#include "base/base_widget.hpp"

class CmdWidget : public BaseWidget {
    QPixmap * m_imgClose;
    ButtonGui m_button_close;
    
public:
    bool m_button_ok = false;
    
    CmdWidget();
    
    void setSize(int width, int height);
    
    void draw();
    int onMouse(int x, int y);
    void open();
   
};

#endif
