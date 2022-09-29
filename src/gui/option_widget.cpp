#include "option_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"
#include "../util/directory_manager.hpp"
#include "../config/langage.hpp"
#include "../framework.hpp"

#include <QFileDialog>

#define PETIT_RAYON2 0.025

OptionWidget::OptionWidget()
:m_qt_network(MyQTNetwork::Instance_ptr())
{
    m_black_mode = false;
    m_imgClose = loadImage("/gui/ok.png");
    m_imgPlus = loadImage("/gui/plus.png");
    m_imgMinus = loadImage("/gui/minus.png");
    m_imgSatBlanc = loadImage("/gui/sat_blanc.png");
    m_imgSatGris = loadImage("/gui/sat_gris.png");
    m_imgVolantBlanc = loadImage("/gui/volant_blanc.png");
    m_imgVolantGris = loadImage("/gui/volant_gris.png");
    m_imgOutilBlanc = loadImage("/gui/outil_blanc.png");
    m_imgOutilGris = loadImage("/gui/outil_gris.png");
    m_imgOptionGris = loadImage("/gui/option_gris.png");
    m_imgImuBlanc = loadImage("/gui/imu_blanc.png");
    m_imgImuGris = loadImage("/gui/imu_gris.png");
    
    m_imgOptionBlanc = loadImageInv("/gui/option_blanc.png");
    m_img_cadena = loadImageInv("/gui/cadena.png");
    
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");
    
    m_img_return = loadImageInv("/gui/return.png");
    //m_close=false;
    //m_page =5;
    //addSerials();
    
}

void OptionWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_y2 = m_height*0.04;
    m_x2 = m_y2;
    m_width2 = m_width-2*m_y2-m_gros_button*2.4;
    m_height2 = m_height-2*m_y2;

    m_y_title = m_y2+m_height*0.08;
    m_y_inter = 0.08*m_height2;
    m_y_begin = m_y_title+4*m_y_inter;
    
    m_width3 = m_width2+m_y2+m_y2;
    m_part_1_x = m_width3*0.04;
    m_part_1_w = m_width3*0.44;
    m_part_1_m = m_part_1_x+0.5*m_width3*0.44;
    m_part_1_x2 = m_part_1_x+0.1*m_width3*0.44;
    m_part_1_x3 = m_part_1_x+0.8*m_width3*0.44;
    m_part_2_x = m_width3*0.52;
    m_part_2_w = m_width3*0.44;
    m_part_2_m = m_part_2_x+0.5*m_width3*0.44;
    m_part_2_x2 = m_part_2_x+0.1*m_width3*0.44;
    m_part_2_x3 = m_part_2_x+0.8*m_width3*0.44;
    
    int x_right = width-m_gros_button*1.2;
    int inter = m_gros_button*2.1;
    int y = m_gros_button*1.2;
    y += inter;
    m_button_p1.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p2.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p3.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p4.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p5.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p6.setResize(x_right, y, m_gros_button);
    y += inter;
    m_button_p7.setResize(x_right, y, m_gros_button);
    
    m_button_return.setResize(x_right, m_height-m_gros_button*1.2, m_gros_button);
    
    setSizePage1();
    setSizePage2();
    setSizePage3();
    setSizePage4();
    setSizePage5();
    setSizePage6();
    setSizePage7();
    
    m_select_widget.setSize(width, height);
    //m_keypad_widget.setSize(width, height);
    //m_keyboard_widget.setSize(width, height);
    
}

