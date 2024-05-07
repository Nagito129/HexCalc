#ifndef HEXCALCULATOR_H
#define HEXCALCULATOR_H

#include <sstream>
#include <QString>
using namespace std;

// Класс для представления числа
class HexCalculator {
private:
    long long HexToDecimal (const string&);
    string DecimalToHex (long long);
public:
    HexCalculator();
    QString HexToDecimal (QString);
    QString PerformOperation(QString);
};
#endif // HEXCALCULATOR_H
