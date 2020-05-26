#include "ui/APASSTools/APASSTools.hpp"
#include <QApplication>

auto main(int argc, char *argv[]) -> int {
  QApplication a(argc, argv);
  APASSTools apasstools = APASSTools(nullptr);
  apasstools.show();
  return QApplication::exec();
}
