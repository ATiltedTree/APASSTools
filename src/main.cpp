#include "ui/APASSTools/APASSTools.h"

#include <QApplication>

#ifdef QT_STATIC
#include <QtPlugin>
#include <QtSvg>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QWindowsVistaStylePlugin)
Q_IMPORT_PLUGIN(QSvgPlugin)
Q_IMPORT_PLUGIN(QICOPlugin)
Q_IMPORT_PLUGIN(QGifPlugin)
Q_IMPORT_PLUGIN(QJpegPlugin)
#endif

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  APASSTools w;
  w.show();

  return a.exec();
}
