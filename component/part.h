#ifndef PART_H
#define PART_H

#include <QString>

class Part
{
public:
    Part(QString name, QString reference);

private:
    QString mName;
    QString mReference;
};

#endif // PART_H
