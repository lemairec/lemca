#include "main_widget.hpp"

#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <iomanip>

#include "../logging.hpp"
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

    //m_widgets.push_back(&m_satWidget);
    m_widgets.push_back(&m_menuWidget);
    m_widgets.push_back(&m_key_pad_widget);
    m_widgets.push_back(&m_option_widget);
    m_widgets.push_back(&m_motor_widget);
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
    m_buttonExit.setResize(m_width*0.8, m_height*0.8, m_gros_gros_button);
    //m_buttonMenu2.setResize(120, m_height-30, m_petit_button);
    m_buttonOption.setResize(m_width*0.2, m_height*0.2, m_petit_button);
    m_buttonSendMessage.setResize(m_width-100, 0.5*m_height, m_gros_button);
    
    int y = m_height-180;
    int y2 = y+20;
    int inter = 16;
    int i = 0;
    
    m_categories.clear();
    for(auto c : Framework::Instance().m_categories){
        ButtonGui * b = new ButtonGui();
        b->setResize(20, y2, 8);
        b->m_labelInt = i;
        
        ++i;
        y2+= inter;
        m_categories.push_back(b);
        
    }
}

MainWidget * MainWidget::instance(){
    static MainWidget gf;
    return &gf;
}

void MainWidget::setPainter(QPainter * p){
    BaseWidget::setPainter(p);
    m_option_widget.setPainter(p);
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


void MainWidget::draw_force(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushDarkGray);

    drawMain();
    drawButtons();
    
    if(m_is_f_call){
        drawText("called", 0.5*m_width, 0.7*m_height);
    }
    if(m_code_source){
        drawText("code source", 0.1*m_width, 0.4*m_height);
    }
    
    for(auto p : m_widgets){
        if(!p->m_close){
            p->draw();
        }
    }
    
    if(!m_key_board_widget.m_close){
        m_key_board_widget.draw();
    }
}

void MainWidget::drawMain(){
    m_painter->setBrush(m_brushWhite);
    
    drawMyImage(*m_logoImg, 0.5*m_width, 0.5*m_height, 2, true);
}

void MainWidget::drawButtons(){
    drawButtonImage(m_buttonBineuse, m_imgBineuse);
    drawText("Bineuse", m_buttonBineuse.m_x, m_buttonBineuse.m_y+40, sizeText_medium,  true);
    if(Framework::Instance().m_config.m_gps){
        drawButtonImage(m_buttonGps, m_imgGPS);
        drawText("GPS", m_buttonGps.m_x, m_buttonGps.m_y+40, sizeText_medium,  true);
    }
    drawButtonImage(m_buttonExit, m_imgExit);
    drawButtonImage(m_buttonOption, m_imgOption);
    /*drawButtonImage(m_buttonMenu, m_imgMenu);
    drawButton(m_buttonMenu2);
    drawButton(m_buttonMenu3);
    drawButton(m_buttonSendMessage);
    drawText("envoyer message", m_buttonSendMessage.m_x, m_buttonSendMessage.m_y, sizeText_little, true);*/
}


void MainWidget::onMouse(int x, int y){
    Framework & f = Framework::Instance();
    
    size_t n = m_widgets.size();
    for(size_t i = 0; i < n; ++i){
        auto p = m_widgets[n-i-1];
        if(!p->m_close){
            p->onMouse(x, y);
            return;
        }
    }
    
    for(auto b : m_categories){
        if(b->isActive(x, y)){
            auto c = f.m_categories[b->m_labelInt];
            c->m_enable = !c->m_enable;
        };
    }
    
    if(m_buttonBineuse.isActive(x, y)){
        if(m_code_source){
            call("/home/lemca/bineuse_src/build/bineuse");
        } else {
            call("~/bineuse/bineuse");
        }
    } else if(m_buttonGps.isActive(x, y)){
        if(Framework::Instance().m_config.m_gps){
            call("cd /home/lemca/agrigpspi/build && ./agri_gps_pi");
        }
    } else if(m_buttonOption.isActive(x, y)){
        m_option_widget.m_close = false;
    } else if(m_buttonExit.isActive(x, y)){
        call("/sbin/shutdown -h now");
    } else if(!m_key_board_widget.m_close){
        m_key_board_widget.onMouse(x, y);
        if(m_key_board_widget.m_close){
            QString s2 = m_key_board_widget.m_res;
            s2 += "\r\n";
            std::string s = s2.toUtf8().constData();
            f.sendMessages(s);
        }
    }
}

void MainWidget::call(const std::string & s){
    if(!m_is_f_call){
        INFO("call " << s);
        m_is_f_call = true;
        system(s.c_str());
        m_is_f_call = false;
        
        //(100);
        //m_is_f_call = false;
        
    } else {
        INFO("not call! " << s);
        
    }
}
