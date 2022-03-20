#include "option_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"

#include "../framework.hpp"

#define PETIT_RAYON2 0.025

OptionWidget::OptionWidget(){
    
    m_imgClose = loadImage("/gui/ok.png");
    m_imgPlus = loadImage("/images/plus.png");
    m_imgMinus = loadImage("/images/minus.png");
    m_imgSatBlanc = loadImage("/images/sat_blanc.png");
    m_imgSatGris = loadImage("/images/sat_gris.png");
    m_imgVolantBlanc = loadImage("/images/volant_blanc.png");
    m_imgVolantGris = loadImage("/images/volant_gris.png");
    m_imgOutilBlanc = loadImage("/images/outil_blanc.png");
    m_imgOutilGris = loadImage("/images/outil_gris.png");
    m_imgOptionBlanc = loadImage("/gui/option_blanc.png");
    m_imgOptionGris = loadImage("/gui/option_gris.png");
    m_imgImuBlanc = loadImage("/images/imu_blanc.png");
    m_imgImuGris = loadImage("/images/imu_gris.png");
    
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");
    //m_close=false;
    //m_page =5;
    //addSerials();
}

void OptionWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_button_close.setResize(0.75*m_width, 0.83*m_height, m_gros_button);
    
    m_button_p1.setResize(0.95*m_width, 0.20*m_height, m_gros_button);
    m_button_p2.setResize(0.95*m_width, 0.30*m_height, m_gros_button);
    m_button_p3.setResize(0.95*m_width, 0.40*m_height, m_gros_button);
    m_button_p4.setResize(0.95*m_width, 0.50*m_height, m_gros_button);
    m_button_p5.setResize(0.95*m_width, 0.60*m_height, m_gros_button);
    m_button_p6.setResize(0.95*m_width, 0.70*m_height, m_gros_button);
    
    resizePage1();
    resizePage2();
    resizePage3();
    resizePage4();
    resizePage5();
    resizePage6();
    
}

void OptionWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRect(0, 0, m_width, m_height);
    m_painter->setBrush(m_brushDarkGray);
    m_painter->drawRect(m_width*0.9, 0, m_width*0.1, m_height);
    
    drawButtonImage(m_button_close, m_imgClose);
    
    if(m_page == 1){
        drawButtonImage(m_button_p1, m_imgOptionBlanc);
        drawPage1();
    } else {
        drawButtonImage(m_button_p1, m_imgOptionGris);
    }
    
    if(m_page == 2){
        drawButtonImage(m_button_p2, m_imgOptionBlanc);
        drawPage2();
    } else {
        drawButtonImage(m_button_p2, m_imgOptionGris);
        
    }
    
    if(Framework::Instance().m_config.m_technicien){
        if(m_page == 3){
            drawButtonImage(m_button_p3, m_imgOptionBlanc);
            drawPage3();
        } else {
            drawButtonImage(m_button_p3, m_imgOptionGris);
            
        }
        
        if(m_page == 4){
            drawButtonImage(m_button_p4, m_imgVolantBlanc);
            drawPage4();
        } else {
            drawButtonImage(m_button_p4, m_imgVolantGris);
        }
        
        //GpsFramework & f = GpsFramework::Instance();
        
        if(m_page == 5){
            drawButtonImage(m_button_p5, m_imgVolantBlanc);
            drawPage5();
        } else {
            drawButtonImage(m_button_p5, m_imgVolantGris);
        }
        
        if(m_page == 6){
            drawButtonImage(m_button_p6, m_imgVolantBlanc);
            drawPage6();
        } else {
            drawButtonImage(m_button_p6, m_imgVolantGris);
        }
    }
}

