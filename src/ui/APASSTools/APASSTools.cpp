#include "APASSTools.h"
#include "./ui_APASSTools.h"

APASSTools::APASSTools(QWidget* parent) : QMainWindow(parent), ui(new Ui::APASSTools) {
  ui->setupUi(this);
  QApplication::setOrganizationName("ATiltedTree");
  QApplication::setApplicationName(CONFIG_APP_NAME);
  this->setupConnections();
  this->changeSettings(SettingsAction::Init);
  this->changeSettings(SettingsAction::RestoreWindow);
  this->changeSettings(SettingsAction::RestoreValues);
}

APASSTools::~APASSTools() {
  delete ui;
}

void APASSTools::closeEvent(QCloseEvent* event) {
  if (this->unsavedChanges) {
    QMessageBox askForSave;
    askForSave.setText("You have pending changes! Save?");
    askForSave.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard);
    askForSave.setDefaultButton(QMessageBox::Save);
    askForSave.setEscapeButton(QMessageBox::Cancel);
    int ret = askForSave.exec();
    switch (ret) {
    case QMessageBox::Save:
      this->onSave();
      this->changeSettings(SettingsAction::SaveWindow);
      this->changeSettings(SettingsAction::Sync);
      event->accept();
      break;
    case QMessageBox::Cancel:
      event->ignore();
      break;
    case QMessageBox::Discard:
      this->changeSettings(SettingsAction::SaveWindow);
      this->changeSettings(SettingsAction::Sync);
      event->accept();
      break;

    default:
      break;
    }
  } else {
    this->changeSettings(SettingsAction::SaveWindow);
    this->changeSettings(SettingsAction::Sync);
    event->accept();
  }
}

void APASSTools::setupConnections() {
  connect(this->ui->actionAboutQt, &QAction::triggered, this, &QApplication::aboutQt);
  connect(this->ui->actionAbout, &QAction::triggered, this, &APASSTools::onAbout);
  connect(this->ui->actionQuit, &QAction::triggered, this, &APASSTools::close);
  connect(this->ui->actionCSV, &QAction::triggered, this, &APASSTools::onFromCSVFile);
  connect(this->ui->actionWeb, &QAction::triggered, this, &APASSTools::onFromWeb);
  connect(this->ui->actionClear, &QAction::triggered, this, &APASSTools::onClear);
  connect(this->ui->actionSettings, &QAction::triggered, this, &APASSTools::onSettings);
  connect(this->ui->actionSave, &QAction::triggered, this, &APASSTools::onSave);
  connect(this->ui->actionSaveAs, &QAction::triggered, this, &APASSTools::onSaveAs);
}

void APASSTools::changeSettings(SettingsAction action) {
  switch (action) {
  case SettingsAction::SaveWindow:
    Settings::windowSettings.pos  = this->pos();
    Settings::windowSettings.size = this->size();
    break;
  case SettingsAction::RestoreWindow:
    this->resize(Settings::windowSettings.size);
    this->move(Settings::windowSettings.pos);
    break;
  case SettingsAction::Init:
    Settings::init();
    break;
  case SettingsAction::Sync:
    Settings::sync();
    break;
  case SettingsAction::RestoreValues:
    this->ui->observationSpin->setValue(Settings::appSettings.observationThreshold);
    this->ui->magnitudeSpin->setValue(Settings::appSettings.magnitudeThreshold);
    break;
  default:
    Settings::sync();
    break;
  }
}

