#pragma once

#include "APASS.h"
#include "Macros.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <memory>

#define LENGTH_OF_DEG 9
#define LENGTH_OF_V_NOBS 2

class PRNFile {
private:
  APASS::Ref apass;
  int radegLength  = LENGTH_OF_DEG;
  int decdegLength = LENGTH_OF_DEG;
  int VnobsLength  = LENGTH_OF_V_NOBS;

public:
  explicit PRNFile(APASS::Ref apass);
  SMART_PTRS(PRNFile)

  void buildFile(const QString& filepath);
};
