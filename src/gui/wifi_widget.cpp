#include "option_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"

#define PETIT_RAYON2 0.025

WifiWidget::WifiWidget()
:m_qt_network(MyQTNetwork::Instance_ptr())
{
    m_black_mode = false;
    m_img_return = loadImageInv("/gui/return.png");
}

void WifiWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_y2 = m_height*0.04;
    m_x2 = m_y2;
    m_width2 = m_width-2*m_y2-m_gros_button*2.4;
    m_height2 = m_height-2*m_y2;

    m_select_widget.setSize(width, height);
    
    
    
    //m_select_serial
    int x = 0.55*m_width;
    int y = 0.35*m_height;
    int inter = 0.1*m_height;
     y+=1.5*inter;
    m_select_wifi.setResize(x, y, "Wifi", true, width/4);
    y+=inter;
    m_password.setResize(x, y);
    y+=1.5*inter;
    m_connect.setResizeStd(0.5*m_width, y, "Connection", true, width/4);
    y+=inter;
    
    
    int x_right = width-m_gros_button*1.2;
    m_button_close.setResize(x_right, m_height-m_gros_button*1.2, m_gros_button);
};


std::string m_reseau;

void WifiWidget::draw(){
    
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_x2, m_y2, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    drawButtonImageCarre(m_button_close, m_img_return, 0.9, false);
    
    auto now = std::chrono::system_clock::now();
    int tick_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now-m_time_open).count();
    
    
    if(tick_ms < 4000){
        drawQText("Recherche des reseaux wifis     " + QString::number((tick_ms/1000)+1) + "/4", 0.25*m_width, 0.35*m_height, sizeText_big, false);

        return;
    }
    
    if(!m_select_widget.m_close){
        m_select_widget.draw();
        return;
    }
    
    drawButtonLabel2(m_connect);
    if(m_qt_network->m_is_connected){
        m_painter->setPen(Qt::darkGreen);
        drawText("Connecté à internet", 0.35*m_width, 0.35*m_height, sizeText_big);
    } else {
        m_painter->setPen(Qt::red);
        drawText("Non connecté à internet", 0.35*m_width, 0.35*m_height, sizeText_big);
    }

    m_painter->setPen(m_pen_black);
    //Framework & f = Framework::Instance();
    drawText("Wifi", 0.5*m_width, 0.2*m_height, sizeText_big);
    
    drawText("Reseau", 0.25*m_width, m_select_wifi.m_y, sizeText_big);
    drawButtonLabel2(m_select_wifi.m_buttonOpen);
    
    if(m_select_widget.m_close){
        m_select_wifi.setValueString(m_reseau);
    }
    
    m_painter->setPen(m_pen_black);
    drawText("Password", 0.25*m_width, m_password.m_y, sizeText_big);
    drawValueGuiKeyBoard(m_password);
    
    
}

int WifiWidget::onMouse(int x, int y){
    KeyBoardWidget & key_board_widget = MainWidget::instancePtr()->m_key_board_widget;
    //Framework & f = Framework::Instance();
    if(!key_board_widget.m_close){
        key_board_widget.onMouse(x, y);
        std::string password = key_board_widget.getText().toUtf8().constData();
        m_password.m_text = password;
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
            std::string cmd = "nmcli dev wifi connect \""+ m_reseau + "\"";
            if(m_password.m_text.size()>0){
                cmd = cmd + " password " + m_password.m_text;
            }
    
            call2(cmd);
            //nmcli dev wifi connect <mySSID> password <myPassword>
            //key_board_widget.m_close = false;
        }
        if(m_button_close.isActive(x, y)){
            m_close = true;
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
        //if(onMouseSelectButton(m_select_wifi, x, y)){
            //config.m_serial.setValue(QString::fromStdString(m_select_serial.getValueString()));
            //loadConfig();
        //}
        
    }
    
    return 0;
    
    
}

void WifiWidget::call2(const std::string & s){
    MainWindow::instancePtr()->call(s);
    m_close = true;
    MainWidget::instancePtr()->m_cmd_widget.open();
}


void WifiWidget::open(){
    addWifis();
    m_time_open = std::chrono::system_clock::now();
    m_qt_network->test();
    m_close = false;
}
void WifiWidget::call(const std::string & s){
    INFO("call " << s);
    system(s.c_str());
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

#include <sstream>      // std::stringstream
void WifiWidget::addWifis(){
    m_select_wifi.clear();
    INFO("addWifis");
    {
        std::string res = execute2("nmcli -f SSID dev wifi");
        std::vector<std::string> strs;
        std::stringstream ss(res);
        std::string item;
        std::vector<std::string> elems;
        while (std::getline(ss, item, '\n')) {
            if(!item.empty()){
                INFO(item);
                if(item.find("SSID") == std::string::npos){
                    std::string s = item;
                    
                    m_select_wifi.addValue(trim(s));
                }
            }
        }
        
    }
}
