#include <QFile>
#include <QTextStream>

#include "titleblock.h"
#include "utils/wlog.h"

TitleBlock::TitleBlock () {}

TitleBlock::TitleBlock(Config config)
{
    WLog& log = WLog::instance();

    QFile sch(config.schematic);
    if (sch.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        QTextStream in(&sch);

        QRegularExpression titleExp = getParsingExpression();
        bool isTitleOpen = false;
        QList<QString> titleContent;

        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();

            // Sheet parsing...
            QRegularExpressionMatch match = titleExp.match(line);
            if (match.hasMatch() && (isTitleOpen == false))
            {
                isTitleOpen = true;
                titleContent.clear();
                log.log(QString("Start Title Block..."),2);
                continue;
            }
            else if (match.hasMatch() && (isTitleOpen == true))
            {
                // Close the sheet parsing and create new object
                isTitleOpen = false;
                parse(titleContent,config);
                log.log(QString("Close Title Block."),2);
                break;
            }

            // Add new element to sheet description tag
            if (isTitleOpen)
            {
                titleContent.append(line);
            }
        }

        // Close file...
        sch.close();

        mBoardName = config.boardName;
    }
    else
    {
//TODO
    }
}

void TitleBlock::parse (QList<QString> params, Config config)
{
    WLog& log = WLog::instance();

    QList<QString>::iterator i;
    for (i = params.begin(); i != params.end(); ++i)
    {
        QString temp = *i;

        if (temp.startsWith("Title "))
        {
            // Save the title...
            mTitle = temp.remove("Title ");
            mTitle.remove('\"');
        }
        else if (temp.startsWith("Comp "))
        {
            mCompany = temp.remove("Comp ");
            mCompany.remove('\"');
        }
        else if (temp.startsWith("Date "))
        {
            mDate = temp.remove("Date ");
            mDate.remove('\"');
        }
        else if (temp.startsWith("Rev "))
        {
            mRevision = temp.remove("Rev ");
            mRevision.remove('\"');
        }
        else if (temp.startsWith("Comment1 "))
        {
            mComment1 = temp.remove("Comment1 ");
            mComment1.remove('\"');
        }
        else if (temp.startsWith("Comment2 "))
        {
            mComment2 = temp.remove("Comment2 ");
            mComment2.remove('\"');
        }
        else if (temp.startsWith("Comment3"))
        {
            mComment3 = temp.remove("Comment3 ");
            mComment3.remove('\"');
        }
        else if (temp.startsWith("Comment4"))
        {
            mComment4 = temp.remove("Comment4 ");
            mComment4.remove('\"');
        }
    }

    log.log(QString("TitleBlock - Title    : " + mTitle),3);
    log.log(QString("TitleBlock - Company  : " + mCompany),3);
    log.log(QString("TitleBlock - Revision : " + mRevision),3);
    log.log(QString("TitleBlock - Date     : " + mDate),3);
    log.log(QString("TitleBlock - Comment1 : " + mComment1),3);
    log.log(QString("TitleBlock - Comment2 : " + mComment2),3);
    log.log(QString("TitleBlock - Comment3 : " + mComment3),3);
    log.log(QString("TitleBlock - Comment4 : " + mComment4),3);
}

QString TitleBlock::getBoardTitle (void) const
{
    return mTitle;
}

QList<QString> TitleBlock::getComments (void) const
{
    QList<QString> comments;
    comments << mComment1;
    comments << mComment2;
    comments << mComment3;
    comments << mComment4;

    return comments;
}

QString TitleBlock::getBoardRevision (void) const
{
    return mRevision;
}

QString TitleBlock::getDate (void) const
{
    return mRevision;
}

QString TitleBlock::getCompany (void) const
{
    return mCompany;
}

QString TitleBlock::getBoardName (void) const
{
    return mBoardName;
}
