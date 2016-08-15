#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QList>
#include "user.h"
#include "course.h"
#include "lesson.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCurrentUser(User *user);
    void setRemeberToken(const QString &name);
    void requestFinished();
    void initCourses();

private slots:
    void on_coursesBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    User *currentUser;
    QString mRemeberToken;

    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QList<Course *> myCourses;
    QList<Lesson *> myLessons;

};

#endif // MAINWINDOW_H
