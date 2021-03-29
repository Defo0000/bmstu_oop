#include "rc.h"

void handle_return_code(const rc_t code)
{
    switch(code)
    {
        case ERR_FILE:
            QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл с указанным названием.");
            break;
        case ERR_ALLOC:
            QMessageBox::critical(nullptr, "Ошибка", "Произошла ошибка во время выделения памяти.");
            break;
        case ERR_READ:
            QMessageBox::critical(nullptr, "Ошибка", "Произошла ошибка во время чтения данных из файла.");
            break;
        case ERR_SIZE:
            QMessageBox::critical(nullptr, "Ошибка", "Указан неверный параметр в качестве количества.");
            break;
        case ERR_DATA:
            QMessageBox::critical(nullptr, "Ошибка", "Внутренние данные структур повреждены.");
            break;
        default:
            QMessageBox::critical(nullptr, "Ошибка", "Неизвестная ошибка.");
    }
}
