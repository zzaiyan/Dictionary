#include "home.h"
#include "ui_home.h"

Home::Home(QWidget* parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  ui->comboBox->setCurrentIndex(1);
  ui->currentTable->setColumnCount(2);
  ui->currentTable->setHorizontalHeaderItem(0, new QTableWidgetItem("单词"));
  ui->currentTable->setHorizontalHeaderItem(1, new QTableWidgetItem("释义"));
  ui->currentTable->setRowCount(20);
}

Home::~Home() {
  delete ui;
}
