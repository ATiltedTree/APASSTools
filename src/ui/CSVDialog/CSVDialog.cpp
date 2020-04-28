#include "CSVDialog.h"

CSVDialog::CSVDialog(QWidget* parent) : QDialog(parent), ui(new Ui::CSVDialog(this)) {
  ui->setupUi();
  connect(this->ui->buttonCSVFile, &QPushButton::clicked, this, &CSVDialog::onSelectFile);
  connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(this->ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

CSVDialog::~CSVDialog() {
  delete ui;
}
QString CSVDialog::getResult() {
  QFile csvFile(this->ui->lineEditCSVFile->text());
  if (!csvFile.open(QIODevice::ReadOnly)) {
    QMessageBox::information(nullptr, "error", csvFile.errorString());
    throw csvFile.errorString();
  }
  QTextStream in(&csvFile);
  QString data = in.readAll();
  csvFile.close();
  return data;
}

void CSVDialog::onSelectFile() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open CSV"), Settings::appSettings.lastCSVDir, tr("CSV Files (*.csv)"));
  Settings::appSettings.lastCSVDir = fileName.left(fileName.lastIndexOf(QChar('/')));
  this->ui->lineEditCSVFile->setText(fileName);
}
