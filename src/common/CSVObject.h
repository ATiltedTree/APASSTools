#pragma once

#include "Macros.h"
#include <QString>

class CSVObject {
public:
  explicit CSVObject(QString value);
  SMART_PTRS(CSVObject)

  QString asString();
  int asInt();
  double asDouble();

private:
  QString value;
};
