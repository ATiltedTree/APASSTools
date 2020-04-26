#pragma once

#include "APASS.h"
#include "Macros.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <memory>

#define LENGTH_OF_DEG 9
#define LENGTH_OF_V_NOBS 2

class PRN {
private:
  APASS::Ref apass;
  int radegLength  = LENGTH_OF_DEG;
  int decdegLength = LENGTH_OF_DEG;
  int VnobsLength  = LENGTH_OF_V_NOBS;

public:
  explicit PRN(APASS::Ref apass);
  SMART_PTRS(PRN)

  void buildFile(const QString& filepath);
};
