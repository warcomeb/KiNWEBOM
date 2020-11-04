#include <QFile>
#include <QJsonDocument>

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

    save(config.outputFile,config.outputModel,config.format);
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

void KiNWEBOM::save (QString output, QString model, BOMFormat format)
{
    WLog& log = WLog::instance();


    if (mList.isEmpty())
    {
        return;
    }

    QJsonObject modelObj;
    if (!model.isNull())
    {
        QFile modelFile(model);
        if (!modelFile.open(QIODevice::ReadOnly))
        {
            log.error(QString("Model file " + model + " not found!"));
            return;
        }
        QByteArray modelData = modelFile.readAll();
        QJsonDocument modelJson = QJsonDocument::fromJson(modelData);
        modelObj = modelJson.object();
    }
    else
    {
        modelObj = QJsonObject();
    }

    switch (format)
    {
    case BOM_FORMAT_JSON:
        return saveJSON(output,modelObj);
        break;
    case BOM_FORMAT_HTML:

        break;
    case BOM_FORMAT_CSV:

        break;
    }
}

void KiNWEBOM::saveJSON (QString output, QJsonObject model)
{
    QFile o(output);
    if (!o.open(QIODevice::WriteOnly))
    {
        //TODO: message
        return;
    }

    QJsonObject obj;

    mTitle.write(obj,model);
    mList.write(obj,model);

    QJsonDocument doc(obj);

    o.write(doc.toJson());
}
