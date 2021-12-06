#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Открыть файл");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Создать новый файл");

}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::on_buttonBox_accepted()
{
    this->close();
    emit mainWindow_openFile();
}

void StartScreen::on_buttonBox_rejected()
{
    this->close();
    emit mainWindow_newFile();
}

void StartScreen::on_StartScreen_finished(int result)
{

}

void StartScreen::on_StartScreen_destroyed()
{

}
