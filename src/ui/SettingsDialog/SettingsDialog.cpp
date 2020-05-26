#include "SettingsDialog.hpp"

SettingsDialog::SettingsDialog(QWidget *parent, Settings *settings)
    : QDialog(parent), ui(new Ui::SettingsDialog(this)), settings(settings) {
  ui->setupUi();
  connect(this->ui->buttons->button(QDialogButtonBox::Apply),
          &QPushButton::clicked, this, &SettingsDialog::onApply);
  connect(this->ui->buttons->button(QDialogButtonBox::Ok),
          &QPushButton::clicked, this, &SettingsDialog::onOK);
  connect(this->ui->buttons->button(QDialogButtonBox::Cancel),
          &QPushButton::clicked, this, &SettingsDialog::reject);

  this->getSettings();
}

void SettingsDialog::getSettings() {
  this->ui->createTDFCheck->setChecked(
      this->settings->appSettings.createTDFFile);
  this->ui->savePathEdit->setText(this->settings->appSettings.defaultSaveDir);
  this->ui->obsSpin->setValue(this->settings->appSettings.observationThreshold);
  this->ui->magSpin->setValue(this->settings->appSettings.magnitudeThreshold);
  this->ui->createTDFCheck->setChecked(
      this->settings->appSettings.createTDFFile);
}

void SettingsDialog::saveSettings() {
  this->settings->appSettings.createTDFFile =
      this->ui->createTDFCheck->isChecked();
  this->settings->appSettings.defaultSaveDir = this->ui->savePathEdit->text();
  this->settings->appSettings.observationThreshold = this->ui->obsSpin->value();
  this->settings->appSettings.magnitudeThreshold = this->ui->magSpin->value();
  this->settings->appSettings.createTDFFile =
      this->ui->createTDFCheck->isChecked();
}

void SettingsDialog::onApply() {
  this->saveSettings();
}

void SettingsDialog::onOK() {
  this->saveSettings();
  this->accept();
}

void SettingsDialog::onChangeSaveLocation() {
  QString dirname =
      QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
  this->ui->savePathEdit->setText(dirname);
}
