

#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <string>


class Phone
{
public:
    Phone(std::string& number, std::string& date, bool& blocker, std::string& lastNameAbon) : number(number), date(date), blocker(blocker), lastNameAbon(lastNameAbon) {}

    std::string getLastNameAbon() const
    {
        return lastNameAbon;
    }

    // приводит данные в нормальный вид для последующей записи в файл
    std::string infoString() const
    {
        return "Фамилия абонента: " + lastNameAbon + "\nНомер: " + number + "\nДата установки: " + date +
            "\nНаличие блокиратора: " + (blocker ? "Имееется" : "Не имеется");
    }

private:
    std::string number;
    std::string date;
    bool blocker;
    std::string lastNameAbon;


};

// функция для записи в файл
void SaveToFile(const std::vector<Phone>& phones)
{
    std::ofstream file;
    file.open("phones.txt");
    for (const auto& phone : phones)
    {
        file << phone.infoString() << "\n\n";
    }
    file.close();

}
bool sort_A_Z(const Phone& a, const Phone& b)
{
    return a.getLastNameAbon() < b.getLastNameAbon();
}
bool sort_Z_A(const Phone& a, const Phone& b)
{
    return a.getLastNameAbon() > b.getLastNameAbon();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::vector<Phone> phones;
    
    while (true)
    {
        // переменная для выбора
        int choice;
        // переменные для записи данных
        std::string number;
        std::string date;
        bool blocker = 0;
        std::string lastNameAbon;


        std::cout << "Введите номер телефона: "; std::cin.ignore(); std::cin.clear(); std::getline(std::cin, number);
        std::cout << "Введите дату установки: "; std::cin.ignore(); std::cin.clear(); std::getline(std::cin, date);
        std::cout << "Введите 1 - Если есть блокиратор, нет - любую цифру: "; std::cin >> choice;
        if (choice == 1)
            blocker = 1;
        std::cout << "Введите фамилию абонента: "; std::cin.ignore(); std::cin.clear(); std::getline(std::cin, lastNameAbon);
        phones.emplace_back(number, date, blocker, lastNameAbon);
        std::cout << "Хотите добавить еще одну запись? 1-ДА, 2-НЕТ(ЗАПИСЬ В ФАЙЛ С СОРТИРОВКОЙ): "; std::cin >> choice;
        if (choice == 1)
        {
            std::cout << std::endl;
        }
        else if (choice == 2)
        {
            std::cout << "Какую сортировку вы хотите выбрать? 1 - По возврастанию, 2 - По убыванию: "; std::cin >> choice;
            if (choice == 1)
            {
                // сортирует от А-Я, A-Z по полю фамилии
                std::sort(phones.begin(), phones.end(), sort_A_Z);
                SaveToFile(phones);
                std::cout << "Успешное сохранение!" << std::endl;
                break;
            }
            else if (choice == 2)
            {
                // сортирует от Я-А, Z-A по полю фамилии
                std::sort(phones.begin(), phones.end(), sort_Z_A);
                SaveToFile(phones);
                std::cout << "Успешное сохранение!" << std::endl;
                break;
            }
        }
    }
}


