#pragma once

#include <QIcon>
#include <QString>
#include <map>

enum class Icon {
  Logo,
  DocumentOpen,
  Download,
  EditClear,
  FileSave,
  FileSaveAs,
  FileNew,
  HelpAbout,
  Help,
  Settings,
  TextCSV,
  WindowClose,
  QtIcon
};

QIcon getIcon(Icon icon);
