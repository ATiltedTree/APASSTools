#include "Settings.hpp"

Settings::Settings() {
  QSettings qsettings;

  this->windowGeometry = qsettings.value("windowGeometry").toByteArray();

  qsettings.beginGroup("AppSettings");
  this->appSettings.defaultSaveDir =
      qsettings.value("defaultSaveDir").toString();
  this->appSettings.lastCSVDir = qsettings.value("lastCSVDir").toString();
  this->appSettings.observationThreshold =
      qsettings.value("observationThreshold").toInt();
  this->appSettings.magnitudeThreshold =
      qsettings.value("magnitudeThreshold").toDouble();
  this->appSettings.createTDFFile = qsettings.value("createTDFFile").toBool();
  qsettings.endGroup();
}

Settings::~Settings() {
  QSettings qsettings;

  qsettings.setValue("windowGeometry", this->windowGeometry);

  qsettings.beginGroup("AppSettings");
  qsettings.setValue("defaultSaveDir", this->appSettings.defaultSaveDir);
  qsettings.setValue("lastCSVDir", this->appSettings.lastCSVDir);
  qsettings.setValue("magnitudeThreshold",
                     this->appSettings.magnitudeThreshold);
  qsettings.setValue("observationThreshold",
                     this->appSettings.observationThreshold);
  qsettings.setValue("createTDFFile", this->appSettings.createTDFFile);
  qsettings.endGroup();
}
