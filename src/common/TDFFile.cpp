#include "TDFFile.hpp"

#include <utility>

TDFFile::TDFFile(QString name) : name(std::move(name)) {}

void TDFFile::buildFile(const QString& filepath) {
  QString content = QString(QObject::tr(TDF_TEMPLATE).arg(name, name + ".prn"));
  QFile file(filepath);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream out(&file);
    out << content;
    file.flush();
    file.close();
  }
}
