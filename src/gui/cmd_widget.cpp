#include "cmd_widget.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"
#include "../config/langage.hpp"

#define PETIT_RAYON2 0.025

CmdWidget::CmdWidget(){
    //m_imgClose = loadImage("/gui/ok.png");
}

void CmdWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_button_close.setResizeStd(0.5*m_width, 0.9*m_height, Langage::getKey("OK"), true);

};

void CmdWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushGray);
    m_painter->drawRect(0, 0, m_width, m_height);
    
    
    Framework & f = Framework::Instance();
    bool debug = f.m_config.isTechnicien();
    
    if(debug){
        m_painter->setBrush(m_brushWhite);
        m_painter->drawRoundedRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.7, 15, 15);
        
        int inter = 18;
        int x = m_width*0.08;
        int y = m_height*0.8-inter;
        for(size_t i = 0; i < f.m_cmd_buffer.size(); ++i){
            std::string s = f.m_cmd_buffer[f.m_cmd_buffer.size()-i-1];
            drawText(s, x, y);
            y-= inter;
            if(y<m_height*0.1){
                break;
            }
        }
    }
    
    double perc = f.m_cmd_buffer.size()/100.0;
    
    bool good = true;
    if(f.m_cmd_end){
        if(f.m_cmd_return != 0){
            good = false;
        }
        perc = 1.0;
    } else {
        if(perc > 0.99){
            perc = 0.99;
        }
    }
    
    int y = m_height*0.45;
    int h = m_height*0.1;
    if(debug){
        y = m_height*0.84;
        h = m_height*0.02;
    }
    
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRoundedRect(m_width*0.05, y-h/2, m_width*0.9, h, 5, 5);
    if(good){
        m_painter->setBrush(m_brushGreenButton);
    } else {
        m_painter->setBrush(m_brushRedButton);
    }
    m_painter->drawRoundedRect(m_width*0.05, y-h/2, perc*m_width*0.9, h, 5, 5);
    if(good){
        QString s = QString::number(std::round(perc*100))+ " %";
        drawQText(s, m_width*0.5, y, sizeText_medium, true);
    } else {
        drawText(Langage::getKey("FAIL"), m_width*0.5, y, sizeText_medium, true);
    }
    
    if(f.m_cmd_end){
        if(f.m_cmd_return == 0){
            m_button_close.m_label = QString::fromStdString(Langage::getKey("OK"));
            drawButtonLabel2(m_button_close, COLOR_VALIDATE);
        } else {
            m_button_close.m_label = QString::fromStdString(Langage::getKey("CANCEL"));
            drawButtonLabel2(m_button_close, COLOR_FAIL);
        }
    }
    /*
    drawButtonLabel2(m_connect);

    //
    drawText("Wifi", 0.5*m_width, 0.2*m_height, sizeText_big);
    
    //drawSelectButtonGuiClose(m_select_wifi);
    
    drawValueGuiKeyBoard(m_password);
    
    //drawSelectButtonGuiOpen(m_select_wifi);*/
        
}

int CmdWidget::onMouse(int x, int y){
    if(m_button_close.isActive(x, y)){
        Framework & f = Framework::Instance();
        if(f.m_cmd_end){
            m_close = true;
        }
    }
    return 0;
    
}

void CmdWidget::open(){
    m_close = false;
    m_button_ok = false;
}
