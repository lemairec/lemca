#include "option_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"
#include "../util/directory_manager.hpp"
#include "../framework.hpp"

#include <QFileDialog>

#define PETIT_RAYON2 0.025

OptionWidget::OptionWidget()
:m_qt_network(MyQTNetwork::Instance_ptr())
{
    
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
    m_file_widget.setSize(width, height);
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
            drawButtonImage(m_button_p4, m_imgOptionBlanc);
            drawPage4();
        } else {
            drawButtonImage(m_button_p4, m_imgOptionGris);
        }
        
        //GpsFramework & f = GpsFramework::Instance();
        
        if(m_page == 5){
            drawButtonImage(m_button_p5, m_imgOptionBlanc);
            drawPage5();
        } else {
            drawButtonImage(m_button_p5, m_imgOptionGris);
        }
        
        /*if(m_page == 6){
            drawButtonImage(m_button_p6, m_imgVolantBlanc);
            drawPage6();
        } else {
            drawButtonImage(m_button_p6, m_imgVolantGris);
        }*/
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
    int x = 0.15*m_width;
    int x2 = 0.55*m_width;
    int y = 0.3*m_height;
    int inter = 0.15*m_height;
    
    m_update_bineuse.setResizeStd(x, y, "Update Bineuse Wifi", false, 220);
    m_update_bineuse_usb.setResizeStd(x2, y, "Update Bineuse USB", false, 220);
    y+= inter;
    m_update_gps.setResizeStd(x, y, "Update GPS", false, 220);
    y+= inter;
    m_serial.setResizeStd(x, y, "Update Serial", false, 220);
    y+= inter;
    m_update_robot.setResizeStd(x, y, "Update Robot", false, 220);
    y+= inter;
    
    
};

void OptionWidget::drawPage1(){
    Framework & f = Framework::Instance();
    drawText(ProjectVersion, 0.2*m_width, 0.8*m_height);
    
    if(f.m_config.m_wifi){
        drawText("Update Wifi", 0.25*m_width, 0.15*m_height, sizeText_medium, true);
        drawButtonLabel2(m_update_bineuse);
        if(f.m_config.m_gps){
            drawButtonLabel2(m_update_gps);
        }
        if(f.m_config.m_serial){
            drawButtonLabel2(m_serial);
        }
        if(f.m_config.m_robot){
            drawButtonLabel2(m_update_robot);
        }
    }
    if(f.m_config.m_usb){
        drawText("Update USB", 0.75*m_width, 0.15*m_height, sizeText_medium, true);
        drawButtonLabel2(m_update_bineuse_usb);
    }
    
    if(!m_file_widget.m_close){
        m_file_widget.draw();
    }
}

void OptionWidget::onMousePage1(int x, int y){
    Framework & f = Framework::Instance();
    if(f.m_config.m_wifi){
        if(m_update_bineuse.isActive(x, y)){
            if(f.m_config.m_code_source){
                call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/bineuse_src_update_wifi.sh");
            } else {
                call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/bineuse_update_wifi.sh");
            }
        }
        if(f.m_config.m_gps){
            if(m_update_gps.isActive(x, y)){
                call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/agrigpspi_update_wifi.sh");
            }
        }
        if(f.m_config.m_serial){
            if(m_serial.isActive(x, y)){
                call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/serie_update_wifi.sh");
            }
        }
        if(f.m_config.m_robot == 1){
            if(m_update_robot.isActive(x, y)){
                call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/robot_inrows_update_wifi.sh");
            }
        }
    }
    
    
    if(f.m_config.m_usb){
        if(!m_file_widget.m_close){
            if(m_file_widget.onMouse(x, y)){
                std::string s = "/media/lemca/"+m_file_widget.m_select_files.getValueString()+"/bineuse.tar.gz";
                call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/bineuse_update_usb.sh " + s);
            } else {
                call("echo fail; exit 1;");
            }
        }
        if(m_update_bineuse_usb.isActive(x, y)){
            m_file_widget.open();
        }
    }
}


/**
 PAGE 2
 */

