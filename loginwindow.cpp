#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "user.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    url = QUrl("http://qatime.cn/api/v1/sessions");
    QByteArray append("client_type=pc");
    append.append("&email=");
    append += this->ui->accountText->text();
    append.append("&password=");
    qInfo(append);
    append += this->ui->passwordText->text();
    QNetworkRequest request(url);
    reply = manager.post(request, append);
    connect(reply, &QNetworkReply::finished, this, &LoginWindow::loginFinished);
}

void LoginWindow::loginFinished()
{
    QByteArray result = reply->readAll();
    QJsonDocument document(QJsonDocument::fromJson(result));
    QJsonObject obj = document.object();
    QJsonObject data = obj["data"].toObject();
    if(obj["status"].toInt() == 1 && data.contains("remember_token"))
    {
        User *user = new User();
        user->readJson(data);
        MainWindow *mainWin = new MainWindow();
        mainWin->setCurrentUser(user);
        mainWin->setRemeberToken(data["remember_token"].toString());
        mainWin->initCourses();
        mainWin->show();
        this->destroy();
    }
    else
    {
        this->ui->messageLabel->setText("<html><head/><body><p><span style=\" font-size:10pt;\">错误</span></p></body></html>");
    }
}
