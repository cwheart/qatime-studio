#ifndef COURSE_H
#define COURSE_H

#include <QJsonObject>

class Course
{
public:
    Course();

    int id();
    QString name() const;
    int status();

    void readJson(const QJsonObject &json);

private:
    int mId;
    QString mName;
    int mStatus;
};

#endif // COURSE_H
