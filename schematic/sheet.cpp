#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "sheet.h"
#include "utils/wlog.h"

Sheet::Sheet(QString name, QString file, QString dir):
    mName(name),
    mFile(file),
    mDir(dir)
{
    parse();
}

Sheet::Sheet (QList<QString> params, QString dir):
    mDir(dir)
{
    WLog log = WLog::instance();

    QList<QString>::iterator i;
    for (i = params.begin(); i != params.end(); ++i)
    {
        QString temp = *i;
        if (temp.startsWith("F0"))
        {
            // Save the names...
            QStringList l = temp.split(" ");
            mName = l.at(1);
            mName.remove('\"');
        }
        else if (temp.startsWith("F1"))
        {
            // Save the file name
            QStringList l = temp.split(" ");
            mFile = l.at(1);
            mFile.remove('\"');
        }
    }

    log.log(QString("Sheet Name : " + mName),2);
    log.log(QString("Sheet File : " + mFile),2);

    parse();
}

void Sheet::parse (void)
{
    WLog log = WLog::instance();
    if (!(mFile == "."))
    {
        QFile sheet(mDir + "/" + mFile);
        if (sheet.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            log.log(QString("Parsing file: " + mDir + "/" + mFile),2);
            QTextStream in(&sheet);

            QRegularExpression compExp = Component::getParsingExpression();
            bool isComponentOpen = false;
            QList<QString> componentContent;

            while (!in.atEnd())
            {
                QString line = in.readLine().trimmed();

                // Sheet parsing...
                QRegularExpressionMatch match = compExp.match(line);
                if (match.hasMatch() && (isComponentOpen == false))
                {
                    isComponentOpen = true;
                    componentContent.clear();
                    log.log(QString("New component founds..."),3);
                    continue;
                }
                else if (match.hasMatch() && (isComponentOpen == true))
                {
                    // Close the component parsing and create new object
                    isComponentOpen = false;
                    mComponents.append(Component(componentContent));
                    log.log(QString("Close component."),3);
                    continue;
                }

                // Add new element to component description tag
                if (isComponentOpen)
                {
                    componentContent.append(line);
                }

            }
        }
        else
        {
            log.log(QString("File not opened: " + mDir + "/" + mFile),2);
        }
    }
}

//QDebug Sheet::operator<< (QDebug debug, const Sheet &s)
//{
//    debug.nospace() << "mysheet";

//    return debug;
//}
