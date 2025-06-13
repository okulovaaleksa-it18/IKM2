#include "Header.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
    setlocale(LC_ALL, "Russian");
    RPNCalculator::PrintWelcome();//Выводит приветственное сообщения
    int Choice;

    do 
    {
        RPNCalculator::PrintMenu();//Выводит меню выбора
        Choice = RPNCalculator::MenuChoice();
        if (Choice == -1) continue;

        try 
        {
            switch (Choice) 
            {
            case 1: //Ввод выражения с консоли
            {
                string Expression;
                cout << "\nВведите выражение в обратной польской записи: ";
                getline(cin, Expression);

                if (Expression.empty()) 
                {
                    cout << "Ошибка: введена пустая строка\n";
                    break;
                }

                double result = RPNCalculator::CalculateRPN(Expression);
                cout << "\nРезультат: " << result << endl;
                break;
            }
            case 2: //Чтение выражения из файла
            {
                try 
                {
                    string Expression = RPNCalculator::ReadFile();
                    cout << "\nПрочитано из файла: " << Expression << endl;
                    double result = RPNCalculator::CalculateRPN(Expression);
                    cout << "Результат: " << result << endl;
                }
                catch (const exception& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }
            case 3: //Генерация случайного выражения
            {
                string Generated = RPNCalculator::GenerateRandom();
                cout << "\nСгенерированное выражение: " << Generated << endl;

                try 
                {
                    double Result = RPNCalculator::CalculateRPN(Generated);
                    cout << "Результат: " << Result << endl;
                }
                catch (const exception& e) 
                {
                    cout << e.what() << endl;
                }
                break;
            }
            case 0:
                cout << "\nВыход из программы...\n";
                break;
            default:
                cout << "\nНеверный выбор. Попробуйте снова.\n";
            }
        }
        catch (const exception& e) 
        {
            cout << e.what() << endl;
        }
    } while (Choice != 0); //Цикл продолжается до того момента, как не будет введен 0 в меню

    return 0;
}
