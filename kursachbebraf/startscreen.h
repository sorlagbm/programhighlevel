#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_StartScreen_finished(int result);

    void on_StartScreen_destroyed();


signals:
    void mainWindow_openFile();
    void mainWindow_newFile();

private:
    Ui::StartScreen *ui;
};

#endif // STARTSCREEN_H
