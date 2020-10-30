#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <QString>
#include <QList>

#include "sheet.h"
#include "titleblock.h"
#include "../config.h"

class Schematic
{
public:
    Schematic();
    Schematic(Config config);

    QList<Sheet> getSheets (void);

private:

    void parseTitleBlock ();
    void parseComeponent ();
    void parseSheet ();

    QList<Sheet> mSheets;
    TitleBlock   mTitleBlock;
};

#endif // SCHEMATIC_H
