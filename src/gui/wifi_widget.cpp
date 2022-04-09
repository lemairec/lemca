#include "option_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"

#define PETIT_RAYON2 0.025

WifiWidget::WifiWidget(){
    m_imgClose = loadImage("/gui/ok.png");
}

void WifiWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_select_widget.setSize(width, height);
    
    m_button_close.setResize(0.75*m_width, 0.83*m_height, m_gros_button);
    m_connect.setResizeStd(0.25*m_width, 0.83*m_height, "connect");
    
    //m_select_serial
    int x = 0.5*m_width;
    int y = 0.4*m_height;
    int inter = 0.1*m_height;
    
    m_select_wifi.setResize(x, y, "Wifi", true, width/4);
    y+=inter;
    m_password.setResize(x, y);

};

std::string m_reseau;

void WifiWidget::draw(){
    
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.8);
    
    if(!m_select_widget.m_close){
        m_select_widget.draw();
        return;
    }
    
    drawButtonImage(m_button_close, m_imgClose);
    drawButtonLabel2(m_connect);

    //Framework & f = Framework::Instance();
    drawText("Wifi", 0.5*m_width, 0.2*m_height, sizeText_big);
    
    drawText("Reseau", 0.25*m_width, m_select_wifi.m_y, sizeText_big);
    drawButtonLabel2(m_select_wifi.m_buttonOpen);
    
    if(m_select_widget.m_close){
        m_select_wifi.setValueString(m_reseau);
    }
    
    drawText("Password", 0.25*m_width, m_password.m_y, sizeText_big);
    drawValueGuiKeyBoard(m_password);
        
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
            m_close = true;
        }
        //if(onMouseSelectButton(m_select_wifi, x, y)){
            //config.m_serial.setValue(QString::fromStdString(m_select_serial.getValueString()));
            //loadConfig();
        //}
        
    }
    
    if(!m_select_widget.m_close){
        if(m_select_widget.onMouseSelect(x, y)){
            m_reseau = m_select_widget.m_selectButton->getValueString();
        }
       
        return 0;
    }
    
    if(m_select_wifi.m_buttonOpen.isActive(x, y)){
        m_select_widget.open();
        m_select_widget.setValueGuiKeyPad(&m_select_wifi);
    }
    return 0;
    
}




void WifiWidget::open(){
    addWifis();
    m_close = false;
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
