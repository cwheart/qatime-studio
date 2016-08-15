#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCourses()
{
    QUrl url = QUrl("http://qatime.cn/api/v1/live_studio/teachers/20/courses");
    QNetworkRequest request(url);
    QString str = this->mRemeberToken;

    qInfo(this->mRemeberToken.toUtf8());
    request.setRawHeader("Remember-Token", this->mRemeberToken.toUtf8());
    reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::requestFinished);
}

void MainWindow::setCurrentUser(User *user)
{
    currentUser = user;
}

void MainWindow::setRemeberToken(const QString &token)
{
    mRemeberToken = token;
}

void MainWindow::requestFinished()
{
    QByteArray result = reply->readAll();
    QJsonDocument document(QJsonDocument::fromJson(result));
    QJsonObject obj = document.object();
}
