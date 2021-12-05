# Трассировка лучей на С++

*Курсовая работа по трассировке лучей*

*Адиятуллин Инсаф 09-912*

## Элементы сцены:
- Физические объекты
- Точечные источники света
- Камеры 

### Физические объекты

Все физические объекты наследуются от абстрактного базового класса Object,
который имеет интерфейс для работы с пересечениями, трансформациями и со светом.
Для этого в классе реализованы следующие методы:
- getIntersectionWith(Ray):

    Метод находит пересечение луча с объектом.

    Принимает в качестве параметра Луч, применяет к ней обратную матрицу своей
    трасформации и вызывает метод пересечения, который реализуется в каждом наследуемом 
    классе необходимым способом.

    Возвращает вещественное число - коэффициент, на который нужно умножить вектор направления луча; 
    если пересечения нет, то возвращает -1.  

- applyTransform(mat4x4)

    Метод применяет к объекту матрицу трансформации.
    
    Принимает в аргумента матрицу размерности 4х4.

- getPhongColor(Ray, Light)
    
    Метод находит цвет в точке пересечения по модели фонга.

    Принимает в качестве аргумента Луч и Точечный источник света

    Возвращает трехмерный вектор.

**Основные физические объекты**
- Сфера
- Куб
- Плоскость
- Треугольник
- Цилиндр

### Точечные источники света

Точечный источник света - это небольшая структура, состоящая из следующих полей:
- точка начала распростанения
- цвет