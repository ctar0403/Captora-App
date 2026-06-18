#include "MouseHook.h"

void MouseHook::run()
{
#ifdef Q_OS_WIN
    if(hHook == nullptr)
    {
        hHook = SetWindowsHookEx(WH_MOUSE_LL, hookProc, nullptr, 0);

        if (hHook == nullptr)
        {
            qDebug() << "Mouse Hook Failed!";
            return;
        }

        // qDebug() << "Mouse hooked";
    }
#endif

    QEventLoop eventLoop;
    eventLoop.exec();
}

void MouseHook::endThread()
{
#ifdef Q_OS_WIN
    if(hHook != nullptr)
    {
        UnhookWindowsHookEx(hHook);
        hHook = nullptr;
        // qDebug() << "Mouse Unhooked";
    }
#endif

    exit(0);
}

void MouseHook::setRightMouseButtonHeld(bool held)
{
    rightMouseButtonHeld = held;
}

bool MouseHook::getRightMouseButtonHeld()
{
    return rightMouseButtonHeld;
}

#ifdef Q_OS_WIN
LRESULT CALLBACK MouseHook::hookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode < 0)
    {
        return CallNextHookEx(MouseHook::getInstance().getHHook(), nCode, wParam, lParam);
    }

    if(wParam == WM_LBUTTONDOWN)
    {
        // qDebug() << "Left mouse down";
        emit MouseHook::getInstance().buttonPressed(MouseHook::LEFT_MOUSE_DOWN);
        return 1;
    }
    else if(wParam == WM_LBUTTONUP)
    {
        // qDebug() << "Left mouse up";
        emit MouseHook::getInstance().buttonPressed(MouseHook::LEFT_MOUSE_UP);
        return 1;
    }
    else if(wParam == WM_RBUTTONDOWN)
    {
        // qDebug() << "Right mouse down";
        MouseHook::getInstance().setRightMouseButtonHeld(true);
        emit MouseHook::getInstance().buttonPressed(MouseHook::RIGHT_MOUSE_DOWN);
        return 1;
    }
    else if(wParam == WM_RBUTTONUP)
    {
        // qDebug() << "Right mouse up";
        MouseHook::getInstance().setRightMouseButtonHeld(false);
        return 1;
    }

    return CallNextHookEx(MouseHook::getInstance().getHHook(), nCode, wParam, lParam);
}
#endif
