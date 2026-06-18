#ifndef OCR_ENGINE_H
#define OCR_ENGINE_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QMutex>
#include <QRect>

#include "tesseract/baseapi.h"
#include "allheaders.h"
// Leptonica >= 1.83 hides the Pix/Box struct internals (see note in PreProcess.h);
// pull in pix_internal.h when present so their members can be accessed directly.
#if defined(__has_include)
#  if __has_include("pix_internal.h")
#    include "pix_internal.h"
#  endif
#endif


class OcrEngine
{
public:
    OcrEngine();
    ~OcrEngine();
public:
    static QStringList getInstalledLangs();
    static bool isLangInstalled(QString lang);
    static QString getFirstInstalledLang();
    bool setLang(QString lang);
    QString performOcr(PIX *pixs, bool singleLine);

    QString getLang() { return lang; }
    bool getVerticalOrientation() const { return verticalOrientation; }
    void setVerticalOrientation(bool value) { verticalOrientation = value; }

    static QString altLangToLang(QString ocrLang);

    QString getWhitelist() const { return whitelist; }
    void setWhitelist(const QString &value) { whitelist = value; }

    QString getBlacklist() const { return blacklist; }
    void setBlacklist(const QString &value) { blacklist = value; }

    QString getConfigFile() const { return configFile; }
    void setConfigFile(const QString &value) { configFile = value.trimmed(); }

private:
    bool isLangCodeInstalled(QString langCode);

    static QMap<QString, QString> populateLangMap();
    static QMap<QString, QString> populateCodeMap();
    static QMap<QString, QString> populateAltLangMap();

    QMutex mutex;
    QString lang;
    bool verticalOrientation = false;
    QString whitelist;
    QString blacklist;
    QString configFile;

    tesseract::TessBaseAPI *tessApi;
    static const QMap<QString, QString> mapLang; // Key = Lang name, Value = Tesseract Code
    static const QMap<QString, QString> mapCode; // Key = Tesseract Code, Value = Lang name
    static const QMap<QString, QString> mapLangAlt; // Key = Alt Lang name, Value = Lang name

};

#endif // OCR_ENGINE_H
