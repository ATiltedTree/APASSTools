#pragma once

#include "common/Icon.hpp"
#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <config.hpp>

namespace Ui {
  class AboutDialog {
  public:
    QGridLayout* gridLayout;
    QLabel* lableTitle;
    QLabel* lableIcon;
    QLabel* lableDesc;
    QDialogButtonBox* buttonBox;
    QDialog* parent;

    AboutDialog(QDialog* parent)
        : gridLayout(new QGridLayout(parent)), lableTitle(new QLabel(parent)),
          lableIcon(new QLabel(parent)), lableDesc(new QLabel(parent)),
          buttonBox(new QDialogButtonBox(parent)), parent(parent){};

    void setupUi() {
      parent->window()->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
      parent->setWindowFlag(Qt::WindowType::MSWindowsFixedSizeDialogHint, true);
      parent->setWindowIcon(getIcon(Icon::HelpAbout));

      lableTitle->setText(
          QObject::tr("<p><span style=\"font-size: 14pt; font-weight:600;\">%1<span/><p/>"
                      "<p>Version: %2"
                      "<br/>Build with: %4 %5, %6"
                      "<br/>Copyright (c) 2020 Tilmann Meyer<p/>")
              .arg(CONFIG_APP_NAME, CONFIG_APP_VERSION, CONFIG_COMPILER, CONFIG_COMPILER_VERSION,
                   CONFIG_COMPILER_ARCH));

      lableDesc->setText(
          "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
          "of this software and associated documentation files (the \"Software\"), to deal\n"
          "in the Software without restriction, including without limitation the rights\n"
          "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
          "copies of the Software, and to permit persons to whom the Software is\n"
          "furnished to do so, subject to the following conditions:\n"
          "\n"
          "The above copyright notice and this permission notice shall be included in all\n"
          "copies or substantial portions of the Software.\n"
          "\n"
          "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
          "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
          "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
          "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
          "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
          "OUT OF OR IN CONNECTION WI"
          "TH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
          "SOFTWARE\n");

      lableIcon->setMaximumSize(QSize(100, 100));
      lableIcon->setPixmap(getIcon(Icon::APASSTools).pixmap(100));
      lableIcon->setScaledContents(true);

      buttonBox->setOrientation(Qt::Horizontal);
      buttonBox->setStandardButtons(QDialogButtonBox::Ok);

      gridLayout->addWidget(buttonBox, 2, 0, 1, 2);
      gridLayout->addWidget(lableIcon, 0, 0, 1, 1);
      gridLayout->addWidget(lableDesc, 1, 0, 1, 2);
      gridLayout->addWidget(lableTitle, 0, 1, 1, 1);

      retranslateUi();
    }

    void retranslateUi() {
      parent->setWindowTitle(QCoreApplication::translate("AboutDialog", "About", nullptr));
    }
  };
} // namespace Ui

class AboutDialog : public QDialog {
  Q_OBJECT

public:
  explicit AboutDialog(QWidget* parent);

private:
  Ui::AboutDialog* ui;
};
