#pragma once

#include "Macros.h"
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
    QProgressBar* progressBar;
    QDialog* parent;

    WebDialog(QDialog* parent)
        : parent(parent), formLayout(new QFormLayout(parent)), labelRA(new QLabel(parent)),
          editRA(new QLineEdit(parent)), labelDec(new QLabel(parent)),
          editDec(new QLineEdit(parent)), labelRadius(new QLabel(parent)),
          spinBoxRadius(new QSpinBox(parent)), widget(new QWidget(parent)),
          buttonBox(new QDialogButtonBox(parent)), progressBar(new QProgressBar(parent)){};

    void setupUi() {
      parent->resize(362, 208);
      parent->setWindowIcon(QIcon::fromTheme("web-browser"));

      spinBoxRadius->setMinimum(1);
      spinBoxRadius->setMaximum(15);

      buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

      progressBar->setEnabled(true);
      progressBar->setValue(0);
      progressBar->setTextVisible(true);

      formLayout->setWidget(0, QFormLayout::LabelRole, labelRA);
      formLayout->setWidget(0, QFormLayout::FieldRole, editRA);
      formLayout->setWidget(1, QFormLayout::LabelRole, labelDec);
      formLayout->setWidget(1, QFormLayout::FieldRole, editDec);
      formLayout->setWidget(2, QFormLayout::LabelRole, labelRadius);
      formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxRadius);
      formLayout->setWidget(3, QFormLayout::FieldRole, widget);
      formLayout->setWidget(4, QFormLayout::SpanningRole, buttonBox);
      formLayout->setWidget(5, QFormLayout::SpanningRole, progressBar);

      retranslateUi();
    }

    void retranslateUi() {
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
  void onProgress(qint64 bytesReceived, qint64 bytesTotal);
  void doDownload();

public:
  explicit WebDialog(QWidget* parent);
  ~WebDialog() override;
  SMART_PTRS(WebDialog)

  QString getResult();

private:
  Ui::WebDialog* ui;
  QNetworkAccessManager manager;
  bool isDone = false;
  QString data;
  QNetworkReply* reply{};
};
