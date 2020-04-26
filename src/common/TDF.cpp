#include "TDF.h"

#include <utility>

TDF::TDF(QString name) : name(std::move(name)) {}

void TDF::buildFile(const QString& filepath) {
  QString content = QString(QObject::tr(TDF_TEMPLATE).arg(name, name + ".prn"));
  QFile file(filepath);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream out(&file);
    out << content;
    file.flush();
    file.close();
  }
}
