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
    m_imgClose = loadImage("/gui/ok.png");
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");
}

void RemoteWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_select_widget.setSize(width, height);
    
    
    //m_select_serial
    int x = 0.55*m_width;
    int y = 0.35*m_height;
    int inter = 0.1*m_height;
    y+=1.5*inter;
    m_control_panel.setResize(0.25*m_width, y, m_gros_button);
    y+=inter;
    y+=inter;
    m_button_open_connection.setResizeStd(0.5*m_width, y, "Ouvrir la connection", true, width/4);
    y+=inter;
    m_button_close.setResize(0.75*m_width, 0.83*m_height, m_gros_button);
    
    m_button_interrupt.setResizeStd(0.5*m_width, y, "Fermer la connection", true, width/4);
    
};

void RemoteWidget::draw(){
    
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRoundedRect(m_width*0.025, m_height*0.05, m_width*0.95, m_height*0.9, RAYON_ROUNDED, RAYON_ROUNDED);
    
    Framework & f = Framework::Instance();
    
    if(f.m_session == 0){
        //Framework & f = Framework::Instance();
        drawText("Connection à distance", 0.5*m_width, 0.2*m_height, sizeText_big, true);
        
        if(m_qt_network->m_is_connected){
            m_painter->setPen(Qt::darkGreen);
            drawText("Connecté à internet", 0.25*m_width, 0.35*m_height, sizeText_big);
        } else {
            m_painter->setPen(Qt::red);
            drawText("Non connecté à internet", 0.25*m_width, 0.35*m_height, sizeText_big);
        }
        m_painter->setPen(m_penBlack);
        drawButtonCheck(m_control_panel, m_control_b, "autoriser le controle du panel");

        drawButtonLabel2(m_button_open_connection);
    } else {
        drawText("Connecté", 0.5*m_width, 0.2*m_height, sizeText_big, true);
        
        drawText("numero de session : ", 0.5*m_width, 0.4*m_height, sizeText_big, true);
        drawText(f.m_session_str, 0.5*m_width, 0.5*m_height, sizeText_big, true);
        
        drawButtonLabel2(m_button_interrupt, COLOR_OTHER);

    }
    drawButtonImage(m_button_close, m_imgClose);
}





int RemoteWidget::onMouse(int x, int y){
    KeyBoardWidget & key_board_widget = MainWidget::instance()->m_key_board_widget;
    //Framework & f = Framework::Instance();
    
    Framework & f = Framework::Instance();
    if(f.m_session == 0){
        if(m_control_panel.isActive(x, y)){
            m_control_b = !m_control_b;
        }
        
            
        if(m_button_open_connection.isActive(x, y)){
            if(f.m_session == 0){
                f.m_session = rand() % 4 + 1;
                INFO(f.m_session);
                f.m_session_str = "lemca_"+std::to_string(f.m_session);
            }
            RemoteConsumer & consumer = RemoteConsumer::instance();
            consumer.start();
            
            m_page = 2;
        }
    } else {
        if(m_button_interrupt.isActive(x, y)){
            std::string s = "kill " + std::to_string(f.m_cmd_pid);
            INFO("kill");
            INFO(s);
            Framework & f = Framework::Instance();
            f.m_cmd_buffer.push_back("****");
            f.m_cmd_buffer.push_back(s);
            f.m_cmd_buffer.push_back("****");
            kill(f.m_cmd_pid, SIGTERM);
            //kill(f.m_cmd_process);
        }
    }
    
    if(m_button_close.isActive(x, y)){
        m_close = true;
    }
    
    return 0;
    
    
}

void RemoteWidget::call2(const std::string & s){
    Framework & f = Framework::Instance();
    
    f.mutex.lock();
    f.m_command_to_execute2 = s;
    f.bufferNotEmpty.wakeAll();
    f.mutex.unlock();
    
    m_page = 2;
}


void RemoteWidget::open(){
    m_qt_network->test();
    m_close = false;
    m_page = 1;
}
void RemoteWidget::call(const std::string & s){
    INFO("call " << s);
    system(s.c_str());
}
