#ifndef COMPONENT_H
#define COMPONENT_H

#include <QRegularExpression>

class Component
{
public:
    Component();

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Comp|\\$EndComp)");
    };
};

#endif // COMPONENT_H
