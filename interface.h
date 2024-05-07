#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include "hexcalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QWidget
{
    Q_OBJECT
    bool check;
    HexCalculator calc;
    void SetMemoryBtns();

    Ui::Interface *ui;

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

private slots:
    void PressNum();
    void PressSign();
    void DelOne();
    void DelAll();
    void PressEqual();
    void ToDec();
    void MemoryBtns();
};
#endif // INTERFACE_H
