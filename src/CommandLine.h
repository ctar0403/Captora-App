#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QDateTime>
#include "OcrEngine.h"
#include "PreProcess.h"

class CommandLine
{
public:
    CommandLine();
    ~CommandLine();
    bool process(QCoreApplication &app);

#ifndef CLI_BUILD
    bool getPortable() const { return portable; }
#endif

private:
    void showInstalledLanguages();
    QString ocrImageFile(QString img);
    void ocrImageFiles(QStringList &imgList);
    void ocrFileOfImages(QString imagesFile);
    QString postProcessText(QString ocrText);
    bool convertStringToRect(QString str, QRect &rect);
    QString ocrScreenRect(QRect rect);
    QImage takeScreenshot(QRect rect);
    void outputOcrText(QString ocrText);
    void outputToFile(QString ocrText);
    void outputToConsole(QString ocrText);
    void ocrImageFileAndOutput(QString img);
    void ocrScreenRectAndOutput(QRect rect);
    QString getDebugImagePath(QString filename);

    QString outputFilePath;
    QString outputFormat;
    PreProcess imagePreprocessor;
    OcrEngine *ocrEngine;
    bool debug;
    bool debugAppendTimestamp;
    bool keepLineBreaks;
    bool copyToClipboard;
    bool preprocessTrim;
    bool preprocessDeskew;
    QDateTime captureTimestamp;
    QFile outputFile;
    QString currentImageFile;
    QString allOcrText; // Used to output to clipoard

#ifndef CLI_BUILD
    bool portable;
#endif

};

#endif // COMMANDLINE_H
