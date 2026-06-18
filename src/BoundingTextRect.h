#ifndef BOUNDING_TEXT_RECT_H
#define BOUNDING_TEXT_RECT_H

#include <QList>
#include "allheaders.h"
// Leptonica >= 1.83 hides the Box struct internals (see note in PreProcess.h);
// pull in pix_internal.h when present so BOX can be used/returned by value.
#if defined(__has_include)
#  if __has_include("pix_internal.h")
#    include "pix_internal.h"
#  endif
#endif
#include "PreProcessCommon.h"


class BoundingTextRect
{
public:
    enum class D8
    {
      Top,
      TopRight,
      Right,
      BottomRight,
      Bottom,
      BottomLeft,
      Left,
      TopLeft
    };

    struct DirDist
    {
      D8 dir;
      int dist;

      DirDist(D8 _dir, int _dist)
          : dir(_dir), dist(_dist) { }
    };

    static BOX getBoundingRect(PIX *pixs, int startX, int startY, bool vertical,
                               int lookahead, int lookbehind, int maxSearchDist);

    static MyPoint findNearestBlackPixel(PIX *pixs, int startX, int startY, int max_dist);
    static bool isBlack(PIX *pixs, int x, int y);
    static bool inRangeX(PIX *pixs, int x);
    static bool inRangeY(PIX *pixs, int y);
    static bool lineContainBlackHoriz(PIX *pixs, int startX, int startY, int width);
    static bool lineContainBlackVert(PIX *pixs, int startX, int startY, int height);

private:
    BoundingTextRect();

    static bool tryExpandRect(PIX *pixs, BOX *rect, D8 dir, int dist);
    static void expandRect(PIX *pixs, QList<DirDist> &dirDistList, BOX *rect, bool keep_going);
};

#endif // BOUNDING_TEXT_RECT_H
