#include <QFile>
#include <QTextStream>

#include "schematic.h"
#include "component.h"

#include <QDebug>

Schematic::Schematic ()
{

}

Schematic::Schematic (QString file)
{
    QFile sch(file);
    if (sch.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QTextStream in(&sch);

        QRegularExpression sheetExp = Sheet::getParsingExpression();
        bool isSheetOpen = false;
        QList<QString> sheetContent;

        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();

            // Sheet parsing...
            QRegularExpressionMatch match = sheetExp.match(line);
            if (match.hasMatch() && (isSheetOpen == false))
            {
                isSheetOpen = true;
                sheetContent.clear();
#if defined QT_DEBUG
                qDebug() << "[INFO] New sheet founds...\r\n";
#endif
                continue;
            }
            else if (match.hasMatch() && (isSheetOpen == true))
            {
                // Close the sheet parsing and create new object
                isSheetOpen = false;
#if defined QT_DEBUG
                qDebug() << "[INFO] Close sheet.\r\n";
#endif
                continue;
            }

            // Add new element to sheet description tag
            if (isSheetOpen)
            {
                sheetContent.append(line);
            }

        }
    }
    else
    {
        printf("ERRORE");
//        qWarning() << "[WARN] " << "Cannot read file: " + file;
    }
}
