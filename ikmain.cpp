#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

// Функция для изменения кодировки консоли на UTF-8
void setConsoleUTF8Encoding()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

// Функция для установки шрифта консоли
void setConsoleFont(const std::wstring& fontName, int fontSize)
{
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 0;
    fontInfo.dwFontSize.Y = fontSize;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, fontName.c_str());

    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
}

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
    setConsoleUTF8Encoding(); // Устанавливаем кодировку консоли на UTF-8
    setConsoleFont(L"Consolas", 16); // Устанавливаем шрифт консоли на Consolas размером 16

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

        // Разбиваем введенную строку с клавишами
