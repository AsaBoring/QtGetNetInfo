#ifndef ASAGLOBAL_H
#define ASAGLOBAL_H

#include <QUrl>
#include <QFile>
#include <QTimer>
#include <QFrame>
#include <QTextEdit>
#include <QLineEdit>
#include <QDateTime>
#include <QEventLoop>
#include <QScrollBar>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#define ASA_NET_URL_WID                 600
#define ASA_NET_URL_HEI                 40
#define ASA_NET_TEXT_WID                600
#define ASA_NET_TEXT_HEI                400
#define ASA_NET_WINDOW_WID              800
#define ASA_NET_WINDOW_HEI              600
#define ASA_BTN_VERSE_TIME              200
#define ASA_NET_BTN_START_WID           300
#define ASA_NET_BTN_START_HEI           50
#define ASA_NET_BTN_URLLABEL_WID        60
#define ASA_NET_BTN_URLLABEL_HEI        30

#define ASA_NET_URL_STYLESHEET                  QString("QLineEdit{padding-left:70;padding-right:5;border:2px solid black;border-bottom:none}")
#define ASA_NET_TEXT_STYLESHEET                 QString("border:2px solid black")
#define ASA_NET_BTN_START_STRING                QString("Start")
#define ASA_NET_TEXT_ERROR_STRING               QString("url is not allowed to be used")
#define ASA_NET_WINDOW_STYLESHEET               QString("background-color:white;border:none")
#define ASA_NET_TEXT_ERROR_STRING_1             QString("fetch null of this url")
#define ASA_NET_BTN_URL_LABEL_STRING            QString("Url    :")
#define ASA_NET_BTN_START_STYLESHEET            QString("background-color:black;color:white")
#define ASA_NET_BTN_URL_LABEL_STYLESHEET        QString("background-color:white;color:black;border:none")
#define ASA_NET_BTN_START_STYLESHEET_REVERSE    QString("background-color:white;color:black")

#endif // ASAGLOBAL_H
