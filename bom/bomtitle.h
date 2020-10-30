#ifndef BOMTITLE_H
#define BOMTITLE_H

#include "schematic/titleblock.h"

class BOMTitle
{
public:
    BOMTitle () {};
    BOMTitle (TitleBlock title);

    void write (QJsonObject &json) const;

private:

    TitleBlock mTitle;
};

#endif // BOMTITLE_H
