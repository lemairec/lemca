#include "option_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"

#define PETIT_RAYON2 0.025

WifiWidget::WifiWidget(){
    
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
    
    //m_close=false;
    //m_page =5;
    //addSerials();
}

void WifiWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_button_close.setResize(0.75*m_width, 0.83*m_height, m_gros_button);
    m_connect.setResize(0.25*m_width, 0.83*m_height, m_gros_button);
    m_connect.m_label = "connect";
    
    //m_select_serial
    int x = 0.5*m_width;
    int y = 0.4*m_height;
    int inter = 0.1*m_height;
    
    m_select_wifi.setResize(x, y, m_petit_button);
    y+=inter;
    m_password.setResize(x+60, y);

};

void WifiWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8);
    
    drawButtonImage(m_button_close, m_imgClose);
    drawButtonLabel2(m_connect);

    //Framework & f = Framework::Instance();
    drawText("Wifi", 0.5*m_width, 0.2*m_height, sizeText_big);
    
    //drawSelectButtonGuiClose(m_select_wifi);
    
    drawValueGuiKeyBoard(m_password);
    
    //drawSelectButtonGuiOpen(m_select_wifi);
        
}

int WifiWidget::onMouse(int x, int y){
    KeyBoardWidget & key_board_widget = MainWidget::instance()->m_key_board_widget;
    //Framework & f = Framework::Instance();
    if(!key_board_widget.m_close){
        key_board_widget.onMouse(x, y);
        m_password.m_text = key_board_widget.m_res.toUtf8().constData();
        if(key_board_widget.m_close){
            /*QString s2 = key_board_widget.m_res;
            s2 += "\r\n";
            std::string s = s2.toUtf8().constData();*/
            //f.sendMessages(s);
        }
    } else {
        if(isActiveValueGuiKeyBoard(m_password, x, y)){
            key_board_widget.m_close = false;
        }
        if(isActiveValueGuiKeyBoard(m_password, x, y)){
            key_board_widget.m_close = false;
        }
        if(m_connect.isActive(x, y)){
            //key_board_widget.m_close = false;
        }
        if(m_button_close.isActive(x, y)){
            m_close = false;
        }
        //if(onMouseSelectButton(m_select_wifi, x, y)){
            //config.m_serial.setValue(QString::fromStdString(m_select_serial.getValueString()));
            //loadConfig();
        //}
        
    }
    
    
}




void WifiWidget::open(){
    addWifis();
    m_close = false;
}

void WifiWidget::addSerials(){
    //Framework & f = Framework::Instance();
    
}

void WifiWidget::call(const std::string & s){
    INFO("call " << s);
    system(s.c_str());
}

#include <sstream>      // std::stringstream
void WifiWidget::addWifis(){
    m_select_wifi.clear();
    INFO("addWifis");
    {
        std::string res = execute2("nmcli -f SSID dev wifi");
        std::vector<std::string> strs;
        m_select_wifi.addValue("non");
        m_select_wifi.addValue("wif");
        std::stringstream ss(res);
        std::string item;
        std::vector<std::string> elems;
        while (std::getline(ss, item, '\n')) {
        if(!item.empty()){
            INFO(item);
            if(item != "SSID"){
                m_select_wifi.addValue(item);
            }
        }
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
        }
        
    }
}
