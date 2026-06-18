#include <QRegularExpression>
#include "PostProcess.h"
#include <QDebug>

PostProcess::PostProcess(QString _ocrLang, bool _keepLineBreaks)
    : ocrLang(_ocrLang),
      keepLineBreaks(_keepLineBreaks)
{

}

QString PostProcess::postProcessOcrText(QString text)
{
    if(!keepLineBreaks)
    {
        if(ocrLang == "Japanese"
                || ocrLang == "Chinese - Simplified"
                || ocrLang == "Chinese - Traditional")
        {
            text.replace("\n", "");
            text.replace("\r", "");
        }
        else
        {
            text.replace("\r\n", " ");
            text.replace("\n", " ");
            text.replace("\r", " ");
        }
    }

    text = text.trimmed();
    text.replace("\n\n", "\n");
    if(ocrLang == "Japanese"
            || ocrLang == "Chinese - Simplified"
            || ocrLang == "Chinese - Traditional")
    {
        text.replace(" ", "");
    }

    // Replace nuisance ligatures
    text.replace("ﬁ", "fi");
    text.replace("ﬂ", "fl");

    for(auto item : replacementList)
    {
        QString to(item.to);
        to.replace("\\t", "\t");
        to.replace("\\r", "\r");
        to.replace("\\n", "\n");
        text.replace(QRegularExpression(item.from), to);
    }

    return text;
}

QString PostProcess::replacementListToStr(QList<Replacement> list)
{
    QString str;

    for(auto item : list)
    {
        str += item.from + "\x1F" + item.to + "\x1F";
    }

    return str;
}


QList<Replacement> PostProcess::strToReplacementList(QString str)
{
    QList<Replacement> list;
    QStringList fields = str.split("\x1F",  QString::KeepEmptyParts);

    Replacement replacement;
    bool addFirst = true;

    for(auto item : fields)
    {
        if(addFirst)
        {
            replacement.from = item;
        }
        else
        {
            replacement.to = item;
            list.append(replacement);
        }

        addFirst = !addFirst;
    }

    return list;
}

void PostProcess::setReplacementList(const QList<Replacement> &value)
{
    replacementList = value;
}



