#ifndef FILE_WIDGET_H
#define FILE_WIDGET_H   

#include "base/base_widget.hpp"
#include "base/select_widget.hpp"

class FileWidget : public BaseWidget {
    ButtonGui m_button_close;
public:
    SelectWidget m_select_widget;
    SelectButtonGui m_select_files;

    bool m_button_ok = false;
    
    FileWidget();
    
    void setSize(int width, int height);
    
    void draw();
    int onMouse(int x, int y);
    void open();
   
};

#endif
