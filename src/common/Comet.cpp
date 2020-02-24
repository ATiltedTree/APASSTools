#include "Comet.h"

Comet::Comet(QList<QString> data)
    : radeg(data[0]), raerr(data[1]), decdeg(data[2]), decerr(data[3]), Johnson_V(data[4]),
      Verr(data[5]), Vnobs(data[6]), Johnson_B(data[7]), Berr(data[8]), Bnobs(data[9]),
      Sloan_u(data[10]), SUerr(data[11]), SUnobs(data[12]), Sloan_g(data[13]), SGerr(data[14]),
      SGnobs(data[15]), Sloan_r(data[16]), SRerr(data[17]), SRnobs(data[18]), Sloan_i(data[19]),
      SIerr(data[20]), SInobs(data[21]), Sloan_z(data[22]), SZerr(data[23]), SZnobs(data[24]),
      PanSTARRS_Y(data[25]), Yerr(data[26]), Ynobs(data[27]) {}

Comet::~Comet() {}
