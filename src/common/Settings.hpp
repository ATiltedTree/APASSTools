#pragma once

#include <QByteArray>
#include <QPoint>
#include <QSettings>
#include <QSize>

struct AppSettings {
  QString defaultSaveDir;
  QString lastCSVDir;
  int observationThreshold;
  bool createTDFFile;
  double magnitudeThreshold;
};

class Settings {
public:
  QByteArray windowGeometry{};
  AppSettings appSettings{};

  Settings();
  ~Settings();

  Settings(const Settings&) = delete;
  Settings& operator=(const Settings&) = delete;
  Settings(Settings&&)                 = delete;
  Settings& operator=(Settings&&) = delete;
};
