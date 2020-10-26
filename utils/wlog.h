#ifndef WLOG_H
#define WLOG_H

#include <QString>
#include <QDateTime>

#include "iostream"
using namespace std;

class WLog
{
private:
    WLog() {};

public:

    static WLog& instance (void)
    {
        static WLog* _instance = 0;
        if (_instance == 0)
        {
            _instance = new WLog();
        }
        return *_instance;
    };

    void setVerboseLevel (qint8 level)
    {
        verbose = level;
    }

    static QString currentTime (void)
    {
        QDateTime c = QDateTime::currentDateTime();
        return c.toString("yyyy.MM.dd hh:mm:ss.zzz");
    };

    static void log (QString text, quint8 level)
    {
        if (level <= verbose)
        {
            cout << currentTime().toUtf8().data()  << " " << text.toUtf8().data() << "\r\n";
        }
    };

//    static void info (QString text)
//    {
//        cout << currentTime().toUtf8().data()  << " [INFO] " << text.toUtf8().data() << "\r\n";
//    };

//    static void warning (QString text)
//    {
//        cout << currentTime().toUtf8().data()  << " [WARN] " << text.toUtf8().data() << "\r\n";
//    };

//    static void danger (QString text)
//    {
//        cout << currentTime().toUtf8().data()  << " [DANG] " << text.toUtf8().data() << "\r\n";
//    };

//    static void error (QString text)
//    {
//        cerr << currentTime().toUtf8().data()  << " [ERR_] " << text.toUtf8().data() << "\r\n";
//    };

    static quint8 verbose;
};

#endif // WLOG_H
