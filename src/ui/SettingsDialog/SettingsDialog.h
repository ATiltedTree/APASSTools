#pragma once

#include "Macros.h"
#include "common/Settings.h"
#include <QCheckBox>
#include <QCoreApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTabWidget>
#include <QToolButton>
#include <config.h>

namespace Ui {
  class SettingsDialog {
  public:
    QFormLayout* formLayout;
    QDialogButtonBox* buttons;
    QTabWidget* tabWidget;
    QWidget* general;
    QVBoxLayout* verticalLayout;
    QGroupBox* filterBox;
    QFormLayout* formLayout_3;
    QLabel* obsLabel;
    QSpinBox* obsSpin;
    QLabel* magLabel;
    QDoubleSpinBox* magSpin;
    QGroupBox* saveBox;
    QFormLayout* formLayout_2;
    QLabel* savePathLabel;
    QHBoxLayout* savePathLayout;
    QLineEdit* savePathEdit;
    QToolButton* savePathButton;
    QLabel* createTDFLabel;
    QCheckBox* createTDFCheck;
    QDialog* parent;

    SettingsDialog(QDialog* parent)
        : parent(parent), formLayout(new QFormLayout(parent)), tabWidget(new QTabWidget(parent)),
          general(new QWidget()), verticalLayout(new QVBoxLayout(general)),
          filterBox(new QGroupBox(general)), formLayout_3(new QFormLayout(filterBox)),
          obsLabel(new QLabel(filterBox)), buttons(new QDialogButtonBox(parent)),
          obsSpin(new QSpinBox(filterBox)), magLabel(new QLabel(filterBox)),
          magSpin(new QDoubleSpinBox(filterBox)), saveBox(new QGroupBox(general)),
          formLayout_2(new QFormLayout(saveBox)), savePathLabel(new QLabel(saveBox)),
          savePathLayout(new QHBoxLayout()), savePathEdit(new QLineEdit(saveBox)),
          savePathButton(new QToolButton(saveBox)), createTDFLabel(new QLabel(saveBox)),
          createTDFCheck(new QCheckBox(saveBox))

              {};

    void setupUi() {
      parent->resize(589, 521);
      parent->setWindowIcon(QIcon(CONFIG_ICON_PATH.string().c_str()));
      parent->setModal(true);

      buttons->setOrientation(Qt::Horizontal);
      buttons->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Cancel |
                                  QDialogButtonBox::Ok);

      formLayout_3->setWidget(0, QFormLayout::LabelRole, obsLabel);
      formLayout_3->setWidget(0, QFormLayout::FieldRole, obsSpin);
      formLayout_3->setWidget(1, QFormLayout::LabelRole, magLabel);
      formLayout_3->setWidget(1, QFormLayout::FieldRole, magSpin);

      savePathLayout->addWidget(savePathEdit);
      savePathLayout->addWidget(savePathButton);

      formLayout_2->setLayout(0, QFormLayout::FieldRole, savePathLayout);
      formLayout_2->setWidget(0, QFormLayout::LabelRole, savePathLabel);
      formLayout_2->setWidget(1, QFormLayout::LabelRole, createTDFLabel);
      formLayout_2->setWidget(1, QFormLayout::FieldRole, createTDFCheck);

      verticalLayout->addWidget(filterBox);
      verticalLayout->addWidget(saveBox);

      tabWidget->addTab(general, QString());
      tabWidget->setCurrentIndex(0);

      formLayout->setWidget(1, QFormLayout::SpanningRole, buttons);
      formLayout->setWidget(0, QFormLayout::SpanningRole, tabWidget);

      retranslateUi();
    }

    void retranslateUi() {
      parent->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Settings", nullptr));
      filterBox->setTitle(QCoreApplication::translate("SettingsDialog", "Filter", nullptr));
      obsLabel->setText(
          QCoreApplication::translate("SettingsDialog", "Observation Threshold", nullptr));
      magLabel->setText(
          QCoreApplication::translate("SettingsDialog", "Magnitude Threshold", nullptr));
      saveBox->setTitle(QCoreApplication::translate("SettingsDialog", "Saving", nullptr));
      savePathLabel->setText(
          QCoreApplication::translate("SettingsDialog", "Default Save Path", nullptr));
      savePathButton->setText(QCoreApplication::translate("SettingsDialog", "...", nullptr));
      createTDFLabel->setText(
          QCoreApplication::translate("SettingsDialog", "Create TDF for Guide", nullptr));
      createTDFCheck->setText(QString());
      tabWidget->setTabText(tabWidget->indexOf(general),
                            QCoreApplication::translate("SettingsDialog", "General", nullptr));
    } // retranslateUi
  };
} // namespace Ui

class SettingsDialog : public QDialog {
  Q_OBJECT

private slots:
  void onApply();
  void onOK();
  void onChangeSaveLocation();

public:
  explicit SettingsDialog(QWidget* parent);
  ~SettingsDialog() override;
  SMART_PTRS(SettingsDialog)

  void getSettings();
  void saveSettings();

private:
  Ui::SettingsDialog* ui;
};
