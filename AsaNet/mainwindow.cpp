#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initLayout();
    initConnect();
}

MainWindow::~MainWindow()
{
    if(btnStart != NULL)
    {
        btnStart->deleteLater();
    }

    if(btnUrlLabel != NULL)
    {
        btnUrlLabel->deleteLater();
    }

    if(vLayout != NULL)
    {
        vLayout->deleteLater();
    }

    if(hLayout != NULL)
    {
        hLayout->deleteLater();
    }

    if(editText != NULL)
    {
        editText->deleteLater();
    }

    if(frame != NULL)
    {
        frame->deleteLater();
    }
    if(editUrl != NULL)
    {
        editUrl->deleteLater();
    }
}

void MainWindow::initLayout()
{
    frame = new QFrame(this);
    frame->setFixedSize(ASA_NET_WINDOW_WID,ASA_NET_WINDOW_HEI);
    frame->setStyleSheet(ASA_NET_WINDOW_STYLESHEET);

    btnStart = new QPushButton(this);
    btnStart->setFixedSize(ASA_NET_BTN_START_WID,ASA_NET_BTN_START_HEI);
    btnStart->setStyleSheet(ASA_NET_BTN_START_STYLESHEET);
    btnStart->setText(ASA_NET_BTN_START_STRING);

    btnUrlLabel = new QPushButton(this);
    btnUrlLabel->setFixedSize(ASA_NET_BTN_URLLABEL_WID,ASA_NET_BTN_URLLABEL_HEI);
    btnUrlLabel->setStyleSheet(ASA_NET_BTN_URL_LABEL_STYLESHEET);
    btnUrlLabel->setText(ASA_NET_BTN_URL_LABEL_STRING);

    editText = new QTextEdit(this);
    editText->setFixedSize(ASA_NET_TEXT_WID,ASA_NET_TEXT_HEI);
    editText->setStyleSheet(ASA_NET_TEXT_STYLESHEET);
    editText->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{border:0px solid grey;");

    editUrl = new QLineEdit(this);
    editUrl->setFixedSize(ASA_NET_URL_WID,ASA_NET_URL_HEI);
    editUrl->setStyleSheet(ASA_NET_URL_STYLESHEET);

    hLayout = new QHBoxLayout(this);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);
    hLayout->addSpacing(10);
    hLayout->addWidget(btnUrlLabel);
    hLayout->addStretch();
    editUrl->setLayout(hLayout);

    vLayout = new QVBoxLayout(this);
    vLayout->setSpacing(0);
    vLayout->setMargin(0);
    vLayout->addSpacing(50);
    vLayout->addWidget(editUrl,0,Qt::AlignHCenter);
    vLayout->addWidget(editText,1,Qt::AlignHCenter);
    vLayout->addStretch();
    vLayout->addWidget(btnStart,2,Qt::AlignHCenter);
    vLayout->addStretch();

    frame->setLayout(vLayout);

    btnUrlLabel->raise();
    btnUrlLabel->show();

    setFixedSize(ASA_NET_WINDOW_WID,ASA_NET_WINDOW_HEI);
    setStyleSheet(ASA_NET_WINDOW_STYLESHEET);
}

void MainWindow::initConnect()
{
    connect(btnStart,&QPushButton::clicked,[=]{
        btnStart->setStyleSheet(ASA_NET_BTN_START_STYLESHEET_REVERSE);
        loopExec(ASA_BTN_VERSE_TIME);
        btnStart->setStyleSheet(ASA_NET_BTN_START_STYLESHEET);
        slotBtnStartClick();
    });
}

void MainWindow::loopExec(int mec)
{
    QTimer time;
    QEventLoop loop;
    connect(&time,&QTimer::timeout,&loop,&QEventLoop::quit);
    time.start(mec);
    loop.exec();
}

void MainWindow::slotBtnStartClick()
{
    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

    if(editUrl->text() == "")
    {
        editText->append(QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss   \n") + ASA_NET_TEXT_ERROR_STRING);
    }else{
        QString strRet = slotGetInfo(editUrl->text());
        qDebug()<<"strRet size is: \n"<<strRet.size();
        qDebug()<<"strRet is: \n"<<strRet;
        editUrl->clear();
        editText->clear();
        if(strRet == "")
        {
            editText->append(QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss   \n") + ASA_NET_TEXT_ERROR_STRING_1);
        }else{
            editText->setPlainText(strRet);
            slotTransferString2File(strRet,"C:/Users/AsaGlory/Desktop/Asa/AsaWorking/Prj/QtGetNetInfo/netInfo.txt");
        }
    }
}

void MainWindow::slotTransferString2File(const QString &strData, const QString &strFilePath)
{
    QFile file(strFilePath);

    file.setFileName(strFilePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        file.write(strData.toStdString().c_str());
        file.close();
    }

    return;
}

QString MainWindow::slotGetInfo(QString strUrl)
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(strUrl));
    QEventLoop * loop = new QEventLoop(this);
    connect(manager,&QNetworkAccessManager::finished,loop,&QEventLoop::quit);
    QNetworkReply * reply = manager->get(request);
    loop->exec();

    return QString(reply->readAll());
}
