// 1. Оператор '!=', сравнивающий все переменные объектов Person
bool operator!=(const Person& other) const
{
    // Используем уже реализованный оператор == и инвертируем результат
    return !(*this == other);
}

// 2. Оператор '<', сравнивающий только возраст
bool operator<(const Person& other) const
{
    return age < other.age;
}

// 3. Оператор сложения с одним параметром, складывающий 'age'
// У вас уже есть бинарный оператор + с двумя параметрами вне класса,
// но если нужно именно с одним параметром внутри класса:
Person operator+(unsigned int years) const
{
    unsigned int newAge = age + years;
    if (newAge > MAX_AGE) newAge = MAX_AGE;
    return Person(name, newAge, passportData);
}

// 4. Оператор декремента (вычитание из возраста)
// У вас уже есть префиксный декремент operator--()
// Добавим постфиксный декремент
Person operator--(int)  // int - фиктивный параметр для отличия от префиксного
{
    Person temp = *this;  // Сохраняем текущее состояние
    if (age > 0) age--;  // Уменьшаем возраст текущего объекта
    return temp;  // Возвращаем старое состояние
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

        // 4. Оператор декремента (префиксный)
        Person& operator--()
        {
            if (age > 0) age--;
            return *this;
        }

        // 4. Оператор декремента (постфиксный)
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

        // 3. Оператор сложения с одним параметром
        Person operator+(unsigned int years) const
        {
            unsigned int newAge = age + years;
            if (newAge > MAX_AGE) newAge = MAX_AGE;
            return Person(name, newAge, passportData);
        }

        // При перегрузке операторов не обязательно возвращать объект класса
        int operator+(int value) const
        {
            return age + value;
        }

        // 1. Оператор '!='
        bool operator!=(const Person& other) const
        {
            return !(*this == other);
        }

        // 2. Оператор '<'
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
    bool operator<=(const Person& other) const
    {
        return age <= other.age;
    }

    bool operator>=(const Person& other) const
    {
        return age >= other.age;
    }