void OptionWidget::resizePage2(){
    int inter = m_width*0.08;
    int x =  m_width*0.5;
    int rayon = m_gros_button;
    int y_begin = m_height*0.4;
    
    int y = y_begin - inter;
    m_button7.setResizeStd(x-inter, y, "7", true, 2*rayon, 2*rayon);
    m_button8.setResizeStd(x, y, "8", true, 2*rayon, 2*rayon);
    m_button9.setResizeStd(x+inter, y, "9", true, 2*rayon, 2*rayon);
    
    y = y_begin;
    m_button4.setResizeStd(x-inter, y, "4", true, 2*rayon, 2*rayon);
    m_button5.setResizeStd(x, y, "5", true, 2*rayon, 2*rayon);
    m_button6.setResizeStd(x+inter, y, "6", true, 2*rayon, 2*rayon);
    
    y = y_begin + inter;
    m_button1.setResizeStd(x-inter, y, "1", true, 2*rayon, 2*rayon);
    m_button2.setResizeStd(x, y, "2", true, 2*rayon, 2*rayon);
    m_button3.setResizeStd(x+inter, y, "3", true, 2*rayon, 2*rayon);
    
    y = y_begin + 3*inter;
    m_button_technicien.setResize(m_width*0.3, y, rayon);
    
    
}

