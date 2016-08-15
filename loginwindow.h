#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

private:
    QUrl url;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    Ui::LoginWindow *ui;

    void loginFinished();
};

#endif // LOGINWINDOW_H
