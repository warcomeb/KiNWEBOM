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
//        QStringList l = temp.split(" ");

        // Library and Reference
        if (temp.at(0) == 'L')
        {
            QStringList l = temp.split(" ");
            mSymbolLibrary = l.at(1);

            if (mSymbolLibrary.startsWith("power"))
            {
                mIsPowerElement = true;
            }
            else
            {
                mIsPowerElement = false;
            }
        }
        // Every field
        else if (temp.at(0) == 'F')
        {
            QString fieldNum = temp.at(2);
            if (temp.at(3).isDigit())
            {
                fieldNum += temp.at(3);
            }
            quint8 num = fieldNum.toUInt();

            // The extra parameters are not considered
            if ((num > 3) && (config.onlyDefault == true))
            {
                continue;
            }

            QRegularExpression data("\"([+:.,\\-/\\€\\$\\s\\w]*)\"");
            QRegularExpressionMatchIterator dataIterator = data.globalMatch(temp);
            QRegularExpressionMatch match;

            if (dataIterator.hasNext())
            {
                switch (num)
                {
                // Reference
                case 0:
                    {
                        match = dataIterator.next();
                        mReference = match.captured();
                        mReference.remove('\"');
                    }
                    break;
                // Name/Value
                case 1:
                    {
                        match = dataIterator.next();
                        mName = match.captured();
                        mName.remove('\"');
                    }
                    break;
                // Footprint
                case 2:
                    {
                        match = dataIterator.next();
                        mFootprint = match.captured();
                        mFootprint.remove('\"');
                    }
                    break;
                // Datasheet
                case 3:
                    {
                        match = dataIterator.next();
                        QString url = match.captured();
                        mDatasheet  = url.remove('\"');
                    }
                    break;
                default:
                    match = dataIterator.next();
                    QString value = match.captured().remove('\"');
                    match = dataIterator.next();
                    QString name = match.captured().remove('\"');
                    mParams[name] = value;
                    break;
                }
            }
        }
    }

    log.log(QString("Component - Name      : " + mName),3);
    log.log(QString("Component - Reference : " + mReference),3);
    log.log(QString("Component - Lib       : " + mSymbolLibrary),3);
    log.log(QString("Component - Footprint : " + mFootprint),3);
    log.log(QString("Component - Datasheet : " + mDatasheet.toString()),3);
    QMapIterator<QString, QString> j(mParams);
    while (j.hasNext())
    {
        j.next();
        log.log(QString("Component - Params    : " + j.key() + " > " + j.value()),3);
    }
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

QMap<QString,QString> Component::getParams (void)
{
    return mParams;
}
