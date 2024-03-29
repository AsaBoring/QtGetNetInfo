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

            QStringList slDownloadInfo;
            slDownloadInfo.clear();

//            slotFetchDownloadWebSiteFromWebInfo(strRet,slDownloadInfo);

            for (int i = 1 ; i < 63 ; ++i) {
                QString strWebSIte = ASA_NET_TARGET_WEB_SITE(i);
                qDebug()<<"Asa strWebSIte is : "<<strWebSIte;
                QString strWebInfo = slotGetInfo(strWebSIte);
                slotFetchDownloadWebSiteFromWebInfo(strWebInfo,slDownloadInfo);
            }
            qDebug()<<"Asa slDownloadInfo size is : "<<slDownloadInfo.size();
            QString strTotal;
            for(QStringList::iterator it = slDownloadInfo.begin() ; it != slDownloadInfo.end() ; ++it){
                strTotal+=*it+"\n";
            }
            slotTransferString2File(strTotal,"C:/Users/AsaGlory/Desktop/Asa/AsaWorking/Prj/QtGetNetInfo/netInfoSplit.txt");
        }
    }

    /*Fetch fdm link from file*/
    /*
    QString strFilePath = "C:/Users/AsaGlory/Desktop/Asa/AsaWorking/Prj/QtGetNetInfo/netInfoSplit.txt";
    QFile file(strFilePath);

    file.setFileName(strFilePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray array =  file.readAll();
        QString strFileInfo(array);
        QStringList slFileInfoList = strFileInfo.split("\n");
        QString strTotal;
        for(int i = 0 ; i < slFileInfoList.size() ; ++i){
            if(slFileInfoList.at(i).contains("mp4") || slFileInfoList.at(i).contains("rmvb"))
            {
                strTotal+=slFileInfoList.at(i)+"\n";
            }
        }
        file.close();

        slotTransferString2File(strTotal,"C:/Users/AsaGlory/Desktop/Asa/AsaWorking/Prj/QtGetNetInfo/netInfoSplit.txt");
        qDebug()<<"Asa end";
    }

    return;
    */

    /*Fetch all file info from web*/
    /*
    QStringList slDownloadInfo;
    slDownloadInfo.clear();

    for (int i = 1 ; i < 63 ; ++i) {
        QString strWebSIte = ASA_NET_TARGET_WEB_SITE(i);
        qDebug()<<"Asa strWebSIte is : "<<strWebSIte;
        QString strWebInfo = slotGetInfo(strWebSIte);
        slotFetchDownloadWebSiteFromWebInfo(strWebInfo,slDownloadInfo);
    }
    qDebug()<<"Asa slDownloadInfo size is : "<<slDownloadInfo.size();
    QString strTotal;
    for(QStringList::iterator it = slDownloadInfo.begin() ; it != slDownloadInfo.end() ; ++it){
        strTotal+=*it+"\n";
    }
    slotTransferString2File(strTotal,"C:/Users/AsaGlory/Desktop/Asa/AsaWorking/Prj/QtGetNetInfo/netInfoSplit.txt");
    */
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
    manager->deleteLater();
    loop->deleteLater();

    return QString(reply->readAll());
}

void MainWindow::slotFetchDownloadWebSiteFromWebInfo(const QString &strWebInfo, QStringList &slRet)
{
    if(strWebInfo.isEmpty())
    {
        return;
    }

//    qDebug()<<"Asa strWebInfo is : "<<strWebInfo;
    QString strTmp = "";

    QString strSpliteLabel1 = "<div id=\"tpl-img-content\">";
    QString strSpliteLabel2 = "<li>";
    QString strSpliteLabel3 = "</li>";
    QString strSpliteLabel4 = "<input type=\"text\" data-clipboard-text=\"";
    QString strSpliteLabel5 = "\" id=\"link11\" class=\"form-control input-sm fdm_down\"";

    QStringList tmpSl = strWebInfo.split(strSpliteLabel1);
    if(tmpSl.size() != 2)
    {
        qDebug()<<"Asa fetch web info failed!!!";
        return;
    }

    QString strPartOfDownload = tmpSl.at(1);
    tmpSl.clear();
    tmpSl = strPartOfDownload.split(strSpliteLabel2);
    for (int i = 0 ; i < tmpSl.size() ; ++i) {
        strTmp += tmpSl.at(i);
    }

    QString strLine;
    QStringList strListHtml,strListName,strListFdm;
    tmpSl.clear();
    tmpSl = strTmp.split(strSpliteLabel3);
    strTmp.clear();
    for (int j = 0 ; j < tmpSl.size()-1 ; ++j) {
        strTmp = tmpSl.at(j);
        QStringList slTmp2 = strTmp.split("\"");
        for (int n = 0 ; n < slTmp2.size() ; ++n) {
            qDebug()<<"str is : "<<slTmp2.at(n);
            //Check download web site as html
            if(slTmp2.at(n).contains("/xiazai/") && slTmp2.at(n).contains(".html"))
            {
                if(!strLine.contains(slTmp2.at(n)))
                {
                    strListHtml.append(QString("https://www.e3sjmydvdo9w.com/")+slTmp2.at(n));
                    strLine+=QString("https://www.e3sjmydvdo9w.com/")+slTmp2.at(n)+"\n";

                    QString strFdm = slotGetInfo(QString("https://www.e3sjmydvdo9w.com/")+slTmp2.at(n)).split(strSpliteLabel4).at(1).split(strSpliteLabel5).at(0);
                    strListFdm.append(strFdm);
                    strLine+=strFdm+"\n";
                }
            }

            //Check file title
            if(slTmp2.at(n).contains("title"))
            {
                if(!strLine.contains(slTmp2.at(n+1)))
                {
                    strListName.append(slTmp2.at(n+1));
                    strLine+=slTmp2.at(n+1)+"\n";
                }
            }
        }
    }

    if(strListHtml.size() == strListName.size() && strListHtml.size() != 0 && strListName.size() != 0)
    {
        for (int k = 0 ; k < strListHtml.size() ; ++k) {
            slRet.append(strListHtml.at(k));
            slRet.append(strListFdm.at(k));
            slRet.append(strListName.at(k));
        }
    }else {
        qDebug()<<"Asa size error !!!!! strListHtml size is : "<<strListHtml.size()<<"     strListName size is : "<<strListName.size();
    }

    qDebug()<<"Asa mapRet size is : "<<slRet.size();
//    slotTransferString2File(strLine,"C:/Users/AsaGlory/Desktop/Asa/AsaWorking/Prj/QtGetNetInfo/netInfoSplit.txt");
}