int OptionWidget::onMouse(int x, int y){
    
    if(m_button_close.isActive(x,y)){
        m_close = true;
    } else if(m_button_p1.isActive(x,y)){
        m_page = 1;
    } else if(m_button_p2.isActive(x,y)){
        m_page = 2;
    } else if(m_button_p3.isActive(x,y)){
        if(Framework::Instance().m_config.m_technicien){
            m_page = 3;
        }
    } else if(m_button_p4.isActive(x,y)){
        m_page = 4;
    } else if(m_button_p5.isActive(x,y)){
        m_page = 5;
    } else if(m_button_p6.isActive(x,y)){
        m_page = 6;
    } else {
        if(m_page == 1){
            onMousePage1(x, y);
        } else if(m_page == 2){
            onMousePage2(x, y);
        } else if(m_page == 3){
            onMousePage3(x, y);
        } else if(m_page == 4){
            onMousePage4(x, y);
        } else if(m_page == 5){
            onMousePage5(x, y);
        } else if(m_page == 6){
            onMousePage6(x, y);
        }
    }
    return 0;
}


/**
 PAGE 1
 */

void OptionWidget::resizePage1(){
    //m_select_serial
    int x = 0.3*m_width;
    int y = 0.4*m_height;
    int inter = 0.1*m_height;
    
    m_update_bineuse.setResize(x, y, m_petit_button);
    y+= inter;
    m_update_gps.setResize(x, y, m_petit_button);
    y+= inter;
    m_serial.setResize(x, y, m_petit_button);
    y+= inter;
    m_update_robot.setResize(x, y, m_petit_button);
};

void OptionWidget::drawPage1(){
    Framework & f = Framework::Instance();
    drawText("Update", 0.5*m_width, 0.3*m_height);
    drawText(ProjectVersion, 0.2*m_width, 0.8*m_height);
    
    drawButton(m_update_bineuse);
    drawText("Update Bineuse", 0.4*m_width, m_update_bineuse.m_y);
    if(f.m_config.m_gps){
        drawButton(m_update_gps);
        drawText("Update Gps", 0.4*m_width, m_update_gps.m_y);
    }
    if(f.m_config.m_serial){
        drawButton(m_serial);
        drawText("Update Serial", 0.4*m_width, m_serial.m_y);
    }
    if(f.m_config.m_robot){
        drawButton(m_update_robot);
        drawText("Update Robot", 0.4*m_width, m_update_robot.m_y);
    }
        
}

void OptionWidget::onMousePage1(int x, int y){
    Framework & f = Framework::Instance();
    if(m_update_bineuse.isActive(x, y)){
        std::string s1 = f.m_config.m_bineuse_update;
        if(f.m_config.m_code_source){
            s1 = f.m_config.m_bineuse_src_update;
        }
        call(s1);
    }
    if(f.m_config.m_gps){
        if(m_update_gps.isActive(x, y)){
            std::string s1 = f.m_config.m_gps_update;
            call(s1);
        }
    }
    if(f.m_config.m_serial){
        if(m_serial.isActive(x, y)){
            call(f.m_config.m_serie_update);
        }
    }
    if(f.m_config.m_robot == 1){
        if(m_update_robot.isActive(x, y)){
            std::string s1 = f.m_config.m_robot_gps_update;
            call(s1);
        }
    }
    if(f.m_config.m_robot == 2){
        if(m_update_robot.isActive(x, y)){
            std::string s1 = f.m_config.m_robot_inrows_update;
            call(s1);
        }
    }
}


/**
 PAGE 2
 */

void OptionWidget::resizePage2(){
    int inter = m_width*0.08;
    int x = m_width*0.5;
    int rayon = m_gros_button;
    ///usr/bin/python /home/lemca/lemca/lemca.py
    int y = m_height*0.5- inter;
    m_button7.setResize(x-inter, y, rayon);
    m_button8.setResize(x, y, rayon);
    m_button9.setResize(x+inter, y, rayon);
    
    y = m_height*0.5;
    m_button4.setResize(x-inter, y, rayon);
    m_button5.setResize(x, y, rayon);
    m_button6.setResize(x+inter, y, rayon);
    
    y = m_height*0.5 + inter;
    m_button1.setResize(x-inter, y, rayon);
    m_button2.setResize(x, y, rayon);
    m_button3.setResize(x+inter, y, rayon);
    
    y = m_height*0.5 + 2*inter;
    m_button_technicien.setResize(m_width*0.3, y, rayon);
    
    
}

