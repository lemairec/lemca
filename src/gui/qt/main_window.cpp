#include "main_window.hpp"
#include "../option_widget.hpp"
#include "../../util/directory_manager.hpp"
#include "../../framework.hpp"

#include <QGridLayout>
#include <QTabWidget>
#include <QStatusBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QResizeEvent>

#include <QTimer>
#include <QFileDialog>
#include "environnement.hpp"

void MyWidget::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e); // effectue le comportement standard

    QPainter painter(this); // construire
    //painter.setRenderHint(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if(m_main_widget){
        m_main_widget->setPainter(&painter);
        m_main_widget->draw();
    }
}




MainWindow * MainWindow::instancePtr(){
    static MainWindow gf;
    return &gf;
}

MainWindow::MainWindow(QWidget *parent)
:QMainWindow(parent)
{
    DEBUG("begin");
    m_timer = new QTimer(this);
    m_timer->start(200);
    
    m_process = new QProcess();
    
    
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerSlot()));
    connect(this, SIGNAL(onValueChangeSignal()), this, SLOT(onValueChangeSlot()));
    
    connect(m_process, SIGNAL(readyReadStandardOutput()),this, SLOT(rightMessage()) );
    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(wrongMessage()) );
    connect(m_process,SIGNAL(finished(int, QProcess::ExitStatus)),this,SLOT(processFinished(int, QProcess::ExitStatus)));
    m_process->start("/bin/bash", QStringList() << "-c" << QString("ls -la"));
    
    setupUi();
    DEBUG("end");
    
}

MainWindow::~MainWindow()
{
    //GpsFramework::Instance().removeObserver();
}

void MainWindow::setupUi(){
    DEBUG("begin");
    if (this->objectName().isEmpty()){
        this->setObjectName(QString::fromUtf8("MainWindow"));
    }
    //this->resize(800, 480);
    this->resize(1400, 800);
    
    m_my_widget = new MyWidget();
    m_main_widget = MainWidget::instancePtr();
    m_my_widget->m_main_widget = m_main_widget;
    m_my_widget->m_main_widget->setSize(800, 480);
    

    //m_my_widget->setupUi();
    this->setCentralWidget(m_my_widget);
    
    
    Framework & f = Framework::Instance();
    if(f.m_config.m_fullscreen){
        showFullScreen();
    }
    
    
    //showMaximized();
    DEBUG("end");
}

void MainWindow::quitFullScreen(){
    showMinimized();
}

//debug
//m_view->scene->setSceneRect(0, 0, width-10, height-10);
void MainWindow::resizeEvent(QResizeEvent *event){
    DEBUG("begin");
    int width = event->size().width();
    int height = event->size().height();
    m_main_widget->setSize(width, height);
    //m_gpsWidget->resizeEvent(event);
    DEBUG("end");
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(!m_my_widget->m_main_widget->m_key_board_widget.m_close){
        if(event->key() == Qt::Key_Backspace){
            m_my_widget->m_main_widget->m_key_board_widget.removeLetter();
        } else{
            INFO("tata " << event->key());
            m_my_widget->m_main_widget->m_key_board_widget.addLetter(event->text());
        }
    } else {
        if(event->key() == Qt::Key_Escape){
            exit(1);
        } else if(event->key() == Qt::Key_Q){
            exit(1);
        }
    }
}

void MainWindow::mousePressEvent ( QMouseEvent * event ){
    int x = event->x();
    int y = event->y();
    
    INFO("mousePressEvent " << x << " " << y);
    if(m_my_widget){
        if(m_my_widget->m_main_widget){
            m_my_widget->m_main_widget->onMouse(x, y);
        }else {
            INFO("not m_main_widget")
        }
    } else {
        INFO("m_my_widget")
    }
}

void MainWindow::onNewPoint(){
    DEBUG("begin");
    onValueChangeSlot();
    DEBUG("end");
}

void MainWindow::onValueChangeSlot(){
    DEBUG("begin");
    //m_view->m_gpsWidget->draw();
    DEBUG("end");
}

void MainWindow::onTimerSlot(){
    DEBUG("begin");
    m_my_widget->update();
    //m_view->m_gpsWidget->draw();
    DEBUG("end");
}

void MainWindow::creerMenu()
{
    DEBUG("begin");
    QMenu *menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction("open File", this, SLOT(openFile()));
    DEBUG("end");
}

void MainWindow::openFile(){
    DEBUG("begin");
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Address Book"), QString::fromStdString(DirectoryManager::instance().getSourceDirectory())+QString("/gps_samples"),
                                                    tr("Gps files (*.ubx)"));
    
    /*GpsFramework & f = GpsFramework::Instance();
    f.m_config.m_file_gps = fileName.toUtf8().constData();
    f.m_config.m_input_gps = "file";
    f.initOrLoadConfig();
    DEBUG("end");*/
}

void MainWindow::rightMessage()
{
    QByteArray strdata = m_process->readAllStandardOutput();
    Framework & f = Framework::Instance();
    QString s = strdata.constData();
    INFO(s.toUtf8().constData());
    
    auto list = s.split("\n");
    for(auto l : list){
        if(!l.isEmpty()){
            f.m_cmd_buffer.push_back(l.toUtf8().constData());
        }
    }
}

// show wrong message
void MainWindow::wrongMessage()
{
    QByteArray strdata = m_process->readAllStandardError();
    Framework & f = Framework::Instance();
    QString s = strdata.constData();
    INFO("error " << s.toUtf8().constData());
    
    auto list = s.split("\n");
    for(auto l : list){
        if(!l.isEmpty()){
            f.m_cmd_buffer.push_back(l.toUtf8().constData());
        }
    }
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    INFO("finished");
    Framework & f = Framework::Instance();
    f.m_cmd_return = exitCode;
    f.m_cmd_end = true;
    f.m_is_f_call = false;
}


void MainWindow::call(const std::string & s){
    Framework & f = Framework::Instance();
    
    f.m_cmd_buffer.clear();
    f.m_cmd_buffer.push_back("MainWindow::call");
    f.m_cmd_buffer.push_back(s);
    f.m_cmd_end = false;
    f.m_cmd_abort = false;
    m_process->start("/bin/bash", QStringList() << "-c" << QString::fromStdString(s));
}
