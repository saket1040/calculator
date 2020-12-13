#include "calculator.h"
#include "ui_calculator.h"

//holds current value of calculation
double calcVal= 0.0;
//define last math button clicked
bool divTrigger=false;
bool addTrigger=false;
bool multTrigger=false;
bool subTrigger=false;
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10;++i){
        QString butname = "Button" + QString::number(i);
        numButtons[i]=Calculator::findChild<QPushButton *>(butname);
        connect(numButtons[i],SIGNAL(released()),this,SLOT(NumPressed()));
    }
    connect(ui->Add,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Substract,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Equal,SIGNAL(released()),this,SLOT(EqualButtonPressed()));
    connect(ui->Clear,SIGNAL(released()),this,SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}
void Calculator::NumPressed(){
    QPushButton *button=(QPushButton *)sender();
    QString butVal=button->text();
    QString displayVal= ui->Display->text();

    if((displayVal.toDouble()==0) || (displayVal.toDouble()==0.0)){
        ui->Display->setText(butVal);
    }
        else {
        QString newVal =displayVal+butVal;
        double dblNewVal= newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));
    }
}

void Calculator::MathButtonPressed(){

        divTrigger=false;
        multTrigger=false;
        addTrigger=false;
        subTrigger=false;

        QString displayVal=ui->Display->text();
        calcVal=displayVal.toDouble();

        QPushButton *button= (QPushButton *)sender();
        QString butVal=button->text();

        if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0){
            divTrigger=true;
        } else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0){
            addTrigger=true;
        } else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0){
            multTrigger=true;
        }    else {
            subTrigger=true;
        }
         ui->Display->setText(butVal);
}

void Calculator::EqualButtonPressed(){

    double solution=0.0;

    QString displayVal=ui->Display->text();
    double dblDisplayVal= displayVal.toDouble();

    if(addTrigger|| subTrigger||divTrigger||multTrigger){
        if(addTrigger){
            solution=calcVal + dblDisplayVal;
        }else if(subTrigger){
            solution=calcVal - dblDisplayVal;
        }else if(multTrigger){
            solution=calcVal*dblDisplayVal;
        }else{
            solution=calcVal / dblDisplayVal;
        }
}
    ui->Display->setText(QString::number(solution));
}

void Calculator::ClearButtonPressed(){
    double clear=0.0;
    ui->Display->setText(QString::number(clear));
}

