#ifndef BOMTITLE_H
#define BOMTITLE_H

#include "schematic/titleblock.h"

#include <QJsonObject>
#include <QXmlStreamWriter>

class BOMTitle
{
public:
    BOMTitle () {};
    BOMTitle (TitleBlock title);

    /*!
     * \brief write
     * \param json
     * \param config
     */
    void write (QJsonObject &json, QJsonObject config = QJsonObject()) const;

    /*!
     * \brief write
     * \param html
     * \param config
     */
    void write (QXmlStreamWriter &html, QJsonObject config = QJsonObject()) const;

private:

    void writeHTMLRow (QXmlStreamWriter &html, QString key, QString value) const;

    TitleBlock mTitle;
};

#endif // BOMTITLE_H
