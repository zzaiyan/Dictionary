#include "home.h"
#include <QStyledItemDelegate>
#include "ui_home.h"

Home::Home(QWidget* parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  ui->lineEdit->installEventFilter(this);
  ui->tableWidget->installEventFilter(this);
  ui->treeWidget->installEventFilter(this);
  ui->tableWidget->setHidden(true);
  ui->treeWidget->setHeaderLabel("headlabel");

  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
  ui->comboBox->setItemDelegate(itemDelegate);
  ui->tableWidget->hide();
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setRowCount(10);
  ui->tableWidget->setFrameShape(QFrame::NoFrame);  //设置无边框
  ui->tableWidget->setShowGrid(false);              //设置不显示格子线
  ui->tableWidget->verticalHeader()->setVisible(false);  //设置垂直头不可见
  ui->tableWidget->horizontalHeader()->setVisible(false);  //设置水平头不可见
  ui->tableWidget->horizontalHeader()->resizeSection(0, 120);
  ui->tableWidget->horizontalHeader()->resizeSection(1, 220);
  ui->tableWidget->setItem(0, 0, new QTableWidgetItem("zhangsan"));
  ui->tableWidget->setItem(0, 1, new QTableWidgetItem("n.法外狂徒"));
}

Home::~Home() {
  delete ui;
}

bool Home::eventFilter(QObject* watched, QEvent* event) {
  if (watched == ui->lineEdit) {
    if (event->type() == QEvent::FocusIn) {
      ui->tableWidget->setHidden(false);
    }
    if (event->type() == QEvent::FocusOut) {
      ui->tableWidget->setHidden(true);
    }
  }
  if (watched == ui->tableWidget) {
    if (event->type() == QEvent::FocusIn) {
      ui->tableWidget->setHidden(false);
    }
    if (event->type() == QEvent::FocusOut) {
      ui->tableWidget->setHidden(true);
    }
  };
  return QWidget::eventFilter(watched, event);
}

void Home::on_comboBox_currentIndexChanged(int index) {
  SearchModelChoice = index;
  return;
}

void Home::on_lineEdit_textChanged(const QString& arg1) {
  vectorForEnglish.clear();
  vectorForChinese.clear();
  ui->tableWidget->clear();
  ui->tableWidget->setHidden(false);
  std::string s;
  if (!(ui->lineEdit->text().isEmpty())) {
    s = ui->lineEdit->text().toStdString();
    ///////////////////////////////////////////////////////Search函数///////////////////////////////////////////////
    // Search(s);
    ///////////////////////////////////////////////////////Search函数///////////////////////////////////////////////
    if (vectorForEnglish.size() <= 0) {
      ui->tableWidget->setHidden(true);
    } else {
      int a = vectorForEnglish.size();
      int temp = (a < 10) ? a : 10;
      for (int i = 0; i < temp; i++) {
        QString str = vectorForChinese[i];
        if (vectorForEnglish[i].length() <= 0) {
          if (i == 0) {
            QMessageBox::warning(nullptr, "warning", "Can't find it !",
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes);
          }
          break;
        } else {
          ui->tableWidget->setItem(i, 0,
                                   new QTableWidgetItem(vectorForEnglish[i]));
          ui->tableWidget->setItem(i, 1,
                                   new QTableWidgetItem(vectorForChinese[i]));
        }
      };
    }
  } else {
    if (vectorForEnglish.size() <= 0) {
      ui->tableWidget->setHidden(true);
    }
  }
  return;
}

void Home::on_pushButton_clicked() {
  vectorForEnglish.clear();
  vectorForChinese.clear();
  ui->treeWidget->clear();
  ui->tableWidget->hide();
  if (!(ui->lineEdit->text().isEmpty())) {
    std::string s;
    QString str1;
    QString str2;
    if (!(ui->lineEdit->text().isEmpty())) {
      s = ui->lineEdit->text().toStdString();
      ///////////////////////////////////////////////////////Search函数///////////////////////////////////////////////
      // Search(s);
      ///////////////////////////////////////////////////////Search函数///////////////////////////////////////////////
      if (vectorForEnglish.size() <= 0) {
        QMessageBox::warning(nullptr, "warning", "Can't find it !",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
      } else {
        if (vectorForEnglish[0].length() <= 0) {
          QMessageBox::warning(nullptr, "warning", "Can't find it !",
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::Yes);
        } else {
          str2 = vectorForChinese[0];
          QTreeWidgetItem* item = new QTreeWidgetItem(
              QStringList() << ui->lineEdit->text() << str2);
          ui->treeWidget->addTopLevelItem(item);
        };
      }
    }
  } else {
    QMessageBox::warning(nullptr, "warning", "Plz tap a word first!",
                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
  }
  return;
};

void Home::on_tableWidget_cellDoubleClicked(int row, int column) {
  if (ui->tableWidget->item(row, column)->text().length() >= 0) {
    ui->lineEdit->insert(ui->tableWidget->item(row, column)->text());
    ui->tableWidget->setHidden(true);
  };
  return;
};