void APASSTools::updateTree() {
  for (Comet comet : this->apass.getComets()) {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, QString::number(comet.radeg.asDouble(), 'd', 3));
    item->setText(1, QString::number(comet.raerr.asDouble(), 'd', 3));
    item->setText(2, QString::number(comet.decdeg.asDouble(), 'd', 3));
    item->setText(3, QString::number(comet.decerr.asDouble(), 'd', 3));
    item->setText(4, QString::number(comet.Johnson_V.asDouble(), 'd', 3));
    item->setText(5, QString::number(comet.Verr.asDouble(), 'd', 3));
    item->setText(6, QString::number(comet.Vnobs.asDouble(), 'd', 3));
    item->setText(7, QString::number(comet.Johnson_B.asDouble(), 'd', 3));
    item->setText(8, QString::number(comet.Berr.asDouble(), 'd', 3));
    item->setText(9, QString::number(comet.Bnobs.asDouble(), 'd', 3));
    item->setText(10, QString::number(comet.Sloan_u.asDouble(), 'd', 3));
    item->setText(11, QString::number(comet.SUerr.asDouble(), 'd', 3));
    item->setText(12, QString::number(comet.SUnobs.asDouble(), 'd', 3));
    item->setText(13, QString::number(comet.Sloan_g.asDouble(), 'd', 3));
    item->setText(14, QString::number(comet.SGerr.asDouble(), 'd', 3));
    item->setText(15, QString::number(comet.SGnobs.asDouble(), 'd', 3));
    item->setText(16, QString::number(comet.Sloan_r.asDouble(), 'd', 3));
    item->setText(17, QString::number(comet.SRerr.asDouble(), 'd', 3));
    item->setText(18, QString::number(comet.SRnobs.asDouble(), 'd', 3));
    item->setText(19, QString::number(comet.Sloan_i.asDouble(), 'd', 3));
    item->setText(20, QString::number(comet.SIerr.asDouble(), 'd', 3));
    item->setText(21, QString::number(comet.SInobs.asDouble(), 'd', 3));
    item->setText(22, QString::number(comet.Sloan_z.asDouble(), 'd', 3));
    item->setText(23, QString::number(comet.SZerr.asDouble(), 'd', 3));
    item->setText(24, QString::number(comet.SZnobs.asDouble(), 'd', 3));
    item->setText(25, QString::number(comet.PanSTARRS_Y.asDouble(), 'd', 3));
    item->setText(26, QString::number(comet.Yerr.asDouble(), 'd', 3));
    item->setText(27, QString::number(comet.Ynobs.asDouble(), 'd', 3));
    this->ui->CSVDisplay->addTopLevelItem(item);
  }
}

void APASSTools::doImport(QString data) {
  this->apass.clearComets();
  QProgressBar* bar = new QProgressBar(this);
  this->ui->statusbar->addWidget(bar, 1);
  this->apass.importCSV(data, this->ui->observationSpin->value(), this->ui->magnitudeSpin->value(),
                        bar);
  this->updateTree();
  this->unsavedChanges = true;
  this->ui->statusbar->removeWidget(bar);
  this->ui->statusbar->showMessage("Import done.", 2000);
}

void APASSTools::onClear() {
  this->ui->CSVDisplay->clear();
  this->unsavedChanges = false;
}

void APASSTools::onFromCSVFile() {
  CSVDialog csvDialog;
  csvDialog.setModal(true);
  if (csvDialog.exec() == QDialog::Accepted) {
    this->doImport(csvDialog.getResult());
  }
}

void APASSTools::onFromWeb() {
  WebDialog webDialog;
  webDialog.setModal(true);
  if (webDialog.exec() == QDialog::Accepted) {
    this->doImport(webDialog.getResult());
  }
}

void APASSTools::onAbout() {
  AboutDialog aboutDialog;
  aboutDialog.setModal(true);
  aboutDialog.exec();
}

void APASSTools::onSettings() {
  SettingsDialog settingsDialog;
  settingsDialog.setModal(true);
  if (settingsDialog.exec() == QDialog::Accepted) {
    this->changeSettings(SettingsAction::RestoreValues);
  }
}

void APASSTools::onSave() {
  if (Settings::appSettings.defaultSaveDir.isEmpty()) {
    QString dirname = QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
    Settings::appSettings.defaultSaveDir = dirname;
    PRN prn                              = PRN(this->apass);
    if (Settings::appSettings.createTDFFile) {
      TDF* tdf = new TDF(this->ui->nameEdit->text());
      tdf->buildFile(Settings::appSettings.defaultSaveDir + "/" + this->ui->nameEdit->text() +
                     ".tdf");
    }
    prn.buildFile(dirname + this->ui->nameEdit->text() + "/" + ".prn");
  } else {
    PRN prn = PRN(this->apass);
    if (Settings::appSettings.createTDFFile) {
      TDF* tdf = new TDF(this->ui->nameEdit->text());
      tdf->buildFile(Settings::appSettings.defaultSaveDir + "/" + this->ui->nameEdit->text() +
                     ".tdf");
    }
    prn.buildFile(Settings::appSettings.defaultSaveDir + "/" + this->ui->nameEdit->text() + ".prn");
  }
  this->unsavedChanges = false;
}
void APASSTools::onSaveAs() {
  QString dirname = QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
  Settings::appSettings.defaultSaveDir = dirname;
  PRN prn                              = PRN(this->apass);
  if (Settings::appSettings.createTDFFile) {
    TDF* tdf = new TDF(this->ui->nameEdit->text());
    tdf->buildFile(Settings::appSettings.defaultSaveDir + "/" + this->ui->nameEdit->text() +
                   ".tdf");
  }
  prn.buildFile(dirname + this->ui->nameEdit->text() + "/" + ".prn");
  this->unsavedChanges = false;
}
