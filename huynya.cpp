#include "queue.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "saveornot.h"

const unsigned short q_cols = 1;

unsigned short q_rows = 0;

QString fileName = "";

QFile* file;

Queue _queue;

bool isChanged;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    MainWindow::setWindowTitle("Last save");
    _queue = Queue(0, new Queue::FileWork(nullptr), ui->tableWidget);
    _queue.curWid->setColumnCount(q_cols);
    _queue.curFile->file = new QFile("exit.tmp");
    if(_queue.curFile->file->size() != 0){
    if (QFile::exists("exit.tmp")){

        _queue.curFile->file->open(QIODevice::ReadOnly);
        unsigned short len;
        _queue.curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
        q_rows = len;
        _queue.curWid->setRowCount(q_rows);
        _queue._resize(q_rows);

        for(int i = 0; i < q_rows; i++){

            _queue.curFile->file->read(reinterpret_cast<char*>(&_queue.get_denials(i)), sizeof(_queue.get_denials(i)));
            size_t _BUF_SZ;
            _queue.curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
            char* _BUF = new char[_BUF_SZ];
            _queue.curFile->file->read(_BUF, _BUF_SZ);
            string g = _BUF;
            qDebug() << QString::fromStdString(g);
            _queue.get_name(i) = QString::fromStdString(g);
            delete[] _BUF;

        }

        for(int i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            _queue.curWid->setItem(i, 0, name);

        }

        _queue.curFile->file->close();
        _queue.curFile->file = nullptr;

    }

    else{
        _queue.curFile->file->write("");
    }
    }
    else{

    }
    isChanged = false;

}

void MainWindow::on_actionDelete_by_id_triggered(){

    QString text = QInputDialog::getText(this, tr("Delete"),
                            tr("Number:"), QLineEdit::Normal,
                            "", new bool());

        unsigned n;

        if(text.isEmpty()){
            n = 0;
            QMessageBox::information(this, "First element was deleted!", "First element was deleted!");
        }
        else n = text.toUInt() - 1;

        _queue.curWid->clear();

        _queue._erase(n);

        q_rows--;

        _queue.curWid->setRowCount(q_rows);

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            _queue.curWid->setItem(i, 0, name);

        }
}

void MainWindow::on_actionAdd_User_triggered(){

    bool ok;

    QString text = QInputDialog::getText(this, tr("New User"),
                            tr("Name:"), QLineEdit::Normal,
                            "", &ok);

    for(int i = 0; i < q_rows; i++){

        if (text == _queue.get_name(i)){

            Dialog* choise = new Dialog;
            if (choise->exec() == QDialog::Rejected){
                return;
            }

        }

    }

    if(!text.isEmpty()){

        _queue.push(text);

        q_rows++;

        _queue.curWid->setRowCount(q_rows);

        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(_queue.get_name(_queue.get_size() - 1));
        _queue.curWid->setItem(q_rows - 1, 0, name);

    }


}

MainWindow::~MainWindow(){

    if(isChanged){
    if(_queue.curFile->file != nullptr){


        SaveorNot* exit = new SaveorNot;
        if(exit->exec() == QDialog::Accepted){
            _queue.curFile->file->close();
            _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);
            for(int i = 0; i < q_rows; i++){

                _queue.get_name(i) = ui->tableWidget->item(i, 0)->text();

            }
            _queue.curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

            for(int i = 0; i < q_rows; i++){

                _queue.curFile->file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                        sizeof(_queue.get_denials(i)));
                size_t _BUF =_queue.get_name(i).size() + 1;
                _queue.curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                _queue.curFile->file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

            }

            _queue.curFile->file->close();

            _queue.curFile->file = nullptr;
            _queue.curFile->file = new QFile("exit.tmp");
            _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

            _queue.curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue.curFile->file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                                sizeof(_queue.get_denials(i)));
                        size_t _BUF = _queue.get_name(i).size() + 1;
                        _queue.curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue.curFile->file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

                    }
            _queue.curFile->file->close();
            delete ui;

        }
        else{
            _queue.curFile->file->close();
        }

    }
    else{

        SaveorNot* exit = new SaveorNot;
        if(exit->exec() == QDialog::Accepted){

            fileName = QFileDialog::getSaveFileName(this, "Save as");
            MainWindow::setWindowTitle(fileName);
            _queue.curFile->file = new QFile(fileName);
            _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);
            for(int i = 0; i < q_rows; i++){

                _queue.get_name(i) = _queue.curWid->item(i, 0)->text();

            }
            _queue.curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

            for(int i = 0; i < q_rows; i++){

                _queue.curFile->file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                        sizeof(_queue.get_denials(i)));
                size_t _BUF =_queue.get_name(i).size() + 1;
                _queue.curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                _queue.curFile->file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

            }

            _queue.curFile->file->close();

            _queue.curFile->file = new QFile("exit.tmp");
            _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

            _queue.curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue.curFile->file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                                sizeof(_queue.get_denials(i)));
                        size_t _BUF = _queue.get_name(i).size() + 1;
                        _queue.curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue.curFile->file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

                    }
            _queue.curFile->file->close();
            delete ui;

        }
        else{
            _queue.curFile->file = new QFile("exit.tmp");
            _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);
            _queue.curFile->file->close();
            delete ui;
        }
    }
    }

}


