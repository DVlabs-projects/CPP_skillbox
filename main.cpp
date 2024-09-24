#include <iostream>
#include <string>
#include <locale>

class Car {
private:
    std::string Trademark;
    int Number_of_cylinders;
    int Power;

    static int count_objects; // Статическая переменная для подсчета объектов

public:
    // Конструктор без параметров
    Car() : Trademark(""), Number_of_cylinders(0), Power(0) {
        count_objects++;
    }

    // Конструктор с параметрами
    Car(const std::string& Mark, int Cylinders, int iPower)
        : Trademark(Mark), Number_of_cylinders(Cylinders), Power(iPower) {
        count_objects++;
    }

    // Конструктор копирования
    Car(const Car& other)
        : Trademark(other.Trademark), Number_of_cylinders(other.Number_of_cylinders), Power(other.Power) {
        count_objects++;
    }

    // Деструктор
    virtual ~Car() {
        count_objects--;
    }

    // Геттеры и сеттеры
    std::string getTrademark() const { return Trademark; }
    void setTrademark(const std::string& Mark) { Trademark = Mark; }

    int getNumber_of_cylinders() const { return Number_of_cylinders; }
    void setNumber_of_cylinders(int Cylinders) { Number_of_cylinders = Cylinders; }

    int getPower() const { return Power; }
    void setPower(int Power) { this->Power = Power; }

    // Перегрузка оператора присваивания
    Car& operator=(const Car& other) {
        if (this != &other) {
            Trademark = other.Trademark;
            Number_of_cylinders = other.Number_of_cylinders;
            Power = other.Power;
        }
        return *this;
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << "Торговая марка: " << car.Trademark << ", Количество цилиндров: " 
           << car.Number_of_cylinders << ", Мощность: " << car.Power;
        return os;
    }

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& is, Car& car) {
        std::cout << "Введите торговую марку: ";
        is >> car.Trademark;
        std::cout << "Введите количество цилиндров: ";
        is >> car.Number_of_cylinders;
        std::cout << "Введите мощность: ";
        is >> car.Power;
        return is;
    }

    // Дружественная функция для подсчета объектов
    friend int count();
};

int Car::count_objects = 0;

// Производный класс Lorry
class Lorry : public Car {
private:
    int Load_capacity;

public:
    // Конструктор без параметров
    Lorry() : Car(), Load_capacity(0) {}

    // Конструктор с параметрами
    Lorry(const std::string& Mark, int Cylinders, int Power, int Load_capacity)
        : Car(Mark, Cylinders, Power), Load_capacity(Load_capacity) {}

    // Конструктор копирования
    Lorry(const Lorry& other)
        : Car(other), Load_capacity(other.Load_capacity) {}

    // Геттеры и сеттеры
    int getLoad_capacity() const { return Load_capacity; }
    void setLoad_capacity(int Load_capacity) { this->Load_capacity = Load_capacity; }

    // Перегрузка оператора присваивания
    Lorry& operator=(const Lorry& other) {
        if (this != &other) {
            Car::operator=(other);
            Load_capacity = other.Load_capacity;
        }
        return *this;
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Lorry& lorry) {
        os << static_cast<const Car&>(lorry)
           << ", грузоподъемность: " << lorry.Load_capacity;
        return os;
    }

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& is, Lorry& lorry) {
        is >> static_cast<Car&>(lorry);
        std::cout << "Введите грузоподъемность: ";
        is >> lorry.Load_capacity;
        return is;
    }
};

// Реализация функции count
int count() {
	return Car::count_objects;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
	Car car1("Toyota", 4, 150);
	Lorry lorry1("Volvo", 6, 400, 10000);

	std::cout << "Car 1: " << car1 << std::endl;
	std::cout << "Lorry 1: " << lorry1 << std::endl;

	std::cout << "Всего создано объектов: " << count() << std::endl;

	Car car2;
	Lorry lorry2;

	std::cin >> car2;
	std::cin >> lorry2;

	std::cout << "Car 2: " << car2 << std::endl;
	std::cout << "Lorry 2: " << lorry2 << std::endl;

	std::cout << "Всего создано объектов: " << count() << std::endl;

	return 0;
}
