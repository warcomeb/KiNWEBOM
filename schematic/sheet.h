#ifndef SHEET_H
#define SHEET_H

#include <QRegularExpression>

#include "component.h"

class Sheet
{
public:
    Sheet (QString name, QString file = QString("."), QString dir = 0);
    Sheet (QList<QString> params, QString dir = 0);

//    QDebug operator<<(QDebug debug, const Sheet &s);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Sheet|\\$EndSheet)");
    };

private:
    void parse (void);

    QString mName;
    QString mFile;
    QString mDir;

    QList<Component> mComponents;
};

#endif // SHEET_H
