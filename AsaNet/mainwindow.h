#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AsaGlobal.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initLayout();
    void initConnect();

    QFrame * frame = NULL;

    QVBoxLayout * vLayout = NULL;
    QHBoxLayout * hLayout = NULL;

    QPushButton * btnStart = NULL;
    QPushButton * btnUrlLabel = NULL;

    QTextEdit * editText = NULL;

    QLineEdit * editUrl = NULL;

    void loopExec(int mec);

public slots:
    void slotBtnStartClick();
    QString slotGetInfo(QString strUrl);
};

#endif // MAINWINDOW_H
