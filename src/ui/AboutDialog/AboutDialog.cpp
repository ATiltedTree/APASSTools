#include "AboutDialog.hpp"

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent), ui(new Ui::AboutDialog(this)) {
  ui->setupUi();
  connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &AboutDialog::accept);
}
