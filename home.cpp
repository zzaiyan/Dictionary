#include "home.h"
#include <QStyledItemDelegate>

#include "ui_home.h"

Home::Home(QWidget* parent) : QWidget(parent), ui(new Ui::Home) {
  ui->setupUi(this);
  this->setFixedSize(this->size());
  ui->lineEdit->installEventFilter(this);
  ui->tableWidget->installEventFilter(this);
  ui->historyWidget->installEventFilter(this);
  ui->tableWidget->setHidden(true);
  //  ui->treeWidget->setHeaderLabel("HeadLabel");

  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
  ui->comboBox->setItemDelegate(itemDelegate);
  ui->tableWidget->hide();
  ui->tableWidget->setColumnCount(2);
  ui->tableWidget->setRowCount(10);
  ui->tableWidget->setFrameShape(QFrame::NoFrame);  //设置无边框
  ui->tableWidget->setShowGrid(false);              //设置不显示格子线
  ui->tableWidget->verticalHeader()->setVisible(false);  //设置垂直头不可见
  ui->tableWidget->horizontalHeader()->setVisible(false);  //设置水平头不可见
  ui->tableWidget->horizontalHeader()->resizeSection(0, 180);
  ui->tableWidget->setSelectionBehavior(
      QAbstractItemView::SelectRows);  //整行选中
  //  ui->tableWidget->horizontalHeader()->resizeSection(1, 260);

  //  ui->historyWidget->setFrameShape(QFrame::NoFrame);  //设置无边框
  //  ui->historyWidget->setShowGrid(false);  //设置不显示格子线
  //  ui->historyWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
  //  ui->historyWidget->horizontalHeader()->setVisible(false);
  //  ui->historyWidget->horizontalHeader()->resizeSection(0, 160);
  //  ui->historyWidget->horizontalHeader()->resizeSection(1, 260);

  model = new QStandardItemModel(this);
  model->setHorizontalHeaderItem(0, new QStandardItem("English"));
  model->setHorizontalHeaderItem(1, new QStandardItem("Chinese"));
  //  model->horizontalHeaderItem(0)

  ui->historyWidget->verticalHeader()->setDefaultSectionSize(30);
  ui->historyWidget->horizontalHeader()->setDefaultSectionSize(160);
  ui->historyWidget->setModel(model);
  builded = 0;
  build();  // Read Dict File
  builded = 1;
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
      if (vectorForEnglish.size())
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
  QString s;
  if (!(ui->lineEdit->text().isEmpty())) {
    s = ui->lineEdit->text();

    Search(s);

    if (vectorForEnglish.size() && vectorForEnglish[0] == s) {
      model->insertRow(0);
      model->setItem(0, 0, new QStandardItem(vectorForEnglish[0]));
      model->setItem(0, 1, new QStandardItem(vectorForChinese[0]));
    } else {
      QMessageBox::warning(nullptr, "warning", "Can't find it !",
                           QMessageBox::Yes | QMessageBox::No,
                           QMessageBox::Yes);
    }
  } else {
    QMessageBox::warning(nullptr, "warning", "Plz tap a word first!",
                         QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
  }
  return;
}

void Home::on_tableWidget_cellDoubleClicked(int row, int column) {
  if (ui->tableWidget->item(row, column)->text().length()) {
    ui->lineEdit->setText(ui->tableWidget->item(row, 0)->text());

    model->insertRow(0);
    model->setItem(0, 0, new QStandardItem(vectorForEnglish[row]));
    model->setItem(0, 1, new QStandardItem(vectorForChinese[row]));

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

  bst = new BSTree(seq);
  qDebug() << "bst builded";
  bst->makeClue();
  qDebug() << "bst is Clued";

  avl = new AVLTree(seq);
  qDebug() << "avl builded";

  for (int i = 0; i < seq.size(); i++) {
    rbt.insert({{seq[i].en}, seq[i].zh});
  }

  qDebug() << "rbt builded";

  trp = new Treap(seq);
  qDebug() << "trp builded";

  ifs.close();
}

void Home::BasicSearch(const QString& s) {
  //  qDebug() << "SeqList Start Searching!";
  int r = 0, maxPre = 0;
  for (; r < seq.size(); r++) {
    wCmp++;
    //    if (builded) {
    //      qDebug() << QString("Cmp %1 with %2").arg(s).arg(seq[r].en);
    //    }
    int Pre = getPre(seq[r].en, s);
    maxPre = max(Pre, maxPre);
    if (maxPre >= s.size())
      break;
  }
  for (int i = r, cnt = 0; i < seq.size() && cnt < 10; i++) {
    if (getPre(s, seq[i].en) >= s.size()) {
      vectorForEnglish.push_back(seq[i].en);
      vectorForChinese.push_back(seq[i].zh);
      cnt++;
    }
  }
}

void Home::BSTSearch(const QString& s) {
  qDebug() << "BST Start Searching!";
  auto ptr = bst->Search(s, bst->getRoot());
  qDebug() << "ptr.num = " << ptr->num;

  for (int cnt = 0; ptr != nullptr && cnt < 10; ptr = ptr->ne) {
    if (getPre(s, bst->vec[ptr->num].en) >= s.size()) {
      vectorForEnglish.push_back(bst->vec[ptr->num].en);
      vectorForChinese.push_back(bst->vec[ptr->num].zh);
      cnt++;
    }
  }
}

void Home::AVLSearch(const QString& s) {
  qDebug() << "AVL Start Searching!";
  int r = avl->Search(s, avl->getRoot());
  qDebug() << "r = " << r;
  //  qDebug() << "wCmp = " << wCmp;
  //  if (r == -1) {
  //    qDebug("Searching Failed!");
  //    return;
  //  }
  r = abs(r);
  for (int i = r, cnt = 0; i < seq.size() && cnt < 10; i++) {
    if (getPre(s, seq[i].en) >= s.size()) {
      vectorForEnglish.push_back(seq[i].en);
      vectorForChinese.push_back(seq[i].zh);
      cnt++;
    }
  }
}

void Home::RBSearch(const QString& s) {
  qDebug() << "RBTree Start Searching!";

  auto it = rbt.lower_bound({s});  // the first ele >= s

  int cnt = 0;
  for (; it != rbt.end() && cnt < 10; it++) {
    if (getPre(s, it->first.data) >= s.size()) {
      vectorForEnglish.push_back(it->first.data);
      vectorForChinese.push_back(it->second);
    }
  }
}

void Home::TreapSearch(const QString& s) {
  qDebug() << "Treap Start Searching!";

  int r = trp->query_nex(s);  // the first ele >= s

  for (int i = r, cnt = 0; i < seq.size() && cnt < 10; i++) {
    if (getPre(s, seq[i].en) >= s.size()) {
      vectorForEnglish.push_back(seq[i].en);
      vectorForChinese.push_back(seq[i].zh);
      cnt++;
    }
  }
}
