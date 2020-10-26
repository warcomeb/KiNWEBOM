#include "kinwebom.h"
#include "utils/wlog.h"

KiNWEBOM::KiNWEBOM(Config config, QObject *parent) : QObject(parent)
{
    mSchematic = Schematic (config.schematic);

    WLog log = WLog::instance();
    log.setVerboseLevel(2);
}
