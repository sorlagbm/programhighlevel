#include "queue.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "saveornot.h"

const unsigned short q_cols = 2;

unsigned short q_rows = 0;

size_t tabCount = 0;
size_t curTab = 0;

QString fileName = "";

QFile* infoFile;

vector<Queue> _queue(1);

bool isChanged;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
    infoFile = new QFile("infoFile.tmp");
    if(infoFile->size() == 0){

        startScreen = new StartScreen(this);
        connect(startScreen, &StartScreen::mainWindow_openFile, this, &MainWindow::show);
        connect(startScreen, &StartScreen::mainWindow_newFile, this, &MainWindow::show);
        startScreen->setWindowTitle("Kursovaya Rabota LVL2");
        if(startScreen->exec() == QDialog::Accepted){

            fileName = QFileDialog::getOpenFileName(this, "*.bin");
            if (fileName.isEmpty()) return;
            MainWindow::setWindowTitle(fileName);

            _queue[0] = Queue(0, new Queue::FileWork(new QFile(fileName), fileName), ui->tableWidget, 0);

            _queue[ui->tabWidget->currentIndex()].curFile->file->open(QIODevice::ReadOnly);
            unsigned short len;
            _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
            q_rows = len;
            _queue[ui->tabWidget->currentIndex()].curWid->setColumnCount(q_cols);
            _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(q_rows);
            _queue[ui->tabWidget->currentIndex()]._resize(q_rows);

            for(int i = 0; i < q_rows; i++){

                _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&_queue[ui->tabWidget->currentIndex()].get_denials(i)),
                        sizeof(_queue[ui->tabWidget->currentIndex()].get_denials(i)));
                size_t _BUF_SZ;
                _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
                char* _BUF = new char[_BUF_SZ];
                _queue[ui->tabWidget->currentIndex()].curFile->file->read(_BUF, _BUF_SZ);
                string g = _BUF;
                qDebug() << QString::fromStdString(g);
                _queue[ui->tabWidget->currentIndex()].get_name(i) = QString::fromStdString(g);

                _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
                _BUF = new char[_BUF_SZ];
                _queue[ui->tabWidget->currentIndex()].curFile->file->read(_BUF, _BUF_SZ);
                g = _BUF;
                qDebug() << QString::fromStdString(g);
                _queue[ui->tabWidget->currentIndex()].get_work(i) = QString::fromStdString(g);

                delete[] _BUF;

            }

            for(int i = 0; i < q_rows; i++){

                QTableWidgetItem *name = new QTableWidgetItem;
                name->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
                _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 0, name);

                QTableWidgetItem *work = new QTableWidgetItem;
                work->setText(_queue[ui->tabWidget->currentIndex()].get_work(i));
                _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 1, work);

            }

            _queue[ui->tabWidget->currentIndex()].curFile->file->close();
            _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;
            ui->tabWidget->setTabText(0, _queue[0].curFile->fileName);
        }
        else{

            MainWindow::setWindowTitle("New file");
            _queue[0] = Queue(0, new Queue::FileWork(nullptr), ui->tableWidget, 0);
            _queue[0].curWid->setColumnCount(q_cols);
            _queue[0].curWid->setRowCount(0);
             ui->tabWidget->setTabText(0, _queue[0].curFile->fileName);

        }

    }
    else {

        startScreen = new StartScreen(this);
        connect(startScreen, &StartScreen::mainWindow_openFile, this, &MainWindow::show);
        connect(startScreen, &StartScreen::mainWindow_newFile, this, &MainWindow::show);
        startScreen->setWindowTitle("Kursovaya Rabota LVL2");

        MainWindow::setWindowTitle("Last save");

        //QFile* conFile = new QFile("temp.tmp");
        //conFile->read(reinterpret_cast<char*>(&tabCount), sizeof(tabCount));
        //conFile->read(reinterpret_cast<char*>(&curTab), sizeof(curTab));
        //ui->tabWidget->setCurrentIndex(curTab);
        //ui->tabWidget->clear();
        infoFile = new QFile("infoFile.tmp");
        infoFile->open(QIODevice::ReadOnly);

        infoFile->read(reinterpret_cast<char*>(&tabCount), sizeof(tabCount));
        infoFile->read(reinterpret_cast<char*>(&curTab), sizeof(curTab));
        _queue.resize(tabCount);

        size_t _BUF_SZ;
        infoFile->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
        char* _BUF = new char[_BUF_SZ];
        infoFile->read(_BUF, _BUF_SZ);
        string g = _BUF;

        _queue[0] = Queue(0, new Queue::FileWork(new QFile(QString::fromStdString(g)), QString::fromStdString(g)), ui->tableWidget, 0);

        _queue[0].curFile->file->open(QIODevice::ReadOnly);
        unsigned short len;
        _queue[0].curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
        q_rows = len;
        _queue[0].curWid->setRowCount(q_rows);
        _queue[0].curWid->setColumnCount(q_cols);
        _queue[0]._resize(q_rows);
        for(int i = 0; i < q_rows; i++){

            _queue[0].curFile->file->read(reinterpret_cast<char*>(&_queue[0].get_denials(i)),
                    sizeof(_queue[0].get_denials(i)));
            size_t _BUF_SZ;
            _queue[0].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
            char* _BUF = new char[_BUF_SZ];
            _queue[0].curFile->file->read(_BUF, _BUF_SZ);
            string a = _BUF;
            qDebug() << QString::fromStdString(a);
            _queue[0].get_name(i) = QString::fromStdString(a);

            _queue[0].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
            _BUF = new char[_BUF_SZ];
            _queue[0].curFile->file->read(_BUF, _BUF_SZ);
            g = _BUF;
            qDebug() << QString::fromStdString(g);
            _queue[0].get_work(i) = QString::fromStdString(g);

            delete[] _BUF;

        }

        for(int i = 0; i < q_rows; i++){


            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue[0].get_name(i));
            _queue[0].curWid->setItem(i, 0, name);

            QTableWidgetItem *work = new QTableWidgetItem;
            work->setText(_queue[0].get_work(i));
            _queue[0].curWid->setItem(i, 1, work);


        }

        ui->tabWidget->setTabText(0, _queue[0].curFile->fileName);
        _queue[0].curFile->file->close();
        _queue[0].curFile->isChanged = false;

        for(size_t index = 1; index < tabCount; ++index){

            size_t _BUF_SZ;
            infoFile->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
            char* _BUF = new char[_BUF_SZ];
            infoFile->read(_BUF, _BUF_SZ);
            string g = _BUF;

            _queue[index] = Queue(0, new Queue::FileWork(new QFile(QString::fromStdString(g)), QString::fromStdString(g)), new QTableWidget(0, 1), 0);

            _queue[index].curFile->file->open(QIODevice::ReadOnly);
            unsigned short len;
            _queue[index].curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
            q_rows = len;
            _queue[index].curWid->setRowCount(q_rows);
            _queue[index].curWid->setColumnCount(q_cols);
            _queue[index]._resize(q_rows);
            for(int i = 0; i < q_rows; i++){

                _queue[index].curFile->file->read(reinterpret_cast<char*>(&_queue[index].get_denials(i)),
                        sizeof(_queue[index].get_denials(i)));
                size_t _BUF_SZ;
                _queue[index].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
                char* _BUF = new char[_BUF_SZ];
                _queue[index].curFile->file->read(_BUF, _BUF_SZ);
                string a = _BUF;
                qDebug() << QString::fromStdString(a);
                _queue[index].get_name(i) = QString::fromStdString(a);

                _queue[index].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
                _BUF = new char[_BUF_SZ];
                _queue[index].curFile->file->read(_BUF, _BUF_SZ);
                g = _BUF;
                qDebug() << QString::fromStdString(g);
                _queue[index].get_work(i) = QString::fromStdString(g);

                delete[] _BUF;

            }

            for(int i = 0; i < q_rows; i++){

                QTableWidgetItem *name = new QTableWidgetItem;
                name->setText(_queue[index].get_name(i));
                _queue[index].curWid->setItem(i, 0, name);

                QTableWidgetItem *work = new QTableWidgetItem;
                work->setText(_queue[index].get_work(i));
                _queue[index].curWid->setItem(i, 1, work);

            }

            _queue[index].curFile->file->close();
            _queue[index].curFile->isChanged = false;

            ui->tabWidget->addTab(_queue[index].curWid, _queue[index].curFile->fileName);

        }

        infoFile->close();
        ui->tabWidget->setCurrentIndex(curTab);

    }

}

