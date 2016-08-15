#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "course.h"
#include "lesson.h"

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
    QUrl url = QUrl("http://qatime.cn/api/v1/live_studio/teachers/20/courses/full");
    QNetworkRequest request(url);
    QString str = this->mRemeberToken;

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
    QJsonArray courses = obj["data"].toArray();
    foreach (const QJsonValue & value, courses)
    {
        QJsonObject obj = value.toObject();
        Course *course = new Course();
        course->readJson(value.toObject());
        this->myCourses.append(course);
        this->ui->coursesBox->addItem(course->name(), QVariant(course->id()));
        QJsonArray lessons = obj["lessons"].toArray();
        foreach (const QJsonValue & value, lessons)
        {
            Lesson *lesson = new Lesson();
            lesson->readJson(value.toObject());
            lesson->setCourseId(course->id());
            this->myLessons.append(lesson);
        }
    }
}

void MainWindow::on_coursesBox_currentIndexChanged(int index)
{
    int courseId = this->myCourses[index]->id();
    this->ui->lessonsBox->clear();
    foreach (Lesson *lesson, this->myLessons)
    {
        if(lesson->courseId() == courseId)
        {
            this->ui->lessonsBox->addItem(lesson->name());
        }
    }
}
