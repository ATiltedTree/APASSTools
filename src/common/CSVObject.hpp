#pragma once

#include <QString>

class CSVObject {
public:
  explicit CSVObject(QString value);
  QString asString();
  int asInt();
  double asDouble();

private:
  QString value;
};
