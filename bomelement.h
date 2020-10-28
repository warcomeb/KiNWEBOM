#ifndef BOMELEMENT_H
#define BOMELEMENT_H

#include <QString>
#include <QList>

#include "schematic/component.h"

class BOMElement
{
public:
    BOMElement(Component c);

private:

    QList<QString> mReferences;
    QString        mName;
};

#endif // BOMELEMENT_H
