#pragma once

#include "Macros.h"
#include "common/APASS.h"
#include "common/Error.h"
#include "common/PRNFile.h"
#include "common/Settings.h"
#include "common/TDFFile.h"
#include "ui/AboutDialog/AboutDialog.h"
#include "ui/CSVDialog/CSVDialog.h"
#include "ui/SettingsDialog/SettingsDialog.h"
#include "ui/WebDialog/WebDialog.h"
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QProgressBar>
#include <QSpacerItem>
#include <QSpinBox>
#include <QStatusBar>
#include <QToolBar>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <config.h>

const QList<QString> apassValues = {
    "radeg",     "raerr",   "decdeg",  "decerr",  "Johnson_V",   "Verr",    "Vnobs",
    "Johnson_B", "Berr",    "Bnobs",   "Sloan_u", "SUerr",       "SUnobs",  "Sloan_g",
    "SGerr",     "SGnobs",  "Sloan_r", "SRerr",   "SRnobs",      "Sloan_i", "SIerr",
    "SInobs",    "Sloan_z", "SZerr",   "SZnobs",  "PanSTARRS_Y", "Yerr",    "Ynobs"};

namespace Ui {
  class APASSTools {
  public:
    QAction* actionCSV;
    QAction* actionWeb;
    QAction* actionSave;
    QAction* actionSaveAs;
    QAction* actionQuit;
    QAction* actionHelp;
    QAction* actionAbout;
    QAction* actionAboutQt;
    QAction* actionSettings;
    QAction* actionClear;
    QWidget* centralwidget;
    QGridLayout* centralLayout;
    QGroupBox* settingsBox;
    QGridLayout* settingsBoxLayout;
    QDoubleSpinBox* magnitudeSpin;
    QSpinBox* observationSpin;
    QLabel* obsLabel;
    QSpacerItem* horizontalSpacer_2;
    QLineEdit* nameEdit;
    QLabel* nameLabel;
    QLabel* magLabel;
    QTreeWidget* CSVDisplay;
    QToolBar* toolBar;
    QMenuBar* menubar;
    QMenu* menuFile;
    QMenu* menuNewFrom;
    QMenu* menuHelp;
    QStatusBar* statusbar;
    QMainWindow* parent;

    APASSTools(QMainWindow* parent) : parent(parent){};

    void setupUi() {
      actionCSV          = new QAction(parent);
      actionWeb          = new QAction(parent);
      actionSave         = new QAction(parent);
      actionSaveAs       = new QAction(parent);
      actionQuit         = new QAction(parent);
      actionHelp         = new QAction(parent);
      actionAbout        = new QAction(parent);
      actionAboutQt      = new QAction(parent);
      actionSettings     = new QAction(parent);
      actionClear        = new QAction(parent);
      centralwidget      = new QWidget(parent);
      centralLayout      = new QGridLayout(centralwidget);
      settingsBox        = new QGroupBox(centralwidget);
      settingsBoxLayout  = new QGridLayout(settingsBox);
      magnitudeSpin      = new QDoubleSpinBox(settingsBox);
      observationSpin    = new QSpinBox(settingsBox);
      obsLabel           = new QLabel(settingsBox);
      horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
      nameEdit           = new QLineEdit(settingsBox);
      nameLabel          = new QLabel(settingsBox);
      magLabel           = new QLabel(settingsBox);
      CSVDisplay         = new QTreeWidget(centralwidget);
      toolBar            = new QToolBar(parent);
      menubar            = new QMenuBar(parent);
      menuFile           = new QMenu(menubar);
      menuNewFrom        = new QMenu(menuFile);
      menuHelp           = new QMenu(menubar);
      statusbar          = new QStatusBar(parent);
      auto* CSVDisplayHeaderItem = new QTreeWidgetItem();
      auto* icon                 = new QIcon();

      icon->addFile(":/logo", QSize(), QIcon::Mode::Normal, QIcon::State::Off);

      parent->setWindowIcon(*icon);
      parent->addToolBar(Qt::TopToolBarArea, toolBar);
      parent->setCentralWidget(centralwidget);
      parent->setMenuBar(menubar);
      parent->setStatusBar(statusbar);

      actionCSV->setIcon(QIcon::fromTheme("text-csv"));
      actionWeb->setIcon(QIcon::fromTheme("web-browser"));
      actionSave->setIcon(QIcon::fromTheme("filesave"));
      actionSaveAs->setIcon(QIcon::fromTheme("filesaveas"));
      actionQuit->setIcon(QIcon::fromTheme("window-close"));
      actionHelp->setIcon(QIcon::fromTheme("help"));
      actionAbout->setIcon(QIcon::fromTheme("help-about"));
      actionAboutQt->setIcon(QIcon::fromTheme("qt5-logo"));
      actionSettings->setIcon(QIcon::fromTheme("settings"));
      actionClear->setIcon(QIcon::fromTheme("edit-clear"));

      settingsBoxLayout->addWidget(magnitudeSpin, 2, 2, 1, 1);
      settingsBoxLayout->addWidget(observationSpin, 1, 2, 1, 1);
      settingsBoxLayout->addWidget(obsLabel, 1, 0, 1, 1);
      settingsBoxLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);
      settingsBoxLayout->addWidget(nameEdit, 0, 2, 1, 1);
      settingsBoxLayout->addWidget(nameLabel, 0, 0, 1, 1);
      settingsBoxLayout->addWidget(magLabel, 2, 0, 1, 1);

