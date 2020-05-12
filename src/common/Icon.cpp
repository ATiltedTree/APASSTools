#include "Icon.hpp"

static const std::map<Icon, QString> iconLookup = {
    {Icon::Logo, "apasstools"},   {Icon::DocumentOpen, "document-open"},
    {Icon::Download, "download"}, {Icon::EditClear, "edit-clear"},
    {Icon::FileSave, "filesave"}, {Icon::FileSaveAs, "filesaveas"},
    {Icon::FileNew, "filenew"},   {Icon::HelpAbout, "help-about"},
    {Icon::Help, "help"},         {Icon::Settings, "settings"},
    {Icon::TextCSV, "text-csv"},  {Icon::WindowClose, "window-close"},
    {Icon::QtIcon, "qt5-logo"}};

QIcon getIcon(Icon icon) {
  QString iconName         = iconLookup.at(icon);
  QString resourceLocation = ":/icons/";
  return QIcon::fromTheme(iconName, QIcon(resourceLocation.append(iconName)));
}
