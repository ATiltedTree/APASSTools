#pragma once

#include <QCloseEvent>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QUrlQuery>

QT_BEGIN_NAMESPACE
namespace Ui {
  class WebDialog;
} // namespace Ui
QT_END_NAMESPACE

class WebDialog : public QDialog {
  Q_OBJECT
private:
  Ui::WebDialog* ui;
  QNetworkAccessManager manager;
  bool isDone = false;
  QString data;
  QNetworkReply* reply;

private slots:
  void onFinished(QNetworkReply* reply);
  void onProgress(qint64 bytesReceived, qint64 bytesTotal);
  void doDownload();

public:
  WebDialog(QWidget* parent = nullptr);
  ~WebDialog();
  QString getResult();
};
