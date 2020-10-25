#include "sheet.h"

Sheet::Sheet(QString name, QString file):
    mName(name),
    mFile(file)
{

}

Sheet::Sheet (QList<QString> params)
{
    QList<QString>::iterator i;
    for (i = params.begin(); i != params.end(); ++i)
    {
        QString temp = *i;
        if (temp.startsWith("F0"))
        {
            // Save the names...
        }
        else if (temp.startsWith("F1"))
        {
            // Save the file name
        }

    }
}

//QDebug Sheet::operator<< (QDebug debug, const Sheet &s)
//{
//    debug.nospace() << "mysheet";

//    return debug;
//}
