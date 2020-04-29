#pragma once

#include "Macros.hpp"
#include "common/Icon.hpp"
#include "common/Settings.hpp"
#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <config.hpp>

namespace Ui {
  class CSVDialog {
  public:
    QFormLayout* formLayout;
    QLabel* labelCSVFile;
    QHBoxLayout* horizontalLayout;
    QLineEdit* lineEditCSVFile;
    QPushButton* buttonCSVFile;
    QDialogButtonBox* buttonBox;
    QDialog* parent;

    CSVDialog(QDialog* parent)
        : parent(parent), formLayout(new QFormLayout(parent)), labelCSVFile(new QLabel(parent)),
          horizontalLayout(new QHBoxLayout()), lineEditCSVFile(new QLineEdit(parent)),
          buttonCSVFile(new QPushButton(parent)), buttonBox(new QDialogButtonBox(parent)){};

    void setupUi() {
      parent->window()->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
      parent->setWindowFlag(Qt::WindowType::MSWindowsFixedSizeDialogHint, true);
      parent->setWindowIcon(getIcon(Icon::TextCSV));

      buttonCSVFile->setIcon(getIcon(Icon::DocumentOpen));

      buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

      horizontalLayout->addWidget(lineEditCSVFile);
      horizontalLayout->addWidget(buttonCSVFile);

      formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);
      formLayout->setWidget(0, QFormLayout::LabelRole, labelCSVFile);
      formLayout->setWidget(1, QFormLayout::FieldRole, buttonBox);

      retranslateUi();
    }

    void retranslateUi() {
      parent->setWindowTitle(QCoreApplication::translate("CSVDialog", "From CSV...", nullptr));
      labelCSVFile->setText(QCoreApplication::translate("CSVDialog", "CSV File", nullptr));
    }
  };
} // namespace Ui

class CSVDialog : public QDialog {
  Q_OBJECT

private slots:
  void onSelectFile();

public:
  explicit CSVDialog(QWidget* parent);
  ~CSVDialog() override;
  SMART_PTRS(CSVDialog)

  QString getResult();

private:
  Ui::CSVDialog* ui;
};
