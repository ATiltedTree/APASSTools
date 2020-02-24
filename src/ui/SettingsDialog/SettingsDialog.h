#pragma once

#include "common/Settings.h"
#include <QDialog>
#include <QFileDialog>
#include <QPushButton>

namespace Ui {
  class SettingsDialog;
}

class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  SettingsDialog(QWidget* parent = nullptr);
  ~SettingsDialog();
  void getSettings();
  void saveSettings();

private slots:
  void onApply();
  void onOK();
  void onChangeSaveLocation();

private:
  Ui::SettingsDialog* ui;
};
