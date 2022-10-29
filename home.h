#ifndef HOME_H
#define HOME_H

#include <QEvent>
#include <QLabel>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui {
class Home;
}
QT_END_NAMESPACE

class Home : public QWidget {
  Q_OBJECT

 public:
  Home(QWidget* parent = nullptr);
  std::vector<QString> vectorForEnglish;
  std::vector<QString> vectorForChinese;
  bool eventFilter(QObject* watched, QEvent* event);
  QStandardItemModel* standItemModel;
  QStandardItemModel* standItemModel2;
  ~Home();
  int SearchModelChoice = 0;
  ///////////////////////////////////////////////////////Search函数///////////////////////////////////////////////
  void BasicSearch(QString s,
                   std::vector<QString> vForEnglish,
                   std::vector<QString> vForChinese) {}
  void BSTSearch(QString s,
                 std::vector<QString> vForEnglish,
                 std::vector<QString> vForChinese) {}
  void AVLSearch(QString s,
                 std::vector<QString> vForEnglish,
                 std::vector<QString> vForChinese) {}
  void RBSearch(QString s,
                std::vector<QString> vForEnglish,
                std::vector<QString> vForChinese) {}
  void DIYSearch(QString s,
                 std::vector<QString> vForEnglish,
                 std::vector<QString> vForChinese) {}

  void Search(QString s) {
    switch (SearchModelChoice) {
      case 0:
        BasicSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 1:
        BSTSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 2:
        AVLSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 3:
        RBSearch(s, vectorForEnglish, vectorForChinese);
        break;
      case 4:
        DIYSearch(s, vectorForEnglish, vectorForChinese);
        break;
      default:
        break;
    };
  }
  ///////////////////////////////////////////////////////Search函数///////////////////////////////////////////////
 private slots:

  void on_comboBox_currentIndexChanged(int index);

  void on_lineEdit_textChanged(const QString& arg1);

  void on_pushButton_clicked();

  void on_tableWidget_cellDoubleClicked(int row, int column);

 private:
  Ui::Home* ui;
};
#endif  // HOME_H
