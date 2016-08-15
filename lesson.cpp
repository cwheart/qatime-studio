#include "lesson.h"

Lesson::Lesson()
{

}

void Lesson::readJson(const QJsonObject &json)
{
    mId = json["id"].toInt();
    mName = json["name"].toString();
    mStatus = json["status"].toInt();
    mCourseId =json["course_id"].toInt();
}

int Lesson::courseId()
{
    return mCourseId;
}

QString Lesson::name()
{
    return mName;
}

