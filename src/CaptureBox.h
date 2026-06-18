#ifndef CAPTURE_BOX_H
#define CAPTURE_BOX_H

#include <QtWidgets>
#include <QDialog>
#include <QTimer>

class CaptureBox : public QWidget
{
    Q_OBJECT
public:
    CaptureBox();
    ~CaptureBox();

    void startCaptureMode();
    void endCaptureMode();
    void updateCaptureMode();

    void autoCapture(QRect &rect);

    QRect getCaptureRect();

    void setBackgroundColor(const QColor &value) { backgroundColor = value; }
    void setUseBackgroundColor(bool value) { useBackgroundColor = value; }

    bool getUseBorder() const  { return useBorder; }
    void setUseBorder(bool value) { useBorder = value; }

    QColor getBorderColor() const { return borderColor; }
    void setBorderColor(const QColor &value) { borderColor = value; }

public slots:
    void turnOnBackground() { useBackgroundColor = true; repaint(); }
    void turnOffBackground() { useBackgroundColor = false; repaint(); }

signals:
    void captured();
    void moved();
    void stoppedMoving();
    void cancel();

protected:
    void paintEvent(QPaintEvent *event);

private:
    enum HotkeyAction
    {
        CANCEL = 100,
        CAPTURE,
        CAPTURE2,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    static const int captureModeUpdateMilliSec = 10;
    static const int moveTimeoutMilliSec = 400;

    void autoCaptureTimeout();
    void moveTimeout();
    void startMoveTimer();
    void hotkeyPressed(int id);

    QTimer timerUpdateCaptureMode;

    QPoint captureModePivot;
    QSize moveCaptureBoxSize;
    QPoint captureModeLastPt;

    // Capture interaction state machine:
    //   IDLE        - not active
    //   ARMED       - OCR hotkey pressed; waiting for the first left-click
    //   FIRST_DOWN  - first left button is down (anchor set, rubber-banding)
    //   WAIT_SECOND - first click released without dragging; waiting to finish
    //   SECOND_DOWN - second left button is down (click or drag to finish)
    // Finish (run OCR) happens on a first-click drag-release, on a second click,
    // or on a second-click drag-release. Esc cancels from any active state.
    enum CaptureState
    {
        CS_IDLE,
        CS_ARMED,
        CS_FIRST_DOWN,
        CS_WAIT_SECOND,
        CS_SECOND_DOWN
    };

    static const int dragThresholdPx = 5;

    CaptureState captureState = CS_IDLE;
    QPoint firstDownPos;

    // Tracks whether we pushed an override (crosshair) cursor, so endCaptureMode
    // pops it exactly once even if called more than once.
    bool cursorOverridden = false;

    void beginSelection();
    void finishSelection();

    bool useBackgroundColor;
    QColor backgroundColor;

    bool useBorder;
    QColor borderColor;

    QTimer autoCaptureTimer;
    QPoint dragPosition;

    QTimer moveTimer;
};

#endif // CAPTURE_BOX_H
