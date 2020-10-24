#ifndef SHEET_H
#define SHEET_H

#include <QRegularExpression>

class Sheet
{
public:
    Sheet();

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Sheet|\\$EndSheet)");
    };
};

#endif // SHEET_H