void MainWindow::on_actionDelete_by_id_triggered(){

    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    QString text = QInputDialog::getText(this, tr("Delete"),
                            tr("Number:"), QLineEdit::Normal,
                            "", new bool());

        unsigned n;

        if(text.isEmpty()){
            n = 0;
            QMessageBox::information(this, "First element was deleted!", "First element was deleted!");
        }
        else n = text.toUInt() - 1;

        if(n >= _queue[ui->tabWidget->currentIndex()].get_size()) {QMessageBox::information(this, "Выход за пределы!", "Выход за пределы!");
             _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;
            return;}

        _queue[ui->tabWidget->currentIndex()].curWid->clear();

        _queue[ui->tabWidget->currentIndex()]._erase(n);

        q_rows--;

        _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(q_rows);

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
            _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 0, name);

            QTableWidgetItem *work = new QTableWidgetItem;
            work->setText(_queue[ui->tabWidget->currentIndex()].get_work(i));
            _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 1, work);

        }
        _queue[ui->tabWidget->currentIndex()].curFile->isChanged = true;
}

void MainWindow::on_actionAdd_User_triggered(){

    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    bool ok;

    QString text = QInputDialog::getText(this, tr("New User"),
                            tr("Name:"), QLineEdit::Normal,
                            "", &ok);

    QString Work = QInputDialog::getText(this, tr("Добавить работу"),
                                         tr("Вид деятельности:"), QLineEdit::Normal,
                                         "", &ok);

    for(int i = 0; i < q_rows; i++){

        if (text == _queue[ui->tabWidget->currentIndex()].get_name(i)){

            Dialog* choise = new Dialog;
            if (choise->exec() == QDialog::Rejected){
                return;
            }
            break;

        }

    }

    if(!text.isEmpty()){

        _queue[ui->tabWidget->currentIndex()].push(text, Work);

        q_rows++;

        _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(q_rows);

        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(_queue[ui->tabWidget->currentIndex()].get_name(_queue[ui->tabWidget->currentIndex()].get_size() - 1));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(q_rows - 1, 0, name);

        QTableWidgetItem *work = new QTableWidgetItem;
        work->setText(_queue[ui->tabWidget->currentIndex()].get_work(_queue[ui->tabWidget->currentIndex()].get_size() - 1));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(q_rows - 1, 1, work);


    }
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = true;

}

