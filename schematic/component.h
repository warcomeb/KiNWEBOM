#ifndef COMPONENT_H
#define COMPONENT_H

#include <QRegularExpression>
#include <QString>

#include "../config.h"

class Component
{
public:
    Component (QString name, Config config);
    Component (QList<QString> params, Config config);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Comp|\\$EndComp)");
    };

private:
    QString mName;
    QString mReference;
    QString mSymbolLibrary;

    bool    mIsPowerElement;
};

#endif // COMPONENT_H
