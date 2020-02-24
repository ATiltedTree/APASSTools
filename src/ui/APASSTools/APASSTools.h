#pragma once

#include "common/APASS.h"
#include "common/PRN.h"
#include "common/Settings.h"
#include "common/TDF.h"
#include "ui/AboutDialog/AboutDialog.h"
#include "ui/CSVDialog/CSVDialog.h"
#include "ui/SettingsDialog/SettingsDialog.h"
#include "ui/WebDialog/WebDialog.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressBar>
#include <QTreeWidgetItem>
#include <config.h>

QT_BEGIN_NAMESPACE
namespace Ui {
  class APASSTools;
}
QT_END_NAMESPACE

enum SettingsAction { SaveWindow, RestoreWindow, RestoreValues, Init, Sync };

class APASSTools : public QMainWindow {
  Q_OBJECT

public:
  APASSTools(QWidget* parent = nullptr);
  ~APASSTools();
  void closeEvent(QCloseEvent* event);
  void updateTree();

private slots:
  void onFromCSVFile();
  void onFromWeb();
  void onAbout();
  void onSettings();
  void onClear();
  void onSave();
  void onSaveAs();

private:
  Ui::APASSTools* ui;
  bool unsavedChanges = false;
  APASS apass;
  void setupConnections();
  void changeSettings(SettingsAction action);
  void doImport(QString data);
};
