#ifndef KINWEBOM_H
#define KINWEBOM_H

#include <QObject>

#include "schematic/schematic.h"

struct Config
{
    QString schematic;
};

class KiNWEBOM : public QObject
{
public:
    explicit KiNWEBOM(Config config, QObject *parent = nullptr);

signals:

private:
    Schematic mSchematic;
};

#endif // KINWEBOM_H
