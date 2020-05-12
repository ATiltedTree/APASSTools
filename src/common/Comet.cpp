#include "Comet.hpp"

Comet::Comet(QList<QString> data)
    : radeg(CSVObject(data[0])), raerr(CSVObject(data[1])), decdeg(CSVObject(data[2])),
      decerr(CSVObject(data[3])), Johnson_V(CSVObject(data[4])), Verr(CSVObject(data[5])),
      Vnobs(CSVObject(data[6])), Johnson_B(CSVObject(data[7])), Berr(CSVObject(data[8])),
      Bnobs(CSVObject(data[9])), Sloan_u(CSVObject(data[10])), SUerr(CSVObject(data[11])),
      SUnobs(CSVObject(data[12])), Sloan_g(CSVObject(data[13])), SGerr(CSVObject(data[14])),
      SGnobs(CSVObject(data[15])), Sloan_r(CSVObject(data[16])), SRerr(CSVObject(data[17])),
      SRnobs(CSVObject(data[18])), Sloan_i(CSVObject(data[19])), SIerr(CSVObject(data[20])),
      SInobs(CSVObject(data[21])), Sloan_z(CSVObject(data[22])), SZerr(CSVObject(data[23])),
      SZnobs(CSVObject(data[24])), PanSTARRS_Y(CSVObject(data[25])), Yerr(CSVObject(data[26])),
      Ynobs(CSVObject(data[27])), data(std::move(data)) {}