MainWindow::~MainWindow(){

    tabCount = ui->tabWidget->count();

    for(size_t index = 0; index < ui->tabWidget->count(); ++index){

        if(!_queue[index].curFile->isChanged && _queue[index].curFile->file == nullptr){

            tabCount -= 1;

        }

    }

    if(tabCount == 0) {
        delete ui;

        infoFile->open(QIODevice::WriteOnly | QIODevice::Truncate);
        infoFile->close();
        return;

    }

    curTab = ui->tabWidget->currentIndex();

    infoFile->open(QIODevice::WriteOnly | QIODevice::Truncate);
    infoFile->write(reinterpret_cast<char*>(&tabCount), sizeof(tabCount));
    infoFile->write(reinterpret_cast<char*>(&curTab), sizeof(curTab));

    for(size_t index = 0; index < tabCount; ++index){

        if(_queue[index].curFile->isChanged){

            SaveorNot* exit = new SaveorNot;
            if(exit->exec() == QDialog::Accepted){

                if(_queue[index].curFile->file != nullptr){
                    if(!_queue[index].curFile->file->isOpen())
                        _queue[index].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].get_name(i) = _queue[index].curWid->item(i, 0)->text();
                        _queue[index].get_work(i) = _queue[index].curWid->item(i, 1)->text();

                    }

                    _queue[index].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_queue[index].get_denials(i)),
                                    sizeof(_queue[index].get_denials(i)));
                        size_t _BUF = _queue[index].get_name(i).size() + 1;
                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[index].curFile->file->write(_queue[index].get_name(i).toStdString().c_str(), _BUF);

                        _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

                    }
                    _queue[index].curFile->file->close();
                    size_t _BUF = _queue[index].curFile->fileName.size() + 1;
                    infoFile->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                    infoFile->write(_queue[index].curFile->fileName.toStdString().c_str(), _BUF);
                }
                else{
                    fileName = QFileDialog::getSaveFileName(this, "*.bin");
                    if (fileName.isEmpty()) return;
                    MainWindow::setWindowTitle(fileName);
                    _queue[index].curFile->file = new QFile(fileName);
                    _queue[index].curFile->fileName = fileName;
                    _queue[index].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].get_name(i) = _queue[index].curWid->item(i, 0)->text();
                        _queue[index].get_work(i) = _queue[index].curWid->item(i, 1)->text();

                    }

                    _queue[index].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_queue[index].get_denials(i)),
                                sizeof(_queue[index].get_denials(i)));
                        size_t _BUF = _queue[index].get_name(i).size() + 1;
                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[index].curFile->file->write(_queue[index].get_name(i).toStdString().c_str(), _BUF);

                        _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

                    }
                    _queue[index].curFile->file->close();
                    size_t _BUF = _queue[index].curFile->fileName.size() + 1;
                    infoFile->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                    infoFile->write(_queue[index].curFile->fileName.toStdString().c_str(), _BUF);
                }
            }
            else{

                size_t _BUF = _queue[index].curFile->fileName.size() + 1;
                infoFile->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                infoFile->write(_queue[index].curFile->fileName.toStdString().c_str(), _BUF);

            }
        }
        else{

            if(_queue[index].curFile->file != nullptr){

                size_t _BUF = _queue[index].curFile->fileName.size() + 1;
                infoFile->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                infoFile->write(_queue[index].curFile->fileName.toStdString().c_str(), _BUF);

            }
        }

    }

    infoFile->close();
    delete ui;
}


