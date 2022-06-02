#ifndef UTILS_H
#define UTILS_H

#include "QRegularExpression"

class Utils
{
private:
    QRegularExpression regExPass = QRegularExpression("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,16}");
public:
    Utils(){};
    bool checkPassword(QString pass);
    QString createReqIdText(QStringList fio_list, QDate bd);

};

#endif // UTILS_H
