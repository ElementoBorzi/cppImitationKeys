#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <chrono>
#include <thread>

// Функция для отправки цифры в выбранный процесс
void sendNumberToProcess(HWND hwnd, int number)
{
    SendMessageA(hwnd, WM_CHAR, '0' + number, 0);
}

// Функция для поиска процесса по названию исполняемого файла
HWND findProcessByExecutableName(const std::string& executableName)
{
    HWND hwnd = NULL;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(snapshot, &processEntry))
        {
            do
            {
                std::string processName = processEntry.szExeFile;
                if (processName == executableName)
                {
                    DWORD processId = processEntry.th32ProcessID;
                    hwnd = FindWindowA(NULL, processEntry.szExeFile);
                    if (hwnd != NULL)
                    {
                        std::cout << "ID процесса: " << processId << std::endl;
                        break;
                    }
                }
            } while (Process32Next(snapshot, &processEntry));
        }

        CloseHandle(snapshot);
    }

    return hwnd;
}

int main()
{
    const std::string executableName = "Farm.exe";

    HWND hwnd = findProcessByExecutableName(executableName);

    if (hwnd == NULL)
    {
        std::cout << "Ошибка: не удалось найти процесс с исполняемым файлом " << executableName << std::endl;
        return 1;
    }

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
