#include "init_widget.hpp"

#include "main_widget.hpp"
#include "environnement.hpp"
#include "qt/main_window.hpp"

#include "../framework.hpp"
#include "../util/util.hpp"

#define PETIT_RAYON2 0.025

InitWidget::InitWidget()
{
    m_black_mode = false;
    m_img_return = loadImageInv("/gui/return.png");
}

void InitWidget::setSize(int width, int height){
    BaseWidget::setSize(width, height);
    
    m_y2 = m_height*0.04;
    m_x2 = m_y2;
    m_width2 = m_width-2*m_y2-m_gros_button*2.4;
    m_height2 = m_height-2*m_y2;
    
    int x = 0.55*m_width;
    int y = 0.65*m_height;
    int inter = 0.1*m_height;
    m_code_constructeur.setResize(x, y);
    y+=1.5*inter;

    m_button_ok.setResizeStd(0.25*m_width, 0.75*m_height, "OK");
    m_button_ignore.setResizeStd(0.75*m_width, 0.75*m_height, "IGNORE");
};

void InitWidget::draw(){
    KeyBoardWidget & key_board_widget = MainWidget::instancePtr()->m_key_board_widget;
    
   
    m_painter->setPen(m_pen_black);
    m_painter->setBrush(m_brush_white);
    m_painter->drawRoundedRect(m_x2, m_y2, m_width2, m_height2, RAYON_ROUNDED, RAYON_ROUNDED);
    
    int y = 0.15*m_height;
    int inter = 0.1*m_height;
    drawText("Premier démarrage", 0.25*m_width, y, sizeText_big);
    y+=inter*1.5;
    drawText("Veuillez saissir votre code constructeur", 0.25*m_width, y, sizeText_big);
    y+=inter;
    drawText(" - 000000 si vous n'etes pas constructeur", 0.25*m_width, y, sizeText_big);
    y+=inter;
    
    drawText("Code constructeur", 0.25*m_width, m_code_constructeur.m_y, sizeText_big);
    drawValueGuiKeyBoard(m_code_constructeur);
    
    drawButtonLabel2(m_button_ok);
    
    if(!key_board_widget.m_close){
        key_board_widget.draw();
    }
}

int InitWidget::onMouse(int x, int y){
    KeyBoardWidget & key_board_widget = MainWidget::instancePtr()->m_key_board_widget;
    //Framework & f = Framework::Instance();
    if(!key_board_widget.m_close){
        key_board_widget.onMouse(x, y);
        std::string password = key_board_widget.getText().toUtf8().constData();
        m_code_constructeur.m_text = password;
        if(key_board_widget.m_close){
            /*QString s2 = key_board_widget.m_res;
            s2 += "\r\n";
            std::string s = s2.toUtf8().constData();*/
            //f.sendMessages(s);
        }
    } else {
        if(isActiveValueGuiKeyBoard(m_code_constructeur, x, y)){
            key_board_widget.m_close = false;
        }
        
        if(m_button_ok.isActive(x, y)){
            Framework & f = Framework::Instance();
            if(m_code_constructeur.m_text == "000000"){
                f.m_config.m_constructor = 0;
            } else if(m_code_constructeur.m_text == "BIN273"){
                f.m_config.m_constructor = 3;
            } else if(m_code_constructeur.m_text == "MAR452"){
                f.m_config.m_constructor = 1;
            } else if(m_code_constructeur.m_text == "VAN613"){
                f.m_config.m_constructor = 2;
            }
            f.initOrLoadConfig();
        }
        
    }
    
    return 0;
    
    
}
