#ifndef SAVEORNOT_H
#define SAVEORNOT_H

#include <QDialog>

namespace Ui {
class SaveorNot;
}

class SaveorNot : public QDialog
{
    Q_OBJECT

public:
    explicit SaveorNot(QWidget *parent = nullptr);
    ~SaveorNot();

private:
    Ui::SaveorNot *ui;
};

#endif // SAVEORNOT_H
