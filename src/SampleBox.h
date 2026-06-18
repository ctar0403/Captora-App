#ifndef SAMPLEBOX_H
#define SAMPLEBOX_H

#include <QWidget>

class SampleBox : public QWidget
{
    Q_OBJECT

public:
    explicit SampleBox(QWidget *parent = 0);

    void setText(const QString &text) { previewText = text; }

    void setTextColor(const QColor &color) { textColor = color; }
    QColor getTextColor() { return textColor; }

    void setBackgroundColor(const QColor &color) { backgroundColor = color; }
    QColor getBackgroundColor() { return backgroundColor; }

    void setBorderColor(const QColor &color) { borderColor = color; }
    QColor getBorderColor() { return borderColor; }

    void setTextFont(const QFont &font) { textFont = font; }
    QFont getTextFont() { return textFont; }

    void setIsCaptureBoxSample(bool value) { isCaptureBoxSample = value; } // False = Preview sample

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    void drawCheckerboard(QPainter &painter);

    const int horizontalPadding = 10;
    const int verticalPadding = 6;

    QString previewText;
    QColor textColor;
    QColor backgroundColor;
    QColor borderColor;
    QFont textFont;
    bool isCaptureBoxSample;
};

#endif // SAMPLEBOX_H
