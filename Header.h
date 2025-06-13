#pragma once
#include <string>
#include <vector>

using namespace std;

// Класс Stack для реализации стека
class Stack 
{
private:
    struct Node 
    {
        double Data; //Данные в узле
        Node* Next; //Указатель на след. узел
        Node(double val) : Data(val), Next(nullptr) {} //Конструктор узла
    };

    Node* TopNode; //Указатель на вершину стека

public:
    Stack(); //Конструктор стека
    ~Stack(); //Деструктор стека

    void Push(double value);    //Добавление элемента
    double Pop();               //Извлечение элемента
    double Top() const;         //Получение верхнего элемента
    bool IsEmpty() const;       //Проверка на пустоту стека
};

// Класс для вычисления выражений в обратной польской записи
class RPNCalculator 
{
public:
    static double CalculateRPN(const string& Expression);  //Метод вычисления
    static string GenerateRandom(); //Генерация рандомного выражения

    //Функции интерфейса
    static void PrintWelcome();
    static void PrintMenu();
    static string ReadFile();
    static int MenuChoice();

private:
    static vector<string> SplitString(const string& Str);  //Разделение строки на токены
    static bool Operator(const string& Token);       //Проверка, является ли токен оператором
    static double Calculate(double a, double b, const string& op);  //Выполнение операции
    static bool ValidNumber(const string& Token);  //Проверка вводимого выражения
};
