#ifndef MOUSEHOOK_H
#define MOUSEHOOK_H

#include <QThread>
#include <QEventLoop>
#include <QDebug>
#include <QMap>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

class MouseHook : public QThread
{
    Q_OBJECT
public:
    void run();

    static const int LEFT_MOUSE_DOWN = 1;
    static const int LEFT_MOUSE_UP = 2;
    static const int RIGHT_MOUSE_DOWN = 3;

    static MouseHook& getInstance()
    {
        static MouseHook instance;
        return instance;
    }
#ifdef Q_OS_WIN
    HHOOK getHHook() const { return hHook; }
#endif

    void setRightMouseButtonHeld(bool held);
    bool getRightMouseButtonHeld();

    void endThread();

signals:
    void buttonPressed(int id);

private:
    bool rightMouseButtonHeld;

#ifdef Q_OS_WIN
    HHOOK hHook;
    bool scribbling = false;

    MouseHook(): hHook(nullptr), rightMouseButtonHeld(false)
    {

    }

    static LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
#endif
};

#endif // MOUSEHOOK_H
