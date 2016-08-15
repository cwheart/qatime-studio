#include "course.h"

Course::Course()
{

}


void Course::readJson(const QJsonObject &json)
{
    mId = json["id"].toInt();
    mName = json["name"].toString();
    mStatus = json["status"].toInt();
}

int Course::id()
{
    return mId;
}

QString Course::name() const
{
    return mName;
}

int Course::status()
{
    return mStatus;
}
