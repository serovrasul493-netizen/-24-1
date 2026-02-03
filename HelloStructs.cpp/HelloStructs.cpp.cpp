#include <string>
#include <Windows.h>
#include <iostream>

using namespace std;

class Person
{
public:
    const static inline unsigned int MAX_AGE = 120;
    string name;
    unsigned int age;
    unsigned int* agePointer;

    void PrintInfo() const;

    explicit Person(string _name, int _age, string _passportData)
    {
        if (_name == "Платон")
        {
            cout << "Неподходящие имя!" << endl;
            name = "Безымянный";
        }
        else name = _name;

        if (_age > MAX_AGE) age = MAX_AGE;
        else if (_age < 0) age = 0;
        else age = _age;

        agePointer = &age;
        passportData = _passportData;
        counter++;
    }

    // Конструктор копирования заменяет копирование по умолчанию
    Person(Person& other)
    {
        name = other.name;
        age = other.age;
        agePointer = &age;
        passportData = other.passportData;
        educationLevel = other.educationLevel;
    }

    void SetPassportData(string _passportData)
    {
        passportData = _passportData;
    }

    void SetEducation(string _educationLevel)
    {
        educationLevel = _educationLevel;
    }

    string GetPassportData() const
    {
        return passportData;
    }

    static void GetCounter()
    {
        cout << counter << endl;
    }
    static inline unsigned int counter;

    // 4. Оператор декремента (префиксный - уже реализован)
    Person& operator--()
    {
        if (age > 0) age--;
        return *this;
    }

    // 4. Оператор декремента (постфиксный - нужно добавить)
    Person operator--(int)
    {
        Person temp = *this;
        if (age > 0) age--;
        return temp;
    }

    // Перегрузка оператора вычитания с возвращением нового объекта через конструктор
    Person operator-(const Person& other) const
    {
        int temp = age - other.age;
        if (temp <= 0) temp = 0;
        return Person{ name, temp, passportData };
    }

    // 3. Оператор сложения с одним параметром (добавляем)
    // Этот оператор складывает возраст текущего объекта с возрастом другого объекта
    Person operator+(const Person& other) const
    {
        unsigned int newAge = age + other.age;
        if (newAge > MAX_AGE) newAge = MAX_AGE;
        return Person(name, newAge, passportData);
    }

    // Другой вариант оператора сложения с целым числом (у вас уже есть)
    int operator+(int value) const
    {
        return age + value;
    }

    // 1. Оператор '!=', сравнивающий все переменные объектов Person (добавляем)
    bool operator!=(const Person& other) const
    {
        // Используем уже реализованный оператор ==
        return !(*this == other);
    }

    // 2. Оператор '<', сравнивающий только возраст (добавляем)
    bool operator<(const Person& other) const
    {
        return age < other.age;
    }

    // Логические операторы
    bool operator==(const Person& other) const
    {
        if (name == other.name && age == other.age && passportData == other.passportData)
        {
            return true;
        }
        else return false;
    }

    bool operator>(const Person& other) const
    {
        return age > other.age;
    }

protected:
    string passportData;
    string educationLevel;
};

// Бинарный оператор с двумя параметрами перегружается вне класса
// Этот вариант можно оставить как альтернативу
Person operator+(const Person& person1, const Person& person2)
{
    int temp = person1.age + person2.age;
    if (temp <= 0) temp = 0;
    if (temp > Person::MAX_AGE) temp = Person::MAX_AGE;
    return Person{ person1.name, temp, person1.GetPassportData() };
}

// операторы потока не относятся к классу
ostream& operator<<(ostream& stream, const Person& person)
{
    stream << "Имя: " << person.name << ". Возраст: " << *person.agePointer << endl;
    return stream;
}

void Person::PrintInfo() const
{
    cout << "Имя: " << name << ". Возраст: " << *agePointer << endl;
    cout << "Серия и номер паспорта: " << passportData << endl;
}

int main()
{
    setlocale(LC_ALL, "Ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Person chelovek1("Leon", 17, "4444 666666");
    Person chelovek2("Zloy David B myte .", 10, "4444 666666");

    cout << "Информация о людях:" << endl;
    chelovek1.PrintInfo();
    chelovek2.PrintInfo();

    cout << "\nТестирование операторов:" << endl;

    // 1. Тест оператора !=
    cout << "chelovek1 != chelovek2: " << (chelovek1 != chelovek2) << endl;

    // 2. Тест оператора <
    cout << "chelovek1 < chelovek2: " << (chelovek1 < chelovek2) << endl;
    cout << "chelovek2 < chelovek1: " << (chelovek2 < chelovek1) << endl;

    // 3. Тест оператора сложения с одним параметром (внутри класса)
    Person chelovek3 = chelovek1 + chelovek2; // Используем operator+(const Person&)
    cout << "\nСумма возрастов (operator+ внутри класса): ";
    chelovek3.PrintInfo();

    // 3. Тест оператора сложения с целым числом
    cout << "chelovek2 + 7 (возраст): " << (chelovek2 + 7) << endl;

    // 4. Тест оператора декремента
    cout << "\nТест декремента:" << endl;
    cout << "Исходный возраст chelovek1: " << chelovek1.age << endl;

    // Префиксный декремент
    Person temp1 = --chelovek1;
    cout << "После --chelovek1: " << chelovek1.age << endl;

    // Постфиксный декремент
    Person temp2 = chelovek2--;
    cout << "После chelovek2--: " << chelovek2.age << endl;
    cout << "Значение, возвращенное chelovek2--: " << temp2.age << endl;

    // Тест других операторов
    cout << "\nДругие операторы:" << endl;
    cout << "chelovek1 == chelovek2: " << (chelovek1 == chelovek2) << endl;
    cout << "chelovek1 > chelovek2: " << (chelovek1 > chelovek2) << endl;

    // Тест оператора вычитания
    Person chelovek4 = chelovek1 - chelovek2;
    cout << "\nРазность возрастов (chelovek1 - chelovek2): ";
    chelovek4.PrintInfo();

    // Тест внешнего оператора сложения
    Person chelovek5 = chelovek1 + chelovek2;
    cout << "\nСумма возрастов (внешний operator+): ";
    chelovek5.PrintInfo();

    return 0;
}
Краткое описание добавленных операторов :












































































































































































































