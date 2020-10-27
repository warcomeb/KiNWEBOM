#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

/*!
 * \brief The Config struct
 */
struct Config
{
    QString path;

    QString schematic;

    // Parse component model
    bool onlyDefault;
};


#endif // CONFIG_H
