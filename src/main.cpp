#include "ui/APASSTools/APASSTools.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  APASSTools::Ref w = APASSTools::New(nullptr);
  w->show();
  return QApplication::exec();
}
