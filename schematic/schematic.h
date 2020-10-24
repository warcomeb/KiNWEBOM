#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <QString>
#include <QVector>

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

    QVector<Sheet> mSheet;
};

#endif // SCHEMATIC_H
