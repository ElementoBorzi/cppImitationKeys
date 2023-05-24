#include <iostream>
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>

// Функция для имитации нажатия клавиши в выбранном процессе
void simulateKeyPress(HWND hwnd, int key)
{
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = 0;

    SendInput(1, &input, sizeof(INPUT));

    // Ждем некоторое время перед отпусканием клавиши
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

// Функция для поиска процесса по названию окна
HWND findProcessByWindowTitle(const std::string& windowTitle)
{
    HWND hwnd = FindWindowA(NULL, windowTitle.c_str());
    return hwnd;
}

int main()
{
    const std::string windowTitle = "Ферма и деньги";

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
