#include "home.h"
#include <QStyledItemDelegate>

#include "ui_home.h"

Home::Home(QWidget* parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  ui->lineEdit->installEventFilter(this);
  ui->tableWidget->installEventFilter(this);
  ui->treeWidget->installEventFilter(this);
  ui->tableWidget->setHidden(true);
  ui->treeWidget->setHeaderLabel("HeadLabel");

  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
  ui->comboBox->setItemDelegate(itemDelegate);
  ui->tableWidget->hide();
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setRowCount(10);
  ui->tableWidget->setFrameShape(QFrame::NoFrame);  //设置无边框
  ui->tableWidget->setShowGrid(false);              //设置不显示格子线
  ui->tableWidget->verticalHeader()->setVisible(false);  //设置垂直头不可见
  ui->tableWidget->horizontalHeader()->setVisible(false);  //设置水平头不可见
  ui->tableWidget->horizontalHeader()->resizeSection(0, 160);
  ui->tableWidget->horizontalHeader()->resizeSection(1, 260);

  build();  // Read Dict File
}

Home::~Home() {
  delete ui;
}

int Home::getPre(const QString& str1, const QString& str2) const {
  int m = min(str1.length(), str2.length()), ret = 0;
  for (int i = 0; i < m; i++)
    ret += str1[i] == str2[i];
  return ret;
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
}

void Home::on_lineEdit_textChanged(const QString& arg1) {
  vectorForEnglish.clear();
  vectorForChinese.clear();
  ui->tableWidget->clear();
  ui->tableWidget->setHidden(false);
  QString s;
  if (!(ui->lineEdit->text().isEmpty())) {
    s = ui->lineEdit->text();
    Search(s);
    if (vectorForEnglish.size() <= 0) {
      ui->tableWidget->setHidden(true);
    } else {
      int a = vectorForEnglish.size();
      int temp = min(a, 10);
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
  //  ui->treeWidget->clear();
  ui->tableWidget->hide();
  if (!(ui->lineEdit->text().isEmpty())) {
    QString s;
    QString str1;
    QString str2;
    if (!(ui->lineEdit->text().isEmpty())) {
      s = ui->lineEdit->text();

      Search(s);

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
  if (ui->tableWidget->item(row, column)->text().length()) {
    ui->lineEdit->setText(ui->tableWidget->item(row, column)->text());
    ui->tableWidget->setHidden(true);
  }
}

void Home::record(int t) {
  ui->labelCmp->setText(QString("CmpTimes: %1").arg(t));
}

void Home::build() {
  ifstream ifs("/home/z/Desktop/QPro/Dictionary/EnWords.csv", ios::in);
  if (!ifs) {
    qDebug() << "File open error!";
    exit(1);
  }
  seq.clear();
  string buf;
  while (getline(ifs, buf)) {
    int div = 0, len = buf.size();
    for (; div < len && buf[div] != ','; div++)
      ;
    QString en = QString::fromLocal8Bit(buf.data(), div++);
    QString zh = QString::fromLocal8Bit(buf.data() + div, len - div);
    //    qDebug() << en << zh;
    seq.push_back({en, zh});
  }
  sort(seq.begin(), seq.end());
  qDebug() << "seq.size = " << seq.size();
  //  qDebug() << seq.front().zh;

  // Start build AVL
  avl = new AVLTree(seq);
  auto rt = avl->getRoot();
  for (int i = 0; i < seq.size(); i++) {
    avl->Insert(i, rt);
    rbt.insert({{seq[i].en}, seq[i].zh});
  }
  qDebug() << "avl.size = " << avl->vec.size();
  qDebug() << "rbt.size = " << rbt.size();
  ifs.close();
}

void Home::BasicSearch(QString s) {
  int r = 0, maxPre = 0;
  for (; r < seq.size(); r++) {
    wCmp++;
    int Pre = getPre(seq[r].en, s);
    maxPre = max(Pre, maxPre);
    if (maxPre >= s.size())
      break;
  }
  record(wCmp);
  for (int i = r, cnt = 0; i < seq.size() && cnt < 10; i++) {
    if (getPre(s, seq[i].en) >= s.size()) {
      vectorForEnglish.push_back(seq[i].en);
      vectorForChinese.push_back(seq[i].zh);
      cnt++;
    }
  }
}

void Home::AVLSearch(QString s) {
  int r = avl->Search(s, avl->getRoot());
  qDebug() << "r = " << r;
  record(wCmp);
  //  qDebug() << "wCmp = " << wCmp;
  if (r == -1) {
    qDebug("Searching Failed!");
    return;
  }
  r = abs(r);
  for (int i = r, cnt = 0; i < seq.size() && cnt < 10; i++) {
    if (getPre(s, seq[i].en) >= s.size()) {
      vectorForEnglish.push_back(seq[i].en);
      vectorForChinese.push_back(seq[i].zh);
      cnt++;
    }
  }
}

void Home::RBSearch(QString s) {
  auto it = rbt.lower_bound({s});
  if (it->first.data != s) {
    qDebug("Searching Failed!");
  }
  record(wCmp);
  int cnt = 0;
  for (; it != rbt.end() && cnt < 10; it++) {
    if (getPre(s, it->first.data) >= s.size()) {
      vectorForEnglish.push_back(it->first.data);
      vectorForChinese.push_back(it->second);
    }
  }
}
