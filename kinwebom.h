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
     * \param config
     * \param model
     */
    bool saveJSON (Config config, QJsonObject model);

    /*!
     * \brief saveHTML
     * \param config
     * \param model
     * \param style
     */
    bool saveHTML (Config config, QJsonObject model, QString style);

    /*!
     * \brief writeDocumentInformations
     * \param config
     * \param html
     * \param model
     */
    void writeDocumentInformations (Config, QXmlStreamWriter &html, QJsonObject model);

    void writeHTMLRow (QXmlStreamWriter &html, QString key, QString value) const;

    Schematic mSchematic;
    BOMList   mList;
    BOMTitle  mTitle;

};

#endif // KINWEBOM_H
