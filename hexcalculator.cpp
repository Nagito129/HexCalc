#include "hexcalculator.h"

HexCalculator::HexCalculator(){

}

// Функция для преобразования шестнадцатеричной строки в десятичное число
long long HexCalculator::HexToDecimal(const string& hexStr) {
    stringstream ss;
    ss << hex << hexStr;
    unsigned long long decimalValue;
    ss >> decimalValue;
    return decimalValue;
}
QString HexCalculator::HexToDecimal (QString input){
    string hexStr = input.toStdString();
    stringstream ss;
    ss << hex << hexStr;
    long long decimalValue;
    ss >> decimalValue;
    return QString::number(decimalValue);
}

// Функция для преобразования десятичного числа в шестнадцатеричную строку
string HexCalculator::DecimalToHex(long long decimalValue) {
    stringstream ss;
    ss << hex << uppercase << decimalValue;
    return ss.str();
}

// Функция для выполнения арифметических операций
QString HexCalculator::PerformOperation(QString input) {
    string arg1, arg2;
    char op;
    QString num;
    int count = 0;
    if (input[0] == '-'){
        num += input [0];
        input.remove(0, 1);
    }
    while(input[count] != '+' && input[count] != '-' && input[count] != '*' && input[count] != '/' && input[count] != '=')
        num += input[count++];
    arg1 = num.toStdString();
    input.remove(0, count);
    if(input.length() == 1) return num;
    op = input[0].toLatin1();
    input.remove(0, 1);
    num = "";
    count = 0;
    while(input[count] != '+' && input[count] != '-' && input[count] != '*' && input[count] != '/' && input[count] != '=')
        num += input[count++];
    arg2 = num.toStdString();
    input.remove(0, count);
    long long operand1 = HexToDecimal(arg1);
    long long operand2 = HexToDecimal(arg2);
    long long result = 0;

    // Выполнение операции в зависимости от переданного оператора, хз как тут надо, если честно
    switch(op){
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        if (operand2 != 0)
            result = operand1 / operand2;
        else
            return "Ошибочка";
        break;
    }

    // Преобразование результата в шестнадцатеричную строку и сохранение в памяти
    QString resultHex = QString::fromStdString(DecimalToHex(result));
    return resultHex;
}
