#pragma once

#include "common/Settings.h"
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
  class CSVDialog;
} // namespace Ui
QT_END_NAMESPACE

class CSVDialog : public QDialog {
  Q_OBJECT
private:
  Ui::CSVDialog* ui;

private slots:
  void onSelectFile();

public:
  CSVDialog(QWidget* parent = nullptr);
  ~CSVDialog();
  QString getResult();
};
