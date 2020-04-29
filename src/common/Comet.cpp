#include "Comet.hpp"

Comet::Comet(QList<QString> data)
    : radeg(CSVObject::New(data[0])), raerr(CSVObject::New(data[1])),
      decdeg(CSVObject::New(data[2])), decerr(CSVObject::New(data[3])),
      Johnson_V(CSVObject::New(data[4])), Verr(CSVObject::New(data[5])),
      Vnobs(CSVObject::New(data[6])), Johnson_B(CSVObject::New(data[7])),
      Berr(CSVObject::New(data[8])), Bnobs(CSVObject::New(data[9])),
      Sloan_u(CSVObject::New(data[10])), SUerr(CSVObject::New(data[11])),
      SUnobs(CSVObject::New(data[12])), Sloan_g(CSVObject::New(data[13])),
      SGerr(CSVObject::New(data[14])), SGnobs(CSVObject::New(data[15])),
      Sloan_r(CSVObject::New(data[16])), SRerr(CSVObject::New(data[17])),
      SRnobs(CSVObject::New(data[18])), Sloan_i(CSVObject::New(data[19])),
      SIerr(CSVObject::New(data[20])), SInobs(CSVObject::New(data[21])),
      Sloan_z(CSVObject::New(data[22])), SZerr(CSVObject::New(data[23])),
      SZnobs(CSVObject::New(data[24])), PanSTARRS_Y(CSVObject::New(data[25])),
      Yerr(CSVObject::New(data[26])), Ynobs(CSVObject::New(data[27])), data(std::move(data)) {}
