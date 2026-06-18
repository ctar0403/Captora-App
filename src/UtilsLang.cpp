#include "UtilsLang.h"

bool UtilsLang::languageSupportsVerticalOrientation(QString lang)
{
    return (lang == "Japanese"
            || lang == "Chinese - Simplified"
            || lang == "Chinese - Traditional");
}

bool UtilsLang::languageSupportsFurigana(QString lang)
{
    return (lang == "Japanese");
}
