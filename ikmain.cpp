#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <Windows.h>
#include <iostream>

// Функция для отправки цифры в выбранный процесс
void sendNumberToProcess(int number)
{
    HWND hwnd = FindWindowA(NULL, "Название окна процесса"); // Замените "Название окна процесса" на фактическое название окна процесса, в которое вы хотите отправлять цифры

    if (hwnd == NULL)
    {
        std::cout << "Ошибка: не удалось найти окно процесса" << std::endl;
        return;
    }

    // Отправка цифры в окно процесса
    SendMessageA(hwnd, WM_CHAR, '0' + number, 0);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Создание главного окна
    QMainWindow window;
    window.setWindowTitle("Отправка цифр в процесс");
    window.setFixedSize(300, 150);

    // Создание виджетов GUI
    QLineEdit *numberLineEdit = new QLineEdit(&window);
    QLineEdit *intervalLineEdit = new QLineEdit(&window);
    QPushButton *startButton = new QPushButton("Старт", &window);

    // Создание компоновщиков
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(numberLineEdit);
    inputLayout->addWidget(intervalLineEdit);

    // Установка компоновки главного окна
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(startButton);

    // Установка компоновки на главное окно
    QWidget *centralWidget = new QWidget(&window);
    centralWidget->setLayout(mainLayout);
    window.setCentralWidget(centralWidget);

    // Соединение сигнала нажатия кнопки со слотом для отправки цифр
    QObject::connect(startButton, &QPushButton::clicked, [&]() {
        QString numberString = numberLineEdit->text();
        QString intervalString = intervalLineEdit->text();

        int interval = intervalString.toInt();

        QStringList numbers = numberString.split(',');

        QTimer *timer = new QTimer(&window);

       
