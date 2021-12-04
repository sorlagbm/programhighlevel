#include "saveornot.h"
#include "ui_saveornot.h"

SaveorNot::SaveorNot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveorNot)
{
    ui->setupUi(this);
}

SaveorNot::~SaveorNot()
{
    delete ui;
}
