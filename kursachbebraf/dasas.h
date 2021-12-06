#ifndef DASAS_H
#define DASAS_H

#include <QDialog>

namespace Ui {
class dASas;
}

class dASas : public QDialog
{
    Q_OBJECT

public:
    explicit dASas(QWidget *parent = nullptr);
    ~dASas();

private:
    Ui::dASas *ui;
};

#endif // DASAS_H
