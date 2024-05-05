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
}

void RemoteWidget::loadImages(){
    BaseWidget::loadImages();
    
    m_img_return = loadImageInv("/gui/return.png", true);
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
    y+=inter;
    m_button_open_wifi.setResizeStd(0.7*m_width, 0.35*m_height, "Paramétrer le Wifi", true, width/4);
    y+=inter;
    m_button_detail.setResizeStd(0.5*m_width, y, "Detail", true, width/4);
    
    int x_right = width-m_gros_button*1.2;
    m_button_close.setResize(x_right, m_height-m_gros_button*1.2, m_gros_button);
};



void RemoteWidget::draw(){
    
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_x2, m_y2, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    Framework & f = Framework::Instance();
    
    drawButtonLabel2(m_button_detail);
    
    if(m_detail){
        m_painter->setPen(m_pen_black);
        m_painter->setBrush(m_brush_white);
        m_painter->drawRoundedRect(m_width*0.05, m_height*0.1, m_width*0.8, m_height*0.7, 15, 15);
        
        int inter = 18;
        int x = m_width*0.08;
        int y = m_height*0.8-inter;
        for(size_t i = 0; i < f.m_cmd_remote_buffer.size(); ++i){
            std::string s = f.m_cmd_remote_buffer[f.m_cmd_remote_buffer.size()-i-1];
            drawText(s, x, y);
            y-= inter;
            if(y<m_height*0.1){
                break;
            }
        }
        return;
    }
    
    if(m_qt_network->m_is_connected){
        m_painter->setPen(Qt::darkGreen);
        drawText("Connecté à internet", 0.25*m_width, 0.35*m_height, sizeText_big);
    } else {
        m_painter->setPen(Qt::red);
        drawText("Non connecté à internet", 0.25*m_width, 0.35*m_height, sizeText_big);
        
        drawButtonLabel2(m_button_open_wifi);
    }
    
    m_painter->setPen(m_pen_black);
    
    
    if(f.m_session == 0){
        //Framework & f = Framework::Instance();
        drawText("Connexion à distance", 0.5*m_width, 0.2*m_height, sizeText_big, true);
        
        
            
        m_painter->setPen(m_pen_black);
        drawButtonCheck(m_control_panel, !f.m_config.m_control_view_only, "autoriser le controle du panel");

        drawButtonLabel2(m_button_open_connection);
        
    } else {
        drawText("Connexion à distance", 0.5*m_width, 0.2*m_height, sizeText_big, true);
        
        if(f.m_remote_connection_ok == 1){
            m_painter->setPen(Qt::darkGreen);
            drawText("Connecté au serveur", 0.25*m_width, 0.4*m_height, sizeText_big);
        } else if(f.m_remote_connection_ok == -1){
            m_painter->setPen(Qt::red);
            drawText("Non connecté au serveur", 0.25*m_width, 0.4*m_height, sizeText_big);
        } else {
            m_painter->setPen(m_pen_black);
            drawText("connection au serveur...", 0.25*m_width, 0.4*m_height, sizeText_big);
        }
        m_painter->setPen(m_pen_black);
        
        if(f.m_config.m_control_view_only){
            drawText("controle du panel desactivé", 0.25*m_width, 0.45*m_height, sizeText_big);
        } else {
            drawText("controle du panel activé", 0.25*m_width, 0.45*m_height, sizeText_big);
        }
        
        if(f.m_remote_nbr_error != 0){
            m_painter->setBrush(m_brush_button_fail);
            std::string s = strprintf("Erreurs : %i", f.m_remote_nbr_error);
            drawText(s, 0.25*m_width, 0.5*m_height, sizeText_big);
        }
        if(!f.m_remote_error.empty()){
            drawText(f.m_remote_error, 0.5*m_width, 0.55*m_height, sizeText_medium, true);
        }
        
        drawText("numero de session : ", 0.5*m_width, 0.7*m_height, sizeText_big, true);
        drawText(f.m_session_str, 0.5*m_width, 0.6*m_height, sizeText_big, true);

    }
    
    drawButtonImageCarre(m_button_close, m_img_return, 0.4, false);
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
    
    if(m_button_detail.isActive(x, y)){
        m_detail = !m_detail;
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
    m_last_s = 10;
}
