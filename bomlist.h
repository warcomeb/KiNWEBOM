#ifndef BOMLIST_H
#define BOMLIST_H

#include "bomelement.h"

#include <QList>

/*!
 * \brief The BOMList class
 */
class BOMList
{
public:
    BOMList();

    /*!
     * \brief clear
     */
    void clear (void);

    /*!
     * \brief add
     * \param e
     */
    void add(BOMElement e);

    /*!
     * \brief find
     * \param name
     * \return
     */
    BOMElement* find (QString name);

    BOMElement* find (BOMElement e);

private:
    QList<BOMElement> mElements;
};

#endif // BOMLIST_H
