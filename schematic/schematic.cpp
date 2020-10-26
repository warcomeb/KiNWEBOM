#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>

#include "schematic.h"
#include "component.h"
#include "utils/wlog.h"

#include <QDebug>

Schematic::Schematic ()
{

}

Schematic::Schematic (QString file)
{
    WLog log = WLog::instance();

    QFile sch(file);
    if (sch.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QDir d = QFileInfo(file).dir();

        QTextStream in(&sch);

        // Initialize this sheet as "main"
        Sheet main = Sheet(QString("Main"));

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
                log.log(QString("New sheet founds..."),2);
                continue;
            }
            else if (match.hasMatch() && (isSheetOpen == true))
            {
                // Close the sheet parsing and create new object
                isSheetOpen = false;
                mSheets.append(Sheet(sheetContent,d.path()));
                log.log(QString("Close sheet."),2);
                continue;
            }

            // Add new element to sheet description tag
            if (isSheetOpen)
            {
                sheetContent.append(line);
            }

//#if defined QT_DEBUG
////                qDebug() << "[INFO] Result object:" << mSheets << "\r\n";
//#endif
        }
    }
    else
    {
        printf("ERRORE");
//        qWarning() << "[WARN] " << "Cannot read file: " + file;
    }
}