void OptionWidget::myDrawButton(ButtonGui * b, QString s){
    drawButton(*b);
    drawQText(s, b->m_x, b->m_y, sizeText_medium, true);
}

void OptionWidget::drawPage2(){
    myDrawButton(&m_button1, "1");
    myDrawButton(&m_button2, "2");
    myDrawButton(&m_button3, "3");
    myDrawButton(&m_button4, "4");
    myDrawButton(&m_button5, "5");
    myDrawButton(&m_button6, "6");
    myDrawButton(&m_button7, "7");
    myDrawButton(&m_button8, "8");
    myDrawButton(&m_button9, "9");
    
    drawButtonCheck(m_button_technicien, Framework::Instance().m_config.m_technicien);
    drawText("technicien", m_width*0.4, m_button_technicien.m_y);
}

int i5 = 0;
void OptionWidget::onMousePage2(int x, int y){
    if(i5 == 0 && m_button6.isActive(x, y)){
        i5 = 1;
    } else if(i5 == 1 && m_button2.isActive(x, y)){
        i5 = 2;
    } else if(i5 == 2 && m_button1.isActive(x, y)){
        i5 = 3;
    } else if(i5 == 3 && m_button5.isActive(x, y)){
        Framework::Instance().m_config.m_technicien = true;
        i5 = 4;
    } else {
        i5 = 0;
    }
    INFO(i5);
}



/**
 PAGE 4
 */

void OptionWidget::resizePage3(){
    int inter = m_width*0.07;
    int y = m_height*0.25;
    m_button_code_source.setResize(m_width*0.3, y, m_gros_button);
    y+= inter;
    m_button_full_screen.setResize(m_width*0.3, y, m_gros_button);
    y+= inter;
    m_button_gps.setResize(m_width*0.3, y, m_gros_button);
    y+= inter;
    m_button_robot.setResize(m_width*0.3, y, m_gros_button);
    y+= inter;
    m_button_serial.setResize(m_width*0.3, y, m_gros_button);
    y = m_height*0.25;
    m_make_archive.setResize(m_width*0.6, y, m_gros_button);
    y+= inter;
    y+= inter;
    m_update_lemca.setResize(m_width*0.6, y, m_gros_button);
    y+= inter;
    m_button_exit.setResize(m_width*0.6, y, m_gros_button);
    
};

void OptionWidget::drawPage3(){
    Framework & f = Framework::Instance();
    
    drawButtonCheck(m_button_code_source, f.m_config.m_code_source);
    drawText("code source", m_width*0.35, m_button_code_source.m_y);
    
    drawButtonCheck(m_button_full_screen, f.m_config.m_fullscreen);
    drawText("full screen", m_width*0.35, m_button_full_screen.m_y);
    
    drawButtonCheck(m_button_gps, f.m_config.m_gps);
    drawText("gps", m_width*0.35, m_button_gps.m_y);
    
    if(f.m_config.m_robot){
        drawButton(m_button_robot, COLOR_CHECK);
    } else {
        drawButton(m_button_robot);
    }
    if(f.m_config.m_robot == 1){
        drawText("robot gps", m_width*0.35, m_button_robot.m_y);
    } else if(f.m_config.m_robot == 2){
        drawText("robot inrows", m_width*0.35, m_button_robot.m_y);
    } else {
        drawText("robot "+ std::to_string(f.m_config.m_robot), m_width*0.35, m_button_robot.m_y);
    }
    
   
    drawButtonCheck(m_button_serial, f.m_config.m_serial);
    drawText("serial", m_width*0.35, m_button_serial.m_y);
    
    if(f.m_config.m_code_source){
        drawButton(m_make_archive);
        drawText("make archive", m_width*0.65, m_make_archive.m_y);
       
    }
    
    drawButton(m_update_lemca);
    drawText("update lemca", m_width*0.65, m_update_lemca.m_y);
    
    drawButton(m_button_exit);
    drawText("quitter", m_width*0.65, m_button_exit.m_y);
    
}

