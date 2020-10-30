#ifndef TITLEBLOCK_H
#define TITLEBLOCK_H

#include <QString>
#include <QRegularExpression>

#include "../config.h"

class TitleBlock
{
public:
    TitleBlock ();
    TitleBlock (Config config);

    void parse (QList<QString> params, Config config);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Descr|\\$EndDescr)");
    };

private:
    QString mTitle;
    QString mRevision;
    QString mDate;
    QString mCompany;

    QString mComment1;
    QString mComment2;
    QString mComment3;
    QString mComment4;
};

#endif // TITLEBLOCK_H
