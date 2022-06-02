#include "utils.h"

#include "QDate"

bool Utils::checkPassword(QString pass)
{
    if (regExPass.match(pass).hasMatch() && pass.size() <= 16)
        return true;
    return false;
}

QString Utils::createReqIdText(QStringList fio_list, QDate bd)
{
    int today = QDate::currentDate().year();
    int age = today - bd.year();

    if (QDate::currentDate().month() < bd.month() && QDate::currentDate().day() < bd.day())
        age--;

    return QString(fio_list[0].front()) + QString(fio_list[1].front()) + QString(fio_list[2].front()) + " " + QString::number(age);
}
