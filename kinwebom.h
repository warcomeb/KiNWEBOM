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


    void create (void);

    /*!
     * \brief save
     * \param config
     * \return
     */
    bool save (Config config);

signals:

private:

    /*!
     * \brief saveJSON
     * \param output
     * \param model
     */
    bool saveJSON (QString output, QJsonObject model);

    /*!
     * \brief saveHTML
     * \param output
     * \param model
     * \param style
     */
    bool saveHTML (QString output, QJsonObject model, QString style);

    Schematic mSchematic;
    BOMList   mList;
    BOMTitle  mTitle;

};

#endif // KINWEBOM_H
