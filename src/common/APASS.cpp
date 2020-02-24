#include "APASS.h"

APASS::~APASS() {}
APASS::APASS() {}

void APASS::addComet(Comet comet) {
  this->comets.append(comet);
}

void APASS::addComet(QList<Comet> comet) {
  this->comets.append(comet);
}

void APASS::clearComets() {
  this->comets.clear();
}

QList<Comet> APASS::getComets() {
  return this->comets;
}

void APASS::importCSV(QString csv, int observationThreshold, double magnitudeThreshold,
                      QProgressBar* bar) {

  QList<QString> csvRows(csv.split("\n"));
  csvRows.removeFirst();
  csvRows.removeLast();
  bar->setMaximum(csvRows.size());
  for (size_t i = 0; i < csvRows.size(); i++) {
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
