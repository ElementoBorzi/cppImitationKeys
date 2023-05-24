#include <iostream>
#include <Windows.h>
#include <string>

// Функция для отправки цифры в выбранный процесс
void sendNumberToProcess(HWND hwnd, int number)
{
    SendMessageA(hwnd, WM_CHAR, '0' + number, 0);
}

int main()
{
    HWND hwnd = FindWindowA(NULL, "Название окна процесса"); // Замените "Название окна процесса" на фактическое название окна процесса, в которое вы хотите отправлять цифры

    if (hwnd == NULL)
    {
        std::cout << "Ошибка: не удалось найти окно процесса" << std::endl;
        return 1;
    }

    while (true)
    {
        std::string numberString;
        std::string intervalString;

        std::cout << "Введите цифры, разделенные запятой: ";
        std::getline(std::cin, numberString);

        std::cout << "Введите интервал в миллисекундах: ";
        std::getline(std::cin, intervalString);

        int interval = std::stoi(intervalString);

        std::string::size_type pos = 0;
        std::string::size_type prevPos = 0;

        while ((pos = numberString.find(',', prevPos)) != std::string::npos)
        {
            std::string number = numberString.substr(prevPos, pos - prevPos);
            sendNumberToProcess(hwnd, std::stoi(number));
            prevPos = pos + 1;
            Sleep(interval);
        }

        // Отправка последней цифры после последней запятой (или единственной цифры, если запятых нет)
        std::string number = numberString.substr(prevPos);
        sendNumberToProcess(hwnd, std::stoi(number));
    }

    return 0;
}
