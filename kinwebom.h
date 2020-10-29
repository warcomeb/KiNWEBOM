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

signals:

private:

    BOMList create (void);

    void save (QString output, BOMFormat format);

    /*!
     * \brief saveJSON
     * \param output
     */
    void saveJSON (QString output);


    Schematic mSchematic;
    BOMList   mList;
};

#endif // KINWEBOM_H
