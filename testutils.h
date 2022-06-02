#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QObject>

#include "QTest"
#include "utils.h"

class TestUtils : public QObject
{
    Q_OBJECT
private:
    Utils utils_;
private slots:
    void checkPassOnlyDigits()
    {
        QCOMPARE(utils_.checkPassword("7893298324"), false);
    }

    void checkPassOnlyLetters()
    {
        QCOMPARE(utils_.checkPassword("Abrakadabra"), false);
    }

    void checkPassOnlyCapitalLetters()
    {
        QCOMPARE(utils_.checkPassword("ABRAKAFFKA"), false);
    }

    void checkPassOnlyLowerLetters()
    {
        QCOMPARE(utils_.checkPassword("abrakabgigw"), false);
    }

    void checkPassCorrectOne()
    {
        QCOMPARE(utils_.checkPassword("Abrakolm34"), true);
    }

    void checkPassOutOfSize()
    {
        QCOMPARE(utils_.checkPassword("fgyfadykuhugbiyuoF4"), false);
    }
public:
    TestUtils(){};
};

#endif // TESTUTILS_H
