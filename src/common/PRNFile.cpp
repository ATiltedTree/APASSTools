#include "PRNFile.hpp"

PRNFile::PRNFile(APASS apass) : apass(std::move(apass)) {}

void PRNFile::buildFile(const QString &filepath) {
  QFile file(filepath);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream out(&file);
    for (Comet comet : this->apass.getComets()) {
      out << QString::number(comet.radeg.asDouble(), 'd', 5)
                 .rightJustified(LENGTH_OF_DEG);
      out << " ";
      out << QString::number(comet.decdeg.asDouble(), 'd', 5)
                 .rightJustified(LENGTH_OF_DEG);
      out << " ";
      out << QString::number(comet.Vnobs.asInt())
                 .rightJustified(LENGTH_OF_V_NOBS);
      out << " ";
      out << QString::number(comet.Johnson_V.asDouble(), 'd', 2);
      out << " ";
      out << QString::number(comet.Verr.asDouble(), 'd', 2);
      out << " ";
      out << QString::number(comet.Johnson_B.asDouble(), 'd', 2);
      out << " ";
      out << QString::number(comet.Berr.asDouble(), 'd', 2);
      out << " ";
      out << QString::number(
          comet.Johnson_B.asDouble() - comet.Johnson_V.asDouble(), 'd', 2);
      out << " ";
      out << QString::number(comet.Johnson_V.asDouble() * 10, 'd', 0);
      out << "c";
      out << "\n";
    }
    file.flush();
    file.close();
  }
}
