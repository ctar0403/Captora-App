#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private slots:
    void on_labelHomePageLink_linkActivated(const QString &link);
    void on_label_8_linkActivated(const QString &link);

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
