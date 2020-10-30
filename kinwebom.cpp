#include <QFile>
#include <QJsonDocument>

#include "kinwebom.h"
#include "utils/wlog.h"

#include "bomelement.h"
#include "bomlist.h"

KiNWEBOM::KiNWEBOM(Config config, QObject *parent):
    QObject(parent)
{
    WLog& log = WLog::instance();
    log.setVerboseLevel(config.verboseLevel);

    mSchematic = Schematic(config);

    create();

    save(config.outputFile,config.format);
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

void KiNWEBOM::save (QString output, BOMFormat format)
{
    if (mList.isEmpty())
    {
        return;
    }

    switch (format)
    {
    case BOM_FORMAT_JSON:
        return saveJSON(output);
        break;
    case BOM_FORMAT_HTML:

        break;
    case BOM_FORMAT_CSV:

        break;
    }
}

void KiNWEBOM::saveJSON (QString output)
{
    QFile o(output);
    if (!o.open(QIODevice::WriteOnly))
    {
        //TODO: message
        return;
    }

    QJsonObject obj;

    mTitle.write(obj);
    mList.write(obj);

    QJsonDocument doc(obj);

    o.write(doc.toJson());
}
