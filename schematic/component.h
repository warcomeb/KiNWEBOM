#ifndef COMPONENT_H
#define COMPONENT_H

#include <QRegularExpression>
#include <QString>
#include <QUrl>

#include "../config.h"

class Component
{
public:
    Component (QString name, Config config);
    Component (QList<QString> params, Config config);

    bool isPowerElement (void);

    QString getName (void);
    QString getReference (void);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Comp|\\$EndComp)");
    };

private:
    QString mName;
    QString mReference;
    QString mSymbolLibrary;
    QString mFootprint;
    QUrl    mDatasheet;

    bool    mIsPowerElement;
};

#endif // COMPONENT_H
