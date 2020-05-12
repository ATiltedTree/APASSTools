#pragma once

#include "APASS.hpp"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <memory>

constexpr int LENGTH_OF_DEG    = 9;
constexpr int LENGTH_OF_V_NOBS = 2;

class PRNFile {
private:
  APASS apass;

public:
  explicit PRNFile(APASS apass);

  void buildFile(const QString& filepath);
};