void MainWindow::on_actionDenie_triggered(){

    bool ok;
    QInputDialog* dial = new QInputDialog;

    QString text;
    text = dial->getText(this, tr("Number of denial"),
                            tr("Number:"), QLineEdit::Normal,
                            "", &ok);
    unsigned n;
    if(text.isEmpty()) n = 0;
    else n = text.toUInt() - 1;

   _queue.get_denials(n)++;

    qDebug() << n << " " << _queue.get_denials(n) << "\n";

    if (_queue.get_denials(n) != 3){

        for(int i = n; i < _queue.get_size() - 1;i++ ){

            swap(_queue[i], _queue[i + 1]);
        }

        _queue.curWid->clear();

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            _queue.curWid->setItem(i, 0, name);

        }

    }

    else{

       _queue._erase(n);

        q_rows--;

        _queue.curWid->setRowCount(q_rows);

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            _queue.curWid->setItem(i, 0, name);

        }

    }

}

void MainWindow::on_action_triggered(){


    fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty()) return;
    MainWindow::setWindowTitle(fileName);
    _queue.curFile->file = new QFile(fileName);
    _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    for(int i = 0; i < q_rows; i++){

        _queue.get_name(i) = _queue.curWid->item(i, 0)->text();

    }
    _queue.curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

    for(int i = 0; i < q_rows; i++){

        _queue.curFile->file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                sizeof(_queue.get_denials(i)));
        size_t _BUF =_queue.get_name(i).size() + 1;
        _queue.curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
        _queue.curFile->file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

    }

    _queue.curFile->file->close();
    isChanged = false;

}

void MainWindow::on_action_2_triggered(){

    if(fileName == nullptr){

        fileName = QFileDialog::getSaveFileName(this, "*.bin");
        if (fileName.isEmpty()) return;
        MainWindow::setWindowTitle(fileName);
        _queue.curFile->file = new QFile(fileName);
        _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

        for(int i = 0; i < q_rows; i++){

            _queue.get_name(i) = _queue.curWid->item(i, 0)->text();

        }

        _queue.curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

        for(int i = 0; i < q_rows; i++){

            _queue.curFile->file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                        sizeof(_queue.get_denials(i)));
            size_t _BUF = _queue.get_name(i).size() + 1;
            _queue.curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            _queue.curFile->file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

        }

        _queue.curFile->file->close();

    }

    else{

        _queue.curFile->file->close();

        _queue.curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

        for(int i = 0; i < q_rows; i++){

            _queue.get_name(i) = _queue.curWid->item(i, 0)->text();

        }

        _queue.curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

        for(int i = 0; i < q_rows; i++){

            _queue.curFile->file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                        sizeof(_queue.get_denials(i)));
            size_t _BUF = _queue.get_name(i).size() + 1;
            _queue.curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            _queue.curFile->file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

        }

        _queue.curFile->file->close();

    }
    isChanged = false;

}


void MainWindow::on_action_3_triggered(){

    _queue._clear();
    fileName = QFileDialog::getOpenFileName(this, "*.bin");
    if (fileName.isEmpty()) return;
    MainWindow::setWindowTitle(fileName);
    _queue.curFile->file = nullptr;
    _queue.curFile->file = new QFile(fileName);
    _queue.curFile->file->open(QIODevice::ReadOnly);
    unsigned short len;
    _queue.curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
    q_rows = len;
    _queue.curWid->setRowCount(q_rows);
    _queue._resize(q_rows);

    for(int i = 0; i < q_rows; i++){

        _queue.curFile->file->read(reinterpret_cast<char*>(&_queue.get_denials(i)),
                sizeof(_queue.get_denials(i)));
        size_t _BUF_SZ;
        _queue.curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
        char* _BUF = new char[_BUF_SZ];
        _queue.curFile->file->read(_BUF, _BUF_SZ);
        string g = _BUF;
        qDebug() << QString::fromStdString(g);
        _queue.get_name(i) = QString::fromStdString(g);

        delete[] _BUF;

    }

    for(int i = 0; i < q_rows; i++){

        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(_queue.get_name(i));
        _queue.curWid->setItem(i, 0, name);

    }

    _queue.curFile->file->close();
    isChanged = false;

}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    isChanged = true;
}

void MainWindow::on_actionNew_file_triggered(){

    if(_queue.curFile->file != nullptr){
    _queue.curFile->file->close();

    _queue.curFile->file = nullptr;

    _queue._clear();

    _queue.curWid->clear();

    _queue._resize(0);

    MainWindow::setWindowTitle("New File");

    _queue.curWid->setRowCount(0);

    q_rows = 0;
    }
    else{
        _queue._clear();

        _queue.curWid->clear();

        _queue._resize(0);

        MainWindow::setWindowTitle("New File");

        _queue.curWid->setRowCount(0);

        q_rows = 0;
    }
    isChanged = false;

}

void MainWindow::on_actionaddtab_triggered(){

    //ui->tabWidget->addTab(new QTableWidget(15, 15), "fdsaf");
    Queue temp;


}

void MainWindow::on_tabWidget_currentChanged(int index){



}
