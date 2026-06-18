#ifndef POPUPDIALOG_H
#define POPUPDIALOG_H

#include <QDialog>
#include "Translate.h"

namespace Ui {
class PopupDialog;
}

class PopupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PopupDialog(QWidget *parent = 0);
    ~PopupDialog();
    void setText(QString ocrText, QString translation);
    QString getOcrText();
    void setTopmost(bool topmost);

private slots:
    void on_PopupDialog_accepted();
    void on_PopupDialog_finished(int result);
    void on_checkBoxTopmost_toggled(bool checked);

    void on_labelFont_linkActivated(const QString &link);

    void on_pushButtonTranslate_clicked();

    void on_pushButtonSpeech_clicked();

protected:
    void showEvent(QShowEvent *event);

private:
    void translationComplete(QString phrase, QString translation, bool error);

    Ui::PopupDialog *ui;
    bool settingTopmost;
    Translate translate;
};

#endif // POPUPDIALOG_H
