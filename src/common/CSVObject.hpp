#pragma once

#include <QString>

class CSVObject {
public:
  explicit CSVObject(QString value);
  auto asString() -> QString;
  auto asInt() -> int;
  auto asDouble() -> double;

private:
  QString value;
};
