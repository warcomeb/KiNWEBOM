#ifndef SHEET_H
#define SHEET_H

#include <QRegularExpression>

class Sheet
{
public:
    Sheet (QString name, QString file = QString("."));
    Sheet (QList<QString> params);

//    QDebug operator<<(QDebug debug, const Sheet &s);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Sheet|\\$EndSheet)");
    };

private:
    QString mName;
    QString mFile;
};

#endif // SHEET_H