void MainWindow::on_actionDenie_triggered(){

    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    bool ok;
    QInputDialog* dial = new QInputDialog;

    QString text;
    text = dial->getText(this, tr("Number of denial"),
                            tr("Number:"), QLineEdit::Normal,
                            "", &ok);
    unsigned n;
    if(text.isEmpty()) n = 0;
    else n = text.toUInt() - 1;

    if(n >= _queue[ui->tabWidget->currentIndex()].get_size()) {QMessageBox::information(this, "Выход за пределы!", "Выход за пределы!");
         _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;
        return;}

   _queue[ui->tabWidget->currentIndex()].get_denials(n)++;

    if (_queue[ui->tabWidget->currentIndex()].get_denials(n) != 3){

        for(int i = n; i < _queue[ui->tabWidget->currentIndex()].get_size() - 1;i++ ){

            swap(_queue[ui->tabWidget->currentIndex()][i], _queue[ui->tabWidget->currentIndex()][i + 1]);
        }

        _queue[ui->tabWidget->currentIndex()].curWid->clear();

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
            _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 0, name);


            QTableWidgetItem *work = new QTableWidgetItem;
            work->setText(_queue[ui->tabWidget->currentIndex()].get_work(i));
            _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 1, work);

        }
        _queue[ui->tabWidget->currentIndex()].curFile->isChanged = true;

    }

    else{

       _queue[ui->tabWidget->currentIndex()]._erase(n);

        q_rows--;

        _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(q_rows);

        for(auto i = 0; i < q_rows; i++){

            QTableWidgetItem *name = new QTableWidgetItem;
            name->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
            _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 0, name);


            QTableWidgetItem *work = new QTableWidgetItem;
            work->setText(_queue[ui->tabWidget->currentIndex()].get_work(i));
            _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 1, work);

        }
        _queue[ui->tabWidget->currentIndex()].curFile->isChanged = true;

    }

}

void MainWindow::on_action_triggered(){

    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty()) return;
    MainWindow::setWindowTitle(fileName);
    _queue[ui->tabWidget->currentIndex()].curFile->file = new QFile(fileName);
    _queue[ui->tabWidget->currentIndex()].curFile->fileName = fileName;
    _queue[ui->tabWidget->currentIndex()].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    for(int i = 0; i < q_rows; i++){

        _queue[ui->tabWidget->currentIndex()].get_name(i) = _queue[ui->tabWidget->currentIndex()].curWid->item(i, 0)->text();
        _queue[ui->tabWidget->currentIndex()].get_work(i) = _queue[ui->tabWidget->currentIndex()].curWid->item(i, 1)->text();

    }
    _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

    for(int i = 0; i < q_rows; i++){

        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_queue[ui->tabWidget->currentIndex()].get_denials(i)),
                sizeof(_queue[ui->tabWidget->currentIndex()].get_denials(i)));
        size_t _BUF =_queue[ui->tabWidget->currentIndex()].get_name(i).size() + 1;
        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_name(i).toStdString().c_str(), _BUF);

        _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);


    }

    _queue[ui->tabWidget->currentIndex()].curFile->file->close();
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;
    ui->tabWidget->setTabText(ui->tabWidget->count() - 1, _queue[ui->tabWidget->currentIndex()].curFile->fileName);

}

