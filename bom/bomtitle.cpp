#include "bomtitle.h"

#include <QJsonObject>

BOMTitle::BOMTitle (TitleBlock title):
    mTitle(title)
{
    // Nothing to do!
}

void BOMTitle::write (QJsonObject &json, QJsonObject config) const
{
    QJsonObject o;

    // Save data...
    o["Title"] = mTitle.getBoardTitle();

    QList<QString> comments = mTitle.getComments();
    if (!config.empty())
    {
        const QJsonObject configObj = config["Informations"].toObject();

        if (configObj.contains("Comment1"))
        {
            const QString val = configObj["Comment1"].toString();
            o[val] = comments.at(0);
        }

        if (configObj.contains("Comment2"))
        {
            const QString val = configObj["Comment2"].toString();
            o[val] = comments.at(1);
        }

        if (configObj.contains("Comment3"))
        {
            const QString val = configObj["Comment3"].toString();
            o[val] = comments.at(2);
        }

        if (configObj.contains("Comment4"))
        {
            const QString val = configObj["Comment4"].toString();
            o[val] = comments.at(3);
        }
    }

    json.insert("Board Informations", o);
}
