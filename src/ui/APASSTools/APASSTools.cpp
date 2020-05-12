#include "APASSTools.hpp"

APASSTools::APASSTools(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::APASSTools(this)), apass(APASS()), settings(Settings()) {
  ui->setupUi();
  QApplication::setOrganizationName("ATiltedTree");
  QApplication::setApplicationName(CONFIG_APP_NAME);
  this->setupConnections();
  this->restoreGeometry(this->settings.windowGeometry);
  this->ui->observationSpin->setValue(this->settings.appSettings.observationThreshold);
  this->ui->magnitudeSpin->setValue(this->settings.appSettings.magnitudeThreshold);
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
      [[fallthrough]];
    case QMessageBox::Discard:
      event->accept();
      break;
    case QMessageBox::Cancel:
      event->ignore();
      return;
    }
  }
  this->settings.windowGeometry = this->saveGeometry();
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

void APASSTools::updateTree() {
  for (Comet comet : this->apass.getComets()) {
    auto* item = new QTreeWidgetItem();
    for (int i = 0; i < comet.data.size(); i++) {
      item->setText(i, QString::number(comet.data[i].toDouble(), 'd', 3));
    }
    this->ui->CSVDisplay->addTopLevelItem(item);
  }
}

void APASSTools::doImport(const QString& data) {
  this->apass.clearComets();
  auto* bar = new QProgressBar(this);
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
  this->apass.clearComets();
  this->unsavedChanges = false;
}

void APASSTools::onFromCSVFile() {
  CSVDialog csvDialog = CSVDialog(this, &this->settings);
  csvDialog.setModal(true);
  if (csvDialog.exec() == QDialog::Accepted) {
    this->doImport(csvDialog.getResult());
  }
}

void APASSTools::onFromWeb() {
  WebDialog webDialog = WebDialog(this);
  webDialog.setModal(true);
  if (webDialog.exec() == QDialog::Accepted) {
    this->doImport(webDialog.getResult());
  }
}

void APASSTools::onAbout() {
  AboutDialog aboutDialog = AboutDialog(this);
  aboutDialog.setModal(true);
  aboutDialog.exec();
}

void APASSTools::onSettings() {
  SettingsDialog settingsDialog = SettingsDialog(this, &this->settings);
  settingsDialog.setModal(true);
  if (settingsDialog.exec() == QDialog::Accepted) {
    this->ui->observationSpin->setValue(this->settings.appSettings.observationThreshold);
    this->ui->magnitudeSpin->setValue(this->settings.appSettings.magnitudeThreshold);
  }
}

void APASSTools::onSave() {
  this->doSave(false);
}

void APASSTools::onSaveAs() {
  this->doSave(true);
}

void APASSTools::doSave(bool saveAs) {
  if (this->ui->nameEdit->text().isEmpty()) {
    QMessageBox::information(this, "Error!", "Please enter a name!");
    return;
  } else if (!this->unsavedChanges) {
    QMessageBox::information(this, "Error!", "Please import something before saving !");
  }
  QString dirname;
  if (this->settings.appSettings.defaultSaveDir.isEmpty()) {
    this->settings.appSettings.defaultSaveDir =
        QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
    dirname = this->settings.appSettings.defaultSaveDir;
  } else if (saveAs) {
    dirname = QFileDialog::getExistingDirectory(this, tr("Open save location"), "/");
  }

  PRNFile prn = PRNFile(this->apass);
  prn.buildFile(dirname + this->ui->nameEdit->text() + "/" + ".prn");
  if (this->settings.appSettings.createTDFFile) {
    TDFFile tdf = TDFFile(this->ui->nameEdit->text());
    tdf.buildFile(dirname + "/" + this->ui->nameEdit->text() + ".tdf");
  }
  this->unsavedChanges = false;
}