void MainWindow::on_action_2_triggered(){

    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    if(_queue[ui->tabWidget->currentIndex()].curFile->file == nullptr){

        fileName = QFileDialog::getSaveFileName(this, "*.bin");
        if (fileName.isEmpty()) return;
        MainWindow::setWindowTitle(fileName);
        _queue[ui->tabWidget->currentIndex()].curFile->file = new QFile(fileName);
        _queue[ui->tabWidget->currentIndex()].curFile->fileName = fileName;
        _queue[ui->tabWidget->currentIndex()].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

        for(int i = 0; i < q_rows; i++){

            _queue[ui->tabWidget->currentIndex()].get_name(i) = _queue[ui->tabWidget->currentIndex()].curWid->item(i, 0)->text();
            _queue[ui->tabWidget->currentIndex()].get_work(i) = _queue[ui->tabWidget->currentIndex()].curWid->item(i, 1)->text();


        }

        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

        for(int i = 0; i < q_rows; i++){

            _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_queue[ui->tabWidget->currentIndex()].get_denials(i)),
                        sizeof(_queue[ui->tabWidget->currentIndex()].get_denials(i)));
            size_t _BUF = _queue[ui->tabWidget->currentIndex()].get_name(i).size() + 1;
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_name(i).toStdString().c_str(), _BUF);

            _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

        }

        _queue[ui->tabWidget->currentIndex()].curFile->file->close();
        _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;

    }

    else{

        _queue[ui->tabWidget->currentIndex()].curFile->file->close();

        _queue[ui->tabWidget->currentIndex()].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

        for(int i = 0; i < q_rows; i++){

            _queue[ui->tabWidget->currentIndex()].get_name(i) = _queue[ui->tabWidget->currentIndex()].curWid->item(i, 0)->text();
           _queue[ui->tabWidget->currentIndex()].get_work(i) = _queue[ui->tabWidget->currentIndex()].curWid->item(i, 1)->text();

        }

        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

        for(int i = 0; i < q_rows; i++){

            _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_queue[ui->tabWidget->currentIndex()].get_denials(i)),
                        sizeof(_queue[ui->tabWidget->currentIndex()].get_denials(i)));
            size_t _BUF = _queue[ui->tabWidget->currentIndex()].get_name(i).size() + 1;
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_name(i).toStdString().c_str(), _BUF);

            _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
            _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

        }

        _queue[ui->tabWidget->currentIndex()].curFile->file->close();

    }
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;

}


void MainWindow::on_action_3_triggered(){

    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    _queue[ui->tabWidget->currentIndex()]._clear();
    fileName = QFileDialog::getOpenFileName(this, "*.bin");
    if (fileName.isEmpty()) return;
    MainWindow::setWindowTitle(fileName);
    _queue[ui->tabWidget->currentIndex()].curFile->file = nullptr;
    _queue[ui->tabWidget->currentIndex()].curFile->file = new QFile(fileName);
    _queue[ui->tabWidget->currentIndex()].curFile->fileName = fileName;
    _queue[ui->tabWidget->currentIndex()].curFile->file->open(QIODevice::ReadOnly);
    unsigned short len;
    _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
    q_rows = len;
    _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(q_rows);
    _queue[ui->tabWidget->currentIndex()]._resize(q_rows);

    for(int i = 0; i < q_rows; i++){

        _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&_queue[ui->tabWidget->currentIndex()].get_denials(i)),
                sizeof(_queue[ui->tabWidget->currentIndex()].get_denials(i)));
        size_t _BUF_SZ;
        _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
        char* _BUF = new char[_BUF_SZ];
        _queue[ui->tabWidget->currentIndex()].curFile->file->read(_BUF, _BUF_SZ);
        string g = _BUF;
        _queue[ui->tabWidget->currentIndex()].get_name(i) = QString::fromStdString(g);


        _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
        _BUF = new char[_BUF_SZ];
        _queue[ui->tabWidget->currentIndex()].curFile->file->read(_BUF, _BUF_SZ);
        g = _BUF;
        qDebug() << QString::fromStdString(g);
        _queue[ui->tabWidget->currentIndex()].get_work(i) = QString::fromStdString(g);


        delete[] _BUF;

    }

    for(int i = 0; i < q_rows; i++){

        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 0, name);

        QTableWidgetItem *work = new QTableWidgetItem;
        work->setText(_queue[ui->tabWidget->currentIndex()].get_work(i));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 1, work);

    }

    _queue[ui->tabWidget->currentIndex()].curFile->file->close();
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), _queue[ui->tabWidget->currentIndex()].curFile->fileName);

}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = true;
}

