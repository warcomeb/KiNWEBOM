#include "bomelement.h"

BOMElement::BOMElement(Component c)
{
    mName = c.getName();
    mReferences.append(c.getReference());
}

QString BOMElement::getName (void)
{
    return mName;
}

QList<QString> BOMElement::getReferences (void)
{
    return mReferences;
}

void BOMElement::addReference (QString ref)
{
    mReferences.append(ref);
}

void BOMElement::addReference (QList<QString> ref)
{
    mReferences.append(ref);
}
