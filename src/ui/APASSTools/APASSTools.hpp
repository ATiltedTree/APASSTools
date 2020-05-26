#pragma once

#include "common/APASS.hpp"
#include "common/Icon.hpp"
#include "common/PRNFile.hpp"
#include "common/Settings.hpp"
#include "common/TDFFile.hpp"
#include "ui/AboutDialog/AboutDialog.hpp"
#include "ui/CSVDialog/CSVDialog.hpp"
#include "ui/SettingsDialog/SettingsDialog.hpp"
#include "ui/WebDialog/WebDialog.hpp"
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
#include <config.hpp>

namespace Ui {
  class APASSTools {
  public:
    const QList<QString> apassValues = {
        "radeg",  "raerr",       "decdeg", "decerr", "Johnson_V", "Verr",
        "Vnobs",  "Johnson_B",   "Berr",   "Bnobs",  "Sloan_u",   "SUerr",
        "SUnobs", "Sloan_g",     "SGerr",  "SGnobs", "Sloan_r",   "SRerr",
        "SRnobs", "Sloan_i",     "SIerr",  "SInobs", "Sloan_z",   "SZerr",
        "SZnobs", "PanSTARRS_Y", "Yerr",   "Ynobs"};

    QAction *actionCSV;
    QAction *actionWeb;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionQuit;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionSettings;
    QAction *actionClear;
    QWidget *centralwidget;
    QGridLayout *centralLayout;
    QGroupBox *settingsBox;
    QFormLayout *settingsBoxLayout;
    QDoubleSpinBox *magnitudeSpin;
    QSpinBox *observationSpin;
    QLabel *obsLabel;
    QLineEdit *nameEdit;
    QLabel *nameLabel;
    QLabel *magLabel;
    QTreeWidget *CSVDisplay;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuNewFrom;
    QMenu *menuHelp;
    QMenu *menuEdit;
    QStatusBar *statusbar;
    QMainWindow *parent;
    QTreeWidgetItem *CSVDisplayHeaderItem;

    APASSTools(QMainWindow *parent)
        : actionCSV(new QAction(parent)), actionWeb(new QAction(parent)),
          actionSave(new QAction(parent)), actionSaveAs(new QAction(parent)),
          actionQuit(new QAction(parent)), actionHelp(new QAction(parent)),
          actionAbout(new QAction(parent)), actionAboutQt(new QAction(parent)),
          actionSettings(new QAction(parent)), actionClear(new QAction(parent)),
          centralwidget(new QWidget(parent)),
          centralLayout(new QGridLayout(centralwidget)),
          settingsBox(new QGroupBox(centralwidget)),
          settingsBoxLayout(new QFormLayout(settingsBox)),
          magnitudeSpin(new QDoubleSpinBox(settingsBox)),
          observationSpin(new QSpinBox(settingsBox)),
          obsLabel(new QLabel(settingsBox)),
          nameEdit(new QLineEdit(settingsBox)),
          nameLabel(new QLabel(settingsBox)), magLabel(new QLabel(settingsBox)),
          CSVDisplay(new QTreeWidget(centralwidget)),
          menubar(new QMenuBar(parent)), menuFile(new QMenu(menubar)),
          menuNewFrom(new QMenu(menuFile)), menuHelp(new QMenu(menubar)),
          menuEdit(new QMenu(menubar)), statusbar(new QStatusBar(parent)),
          parent(parent), CSVDisplayHeaderItem(new QTreeWidgetItem()) {}

    void setupUi() const {
      parent->setWindowIcon(getIcon(Icon::Logo));
      parent->setCentralWidget(centralwidget);
      parent->setMenuBar(menubar);
      parent->setStatusBar(statusbar);

      settingsBoxLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);
      settingsBoxLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);
      settingsBoxLayout->setWidget(1, QFormLayout::FieldRole, observationSpin);
      settingsBoxLayout->setWidget(1, QFormLayout::LabelRole, obsLabel);
      settingsBoxLayout->setWidget(2, QFormLayout::FieldRole, magnitudeSpin);
      settingsBoxLayout->setWidget(2, QFormLayout::LabelRole, magLabel);

      for (int i = 0; i < apassValues.size(); i++) {
        CSVDisplayHeaderItem->setText(i, apassValues.at(i));
      }

