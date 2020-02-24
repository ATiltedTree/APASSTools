#pragma once

#include <QFile>
#include <QObject>
#include <QString>
#include <QTextStream>
#include <config.h>

class TDF : public QObject {
  Q_OBJECT
private:
  QString name;

public:
  TDF(QString name);
  ~TDF();
  void buildFile(QString filepath);
};
