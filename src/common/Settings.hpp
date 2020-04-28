#pragma once

#include <QPoint>
#include <QSettings>
#include <QSize>

struct WindowSettings {
  QSize size;
  QPoint pos;
};

struct AppSettings {
  QString defaultSaveDir;
  QString lastCSVDir;
  int observationThreshold;
  double magnitudeThreshold;
  bool createTDFFile;
};

class Settings {
private:
  /* data */
public:
  static WindowSettings windowSettings;
  static AppSettings appSettings;

  static void init();
  static void sync();
};
