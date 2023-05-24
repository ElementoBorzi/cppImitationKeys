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
        std::string keysString;
        std::string intervalString;

        std::cout << "Введите клавиши (в виде кодов ASCII, разделенных запятой, или 'exit' для выхода): ";
        std::getline(std::cin, keysString);

        if (keysString == "exit")
            break;

        std::cout << "Введите интервал в миллисекундах: ";
        std::getline(std::cin, intervalString);

        int interval = std::stoi(intervalString);

        std::string::size_type pos = 0;
        std::string::size_type prevPos = 0;

        while ((pos = keysString.find(',', prevPos)) != std::string::npos)
        {
            std::string key = keysString.substr(prevPos, pos - prevPos);
            int keyASCII = std::stoi(key);
            simulateKeyPress(hwnd, keyASCII);
            prevPos = pos + 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }

        // Обработка последней клавиши после последней запятой (или единственной клавиши, если запятых нет)
        std::string key = keysString.substr(prevPos);
        int keyASCII = std::stoi(key);
        simulateKeyPress(hwnd, keyASCII);

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }

    return 0;
}
