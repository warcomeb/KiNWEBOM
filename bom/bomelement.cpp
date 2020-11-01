#include "bomelement.h"

#include <QJsonArray>

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

void BOMElement::write (QJsonObject &json) const
{
    QJsonObject o;
    // Save name...
    o["Name"] = mName;

    QJsonArray refs;
    foreach (const QString ref, mReferences)
    {
        refs.push_back(ref);
    }
    o["Reference"] = refs;

    json.insert("Element", o);
}
