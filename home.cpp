#include "home.h"
#include "ui_home.h"

Home::Home(QWidget* parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  // set RegExp to match English Words
  QRegExp rx("^[A-Za-z]+$");
  ui->lineEdit->setValidator(new QRegExpValidator(rx, this));
  // set Default Data Structure
  ui->comboBox->setCurrentIndex(1);
  // set Table Headers
  ui->currentTable->setColumnCount(2);
  ui->currentTable->setHorizontalHeaderItem(0, new QTableWidgetItem("单词"));
  ui->currentTable->setHorizontalHeaderItem(1, new QTableWidgetItem("释义"));
  ui->histaryTable->setColumnCount(2);
  ui->histaryTable->setHorizontalHeaderItem(0, new QTableWidgetItem("单词"));
  ui->histaryTable->setHorizontalHeaderItem(1, new QTableWidgetItem("释义"));
  ui->currentTable->setRowCount(20);
}

Home::~Home() {
  delete ui;
}
