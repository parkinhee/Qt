#include "SQLite.h"
#include "ui_SQLite.h"
#include <QString>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 버튼 활성화 함수
    Login_chk();
    Join_chk();

    QMovie*Movie = new QMovie("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/ad.gif"); //광고 띄우기
    ui->page_1_ad1->setMovie(Movie);
    Movie->setScaledSize(QSize(620,51));
    Movie->start();

        // 할부 정보 링크
    ui -> ad_1-> setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui -> ad_1-> setOpenExternalLinks(1);
    ui -> ad_1-> setText("<a href=\"https://mauto.danawa.com/newcar/?Work=finance&Tab=samsungC2\"style=\"background-color:black;""color: white;\">혜택 알아보기 </a>");
    ui -> ad_2-> setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui -> ad_2-> setOpenExternalLinks(1);
    ui -> ad_2-> setText("<a href=\"https://mauto.danawa.com/newcar/?Work=finance&Tab=woori\"style=\"background-color:black;""color: white;\"> 혜택 알아보기 </a>");
    ui -> ad_3-> setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui -> ad_3-> setOpenExternalLinks(1);
    ui -> ad_3-> setText("<a href=\"https://mauto.danawa.com/newcar/?Work=finance&Tab=lotte\"style=\"background-color:black;""color: white;\"> 혜택 알아보기</a>");
    ui->ad_4->setText("<a href=\"https://mauto.danawa.com/newcar/?Work=cash&Tab=samsung\" style=\"color: black;\">11111111111111111111111111</a>");
    ui->ad_5->setText("<a href=\"https://mauto.danawa.com/newcar/?Work=cash&Tab=lotte\" style=\"color: black;\">11111111111111111111111111</a>");
    ui->ad_6->setText("<a href=\"https://mauto.danawa.com/newcar/?Work=cash&Tab=hana\" style=\"color: black;\">11111111111111111111111111</a>");

    // 첫 화면 지정
    ui -> stackedWidget -> setCurrentIndex(0);

    // 판매실적 첫 탭 지정
    ui -> tabWidget -> setCurrentIndex(0);
    ui -> tabWidget_2 -> setCurrentIndex(0);
    ui -> tabWidget_3 -> setCurrentIndex(0);
    ui -> tabWidget_4 -> setCurrentIndex(0);
    ui -> tabWidget_5 -> setCurrentIndex(0);
    ui -> tabWidget_6 -> setCurrentIndex(0);

    // 판매실적 Tab 크기 조정
    ui -> tabWidget-> setStyleSheet("QTabBar::tab {height: 25px; width: 206px;}");
    ui -> tabWidget_2 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");
    ui -> tabWidget_3 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");
    ui -> tabWidget_4 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");
    ui -> tabWidget_5 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");
    ui -> tabWidget_6 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");
    ui -> tabWidget_7 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");
    ui -> tabWidget_8 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");
    ui -> tabWidget_9 -> setStyleSheet("QTabBar::tab {height: 25px; width: 305px;}");



    // 비밀번호 입력시 정수만 입력
    ui -> lineEdit_2 -> setValidator(new QIntValidator(0, 9999,this));

    // DB 오픈
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/Users/IOT/Desktop/Important/SQLite3/USER_DATA");

    if(!mydb.open())
        ui -> label -> setText("Fail Database");
    else
        ui -> label -> setText("DB Connect");
}
Widget::~Widget()
{
    delete ui;
}
void Widget::Login_chk()                // 로그인 버튼 활성화
{
    QString ID,PW;
    ID = ui -> lineEdit_6 -> text();
    PW = ui -> lineEdit_7 -> text();
    if(ID.length() > 3 && PW.length() > 3)
    {
        ui -> pushButton_2 -> setEnabled(true);
    }
    else
    {
        ui -> pushButton_2 -> setDisabled(true);
    }
}
void Widget::Join_chk()                 // 회원가입 버튼 활성화
{
    QString ID,PW,NAME,PHONE,EMAIL;
    ID = ui -> lineEdit -> text();
    PW = ui -> lineEdit_2 -> text();
    NAME = ui -> lineEdit_3 -> text();
    PHONE = ui -> lineEdit_4 -> text();
    EMAIL = ui -> lineEdit_5 -> text();

    if(ID.length() >= 3 && PW.length() > 3 && NAME.length() >= 3 && PHONE.length() >= 3 && EMAIL.length() >= 3)
    {
        ui -> pushButton -> setEnabled(true);
    }
    else
    {
        ui -> pushButton -> setDisabled(true);
    }
}
void Widget::Login()                    // 로그인
{
    QString ID,PW;
    ID = ui -> lineEdit_6 -> text();
    PW = ui -> lineEdit_7 -> text();
    QSqlQuery query;
    query.prepare("SELECT * FROM USER_DATA WHERE ID = :ID AND PW = :PW");
    query.bindValue(":ID",ID);
    query.bindValue(":PW",PW);
    if(query.exec() && query.next())
    {
        QMessageBox MsgBox;
        MsgBox.setText("로그인 되었습니다.");
        MsgBox.exec();
        ui -> lineEdit_6 -> clear();
        ui -> lineEdit_7 -> clear();
        ui -> stackedWidget -> setCurrentIndex(5);
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText("회원정보가 일치하지 않습니다.");
        MsgBox.exec();
        ui -> lineEdit_6 -> clear();
        ui -> lineEdit_7 -> clear();
        ui -> lineEdit_6 -> setFocus();
    }
}
void Widget::Join()                 // 회원가입
{
    QString ID,PW,NAME,PHONE,EMAIL;
    QThread thread;
    ID = ui -> lineEdit -> text();
    PW = ui -> lineEdit_2 -> text();
    NAME = ui -> lineEdit_3 -> text();
    PHONE = ui -> lineEdit_4 -> text();
    EMAIL = ui -> lineEdit_5 -> text() + ui -> label_84 -> text() + ui-> comboBox_19 -> currentText();
    QSqlQuery query;
    query.prepare("INSERT INTO USER_DATA (ID,PW,NAME,PHONE,EMAIL)"
                  "VALUES (:ID, :PW, :NAME, :PHONE, :EMAIL)");
    query.bindValue(":ID",ID);
    query.bindValue(":PW",PW);
    query.bindValue(":NAME",NAME);
    query.bindValue(":PHONE",PHONE);
    query.bindValue(":EMAIL",EMAIL);
    query.exec();

    QMessageBox MsgBox;
    MsgBox.setText("회원가입 되었습니다.");
    MsgBox.exec();
    ui -> lineEdit -> clear();
    ui -> lineEdit_2 -> clear();
    ui -> lineEdit_3 -> clear();
    ui -> lineEdit_4 -> clear();
    ui -> lineEdit_5 -> clear();
    ui -> lineEdit_15 -> clear();
    ui -> stackedWidget -> setCurrentIndex(0);
}
void Widget::JoinCheckID()      // ID 중복확인
{
    QString ID;
    ID = ui -> lineEdit -> text();
    QSqlQuery query;
    query.prepare("SELECT ID FROM USER_DATA WHERE ID = :ID");
    query.bindValue(":ID",ID);
    if(query.exec() && query.next())
    {
        QMessageBox MsgBox;
        MsgBox.setStyleSheet("background-color: white ; color : red");
        MsgBox.setText("중복된 ID입니다.");
        MsgBox.exec();
        ui -> lineEdit -> clear();
        ui -> lineEdit -> setFocus();
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText("사용 가능한 ID입니다.");
        MsgBox.exec();
        ui -> lineEdit_2 -> setFocus();
    }
}
void Widget::JoinCheckPHONE()       // PHONE 중복확인
{
    QString PHONE;
    PHONE = ui -> lineEdit_4 -> text();
    QSqlQuery query;
    query.prepare("SELECT PHONE FROM USER_DATA WHERE PHONE = :PHONE");
    query.bindValue(":PHONE",PHONE);
    if(query.exec() && query.next())
    {
        QMessageBox MsgBox;
        MsgBox.setStyleSheet("background-color: white ; color : red");
        MsgBox.setText("중복된 전화번호입니다.");
        MsgBox.exec();
        ui -> lineEdit_4 -> clear();
        ui -> lineEdit_4 -> setFocus();
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText("사용 가능한 전화번호입니다.");
        MsgBox.exec();
        ui -> lineEdit_5 -> setFocus();
    }
}
void Widget::JoinCheckEMAIL()           // EMAIL 중복확인
{
    QString EMAIL;
    EMAIL = ui -> lineEdit_5 -> text() + ui -> label_84 -> text() + ui-> comboBox_19 -> currentText();
    QSqlQuery query;
    query.prepare("SELECT EMAIL FROM USER_DATA WHERE EMAIL = :EMAIL");
    query.bindValue(":EMAIL",EMAIL);
    if(query.exec() && query.next())
    {
        QMessageBox MsgBox;
        MsgBox.setStyleSheet("background-color: white ; color : red");
        MsgBox.setText("중복된 EMAIL입니다.");
        MsgBox.exec();
        ui -> lineEdit_5 -> clear();
        ui -> lineEdit_5 -> setFocus();
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setText("사용 가능한 EMAIL입니다.");
        MsgBox.exec();
    }
}
void Widget::ReconfirmPW()                  // 비밀번호 확인
{
    QString PW,RECONFIRM_PW;
    PW = ui -> lineEdit_2 -> text();
    RECONFIRM_PW = ui -> lineEdit_15 -> text();
    if(PW == RECONFIRM_PW)
    {
        QMessageBox MsgBox;
        MsgBox.setText("비밀번호가 확인되었습니다.");
        MsgBox.exec();
        ui -> lineEdit_3 -> setFocus();
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setStyleSheet("background-color: white ; color : red");
        MsgBox.setText("비밀번호가 일치하지 않습니다.");
        MsgBox.exec();
        ui -> lineEdit_15 -> clear();
        ui -> lineEdit_15 -> setFocus();
    }
}
void Widget::FindID()                   // ID 찾기
{
    QString NAME,PHONE,EMAIL;
    NAME = ui -> lineEdit_8 -> text();
    PHONE = ui -> lineEdit_9 -> text();
    EMAIL = ui -> lineEdit_10 -> text() + ui -> label_86 -> text() + ui-> comboBox_20 -> currentText();
    QSqlQuery query;
    query.prepare("SELECT ID FROM USER_DATA WHERE NAME = :NAME AND PHONE = :PHONE AND EMAIL = :EMAIL");
    query.bindValue(":NAME",NAME);
    query.bindValue(":PHONE",PHONE);
    query.bindValue(":EMAIL",EMAIL);
    if(query.exec() && query.next())
    {
        QString Find_ID = query.value(0).toString();
        QMessageBox MsgBox;
        MsgBox.setText("ID는  "+Find_ID+"  입니다.");
        MsgBox.exec();
        ui -> stackedWidget -> setCurrentIndex(1);
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setStyleSheet("background-color: white ; color : red");
        MsgBox.setText("회원정보가 일치하지 않습니다.");
        MsgBox.exec();
        ui -> lineEdit_8 -> clear();
        ui -> lineEdit_9 -> clear();
        ui -> lineEdit_10 -> clear();
    }
}
void Widget::FindPW()                   // PW 찾기
{
    QString ID,NAME,PHONE,EMAIL;

    ID = ui -> lineEdit_11 -> text();
    NAME = ui -> lineEdit_12 -> text();
    PHONE = ui -> lineEdit_13 -> text();
    EMAIL = ui -> lineEdit_14 -> text() + ui -> label_87 -> text() + ui-> comboBox_21 -> currentText();
    QSqlQuery query;
    query.prepare("SELECT PW FROM USER_DATA WHERE ID = :ID AND NAME = :NAME AND PHONE = :PHONE AND EMAIL = :EMAIL");
    query.bindValue(":ID",ID);
    query.bindValue(":NAME",NAME);
    query.bindValue(":PHONE",PHONE);
    query.bindValue(":EMAIL",EMAIL);
    if(query.exec() && query.next())
    {
        QString Find_PW = query.value(0).toString();
        QMessageBox MsgBox;
        MsgBox.setText("PW는  "+Find_PW+"  입니다.");
        MsgBox.exec();
        ui -> stackedWidget -> setCurrentIndex(1);
    }
    else
    {
        QMessageBox MsgBox;
        MsgBox.setStyleSheet("background-color: white ; color : red");
        MsgBox.setText("회원정보가 일치하지 않습니다.");
        MsgBox.exec();
        ui -> lineEdit_11 -> clear();
        ui -> lineEdit_12 -> clear();
        ui -> lineEdit_13 -> clear();
        ui -> lineEdit_14 -> clear();
    }
}
void Widget::Table_3()                                  // 전체 모델top10 월별 + 첫화면
{
    // 각 브랜드의 아이콘을 생성하고 설정
    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);

    QString CAR,E_A_1,E_A,E_A_2,RATE;
    int RATE_1;
    int row = 0;
    QString row1,BRAND;
    QString query;
    int tabWidget5 = ui->tabWidget_5->currentIndex();
    // 현재 탭을 확인
    if(tabWidget5==0)
    {
        // 선택된 탭이 첫번째 탭일경우 국산브랜드들의 데이터를 가져옴
        query = QString("SELECT BRAND,MODEL,EA_12,EA_12-EA_11 FROM DNAWA_DATA WHERE BRAND IN('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY EA_12-EA_11 DESC LIMIT 10");
        QSqlQuery qry(query);
        qry.exec();
        ui -> tableWidget_3 -> setRowCount(0);
        //쿼리문으로 실행한데이터를 한줄씩읽어서 데이터를 처리
        while(qry.next())
        {
            //각 변수에 읽은데이터를 저장
            BRAND = qry.value(0).toString();
            CAR = qry.value(1).toString();
            E_A = qry.value(2).toString();
            E_A_1 = QString("%1대").arg(E_A);
            RATE = qry.value(3).toString();
            RATE_1=qry.value(3).toInt();//전월대비 판매량의 음수양수 확인
            if(RATE_1>0)
            {

                RATE=QString("▲ %1").arg(RATE_1);//양수

            }
            else if(RATE_1<0)
            {
                RATE_1=RATE_1*-1;
                RATE=QString("▼ %1").arg(RATE_1);//음수
            }
            else
            {
                RATE=QString("(-) %1").arg(RATE_1);//변화없음
            }
            //각 변수에 저장된 데이터를 테이블위젯에 아이템으로 추가
            row1=QString("%1").arg(row+1);
            ui -> tableWidget_3 -> insertRow(row);
            ui -> tableWidget_3 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_3 -> setItem(row,2,new QTableWidgetItem(CAR));
            ui -> tableWidget_3 -> setItem(row,3,new QTableWidgetItem(E_A_1));
            ui -> tableWidget_3 -> setItem(row,4,new QTableWidgetItem(RATE));
            //브랜드에 따라 해당하는 아이콘을 할당 및 출력
            if(BRAND == "Hyundai")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item1));
            }
            else if(BRAND == "Kia")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item2));
            }
            else if(BRAND == "Genesis")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item3));
            }
            else if(BRAND == "Chevorlet")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item4));
            }
            else if(BRAND == "KG-mobility")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item5));
            }
            else if(BRAND == "Renaukorea")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item6));
            }
            ui->tableWidget_3->item(row,3)->setForeground(Qt::blue);
            ui->tableWidget_3->item(row,4)->setForeground(Qt::red);

            row++;
        }
    }
    else
    {
        //현재 탭이 두번째 탭일때 수입차브랜드들의 데이터를 가
        query = QString("SELECT BRAND,MODEL,EA_12,EA_12-EA_11 FROM DNAWA_DATA WHERE BRAND IN('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY EA_12-EA_11 DESC LIMIT 10");
        QSqlQuery qry(query);
        qry.exec();
        ui -> tableWidget_5 -> setRowCount(0);
        while(qry.next())
        {
            BRAND = qry.value(0).toString();
            CAR = qry.value(1).toString();
            E_A = qry.value(2).toString();
            E_A_2 = QString("%1대").arg(E_A);
            RATE = qry.value(3).toString();
            RATE_1=qry.value(3).toInt();
            if(RATE_1>0)
            {
                RATE=QString("▲ %1").arg(RATE_1);
            }
            else if(RATE_1<0)
            {
                RATE_1=RATE_1*-1;
                RATE=QString("▼ %1").arg(RATE_1);
            }
            else
            {
                RATE=QString("(-) %1").arg(RATE_1);
            }
            row1=QString("%1").arg(row+1);
            ui -> tableWidget_5 -> insertRow(row);
            ui -> tableWidget_5 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_5 -> setItem(row,2,new QTableWidgetItem(CAR));
            ui -> tableWidget_5 -> setItem(row,3,new QTableWidgetItem(E_A_2));
            ui -> tableWidget_5 -> setItem(row,4,new QTableWidgetItem(RATE));
            if(BRAND == "Mercedes-Benz")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item7));
            }
            else if(BRAND == "Audi")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item8));
            }
            else if(BRAND == "Porsche")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item9));
            }
            else if(BRAND == "Maserati")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item10));
            }
            ui->tableWidget_5->item(row,3)->setForeground(Qt::blue);
            ui->tableWidget_5->item(row,4)->setForeground(Qt::red);
            row++;
        }
    }
}
void Widget::Table_4()                                      // 전체 모델별 top10 기간 조회
{
    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);

    QString BRAND,CAR,E_A,PERCENT;
    int i=0;
    int row=0;
    int comboBox4 = ui -> comboBox_4-> currentIndex();
    int comboBox6 = ui -> comboBox_6-> currentIndex();
    comboBox4+=1;
    comboBox6+=1;
    QString value,value1;
    for(i=comboBox4;i<=comboBox6;i++)
    {
        if(i>comboBox4)
            value+="+";
        value=value+QString("EA_%1").arg(i);
    }

    if(ui -> tabWidget_5 ->currentIndex() == 0)
    {
        ui -> tableWidget_3->setRowCount(0);
        QString query = QString("SELECT BRAND,MODEL,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA WHERE BRAND IN('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY %1 DESC LIMIT 10").arg(value);
        QSqlQuery qry(query);
        qry.exec();

        while(qry.next())
        {
            BRAND = qry.value(0).toString();
            CAR = qry.value(1).toString();
            E_A = qry.value(2).toString();
            PERCENT = qry.value(3).toString();

            ui -> tableWidget_3 -> insertRow(row);
            ui -> tableWidget_3 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_3 -> setItem(row,2,new QTableWidgetItem(CAR));
            ui -> tableWidget_3 -> setItem(row,3,new QTableWidgetItem(E_A));
            ui -> tableWidget_3 -> setItem(row,4,new QTableWidgetItem(PERCENT));
            if(BRAND == "Hyundai")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item1));
            }
            else if(BRAND == "Kia")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item2));
            }
            else if(BRAND == "Genesis")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item3));
            }
            else if(BRAND == "Chevorlet")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item4));
            }
            else if(BRAND == "KG-mobility")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item5));
            }
            else if(BRAND == "Renaukorea")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item6));
            }

            row++;
        }
    }
    else
    {
        ui -> tableWidget_5->setRowCount(0);
        QString query = QString("SELECT BRAND,MODEL,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA WHERE BRAND IN ('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY %1 desc LIMIT 10;").arg(value);
        QSqlQuery qry(query);
        qry.exec();

        while(qry.next())
        {
            BRAND = qry.value(0).toString();
            CAR = qry.value(1).toString();
            E_A = qry.value(2).toString();
            PERCENT = qry.value(3).toString();

            ui -> tableWidget_5 -> insertRow(row);
            ui -> tableWidget_5 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_5 -> setItem(row,2,new QTableWidgetItem(CAR));
            ui -> tableWidget_5 -> setItem(row,3,new QTableWidgetItem(E_A));
            ui -> tableWidget_5 -> setItem(row,4,new QTableWidgetItem(PERCENT));
            if(BRAND == "Mercedes-Benz")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item7));
            }
            else if(BRAND == "Audi")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item8));
            }
            else if(BRAND == "Porsche")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item9));
            }
            else if(BRAND == "Maserati")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item10));
            }
            row++;
        }
    }
}
void Widget::ComboBox_2_change()                    // 전체 기간 top5 조회
{
    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);

    QString EA,MODEL,BRAND,PERCENT;
    int i=0;
    int row=0;
    int comboBox2 = ui -> comboBox_2-> currentIndex();
    ui -> tableWidget -> setRowCount(0);
    comboBox2+=1;
    QString value;
    for(i=comboBox2;i<=comboBox2;i++)
    {
        if(i>comboBox2)
            value+="+";
        value=value+QString("EA_%1").arg(i);
    }
    if(ui -> tabWidget_4 ->currentIndex() == 0)
    {
        ui -> tableWidget->setRowCount(0);
        QString query = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY 2 DESC LIMIT 5;").arg(value);
        QSqlQuery qry(query);
        qry.exec();

        while(qry.next())
        {
            BRAND=qry.value(0).toString();
            EA=qry.value(1).toString();
            PERCENT=qry.value(2).toString();

            ui -> tableWidget -> insertRow(row);
            ui -> tableWidget -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget -> setItem(row,2,new QTableWidgetItem(EA));
            ui -> tableWidget -> setItem(row,3,new QTableWidgetItem(PERCENT));
            if(BRAND == "Hyundai")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item1));
            }
            else if(BRAND == "Kia")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item2));
            }
            else if(BRAND == "Genesis")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item3));
            }
            else if(BRAND == "Chevorlet")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item4));
            }
            else if(BRAND == "KG-mobility")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item5));
            }
            else if(BRAND == "Renaukorea")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item6));
            }
            row++;
        }
    }
    else
    {
        ui -> tableWidget_4->setRowCount(0);
        QString query = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN ('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY 3 desc LIMIT 5;").arg(value);
        QSqlQuery qry(query);
        qry.exec();

        while(qry.next())
        {
            BRAND=qry.value(0).toString();
            EA=qry.value(1).toString();
            PERCENT=qry.value(2).toString();

            ui -> tableWidget_4 -> insertRow(row);
            ui -> tableWidget_4 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_4 -> setItem(row,2,new QTableWidgetItem(EA));
            ui -> tableWidget_4 -> setItem(row,3,new QTableWidgetItem(PERCENT));
            if(BRAND == "Mercedes-Benz")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item7));
            }
            else if(BRAND == "Audi")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item8));
            }
            else if(BRAND == "Porsche")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item9));
            }
            else if(BRAND == "Maserati")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item10));
            }
            row++;
        }
    }
}
void Widget::on_comboBox_2_currentIndexChanged(int index)           // 전체 월별 top5 조회
{
    int comboBox2 = ui -> comboBox_2-> currentIndex();
    index+=1;
    QString EA;
    if(index==1)
    {
        EA="EA_1";
    }
    else
    {
        EA="";
        EA=EA+QString("EA_%1-EA_%2").arg(index).arg(comboBox2);
    }
    QString CAR,E_A,E_A_1,E_A_2,RATE;
    int RATE_1;
    int row = 0;
    QString row1,BRAND;
    QString query;
    int tabWidget5 = ui->tabWidget_5->currentIndex();

    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);

    if(tabWidget5==0)
    {
        query = QString("SELECT BRAND,MODEL,EA_%2,%1 FROM DNAWA_DATA WHERE BRAND IN('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY %1 DESC LIMIT 10").arg(EA).arg(index);
        QSqlQuery qry(query);
        qry.exec();
        ui -> tableWidget_3 -> setRowCount(0);
        while(qry.next())
        {
            BRAND = qry.value(0).toString();
            CAR = qry.value(1).toString();
            E_A = qry.value(2).toString();
            E_A_1 = QString("%1대").arg(E_A);
            RATE = qry.value(3).toString();
            RATE_1=qry.value(3).toInt();

            if(RATE_1>0)
            {
                RATE=QString("▲ %1").arg(RATE_1);
            }
            else if(RATE_1<0)
            {
                RATE_1=RATE_1*-1;
                RATE=QString("▼ %1").arg(RATE_1);
            }
            else
            {
                RATE=QString("(-) %1").arg(RATE_1);
            }
            row1=QString("%1").arg(row+1);
            ui -> tableWidget_3 -> insertRow(row);
            ui -> tableWidget_3 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_3 -> setItem(row,2,new QTableWidgetItem(CAR));
            ui -> tableWidget_3 -> setItem(row,3,new QTableWidgetItem(E_A_1));
            ui -> tableWidget_3 -> setItem(row,4,new QTableWidgetItem(RATE));
            if(BRAND == "Hyundai")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item1));
            }
            else if(BRAND == "Kia")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item2));
            }
            else if(BRAND == "Genesis")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item3));
            }
            else if(BRAND == "Chevorlet")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item4));
            }
            else if(BRAND == "KG-mobility")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item5));
            }
            else if(BRAND == "Renaukorea")
            {
                ui -> tableWidget_3 -> setItem(row,0,new QTableWidgetItem(*icon_item6));
            }
            ui->tableWidget_3->item(row,3)->setForeground(Qt::blue);
            ui->tableWidget_3->item(row,4)->setForeground(Qt::red);
            row++;
        }
    }
    else
    {
        query = QString("SELECT BRAND,MODEL,EA_%2,%1 FROM DNAWA_DATA WHERE BRAND IN('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY  %1 DESC LIMIT 10").arg(EA).arg(index);;
        QSqlQuery qry(query);
        qry.exec();
        ui -> tableWidget_5 -> setRowCount(0);
        while(qry.next())
        {
            BRAND = qry.value(0).toString();
            CAR = qry.value(1).toString();
            E_A = qry.value(2).toString();
            E_A_2 = QString("%1대").arg(E_A);
            RATE = qry.value(3).toString();
            RATE_1=qry.value(3).toInt();
            if(RATE_1>0)
            {
                RATE=QString("▲ %1").arg(RATE_1);
            }
            else if(RATE_1<0)
            {
                RATE_1=RATE_1*-1;
                RATE=QString("▼ %1").arg(RATE_1);
            }
            else
            {
                RATE=QString("(-) %1").arg(RATE_1);
            }
            row1=QString("%1").arg(row+1);
            ui -> tableWidget_5 -> insertRow(row);
            ui -> tableWidget_5 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_5 -> setItem(row,2,new QTableWidgetItem(CAR));
            ui -> tableWidget_5 -> setItem(row,3,new QTableWidgetItem(E_A_2));
            ui -> tableWidget_5 -> setItem(row,4,new QTableWidgetItem(RATE));
            if(BRAND == "Mercedes-Benz")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item7));
            }
            else if(BRAND == "Audi")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item8));
            }
            else if(BRAND == "Porsche")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item9));
            }
            else if(BRAND == "Maserati")
            {
                ui -> tableWidget_5 -> setItem(row,0,new QTableWidgetItem(*icon_item10));
            }
            ui->tableWidget_5->item(row,3)->setForeground(Qt::blue);
            ui->tableWidget_5->item(row,4)->setForeground(Qt::red);
            row++;
        }
    }
}
void Widget::Table_HyunDai(QString Brand)                 // 브랜드별 데이터 조회
{
    QSqlQuery query;
    QString BRAND,MODEL,EA_1,PERCENT_1,EA,PERCENT;

    query.exec();
    int row = 0;
    ui -> tableWidget_9 -> setRowCount(0);
    query.prepare("SELECT BRAND,MODEL,EA_1,CONCAT((PERCENT_1),'%') FROM DNAWA_DATA WHERE BRAND = '"+Brand+"' ORDER BY 3 desc; ");
    query.exec();
    while(query.next())
    {
        BRAND = query.value(0).toString();
        MODEL = query.value(1).toString();
        EA_1 = query.value(2).toString();
        PERCENT_1 = query.value(3).toString();

        ui -> tableWidget_9 -> insertRow(row);
        ui -> tableWidget_9 -> setItem(row,0,new QTableWidgetItem(BRAND));
        ui -> tableWidget_9 -> setItem(row,1,new QTableWidgetItem(MODEL));
        ui -> tableWidget_9 -> setItem(row,2,new QTableWidgetItem(EA_1));
        ui -> tableWidget_9 -> setItem(row,3,new QTableWidgetItem(PERCENT_1));
        row++;
    }
}
void Widget::Table_Car(QString Car)
{
    QSqlQuery query;
    QString BRAND,MODEL,EA_1,PERCENT_1,EA,PERCENT;

    query.exec();
    int row = 0;
    ui -> tableWidget_10 -> setRowCount(0);
    query.prepare("SELECT BRAND,MODEL,EA_1,CONCAT((PERCENT_1),'%') FROM DNAWA_DATA WHERE CAR = '"+Car+"' ORDER BY 3 desc; ");
    query.exec();
    while(query.next())
    {
        BRAND = query.value(0).toString();
        MODEL = query.value(1).toString();
        EA_1 = query.value(2).toString();
        PERCENT_1 = query.value(3).toString();

        ui -> tableWidget_10 -> insertRow(row);
        ui -> tableWidget_10 -> setItem(row,0,new QTableWidgetItem(BRAND));
        ui -> tableWidget_10 -> setItem(row,1,new QTableWidgetItem(MODEL));
        ui -> tableWidget_10 -> setItem(row,2,new QTableWidgetItem(EA_1));
        ui -> tableWidget_10 -> setItem(row,3,new QTableWidgetItem(PERCENT_1));
        row++;
    }
}
void Widget::on_pushButton_17_clicked()                     // 전체 카테고리 기간 조회 버튼
{

    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);

    QString EA,MODEL,BRAND,PERCENT;
    int i=0;
    int row=0;
    int comboBox4 = ui -> comboBox_4-> currentIndex();
    int comboBox6 = ui -> comboBox_6-> currentIndex();
    comboBox4+=1;
    comboBox6+=1;
    QString value;
    for(i=comboBox4;i<=comboBox6;i++)
    {
        if(i>comboBox4)
            value+="+";
        value=value+QString("EA_%1").arg(i);
    }
    if(ui -> tabWidget_4 -> currentIndex() == 0)
    {
        ui -> tableWidget->setRowCount(0);
        QString query = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY 3 desc LIMIT 5;").arg(value);
        QSqlQuery qry(query);
        qry.exec();

        while(qry.next())
        {
            BRAND=qry.value(0).toString();
            EA=qry.value(1).toString();
            PERCENT=qry.value(2).toString();

            ui -> tableWidget -> insertRow(row);
            ui -> tableWidget -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget -> setItem(row,2,new QTableWidgetItem(EA));
            ui -> tableWidget -> setItem(row,3,new QTableWidgetItem(PERCENT));
            if(BRAND == "Hyundai")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item1));
            }
            else if(BRAND == "Kia")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item2));
            }
            else if(BRAND == "Genesis")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item3));
            }
            else if(BRAND == "Chevorlet")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item4));
            }
            else if(BRAND == "KG-mobility")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item5));
            }
            else if(BRAND == "Renaukorea")
            {
                ui -> tableWidget -> setItem(row,0,new QTableWidgetItem(*icon_item6));
            }
            row++;
        }
    }
    else
    {
        ui -> tableWidget_4 ->setRowCount(0);
        QString query = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN ('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY 2 desc LIMIT 5;").arg(value);
        QSqlQuery qry(query);
        qry.exec();

        while(qry.next())
        {
            BRAND=qry.value(0).toString();
            EA=qry.value(1).toString();
            PERCENT=qry.value(2).toString();

            ui -> tableWidget_4 -> insertRow(row);
            ui -> tableWidget_4 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_4 -> setItem(row,2,new QTableWidgetItem(EA));
            ui -> tableWidget_4 -> setItem(row,3,new QTableWidgetItem(PERCENT));
            if(BRAND == "Mercedes-Benz")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item7));
            }
            else if(BRAND == "Audi")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item8));
            }
            else if(BRAND == "Porsche")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item9));
            }
            else if(BRAND == "Maserati")
            {
                ui -> tableWidget_4 -> setItem(row,0,new QTableWidgetItem(*icon_item10));
            }
            row++;
        }
    }
}
void Widget::on_pushButton_78_clicked()                     // 브랜드별 카테고리 기간 조회 버튼
{

    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QString EA,MODEL,BRAND,PERCENT;
    int i=0;
    int row=0;
    int comboBox12 = ui -> comboBox_12-> currentIndex();
    int comboBox10 = ui -> comboBox_10-> currentIndex();
    ui -> tableWidget_9 -> setRowCount(0);

    comboBox12+=1;
    comboBox10+=1;
    QString value;
    for(i=comboBox12;i<=comboBox10;i++)
    {
        if(i>comboBox12)
            value+="+";
        value=value+QString("EA_%1").arg(i);
    }
    QString query = QString("SELECT BRAND,MODEL,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA WHERE BRAND = '"+Brand+"' ORDER BY 3 desc;").arg(value);
    QSqlQuery qry(query);
    qry.exec();

    while(qry.next())
    {
        BRAND=qry.value(0).toString();
        MODEL=qry.value(1).toString();
        EA=qry.value(2).toString();
        PERCENT=qry.value(3).toString();

        ui -> tableWidget_9 -> insertRow(row);
        ui -> tableWidget_9 -> setItem(row,0,new QTableWidgetItem(BRAND));
        ui -> tableWidget_9 -> setItem(row,1,new QTableWidgetItem(MODEL));
        ui -> tableWidget_9 -> setItem(row,2,new QTableWidgetItem(EA));
        ui -> tableWidget_9 -> setItem(row,3,new QTableWidgetItem(PERCENT));
        row++;
    }
    QString E_A,RATE,BRAND_1,E_A_1,RATE_1;
    int row1=0;
    QString query2;

    query2 = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN ('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY 2 DESC").arg(value);
    QSqlQuery qry2(query2);
    qry2.exec();
    // 국산차 테이블위젯 번호로 바꾸고
    ui -> tableWidget_2 -> setRowCount(0);

    while(qry2.next())
    {
        BRAND = qry2.value(0).toString();
        E_A = qry2.value(1).toString();
        RATE = qry2.value(2).toString();
        // 국산차 테이블위젯 번호로 바꾸고
        ui -> tableWidget_2 -> insertRow(row);
        ui -> tableWidget_2 -> setItem(row,1,new QTableWidgetItem(BRAND));
        ui -> tableWidget_2 -> setItem(row,2,new QTableWidgetItem(E_A));
        ui -> tableWidget_2 -> setItem(row,3,new QTableWidgetItem(RATE));
        if(BRAND == "Hyundai")
        {
            ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item1));
        }
        else if(BRAND == "Kia")
        {
            ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item2));
        }
        else if(BRAND == "Genesis")
        {
            ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item3));
        }
        else if(BRAND == "Chevorlet")
        {
            ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item4));
        }
        else if(BRAND == "KG-mobility")
        {
            ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item5));
        }
        else if(BRAND == "Renaukorea")
        {
            ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item6));
        }
        row++;
    }
    QString query3;
    query3 = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY 2 DESC").arg(value);
    QSqlQuery qry3(query3);
    qry3.exec();

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);
    //테이블 위젯 번호 수입차로 바꾸고
    ui -> tableWidget_6 -> setRowCount(0);

    while(qry3.next())
    {
        BRAND_1 = qry3.value(0).toString();
        E_A_1 = qry3.value(1).toString();
        RATE_1 = qry3.value(2).toString();

        //테이블 위젯 번호 수입차로 바꾸고
        ui -> tableWidget_6 -> insertRow(row1);
        ui -> tableWidget_6 -> setItem(row1,1,new QTableWidgetItem(BRAND_1));
        ui -> tableWidget_6 -> setItem(row1,2,new QTableWidgetItem(E_A_1));
        ui -> tableWidget_6 -> setItem(row1,3,new QTableWidgetItem(RATE_1));
        if(BRAND_1 == "Mercedes-Benz")
        {
            ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item7));
        }
        else if(BRAND_1 == "Audi")
        {
            ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item8));
        }
        else if(BRAND_1 == "Porsche")
        {
            ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item9));
        }
        else if(BRAND_1 == "Maserati")
        {
            ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item10));
        }
        row1++;
    }

}
void Widget::on_comboBox_8_currentIndexChanged(int index)               // 브랜드별 카테고리 월별 조회
{
    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);

    QString aa = ui -> comboBox_8 -> currentText();
    ui -> label_103 -> setText("2023년 " + aa);
    ui -> label_104 -> setText("2023년 " + aa);
    QString EA,MODEL,BRAND,PERCENT;
    int i=0;
    int row=0;
    int comboBox8 = ui -> comboBox_8-> currentIndex();
    ui -> tableWidget_9 -> setRowCount(0);
    comboBox8+=1;

    QString value;
    QString query1;
    for(i=comboBox8;i<=comboBox8;i++)
    {
        if(i>comboBox8)
            value+="+";
        value=value+QString("EA_%1").arg(i);
    }
    if(ui -> stackedWidget_2 ->currentIndex() == 0)
    {
        QString E_A,RATE,BRAND_1,E_A_1,RATE_1;
        int row1=0;
        QString query2;

        query2 = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN ('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY %1 DESC").arg(value);
        QSqlQuery qry2(query2);
        qry2.exec();
        // 국산차 테이블위젯 번호로 바꾸고
        ui -> tableWidget_2 -> setRowCount(0);

        while(qry2.next())
        {
            BRAND = qry2.value(0).toString();
            E_A = qry2.value(1).toString();
            RATE = qry2.value(2).toString();
            // 국산차 테이블위젯 번호로 바꾸고
            ui -> tableWidget_2 -> insertRow(row);
            ui -> tableWidget_2 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_2 -> setItem(row,2,new QTableWidgetItem(E_A));
            ui -> tableWidget_2 -> setItem(row,3,new QTableWidgetItem(RATE));
            if(BRAND == "Hyundai")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item1));
            }
            else if(BRAND == "Kia")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item2));
            }
            else if(BRAND == "Genesis")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item3));
            }
            else if(BRAND == "Chevorlet")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item4));
            }
            else if(BRAND == "KG-mobility")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item5));
            }
            else if(BRAND == "Renaukorea")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item6));
            }
            row++;
        }
        QString query3;
        query3 = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY %1 DESC").arg(value);
        QSqlQuery qry3(query3);
        qry3.exec();

        //테이블 위젯 번호 수입차로 바꾸고
        ui -> tableWidget_6 -> setRowCount(0);

        while(qry3.next())
        {
            BRAND_1 = qry3.value(0).toString();
            E_A_1 = qry3.value(1).toString();
            RATE_1 = qry3.value(2).toString();

            //테이블 위젯 번호 수입차로 바꾸고
            ui -> tableWidget_6 -> insertRow(row1);
            ui -> tableWidget_6 -> setItem(row1,1,new QTableWidgetItem(BRAND_1));
            ui -> tableWidget_6 -> setItem(row1,2,new QTableWidgetItem(E_A_1));
            ui -> tableWidget_6 -> setItem(row1,3,new QTableWidgetItem(RATE_1));
            if(BRAND_1 == "Mercedes-Benz")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item7));
            }
            else if(BRAND_1 == "Audi")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item8));
            }
            else if(BRAND_1 == "Porsche")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item9));
            }
            else if(BRAND_1 == "Maserati")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item10));
            }
            row1++;
        }
    }
    else if(ui -> stackedWidget_2 ->currentIndex() == 1)
    {

        QString query1 = QString("SELECT BRAND,MODEL,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA WHERE BRAND = '"+Brand+"' ORDER BY 3 desc;").arg(value);
        QSqlQuery qry1(query1);
        qry1.exec();

        while(qry1.next())
        {
            BRAND=qry1.value(0).toString();
            MODEL=qry1.value(1).toString();
            EA=qry1.value(2).toString();
            PERCENT=qry1.value(3).toString();

            ui -> tableWidget_9 -> insertRow(row);
            ui -> tableWidget_9 -> setItem(row,0,new QTableWidgetItem(BRAND));
            ui -> tableWidget_9 -> setItem(row,1,new QTableWidgetItem(MODEL));
            ui -> tableWidget_9 -> setItem(row,2,new QTableWidgetItem(EA));
            ui -> tableWidget_9 -> setItem(row,3,new QTableWidgetItem(PERCENT));
            row++;
        }
    }
}
void Widget::on_tabWidget_currentChanged(int index)
{
    QTableWidgetItem *icon_item1 = new QTableWidgetItem;
    QIcon icon1("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/현대.png");
    icon_item1 -> setIcon(icon1);

    QTableWidgetItem *icon_item2 = new QTableWidgetItem;
    QIcon icon2("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/기아.png");
    icon_item2 -> setIcon(icon2);

    QTableWidgetItem *icon_item3 = new QTableWidgetItem;
    QIcon icon3("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/제네시스.png");
    icon_item3 -> setIcon(icon3);

    QTableWidgetItem *icon_item4 = new QTableWidgetItem;
    QIcon icon4("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/쉐보레.png");
    icon_item4 -> setIcon(icon4);

    QTableWidgetItem *icon_item5 = new QTableWidgetItem;
    QIcon icon5("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/KG모빌리티.png");
    icon_item5 -> setIcon(icon5);

    QTableWidgetItem *icon_item6 = new QTableWidgetItem;
    QIcon icon6("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/르노코리아.png");
    icon_item6 -> setIcon(icon6);

    QTableWidgetItem *icon_item7 = new QTableWidgetItem;
    QIcon icon7("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/벤츠.png");
    icon_item7 -> setIcon(icon7);

    QTableWidgetItem *icon_item8 = new QTableWidgetItem;
    QIcon icon8("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/아우디.png");
    icon_item8 -> setIcon(icon8);

    QTableWidgetItem *icon_item9 = new QTableWidgetItem;
    QIcon icon9("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/포르쉐.png");
    icon_item9 -> setIcon(icon9);

    QTableWidgetItem *icon_item10 = new QTableWidgetItem;
    QIcon icon10("/Users/IOT/Desktop/Important/다나와_프로젝트/사진/마세라티.png");
    icon_item10 -> setIcon(icon10);

    ui -> stackedWidget_2 -> setCurrentIndex(0);
    if (index==2)
    {
        QString EA,MODEL,BRAND,PERCENT;
        int row=0;
        // int comboBox14 = ui -> comboBox_14-> currentIndex();
        ui -> tableWidget_10 -> setRowCount(0);
        // comboBox14+=1;
        // QString value;
        // value=value+QString("EA%1").arg(comboBox14);

        //QString query = QString("SELECT BRAND,MODEL,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()10010)/10),'%') FROM DNAWA_DATA ORDER BY 3 desc;").arg(value);
        QString query = QString("SELECT BRAND,MODEL,EA_1,CONCAT((ROUND((EA_1)/SUM(EA_1)OVER()*100*10)/10),'%') FROM DNAWA_DATA ORDER BY 3 desc;");
        QSqlQuery qry(query);
        qry.exec();

        while(qry.next())
        {
            BRAND=qry.value(0).toString();
            MODEL=qry.value(1).toString();
            EA=qry.value(2).toString();
            PERCENT=qry.value(3).toString();

            ui -> tableWidget_10 -> insertRow(row);
            ui -> tableWidget_10 -> setItem(row,0,new QTableWidgetItem(BRAND));
            ui -> tableWidget_10 -> setItem(row,1,new QTableWidgetItem(MODEL));
            ui -> tableWidget_10 -> setItem(row,2,new QTableWidgetItem(EA));
            ui -> tableWidget_10 -> setItem(row,3,new QTableWidgetItem(PERCENT));
            row++;
        }
    }
    else if(index == 1)
    {
        QString value;
        int comboBox8=ui->comboBox_8->currentIndex();
        comboBox8+=1;
        value=value+QString("EA_%1").arg(comboBox8);

        index=1;
        QString E_A,RATE,BRAND,BRAND_1,E_A_1,RATE_1;
        int row = 0;
        int row1=0;
        QString query,query1;

        query = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN ('Hyundai','Kia','Chevorlet','Genesis','KG-mobility','Renaukorea') ORDER BY %1 DESC").arg(value);
        QSqlQuery qry(query);
        qry.exec();
        // 국산차 테이블위젯 번호로 바꾸고
        ui -> tableWidget_2 -> setRowCount(0);

        while(qry.next())
        {
            BRAND = qry.value(0).toString();
            E_A = qry.value(1).toString();
            RATE = qry.value(2).toString();
            // 국산차 테이블위젯 번호로 바꾸고
            ui -> tableWidget_2 -> insertRow(row);
            ui -> tableWidget_2 -> setItem(row,1,new QTableWidgetItem(BRAND));
            ui -> tableWidget_2 -> setItem(row,2,new QTableWidgetItem(E_A));
            ui -> tableWidget_2 -> setItem(row,3,new QTableWidgetItem(RATE));
            if(BRAND == "Hyundai")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item1));
            }
            else if(BRAND == "Kia")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item2));
            }
            else if(BRAND == "Genesis")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item3));
            }
            else if(BRAND == "Chevorlet")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item4));
            }
            else if(BRAND == "KG-mobility")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item5));
            }
            else if(BRAND == "Renaukorea")
            {
                ui -> tableWidget_2 -> setItem(row,0,new QTableWidgetItem(*icon_item6));
            }
            row++;
        }

        query1 = QString("SELECT BRAND,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA_TOTAL WHERE BRAND IN('Porsche','Audi','Maserati','Mercedes-Benz') ORDER BY %1 DESC").arg(value);
        QSqlQuery qry1(query1);
        qry1.exec();

        //테이블 위젯 번호 수입차로 바꾸고
        ui -> tableWidget_6 -> setRowCount(0);

        while(qry1.next())
        {
            BRAND_1 = qry1.value(0).toString();
            E_A_1 = qry1.value(1).toString();
            RATE_1 = qry1.value(2).toString();

            //테이블 위젯 번호 수입차로 바꾸고
            ui -> tableWidget_6 -> insertRow(row1);
            ui -> tableWidget_6 -> setItem(row1,1,new QTableWidgetItem(BRAND_1));
            ui -> tableWidget_6 -> setItem(row1,2,new QTableWidgetItem(E_A_1));
            ui -> tableWidget_6 -> setItem(row1,3,new QTableWidgetItem(RATE_1));
            if(BRAND_1 == "Mercedes-Benz")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item7));
            }
            else if(BRAND_1 == "Audi")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item8));
            }
            else if(BRAND_1 == "Porsche")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item9));
            }
            else if(BRAND_1 == "Maserati")
            {
                ui -> tableWidget_6 -> setItem(row1,0,new QTableWidgetItem(*icon_item10));
            }
            row1++;
        }
    }
}
void Widget::on_comboBox_14_currentIndexChanged(int index)
{
    QString EA,MODEL,BRAND,PERCENT;
    int i = 0;
    int row=0;
    int comboBox14 = ui -> comboBox_14-> currentIndex();

    comboBox14+=1;
    QString value;
    for(i=comboBox14;i<=comboBox14;i++)
    {
        if(i>comboBox14)
            value+="+";
        value=value+QString("EA_%1").arg(i);
    }

    QString query = QString("SELECT BRAND,MODEL,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA WHERE CAR = '"+Car+"' ORDER BY 3 desc;").arg(value);
    QSqlQuery qry(query);
    qry.exec();
    ui -> tableWidget_10 -> setRowCount(0);
    while(qry.next())
    {

        BRAND=qry.value(0).toString();
        MODEL=qry.value(1).toString();
        EA=qry.value(2).toString();
        PERCENT=qry.value(3).toString();

        ui -> tableWidget_10 -> insertRow(row);
        ui -> tableWidget_10 -> setItem(row,0,new QTableWidgetItem(BRAND));
        ui -> tableWidget_10 -> setItem(row,1,new QTableWidgetItem(MODEL));
        ui -> tableWidget_10 -> setItem(row,2,new QTableWidgetItem(EA));
        ui -> tableWidget_10 -> setItem(row,3,new QTableWidgetItem(PERCENT));
        row++;
    }
}
void Widget::on_pushButton_79_clicked()
{
    QString EA,MODEL,BRAND,PERCENT;
    int row=0;
    int i=0;
    int comboBox18 = ui -> comboBox_18-> currentIndex();
    int comboBox16 = ui -> comboBox_16-> currentIndex();
    ui -> tableWidget_10 -> setRowCount(0);
    comboBox18+=1;
    comboBox16+=1;
    QString value;
    for(i=comboBox18;i<=comboBox16;i++)
    {
        if(i>comboBox18)
            value+="+";
        value=value+QString("EA_%1").arg(i);
    }

    QString query = QString("SELECT BRAND,MODEL,%1,CONCAT((ROUND((%1)/SUM(%1)OVER()*100*10)/10),'%') FROM DNAWA_DATA WHERE CAR = '"+Car+"' ORDER BY 3 desc;").arg(value);
    QSqlQuery qry(query);
    qry.exec();

    while(qry.next())
    {
        BRAND=qry.value(0).toString();
        MODEL=qry.value(1).toString();
        EA=qry.value(2).toString();
        PERCENT=qry.value(3).toString();

        ui -> tableWidget_10 -> insertRow(row);
        ui -> tableWidget_10 -> setItem(row,0,new QTableWidgetItem(BRAND));
        ui -> tableWidget_10 -> setItem(row,1,new QTableWidgetItem(MODEL));
        ui -> tableWidget_10 -> setItem(row,2,new QTableWidgetItem(EA));
        ui -> tableWidget_10 -> setItem(row,3,new QTableWidgetItem(PERCENT));
        row++;
    }
}
void Widget::Btn_Join()       // 회원가입 버튼
{
    ui -> stackedWidget -> setCurrentIndex(2);
}
void Widget::Btn_FindID()     // ID 찾기 버튼
{
    ui -> stackedWidget -> setCurrentIndex(3);
}
void Widget::Btn_FindPW()     // PW 찾기 버튼
{
    ui -> stackedWidget -> setCurrentIndex(4);
}
void Widget::Btn_Back()       // 뒤로가기 버튼
{
    ui -> stackedWidget -> setCurrentIndex(1);
}
void Widget::Btn_Main()       // 첫화면 버튼
{
    ui -> stackedWidget -> setCurrentIndex(1);
}
void Widget::Btn_Info()       // 판매실적 버튼
{
    ui -> stackedWidget -> setCurrentIndex(5);
}
void Widget::Btn_Brand()     // 브랜드 버튼
{
    ui -> tabWidget -> setCurrentIndex(1);
    ui -> stackedWidget_2 -> setCurrentIndex(1);
}
void Widget::Btn_Model()    // 모델 버튼
{
    ui -> tabWidget -> setCurrentIndex(2);
    ui -> tabWidget_2 -> setCurrentIndex(0);
}
void Widget::Btn_Home()     // 홈 버튼
{
    ui -> stackedWidget -> setCurrentIndex(0);
}
void Widget::Btn_sale()
{
    ui -> stackedWidget -> setCurrentIndex(6);
}
void Widget::Btn_danawa1()
{
    QMessageBox MsgBox;
    MsgBox.setText("로그인 화면입니다\n딴짓 하지말고 로그인하세요.");
    MsgBox.exec();
}
void Widget::Btn_danawa2()
{
    QMessageBox MsgBox;
    MsgBox.setText("회원가입 화면입니다\n딴짓 하지말고 회원가입하세요.");
    MsgBox.exec();
}
void Widget::Btn_danawa3()
{
    QMessageBox MsgBox;
    MsgBox.setText("아이디 찾기 화면입니다\n딴짓 하지말고 아이디 찾으세요.");
    MsgBox.exec();
}
void Widget::Btn_danawa4()
{
    QMessageBox MsgBox;
    MsgBox.setText("비밀번호 찾기 화면입니다\n딴짓 하지말고 비밀번호 찾으세요.");
    MsgBox.exec();
}
void Widget::Btn_danawa5()
{
    QMessageBox MsgBox;
    MsgBox.setText("판매실적 화면입니다\n딴짓 하지말고 판매실적 보세요.");
    MsgBox.exec();
}
void Widget::on_Hyundai_clicked()
{
    Brand = "Hyundai";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);

}
void Widget::on_Kia_clicked()
{
    Brand = "Kia";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_Genesis_clicked()
{
    Brand = "Genesis";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_Chevorlet_clicked()
{
    Brand = "Chevorlet";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_pushButton_26_clicked()
{
    Brand = "KG-mobility";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_pushButton_19_clicked()
{
    Brand = "Renaukorea";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_pushButton_21_clicked()
{
    Brand = "Mercedes-Benz";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_pushButton_22_clicked()
{
    Brand = "Audi";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_pushButton_25_clicked()
{
    Brand = "Porsche";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_pushButton_27_clicked()
{
    Brand = "Maserati";
    Widget::Btn_Brand();
    Widget::Table_HyunDai(Brand);
}
void Widget::on_pushButton_33_clicked()
{
    Car = "경차";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_31_clicked()
{
    Car = "소형";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_36_clicked()
{
    Car = "준중형";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_37_clicked()
{
    Car = "중형";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_34_clicked()
{
    Car = "준대형";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_32_clicked()
{
    Car = "대형";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_28_clicked()
{
    Car = "스포츠카";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_29_clicked()
{
    Car = "소형SUV";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_30_clicked()
{
    Car = "중형SUV";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_35_clicked()
{
    Car = "대형SUV";
    Widget::Btn_Model();
    Widget::Table_Car(Car);
    ui -> tabWidget_6 -> setCurrentIndex(0);
}
void Widget::on_pushButton_94_clicked()
{
    ui -> tabWidget_4 -> setCurrentIndex(1);
}

void Widget::on_pushButton_95_clicked()
{
    ui -> tabWidget_4 -> setCurrentIndex(0);
}
void Widget::on_pushButton_98_clicked()
{
    ui -> tabWidget_5 -> setCurrentIndex(1);
}

void Widget::on_pushButton_100_clicked()
{
    ui -> tabWidget_5 -> setCurrentIndex(0);
}



