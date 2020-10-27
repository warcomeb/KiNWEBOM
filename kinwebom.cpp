#include "kinwebom.h"
#include "utils/wlog.h"

KiNWEBOM::KiNWEBOM(Config config, QObject *parent):
    QObject(parent)
{
    WLog& log = WLog::instance();
    log.setVerboseLevel(3);

    mSchematic = Schematic(config);
}
