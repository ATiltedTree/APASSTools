#include "ui/APASSTools/APASSTools.h"

#include <QApplication>

#ifdef QT_STATIC
#include <QtPlugin>
#include <QtSvg>
#ifdef WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QWindowsVistaStylePlugin)
#endif
Q_IMPORT_PLUGIN(QSvgPlugin)
#endif

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  APASSTools::Ref w = APASSTools::New(nullptr);
  w->show();
  return QApplication::exec();
}
