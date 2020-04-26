#pragma once

#include "Comet.h"
#include "Macros.h"
#include <QList>
#include <QProgressBar>
#include <QString>

class APASS {
private:
  QList<Comet::Ref> comets;

public:
  APASS();
  SMART_PTRS(APASS)

  void addComet(Comet::Ref comet);
  void clearComets();
  QList<Comet::Ref> getComets();
  void importCSV(const QString& csv, int observationThreshold, double magnitudeThreshold,
                 QProgressBar* bar);
};
