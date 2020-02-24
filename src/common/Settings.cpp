#include "Settings.h"

WindowSettings Settings::windowSettings = WindowSettings();
AppSettings Settings::appSettings       = AppSettings();

void Settings::init() {
  QSettings settings;

  settings.beginGroup("WindowSettings");
  Settings::windowSettings.pos  = settings.value("pos").toPoint();
  Settings::windowSettings.size = settings.value("size").toSize();
  settings.endGroup();

  settings.beginGroup("AppSettings");
  Settings::appSettings.defaultSaveDir       = settings.value("defaultSaveDir").toString();
  Settings::appSettings.lastCSVDir           = settings.value("lastCSVDir").toString();
  Settings::appSettings.observationThreshold = settings.value("observationThreshold").toInt();
  Settings::appSettings.magnitudeThreshold   = settings.value("magnitudeThreshold").toFloat();
  Settings::appSettings.createTDFFile        = settings.value("createTDFFile").toBool();
  settings.endGroup();
}

void Settings::sync() {
  QSettings settings;

  settings.beginGroup("WindowSettings");
  settings.setValue("pos", Settings::windowSettings.pos);
  settings.setValue("size", Settings::windowSettings.size);
  settings.endGroup();

  settings.beginGroup("AppSettings");
  settings.setValue("defaultSaveDir", Settings::appSettings.defaultSaveDir);
  settings.setValue("lastCSVDir", Settings::appSettings.lastCSVDir);
  settings.setValue("magnitudeThreshold", Settings::appSettings.magnitudeThreshold);
  settings.setValue("observationThreshold", Settings::appSettings.observationThreshold);
  settings.setValue("createTDFFile", Settings::appSettings.createTDFFile);
  settings.endGroup();
}