void MainWindow::on_actionNew_file_triggered(){

    q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    if(_queue[ui->tabWidget->currentIndex()].curFile->file != nullptr){
    _queue[ui->tabWidget->currentIndex()].curFile->file->close();

    _queue[ui->tabWidget->currentIndex()].curFile->file = nullptr;
    _queue[ui->tabWidget->currentIndex()].curFile->fileName = "";

    _queue[ui->tabWidget->currentIndex()]._clear();

    _queue[ui->tabWidget->currentIndex()].curWid->clear();

    _queue[ui->tabWidget->currentIndex()]._resize(0);

    MainWindow::setWindowTitle("New File");

    _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(0);

    q_rows = 0;
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;
    }
    else{
        _queue[ui->tabWidget->currentIndex()]._clear();

        _queue[ui->tabWidget->currentIndex()].curWid->clear();

        _queue[ui->tabWidget->currentIndex()]._resize(0);

        MainWindow::setWindowTitle("New File");

        _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(0);

        q_rows = 0;
    }
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = false;
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), "New file");

}

void MainWindow::on_actionaddtab_triggered(){

    QTableWidget* newT = new QTableWidget(0, 2);
    //q_rows = _queue[ui->tabWidget->currentIndex()].get_size();
    ui->tabWidget->addTab(newT, "fdsaf");
    Queue temp = Queue(0, new Queue::FileWork(), newT, 0);
    _queue.push_back(temp);
    tabCount += 1;
    ui->tabWidget->setTabText(ui->tabWidget->count() - 1, "New file");
    _queue[ui->tabWidget->count() - 1].curFile->isChanged = false;

}

void MainWindow::on_tabWidget_currentChanged(int index){

    if (!_queue[index].curFile->fileName.isEmpty() && _queue[index].curFile->file != nullptr)
        MainWindow::setWindowTitle(_queue[index].curFile->fileName);
    else
        MainWindow::setWindowTitle("New File");

}

void MainWindow::on_tableWidget_itemEntered(QTableWidgetItem *item){



}

