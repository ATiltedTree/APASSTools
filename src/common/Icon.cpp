#include "Icon.hpp"

#include <QIcon>
#include <QString>

QIcon getIcon(Icon icon) {
  std::string iconName         = iconLookup.at(icon);
  std::string resourceLocation = ":/icons/";
  return QIcon::fromTheme(iconName.c_str(), QIcon(resourceLocation.append(iconName).c_str()));
}