void OptionWidget::onMousePage3(int x, int y){
    Framework & f = Framework::Instance();
    if(m_button_code_source.isActive(x, y)){
        f.m_config.m_code_source = !f.m_config.m_code_source;
        f.initOrLoadConfig();
    }
    if(m_button_full_screen.isActive(x, y)){
        f.m_config.m_fullscreen = !f.m_config.m_fullscreen;
        f.initOrLoadConfig();
    }
    if(m_button_gps.isActive(x, y)){
        f.m_config.m_gps = !f.m_config.m_gps;
        f.initOrLoadConfig();
    }
    if(m_button_robot.isActive(x, y)){
        f.m_config.m_robot += 1;
        f.m_config.m_robot = f.m_config.m_robot%3;
        f.initOrLoadConfig();
    }
    if(m_button_serial.isActive(x, y)){
        f.m_config.m_serial = !f.m_config.m_serial;
        f.initOrLoadConfig();
    }
    
    if(m_button_exit.isActive(x, y)){
        exit(0);
    }
    if(m_make_archive.isActive(x, y)){
        std::string s1 = f.m_config.m_make_archive;
        call(s1);
    }
    if(m_update_lemca.isActive(x, y)){
        std::string s1 = f.m_config.m_update_lemca;
        call2(s1);
        call2("/sbin/shutdown -h now");
    }
}


/**
 PAGE 5
 */

void OptionWidget::resizePage5(){
    m_button_motor_inverse.setResize(0.35*m_width, 0.20*m_height, m_petit_button);
    m_button_encoder_inverse.setResize(0.6*m_width, 0.20*m_height, m_petit_button);
    
    m_motor_vitesse_agressivite.setResize(0.35*m_width, 0.3*m_height, m_petit_button, "moteur agressivite ");
    m_motor_vitesse_max.setResize(0.35*m_width, 0.35*m_height, m_petit_button, "moteur vitesse max ");
    m_volant_pas_by_tour.setResize(0.35*m_width, 0.45*m_height, m_petit_button, "encoder pas par tour ");
    m_volant_angle_by_tour.setResize(0.35*m_width, 0.5*m_height, m_petit_button, "roue angle par tour de volant ");
    m_volant_derive.setResize(0.35*m_width, 0.55*m_height, m_petit_button, "rattrapage de derive ");
    
    m_volant_frequence.setResize(0.35*m_width, 0.65*m_height, m_petit_button, "frequence ");
    m_virtual_point.setResize(0.35*m_width, 0.7*m_height, m_petit_button, "virtual point ");
    
    m_button_auto_deactive.setResize(0.35*m_width, 0.8*m_height, m_petit_button, "auto deactive ");
    m_button_auto_active.setResize(0.35*m_width, 0.85*m_height, m_petit_button, "auto active ");
};

void OptionWidget::drawPage5(){
    
}

void OptionWidget::onMousePage5(int x, int y){
    
}


/**
 PAGE 6
 */

void OptionWidget::resizePage6(){
};

void OptionWidget::drawPage6(){
    }

void OptionWidget::onMousePage6(int x, int y){
   
}


/**
 PAGE 4
 */

void OptionWidget::resizePage4(){
}



void OptionWidget::drawPage4(){
   
}

void OptionWidget::onMousePage4(int x, int y){
    
}

void OptionWidget::open(){
    addSerials();
}

void OptionWidget::addSerials(){
    //Framework & f = Framework::Instance();
    
}

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string execute4(std::string cmd) {
    
    return "";
}

void OptionWidget::call(const std::string & s){
    Framework & f = Framework::Instance();
    f.mutex.lock();
    f.m_command_to_execute2 = s+" 2>&1";
    f.bufferNotEmpty.wakeAll();
    f.mutex.unlock();
    
    m_close = true;
    MainWidget::instance()->m_cmd_widget.open();
}


void OptionWidget::call2(const std::string & s){
    std::string s2 = "xterm -e \"" + s + "\"";
    INFO("call " << s2);
    system(s2.c_str());
}

