#ifndef LESSON_H
#define LESSON_H

#include <QJsonObject>

class Lesson
{
public:
    Lesson();
    void readJson(const QJsonObject &json);
    int courseId();
    QString name();

private:
    int mId;
    int mCourseId;
    QString mName;
    int mStatus;
};

#endif // LESSON_H
