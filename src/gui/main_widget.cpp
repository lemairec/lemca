#include "main_widget.hpp"

#include "qt/main_window.hpp"

#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <iomanip>

#include "../util/log.hpp"
#include "environnement.hpp"
#include "../framework.hpp"
#include "../config/langage.hpp"
#include "../util/directory_manager.hpp"

#define MY_WIDTH 800
#define MY_HEIGHT 400

QGraphicsPixmapItem * item;
QPixmap * p;

int l_bottom = 20;

MainWidget::MainWidget()
{
    //m_widgets.push_back(&m_satWidget);
    m_widgets.push_back(&m_remote_widget);
    m_widgets.push_back(&m_key_pad_widget);
    m_widgets.push_back(&m_option_widget);
    m_widgets.push_back(&m_wifi_widget);
    m_widgets.push_back(&m_cmd_widget);
}

void MainWidget::loadImages(){
    BaseWidget::loadImages();
    m_imgBineuse = loadImageInv("/gui/bineuse.png");
    m_imgGPS = loadImageInv("/gui/gps.png");
    m_imgExit = loadImage("/gui/off.png", true);
    m_imgOption = loadImageInv("/gui/infos.png");
    m_imgWifi = loadImageInv("/gui/wifi.png");
    m_img_remote = loadImageInv("/gui/reseau.png");
    
    m_logo_lemca = loadImage("/gui/logo/logo.png");
    m_logo_marechalle = loadImage("/gui/logo/logo_marechalle.png");
    m_logo_vanhoucke = loadImage("/gui/logo/logo_vanhoucke.png");
    m_logo_binnove = loadImage("/gui/logo/logo_binnove.png");
    m_logo_agronomic = loadImage("/gui/logo/logo_agronomic.png");
    m_logo_agrivaux = loadImage("/gui/logo/logo_agrivaux.png");
}

void MainWidget::setPainter(QPainter * p){
    BaseWidget::setPainter(p);
    m_init_widget.setPainter(p);
    m_option_widget.setPainter(p);
    m_option_widget.m_file_widget.setPainter(p);
    m_option_widget.m_file_widget.setPainter(p);
    m_option_widget.m_file_widget.m_select_widget.setPainter(p);
    m_option_widget.m_select_widget.setPainter(p);
    m_option_widget.m_keyboard_widget.setPainter(p);
    m_wifi_widget.m_select_widget.setPainter(p);
    for(auto p2 : m_widgets){
        p2->setPainter(p);
    }
    m_key_board_widget.setPainter(p);
}

void MainWidget::setSize(int width, int height){
    Framework & f = Framework::Instance();
    BaseWidget::setSize(width, height);
    
    m_widthMax = m_width/2-50;
    m_heightMax = m_height/2-50;
    
    m_init_widget.setSize(m_width, m_height);
    m_option_widget.setSize(m_width, m_height);
    for(auto p : m_widgets){
        p->setSize(m_width, m_height);
    }
    m_key_pad_widget.setSize(m_width, m_height);
    m_key_board_widget.setSize(m_width, m_height);
    
    int button_size = 0.05*m_width;
    int inter = 0.12*m_width;
    int nb = 3;
    if(f.m_config.m_gps){
        nb++;
    }
    if(f.m_config.m_excavator){
        nb++;
    }
    if(f.m_config.m_remote){
        nb++;
    }
    int x = 0.5*m_width-inter*(nb*0.5-0.5);
    m_buttonBineuse.setResize(x, m_height*0.55, button_size);
    x+=inter;
    if(f.m_config.m_gps){
        m_buttonGps.setResize(x, m_height*0.55, button_size);
        x+=inter;
    }
    if(f.m_config.m_excavator){
        m_buttonExcavator.setResize(x, m_height*0.55, button_size);
        x+=inter;
    }
    if(f.m_config.m_remote){
        m_button_remote.setResize(x, m_height*0.55, button_size);
        x+=inter;
    }
    m_buttonWifi.setResize(x, m_height*0.55, button_size);
    x+=inter;
    m_buttonOption.setResize(x, m_height*0.55, button_size);
   
    m_buttonExit.setResize(m_width*0.5, m_height*0.8, button_size);
    m_buttonExit.m_height = 1.2*button_size;
    m_buttonExit.m_width = 3*button_size;
    
    x = 0.5*m_width-inter*2.5;
    m_buttonRobot.setResize(x, m_height*0.8, button_size);
    
    x = 0.5*m_width+inter*2.5;
    m_buttonSerial.setResize(x, m_height*0.8, button_size);
    //m_buttonMenu2.setResize(120, m_height-30, button_size);
    m_buttonSendMessage.setResize(m_width-100, 0.5*m_height, button_size);
}