void OptionWidget::myDrawButton(ButtonGui * b, QString s){
    drawButtonLabel2(*b, COLOR_WHITE);
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
 PAGE 3
 */



void OptionWidget::resizePage3(){
    int inter = m_width*0.07;
    int y = m_height*0.25;
    int x = m_width*0.2;
    m_button_gps.setResize(x, y, m_gros_button);
    y+= inter;
    m_button_robot.setResize(x, y, m_gros_button);
    y+= inter;
    m_button_serial.setResize(x, y, m_gros_button);
    y+= inter;
    y+= inter;
    m_button_wifi.setResize(x, y, m_gros_button);
    y+= inter;
    m_button_usb.setResize(x, y, m_gros_button);
    y = m_height*0.25;
    x = m_width*0.55;
};

void OptionWidget::drawPage3(){
    Framework & f = Framework::Instance();
    
    drawButtonCheck(m_button_gps, f.m_config.m_gps, "gps");
    drawButtonCheck(m_button_robot, f.m_config.m_robot, "robot inrows");
    drawButtonCheck(m_button_serial, f.m_config.m_serial, "serial");
    
    drawButtonCheck(m_button_wifi, f.m_config.m_wifi, "wifi");
    drawButtonCheck(m_button_usb, f.m_config.m_usb, "usb");
    
    
    
}

void OptionWidget::onMousePage3(int x, int y){
    
    
    Framework & f = Framework::Instance();
    if(m_button_gps.isActive(x, y)){
        f.m_config.m_gps = !f.m_config.m_gps;
        f.initOrLoadConfig();
    }
    if(m_button_robot.isActive(x, y)){
        f.m_config.m_robot += 1;
        f.m_config.m_robot = f.m_config.m_robot%2;
        f.initOrLoadConfig();
    }
    if(m_button_serial.isActive(x, y)){
        f.m_config.m_serial = !f.m_config.m_serial;
        f.initOrLoadConfig();
    }
    if(m_button_wifi.isActive(x, y)){
        f.m_config.m_wifi = !f.m_config.m_wifi;
        f.initOrLoadConfig();
    }
    if(m_button_usb.isActive(x, y)){
        f.m_config.m_usb = !f.m_config.m_usb;
        f.initOrLoadConfig();
    }
}

/**
 PAGE 4
 */

void OptionWidget::resizePage4(){
    int inter = m_width*0.07;
    int y = m_height*0.25;
    int x = m_width*0.2;
    m_button_code_source.setResize(x, y, m_gros_button);
    y+= inter;
    m_button_full_screen.setResize(x, y, m_gros_button);
    y+= inter*1.5;
    m_clear_data.setResizeStd(m_width*0.15, y, "Clear Data", false, 220);
   
    y+= inter;
    m_update_deps.setResizeStd(m_width*0.15, y, "Install dep", false, 220);
    
    y = m_height*0.25;
    x = m_width*0.55;
    m_run_cmd.setResizeStd(x, y, "Run cmd", false, 220);
    y+= inter*1.5;
    m_make_archive.setResizeStd(x, y, "Make archive", false, 220);
    y+= inter;
    m_update_lemca.setResizeStd(x, y, "Update Lemca", false, 220);
    y+= inter;
    m_quit_full_screen.setResizeStd(x, y, "Quit FullScreen", false, 220);
}



void OptionWidget::drawPage4(){
    Framework & f = Framework::Instance();
    drawButtonCheck(m_button_code_source, f.m_config.m_code_source);
    int x = m_width*0.25;
    drawText("code source", x, m_button_code_source.m_y);
    
    drawButtonCheck(m_button_full_screen, f.m_config.m_fullscreen);
    drawText("full screen", x, m_button_full_screen.m_y);
    
    if(f.m_config.m_code_source){
        drawButtonLabel2(m_make_archive);
    }
    
    drawButtonLabel2(m_run_cmd);
    drawButtonLabel2(m_update_lemca);
    drawButtonLabel2(m_update_deps);
    drawButtonLabel2(m_clear_data);
    drawButtonLabel2(m_quit_full_screen);
}

void OptionWidget::onMousePage4(int x, int y){
    KeyBoardWidget & key_board_widget = MainWidget::instance()->m_key_board_widget;
    //Framework & f = Framework::Instance();
    if(!key_board_widget.m_close){
        if(key_board_widget.onMouse(x, y)){
            std::string s1 = key_board_widget.getText().toUtf8().constData();
            call(s1);
            m_close = false;
            key_board_widget.clear();
        };
        return;
    }
    
    Framework & f = Framework::Instance();
    if(m_button_code_source.isActive(x, y)){
        f.m_config.m_code_source = !f.m_config.m_code_source;
        f.initOrLoadConfig();
    }
    if(m_button_full_screen.isActive(x, y)){
        f.m_config.m_fullscreen = !f.m_config.m_fullscreen;
        f.initOrLoadConfig();
    }
    if(f.m_config.m_code_source){
        if(m_make_archive.isActive(x, y)){
            std::string s1 = f.m_config.m_make_archive;
            call(s1);
        }
    }
    
    if(m_run_cmd.isActive(x, y)){
        key_board_widget.m_close = false;
    }
    if(m_update_lemca.isActive(x, y)){
        call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/lemca_update_wifi.sh");
    }
    if(m_update_deps.isActive(x, y)){
        call("echo lemca | su -S sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/install_dep.sh");
    }
    if(m_quit_full_screen.isActive(x, y)){
        MainWindow::instance()->quitFullScreen();
    }
    if(m_clear_data.isActive(x, y)){
        DirectoryManager::Instance().clearAll();
    }
}


/**
 PAGE 5
 */

void OptionWidget::resizePage5(){
    int x = m_width*0.3;
    int y = m_height*0.2;
    m_refresh.setResizeStd(x, y, "Refresh", false, 220);
    x = m_width*0.2;
    m_camera30.setResize(x, m_height*0.4, "Refresh", m_gros_button);
    m_camera31.setResize(x, m_height*0.5, "Refresh", m_gros_button);
    
};

void OptionWidget::drawPage5(){
    drawButtonLabel2(m_refresh);
    
    int x = m_width*0.3;
    if(m_qt_network->m_camera_30_connected){
        m_painter->setPen(Qt::darkGreen);
    } else {
        m_painter->setPen(Qt::red);
    }
    drawText("192.168.1.30", x, m_height*0.4, sizeText_big);
    drawButtonImage(m_camera30, m_imgOptionGris);
    
    if(m_qt_network->m_camera_31_connected){
        m_painter->setPen(Qt::darkGreen);
    } else {
        m_painter->setPen(Qt::red);
    }
    drawText("192.168.1.31", x, m_height*0.5, sizeText_big);
    drawButtonImage(m_camera31, m_imgOptionGris);
    m_painter->setPen(m_penBlack);
}

void OptionWidget::onMousePage5(int x, int y){
    if(m_refresh.isActive(x, y)){
        m_qt_network->test_camera();;
    }
    if(m_camera30.isActive(x, y)){
        call("florence & firefox http://192.168.1.30");
    }
    if(m_camera31.isActive(x, y)){
        call("florence & firefox http://192.168.1.31");
    }
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




void OptionWidget::open(){
    m_close = false;
    m_file_widget.m_close = true;
}

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


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

