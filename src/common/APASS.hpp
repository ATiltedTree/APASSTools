#pragma once

#include "Comet.hpp"
#include <QList>
#include <QProgressBar>
#include <QString>

class APASS {
private:
  QList<Comet> comets;

public:
  void addComet(const Comet &comet);
  void clearComets();
  auto getComets() -> QList<Comet>;
  void importCSV(const QString &csv, int observationThreshold,
                 double magnitudeThreshold, QProgressBar *bar);
};
