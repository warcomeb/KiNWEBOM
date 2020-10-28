#include "bomelement.h"

BOMElement::BOMElement(Component c)
{
    mName = c.getName();
    mReferences.append(c.getReference());
}
