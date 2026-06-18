#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QString>
#include <QMap>

class Translate : public QObject
{
    Q_OBJECT
public:
    Translate();
    bool startTranslate(QString keyword, QString from, QString to, int timeoutMillisec);
    static QStringList getAvailableLangs();
    static bool isValidLang(QString lang);

signals:
    void translationComplete(QString phrase, QString translation, bool error);

private:
    static QMap<QString, QString> populateLangMap();
    void requestFinished(QNetworkReply *data);

    static const QMap<QString, QString> mapLang; // Key = Lang name, Value = Two-letter code
    QNetworkAccessManager manager;
    QMap<QString, QString> requestMap; // Key = URL, Value = phrase.
};

#endif // TRANSLATE_H
