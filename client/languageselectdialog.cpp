#include <QDesktopWidget>

#include "languageselectdialog.h"
#include "ui_languageselectdialog.h"
#include "defines.h"

LanguageSelectDialog::LanguageSelectDialog(QSettings *settings, QMap<QString, QString> &languages, QWidget *parent)
    : QDialog(parent)
    , _settings(settings)
    , _languages(languages)
    , ui(new Ui::LanguageSelectDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setGeometry(QDesktopWidget().availableGeometry().center().x() - (this->width() / 2),
                      QDesktopWidget().availableGeometry().center().y() - (this->height() / 2),
                       this->width(), this->height());
    showTypes();
    QString sourcestype = _settings->value("general/sourcetype", DEFAULT_SOURCES_TYPE).toString();
    int srcIndex = ui->comboLanguageType->findData(sourcestype);
    if (srcIndex != -1) {
        ui->comboLanguageType->setCurrentIndex(srcIndex);
    }
}

LanguageSelectDialog::~LanguageSelectDialog()
{
    delete ui;
}

void LanguageSelectDialog::showTypes()
{
    for (QMap<QString, QString>::iterator i = _languages.begin(); i != _languages.end(); i++) {
        ui->comboLanguageType->addItem(i.value(), i.key());
    }
}

void LanguageSelectDialog::on_buttonBox_accepted()
{
    _settings->setValue("general/sourcetype" ,ui->comboLanguageType->itemData(ui->comboLanguageType->currentIndex()).toString());
}
