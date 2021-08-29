#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include "base_widget.hpp"
#include "option_widget.hpp"
#include "menu_widget.hpp"
#include "keyboard_widget.hpp"
#include "harxon_widget.hpp"
#include <QThread.h>
#include <QWaitCondition.h>

class MainWidget : public BaseWidget {
    MainWidget();
public:
    static MainWidget * instance();
    
    MenuWidget m_menuWidget;
    OptionWidget m_option_widget;
    MotorWidget m_motor_widget;
    
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
    
    
    ButtonGui m_buttonBineuse;
    ButtonGui m_buttonGps;
    ButtonGui m_buttonExit;
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
    
    
    void onMouse(int x, int y);
};


#endif // GPS_WIDGET_H
