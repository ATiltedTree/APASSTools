#include "APASSTools.h"

APASSTools::APASSTools(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::APASSTools(this)), apass(APASS::New()) {
  ui->setupUi();
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
  for (Comet::Ref comet : this->apass->getComets()) {
    auto* item = new QTreeWidgetItem();
    for (int i = 0; i < comet->data.size(); i++) {
      item->setText(i, QString::number(comet->data[i].toDouble(), 'd', 3));
    }
    this->ui->CSVDisplay->addTopLevelItem(item);
  }
}

void APASSTools::doImport(const QString& data) {
  this->apass->clearComets();
  auto* bar = new QProgressBar(this);
  this->ui->statusbar->addWidget(bar, 1);
  this->apass->importCSV(data, this->ui->observationSpin->value(), this->ui->magnitudeSpin->value(),
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
  CSVDialog::Ref csvDialog = CSVDialog::New(this);
  csvDialog->setModal(true);
  if (csvDialog->exec() == QDialog::Accepted) {
    this->doImport(csvDialog->getResult());
  }
}

void APASSTools::onFromWeb() {
  WebDialog::Ref webDialog = WebDialog::New(this);
  webDialog->setModal(true);
  if (webDialog->exec() == QDialog::Accepted) {
    this->doImport(webDialog->getResult());
  }
}

void APASSTools::onAbout() {
  AboutDialog::Ref aboutDialog = AboutDialog::New(this);
  aboutDialog->setModal(true);
  aboutDialog->exec();
}

void APASSTools::onSettings() {
  SettingsDialog::Ref settingsDialog = SettingsDialog::New(this);
  settingsDialog->setModal(true);
  if (settingsDialog->exec() == QDialog::Accepted) {
    this->changeSettings(SettingsAction::RestoreValues);
  }
}

void APASSTools::onSave() {
  if (this->ui->nameEdit->text().isEmpty()) {
    SHOW_ERROR(Please enter a name !)
  } else if (!this->unsavedChanges) {
    SHOW_ERROR(Please import something before saving !)
  }
  if (Settings::appSettings.defaultSaveDir.isEmpty()) {
    QString dirname = QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
    Settings::appSettings.defaultSaveDir = dirname;
  }
  this->doSave(Settings::appSettings.defaultSaveDir, Settings::appSettings.createTDFFile);
}

void APASSTools::onSaveAs() {
  if (this->ui->nameEdit->text().isEmpty()) {
    SHOW_ERROR(Please enter a name !)
  } else if (!this->unsavedChanges) {
    SHOW_ERROR(Please import something before saving !)
  }
  QString dirname = QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
  Settings::appSettings.defaultSaveDir = dirname;

  this->doSave(Settings::appSettings.defaultSaveDir, Settings::appSettings.createTDFFile);
}

void APASSTools::doSave(const QString& dirname, bool createTDF) {
  PRN::Ref prn = PRN::New(this->apass);
  prn->buildFile(dirname + this->ui->nameEdit->text() + "/" + ".prn");
  if (createTDF) {
    TDF::Ref tdf = TDF::New(this->ui->nameEdit->text());
    tdf->buildFile(dirname + "/" + this->ui->nameEdit->text() + ".tdf");
  }
  this->unsavedChanges = false;
}
