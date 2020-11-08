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

void BOMElement::write (QJsonObject &json, QJsonObject config) const
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

    if (!config.empty())
    {
        const QMap<QString,QString> params = mComponent.getParams();
        const QJsonArray configArray = config["Elements"].toArray();

        for (quint8 confIndex = 0; confIndex < configArray.size(); ++confIndex)
        {
            QString key = configArray[confIndex].toString();

            QMap<QString,QString>::const_iterator i = params.find(key);
            if (i != params.end())
            {
                o[key] = i.value();
            }
        }
    }

    json.insert("Element", o);
}

void BOMElement::write (QXmlStreamWriter &html, QJsonObject config) const
{
    html.writeStartElement(QStringLiteral("tr"));

    QString refs;
    foreach (const QString ref, mReferences)
    {
        refs += ref + " ";
    }

    html.writeStartElement(QStringLiteral("td"));
    html.writeCharacters(refs);
    html.writeEndElement(); //td

    html.writeStartElement(QStringLiteral("td"));
    html.writeCharacters(mComponent.getName());
    html.writeEndElement(); //td

    html.writeStartElement(QStringLiteral("td"));
    html.writeCharacters(QString::number(mQuantity));
    html.writeEndElement(); //td

    if (!config.empty())
    {
        const QMap<QString,QString> params = mComponent.getParams();
        const QJsonArray configArray = config["Elements"].toArray();

        for (quint8 confIndex = 0; confIndex < configArray.size(); ++confIndex)
        {
            QString key = configArray[confIndex].toString();

            QMap<QString,QString>::const_iterator i = params.find(key);
            if (i != params.end())
            {
                html.writeStartElement(QStringLiteral("td"));
                html.writeCharacters(i.value());
                html.writeEndElement(); //td
            }
        }
    }

    html.writeEndElement(); //tr
}
