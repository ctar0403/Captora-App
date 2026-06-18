#include "HotkeyWidget.h"
#include "ui_HotkeyWidget.h"
//#include "Hotkey.h"

HotkeyWidget::HotkeyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotkeyWidget)
{
    ui->setupUi(this);

//    QList<KeyNameCode> keyNameCode = Hotkey::getKeyNameCodes();

//    for(auto item : keyNameCode)
//    {
//        // Don't add reserved hotkeys to list
//        if(item.name != "Enter"
//                && item.name != "Esc"
//                && item.name != "Left"
//                && item.name != "Right"
//                && item.name != "Up"
//                && item.name != "Down"
//                )
//        {
//          ui->comboBoxKeys->addItem(item.name);
//        }
//    }
}

HotkeyWidget::~HotkeyWidget()
{
    delete ui;
}

void HotkeyWidget::setHotkey(QKeySequence hotkey)
{
//    ui->checkBoxCtrl->setChecked(hotkey.getModCtrl());
//    ui->checkBoxShift->setChecked(hotkey.getModShift());
//    ui->checkBoxAlt->setChecked(hotkey.getModAlt());
//    ui->checkBoxWin->setChecked(hotkey.getModWin());
//    ui->comboBoxKeys->setCurrentText(hotkey.getVkCodeName());
    ui->keySequenceEdit->setKeySequence(hotkey);
}

QKeySequence HotkeyWidget::getHotkey()
{
    return ui->keySequenceEdit->keySequence();
//    return Hotkey(ui->checkBoxCtrl->isChecked(),
//                  ui->checkBoxShift->isChecked(),
//                  ui->checkBoxAlt->isChecked(),
//                  ui->checkBoxWin->isChecked(),
//                  Hotkey::keyNameToVkCode(ui->comboBoxKeys->currentText()));
}
