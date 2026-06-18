#include <QGuiApplication>
#include <QPixmap>
#include <QDebug>
#include <QWidget>
#include <QScreen>
#include "UtilsCommon.h"
#include "UtilsImg.h"


QImage UtilsImg::takeScreenshot(const QRect &rect)
{
    QScreen *screen = QGuiApplication::primaryScreen();

    if (!screen)
    {
        return QImage();
    }

    // use width() - 1 and height() - 1 to remove black line on previewbox
    QPixmap capturePixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width() - 1, rect.height() - 1);

    return capturePixmap.toImage();
}

QString UtilsImg::getDebugScreenshotPath(QString filename, bool useTimestamp, QDateTime timestamp)
{
    if(useTimestamp)
    {
        QString timestampStr = UtilsCommon::timestampToStr(timestamp);
        filename = filename.replace(".png", "");
        return UtilsCommon::getAppDir(true) + filename + "_" + timestampStr + ".png";
    }
    else
    {
        return UtilsCommon::getAppDir(true) + filename;
    }
}
