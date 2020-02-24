#pragma once

#include "APASS.h"
#include <QFile>
#include <QString>
#include <QTextStream>

class PRN {
private:
  APASS apass;
  int radegLength  = 9;
  int decdegLength = 9;
  int VnobsLength  = 2;

public:
  PRN(APASS apass);
  ~PRN();
  void buildFile(QString filepath);
};
