#include "bomelement.h"

#include <QJsonArray>

BOMElement::BOMElement(Component c):
    mComponent(c)
{
    mReferences.append(c.getReference());

    mQuantity = 1;
}

QString BOMElement::getName (void)
{
    return mComponent.getName();
}

QList<QString> BOMElement::getReferences (void)
{
    return mReferences;
}

void BOMElement::addReference (QString ref)
{
    mReferences.append(ref);
    mQuantity++;
}

void BOMElement::addReference (QList<QString> ref)
{
    mReferences.append(ref);
    mQuantity += ref.size();
}

void BOMElement::write (QJsonObject &json) const
{
    QJsonObject o;
    // Save name...
    o["Name"] = mComponent.getName();

    QJsonArray refs;
    foreach (const QString ref, mReferences)
    {
        refs.push_back(ref);
    }
    o["Reference"] = refs;
    o["Quantity"]  = QString::number(mQuantity);

    json.insert("Element", o);
}
