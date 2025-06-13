#include "Header.h"
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

//Конструктор стека
Stack::Stack() : TopNode(nullptr) {}

//Деструктор
Stack::~Stack() 
{
    while (!IsEmpty()) 
    {
        Pop();
    }
}

//Добавляет элементы в стек
void Stack::Push(double value) 
{
    Node* NewNode = new Node(value);
    NewNode->Next = TopNode;
    TopNode = NewNode;
}

//Извлекает элементы из стека
double Stack::Pop() 
{
    if (IsEmpty()) 
    {
        throw runtime_error("Ошибка: попытка извлечь элемент из пустого стека");
    }

    Node* Temp = TopNode;
    double value = Temp->Data;
    TopNode = TopNode->Next;
    delete Temp;
    return value;
}

//Смотрит верхний элемент
double Stack::Top() const
{
    if (IsEmpty()) 
    {
        throw runtime_error("Ошибка: стек пуст");
    }
    return TopNode->Data;
}

//Проверяет, пуст ли стек
bool Stack::IsEmpty() const
{
    return TopNode == nullptr;
}

//Реализация методов класса RPNCalculator
//Разделяет строки на токены
vector<string> RPNCalculator::SplitString(const string& str)
{
    vector<string> Tokens;
    string Token;
    istringstream TokenStream(str);

    while (TokenStream >> Token)
    {
        Tokens.push_back(Token);
    }

    return Tokens;
}

//Проверяет, является ли токен оператором
bool RPNCalculator::Operator(const string& Token)
{
    return Token == "+" || Token == "-" || Token == "*" || Token == "/";
}

//Выполнение операций
double RPNCalculator::Calculate(double a, double b, const string& op)
{
    if (op == "+") return b + a;
    if (op == "-") return b - a;
    if (op == "*") return b * a;
    if (op == "/") {
        if (a == 0) throw runtime_error("Ошибка: деление на ноль");
        return b / a;
    }
    throw runtime_error("Ошибка: неизвестный оператор '" + op + "'");
}

//Вычисляет выражения в обратной польской записи
double RPNCalculator::CalculateRPN(const string& Expression)
{
    Stack Stack;
    vector<string> Tokens = SplitString(Expression);

    for (const auto& Token : Tokens) //Проходит по каждому токену
    {
        if (Operator(Token)) //Если токен - оператор
        {
            if (Stack.IsEmpty()) throw runtime_error("Ошибка: недостаточно операндов для оператора '" + Token + "'");
            double a = Stack.Pop(); //Извлекаем первый операнд

            if (Stack.IsEmpty()) throw runtime_error("Ошибка: недостаточно операндов для оператора '" + Token + "'");
            double b = Stack.Pop(); //Извлекаем второй операнд

            double result = Calculate(a, b, Token); //Выполняем операцию
            Stack.Push(result); //Результат операции кладем в стек
        }
        else
        {
            //Заменяем "," на "." для корректной работы
            string NormalizedToken = Token;

            for (size_t i = 0; i < NormalizedToken.length(); ++i)
            {
                if (NormalizedToken[i] == '.')
                {
                    NormalizedToken[i] = ',';
                }
            }

            if (!ValidNumber(NormalizedToken)) {
                throw runtime_error("Ошибка: недопустимый числовой формат '" + Token + "'");
            }

            //Преобразование строки в число
            char* EndPtr;
            double num = strtod(NormalizedToken.c_str(), &EndPtr);

            if (*EndPtr != '\0')
            {
                throw runtime_error("Ошибка: не удалось преобразовать число '" + Token + "'");
            }

            Stack.Push(num);
        }
    }

    if (Stack.IsEmpty()) throw runtime_error("Ошибка: выражение не содержит результата");
    double Result = Stack.Pop();

    if (!Stack.IsEmpty())
    {
        throw runtime_error("Ошибка: в стеке остались лишние операнды");
    }

    return Result;
}

//Проверяет корректность вводимого числа
bool RPNCalculator::ValidNumber(const string& Token)
{
    if (Token.empty()) return false;
    bool HasDecimal = false;

    //Проверяет каждый символ на цифры и наличие запятой
    for (char c : Token)
    {
        if (c == ',')
        {
            if (HasDecimal) return false;
            HasDecimal = true;
        }
        else if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

//Получает выбор из меню + проверка на корректность числа
int RPNCalculator::MenuChoice()
{
    string input;
    getline(cin, input);
    input.erase(0, input.find_first_not_of(" \t\r\n"));
    input.erase(input.find_last_not_of(" \t\r\n") + 1);

    if (input.empty() || input.find_first_not_of("0123456789") != string::npos)
    {
        cout << "\nОшибка: введите целое число (0, 1, 2 или 3)\n";
        return -1;
    }

    int choice = stoi(input);
    return choice;
}

//Выводит приветственное сообщение
void RPNCalculator::PrintWelcome()
{
    cout << "============================================\n";
    cout << "КАЛЬКУЛЯТОР ОБРАТНОЙ ПОЛЬСКОЙ ЗАПИСИ\n";
    cout << "============================================\n";
    cout << "Доступные операции: +, -, *, /\n";
    cout << "Пример ввода: 5 3 2 * + 7 /\n";
    cout << "Это соответствует выражению: (5 + (3 * 2)) / 7\n";
    cout << "============================================\n\n";
}

//Функция для вывода меню
void RPNCalculator::PrintMenu() 
{
    cout << "\nМЕНЮ:\n";
    cout << "1. Ввести выражение с клавиатуры\n";
    cout << "2. Прочитать выражение из файла\n";
    cout << "3. Сгенерировать случайное выражение\n";
    cout << "0. Выход\n";
    cout << "Выберите вариант: ";
}

//Функция для чтения выражения из файла + проверка на корректность выражения
string RPNCalculator::ReadFile()
{
    const string filename = "IKM2.txt";
    ifstream file(filename);

    if (!file.is_open()) 
    {
        throw runtime_error("Не удалось открыть файл " + filename);
    }

    string Expression;
    getline(file, Expression);
    file.close();

    if (Expression.empty())
    {
        throw runtime_error("Файл " + filename + " пуст");
    }

    for (char c : Expression)
    {
        if (!isdigit(c) && c != '.' && c != '+' && c != '-' && c != '*' && c != '/' && !isspace(c)) {
            throw runtime_error("Файл содержит недопустимые символы: '" + string(1, c) + "'");
        }
    }

    return Expression;
}

//Генерация случайного выражения в обратной польской записи
string RPNCalculator::GenerateRandom()
{
    const int MaxLength = 10;
    string Expression;
    string ops[] = { "+", "-", "*", "/" };
    int OperandCount = 0;
    srand(time(nullptr));

    for (int i = 0; i < MaxLength; ++i)
    {
        bool addOperand = OperandCount < 2 || rand() % 2 == 0;

        if (addOperand)
        {
            int whole = rand() % 20 + 1;
            int decimal = rand() % 10;
            string num = to_string(whole) + "," + to_string(decimal);
            Expression += num + " ";
            OperandCount++;
        }
        else 
        {
            string op = ops[rand() % 4];
            Expression += op + " ";
            OperandCount--;
        }
    }

    while (OperandCount > 1) 
    {
        string op = ops[rand() % 4];
        Expression += op + " ";
        OperandCount--;
    }

    return Expression;
}
