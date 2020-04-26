#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::SettingsDialog(this)) {
  ui->setupUi();
  connect(this->ui->buttons->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
          &SettingsDialog::onApply);
  connect(this->ui->buttons->button(QDialogButtonBox::Ok), &QPushButton::clicked, this,
          &SettingsDialog::onOK);
  connect(this->ui->buttons->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this,
          &SettingsDialog::reject);

  this->getSettings();
}

SettingsDialog::~SettingsDialog() {
  delete ui;
}

void SettingsDialog::getSettings() {
  this->ui->createTDFCheck->setChecked(Settings::appSettings.createTDFFile);
  this->ui->savePathEdit->setText(Settings::appSettings.defaultSaveDir);
  this->ui->obsSpin->setValue(Settings::appSettings.observationThreshold);
  this->ui->magSpin->setValue(Settings::appSettings.magnitudeThreshold);
  this->ui->createTDFCheck->setChecked(Settings::appSettings.createTDFFile);
}

void SettingsDialog::saveSettings() {
  Settings::appSettings.createTDFFile        = this->ui->createTDFCheck->isChecked();
  Settings::appSettings.defaultSaveDir       = this->ui->savePathEdit->text();
  Settings::appSettings.observationThreshold = this->ui->obsSpin->value();
  Settings::appSettings.magnitudeThreshold   = this->ui->magSpin->value();
  Settings::appSettings.createTDFFile        = this->ui->createTDFCheck->isChecked();
}

void SettingsDialog::onApply() {
  this->saveSettings();
}

void SettingsDialog::onOK() {
  this->saveSettings();
  this->accept();
}

void SettingsDialog::onChangeSaveLocation() {
  QString dirname = QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
  this->ui->savePathEdit->setText(dirname);
}
