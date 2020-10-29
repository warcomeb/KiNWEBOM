#ifndef KINWEBOM_H
#define KINWEBOM_H

#include <QObject>

#include "schematic/schematic.h"
#include "config.h"

#include "bomlist.h"

class KiNWEBOM : public QObject
{
public:
    explicit KiNWEBOM (Config config, QObject *parent = nullptr);

    BOMList createBOM (void);

signals:

private:
    Schematic mSchematic;

    BOMList   mList;
};

#endif // KINWEBOM_H
