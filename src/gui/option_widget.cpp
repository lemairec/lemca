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
    m_img_update = loadImageInv("/gui/update.png");
    
    m_img_check_on = loadImage("/gui/check_on.png");
    m_img_check_off = loadImage("/gui/check_off.png");
    
    m_img_return = loadImageInv("/gui/return.png");
    //m_close=false;
    //m_page =5;
    //addSerials();
    
}


void OptionWidget::open(){
    m_close = false;
    m_file_widget.m_close = true;
    m_qt_network->m_test_camera = true;
}


void OptionWidget::close(){
    m_close = true;
    m_qt_network->m_test_camera = false;
}

void OptionWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_y2 = m_height*0.04;
    m_x2 = m_y2;
    m_width2 = m_width-2*m_y2-m_gros_button*2.4;
    m_height2 = m_height-2*m_y2;

    m_y_title = m_y2+m_height*0.08;
    m_y_inter = 0.08*m_height2;
    m_y_begin = m_y_title+3*m_y_inter;
    
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
    
    drawButtonOption(m_button_p2, m_img_update, (m_page == 2), 0.4);
    if(m_page == 2){
        drawPage2();
    }
    
    drawButtonOption(m_button_p3, m_img_cadena, (m_page == 3), 0.3);
    if(m_page == 3){
        drawPage3();
    }
    
    if(Framework::Instance().m_config.isTechnicien()){
        drawButtonOption(m_button_p4, m_imgOptionBlanc, (m_page == 4), 0.3);
        if(m_page == 4){
            drawPage4();
        };
    }
    if(Framework::Instance().m_config.isDeveloppeur()){
        drawButtonOption(m_button_p5, m_imgOptionBlanc, (m_page == 5), 0.3);
        if(m_page == 5){
            drawPage5();
        };
        
        drawButtonOption(m_button_p6, m_imgOptionBlanc, (m_page == 6), 0.3);
        if(m_page == 6){
            drawPage6();
        };
        
        /*drawButtonOption(m_button_p7, m_imgOptionBlanc, (m_page == 7), 0.3);
        if(m_page == 7){
            drawPage7();
        };*/
    }
    
    if(!m_select_widget.m_close){
        m_select_widget.draw();
    }
}