void OptionWidget::draw(){
    
    
    m_painter->setBrush(m_brush_background_1);
    m_painter->drawRect(0 , 0, m_width, m_height);
    
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRoundedRect(m_x2, m_y2, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    drawButtonOption(m_button_return, m_img_return, false, 0.3);
    
    drawButtonOption(m_button_p1, m_imgOptionBlanc, (m_page == 1), 0.3);
    if(m_page == 1){
        drawPage1();
    }
    
    drawButtonOption(m_button_p2, m_imgOptionBlanc, (m_page == 2), 0.3);
    if(m_page == 2){
        drawPage2();
    }
    
    drawButtonOption(m_button_p3, m_img_cadena, (m_page == 3), 0.3);
    if(m_page == 3){
        drawPage3();
    }
    
    if(Framework::Instance().m_config.m_technicien){
        drawButtonOption(m_button_p4, m_imgOptionBlanc, (m_page == 4), 0.3);
        if(m_page == 4){
            drawPage4();
        };
        
        drawButtonOption(m_button_p5, m_imgOptionBlanc, (m_page == 5), 0.3);
        if(m_page == 5){
            drawPage5();
        };
        
        drawButtonOption(m_button_p6, m_imgOptionBlanc, (m_page == 6), 0.3);
        if(m_page == 6){
            drawPage6();
        };
        
        drawButtonOption(m_button_p7, m_imgOptionBlanc, (m_page == 7), 0.3);
        if(m_page == 7){
            drawPage7();
        };
        //drawButtonOption(m_button_p7, m_img_option_7, (m_page == 7), 0.3);
    }
    
    if(!m_select_widget.m_close){
        m_select_widget.draw();
    }
}

int OptionWidget::onMouse(int x, int y){
    
    if(m_button_return.isActive(x,y)){
        m_close = true;
    } else if(m_button_p1.isActive(x,y)){
        m_page = 1;
    } else if(m_button_p2.isActive(x,y)){
        m_page = 2;
    } else if(m_button_p3.isActive(x,y)){
        m_page = 3;
    } else if(m_button_p4.isActive(x,y)){
        if(Framework::Instance().m_config.m_technicien){
            m_page = 4;
        }
    } else if(m_button_p5.isActive(x,y)){
        if(Framework::Instance().m_config.m_technicien){
            m_page = 5;
        }
    } else if(m_button_p6.isActive(x,y)){
        if(Framework::Instance().m_config.m_technicien){
            m_page = 6;
        }
    } else if(m_button_p7.isActive(x,y)){
        if(Framework::Instance().m_config.m_technicien){
            m_page = 7;
        }
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
        } else if(m_page == 7){
            onMousePage7(x, y);
        }
    }
    return 0;
}


/**
 PAGE 1
 */

void OptionWidget::setSizePage1(){
    int y = m_y_begin;
    m_langage.setResize(m_part_1_x+m_part_1_w/2, y, Langage::getKey("OPT_LANGUAGE"), true, m_part_1_w/2);
    m_langage.clear();
    m_langage.addValue(Langage::getKey("FR"));
    m_langage.addValue(Langage::getKey("EN"));
    m_langage.addValue(Langage::getKey("DE"));
    
    y+= m_y_inter;
    y+= m_y_inter;
    y+= m_y_inter;
    m_unity.setResize(m_part_1_x+m_part_1_w/2, y, Langage::getKey("OPT_LANGUAGE"), true, m_part_1_w/2);
    m_unity.clear();
    m_unity.addValue(Langage::getKey("METRIQUE"));
    m_unity.addValue(Langage::getKey("IMPERIAL"));
};

void OptionWidget::drawPage1(){
    Framework & f = Framework::Instance();
    Config & config = f.m_config;
    
    
    drawText("Menu Infos", 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
    
    drawPart1Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, Langage::getKey("OPT_LANGUAGE"));
    drawPart1Title(m_unity.m_y-2*m_y_inter, m_y_inter*3, Langage::getKey("OPT_UNITY"));
    
    if(m_select_widget.m_close){
        m_langage.setValueString(Langage::getKey(config.m_langage));
    }
    drawButtonLabel2(m_langage.m_buttonOpen);
    
    if(m_select_widget.m_close){
        m_unity.setValueString(Langage::getKey("METRIQUE"));
    }
    drawButtonLabel2(m_unity.m_buttonOpen);
    
    
    drawPart2Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, Langage::getKey("VERSION"));
    drawText(ProjectVersion, m_part_2_m, m_langage.m_y, sizeText_medium, true);
}

void OptionWidget::onMousePage1(int x, int y){
    Framework & f = Framework::Instance();
    Config & config = f.m_config;
    if(!m_select_widget.m_close){
        if(m_select_widget.onMouseSelect(x, y)){
            std::string s = m_select_widget.m_selectButton->getValueString();
            if(s == Langage::getKey("FR")){
                config.m_langage = "FR";
            } else if(s == Langage::getKey("EN")){
                config.m_langage = "EN";
            } else if(s == Langage::getKey("DE")){
                config.m_langage = "DE";
            }
        }
       
        return;
    }
    
    if(m_langage.m_buttonOpen.isActive(x, y)){
        m_select_widget.open();
        m_select_widget.setValueGuiKeyPad(&m_langage);
    }
}

