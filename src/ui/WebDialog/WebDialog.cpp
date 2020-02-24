#include "WebDialog.h"
#include "./ui_WebDialog.h"

WebDialog::WebDialog(QWidget* parent) : QDialog(parent), ui(new Ui::WebDialog) {
  ui->setupUi(this);
  connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &WebDialog::doDownload);
  connect(this->ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

WebDialog::~WebDialog() {
  delete ui;
}

void WebDialog::doDownload() {
  this->ui->buttonBox->setEnabled(false);
  QUrlQuery query;
  query.addQueryItem("ra", this->ui->editRA->text());
  query.addQueryItem("dec", this->ui->editDec->text());
  query.addQueryItem("radius", this->ui->spinBoxRadius->text());
  query.addQueryItem("outtype", "1");
  QNetworkRequest req;
  req.setUrl(QUrl("http://www.aavso.org/cgi-bin/apass_dr10_download.pl"));
  req.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
  this->reply = this->manager.post(req, query.toString().toUtf8());
  connect(this->reply, &QNetworkReply::downloadProgress, this, &WebDialog::onProgress);
  connect(&this->manager, &QNetworkAccessManager::finished, this, &WebDialog::onFinished);
}

void WebDialog::onProgress(qint64 bytesReceived, qint64 bytesTotal) {
  this->ui->progressBar->setMaximum(this->reply->size());
  this->ui->progressBar->setValue(bytesReceived);
}

void WebDialog::onFinished(QNetworkReply* reply) {
  if (reply->isReadable()) {
    this->data   = reply->readAll();
    this->isDone = true;
    this->accept();
  }
}

QString WebDialog::getResult() {
  return this->data;
}