int OptionWidget::onMouse(int x, int y){
    
    if(m_button_return.isActive(x,y)){
        close();
    } else if(m_button_p1.isActive(x,y)){
        m_page = 1;
    } else if(m_button_p2.isActive(x,y)){
        m_page = 2;
    } else if(m_button_p3.isActive(x,y)){
        m_page = 3;
    } else if(m_button_p4.isActive(x,y)){
        if(Framework::Instance().m_config.isTechnicien()){
            m_page = 4;
        }
    } else if(m_button_p5.isActive(x,y)){
        if(Framework::Instance().m_config.isDeveloppeur()){
            m_page = 5;
        }
    } else if(m_button_p6.isActive(x,y)){
        if(Framework::Instance().m_config.isDeveloppeur()){
            m_page = 6;
        }
    } else if(m_button_p7.isActive(x,y)){
        if(Framework::Instance().m_config.isDeveloppeur()){
            //m_page = 7;
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
    y+= m_y_inter;
    m_langage.setResize(m_part_1_x+m_part_1_w/2, y, Langage::getKey("OPT_LANGAGE"), true, m_part_1_w/2);
    m_langage.clear();
    m_langage.addValue(Langage::getKey("FR"));
    m_langage.addValue(Langage::getKey("EN"));
    m_langage.addValue(Langage::getKey("DE"));
    m_langage.addValue(Langage::getKey("NL"));
    
    y+= m_y_inter;
    y+= m_y_inter;
    y+= m_y_inter;
    m_unity.setResize(m_part_1_x+m_part_1_w/2, y, Langage::getKey("OPT_UNITY"), true, m_part_1_w/2);
    m_unity.clear();
    m_unity.addValue(Langage::getKey("METRIQUE"));
    m_unity.addValue(Langage::getKey("IMPERIAL"));
};

void OptionWidget::drawPage1(){
    Framework & f = Framework::Instance();
    Config & config = f.m_config;
    
    
    drawText(Langage::getKey("INFOS_AV_TITLE"), 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
    
    drawPart1Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, Langage::getKey("OPT_LANGAGE"));
    drawPart1Title(m_unity.m_y-2*m_y_inter, m_y_inter*3, Langage::getKey("OPT_UNITY"));
    
    if(m_select_widget.m_close){
        m_langage.setValueString(Langage::getKey(config.m_langage));
    }
    drawButtonLabel2(m_langage.m_buttonOpen);
    
    if(m_select_widget.m_close){
        m_unity.setValueString(Langage::getKey("METRIQUE"));
    }
    drawButtonLabel2(m_unity.m_buttonOpen);
    
    
    int y = m_y_begin+m_y_inter;
    drawPart2Title(m_langage.m_y-2*m_y_inter, y, Langage::getKey("VERSION"));
    y+= m_y_inter;
    drawText(ProjectVersion, m_part_2_m, y, sizeText_medium, true);
    y+= m_y_inter;
    drawText(f.m_config.m_version_selected, m_part_2_m, y, sizeText_medium, true);
    
}

void OptionWidget::onMousePage1(int x, int y){
    Framework & f = Framework::Instance();
    Config & config = f.m_config;
    if(!m_select_widget.m_close){
        if(m_select_widget.onMouseSelect(x, y)){
            std::string s = m_select_widget.m_selectButton->getValueString();
            if(s == Langage::getKey("FR")){
                config.m_langage = "FR";
                f.initOrLoadConfig();
            } else if(s == Langage::getKey("EN")){
                config.m_langage = "EN";
                f.initOrLoadConfig();
            } else if(s == Langage::getKey("DE")){
                config.m_langage = "DE";
                f.initOrLoadConfig();
            } else if(s == Langage::getKey("NL")){
                config.m_langage = "NL";
                f.initOrLoadConfig();
            }
            MainWidget::instancePtr()->setSize(m_width, m_height);
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
    y+= m_y_inter;
    m_update_bineuse.setResizeStd(m_part_1_m, y, Langage::getKey("UPDATE_BINEUSE_WIFI"), true, m_part_1_w/2);
    m_update_bineuse_usb.setResizeStd(m_part_2_m, y, Langage::getKey("UPDATE_BINEUSE_USB"), true, m_part_1_w/2);
    y+= m_y_inter;
    m_update_gps.setResizeStd(m_part_1_m, y, Langage::getKey("UPDATE_GPS_WIFI"), true, m_part_1_w/2);
    y+= m_y_inter;
    m_serial.setResizeStd(m_part_1_m, y, Langage::getKey("UPDATE_SERIAL_WIFI"), true, m_part_1_w/2);
    y+= m_y_inter;
    m_update_robot.setResizeStd(m_part_1_m, y, Langage::getKey("UPDATE_ROBOT"), true, m_part_1_w/2);
    y+= m_y_inter;
    
    m_file_widget.setSize(m_width, m_height);
};

void OptionWidget::drawPage2(){
    Framework & f = Framework::Instance();
    drawText(Langage::getKey("UPDATE"), 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
    
    if(f.m_config.m_update_wifi){
        drawPart1Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, Langage::getKey("UPDATE_WIFI"));
        
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
    if(f.m_config.m_update_usb){
        drawPart2Title(m_langage.m_y-2*m_y_inter, m_y_inter*3, Langage::getKey("UPDATE_USB"));
        
        drawButtonLabel2(m_update_bineuse_usb);
    }
    
    if(!m_file_widget.m_close){
        m_file_widget.draw();
    }
}

void OptionWidget::onMousePage2(int x, int y){
    Framework & f = Framework::Instance();
    if(f.m_config.m_update_wifi){
        if(m_update_bineuse.isActive(x, y)){
            if(f.m_config.m_code_source){
                std::string opt = f.m_config.m_version_selected;
                std::string cmd = "sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/bineuse_src_update_wifi.sh " + opt;
                call(cmd);
            } else {
                std::string opt = f.m_config.m_version_selected;
                std::string cmd = "sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/bineuse_update_wifi.sh " + opt;
                call(cmd);
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
    
    
    if(f.m_config.m_update_usb){
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
    int x = m_width2/2;
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
    
    y = y_begin + 2*inter;
    m_button0.setResizeStd(x, y, "0", true, 2*rayon, 2*rayon);
}

void OptionWidget::myDrawButton(ButtonGui * b, QString s){
    drawButtonLabel2(*b, COLOR_WHITE);
}

void OptionWidget::drawPage3(){
    drawText(Langage::getKey("INFOS_AV_TITLE"), 0.45*m_width, m_y_title, sizeText_bigbig, true);
    
    myDrawButton(&m_button0, "0");
    myDrawButton(&m_button1, "1");
    myDrawButton(&m_button2, "2");
    myDrawButton(&m_button3, "3");
    myDrawButton(&m_button4, "4");
    myDrawButton(&m_button5, "5");
    myDrawButton(&m_button6, "6");
    myDrawButton(&m_button7, "7");
    myDrawButton(&m_button8, "8");
    myDrawButton(&m_button9, "9");
}

int i_technicien = 0;
int i_avance = 0;
void OptionWidget::onMousePage3(int x, int y){
    Framework & f = Framework::Instance();
    if(i_avance == 0 && m_button6.isActive(x, y)){
        i_avance = 1;
    } else if(i_avance == 1 && m_button1.isActive(x, y)){
        i_avance = 2;
    } else if(i_avance == 2 && m_button5.isActive(x, y)){
        i_avance = 3;
    } else if(i_avance == 3 && m_button5.isActive(x, y)){
        f.m_config.m_user_mode = 2;
    } else if(i_technicien == 0 && m_button0.isActive(x, y)){
        i_technicien = 1;
    } else if(i_technicien == 1 && m_button0.isActive(x, y)){
        i_technicien = 2;
    } else if(i_technicien == 2 && m_button0.isActive(x, y)){
        i_technicien = 3;
    } else if(i_technicien == 3 && m_button0.isActive(x, y)){
        f.m_config.m_user_mode = 1;
    } else {
        i_technicien = 0;
        i_avance = 0;
    }
    //INFO(i_technicien << " " << i_avance << " " << f.m_config.m_user_mode);
}



/**
 PAGE 4
 */



void OptionWidget::setSizePage4(){
    int y = m_y_begin;
    m_button_update_wifi.setResize(m_part_1_x2, y, m_petit_button);
    y += m_y_inter;
    m_button_update_usb.setResize(m_part_1_x2, y, m_petit_button);
    y += m_y_inter;
    m_button_remote.setResize(m_part_1_x2, y, m_petit_button);
    y+= m_y_inter;
    y+= m_y_inter;
    m_send_images.setResizeStd(m_part_1_m, y, Langage::getKey("SEND_IMAGES"), true, m_part_1_w/2);
    y+= m_y_inter;
    y+= m_y_inter;
    
    y = m_y_begin;
    m_update_lemca.setResizeStd(m_part_2_m, y, Langage::getKey("UPDATE_OS"), true, m_part_1_w/2);
    y+= m_y_inter;
    m_update_deps.setResizeStd(m_part_2_m, y, Langage::getKey("UPDATE_DEPS"), true, m_part_1_w/2);
    y+= m_y_inter;
    m_update_acces_dist.setResizeStd(m_part_2_m, y, Langage::getKey("UPDATE_ACCES_DIST"), true, m_part_1_w/2);
    y+= m_y_inter;
    y+= m_y_inter;
   
    m_version_selected.setResize(m_part_2_x+m_part_1_w/2, y, "Version", true, m_part_1_w/2);
    m_version_selected.clear();
    m_version_selected.addValue(("test"));
    m_version_selected.addValue(("prod"));
    m_version_selected.addValue(("v_22_09"));
    m_version_selected.addValue(("v_22_03"));
};

void OptionWidget::drawPage4(){
    Framework & f = Framework::Instance();
    
    drawText(Langage::getKey("INFOS_OPTIONS"), 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
    drawPart1Title(m_button_update_wifi.m_y-2*m_y_inter, 0, Langage::getKey("OPTIONS"), false);
    drawButtonCheck(m_button_update_wifi, f.m_config.m_update_wifi, Langage::getKey("UPDATE_WIFI_ENABLE"));
    drawButtonCheck(m_button_update_usb, f.m_config.m_update_usb, Langage::getKey("UPDATE_USB_ENABLE"));
    drawButtonCheck(m_button_remote, f.m_config.m_remote, Langage::getKey("REMOTE_ENABLE"));
    
    
    drawPart1Title(m_send_images.m_y-m_y_inter, 0, "", true);
    drawButtonLabel2(m_send_images);
    
    int y = m_send_images.m_y + 2*m_y_inter;
    drawPart1Title(y-m_y_inter, 0, "", true);
    if(m_qt_network->m_cam1_connected){
        m_painter->setPen(Qt::darkGreen);
    } else {
        m_painter->setPen(Qt::red);
    }
    drawText("CAM1", m_part_1_x+m_part_1_w*0.4, y, sizeText_medium, true);
    
    if(m_qt_network->m_cam2_connected){
        m_painter->setPen(Qt::darkGreen);
    } else {
        m_painter->setPen(Qt::red);
    }
    drawText("CAM2", m_part_1_x+m_part_1_w*0.6, y, sizeText_medium, true);
    
    
    drawPart2Title(m_y_begin-2*m_y_inter, 0, Langage::getKey("OPERATING_SYSTEM"));
    drawButtonLabel2(m_update_lemca);
    drawButtonLabel2(m_update_deps);
    drawButtonLabel2(m_update_acces_dist);
    
    drawPart2Title(m_version_selected.m_y-m_y_inter, 0, "", true);
    if(m_select_widget.m_close){
        m_version_selected.setValueString(f.m_config.m_version_selected);
    }
    drawButtonLabel2(m_version_selected.m_buttonOpen);
    
    
    
    
}

void OptionWidget::onMousePage4(int x, int y){
    Framework & f = Framework::Instance();
    
    if(m_button_update_wifi.isActive(x, y)){
        f.m_config.m_update_wifi = !f.m_config.m_update_wifi;
        f.initOrLoadConfig();
    }
    if(m_button_update_usb.isActive(x, y)){
        f.m_config.m_update_usb = !f.m_config.m_update_usb;
        f.initOrLoadConfig();
    }
    if(m_button_remote.isActive(x, y)){
        f.m_config.m_remote = !f.m_config.m_remote;
        f.initOrLoadConfig();
    }
    
    if(m_update_lemca.isActive(x, y)){
        call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/lemca_update_wifi.sh");
    }
    if(m_update_deps.isActive(x, y)){
        call("echo lemca | su -c \"sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/install_dep.sh\"");
    }
    if(m_update_acces_dist.isActive(x, y)){
        call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/install_acces_dist.sh");
        
    }
    if(m_send_images.isActive(x, y)){
        call("sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/send_images.sh");
    }
    
    //m_version_selected
    if(!m_select_widget.m_close){
        if(m_select_widget.onMouseSelect(x, y)){
            f.m_config.m_version_selected = m_version_selected.getValueString();
            f.initOrLoadConfig();
        }
       
        return;
    }
    
    if(m_version_selected.m_buttonOpen.isActive(x, y)){
        m_select_widget.open();
        m_select_widget.setValueGuiKeyPad(&m_version_selected);
    }
}

/**
 PAGE 5
 */

void OptionWidget::setSizePage5(){
    
    int y = m_y_begin;
    m_button_code_source.setResize(m_part_1_x2, y, m_petit_button);
    y += m_y_inter;
    m_make_archive.setResizeStd(m_part_1_m, y, "Make archive", true, m_part_1_w/2);
    
    y += m_y_inter;
    y += m_y_inter;
    m_button_full_screen.setResize(m_part_1_x2, y, m_petit_button);
    y += m_y_inter;
    m_quit_full_screen.setResizeStd(m_part_1_m, y, "Minimized", true, m_part_1_w/2);
    
    y += m_y_inter;
    y += m_y_inter;
    m_clear_data.setResizeStd(m_part_1_m, y, "Clear Data", true, m_part_1_w/2);
    y += m_y_inter;
    m_run_cmd.setResizeStd(m_part_1_m, y, "Run cmd", true, m_part_1_w/2);
    
    y = m_y_begin;
    m_cam1.setResize(m_part_2_x2, y, "Refresh", m_gros_button);
    y += m_y_inter;
    m_cam2.setResize(m_part_2_x2, y, "Refresh", m_gros_button);
    y += m_y_inter;
    m_reseau.setResizeStd(m_part_2_m, y, "Reseau", true, m_part_1_w/2);
    
    y += m_y_inter;
    m_ping.setResizeStd(m_part_2_m, y, "Ping", true, m_part_1_w/2);
    y += m_y_inter;
    y += m_y_inter;
    m_constructor.setResize(m_part_2_x+m_part_1_w/2, y, "Constructor", true, m_part_1_w/2);
    m_constructor.clear();
    m_constructor.addValue(("0. Lemca"));
    m_constructor.addValue(("1. Marechalle"));
    m_constructor.addValue(("2. Vanhouke"));
    m_constructor.addValue(("3. Binnove"));
    
}



void OptionWidget::drawPage5(){
    Framework & f = Framework::Instance();
    drawText("Developper", 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
    
    drawPart1Title(m_y_begin-2*m_y_inter, 0, "Source");
    drawButtonCheck(m_button_code_source, f.m_config.m_code_source, "code source");
    m_make_archive.m_label = "Make archive - "+QString::fromStdString(f.m_config.m_version_selected);
    if(f.m_config.m_code_source){
        drawButtonLabel2(m_make_archive);
    }
    
    drawPart1Title(m_button_full_screen.m_y-m_y_inter, 0, "", true);
    drawButtonCheck(m_button_full_screen, f.m_config.m_fullscreen, "full screen");
    drawButtonLabel2(m_quit_full_screen);
    
    
    drawPart1Title(m_clear_data.m_y-m_y_inter, 0, "", true);
    drawButtonLabel2(m_run_cmd);
    drawButtonLabel2(m_clear_data);
    
    
    
    drawPart2Title(m_y_begin-2*m_y_inter, 0, "Caméras");
    
    int x = m_part_2_m;
    if(m_qt_network->m_cam1_connected){
        m_painter->setPen(Qt::darkGreen);
    } else {
        m_painter->setPen(Qt::red);
    }
    drawText("CAM1 - 192.168.1.30", x, m_cam1.m_y, sizeText_medium, true);
    drawButtonImage(m_cam1, m_imgOptionGris);
    
    if(m_qt_network->m_cam2_connected){
        m_painter->setPen(Qt::darkGreen);
    } else {
        m_painter->setPen(Qt::red);
    }
    drawText("CAM2 - 192.168.1.31", x, m_cam2.m_y, sizeText_medium, true);
    drawButtonImage(m_cam2, m_imgOptionGris);
    
    drawButtonLabel2(m_reseau);
    drawButtonLabel2(m_ping);
    
    //constructor
    drawPart2Title(m_constructor.m_y-m_y_inter, 0, "Constructeur", true);
    if(m_select_widget.m_close){
        m_constructor.setSelectedValue(f.m_config.m_constructor);
    }
    drawButtonLabel2(m_constructor.m_buttonOpen);
}

void OptionWidget::onMousePage5(int x, int y){
    KeyBoardWidget & key_board_widget = MainWidget::instancePtr()->m_key_board_widget;
    //Framework & f = Framework::Instance();
    if(!key_board_widget.m_close){
        if(key_board_widget.onMouse(x, y)){
            std::string s1 = key_board_widget.getText().toUtf8().constData();
            call(s1);
            close();
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
            INFO("m_make_archive");
            std::string opt = f.m_config.m_version_selected;
            std::string cmd = "sh " + DirectoryManager::Instance().getSourceDirectory() + "/src/sh/make_archive.sh " + opt;
            call(cmd);
        }
    }
    
    if(m_run_cmd.isActive(x, y)){
        key_board_widget.m_close = false;
    }
    
    if(m_quit_full_screen.isActive(x, y)){
        MainWindow::instancePtr()->quitFullScreen();
    }
    if(m_clear_data.isActive(x, y)){
        DirectoryManager::Instance().clearAll();
    }
    
    
    if(m_cam1.isActive(x, y)){
        MainWidget::instancePtr()->m_cmd_widget.m_enable_abort = true;
        openFirefox("onboard & firefox http://192.168.1.30;");
    }
    if(m_cam2.isActive(x, y)){
        MainWidget::instancePtr()->m_cmd_widget.m_enable_abort = true;
        openFirefox("onboard & firefox http://192.168.1.31;");
    }
    if(m_reseau.isActive(x, y)){
        MainWidget::instancePtr()->m_cmd_widget.m_enable_abort = true;
        call("nmap 192.168.1.0/24");
    }
    if(m_ping.isActive(x, y)){
        MainWidget::instancePtr()->m_cmd_widget.m_enable_abort = true;
        call("ping 192.168.1.30 -c 20 -i 0.2; ping 192.168.1.31 -c 20 -i 0.2;");
    }
    
    //constructor
    if(!m_select_widget.m_close){
        if(m_select_widget.onMouseSelect(x, y)){
            f.m_config.m_constructor = m_constructor.m_selectedValue;
            f.initOrLoadConfig();
        }
       
        return;
    }
    
    if(m_constructor.m_buttonOpen.isActive(x, y)){
        m_select_widget.open();
        m_select_widget.setValueGuiKeyPad(&m_constructor);
    }
}


/**
 PAGE 6
 */

void OptionWidget::setSizePage6(){
    int y = m_y_begin;
    m_button_robot.setResize(m_part_1_x2, y, m_petit_button);
    y+= m_y_inter;
    m_port.setResizeLabel(m_part_1_x3, y, "port label");
    m_port.setResize(m_part_1_x3, y, m_gros_button);
    y+= m_y_inter;
    m_auto_launch.setResize(m_part_1_x2, y, m_petit_button);
    
    y = m_y_begin;
    m_button_gps.setResize(m_part_2_x2, y, m_petit_button);
    y += m_y_inter;
    m_button_serial.setResize(m_part_2_x2, y, m_petit_button);
    y += m_y_inter;
    
};

void OptionWidget::drawPage6(){
    Framework & f = Framework::Instance();
    drawText("Robot", 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
    
    drawPart1Title(m_y_begin-2*m_y_inter, 0, "Robot");
    drawButtonCheck(m_button_robot, f.m_config.m_robot, "robot");
    
    m_port.m_value = f.m_config.m_port_remote;
    drawText("port label", m_part_1_x2,m_port.m_y, sizeText_medium);
    drawValueGuiKeyPad2(m_port);
    
    drawButtonCheck(m_auto_launch, f.m_config.m_auto_launch, "auto launch robot");
    
    
    drawPart2Title(m_y_begin-2*m_y_inter, 0, Langage::getKey("SOFTWARE"));
    drawButtonCheck(m_button_gps, f.m_config.m_gps, Langage::getKey("GPS"));
    drawButtonCheck(m_button_serial, f.m_config.m_serial, Langage::getKey("SERIAL"));
    
}

void OptionWidget::onMousePage6(int x, int y){
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
    if(m_button_robot.isActive(x, y)){
        f.m_config.m_robot += 1;
        f.m_config.m_robot = f.m_config.m_robot%2;
        f.initOrLoadConfig();
    }
    
    if(m_button_gps.isActive(x, y)){
        f.m_config.m_gps = !f.m_config.m_gps;
        f.initOrLoadConfig();
    }
    if(m_button_serial.isActive(x, y)){
        f.m_config.m_serial = !f.m_config.m_serial;
        f.initOrLoadConfig();
    }
}


/**
 PAGE 7
 */

void OptionWidget::setSizePage7(){
    
};

void OptionWidget::drawPage7(){
    drawText("Not used", 0.45*m_width, m_y_title, sizeText_bigbig, true);
    drawSeparateurH();
}

void OptionWidget::onMousePage7(int x, int y){
}

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>


void OptionWidget::call(const std::string & s){
    INFO("cmd " << s);
    
    Framework & f = Framework::Instance();
    //f.mutex.lock();
    //f.m_command_to_execute2 = s+" 2>&1";
    f.m_cmd_buffer.clear();
    f.m_cmd_buffer.push_back(s);
    f.m_cmd_end = false;
    f.m_cmd_abort = false;
    MainWindow::instancePtr()->m_process->start("/bin/bash", QStringList() << "-c" << QString::fromStdString(s));
    //f.bufferNotEmpty.wakeAll();
    //f.mutex.unlock();

    MainWidget::instancePtr()->m_cmd_widget.open();
}

void OptionWidget::openFirefox(const std::string & s){
    INFO("firefox");
    QProcess * p = new QProcess();
    p->start("/bin/bash", QStringList() << "-c" << QString::fromStdString(s));
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
