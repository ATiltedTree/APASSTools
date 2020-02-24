#include "TDF.h"

TDF::TDF(QString name) : name(name) {}

TDF::~TDF() {}

void TDF::buildFile(QString filepath) {
  QString content = QString(tr(CONFIG_TDF_TEMPLATE).arg(name, name + ".prn"));
  QFile file(filepath);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream out(&file);
    out << content;
    file.flush();
    file.close();
  }
}
