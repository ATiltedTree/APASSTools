#pragma once

#include "CSVObject.hpp"
#include <QList>
#include <QString>

class Comet {
public:
  explicit Comet(QList<QString> data);

  CSVObject radeg;
  CSVObject raerr;
  CSVObject decdeg;
  CSVObject decerr;
  CSVObject Johnson_V;
  CSVObject Verr;
  CSVObject Vnobs;
  CSVObject Johnson_B;
  CSVObject Berr;
  CSVObject Bnobs;
  CSVObject Sloan_u;
  CSVObject SUerr;
  CSVObject SUnobs;
  CSVObject Sloan_g;
  CSVObject SGerr;
  CSVObject SGnobs;
  CSVObject Sloan_r;
  CSVObject SRerr;
  CSVObject SRnobs;
  CSVObject Sloan_i;
  CSVObject SIerr;
  CSVObject SInobs;
  CSVObject Sloan_z;
  CSVObject SZerr;
  CSVObject SZnobs;
  CSVObject PanSTARRS_Y;
  CSVObject Yerr;
  CSVObject Ynobs;

  QList<QString> data;
};
