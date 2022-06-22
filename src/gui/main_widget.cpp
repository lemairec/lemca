#include "main_widget.hpp"

#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <iomanip>

#include "../util/log.hpp"
#include "environnement.hpp"
#include "../framework.hpp"


#define MY_WIDTH 800
#define MY_HEIGHT 400

QGraphicsPixmapItem * item;
QPixmap * p;

int l_bottom = 20;

MainWidget::MainWidget()
{
    
    m_logoImg = loadImage("/gui/logo.png");
    m_imgBineuse = loadImage("/gui/bineuse.png");
    m_imgGPS = loadImage("/gui/gps.png");
    m_imgExit = loadImage("/gui/off.png");
    m_imgOption = loadImage("/gui/option_gris_gros.png");
    m_imgWifi = loadImage("/gui/wifi.png");
    m_img_remote = loadImage("/gui/reseau.png");

    //m_widgets.push_back(&m_satWidget);
    m_widgets.push_back(&m_remote_widget);
    m_widgets.push_back(&m_menuWidget);
    m_widgets.push_back(&m_key_pad_widget);
    m_widgets.push_back(&m_option_widget);
    m_widgets.push_back(&m_wifi_widget);
    m_widgets.push_back(&m_cmd_widget);
}

void MainWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_widthMax = m_width/2-50;
    m_heightMax = m_height/2-50;
    
    m_option_widget.setSize(m_width, m_height);
    for(auto p : m_widgets){
        p->setSize(m_width, m_height);
    }
    m_key_pad_widget.setSize(m_width, m_height);
    m_key_board_widget.setSize(m_width, m_height);
    
    m_buttonBineuse.setResize(m_width*0.2, m_height*0.8, m_gros_gros_button);
    m_buttonGps.setResize(m_width*0.4, m_height*0.8, m_gros_gros_button);
    m_buttonRobot.setResize(m_width*0.6, m_height*0.8, m_gros_gros_button);
    m_buttonExit.setResize(m_width*0.8, m_height*0.8, m_gros_gros_button);
    m_buttonWifi.setResize(m_width*0.8, m_height*0.2, m_gros_gros_button);
    m_button_remote.setResize(m_width*0.6, m_height*0.2, m_gros_gros_button);
    m_buttonSerial.setResize(m_width*0.8, m_height*0.5, m_gros_gros_button);
    //m_buttonMenu2.setResize(120, m_height-30, m_petit_button);
    m_buttonOption.setResize(m_width*0.2, m_height*0.2, m_gros_gros_button);
    m_buttonSendMessage.setResize(m_width-100, 0.5*m_height, m_gros_button);
}

MainWidget * MainWidget::instance(){
    static MainWidget gf;
    return &gf;
}

void MainWidget::setPainter(QPainter * p){
    BaseWidget::setPainter(p);
    m_option_widget.setPainter(p);
    m_option_widget.m_file_widget.setPainter(p);
    m_option_widget.m_file_widget.m_select_widget.setPainter(p);
    m_wifi_widget.m_select_widget.setPainter(p);
    for(auto p2 : m_widgets){
        p2->setPainter(p);
    }
    m_key_board_widget.setPainter(p);
}

int max = 10000;



void MainWidget::draw(){
    //scene = s;
    DEBUG("BEGIN");
    draw_force();
    DEBUG("END");
}

bool init = false;
void MainWidget::draw_force(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushDarkGray);

    drawMain();
    drawButtons();
    
    Framework & f = Framework::Instance();
    
    if(f.m_config.m_code_source){
        drawText("code source", 0.1*m_width, 0.4*m_height);
    }
    
    if(!f.m_session_str.empty()){
        drawText("session : "+f.m_session_str, 0.1*m_width, 0.45*m_height);
    }
    
    for(auto p : m_widgets){
        if(!p->m_close){
            p->draw();
        }
    }
    
    
    if(f.m_is_f_call){
        m_painter->drawRect(0.2*m_width, 0.2*m_height,0.6*m_width, 0.6*m_height);
        drawText("loading", 0.5*m_width, 0.5*m_height);
    }
    
    if(!m_key_board_widget.m_close){
        m_key_board_widget.draw();
    }
    
    if(!init){
        init = true;
        if(f.m_config.m_port_remote != 0){
            RemoteConsumer & consumer = RemoteConsumer::instance();
            consumer.start();
        }
    }
}

