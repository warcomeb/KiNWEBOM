#ifndef BOMTITLE_H
#define BOMTITLE_H

#include "schematic/titleblock.h"

#include <QJsonObject>

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

private:

    TitleBlock mTitle;
};

#endif // BOMTITLE_H
