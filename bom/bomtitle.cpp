#include "bomtitle.h"

#include <QJsonObject>

BOMTitle::BOMTitle (TitleBlock title):
    mTitle(title)
{
    // Nothing to do!
}

void BOMTitle::write (QJsonObject &json) const
{
    QJsonObject o;

    // Save data...
    o["Title"] = mTitle.getBoardTitle();

    json.insert("Board Informations", o);
}
