#ifndef KINWEBOM_H
#define KINWEBOM_H

#include <QObject>

#include "schematic/schematic.h"
#include "config.h"

#include "bom/bomlist.h"
#include "bom/bomtitle.h"

class KiNWEBOM : public QObject
{
public:
    explicit KiNWEBOM (Config config, QObject *parent = nullptr);

signals:

private:

    void create (void);

    void save (QString output, QString model, BOMFormat format);

    /*!
     * \brief saveJSON
     * \param output
     * \param model
     */
    void saveJSON (QString output, QJsonObject model);


    Schematic mSchematic;
    BOMList   mList;
    BOMTitle  mTitle;

};

#endif // KINWEBOM_H
