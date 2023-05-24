#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

// Функция для имитации нажатия клавиши в выбранном процессе
void simulateKeyPress(HWND hwnd, int key)
{
    PostMessage(hwnd, WM_KEYDOWN, key, 0);

    // Ждем некоторое время перед отпусканием клавиши
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    PostMessage(hwnd, WM_KEYUP, key, 0);
}

// Функция для поиска процесса по названию окна
HWND findProcessByWindowTitle(const std::string& windowTitle)
{
    HWND hwnd = FindWindowA(NULL, windowTitle.c_str());
    return hwnd;
}

int main()
{
    const std::string windowTitle = "World of Warcraft";

    HWND hwnd = findProcessByWindowTitle(windowTitle);

    if (hwnd == NULL)
    {
        std::cout << "Ошибка: не удалось найти окно процесса" << std::endl;
        return 1;
    }

    while (true)
    {
        std::string keyString;
        std::string intervalString;

        std::cout << "Введите клавиши (в виде кодов ASCII, разделенных запятыми, или 'exit' для выхода): ";
        std::getline(std::cin, keyString);

        if (keyString == "exit")
            break;

        std::cout << "Введите интервал в миллисекундах: ";
        std::getline(std::cin, intervalString);

        int interval = std::stoi(intervalString);

        std::vector<int> keys;

        // Разбиваем введенную строку с клавишами на отдельные коды ASCII
        size_t pos = 0;
        while ((pos = keyString.find(',')) != std::string::npos)
        {
            std::string key = keyString.substr(0, pos);
            keys.push_back(std::stoi(key));
            keyString.erase(0, pos + 1);
        }
        keys.push_back(std::stoi(keyString));

        while (true)
        {
            // Имитируем нажатие для каждого кода ASCII
            for (int key : keys)
            {
                simulateKeyPress(hwnd, key);
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            }
        }
    }

    return 0;
}
