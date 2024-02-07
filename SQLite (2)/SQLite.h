#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QFileInfo>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTableWidget>
#include <QThread>
#include <QMovie>
#include <QIcon>


QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void Login_chk();
    void Join();
    void Btn_Join();
    void FindID();
    void Btn_FindID();
    void FindPW();
    void Btn_FindPW();
    void JoinCheckID();
    void ReconfirmPW();
    void JoinCheckPHONE();
    void JoinCheckEMAIL();
    void Login();
    void Table_3();
    void Table_4();
    void Table_Car(QString Car);
    void Table_HyunDai(QString Brand);
    void ComboBox_2_change();
    void on_comboBox_8_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void Btn_sale();
    void Btn_Home();
    void Btn_Back();
    void Btn_Main();
    void Btn_Info();
    void Join_chk();
    void Btn_Brand();
    void Btn_Model();
    void Btn_danawa1();
    void Btn_danawa2();
    void Btn_danawa3();
    void Btn_danawa4();
    void Btn_danawa5();
    void on_Kia_clicked();
    void on_Hyundai_clicked();
    void on_Genesis_clicked();
    void on_Chevorlet_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_78_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_34_clicked();
    void on_pushButton_32_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_35_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_comboBox_14_currentIndexChanged(int index);
    void on_pushButton_79_clicked();

    void on_pushButton_100_clicked();

    void on_pushButton_98_clicked();

    void on_pushButton_95_clicked();

    void on_pushButton_94_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QString Brand,Car;

};
#endif // WIDGET_H
