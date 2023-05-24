#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>

// Функция для отправки цифры в выбранный процесс
void sendNumberToProcess(HWND hwnd, int number)
{
    SendMessageA(hwnd, WM_CHAR, '0' + number, 0);
}

int main()
{
    HWND hwnd = NULL;
    do
    {
        hwnd = GetForegroundWindow();
        DWORD processId;
        GetWindowThreadProcessId(hwnd, &processId);
        if (hwnd != NULL && processId != 0)
        {
            std::cout << "ID процесса: " << processId << std::endl;
            break;
        }
    } while (true);

    while (true)
    {
        std::string numberString;
        std::string intervalString;

        std::cout << "Введите цифры, разделенные запятой (или 'exit' для выхода): ";
        std::getline(std::cin, numberString);

        if (numberString == "exit")
            break;

        std::cout << "Введите интервал в миллисекундах: ";
        std::getline(std::cin, intervalString);

        int interval = std::stoi(intervalString);

        std::string::size_type pos = 0;
        std::string::size_type prevPos = 0;

        while (true)
        {
            while ((pos = numberString.find(',', prevPos)) != std::string::npos)
            {
                std::string number = numberString.substr(prevPos, pos - prevPos);
                sendNumberToProcess(hwnd, std::stoi(number));
                prevPos = pos + 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            }

            // Отправка последней цифры после последней запятой (или единственной цифры, если запятых нет)
            std::string number = numberString.substr(prevPos);
            sendNumberToProcess(hwnd, std::stoi(number));

            std::this_thread::sleep_for(std::chrono::milliseconds(interval));

            pos = 0;
            prevPos = 0;
        }
    }

    return 0;
}
