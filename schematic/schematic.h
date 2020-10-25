#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <QString>
#include <QList>

#include "sheet.h"

class Schematic
{
public:
    Schematic();
    Schematic(QString file);

private:

    void parseTitleBlock ();
    void parseComeponent ();
    void parseSheet ();

    QList<Sheet> mSheets;
};

#endif // SCHEMATIC_H
