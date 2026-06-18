#ifndef UTILSLANG_H
#define UTILSLANG_H

#include <QString>

class UtilsLang
{
public:
    static bool languageSupportsVerticalOrientation(QString lang);
    static bool languageSupportsFurigana(QString lang);
private:
    UtilsLang() { }
};

#endif // UTILSLANG_H