      CSVDisplay->setHeaderItem(CSVDisplayHeaderItem);
      CSVDisplay->setRootIsDecorated(false);
      CSVDisplay->setItemsExpandable(false);
      CSVDisplay->setSortingEnabled(true);

      centralLayout->addWidget(settingsBox, 0, 0, 2, 2);
      centralLayout->addWidget(CSVDisplay, 2, 0, 1, 2);

      actionCSV->setIcon(getIcon(Icon::TextCSV));
      actionWeb->setIcon(getIcon(Icon::Download));
      actionSave->setIcon(getIcon(Icon::FileSave));
      actionSaveAs->setIcon(getIcon(Icon::FileSaveAs));
      actionQuit->setIcon(getIcon(Icon::WindowClose));
      actionHelp->setIcon(getIcon(Icon::Help));
      actionAbout->setIcon(getIcon(Icon::HelpAbout));
      actionAboutQt->setIcon(getIcon(Icon::QtIcon));
      actionSettings->setIcon(getIcon(Icon::Settings));
      actionClear->setIcon(getIcon(Icon::EditClear));

      menuNewFrom->setIcon(getIcon(Icon::FileNew));
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

      menuEdit->addAction(actionClear);

      menubar->addAction(menuFile->menuAction());
      menubar->addAction(menuEdit->menuAction());
      menubar->addAction(menuHelp->menuAction());

      retranslateUi();
    }

    void retranslateUi() const {
      parent->setWindowTitle(
          QCoreApplication::translate("APASSTools", "APASSTools", nullptr));

      actionCSV->setText(
          QCoreApplication::translate("APASSTools", "CSV File", nullptr));
      actionWeb->setText(
          QCoreApplication::translate("APASSTools", "Web", nullptr));
      actionSave->setText(
          QCoreApplication::translate("APASSTools", "Save", nullptr));
      actionSave->setShortcut(
          QCoreApplication::translate("APASSTools", "Ctrl+S", nullptr));
      actionSaveAs->setText(
          QCoreApplication::translate("APASSTools", "Save as ...", nullptr));
      actionSaveAs->setShortcut(
          QCoreApplication::translate("APASSTools", "Ctrl+Shift+S", nullptr));
      actionQuit->setText(
          QCoreApplication::translate("APASSTools", "Quit", nullptr));
      actionQuit->setShortcut(
          QCoreApplication::translate("APASSTools", "Ctrl+Q", nullptr));
      actionHelp->setText(
          QCoreApplication::translate("APASSTools", "Help", nullptr));
      actionHelp->setShortcut(
          QCoreApplication::translate("APASSTools", "F1", nullptr));
      actionAbout->setText(
          QCoreApplication::translate("APASSTools", "About", nullptr));
      actionAboutQt->setText(
          QCoreApplication::translate("APASSTools", "About Qt", nullptr));
      actionSettings->setText(
          QCoreApplication::translate("APASSTools", "Settings", nullptr));
      actionClear->setText(
          QCoreApplication::translate("APASSTools", "Clear", nullptr));
      actionClear->setToolTip(
          QCoreApplication::translate("APASSTools", "Clear preview", nullptr));

      settingsBox->setTitle(
          QCoreApplication::translate("APASSTools", "Settings", nullptr));
      obsLabel->setText(QCoreApplication::translate(
          "APASSTools", "Observation Threshold", nullptr));
      nameLabel->setText(
          QCoreApplication::translate("APASSTools", "Name", nullptr));
      magLabel->setText(QCoreApplication::translate(
          "APASSTools", "Magnitude Threshold", nullptr));
      menuFile->setTitle(
          QCoreApplication::translate("APASSTools", "File", nullptr));
      menuEdit->setTitle(
          QCoreApplication::translate("APASSTools", "Edit", nullptr));
      menuNewFrom->setTitle(
          QCoreApplication::translate("APASSTools", "New from", nullptr));
      menuHelp->setTitle(
          QCoreApplication::translate("APASSTools", "Help", nullptr));
    } // retranslateUi
  };
} // namespace Ui

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
  explicit APASSTools(QWidget *parent);
  void closeEvent(QCloseEvent *event) override;
  void updateTree();

private:
  Ui::APASSTools *ui;
  bool unsavedChanges = false;
  APASS apass;
  Settings settings;

  void setupConnections();
  void doImport(const QString &data);
  void doSave(bool saveAs);
};
