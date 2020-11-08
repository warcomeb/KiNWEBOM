#include "bomlist.h"

#include "utils/wlog.h"

#include <QJsonArray>
#include <QXmlStreamWriter>

BOMList::BOMList()
{

}

void BOMList::clear (void)
{
    WLog& log = WLog::instance();
    log.log(QString("BOM List is cleared..."),3);
    mElements.clear();
}

bool BOMList::isEmpty (void)
{
    return mElements.isEmpty();
}

void BOMList::add (BOMElement e)
{
    WLog& log = WLog::instance();
    BOMElement* l = find(e);
    if (l == nullptr)
    {
        mElements.append(e);
        log.log(QString("BOM List: append new element -> ") + e.getName(),3);
    }
    else
    {
        l->addReference(e.getReferences());
        log.log(QString("BOM List: update element ") + l->getName(),3);
    }
}

BOMElement* BOMList::find (QString name)
{
    BOMElement* ret = nullptr;
    QList<BOMElement>::iterator i;
    for (i = mElements.begin(); i != mElements.end(); ++i)
    {
        if ((*i).getName() == name)
        {
            ret = &(*i);
        }
    }
    return ret;
}

BOMElement* BOMList::find (BOMElement e)
{
    BOMElement* ret = nullptr;
    QList<BOMElement>::iterator i;
    for (i = mElements.begin(); i != mElements.end(); ++i)
    {
        if ((*i).getName() == e.getName())
        {
            ret = &(*i);
        }
    }
    return ret;
}

void BOMList::write (QJsonObject &json, QJsonObject config) const
{
    QJsonArray refs;

    foreach (const BOMElement e, mElements)
    {
        QJsonObject o;
        e.write(o,config);
        refs.push_back(o);
    }
    json["Elements"] = refs;
}

void BOMList::write (QXmlStreamWriter &html, QJsonObject config) const
{
    html.writeStartElement(QStringLiteral("table"));
    html.writeAttribute(QStringLiteral("class"),QStringLiteral("list-table"));

    // Print TABLE head
    html.writeStartElement(QStringLiteral("thead"));
    html.writeStartElement(QStringLiteral("tr"));

    html.writeStartElement(QStringLiteral("th"));
    html.writeCharacters(QStringLiteral("References"));
    html.writeEndElement(); //th

    html.writeStartElement(QStringLiteral("th"));
    html.writeCharacters(QStringLiteral("Name"));
    html.writeEndElement(); //th

    html.writeStartElement(QStringLiteral("th"));
    html.writeCharacters(QStringLiteral("Quantity"));
    html.writeEndElement(); //th

    if (!config.empty())
    {
        const QJsonArray configArray = config["Elements"].toArray();

        for (quint8 confIndex = 0; confIndex < configArray.size(); ++confIndex)
        {
            html.writeStartElement(QStringLiteral("th"));
            html.writeCharacters(configArray[confIndex].toString());
            html.writeEndElement(); //th
        }
    }

    html.writeEndElement(); //tr
    html.writeEndElement(); //thead

    html.writeStartElement(QStringLiteral("tbody"));
    foreach (const BOMElement e, mElements)
    {
        e.write(html,config);
    }

    html.writeEndElement(); //tbody
    html.writeEndElement(); //table
}
