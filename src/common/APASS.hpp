#pragma once

#include "Comet.hpp"
#include <QList>
#include <QProgressBar>
#include <QString>

class APASS {
private:
  QList<Comet> comets;

public:
  APASS();

  void addComet(Comet comet);
  void clearComets();
  QList<Comet> getComets();
  void importCSV(const QString& csv, int observationThreshold, double magnitudeThreshold,
                 QProgressBar* bar);
};
