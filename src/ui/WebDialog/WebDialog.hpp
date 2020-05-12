#pragma once

#include "common/Icon.hpp"
#include <QApplication>
#include <QCloseEvent>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProgressBar>
#include <QSpinBox>
#include <QString>
#include <QUrlQuery>
#include <QWidget>
#include <config.hpp>

constexpr int MAX_RADIUS = 15;

namespace Ui {
  class WebDialog {
  public:
    QFormLayout* formLayout;
    QLabel* labelRA;
    QLineEdit* editRA;
    QLabel* labelDec;
    QLineEdit* editDec;
    QLabel* labelRadius;
    QSpinBox* spinBoxRadius;
    QWidget* widget;
    QDialogButtonBox* buttonBox;
    QDialog* parent;

    WebDialog(QDialog* parent)
        : formLayout(new QFormLayout(parent)), labelRA(new QLabel(parent)),
          editRA(new QLineEdit(parent)), labelDec(new QLabel(parent)),
          editDec(new QLineEdit(parent)), labelRadius(new QLabel(parent)),
          spinBoxRadius(new QSpinBox(parent)), widget(new QWidget(parent)),
          buttonBox(new QDialogButtonBox(parent)), parent(parent) {}

    void setupUi() const {
      parent->window()->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
      parent->setWindowFlag(Qt::WindowType::MSWindowsFixedSizeDialogHint, true);
      parent->setWindowIcon(getIcon(Icon::Download));

      spinBoxRadius->setMinimum(1);
      spinBoxRadius->setMaximum(MAX_RADIUS);

      buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

      formLayout->setWidget(0, QFormLayout::LabelRole, labelRA);
      formLayout->setWidget(0, QFormLayout::FieldRole, editRA);
      formLayout->setWidget(1, QFormLayout::LabelRole, labelDec);
      formLayout->setWidget(1, QFormLayout::FieldRole, editDec);
      formLayout->setWidget(2, QFormLayout::LabelRole, labelRadius);
      formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxRadius);
      formLayout->setWidget(3, QFormLayout::FieldRole, widget);
      formLayout->setWidget(4, QFormLayout::SpanningRole, buttonBox);

      retranslateUi();
    }

    void retranslateUi() const {
      parent->setWindowTitle(QCoreApplication::translate("WebDialog", "From Web...", nullptr));
      labelRA->setText(QCoreApplication::translate("WebDialog", "R. A.", nullptr));
      labelDec->setText(QCoreApplication::translate("WebDialog", "Dec.", nullptr));
      labelRadius->setText(QCoreApplication::translate("WebDialog", "Radius", nullptr));
    }
  };
} // namespace Ui

class WebDialog : public QDialog {
  Q_OBJECT

private slots:
  void onFinished(QNetworkReply* networkReply);
  void doDownload();

public:
  explicit WebDialog(QWidget* parent);
  QString getResult();

private:
  Ui::WebDialog* ui;
  QNetworkAccessManager manager;
  QString data;
};
