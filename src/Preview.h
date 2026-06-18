#ifndef PREVIEW_H
#define PREVIEW_H

#include <QtWidgets>
#include <QDialog>
#include <QFont>
#include <QTimer>

class Preview : public QWidget
{
        Q_OBJECT
public:
    Preview();
    void setText(const QString &text);
    QString getText();
    void setTextColor(const QColor &color);
    void setBackgroundColor(const QColor &color);
    void setBorderColor(const QColor &color);
    void setTextFont(const QFont &font);
    int getBoxHeight();
    void hideAndReset();
    void showInfo(QString text);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void infoTimeout();

    const int horizontalPadding = 10;
    const int verticalPadding = 6;

    QString previewText;
    QColor textColor;
    QColor backgroundColor;
    QColor borderColor;
    QFont textFont;
    QTimer infoTimer;
};

#endif // PREVIEW_H
