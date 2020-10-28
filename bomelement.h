#ifndef BOMELEMENT_H
#define BOMELEMENT_H

#include <QString>
#include <QList>

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

private:

    QList<QString> mReferences;
    QString        mName;
};

#endif // BOMELEMENT_H
