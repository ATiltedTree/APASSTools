#pragma once

#include "CSVObject.hpp"
#include "Macros.hpp"
#include <QList>
#include <QString>

class Comet {
public:
  explicit Comet(QList<QString> data);
  SMART_PTRS(Comet)

  CSVObject::Ref radeg;
  CSVObject::Ref raerr;
  CSVObject::Ref decdeg;
  CSVObject::Ref decerr;
  CSVObject::Ref Johnson_V;
  CSVObject::Ref Verr;
  CSVObject::Ref Vnobs;
  CSVObject::Ref Johnson_B;
  CSVObject::Ref Berr;
  CSVObject::Ref Bnobs;
  CSVObject::Ref Sloan_u;
  CSVObject::Ref SUerr;
  CSVObject::Ref SUnobs;
  CSVObject::Ref Sloan_g;
  CSVObject::Ref SGerr;
  CSVObject::Ref SGnobs;
  CSVObject::Ref Sloan_r;
  CSVObject::Ref SRerr;
  CSVObject::Ref SRnobs;
  CSVObject::Ref Sloan_i;
  CSVObject::Ref SIerr;
  CSVObject::Ref SInobs;
  CSVObject::Ref Sloan_z;
  CSVObject::Ref SZerr;
  CSVObject::Ref SZnobs;
  CSVObject::Ref PanSTARRS_Y;
  CSVObject::Ref Yerr;
  CSVObject::Ref Ynobs;

  QList<QString> data;
};
