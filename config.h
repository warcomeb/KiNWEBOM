#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

/*!
 * \brief The BOM_Format enum
 */
enum BOMFormat
{
    BOM_FORMAT_JSON,
    BOM_FORMAT_HTML,
    BOM_FORMAT_CSV,
};

/*!
 * \brief The Config struct
 */
struct Config
{
    QString path;

    QString schematic;

    // Parse component model
    bool onlyDefault;

    /*!
     * \brief outputModel
     */
    QString outputModel;

    QString outputFile;
    BOMFormat format;

    /*!
     * \brief verboseLevel
     */
    quint8 verboseLevel;
};


#endif // CONFIG_H
