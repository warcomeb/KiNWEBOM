#ifndef BOMELEMENT_H
#define BOMELEMENT_H

#include <QString>
#include <QList>
#include <QJsonObject>

#include "schematic/component.h"

class BOMElement
{
public:
    BOMElement(Component c);

    /*!
     * \brief getName
     * \return
     */
    QString getName (void);

    /*!
     * \brief getReferences
     * \return
     */
    QList<QString> getReferences (void);

    /*!
     * \brief addReference
     * \param ref
     */
    void addReference (QString ref);

    /*!
     * \brief addReference
     * \param ref
     */
    void addReference (QList<QString> ref);

    /*!
     * \brief write
     * \param json
     * \param config
     */
    void write (QJsonObject &json, QJsonObject config = QJsonObject()) const;

private:

    Component      mComponent;
    QList<QString> mReferences;
//    QString        mName;

    quint32        mQuantity;
};

#endif // BOMELEMENT_H