void MainWindow::on_tabWidget_tabCloseRequested(int index){

    q_rows = _queue[index].get_size();

    if(ui->tabWidget->count() != 1){
        if(_queue[index].curFile->isChanged){

            SaveorNot* exit = new SaveorNot;
            if(exit->exec() == QDialog::Accepted){

                if(_queue[index].curFile->file != nullptr){
                    if(!_queue[index].curFile->file->isOpen())
                        _queue[index].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].get_name(i) = _queue[index].curWid->item(i, 0)->text();
                        _queue[index].get_work(i) = _queue[index].curWid->item(i, 1)->text();

                    }

                    _queue[index].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_queue[index].get_denials(i)),
                                    sizeof(_queue[index].get_denials(i)));
                        size_t _BUF = _queue[index].get_name(i).size() + 1;
                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[index].curFile->file->write(_queue[index].get_name(i).toStdString().c_str(), _BUF);

                        _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

                    }
                    _queue[index].curFile->file->close();
                }
                else{
                    fileName = QFileDialog::getSaveFileName(this, "*.bin");
                    if (fileName.isEmpty()) return;
                    MainWindow::setWindowTitle(fileName);
                    _queue[index].curFile->file = new QFile(fileName);
                    _queue[index].curFile->fileName = fileName;
                    _queue[index].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].get_name(i) = _queue[index].curWid->item(i, 0)->text();
                        _queue[index].get_work(i) = _queue[index].curWid->item(i, 1)->text();

                    }

                    _queue[index].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_queue[index].get_denials(i)),
                                sizeof(_queue[index].get_denials(i)));
                        size_t _BUF = _queue[index].get_name(i).size() + 1;
                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[index].curFile->file->write(_queue[index].get_name(i).toStdString().c_str(), _BUF);

                        _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

                    }
                    _queue[index].curFile->file->close();
                }
            }
        }
        ui->tabWidget->removeTab(index);
        _queue.erase(_queue.begin() + index);
    }
    else{


        if(_queue[index].curFile->isChanged){

            SaveorNot* exit = new SaveorNot;
            if(exit->exec() == QDialog::Accepted){

                if(_queue[index].curFile->file != nullptr){
                    if(!_queue[index].curFile->file->isOpen())
                        _queue[index].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].get_name(i) = _queue[index].curWid->item(i, 0)->text();
                        _queue[index].get_work(i) = _queue[index].curWid->item(i, 1)->text();

                    }

                    _queue[index].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_queue[index].get_denials(i)),
                                    sizeof(_queue[index].get_denials(i)));
                        size_t _BUF = _queue[index].get_name(i).size() + 1;
                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[index].curFile->file->write(_queue[index].get_name(i).toStdString().c_str(), _BUF);

                        _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

                    }
                    _queue[index].curFile->file->close();
                }
                else{
                    fileName = QFileDialog::getSaveFileName(this, "*.bin");
                    if (fileName.isEmpty()) return;
                    MainWindow::setWindowTitle(fileName);
                    _queue[index].curFile->file = new QFile(fileName);
                    _queue[index].curFile->fileName = fileName;
                    _queue[index].curFile->file->open(QIODevice::WriteOnly | QIODevice::Truncate);

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].get_name(i) = _queue[index].curWid->item(i, 0)->text();
                        _queue[index].get_work(i) = _queue[index].curWid->item(i, 1)->text();

                    }

                    _queue[index].curFile->file->write(reinterpret_cast<char*>(&q_rows), sizeof(q_rows));

                    for(int i = 0; i < q_rows; i++){

                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_queue[index].get_denials(i)),
                                sizeof(_queue[index].get_denials(i)));
                        size_t _BUF = _queue[index].get_name(i).size() + 1;
                        _queue[index].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[index].curFile->file->write(_queue[index].get_name(i).toStdString().c_str(), _BUF);


                        _BUF =_queue[ui->tabWidget->currentIndex()].get_work(i).size() + 1;
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(reinterpret_cast<char*>(&_BUF), sizeof(_BUF));
                        _queue[ui->tabWidget->currentIndex()].curFile->file->write(_queue[ui->tabWidget->currentIndex()].get_work(i).toStdString().c_str(), _BUF);

                    }
                    _queue[index].curFile->file->close();
                }
            }
        }

        this->hide();

        if(startScreen->exec() == QDialog::Accepted){

            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setColumnCount(q_cols);
            fileName = QFileDialog::getOpenFileName(this, "*.bin");
            if (fileName.isEmpty()) return;
            MainWindow::setWindowTitle(fileName);

            _queue[0]._clear();
            _queue[0].curFile->file = new QFile(fileName);
            _queue[0].curFile->fileName = fileName;
            _queue[0].curWid = ui->tableWidget;

            _queue[0].curFile->file->open(QIODevice::ReadOnly);
            unsigned short len;
            _queue[0].curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
            q_rows = len;
            _queue[0].curWid->setColumnCount(q_cols);
            _queue[0].curWid->setRowCount(q_rows);
            _queue[0]._resize(q_rows);

            for(int i = 0; i < q_rows; i++){

                _queue[0].curFile->file->read(reinterpret_cast<char*>(&_queue[0].get_denials(i)),
                        sizeof(_queue[0].get_denials(i)));
                size_t _BUF_SZ;
                _queue[0].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
                char* _BUF = new char[_BUF_SZ];
                _queue[0].curFile->file->read(_BUF, _BUF_SZ);
                string g = _BUF;
                _queue[0].get_name(i) = QString::fromStdString(g);


                _queue[ui->tabWidget->currentIndex()].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
                _BUF = new char[_BUF_SZ];
                _queue[ui->tabWidget->currentIndex()].curFile->file->read(_BUF, _BUF_SZ);
                g = _BUF;
                qDebug() << QString::fromStdString(g);
                _queue[ui->tabWidget->currentIndex()].get_work(i) = QString::fromStdString(g);


                delete[] _BUF;

            }

            for(int i = 0; i < q_rows; i++){

                QTableWidgetItem *name = new QTableWidgetItem;
                name->setText(_queue[0].get_name(i));
                _queue[0].curWid->setItem(i, 0, name);

                QTableWidgetItem *work = new QTableWidgetItem;
                work->setText(_queue[0].get_work(i));
                _queue[0].curWid->setItem(i, 1, work);

            }

            _queue[0].curFile->file->close();
            _queue[0].curFile->isChanged = false;
        }
        else{
            ui->tableWidget->clear();
            ui->tableWidget->setRowCount(0);
            ui->tableWidget->setColumnCount(q_cols);

            MainWindow::setWindowTitle("New file");
            _queue[0] = Queue(0, new Queue::FileWork(nullptr), ui->tableWidget, 0);
            _queue[0].curWid->setColumnCount(q_cols);
            _queue[0].curWid->setRowCount(0);

            _queue[0]._clear();
            _queue[0].curFile->file = new QFile(fileName);
            _queue[0].curFile->fileName = fileName;
            _queue[0].curWid = ui->tableWidget;
            _queue[0].curFile->isChanged = false;

        }

    }
}

void merge(vector<Queue>& c, vector<Queue> a, vector<Queue> b, int id){


    static const std::size_t STEP(1);
    vector<Queue::User>::const_iterator bIt = b[0]._queue.begin();
    for(vector<Queue::User>::const_iterator aIt = a[id]._queue.begin();
        aIt != a[id]._queue.end(); ++aIt)
    {
        c[0].push(aIt->name, aIt->work);
    }
    for(vector<Queue::User>::const_iterator bIt = b[0]._queue.begin();
        bIt != b[0]._queue.end(); ++bIt)
    {
        c[0].push(bIt->name, bIt->work);
    }

}

