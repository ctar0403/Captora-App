#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include <QString>
#include <QList>
#include <QPair>


struct Replacement
{
    QString from; // Regex
    QString to;
    Replacement() : from(""), to("") {}
    Replacement(QString _from, QString _to)
        : from(_from), to(_to) {}

};

class PostProcess
{
public:
    PostProcess(QString _ocrLang, bool _keepLineBreaks);
    QString postProcessOcrText(QString text);
    static QString replacementListToStr(QList<Replacement> list);
    static QList<Replacement> strToReplacementList(QString str);
    void setReplacementList(const QList<Replacement> &value);

private:
    QString ocrLang;
    bool keepLineBreaks;
    QList<Replacement> replacementList;

};

#endif // POSTPROCESS_H
