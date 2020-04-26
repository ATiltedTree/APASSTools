#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AboutDialog(this)) {
  ui->setupUi();
  connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &AboutDialog::accept);
}

AboutDialog::~AboutDialog() {
  delete ui;
}
