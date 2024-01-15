#ifndef INIT_WIDGET_H
#define INIT_WIDGET_H

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"
#include "qt/my_qt_network.hpp"

class InitWidget : public BaseWidget {
    QPixmap * m_img_return;
    
    int m_width2, m_height2, m_x2, m_y2;
public:
    InitWidget();
    
    void loadImages();
    void setSize(int width, int height);
    
    virtual void draw();
    virtual int onMouse(int x, int y);
    
    ValueGuiKeyBoard m_code_constructeur;
    ButtonGui m_button_ignore;
    ButtonGui m_button_ok;
};

#endif
