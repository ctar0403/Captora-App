#ifndef PRE_PROCESS_H
#define PRE_PROCESS_H

#include <QImage>
#include "allheaders.h"
// Leptonica >= 1.83 moved the Box/Boxa/... struct definitions out of the public
// headers (pix.h only forward-declares them) into pix_internal.h. This code uses
// BOX by value and accesses its members directly, so pull in the internal header
// when it exists. Guarded so older Leptonica (where the struct is still public)
// keeps building.
#if defined(__has_include)
#  if __has_include("pix_internal.h")
#    include "pix_internal.h"
#  endif
#endif
#include "PreProcessCommon.h"

class PreProcess
{
public:
    PreProcess();

    bool getVerticalText() const;
    void setVerticalOrientation(bool value);

    bool getRemoveFurigana() const;
    void setRemoveFurigana(bool value);

    int getJapNumTextLines() const;

    QRect getBoundingRect() const;

    float getScaleFactor() const;
    void setScaleFactor(float value);

    PIX *convertImageToPix(QString imageFile);
    PIX *convertImageToPix(QImage &image);

    PIX *processImage(PIX *pixs, bool performDeskew=false, bool trim=false);
    PIX *extractTextBlock(PIX *pixs, int pt_x, int pt_y, int lookahead, int lookbehind, int searchRadius);
    PIX *extractBubbleText(PIX *pixs, int pt_x, int pt_y);

private:
    PIX *makeGray(PIX *pixs);
    PIX *scale(PIX *pixs);
    PIX *unsharpMask(PIX *pixs);
    PIX *binarize(PIX *pixs);
    PIX *scaleUnsharpBinarize(PIX *pixs);
    PIX *deskew(PIX *pixs);
    PIX *addBorder(PIX *pixs);
    PIX *removeNoise(PIX *pixs);
    PIX *eraseFurigana(PIX *pixs);
    void setDPI(PIX *pixs);

    void debugMsg(QString str, bool error=true);
    void debugImg(QString filename, PIX *pixs);

#ifdef QT_DEBUG
//    const bool debug = false;
    const bool debug = true;
#endif

    // From 0.0 to 1.0, with 0 being all white and 1 being all black
//    const float darkBgThreshold = 0.5f;
    const float darkBgThreshold = 0.6f;

    // Amount to scale input image to meet OCR engine minimum DPI requirements
    float scaleFactor = 3.5f;

    // Is the text vertical (affects furigana removal)
    bool verticalText;

    // The last bounding rect extracted.
    // Set in extractTextBlock() and extractBubbleText().
    // Can be used for display purposes.
    BOX boundingRect;

    bool removeFurigana;

    // Number of lines detected when last furigana removal was performed
    int japNumTextLines = 0;

    int debugImgCount = 0;
};

#endif // PRE_PROCESS_H
