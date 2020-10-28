#include "kinwebom.h"
#include "utils/wlog.h"

#include "bomelement.h"
#include "bomlist.h"

KiNWEBOM::KiNWEBOM(Config config, QObject *parent):
    QObject(parent)
{
    WLog& log = WLog::instance();
    log.setVerboseLevel(3);

    mSchematic = Schematic(config);
}

BOMList KiNWEBOM::createBOM (void)
{
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
                mList.add(e);
            }
        }

    }
}
