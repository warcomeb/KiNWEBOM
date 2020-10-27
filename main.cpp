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
            QCoreApplication::translate("main", "Enable verbose output"));
    parser.addOption(verboseOption);

    const QCommandLineOption onlyDefaultOption(QStringList() << "o" << "only-default",
            QCoreApplication::translate("main", "Parse only default parameters"));
    parser.addOption(onlyDefaultOption);

    const QCommandLineOption parseTypeOption(QStringList() << "p" << "parse-model",
            QCoreApplication::translate("main", "Parse <model> type for components (JSON file)"),
            QCoreApplication::translate("main", "model"));
    parser.addOption(parseTypeOption);

    parser.addPositionalArgument("source", QCoreApplication::translate("main", "The schematic main (.sch) file."));


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

    const QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.isEmpty())
    {
        *errorMessage = "Error: Argument 'source' missing.";
        return CLI_PARSE_RESULT_ERROR;
    }

    if (positionalArguments.size() > 1)
    {
        *errorMessage = "Several arguments specified.";
        return CLI_PARSE_RESULT_ERROR;
    }

    config->schematic = positionalArguments.at(0);

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
