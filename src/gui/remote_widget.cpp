#include "remote_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"

#include <signal.h>

#define PETIT_RAYON2 0.025

RemoteWidget::RemoteWidget()
:m_qt_network(MyQTNetwork::Instance_ptr())
{
    m_black_mode = false;
    m_img_return = loadImageInv("/gui/return.png");
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");
}

void RemoteWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_select_widget.setSize(width, height);
    
    m_y2 = m_height*0.04;
    m_x2 = m_y2;
    m_width2 = m_width-2*m_y2-m_gros_button*2.4;
    m_height2 = m_height-2*m_y2;

    int y = 0.35*m_height;
    int inter = 0.1*m_height;
    y+=1.5*inter;
    m_control_panel.setResize(0.25*m_width, y, m_gros_button);
    y+=inter;
    y+=inter;
    m_button_open_connection.setResizeStd(0.5*m_width, y, "Ouvrir la connection", true, width/4);
    m_button_open_wifi.setResizeStd(0.7*m_width, 0.35*m_height, "Paramétrer le Wifi", true, width/4);
    y+=inter;
    
    int x_right = width-m_gros_button*1.2;
    m_button_close.setResize(x_right, m_height-m_gros_button*1.2, m_gros_button);
};



void RemoteWidget::draw(){
    
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRoundedRect(m_x2, m_y2, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    Framework & f = Framework::Instance();
    
    if(f.m_session == 0){
        auto now = std::chrono::system_clock::now();
        int tick_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now-m_time_open).count();
        
        
        //Framework & f = Framework::Instance();
        drawText("Connection à distance", 0.5*m_width, 0.2*m_height, sizeText_big, true);
        
        if(tick_ms < 5000){
            drawQText("Recherche des connections     " + QString::number((tick_ms/1000)+1) + "/5", 0.25*m_width, 0.35*m_height, sizeText_big, false);
        } else {
            if(m_qt_network->m_is_connected){
                m_painter->setPen(Qt::darkGreen);
                drawText("Connecté à internet", 0.25*m_width, 0.35*m_height, sizeText_big);
            
                m_painter->setPen(m_penBlack);
                drawButtonCheck(m_control_panel, !f.m_config.m_control_view_only, "autoriser le controle du panel");

                drawButtonLabel2(m_button_open_connection);
            } else {
                m_painter->setPen(Qt::red);
                drawText("Non connecté à internet", 0.2*m_width, 0.35*m_height, sizeText_big);
                
                drawButtonLabel2(m_button_open_wifi);
            }
            
        }
    } else {
        drawText("Connection à distance", 0.5*m_width, 0.2*m_height, sizeText_big, true);
        
        if(!f.m_remote_error.empty()){
            m_painter->setBrush(m_brushRedButton);
            m_painter->drawRoundedRect(0.3*m_width, 0.3*m_height, 0.4*m_width, 0.15*m_height, 15, 15);
            drawText("Erreur : ", 0.5*m_width, 0.35*m_height, sizeText_big, true);
            drawText(f.m_remote_error, 0.5*m_width, 0.4*m_height, sizeText_medium, true);
        }
        
        drawText("numero de session : ", 0.5*m_width, 0.55*m_height, sizeText_big, true);
        drawText(f.m_session_str, 0.5*m_width, 0.6*m_height, sizeText_big, true);

    }
    
    drawButtonImageCarre(m_button_close, m_img_return, 0.9, false);
}





int RemoteWidget::onMouse(int x, int y){
    //KeyBoardWidget & key_board_widget = MainWidget::instance()->m_key_board_widget;
    //Framework & f = Framework::Instance();
    
    Framework & f = Framework::Instance();
    
    if(f.m_session == 0){
        if(m_control_panel.isActive(x, y)){
            f.m_config.m_control_view_only = !f.m_config.m_control_view_only;
        }
        
            
        if(m_button_open_connection.isActive(x, y)){
            if(f.m_session == 0){
                srand (time (NULL));
                int my_rand = rand();
                f.m_session = my_rand % 4 + 1;
            }
            RemoteConsumer & consumer = RemoteConsumer::instance();
            consumer.start();
            
            m_page = 2;
        }
        
        if(m_button_open_wifi.isActive(x, y)){
            MainWidget::instancePtr()->m_wifi_widget.open();
            m_close = true;
        }
    }
    
    if(m_button_close.isActive(x, y)){
        m_close = true;
    }
    
    return 0;
    
    
}


void RemoteWidget::open(){
    m_time_open = std::chrono::system_clock::now();
    
    m_qt_network->test();
    
    m_close = false;
    m_page = 1;
}
