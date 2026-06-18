#ifndef UTILSIMG_H
#define UTILSIMG_H

#include "OcrEngine.h"
#include "PreProcess.h"

class UtilsImg
{
public:
    static QImage takeScreenshot(const QRect &rect);
    static QString getDebugScreenshotPath(QString filename, bool useTimestamp, QDateTime timestamp);
private:
     UtilsImg() {}
};

#endif // UTILSIMG_H
