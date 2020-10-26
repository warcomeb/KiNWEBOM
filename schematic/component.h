#ifndef COMPONENT_H
#define COMPONENT_H

#include <QRegularExpression>
#include <QString>

class Component
{
public:
    Component (QString name);
    Component (QList<QString> params);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Comp|\\$EndComp)");
    };

private:
    QString mName;
};

#endif // COMPONENT_H
