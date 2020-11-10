#include <QCoreApplication>

#include <QCommandLineParser>

#include <QDir>
#include <QFileInfo>

#include "metadata.h"
#include "kinwebom.h"
#include "config.h"

enum CLIParseResult
{
    CLI_PARSE_RESULT_OK,
    CLI_PARSE_RESULT_ERROR,
    CLI_PARSE_RESULT_VERSION,
    CLI_PARSE_RESULT_HELP,
};

CLIParseResult parseCommandLine (QCommandLineParser &parser, Config *config, QString *errorMessage)
{
    const QCommandLineOption helpOption = parser.addHelpOption();

    const QCommandLineOption verboseOption(QStringList() << "v" << "verbose",
            QCoreApplication::translate("main", "Select verbose output <level>"),
            QCoreApplication::translate("main", "level"));
    parser.addOption(verboseOption);

    const QCommandLineOption onlyDefaultOption(QStringList() << "o" << "only-default",
            QCoreApplication::translate("main", "Parse only default parameters"));
    parser.addOption(onlyDefaultOption);

    const QCommandLineOption modelOutputOption(QStringList() << "m" << "model",
            QCoreApplication::translate("main", "Output <model> type for BOMs (JSON file)"),
            QCoreApplication::translate("main", "model"));
    parser.addOption(modelOutputOption);

    const QCommandLineOption nameOption(QStringList() << "n" << "name",
            QCoreApplication::translate("main", "The board <name>"),
            QCoreApplication::translate("main", "name"));
    parser.addOption(nameOption);

    const QCommandLineOption cssStyleOption(QStringList() << "s" << "style",
            QCoreApplication::translate("main", "CSS file <style> for HTML output"),
            QCoreApplication::translate("main", "style"));
    parser.addOption(cssStyleOption);

    parser.addPositionalArgument("source", QCoreApplication::translate("main", "The schematic main (.sch) file."));
    parser.addPositionalArgument("output", QCoreApplication::translate("main", "BoM output file name."
                                                                               "The suffix choose the output file type."
                                                                               "The format supported are CSV, HTML and JSON (default)."));


    if (!parser.parse(QCoreApplication::arguments()))
    {
        *errorMessage = parser.errorText();
        return CLI_PARSE_RESULT_ERROR;
    }

//    const QStringList args = parser.optionNames();
//    if (args.size() < 1)
//    {
//        *errorMessage = "Error: Must specify an argument!";
//        return CLI_PARSE_RESULT_ERROR;
//    }

    if (parser.isSet(helpOption))
    {
        return CLI_PARSE_RESULT_HELP;
    }

    if (parser.isSet(onlyDefaultOption))
    {
        config->onlyDefault = true;
    }
    else
    {
        config->onlyDefault = false;
    }

    if (parser.isSet(verboseOption))
    {
        const QString verbose = parser.value(verboseOption);
        bool conversionValue = false;
        const quint8 verboseValue = verbose.toUInt(&conversionValue);
        if ((verboseValue < 0) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'verbose' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->verboseLevel = verboseValue;
    }
    else
    {
        config->verboseLevel = 0;
    }

    if (parser.isSet(modelOutputOption))
    {
        config->outputModel = parser.value(modelOutputOption);
    }
    else
    {
        config->outputModel = QString::Null();
    }

    if (parser.isSet(nameOption))
    {
        config->boardName = parser.value(nameOption);
    }
    else
    {
        config->boardName = QString::Null();
    }

    if (parser.isSet(cssStyleOption))
    {
        config->styleFile = parser.value(cssStyleOption);
    }
    else
    {
        config->styleFile = QString::Null();
    }

    const QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.isEmpty())
    {
        *errorMessage = "Error: Argument 'source' missing.";
        return CLI_PARSE_RESULT_ERROR;
    }

    if (positionalArguments.size() != 2)
    {
        *errorMessage = "Wrong arguments number specified.";
        return CLI_PARSE_RESULT_ERROR;
    }

    config->schematic  = positionalArguments.at(0);

    // Save aoutput file name and file format
    config->outputFile = positionalArguments.at(1);
    QString ext = QFileInfo(config->outputFile).suffix();
    if (ext == "json")
    {
        config->format = BOM_FORMAT_JSON;
    }
    else if (ext == "html")
    {
        config->format = BOM_FORMAT_HTML;
    }
    else if (ext == "csv")
    {
        config->format = BOM_FORMAT_CSV;
    }
    else
    {
        *errorMessage = "Output file format not supported.";
        return CLI_PARSE_RESULT_ERROR;
    }

    QDir d = QFileInfo(config->schematic).dir();
    config->path = d.path();

    return CLI_PARSE_RESULT_OK;
}

static KiNWEBOM* nweBom;

int main (int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);

    QCommandLineParser parser;
    QString errorMessage;
    Config config;
    parser.setApplicationDescription(QCoreApplication::translate("main",PROJECT_DESCRIPTION));
    switch (parseCommandLine(parser,&config,&errorMessage))
    {
    case CLI_PARSE_RESULT_HELP:
        parser.showHelp();
        Q_UNREACHABLE();
    case CLI_PARSE_RESULT_ERROR:
        fputs(qPrintable("ERROR: "), stderr);
        fputs(qPrintable(errorMessage), stderr);
        fputs("\n\n", stderr);
        fputs(qPrintable(parser.helpText()), stderr);
        return 1;
    case CLI_PARSE_RESULT_OK:
        // Nothing to do!
        // Start parsing...
        break;
    default:
        return 1;
    }

    nweBom = new KiNWEBOM(config);
    return 0;

//    return a.exec();
}
