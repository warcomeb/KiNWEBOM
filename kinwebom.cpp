#include <QFile>
#include <QJsonDocument>
#include <QXmlStreamWriter>

#include "kinwebom.h"
#include "utils/wlog.h"

#include "bom/bomelement.h"
#include "bom/bomlist.h"

KiNWEBOM::KiNWEBOM(Config config, QObject *parent):
    QObject(parent)
{
    WLog& log = WLog::instance();
    log.setVerboseLevel(config.verboseLevel);

    mSchematic = Schematic(config);

    create();

    save(config);
}

void KiNWEBOM::create (void)
{
    WLog& log = WLog::instance();

    mList.clear();

    QList<Sheet> sheets = mSchematic.getSheets();
    QList<Sheet>::iterator i;
    for (i = sheets.begin(); i != sheets.end(); ++i)
    {
        QList<Component> components = (*i).getComponents();
        QList<Component>::iterator j;
        for (j = components.begin(); j != components.end(); ++j)
        {
            // Whether is not a power symbol, save it!
            if ((*j).isPowerElement() == false)
            {
                BOMElement e = BOMElement((*j));
                log.log(QString("KiNWEBOM: manage element -> ") + e.getName(),3);

                mList.add(e);
            }
        }
    }

    mTitle = BOMTitle(mSchematic.getTitleBlock());
}

bool KiNWEBOM::save (Config config)
{
    WLog& log = WLog::instance();

    if (mList.isEmpty())
    {
        return false;
    }

    QJsonObject modelObj;
    if (!config.outputModel.isNull())
    {
        QFile modelFile(config.outputModel);
        if (!modelFile.open(QIODevice::ReadOnly))
        {
            log.error(QString("Model file " + config.outputModel + " not found!"));
            return false;
        }
        QByteArray modelData = modelFile.readAll();
        QJsonDocument modelJson = QJsonDocument::fromJson(modelData);
        modelObj = modelJson.object();
        modelFile.close();
    }
    else
    {
        modelObj = QJsonObject();
    }

    // Open stylesheet
    QString style;
    if (config.format == BOM_FORMAT_HTML)
    {
        if (config.styleFile.isNull())
        {
            QFile styleFile( ":/style/resources/style/default.css");
            if (!styleFile.open(QIODevice::ReadOnly))
            {
                log.error(QString("Stylesheet default file not opened!"));
                return false;
            }
            style = styleFile.readAll();
            styleFile.close();
        }
        else
        {
            QFile styleFile(config.styleFile);
            if (!styleFile.open(QIODevice::ReadOnly))
            {
                log.error(QString("Stylesheet file " + config.styleFile + " not found!"));
                return false;
            }

            // TODO!

            styleFile.close();
        }
    }

    switch (config.format)
    {
    case BOM_FORMAT_JSON:
        return saveJSON(config.outputFile,modelObj);
        break;
    case BOM_FORMAT_HTML:
        return saveHTML(config.outputFile,modelObj,style);
        break;
    case BOM_FORMAT_CSV:
        return false;
        break;
    }

    return false;
}

bool KiNWEBOM::saveJSON (QString output, QJsonObject model)
{
    QFile o(output);
    if (!o.open(QIODevice::WriteOnly))
    {
        //TODO: message
        return false;
    }

    QJsonObject obj;

    mTitle.write(obj,model);
    mList.write(obj,model);

    QJsonDocument doc(obj);

    o.write(doc.toJson());
    return true;
}

bool KiNWEBOM::saveHTML (QString output, QJsonObject model, QString style)
{
    QFile o(output);
    if (!o.open(QIODevice::WriteOnly))
    {
        //TODO: message
        return false;
    }

//    QJsonObject obj;


    QTextStream textStream(&o);
    // TODO
//    textStream << QStringLiteral("<!DOCTYPE html>");
    QXmlStreamWriter obj(&o);
    obj.writeStartElement(QStringLiteral("html"));
    obj.writeAttribute(QStringLiteral("xmlns"),QStringLiteral("http://www.w3.org/1999/xhtml"));
    obj.writeAttribute(QStringLiteral("lang"),QStringLiteral("en"));
    obj.writeAttribute(QStringLiteral("xml"),QStringLiteral("lang"),QStringLiteral("en"));
    obj.writeStartElement(QStringLiteral("head"));
//    htmlWriter.writeStartElement(QStringLiteral("meta"));
//    htmlWriter.writeAttribute(QStringLiteral("http-equiv"),QStringLiteral("Content-Type"));
//    htmlWriter.writeAttribute(QStringLiteral("content"),QStringLiteral("text/html; charset=utf-8"));
//    htmlWriter.writeEndElement(); //meta
    obj.writeStartElement(QStringLiteral("title"));
    obj.writeCharacters(QStringLiteral("BOM"));
    obj.writeEndElement(); //title

    obj.writeStartElement(QStringLiteral("style"));
    obj.writeCharacters(style);
    obj.writeEndElement(); //style

    obj.writeEndElement(); //head

    obj.writeStartElement(QStringLiteral("body"));

//    htmlWriter.writeStartElement(QStringLiteral("h1"));
//    htmlWriter.writeCharacters(QStringLiteral("Test Page"));
//    htmlWriter.writeEndElement(); //h1
//    htmlWriter.writeStartElement(QStringLiteral("h2"));
//    htmlWriter.writeCharacters(QStringLiteral("Lorem"));
//    htmlWriter.writeEndElement(); //h2
//    htmlWriter.writeStartElement(QStringLiteral("p"));
//    htmlWriter.writeCharacters(QStringLiteral("Lorem ipsum dolor sit amet, consectetur adipiscing elit."));
//    htmlWriter.writeEndElement(); //p

//    mTitle.write(obj,model);
    mList.write(obj,model);

    obj.writeEndElement(); //body
    obj.writeEndElement(); //html

    return true;
}
