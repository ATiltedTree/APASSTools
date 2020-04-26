#pragma once

#include "Macros.h"
#include <QFile>
#include <QObject>
#include <QString>
#include <QTextStream>

#define TDF_TEMPLATE                                                                               \
  "file %1\ntitle %2\nRA H  1 9\nunits0 -2   # RA 'hours' are really decimal degrees\nde d  10 "   \
  "10\ntext 50 4\n~r  1  19  Data from APASS photometry: \\n\n~c  1  19 Photometry "               \
  "(APASS):\\n\n~r  1  20 \\n\n~c 23   6 V-magnitude: %s\\n\n~r 23   6  ^V-magnitude^: %s\\n\n~r " \
  "29   5  ^Error in V^: %s\\n\n~c 45   5 B-V: %s\\n\n~r 34   6  ^B-magnitude^: %s\\n\n~r 40   5 " \
  " ^Error in B^: %s\\n\n~r 20   3  ^number of measurements^: %s\\n\n~r  1  20 \\n\n~r  1  20  "   \
  "^ICQ reference key^: AQ.\\n\n~r  1  20 \\n\nepoch 2000\nfield 0.00 21.00\nshown 5\ntype "       \
  "6\nend\n"

class TDFFile {
private:
  QString name;

public:
  explicit TDFFile(QString name);
  SMART_PTRS(TDFFile)

  void buildFile(const QString& filepath);
};
