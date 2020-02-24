#pragma once

#include "Comet.h"
#include <QList>
#include <QProgressBar>
#include <QString>

class APASS {
private:
  QList<Comet> comets;

public:
  APASS();
  ~APASS();
  void addComet(Comet comet);
  void addComet(QList<Comet> comet);
  void clearComets();
  QList<Comet> getComets();
  void importCSV(QString csv, int observationThreshold, double magnitudeThreshold,
                 QProgressBar* bar);
};
