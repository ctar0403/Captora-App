#ifndef UTILSCOMMON_H
#define UTILSCOMMON_H

#include <QDateTime>

#ifndef CLI_BUILD
    #include <QColor>
    #include <QFont>
#endif

class UtilsCommon
{
public:
    #ifndef CLI_BUILD
    static QColor pickColor(QColor initialColor);
    static QFont pickFont(QFont initialFont);
    #endif
    static QString timestampToStr(QDateTime timestamp);
    static QString getAppDir(bool appendSlash);
    static QString formatLogLine(QString format, QString ocrText, QDateTime timestamp, QString translation, QString file);
    static void writeTextFile(QString file, QString text, bool append=false);
private:
    UtilsCommon() { }
};

#endif // UTILSCOMMON_H
