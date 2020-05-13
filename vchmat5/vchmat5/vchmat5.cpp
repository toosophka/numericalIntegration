
#include <iostream>
#include <math.h>

using namespace std;

//заданная функция
double function(double x)
{
    return (1 + sqrt(x)) / (1 + 4 * x + 3 * pow(x, 2));
}

//метод средних прямоугольников
double averageRect(double a, double b, int n)
{
    double h = (b - a) / n;
    double answ=0;
    double* x = new double[n + 1];
    int m = 0;

    for (int i = 0; i < n + 1; i++)
        x[i] = a+h*i;

    for (int i = 0; i < n; i++)
        answ += h * function((x[i] + x[i + 1]) / 2);

    return answ;
}

//метод левых прямоугольников
double leftRect(double a, double b, int n)
{
    double h = (b - a) / n;
    double answ = 0;
    double* x = new double[n + 1];
    int m = 0;

    for (int i = 0; i < n + 1; i++)
        x[i] = a + h * i;

    for (int i = 0; i < n; i++)
        answ += h * function(x[i]);

    return answ;
}

//метод Ньютона-Котеса 4го порядка
double newtonCotes(double a, double b,int n)
{
    double c0 = (double)2 / 45;
    int w[5] = { 7,32,12,32,7 };
    double h = (b - a) / n;
    double answ = 0;
    double* x = new double[n + 1];

    for (int i = 0; i < n + 1; i++)
        x[i] = a + h * i;

    for (int j = 0; j < n; j += 4)
        for (int i = 0; i < 5; i++)
                answ += w[i] * function(x[j] + 4 * h * i);
    return c0*h*answ;
}

//интегрирование выбранным методом с заданной точностью
double integration(double a, double b, double eps)
{
    int m = 0, var, m1 = 1;
    double answ;

    cout << "Укажите метод:" << endl;
    cout<< "1 - Метод средних прямоугольников" << endl << "2 - Метод левых прямоугольников" << endl << "3 - Метод Ньютона-Котеса 4го порядка" << endl;
    cin >> var;
    switch (var)
    {
    case(1):
        while (abs(averageRect(a, b, pow(2, m)) - averageRect(a, b, pow(2, m + 1))) >= eps)
            m++;
        answ = averageRect(a, b, pow(2, m + 1));
        cout << "Шаг интегрирования:  "<<(b-a)/ pow(2, m + 1)<<endl;
        break;
    case(2):
        while (abs(leftRect(a, b, pow(2, m)) - leftRect(a, b, pow(2, m + 1))) >= eps)
            m++;
        answ = leftRect(a, b, pow(2, m + 1));
        cout << "Шаг интегрирования:  " << (b - a) / pow(2, m + 1)<< endl;
        break;
    case(3):
        while (abs(newtonCotes(a, b, pow(4, m1)) - newtonCotes(a, b, pow(4, m1 + 1))) >= eps)
            m1++;
        answ = newtonCotes(a, b, pow(4,m1 + 1));
        cout << "Шаг интегрирования:  " << (b - a) / pow(4, m1 + 1) << endl;
        break;
    }
    return answ;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    double a, b, eps;
    int act;
    while (1)
    {
        cout << endl << "Введите границы интервала:" << endl;
        cin >> a >> b;
        //если пользователь случайно введет сначала правую границу, потом левую границу интервала
        if (a > b)
        {
            double temp = a;
            a = b;
            b = temp;
        }
        while (1)
        {
            cout << "Введите точность интегрирования:" << endl;
            cin >> eps;
            cout << "Значение интеграла:  "<<integration(a, b, eps) << endl;
            cout << "1 - продолжить работу с этим интервалом" << endl <<"2 - продолжить работу с новым интервалом"<<endl<< "0 - выйти" << endl;
            cin >> act;
            if (act == 1)
                continue;
            else
                break;
        }
        if (act == 0)
            break;
    }
}


