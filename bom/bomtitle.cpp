#include "bomtitle.h"

#include <QJsonObject>

BOMTitle::BOMTitle (TitleBlock title):
    mTitle(title)
{
    // Nothing to do!
}

void BOMTitle::write (QJsonObject &json, QJsonObject config) const
{
    QJsonObject o;

    // Save data...
    o["Title"] = mTitle.getBoardTitle();

    QList<QString> comments = mTitle.getComments();
    if (!config.empty())
    {
        const QJsonObject configObj = config["Informations"].toObject();

        if (configObj.contains("Comment1"))
        {
            const QString val = configObj["Comment1"].toString();
            o[val] = comments.at(0);
        }

        if (configObj.contains("Comment2"))
        {
            const QString val = configObj["Comment2"].toString();
            o[val] = comments.at(1);
        }

        if (configObj.contains("Comment3"))
        {
            const QString val = configObj["Comment3"].toString();
            o[val] = comments.at(2);
        }

        if (configObj.contains("Comment4"))
        {
            const QString val = configObj["Comment4"].toString();
            o[val] = comments.at(3);
        }
    }

    json.insert("Board Informations", o);
}

void BOMTitle::writeHTMLRow (QXmlStreamWriter &html, QString key, QString value) const
{
    html.writeStartElement(QStringLiteral("tr"));
    html.writeStartElement(QStringLiteral("td"));
    html.writeAttribute(QStringLiteral("class"),QStringLiteral("title-table-key"));
    html.writeCharacters(key);
    html.writeEndElement(); //td
    html.writeStartElement(QStringLiteral("td"));
    html.writeCharacters(value);
    html.writeEndElement(); //td
    html.writeEndElement(); //tr
}

void BOMTitle::write (QXmlStreamWriter &html, QJsonObject config) const
{
    html.writeStartElement(QStringLiteral("table"));
    html.writeAttribute(QStringLiteral("class"),QStringLiteral("title-table"));

    writeHTMLRow(html,"Title",mTitle.getBoardTitle());
    writeHTMLRow(html,"Board Name",mTitle.getBoardName());
    writeHTMLRow(html,"Board Revision",mTitle.getBoardRevision());

//    html.writeStartElement(QStringLiteral("tbody"));
    QList<QString> comments = mTitle.getComments();
    if (!config.empty())
    {
        const QJsonObject configObj = config["Informations"].toObject();

        if (configObj.contains("Comment1"))
        {
            const QString val = configObj["Comment1"].toString();
            writeHTMLRow(html,val,comments.at(0));
        }

        if (configObj.contains("Comment2"))
        {
            const QString val = configObj["Comment2"].toString();
            writeHTMLRow(html,val,comments.at(1));
        }

        if (configObj.contains("Comment3"))
        {
            const QString val = configObj["Comment3"].toString();
            writeHTMLRow(html,val,comments.at(2));
        }

        if (configObj.contains("Comment4"))
        {
            const QString val = configObj["Comment4"].toString();
            writeHTMLRow(html,val,comments.at(3));
        }
    }
//    html.writeEndElement(); //tbody

    html.writeEndElement(); //table
}