/**
 PAGE 2
 */

void OptionWidget::setSizePage2(){
    int y = m_y_begin;
    m_update_bineuse.setResizeStd(m_part_1_x+m_part_1_w/2, y, "Update Bineuse Wifi", true, m_part_1_w/2);
    m_update_bineuse_usb.setResizeStd(m_part_2_x+m_part_1_w/2, y, "Update Bineuse USB", true, m_part_1_w/2);
    y+= m_y_inter;
    m_update_gps.setResizeStd(m_part_1_x+m_part_1_w/2, y, "Update GPS", true, m_part_1_w/2);
    y+= m_y_inter;
    m_serial.setResizeStd(m_part_1_x+m_part_1_w/2, y, "Update Serial", true, m_part_1_w/2);
    y+= m_y_inter;
    m_update_robot.setResizeStd(m_part_1_x+m_part_1_w/2, y, "Update Robot", true, m_part_1_w/2);
    y+= m_y_inter;
    
    
};

void OptionWidget::drawPage2(){
    Framework & f = Framework::Instance();
    drawText("Mise à jour", 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
    
    if(f.m_config.m_wifi){
        drawPart1Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, "Update Wifi");
        
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
        drawPart2Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, "Update USB");
        
        drawButtonLabel2(m_update_bineuse_usb);
    }
    
    if(!m_file_widget.m_close){
        m_file_widget.draw();
    }
}