void MainWindow::on_connectQueue_triggered(){

    //_queue[ui->tabWidget->currentIndex()].curWid->clear();
    //_queue[ui->tabWidget->currentIndex()].curWid->setRowCount(0);

    fileName = QFileDialog::getOpenFileName(this, "*.bin");
    if (fileName.isEmpty()) return;

    vector<Queue> temp(1);
    temp[0] = Queue(0, new Queue::FileWork(new QFile(fileName), fileName), _queue[ui->tabWidget->currentIndex()].curWid, 0);
    temp[0].curFile->file->open(QIODevice::ReadOnly);
    unsigned short len;
    temp[0].curFile->file->read(reinterpret_cast<char*>(&len), sizeof(len));
    q_rows = len;
    //temp[0].curWid->setRowCount(q_rows);
    temp[0]._resize(q_rows);

    for(int i = 0; i < q_rows; i++){

        temp[0].curFile->file->read(reinterpret_cast<char*>(&temp[0].get_denials(i)),
                sizeof(temp[0].get_denials(i)));
        size_t _BUF_SZ;
        temp[0].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
        char* _BUF = new char[_BUF_SZ];
        temp[0].curFile->file->read(_BUF, _BUF_SZ);
        string g = _BUF;
        temp[0].get_name(i) = QString::fromStdString(g);


        temp[0].curFile->file->read(reinterpret_cast<char*>(&_BUF_SZ), sizeof(_BUF_SZ));
        _BUF = new char[_BUF_SZ];
        temp[0].curFile->file->read(_BUF, _BUF_SZ);
        g = _BUF;
        qDebug() << QString::fromStdString(g);
        temp[0].get_work(i) = QString::fromStdString(g);

        delete[] _BUF;

    }
    qDebug() << _queue[ui->tabWidget->currentIndex()].get_size();
    temp[0].curFile->file->close();


    //_queue[ui->tabWidget->currentIndex()]._resize(temp.size() + _queue[ui->tabWidget->currentIndex()].get_size());
    vector<Queue> c(1);
    c[0] = Queue(0,
            nullptr, _queue[ui->tabWidget->currentIndex()].curWid, 0);
    //c[0]._resize(temp[0].get_size() +_queue[ui->tabWidget->currentIndex()].get_size());
    merge(c, _queue, temp, ui->tabWidget->currentIndex());

    _queue[ui->tabWidget->currentIndex()]._resize(c[0].get_size());
    _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(c[0].get_size());
    for(int i = 0; i < c[0].get_size(); i++){

        _queue[ui->tabWidget->currentIndex()].get_name(i) = c[0].get_name(i);
        _queue[ui->tabWidget->currentIndex()].get_work(i) = c[0].get_work(i);

    }

    for(int i = 0; i < c[0].get_size(); i++){

        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 0, name);

        QTableWidgetItem *work = new QTableWidgetItem;
        work->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 1, work);

    }



    //_queue[ui->tabWidget->currentIndex()].curFile->file->close();
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = true;

}

void MainWindow::on_read_triggered(){

    QString text = QInputDialog::getText(this, tr("Извлечь во роду деятельности"),
                            tr("Работа:"), QLineEdit::Normal,
                            "", new bool());

    for(int i = 0; i < _queue[ui->tabWidget->currentIndex()].get_size(); i++){

        if(text == _queue[ui->tabWidget->currentIndex()].get_work(i)){

            _queue[ui->tabWidget->currentIndex()]._erase(i);
            i -= 1;
            qDebug() << i;

        }

    }

    _queue[ui->tabWidget->currentIndex()].curWid->clear();

    _queue[ui->tabWidget->currentIndex()].curWid->setRowCount(_queue[ui->tabWidget->currentIndex()].get_size());

    for(auto i = 0; i < _queue[ui->tabWidget->currentIndex()].get_size(); i++){

        QTableWidgetItem *name = new QTableWidgetItem;
        name->setText(_queue[ui->tabWidget->currentIndex()].get_name(i));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 0, name);

        QTableWidgetItem *work = new QTableWidgetItem;
        work->setText(_queue[ui->tabWidget->currentIndex()].get_work(i));
        _queue[ui->tabWidget->currentIndex()].curWid->setItem(i, 1, work);

    }
    _queue[ui->tabWidget->currentIndex()].curFile->isChanged = true;

}
