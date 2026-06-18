#include <QCoreApplication>
#include <QDir>
#include <QTextStream>

#ifndef CLI_BUILD
    #include <QColorDialog>
    #include <QFontDialog>
#endif

#include "UtilsCommon.h"

#ifndef CLI_BUILD
QColor UtilsCommon::pickColor(QColor initialColor)
{
    QColor color = QColorDialog::getColor(initialColor,
                                          nullptr, "Select Color", QColorDialog::ShowAlphaChannel);
    if(!color.isValid())
    {
        return initialColor;
    }

    return color;
}

QFont UtilsCommon::pickFont(QFont initialFont)
{
    bool fontValid = false;
    QFont font = QFontDialog::getFont(&fontValid, initialFont, nullptr, "Select Font");

    if(!fontValid)
    {
        return initialFont;
    }

    return font;
}
#endif


QString UtilsCommon::timestampToStr(QDateTime timestamp)
{
    return timestamp.toString("yyyyMMdd_hhmmsszzz");
}

QString UtilsCommon::getAppDir(bool appendSlash)
{
    if(appendSlash)
    {
        return QCoreApplication::applicationDirPath() + QDir::separator();
    }
    else
    {
        return QCoreApplication::applicationDirPath();
    }
}

QString UtilsCommon::formatLogLine(QString format, QString ocrText, QDateTime timestamp, QString translation, QString file)
{
    QString line = format;
    line.replace("${tab}", "\t");
    line.replace("${linebreak}", "\n");
    line.replace("${}", timestampToStr(timestamp));
    line.replace("${file}", file);
    line.replace("${translation}", translation);
    line.replace("${capture}", ocrText);
    return line;
}

void UtilsCommon::writeTextFile(QString file, QString text, bool append)
{
    QFile theFile(file);
    QIODevice::OpenMode mode = QIODevice::WriteOnly | QIODevice::Text;

    if(append)
    {
        mode |= QIODevice::Append;
    }

    if (theFile.open(mode))
    {
        QTextStream stream(&theFile);
        stream.setCodec("UTF-8");
        stream.setGenerateByteOrderMark(true);
        stream << text;
        theFile.close();
    }
}