MainWidget * MainWidget::instancePtr(){
    static MainWidget gf;
    return &gf;
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
    Framework & f = Framework::Instance();
    
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_background_2);
    m_painter->drawRect(0, 0, m_width, m_height);
    
    if(f.m_config.m_constructor == -1){
        m_init_widget.draw();
        return;
    }
    drawMain();
    drawButtons();
    
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
        int y2 = m_height*0.1;
        int x2 = y2;
        int width2 = m_width-2*y2;
        int height2 = m_height-2*y2;
        m_painter->setPen(m_pen_black);
        m_painter->setBrush(m_brush_white);
        m_painter->drawRoundedRect(x2, y2, width2, height2, RAYON_ROUNDED, RAYON_ROUNDED);
        
        drawText(Langage::getKey("LOADING"), 0.5*m_width, 0.5*m_height, sizeText_bigbig, true);
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
        if(f.m_config.m_auto_launch == AutoLaunch_Robot){
            if(f.m_config.m_robot == 1){
                call(f.m_config.m_robot_inrows_run);
            }
        }
    }
}

void MainWidget::drawMain(){
    Framework & f = Framework::Instance();
    
    m_painter->setBrush(m_brush_white);
    m_painter->setPen(m_pen_no);
    
    m_painter->drawRoundedRect(0.1*m_width, 0.05*m_height, 0.8*m_width,  0.35*m_height, 10, 10);
    
    m_painter->setPen(m_pen_black_inv);
    if(f.m_config.m_constructor == 1){
        drawMyImage(*m_logo_marechalle, 0.35*m_width,  0.2*m_height, 0.5, true);
        drawMyImage(*m_logo_lemca, 0.75*m_width, 0.2*m_height, 0.15, true);
    } else if(f.m_config.m_constructor == 2){
        drawMyImage(*m_logo_vanhoucke, 0.3*m_width, 0.2*m_height, 0.5, true);
        drawMyImage(*m_logo_lemca, 0.75*m_width, 0.2*m_height, 0.15, true);
    } else if(f.m_config.m_constructor == 3){
        drawMyImage(*m_logo_binnove, 0.5*m_width, 0.2*m_height, 0.3, true);
    } else if(f.m_config.m_constructor == 4){
        drawMyImage(*m_logo_agronomic, 0.35*m_width,  0.2*m_height, 0.3, true);
        drawMyImage(*m_logo_lemca, 0.75*m_width, 0.2*m_height, 0.15, true);
    } else if(f.m_config.m_constructor == 5){
        drawMyImage(*m_logo_agrivaux, 0.5*m_width,  0.2*m_height, 0.07, true);
    } else {
        drawMyImage(*m_logo_lemca, 0.5*m_width,  0.2*m_height, 0.15, true);
    }
    
}

void MainWidget::drawButton(ButtonGui & button, QPixmap * pixmap, const std::string & s, double scale){
    double scale2 = 0.4*scale;
    int w = pixmap->size().width()*scale2;
    int h = pixmap->size().height()*scale2;

    int x = button.m_x -button.m_width/2;
    int y = button.m_y- button.m_height/2;
    
    int y_image = button.m_y-h/2-15;
    m_painter->setPen(m_pen_no);
    
    m_painter->setBrush(m_brush_background_3);
    m_painter->drawRoundedRect(x, y, button.m_width, button.m_height, 15, 15);
        
    m_painter->drawPixmap(button.m_x-w/2, y_image, w, h, *pixmap);
    if(m_black_mode){
        m_painter->setPen(m_pen_white);
    } else {
        m_painter->setPen(m_pen_black);
    }
    drawQText(QString::fromStdString(s), button.m_x, button.m_y+30, sizeText_medium, true);
}

void MainWidget::drawButtonMultiLines(ButtonGui & button, QPixmap * pixmap, const std::string & s, double scale){
    double scale2 = 0.4*scale;
    int w = pixmap->size().width()*scale2;
    int h = pixmap->size().height()*scale2;

    int x = button.m_x -button.m_width/2;
    int y = button.m_y- button.m_height/2;
    
    int y_image = button.m_y-h/2-15;
    m_painter->setPen(m_pen_no);
    
    m_painter->setBrush(m_brush_background_3);
    m_painter->drawRoundedRect(x, y, button.m_width, button.m_height, 15, 15);
        
    m_painter->drawPixmap(button.m_x-w/2, y_image, w, h, *pixmap);
    if(m_black_mode){
        m_painter->setPen(m_pen_white);
    } else {
        m_painter->setPen(m_pen_black);
    }
    drawQTexts(QString::fromStdString(s), button.m_x, button.m_y+30, sizeText_medium, true);
}
    
