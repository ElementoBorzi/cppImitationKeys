#include <iostream>
#include <Windows.h>
#include <string>
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

        std::cout << "Введите клавишу (в виде кода ASCII, или 'exit' для выхода): ";
        std::getline(std::cin, keyString);

        if (keyString == "exit")
            break;

        std::cout << "Введите интервал в миллисекундах: ";
        std::getline(std::cin, intervalString);

        int interval = std::stoi(intervalString);

        int key = std::stoi(keyString);

        while (true)
        {
            simulateKeyPress(hwnd, key);

            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }

    return 0;
}
