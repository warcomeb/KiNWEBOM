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

            if (mSymbolLibrary.startsWith("power"))
            {
                mIsPowerElement = true;
            }
        }
        // Every field
        else if (l.at(0) == "F")
        {
            quint8 num = l.at(1).toUInt();

            // The extra parameters are not considered
            if ((num > 3) && (config.onlyDefault == true))
            {
                continue;
            }

            switch (num)
            {
            // Reference
            case 0:
                mReference = l.at(2);
                mReference.remove('\"');
                break;
            // Name/Value
            case 1:
                mName = l.at(2);
                mName.remove('\"');
                break;
            // Footprint
            case 2:
                mFootprint = l.at(2);
                mFootprint.remove('\"');
                break;
            // Datasheet
            case 3:
                QString url = l.at(2);
                mDatasheet  = url.remove('\"');
                break;
            }
        }
    }

    log.log(QString("Component - Name     : " + mName),3);
    log.log(QString("Component - Reference: " + mReference),3);
    log.log(QString("Component - Lib      : " + mSymbolLibrary),3);
    log.log(QString("Component - Footprint: " + mFootprint),3);
    log.log(QString("Component - Datashee : " + mDatasheet.toString()),3);
}

bool Component::isPowerElement (void)
{
    return mIsPowerElement;
}

QString Component::getName (void)
{
    return mName;
}

QString Component::getReference (void)
{
    return mReference;
}