void MainWidget::drawButtonOff(ButtonGui & button, QPixmap * pixmap, const std::string & s, double scale){
    double scale2 = 0.4*scale;
    int w = pixmap->size().width()*scale2;
    int h = pixmap->size().height()*scale2;

    int x = button.m_x-button.m_width*0.5;
    int y = button.m_y- button.m_height/2;
    
    int y_image = button.m_y-h/2;
    m_painter->setPen(m_pen_no);
    
    m_painter->setBrush(m_alert_error);
    m_painter->drawRoundedRect(x, y, button.m_width, button.m_height, 15, 15);
        
    m_painter->drawPixmap(button.m_x-button.m_width*0.35, y_image, w, h, *pixmap);
    m_painter->setPen(m_pen_white);
    
    drawQText(QString::fromStdString(s), button.m_x-15, button.m_y+5, sizeText_medium);
}


void MainWidget::drawButtons(){
    Framework & f = Framework::Instance();
    
    drawButton(m_buttonBineuse, m_imgBineuse, Langage::getKey("HOME_BINEUSE"));

    
    if(f.m_config.m_gps){
        drawButton(m_buttonGps, m_imgGPS, Langage::getKey("HOME_GPS"));
    }
    if(f.m_config.m_excavator){
        drawButton(m_buttonExcavator, m_imgGPS, Langage::getKey("HOME_EXCAVATOR"));
    }
    if(f.m_config.m_robot){
        drawButton(m_buttonRobot, m_imgGPS, "Robot");
    }
    if(f.m_config.m_serial){
        drawButton(m_buttonSerial, m_imgGPS, Langage::getKey("HOME_SERIAL"));
    }
    
    if(f.m_config.m_wifi2){
        drawButton(m_buttonWifi, m_imgWifi, Langage::getKey("HOME_WIFI"), 1.2);
    }
    if(f.m_config.m_remote){
        drawButtonMultiLines(m_button_remote, m_img_remote, Langage::getKey("HOME_REMOTE"));
    }
    drawButtonOff(m_buttonExit, m_imgExit, Langage::getKey("HOME_OFF"), 0.8);
    drawButton(m_buttonOption, m_imgOption, Langage::getKey("HOME_INFOS"), 1.2);
    /*drawButtonImage(m_buttonMenu, m_imgMenu);
    drawButton(m_buttonMenu2);
    drawButton(m_buttonMenu3);
    drawButton(m_buttonSendMessage);
    drawText("envoyer message", m_buttonSendMessage.m_x, m_buttonSendMessage.m_y, sizeText_little, true);*/
}


int MainWidget::onMouse(int x, int y){
    Framework & f = Framework::Instance();

    if(f.m_config.m_constructor == -1){
        m_init_widget.onMouse(x, y);
        return 0;
    }
    
    size_t n = m_widgets.size();
    for(size_t i = 0; i < n; ++i){
        auto p = m_widgets[n-i-1];
        if(!p->m_close){
            p->onMouse(x, y);
            return 0;
        }
    }
    
    if(m_buttonBineuse.isActive(x, y)){
        std::string cmd = f.m_config.m_bineuse_run;
        cmd = cmd + " -l "+ f.m_config.m_langage;
        cmd = cmd + " -c "+ std::to_string(f.m_config.m_constructor);
        cmd = cmd + " -p "+ f.m_config.m_panel;
        call(cmd);
    } else if(m_buttonGps.isActive(x, y)){
        if(Framework::Instance().m_config.m_gps){
            std::string cmd = f.m_config.m_bineuse_run;
            cmd = cmd + " -l "+ f.m_config.m_langage;
            cmd = cmd + " -c "+ std::to_string(f.m_config.m_constructor);
            cmd = cmd + " -p "+ f.m_config.m_panel;
            call(cmd);
        }
    } else if(m_buttonExcavator.isActive(x, y)){
        if(Framework::Instance().m_config.m_excavator){
            call(f.m_config.m_excavator_run);
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
    if(f.m_config.m_wifi2){
        if(m_buttonWifi.isActive(x, y)){
            m_wifi_widget.open();
        }
    }
    if(f.m_config.m_remote){
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
        f.m_is_f_call = true;
        std::string s2 = s;
        if(f.m_config.m_log_run){
            std::string temp_file = DirectoryManager::instance().m_log_cmd_file;
            s2 = s + " > " + temp_file;
            INFO(s2);
        }
        MainWindow::instancePtr()->call(s2);
    } else {
        INFO("not call! " << s);
        
    }
}