void MainWidget::drawMain(){
    m_painter->setBrush(m_brushWhite);
    
    drawMyImage(*m_logoImg, 0.5*m_width, 0.5*m_height, 2, true);
}

void MainWidget::drawButtons(){
    Framework & f = Framework::Instance();
    
    
    drawButtonImage(m_buttonBineuse, m_imgBineuse);

    drawText("Bineuse", m_buttonBineuse.m_x, m_buttonBineuse.m_y+40, sizeText_medium,  true);
    if(f.m_config.m_gps){
        drawButtonImage(m_buttonGps, m_imgGPS);
        drawText("GPS", m_buttonGps.m_x, m_buttonGps.m_y+40, sizeText_medium,  true);
    }
    if(f.m_config.m_robot){
        drawButtonImage(m_buttonRobot, m_imgGPS);
        drawText("Robot", m_buttonRobot.m_x, m_buttonRobot.m_y+40, sizeText_medium,  true);
    }
    if(f.m_config.m_serial){
        drawButtonImage(m_buttonSerial, m_imgGPS);
        drawText("Serial", m_buttonSerial.m_x, m_buttonSerial.m_y+40, sizeText_medium,  true);
    }
    
    if(f.m_config.m_wifi){
        drawButtonImage(m_buttonWifi, m_imgWifi);
        drawButtonImage(m_button_remote, m_img_remote);
    }
    drawButtonImage(m_buttonExit, m_imgExit);
    drawButtonImage(m_buttonOption, m_imgOption);
    /*drawButtonImage(m_buttonMenu, m_imgMenu);
    drawButton(m_buttonMenu2);
    drawButton(m_buttonMenu3);
    drawButton(m_buttonSendMessage);
    drawText("envoyer message", m_buttonSendMessage.m_x, m_buttonSendMessage.m_y, sizeText_little, true);*/
}


int MainWidget::onMouse(int x, int y){
    Framework & f = Framework::Instance();
    
    size_t n = m_widgets.size();
    for(size_t i = 0; i < n; ++i){
        auto p = m_widgets[n-i-1];
        if(!p->m_close){
            p->onMouse(x, y);
            return 0;
        }
    }
    
    
    if(m_buttonBineuse.isActive(x, y)){
        if(f.m_config.m_code_source){
            call(f.m_config.m_bineuse_src_run);
        } else {
            call(f.m_config.m_bineuse_run);
        }
    } else if(m_buttonGps.isActive(x, y)){
        if(Framework::Instance().m_config.m_gps){
            call(f.m_config.m_gps_run);
        }
    } else if(m_buttonRobot.isActive(x, y)){
        if(Framework::Instance().m_config.m_robot == 1){
            call(f.m_config.m_robot_inrows_run);
        }
    } else if(m_buttonSerial.isActive(x, y)){
        if(Framework::Instance().m_config.m_serial){
            call(f.m_config.m_serie_run);
        }
    } else if(m_buttonOption.isActive(x, y)){
        m_option_widget.open();
    } 
    
    //Framework & f = Framework::Instance();
    if(f.m_config.m_wifi){
        if(m_buttonWifi.isActive(x, y)){
            m_wifi_widget.open();
        }
        if(m_button_remote.isActive(x, y)){
            m_remote_widget.open();
        }
    }
    if(m_buttonExit.isActive(x, y)){
        call("/sbin/shutdown -h now");
    }
    return 0;
}

void MainWidget::call(const std::string & s){
    Framework & f = Framework::Instance();
    if(!f.m_is_f_call){
        INFO("call " << s);
        f.mutex.lock();
        f.m_is_f_call = true;
        f.m_command_to_execute = s;
        f.mutex.unlock();
        f.bufferNotEmpty.wakeAll();
        //(100);
        //m_is_f_call = false;
        
    } else {
        INFO("not call! " << s);
        
    }
}
