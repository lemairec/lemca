#include "file_widget.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"
#include <boost/algorithm/string.hpp>

#define PETIT_RAYON2 0.025

FileWidget::FileWidget(){
    //m_imgClose = loadImage("/gui/ok.png");
    //open();
}

void FileWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    m_button_close.setResizeStd(0.5*m_width, 0.9*m_height, "OK", true);
    m_select_widget.setSize(width, height);
    
};

void FileWidget::draw(){
    m_painter->setPen(m_penBlack);
    m_painter->setBrush(m_brushGray);
    m_painter->drawRect(0, 0, m_width, m_height);
    m_select_widget.draw();
    /*
    drawButtonLabel2(m_connect);

    //
    drawText("Wifi", 0.5*m_width, 0.2*m_height, sizeText_big);
    
    //drawSelectButtonGuiClose(m_select_wifi);
    
    drawValueGuiKeyBoard(m_password);
    
    //drawSelectButtonGuiOpen(m_select_wifi);*/
        
}

int FileWidget::onMouse(int x, int y){
    if(m_select_widget.onMouseSelect(x, y)){
        m_close = true;
        return 1;
    };
    return 0;
    
}

void FileWidget::open(){
    m_close = false;
    m_select_widget.setValueGuiKeyPad(&m_select_files);
    std::string res = execute2("ls /media/lemca/");
    std::vector<std::string> strs;
    boost::split(strs, res, boost::is_any_of("\n"));
    m_select_files.clear();
    for(auto s : strs){
        if(!s.empty()){
            INFO(s);
            m_select_files.addValue(s);
        }
    }
}
