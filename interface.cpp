#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);
    ui->output->setAlignment(Qt::AlignRight);
    ui->expres->setAlignment(Qt::AlignRight);
    ui->memoryText->setAlignment(Qt::AlignCenter);
    check = 0;
    ui->memory1->setEnabled(false);
    ui->memory2->setEnabled(false);
    ui->memory3->setEnabled(false);
    ui->memory4->setEnabled(false);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_A, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_B, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_D, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_E, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->pushButton_F, SIGNAL(clicked()), this, SLOT(PressNum()));
    connect(ui->plusBtn, SIGNAL(clicked()), this, SLOT(PressSign()));
    connect(ui->minusBtn, SIGNAL(clicked()), this, SLOT(PressSign()));
    connect(ui->multBtn, SIGNAL(clicked()), this, SLOT(PressSign()));
    connect(ui->divBtn, SIGNAL(clicked()), this, SLOT(PressSign()));
    connect(ui->delOnebtn, SIGNAL(clicked()), this, SLOT(DelOne()));
    connect(ui->delAllBtn, SIGNAL(clicked()), this, SLOT(DelAll()));
    connect(ui->equalBtn, SIGNAL(clicked()), this, SLOT(PressEqual()));
    connect(ui->toDecBtn, SIGNAL(clicked()), this, SLOT(ToDec()));
    connect(ui->memory1, SIGNAL(clicked()), this, SLOT(MemoryBtns()));
    connect(ui->memory2, SIGNAL(clicked()), this, SLOT(MemoryBtns()));
    connect(ui->memory3, SIGNAL(clicked()), this, SLOT(MemoryBtns()));
    connect(ui->memory4, SIGNAL(clicked()), this, SLOT(MemoryBtns()));
}

Interface::~Interface()
{
    delete ui;
}

void Interface::PressNum(){
    ui->plusBtn->setEnabled(true);
    ui->minusBtn->setEnabled(true);
    ui->multBtn->setEnabled(true);
    ui->divBtn->setEnabled(true);
    ui->toDecBtn->setEnabled(true);
    ui->equalBtn->setEnabled(true);
    ui->delOnebtn->setEnabled(true);
    if(ui->expres->text() != "" && ui->expres->text()[ui->expres->text().length()-1] == '=')
        ui->expres->setText("");
    if (ui->output->text() == "Ошибочка"){
        ui->expres->setText("");
    }
    if(ui->output->text() == "0")
        ui->output->setText("");
    if (check){
        ui->output->setText("");
        check = 0;
    }
    QPushButton *btn = (QPushButton*) sender();
    if (ui->output->text().length() < 16)
        ui->output->setText(ui->output->text() + btn->text());
}

void Interface::PressSign(){
    ui->equalBtn->setEnabled(true);
    check = 1;
    QPushButton *btn = (QPushButton*) sender();
    if (ui->expres->text() == "" || ui->expres->text()[ui->expres->text().length() - 1] == '='){
        ui->expres->setText(ui->output->text());
        if (btn == ui->plusBtn)
            ui->expres->setText(ui->expres->text() + "+");
        else if (btn == ui->minusBtn)
            ui->expres->setText(ui->expres->text() + "-");
        else if (btn == ui->multBtn)
            ui->expres->setText(ui->expres->text() + "*");
        else if (btn == ui->divBtn)
            ui->expres->setText(ui->expres->text() + "/");
    }
    else{
        QChar last = ui->expres->text()[ui->expres->text().length()-1];
        if (last == '+' || last == '-' || last == '*' || last == '/'){
            QString temp = ui->expres->text();
            temp.remove(temp.length()-1, 1);
            ui->expres->setText(temp);
            if (btn == ui->plusBtn)
                ui->expres->setText(ui->expres->text() + "+");
            else if (btn == ui->minusBtn)
                ui->expres->setText(ui->expres->text() + "-");
            else if (btn == ui->multBtn)
                ui->expres->setText(ui->expres->text() + "*");
            else if (btn == ui->divBtn)
                ui->expres->setText(ui->expres->text() + "/");
            return;
        }
    }
}

void Interface::PressEqual(){
    check = 1;
    if(ui->expres->text() != "" && ui->expres->text()[ui->expres->text().length()-1] == '=')
        ui->expres->setText("");
    ui->expres->setText(ui->expres->text() + ui->output->text() + "=");
    QString answer = calc.PerformOperation(ui->expres->text());
    ui->output->setText(answer);
    ui->equalBtn->setEnabled(false);
    if (answer == "Ошибочка"){
        ui->plusBtn->setEnabled(false);
        ui->minusBtn->setEnabled(false);
        ui->multBtn->setEnabled(false);
        ui->divBtn->setEnabled(false);
        ui->toDecBtn->setEnabled(false);
        ui->delOnebtn->setEnabled(false);
        return;
    }
    SetMemoryBtns();
}

void Interface::SetMemoryBtns(){
    if (ui->memory1->text() == ""){
        ui->memory1->setText(ui->expres->text() + "\n" + ui->output->text());
        ui->memory1->setEnabled(true);
    }
    else if(ui->memory2->text() == ""){
        ui->memory2->setText(ui->memory1->text());
        ui->memory1->setText(ui->expres->text() + "\n" + ui->output->text());
        ui->memory2->setEnabled(true);
    }
    else if(ui->memory3->text() == ""){
        ui->memory3->setText(ui->memory2->text());
        ui->memory2->setText(ui->memory1->text());
        ui->memory1->setText(ui->expres->text() + "\n" + ui->output->text());
        ui->memory3->setEnabled(true);
    }
    else{
        ui->memory4->setText(ui->memory3->text());
        ui->memory3->setText(ui->memory2->text());
        ui->memory2->setText(ui->memory1->text());
        ui->memory1->setText(ui->expres->text() + "\n" + ui->output->text());
        ui->memory4->setEnabled(true);
    }
}

void Interface::MemoryBtns(){
    ui->plusBtn->setEnabled(true);
    ui->minusBtn->setEnabled(true);
    ui->multBtn->setEnabled(true);
    ui->divBtn->setEnabled(true);
    ui->toDecBtn->setEnabled(true);
    ui->equalBtn->setEnabled(true);
    ui->delOnebtn->setEnabled(true);
    QPushButton *btn = (QPushButton*) sender();
    QString temp = btn->text();
    while(temp[0] != '\n') temp.remove(0,1);
    temp.remove(0,1);
    ui->output->setText(temp);
}

void Interface::ToDec(){
    check = 1;
    ui->equalBtn->setEnabled(false);
    ui->plusBtn->setEnabled(false);
    ui->minusBtn->setEnabled(false);
    ui->multBtn->setEnabled(false);
    ui->divBtn->setEnabled(false);
    ui->toDecBtn->setEnabled(false);
    ui->delOnebtn->setEnabled(false);
    QString temp = ui->output->text();
    ui->output->setText(calc.HexToDecimal(temp));
}

void Interface::DelOne(){
    if (ui->output->text().length() > 1){
        QString temp = ui->output->text();
        temp.remove(temp.length()-1, 1);
        ui->output->setText(temp);
    }
    else ui->output->setText("0");
}

void Interface::DelAll(){
    ui->plusBtn->setEnabled(true);
    ui->minusBtn->setEnabled(true);
    ui->multBtn->setEnabled(true);
    ui->divBtn->setEnabled(true);
    ui->toDecBtn->setEnabled(true);
    ui->equalBtn->setEnabled(true);
    ui->delOnebtn->setEnabled(true);
    ui->expres->setText("");
    ui->output->setText("0");
}