void OptionWidget::onMousePage2(int x, int y){
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
 PAGE 3
 */

void OptionWidget::setSizePage3(){
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

void OptionWidget::drawPage3(){
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
void OptionWidget::onMousePage3(int x, int y){
    if(i5 == 0 && m_button6.isActive(x, y)){
        i5 = 1;
    } else if(i5 == 1 && m_button1.isActive(x, y)){
        i5 = 2;
    } else if(i5 == 2 && m_button5.isActive(x, y)){
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



void OptionWidget::setSizePage4(){
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

void OptionWidget::drawPage4(){
    Framework & f = Framework::Instance();
    
    drawButtonCheck(m_button_gps, f.m_config.m_gps, "gps");
    drawButtonCheck(m_button_robot, f.m_config.m_robot, "robot inrows");
    drawButtonCheck(m_button_serial, f.m_config.m_serial, "serial");
    
    drawButtonCheck(m_button_wifi, f.m_config.m_wifi, "wifi");
    drawButtonCheck(m_button_usb, f.m_config.m_usb, "usb");
    
    
    
}

void OptionWidget::onMousePage4(int x, int y){
    
    
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
 PAGE 5
 */

void OptionWidget::setSizePage5(){
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



void OptionWidget::drawPage5(){
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

void OptionWidget::onMousePage5(int x, int y){
    KeyBoardWidget & key_board_widget = MainWidget::instancePtr()->m_key_board_widget;
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
            call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/make_archive.sh");;
        }
    }
    
    if(m_run_cmd.isActive(x, y)){
        key_board_widget.m_close = false;
    }
    if(m_update_lemca.isActive(x, y)){
        call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/lemca_update_wifi.sh");
    }
    if(m_update_deps.isActive(x, y)){
        call("echo lemca | su -c \"sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/install_dep.sh\"");
    }
    if(m_quit_full_screen.isActive(x, y)){
        MainWindow::instancePtr()->quitFullScreen();
    }
    if(m_clear_data.isActive(x, y)){
        DirectoryManager::Instance().clearAll();
    }
}


/**
 PAGE 6
 */

void OptionWidget::setSizePage6(){
    int x = m_width*0.3;
    int y = m_height*0.2;
    m_refresh.setResizeStd(x, y, "Refresh", false);
    x = m_width*0.2;
    m_camera30.setResize(x, m_height*0.4, "Refresh", m_gros_button);
    m_camera31.setResize(x, m_height*0.5, "Refresh", m_gros_button);
    m_reseau.setResizeStd(m_width*0.3, m_height*0.7, "Reseau");
};

void OptionWidget::drawPage6(){
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
    
    drawButtonLabel2(m_reseau);
}

void OptionWidget::onMousePage6(int x, int y){
    if(m_refresh.isActive(x, y)){
        m_qt_network->test_camera();;
    }
    if(m_camera30.isActive(x, y)){
        call("onboard & firefox http://192.168.1.30");
    }
    if(m_camera31.isActive(x, y)){
        call("onboard & firefox http://192.168.1.31");
    }
    if(m_reseau.isActive(x, y)){
        call("nmap 192.168.1.0/24");
    }
}


/**
 PAGE 7
 */

void OptionWidget::setSizePage7(){
    
    int inter = m_width*0.07;
    int y = m_height*0.25;
    int x = m_width*0.2;
    y+= inter;
    INFO(x << " " << y);
    m_port.setResizeLabel(x, y, "port label");
    m_port.setResize(x, y, m_gros_button);
    y+= inter;
    m_auto_launch.setResizeStd(x, y, "none");
};

void OptionWidget::drawPage7(){
    drawText("robot", m_width*0.5, m_height*0.1, sizeText_big, true);
    
    Framework & f = Framework::Instance();
    drawValueGuiAndLabel(m_port, f.m_config.m_port_remote);
    
    if(f.m_config.m_auto_launch == AutoLaunch_Robot){
        m_auto_launch.m_label = "auto launch robot";
    } else {
        m_auto_launch.m_label = "none";
    }
    drawButtonLabel2(m_auto_launch);
}

void OptionWidget::onMousePage7(int x, int y){
    Framework & f = Framework::Instance();
    if(onMouseKeyPad2(m_port, x, y, 1)){
        f.m_config.m_port_remote = m_port.m_value;
        f.initOrLoadConfig();
    }
    if(m_auto_launch.isActive(x, y)){
        int i = (int)f.m_config.m_auto_launch;
        i = (i+1)%2;
        f.m_config.m_auto_launch = (AutoLaunch)i;
        f.initOrLoadConfig();
    }
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
    MainWidget::instancePtr()->m_cmd_widget.open();
}


void OptionWidget::call2(const std::string & s){
    std::string s2 = "xterm -e \"" + s + "\"";
    INFO("call " << s2);
    system(s2.c_str());
}


/**
 BASE
 */

void OptionWidget::drawButtonOption(ButtonGui & button, QPixmap * image, bool check, double scale){
    drawButtonImageCarre(button, image, scale*3, check);

}

void OptionWidget::drawPart1Title(double y, double h, const std::string & title, bool separateur){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushNo);
    //m_painter->drawRoundedRect(m_part_1_x, y+8, m_width3*0.44, h-16, 5, 5);
    drawText(title, m_part_1_x+m_part_1_w/2, y+m_y_inter*0.8, sizeText_big, true);
    if(separateur){
        drawSeparateurV1(y);
    }
    
}

void OptionWidget::drawPart2Title(double y, double h, const std::string & title, bool separateur){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushNo);
    //m_painter->drawRoundedRect(m_part_2_x, y+8, m_width3*0.44, h-16, 5, 5);
    drawText(title, m_part_2_x+m_part_1_w/2, y+m_y_inter*0.8, sizeText_big, true);
    if(separateur){
        drawSeparateurV2(y);
    }
}

void OptionWidget::drawPart2(double y, double h, bool separateur){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushNo);
    //m_painter->drawRoundedRect(m_part_2_x, y+8, m_width3*0.44, h-16, 5, 5);
    if(separateur){
        drawSeparateurV2(y);
    }
}


void OptionWidget::drawSeparateurH(){
    m_painter->drawLine(m_width3/2, m_height*0.25, m_width3/2, m_height*0.75);
}

void OptionWidget::drawSeparateurV1(double y){
    m_painter->drawLine(m_part_1_x+m_part_1_w*0.2, y, m_part_1_x+m_part_1_w*0.8, y);
    
}

void OptionWidget::drawSeparateurV2(double y){
    m_painter->drawLine(m_part_2_x+m_part_2_w*0.2, y, m_part_2_x+m_part_2_w*0.8, y);
    
}
