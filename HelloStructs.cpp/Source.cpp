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

    Person& operator--()
    {
        *agePointer -= 1;
        return *this;
    }

    // Перегрузка оператора вычитания с возвращением нового объекта через конструктор
    // Бинарный оператор с одним параметром
    Person operator-(const Person& other) const
    {
        int temp = age - other.age;
        if (temp <= 0) temp = 0;
        return Person{ name, temp, passportData };
    }

    // При перегрузке операторов не обязательно возвращать объект класса. Это может быть любой объект в зависимости от ситуации.
    int operator+(int value)
    {
        return age + value;
    }

    // Логические операторы
    bool operator==(const Person& other) const // на дз почему можно вызвать приватный passportData
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

// Бинарный оператор с двумя параметрами перегружается вне класса, поскольку принимает два независимых объекта
Person operator+(const Person& person1, const Person& person2)
{
    int temp = person1.age + person2.age;
    if (temp <= 0) temp = 0;
    return Person{ person1.name, temp, person1.GetPassportData() };
}

// операторы потока не относятся к классу, поэтому должны быть переопределены вне его.
ostream& operator<<(ostream& stream, const Person& person)
{
    stream << "Имя: " << person.name << ". Возраст: " << *person.agePointer << endl; return stream;
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
    chelovek1.PrintInfo();
    chelovek2.PrintInfo();
    //cout << chelovek1 - chelovek2;
    //cout << chelovek1 + chelovek2;
    cout << chelovek2 + 7;
    chelovek2.PrintInfo();

    cout << (chelovek1 == chelovek2);
    cout << (chelovek1 > chelovek2);
}