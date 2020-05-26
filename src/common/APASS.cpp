#include "APASS.hpp"

void APASS::addComet(const Comet &comet) {
  this->comets.append(comet);
}

void APASS::clearComets() {
  this->comets.clear();
}

auto APASS::getComets() -> QList<Comet> {
  return this->comets;
}

void APASS::importCSV(const QString &csv, int observationThreshold,
                      double magnitudeThreshold, QProgressBar *bar) {
  QList<QString> csvRows(csv.split("\n"));
  csvRows.removeFirst();
  csvRows.removeLast();
  bar->setMaximum(csvRows.size());
  for (int i = 0; i < csvRows.size(); i++) {
    QList<QString> csvRow(csvRows[i].split(","));
    Q_ASSERT(csvRow.size() == 28);
    Comet comet = Comet(csvRow);
    if (comet.Vnobs.asInt() >= observationThreshold) {
      if (comet.Johnson_B.asDouble() - comet.Johnson_V.asDouble() < 1) {
        this->addComet(comet);
        bar->setValue(i);
      }
    }
  }
}
