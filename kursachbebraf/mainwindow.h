#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionDelete_by_id_triggered();

    void on_actionAdd_User_triggered();

    void on_actionDenie_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_actionNew_file_triggered();

    void on_actionaddtab_triggered();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
