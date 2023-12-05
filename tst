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
bool serializeString(std::ostream& os, const std::array<char, 20>& str)
{
    bool hasComma = false;
    for(char ch : str)
        if(ch == ','){
            hasComma = true;
            break;
        }
    if(hasComma){
        return false;
    }
    else
    {
        os.write(str.data(), str.size());
    }
    return true;
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
bool serializeObject(std::ostream& os, const Person& person)
{
    {
        bool isSuccess = serializeString(os, person.name);
        if (!isSuccess)
        {
            return false;
        }
    }
    os << ",";
    serializeInteger(os, person.age);
    os << ",";
    serializeGender(os, person.gender);
    return true;
}

// Функция для десериализации строки
bool deserializeString(std::istream& is, std::array<char, 20>& str)
{
    is.get(str.data(), str.size(), ',');
    return is.get() == ',';
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
    decltype(Person::name) name{"John"};
    std::vector persons{
        {Person{name, 25, Gender::Male}, Person{{"Alice"}, 30, Gender::Female}} };
    serializeVector(outFile, persons);
    outFile.close();

    std::ifstream inFile("persons.csv");
    std::vector<Person> loadedPersons = deserializeVector(inFile);
    inFile.close();

    // Вывод загруженных объектов
    // for (const auto& person : loadedPersons)
    // {
    //     std::cout << "Name: " << person.name.data() << ", Age: " << person.age
    //         << ", Gender: " << static_cast<int>(person.gender) << std::endl;
    // }

     //Вывод загруженных объектов
    // for (const auto& person{loadedPersons.begin()}; person != loadedPersons.end(); ++person)
    // {
    //     std::cout << "Name: " << person->name.data() << ", Age: " << person->age
    //         << ", Gender: " << static_cast<int>(person->gender) << std::endl;
    // }

    for (size_t i = 0; i < loadedPersons.size(); ++i)
    {
        const Person& person = loadedPersons[i];
        std::cout << "Name: " << person.name.data() << ", Age: " << person.age
            << ", Gender: " << static_cast<int>(person.gender) << std::endl;
    }

    // const auto& person { loadedPersons};
    // person +=1;
    // std::cout << "Name: " << person.name.data() << std::endl;
    // person +=2;
    // std::cout << ", Age: " << person.age << std::endl;
    // person +=3;
    // std::cout << ", Gender: " << static_cast<int>(person.gender) << std::endl;
    

            
    return 0;
}
