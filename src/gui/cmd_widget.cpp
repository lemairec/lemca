#include "cmd_widget.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"

#define PETIT_RAYON2 0.025

CmdWidget::CmdWidget(){
    //m_imgClose = loadImage("/gui/ok.png");
}

void CmdWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_button_close.setResizeStd(0.6*m_width, 0.9*m_height, "OK", true);
    m_button_interrupt.setResizeStd(0.4*m_width, 0.9*m_height, "CANCEL", true);
};



void CmdWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushGray);
    m_painter->drawRect(0, 0, m_width, m_height);
    
    m_painter->setBrush(m_brushWhite);
    m_painter->drawRect(m_width*0.05, m_height*0.1, m_width*0.9, m_height*0.7);
    
    int inter = 18;
    int x = m_width*0.08;
    int y = m_height*0.8-inter;
    Framework & f = Framework::Instance();
    for(size_t i = 0; i < f.m_cmd_buffer.size(); ++i){
        std::string s = f.m_cmd_buffer[f.m_cmd_buffer.size()-i-1];
        drawText(s, x, y);
        y-= inter;
        if(y<m_height*0.1){
            break;
        }
    }
    if(f.m_cmd_end){
        if(f.m_cmd_return == 0){
            drawButtonLabel2(m_button_close, COLOR_VALIDATE);
        } else {
            drawButtonLabel2(m_button_close, COLOR_RED);
        }
    }
    drawButtonLabel2(m_button_interrupt, COLOR_OTHER);
}

int CmdWidget::onMouse(int x, int y){
    Framework & f = Framework::Instance();
    INFO("onmouse");
    if(f.m_cmd_end){
        if(m_button_close.isActive(x, y)){
            Framework & f = Framework::Instance();
            if(f.m_cmd_end){
                m_close = true;
            }
        }
    }
    if(m_button_interrupt.isActive(x, y)){
        std::string s = "kill " + std::to_string(f.m_cmd_pid);
        f.m_cmd_buffer.push_back("****");
        f.m_cmd_buffer.push_back(s);
        f.m_cmd_buffer.push_back("****");
        system(s.c_str());
        //kill(f.m_cmd_process);
    }
    return 0;
    
}

void CmdWidget::open(){
    m_close = false;
    m_button_ok = false;
}
