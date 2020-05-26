#include "WebDialog.hpp"

WebDialog::WebDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::WebDialog(this)) {
  ui->setupUi();
  connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this,
          &WebDialog::doDownload);
  connect(this->ui->buttonBox, &QDialogButtonBox::rejected, this,
          &QDialog::reject);
  connect(&this->manager, &QNetworkAccessManager::finished, this,
          &WebDialog::onFinished);
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
  this->manager.post(req, query.toString().toUtf8());
}

void WebDialog::onFinished(QNetworkReply *networkReply) {
  if (networkReply->isReadable()) {
    this->data = networkReply->readAll();
    this->accept();
  } else {
    this->reject();
  }
}

auto WebDialog::getResult() -> QString {
  return this->data;
}
