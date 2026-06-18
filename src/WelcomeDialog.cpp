#include <QDesktopServices>
#include <QUrl>
#include "WelcomeDialog.h"
#include "ui_WelcomeDialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    setWindowFlags(windowFlags()
                   & ~Qt::WindowContextHelpButtonHint);

    ui->setupUi(this);
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}

void WelcomeDialog::on_labelHello_linkActivated(const QString &)
{
    QDesktopServices::openUrl(QUrl("http://capture2text.sourceforge.net"));
}
