#include "component.h"
#include "../utils/wlog.h"

Component::Component(QString name, Config config):
    mName(name),
    mIsPowerElement(false)
{

}

Component::Component (QList<QString> params, Config config)
{
    WLog& log = WLog::instance();

    QList<QString>::iterator i;
    for (i = params.begin(); i != params.end(); ++i)
    {
        QString temp = *i;
        QStringList l = temp.split(" ");

        // Library and Reference
        if (l.at(0) == "L")
        {
            mSymbolLibrary = l.at(1);
            mReference     = l.at(2);

            if (mSymbolLibrary.startsWith("power"))
            {
                mIsPowerElement = true;
            }
        }
        else if (l.at(0) == "F")
        {

        }
    }

//    log.log(QString("Component - Name: " + mName),3);
    log.log(QString("Component - Ref : " + mReference),3);
    log.log(QString("Component - Lib : " + mSymbolLibrary),3);
}
