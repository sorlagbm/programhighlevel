#include "queue.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

const unsigned short q_cols = 2;

unsigned short q_rows = 0;

QString fileName = "";

QFile* file;

Queue _queue;

bool isChanged;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    ui->tableWidget->setColumnCount(q_cols);

    MainWindow::setWindowTitle("Last save");

    file = nullptr;
    file = new QFile("exit.tmp");
    if (QFile::exists("exit.tmp")){

        file->open(QIODevice::ReadOnly);
        unsigned short len;
        file->read(reinterpret_cast<char*>(&len), sizeof(len));
        q_rows = len;
        ui->tableWidget->setRowCount(q_rows);
        _queue._resize(q_rows);

        for(int i = 0; i < q_rows; i++){

            file->read(reinterpret_cast<char*>(&_queue.get_denials(i)), sizeof(_queue.get_denials(i)));
            size_t _BUF_SZ;
            file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
            char* _BUF = new char[_BUF_SZ];
            file->read(_BUF, _BUF_SZ);
            string g = _BUF;
            qDebug() << QString::fromStdString(g);
            _queue.get_name(i) = QString::fromStdString(g);
            delete[] _BUF;

        }

        for(int i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            ui->tableWidget->setItem(i, 0, name);

        }

        file->close();

    }

    else{
        file->write("");
    }


}

void MainWindow::on_actionDelete_by_id_triggered(){

    QString text = QInputDialog::getText(this, tr("Delete"),
                            tr("Number:"), QLineEdit::Normal,
                            "", new bool());

    if(text == ""){

        QMessageBox::information(this, "No information!", "No information!");

    }
    else {

        unsigned n = text.toUInt();

        ui->tableWidget->clear();

        _queue._erase(n);

        q_rows--;

        ui->tableWidget->setRowCount(q_rows);

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            ui->tableWidget->setItem(i, 0, name);

        }

    }
}

void MainWindow::on_actionAdd_User_triggered(){

    bool ok;

    QString text = QInputDialog::getText(this, tr("New User"),
                            tr("Name:"), QLineEdit::Normal,
                            "", &ok);

    for(int i = 0; i < q_rows; i++){

        if (text == _queue.get_name(i)){

            QMessageBox::information(this, "Copy!!!", "Copy!!!");
            return;

        }

    }

    _queue.push(text);

    q_rows++;

    ui->tableWidget->setRowCount(q_rows);

    QTableWidgetItem *name = new QTableWidgetItem;
    name->setText(_queue.get_name(_queue.get_size() - 1));
    ui->tableWidget->setItem(q_rows - 1, 0, name);

;
}

MainWindow::~MainWindow(){

    file = nullptr;
    file = new QFile("exit.tmp");
    file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

    for(int i = 0; i < q_rows; i++){

        file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                sizeof(_queue.get_denials(i)));
        size_t _BUF = _queue.get_name(i).size() + 1;
        file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
        file->write(_queue.get_name(i).toStdString().c_str(), _BUF);

    }
    file->close();
    delete ui;

}


void MainWindow::on_actionDenie_triggered(){

    bool ok;

    QString text = QInputDialog::getText(this, tr("Number of denial"),
                            tr("Number:"), QLineEdit::Normal,
                            "", &ok);

    unsigned n = text.toUInt();

   _queue.get_denials(n)++;

    qDebug() << n << " " << _queue.get_denials(n) << "\n";

    if (_queue.get_denials(n) != 3){

        for(int i = n; i < _queue.get_size() - 1;i++ ){

            swap(_queue[i], _queue[i + 1]);
        }

        ui->tableWidget->clear();

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            ui->tableWidget->setItem(i, 0, name);

        }

    }

    else{

       _queue._erase(n);

        q_rows--;

        ui->tableWidget->setRowCount(q_rows);

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue.get_name(i));
            ui->tableWidget->setItem(i, 0, name);

        }

    }

}

void MainWindow::on_action_triggered(){

    fileName = QFileDialog::getSaveFileName(this, "Save as");
    MainWindow::setWindowTitle(fileName);
    if(file == nullptr) file = new QFile(fileName);
    file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

    for(int i = 0; i < q_rows; i++){

        file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                sizeof(_queue.get_denials(i)));
        size_t _BUF =_queue.get_name(i).size() + 1;
        file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
        file->write(_queue.get_name(i).toStdString().c_str(), _BUF);
        _BUF = _queue.get_work(i).size() + 1;
        file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
        file->write(_queue.get_work(i).toStdString().c_str(), _BUF);

    }

    file->close();

}

void MainWindow::on_action_2_triggered(){

    if(fileName == nullptr){

        fileName = QFileDialog::getSaveFileName(this, "*.bin");
        MainWindow::setWindowTitle(fileName);
        file = new QFile(fileName);
        file->open(QIODevice::WriteOnly | QIODevice::Truncate);
        file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

        for(int i = 0; i < q_rows; i++){

            file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                        sizeof(_queue.get_denials(i)));
            size_t _BUF = _queue.get_name(i).size() + 1;
            file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            file->write(_queue.get_name(i).toStdString().c_str(), _BUF);
            _BUF = _queue.get_work(i).size() + 1;
            file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            file->write(_queue.get_work(i).toStdString().c_str(), _BUF);

        }

        file->close();

    }

    else{

        file->close();
        file->open(QIODevice::WriteOnly | QIODevice::Truncate);
        file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

        for(int i = 0; i < q_rows; i++){

            file->write(reinterpret_cast<char*>(&_queue.get_denials(i)),
                        sizeof(_queue.get_denials(i)));
            size_t _BUF = _queue.get_name(i).size() + 1;
            file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            file->write(_queue.get_name(i).toStdString().c_str(), _BUF);
            _BUF = _queue.get_work(i).size() + 1;
            file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            file->write(_queue.get_work(i).toStdString().c_str(), _BUF);

        }

        file->close();

    }

}


void MainWindow::on_action_3_triggered(){

    _queue._clear();
    fileName = QFileDialog::getOpenFileName(this, "*.bin");
    MainWindow::setWindowTitle(fileName);
    file = nullptr;
    file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    unsigned short len;
    file->read(reinterpret_cast<char*>(&len), sizeof(len));
    q_rows = len;
    ui->tableWidget->setRowCount(q_rows);
    _queue._resize(q_rows);

    for(int i = 0; i < q_rows; i++){

        file->read(reinterpret_cast<char*>(&_queue.get_denials(i)),
                sizeof(_queue.get_denials(i)));
        size_t _BUF_SZ;
        file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
        char* _BUF = new char[_BUF_SZ];
        file->read(_BUF, _BUF_SZ);
        string g = _BUF;
        qDebug() << QString::fromStdString(g);
        _queue.get_name(i) = QString::fromStdString(g);

        delete[] _BUF;

    }

    for(int i = 0; i < q_rows; i++){

        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(_queue.get_name(i));
        ui->tableWidget->setItem(i, 0, name);

    }

    file->close();

}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    isChanged = true;
}

void MainWindow::on_actionNew_file_triggered(){

    if(file != nullptr){
    file->close();

    file = nullptr;

    _queue._clear();

    ui->tableWidget->clear();

    _queue._resize(0);

    MainWindow::setWindowTitle("New File");

    ui->tableWidget->setRowCount(0);

    q_rows = 0;
    }

}

void MainWindow::on_actionaddtab_triggered(){

    //ui->tabWidget->addTab(new QTableWidget(15, 15), "fdsaf");
    Queue temp;


}

void MainWindow::on_tabWidget_currentChanged(int index){



}
