#pragma once

#include <QIcon>
#include <QString>
#include <map>

enum Icon {
  APASSTools,
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

static std::map<Icon, std::string> iconLookup = {std::pair{Icon::APASSTools, "apasstools"},
                                                 {Icon::DocumentOpen, "document-open"},
                                                 {Icon::Download, "download"},
                                                 {Icon::EditClear, "edit-clear"},
                                                 {Icon::FileSave, "filesave"},
                                                 {Icon::FileSaveAs, "filesaveas"},
                                                 {Icon::FileNew, "filenew"},
                                                 {Icon::HelpAbout, "help-about"},
                                                 {Icon::Help, "help"},
                                                 {Icon::Settings, "settings"},
                                                 {Icon::TextCSV, "text-csv"},
                                                 {Icon::WindowClose, "window-close"},
                                                 {Icon::QtIcon, "qt5-logo"}};

QIcon getIcon(Icon icon);
