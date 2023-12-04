#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <sstream>

enum class Gender
{
    Male,
    Female
};

struct Person
{
    std::array<char, 20> name;
    int age;
    Gender gender;
};

// Функция для сериализации строки
void serializeString(std::ostream& os, const std::array<char, 20>& str)
{
    os.write(str.data(), str.size());
}

// Функция для сериализации целого числа
void serializeInteger(std::ostream& os, int intValue)
{
    os << intValue;
}

// Функция для сериализации поля enum class Gender
void serializeGender(std::ostream& os, Gender gender)
{
    switch (gender)
    {
    case Gender::Male:
        os << "M";
        break;
    case Gender::Female:
        os << "F";
        break;
    }
}

// Функция для сериализации объекта Person в CSV формат
void serializeObject(std::ostream& os, const Person& person)
{
    serializeString(os, person.name);
    os << ",";
    serializeInteger(os, person.age);
    os << ",";
    serializeGender(os, person.gender);
}

// Функция для десериализации строки
void deserializeString(std::istream& is, std::array<char, 20>& str)
{
    is.read(str.data(), str.size());
    str[str.size() - 1] = '\0'; // Установим нулевой символ в конце строки
}

// Функция для десериализации целого числа
int deserializeInteger(std::istream& is)
{
    std::string token;
    std::getline(is, token, ',');
    try
    {
        return std::stoi(token);
    }
    catch (const std::invalid_argument&)
    {
        // Обработка ошибки (можно заменить на другое значение, например, -1)
        return 0;
    }
}

// Функция для десериализации поля enum class Gender
Gender deserializeGender(std::istream& is)
{
    std::string token;
    std::getline(is, token, ',');
    if (token == "M")
        return Gender::Male;
    else if (token == "F")
        return Gender::Female;
    // Можно добавить обработку ошибки, например, бросить исключение
    return Gender::Male; // По умолчанию
}

// Функция для десериализации объекта Person из строки CSV
Person deserializeObject(std::istream& is)
{
    Person result;
    deserializeString(is, result.name);
    result.age = deserializeInteger(is);
    result.gender = deserializeGender(is);
    return result;
}

// Функция для сериализации std::vector из объектов Person в std::ostream
void serializeVector(std::ostream& os, const std::vector<Person>& persons)
{
    for (const auto& person : persons)
    {
        serializeObject(os, person);
        os << "\n"; // Разделитель объектов
    }
}

// Функция для десериализации std::vector из строк CSV в std::istream
std::vector<Person> deserializeVector(std::istream& is)
{
    std::vector<Person> persons;
    std::string line;
    while (std::getline(is, line))
    {
        std::istringstream iss(line);
        persons.push_back(deserializeObject(iss));
    }
    return persons;
}

int main()
{
    // Пример использования
    std::ofstream outFile("persons.csv");
    std::vector<Person> persons{
        {{"John", 25, Gender::Male}, {"Alice", 30, Gender::Female}} };
    serializeVector(outFile, persons);
    outFile.close();

    std::ifstream inFile("persons.csv");
    std::vector<Person> loadedPersons = deserializeVector(inFile);
    inFile.close();

    // Вывод загруженных объектов
    for (const auto& person : loadedPersons)
    {
        std::cout << "Name: " << person.name.data() << ", Age: " << person.age
            << ", Gender: " << static_cast<int>(person.gender) << std::endl;
    }
    return 0;
}
