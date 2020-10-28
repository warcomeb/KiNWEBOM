#include "bomlist.h"

#include "utils/wlog.h"

BOMList::BOMList()
{

}

void BOMList::clear (void)
{
    WLog& log = WLog::instance();
    log.log(QString("BOM List is cleared..."),3);
    mElements.clear();
}

void BOMList::add (BOMElement e)
{
    WLog& log = WLog::instance();
    BOMElement* l = find(e);
    if (l == nullptr)
    {
        mElements.append(e);
        log.log(QString("BOM List: append new element -> ") + e.getName(),3);
    }
    else
    {
        l->addReference(e.getReferences());
        log.log(QString("BOM List: update element ") + l->getName(),3);
    }
}

BOMElement* BOMList::find (QString name)
{
    BOMElement* ret = nullptr;
    QList<BOMElement>::iterator i;
    for (i = mElements.begin(); i != mElements.end(); ++i)
    {
        if ((*i).getName() == name)
        {
            ret = &(*i);
        }
    }
    return ret;
}

BOMElement* BOMList::find (BOMElement e)
{
    BOMElement* ret = nullptr;
    QList<BOMElement>::iterator i;
    for (i = mElements.begin(); i != mElements.end(); ++i)
    {
        if ((*i).getName() == e.getName())
        {
            ret = &(*i);
        }
    }
    return ret;
}
