#ifndef FURIGANA_H
#define FURIGANA_H

#include "allheaders.h"
// Leptonica >= 1.83 hides the Pix/Box struct internals (see note in PreProcess.h);
// pull in pix_internal.h when present so their members can be accessed directly.
#if defined(__has_include)
#  if __has_include("pix_internal.h")
#    include "pix_internal.h"
#  endif
#endif

class Furigana
{
public:

    static bool eraseFuriganaVertical(PIX *pixs, float scaleFactor, int *numTextLines);
    static bool eraseFuriganaHorizontal(PIX *pixs, float scaleFactor, int *numTextLines);

private:
    // Span of lines that contain foreground text. Used during furigana removal.
    struct FuriganaSpan
    {
        int start;
        int end;

        int getLength() { return abs(end - start) + 1; }

        FuriganaSpan(int s, int e)
        {
          start = s;
          end = e;
        }
    };

    Furigana();

    // Minimum number of foreground pixels that a line must contain for it to be part of a span.
    // Needed because sometimes furigana does not have a perfect gap between the text and itself.
    static const float FURIGANA_MIN_FG_PIX_PER_LINE;

    // Minimum width of a span (in pixels) for it to be included in the span list.
    static const float FURIGANA_MIN_WIDTH;

    static bool eraseAreaLeftToRight(PIX *pixs, int x, int width);
    static bool eraseAreaTopToBottom(PIX *pixs, int y, int height);

    static bool averageLargestSpans(PIX *pixs, float scaleFactor);


};

#endif // FURIGANA_H
