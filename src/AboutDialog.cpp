#include <QDesktopServices>
#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    setWindowFlags(windowFlags()
                   & ~Qt::WindowContextHelpButtonHint
                   | Qt::WindowMinMaxButtonsHint);

    ui->setupUi(this);

    ui->labelVersion->setText(QCoreApplication::applicationVersion());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_labelHomePageLink_linkActivated(const QString &)
{
    QDesktopServices::openUrl(QUrl("http://capture2text.sourceforge.net"));
}

void AboutDialog::on_label_8_linkActivated(const QString &)
{
    QDesktopServices::openUrl(QUrl("https://sourceforge.net/p/capture2text/tickets/"));
}
