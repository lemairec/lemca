#include "include_qt.hpp"
#include "../main_widget.hpp"
#include "../../util/log.hpp"

#include <QProcess>

class MyWidget : public QWidget
{
public:
    MainWidget * m_main_widget = NULL;
    MyWidget( QWidget *parent = 0 ) : QWidget( parent ) {}

    void paintEvent(QPaintEvent* e);
};

class MainWindow : public QMainWindow
{
    MainWidget * m_main_widget;
    QTimer *m_timer;
    Q_OBJECT
    
    QWidget *centralWidget;
    explicit MainWindow(QWidget *parent = 0);
    
public:
    static MainWindow * instancePtr();
    MyWidget * m_my_widget;
    
    ~MainWindow();
    
    void test();
    void resizeEvent(QResizeEvent* event);

protected:
    void setupUi();
    void onNewPoint();
    void creerMenu();

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent ( QMouseEvent * event );
signals:
    void onValueChangeSignal();

public slots:
    void onValueChangeSlot();
    void onTimerSlot();
    
    void openFile();
    void quitFullScreen();
    void rightMessage();
    void wrongMessage();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus = QProcess::NormalExit);
    
public:
    QProcess * m_process;
    void call(const std::string & s);
};
