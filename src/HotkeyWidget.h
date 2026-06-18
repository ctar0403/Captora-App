#ifndef HOTKEYWIDGET_H
#define HOTKEYWIDGET_H

#include <QWidget>
#include <QKeySequence>
//#include "Hotkey.h"

namespace Ui {
class HotkeyWidget;
}

class HotkeyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HotkeyWidget(QWidget *parent = 0);
    ~HotkeyWidget();
    void setHotkey(QKeySequence hotkey);
    QKeySequence getHotkey();
//    void setHotkey(Hotkey hotkey);
//    Hotkey getHotkey();


private:
    Ui::HotkeyWidget *ui;
};

#endif // HOTKEYWIDGET_H
