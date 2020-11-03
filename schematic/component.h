#ifndef COMPONENT_H
#define COMPONENT_H

#include <QRegularExpression>
#include <QString>
#include <QUrl>

#include "../config.h"

/*!
 * \brief The Component class
 */
class Component
{
public:
    Component (QString name, Config config);
    Component (QList<QString> params, Config config);

    bool isPowerElement (void);

    /*!
     * \brief getName
     * \return
     */
    QString getName (void);
    /*!
     * \brief getReference
     * \return
     */
    QString getReference (void);
    /*!
     * \brief getParams
     * \return
     */
    QMap<QString,QString> getParams (void);

    static QRegularExpression getParsingExpression (void)
    {
        return QRegularExpression("(\\$Comp|\\$EndComp)");
    };

private:
    QString mName;
    QString mReference;
    QString mSymbolLibrary;
    QString mFootprint;
    QUrl    mDatasheet;
    QMap<QString,QString> mParams;

    bool    mIsPowerElement;
};

#endif // COMPONENT_H
