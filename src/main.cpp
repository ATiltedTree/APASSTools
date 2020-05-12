#include "ui/APASSTools/APASSTools.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  APASSTools apasstools = APASSTools(nullptr);
  apasstools.show();
  return QApplication::exec();
}
