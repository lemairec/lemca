#include "gui/qt/main_window.hpp"
#include <QApplication>
#include "framework.hpp"
#include <inttypes.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //consumer.wait();
    Framework & framework = Framework::Instance();
    //framework.test();
    MainWindow * m = MainWindow::instancePtr();
    DEBUG("init");
    framework.initOrLoadConfig();
    DEBUG("fin init");
    m->show();
    DEBUG("exec");
    
    return app.exec();
}

