#include "CSVDialog.hpp"

CSVDialog::CSVDialog(QWidget *parent, Settings *settings)
    : QDialog(parent), ui(new Ui::CSVDialog(this)), settings(settings) {
  ui->setupUi();
  connect(this->ui->buttonCSVFile, &QPushButton::clicked, this,
          &CSVDialog::onSelectFile);
  connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this,
          &QDialog::accept);
  connect(this->ui->buttonBox, &QDialogButtonBox::rejected, this,
          &QDialog::reject);
}

auto CSVDialog::getResult() -> QString {
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
      this, tr("Open CSV"), this->settings->appSettings.lastCSVDir,
      tr("CSV Files (*.csv)"));
  this->settings->appSettings.lastCSVDir =
      fileName.left(fileName.lastIndexOf(QChar('/')));
  this->ui->lineEditCSVFile->setText(fileName);
}