      for (int i = 0; i < apassValues.size(); i++) {
        CSVDisplayHeaderItem->setText(i, apassValues.at(i));
      }

      CSVDisplay->setHeaderItem(CSVDisplayHeaderItem);
      CSVDisplay->setRootIsDecorated(false);
      CSVDisplay->setItemsExpandable(false);
      CSVDisplay->setSortingEnabled(true);

      centralLayout->addWidget(settingsBox, 0, 0, 2, 2);
      centralLayout->addWidget(CSVDisplay, 2, 0, 1, 2);

      toolBar->addAction(actionCSV);
      toolBar->addAction(actionWeb);
      toolBar->addSeparator();
      toolBar->addAction(actionSave);
      toolBar->addAction(actionSaveAs);
      toolBar->addSeparator();
      toolBar->addAction(actionClear);
      toolBar->addSeparator();
      toolBar->addAction(actionSettings);
      toolBar->addAction(actionAbout);

      menuNewFrom->setIcon(QIcon::fromTheme("filenew"));
      menuNewFrom->addAction(actionCSV);
      menuNewFrom->addAction(actionWeb);

      menuFile->addAction(menuNewFrom->menuAction());
      menuFile->addSeparator();
      menuFile->addAction(actionSave);
      menuFile->addAction(actionSaveAs);
      menuFile->addSeparator();
      menuFile->addAction(actionSettings);
      menuFile->addSeparator();
      menuFile->addAction(actionQuit);

      menuHelp->addAction(actionHelp);
      menuHelp->addSeparator();
      menuHelp->addAction(actionAbout);
      menuHelp->addAction(actionAboutQt);

      menubar->addAction(menuFile->menuAction());
      menubar->addAction(menuHelp->menuAction());

      retranslateUi();
    }

    void retranslateUi() {
      parent->setWindowTitle(QCoreApplication::translate("APASSTools", "APASSTools", nullptr));

      actionCSV->setText(QCoreApplication::translate("APASSTools", "CSV File", nullptr));
      actionWeb->setText(QCoreApplication::translate("APASSTools", "Web", nullptr));
      actionSave->setText(QCoreApplication::translate("APASSTools", "Save", nullptr));
      actionSave->setShortcut(QCoreApplication::translate("APASSTools", "Ctrl+S", nullptr));
      actionSaveAs->setText(QCoreApplication::translate("APASSTools", "Save as ...", nullptr));
      actionSaveAs->setShortcut(QCoreApplication::translate("APASSTools", "Ctrl+Shift+S", nullptr));
      actionQuit->setText(QCoreApplication::translate("APASSTools", "Quit", nullptr));
      actionQuit->setShortcut(QCoreApplication::translate("APASSTools", "Ctrl+Q", nullptr));
      actionHelp->setText(QCoreApplication::translate("APASSTools", "Help", nullptr));
      actionHelp->setShortcut(QCoreApplication::translate("APASSTools", "F1", nullptr));
      actionAbout->setText(QCoreApplication::translate("APASSTools", "About", nullptr));
      actionAboutQt->setText(QCoreApplication::translate("APASSTools", "About Qt", nullptr));
      actionSettings->setText(QCoreApplication::translate("APASSTools", "Settings", nullptr));
      actionClear->setText(QCoreApplication::translate("APASSTools", "Clear", nullptr));
      actionClear->setToolTip(QCoreApplication::translate("APASSTools", "Clear preview", nullptr));

      settingsBox->setTitle(QCoreApplication::translate("APASSTools", "Settings", nullptr));
      obsLabel->setText(
          QCoreApplication::translate("APASSTools", "Observation Threshold", nullptr));
      nameLabel->setText(QCoreApplication::translate("APASSTools", "Name", nullptr));
      magLabel->setText(QCoreApplication::translate("APASSTools", "Magnitude Threshold", nullptr));
      menuFile->setTitle(QCoreApplication::translate("APASSTools", "File", nullptr));
      menuNewFrom->setTitle(QCoreApplication::translate("APASSTools", "New from", nullptr));
      menuHelp->setTitle(QCoreApplication::translate("APASSTools", "Help", nullptr));
    } // retranslateUi
  };
} // namespace Ui

enum SettingsAction { SaveWindow, RestoreWindow, RestoreValues, Init, Sync };

class APASSTools : public QMainWindow {
  Q_OBJECT

private slots:
  void onFromCSVFile();
  void onFromWeb();
  void onAbout();
  void onSettings();
  void onClear();
  void onSave();
  void onSaveAs();

public:
  explicit APASSTools(QWidget* parent);
  ~APASSTools() override;
  SMART_PTRS(APASSTools)

  void closeEvent(QCloseEvent* event) override;
  void updateTree();

private:
  Ui::APASSTools* ui;
  bool unsavedChanges = false;
  APASS::Ref apass;
  void setupConnections();
  void changeSettings(SettingsAction action);
  void doImport(const QString& data);
  void doSave(const QString& dirname, bool createTDF);
};
