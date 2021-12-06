#include "dasas.h"
#include "ui_dasas.h"

dASas::dASas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dASas)
{
    ui->setupUi(this);
}

dASas::~dASas()
{
    delete ui;
}
