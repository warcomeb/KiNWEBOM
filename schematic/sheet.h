#ifndef SHEET_H
#define SHEET_H

#include <QRegularExpression>

#include "component.h"
#include "../config.h"

class Sheet
{
public:
    Sheet (QString name, QString file, Config config);
    Sheet (QList<QString> params, Config config);

    QList<Component> getComponents (void);

//    QDebug operator<<(QDebug debug, const Sheet &s);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Sheet|\\$EndSheet)");
    };

private:
    void parse (Config config);

    QString mName;
    QString mFile;
    QString mDir;

    QList<Component> mComponents;
};

#endif // SHEET_H
