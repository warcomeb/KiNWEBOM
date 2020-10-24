#include "kinwebom.h"

KiNWEBOM::KiNWEBOM(Config config, QObject *parent) : QObject(parent)
{
    mSchematic = Schematic (config.schematic);

}
