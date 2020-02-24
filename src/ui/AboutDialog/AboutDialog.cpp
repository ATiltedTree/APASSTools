#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include <config.h>

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AboutDialog) {
  ui->setupUi(this);
  connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &AboutDialog::accept);
  this->ui->lableTitle->setText(
      tr("<p><span style=\"font-size: 14pt; font-weight:600;\">%1<span/><p/>"
         "<p>Version: %2"
         "<br/>Build with: %4 %5, %6"
         "<br/>Copyright (c) 2020 Tilmann Meyer<p/>")
          .arg(CONFIG_APP_NAME, CONFIG_APP_VERSION, CONFIG_COMPILER, CONFIG_COMPILER_VERSION,
               CONFIG_COMPILER_ARCH));
}

AboutDialog::~AboutDialog() {
  delete ui;
}
