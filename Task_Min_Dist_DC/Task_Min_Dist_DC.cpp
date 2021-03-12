#include <iostream>
#include <cmath>
using namespace std;

class Point
{
public:
    int x, y;
};

int compareX(const void* a, const void* b)
{
    Point* p1 = (Point*)a, *p2 = (Point*)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
    Point* p1 = (Point*)a, *p2 = (Point*)b;
    return (p1->y - p2->y);
}

double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Метод грубой силы, чтобы вернуть наименьшее расстояние между двумя точками
// в P [] размера n

double bruteForce(Point P[], int n)
{
    double min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}
// Утилита для поиска минимум двух значений с плавающей запятой
double min(double x, double y)
{
    return (x < y) ? x : y;
}
// Полезная функция для определения расстояния между ближайшими точками
// полоса заданного размера. Все точки в полосе [] отсортированы по
// координата у. Все они имеют верхнюю границу минимального расстояния как d.
// Обратите внимание, что этот метод выглядит как метод O (n ^ 2), но это O (n)
// метод, поскольку внутренний цикл выполняется не более 6 раз

double stripClosest(Point strip[], int size, double d)
{
    double min = d;  // Инициализируем минимальное расстояние как d
    // Собираем все точки по одной и пробуем следующие до разницы
    // между координатами y меньше, чем d.
    // Это доказанный факт, что этот цикл выполняется не более 6 раз
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y) - strip[i].y < min; ++j)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);
    return min;
}

// Рекурсивная функция для наименьшего расстояния. Массив Px содержит
// все точки отсортированы по x координатам, а Py содержит все точки
// отсортировано по координатам y

double closestUtil(Point Px[], Point Py[], int n)
{
    // Если есть 2 или 3 очка, то используйте грубую силу
    if (n <= 3)
        return bruteForce(Px, n);
    // Найти среднюю точку
    int mid = n / 2;
    Point midPoint = Px[mid];
    // Делим точки в отсортированном по y массиве вокруг вертикальной линии.
    // Предположение: все координаты х различны.
    Point* Pyl = new Point[mid + 1];   // y отсортированные точки слева от вертикальной линии
    Point* Pyr = new Point[n - mid - 1];  // y отсортированные точки справа от вертикальной линии
    int li = 0, ri = 0;  // индексы левого и правого подмассивов
    for (int i = 0; i < n; i++)
    {
        if (Py[i].x <= midPoint.x)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }
    // Рассмотрим вертикальную линию, проходящую через среднюю точку
    // вычисляем наименьшее расстояние dl слева от средней точки и
    // доктор на правой стороне
    double dl = closestUtil(Px, Pyl, mid);
    double dr = closestUtil(Px + mid, Pyr, n - mid);
    // Находим меньшее из двух расстояний
    double d = min(dl, dr);
    // Построить массив полос [], который содержит точки близко (ближе, чем d)
    // к линии, проходящей через среднюю точку
    Point* strip = new Point[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)

            strip[j] = Py[i], j++;
    // Находим ближайшие точки в полосе. Вернуть минимум d и ближайший
    // расстояние - полоса []
    return min(d, stripClosest(strip, j, d));
}

double closest(Point P[], int n)
{
    Point* Px = new Point[n];
    Point* Py = new Point[n];
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }
    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);
    return closestUtil(Px, Py, n);
}

int main()
{
    Point P[] {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(P) / sizeof(P[0]);
    cout << "The smallest distance is " << closest(P, n) << endl;
    return 0;
}