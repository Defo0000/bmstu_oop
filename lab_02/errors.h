#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <ctime>
#include <chrono>
#include <memory>
#include <string>
#include <cstring>

class base_error : public std::exception
{
public:
    base_error(
            const std::string &file_name,
            std::string time,
            const std::string &class_name,
            const std::string &func_name,
            const int line,
            const std::string &info_msg)
    {
        error_info = "\nFile: " + file_name + \
                "\nTime: " + time + \
                "\nClass: " + class_name + \
                "\nFunction: " + func_name + \
                "\nLine: " + std::to_string(line) + \
                "\nError message: " + info_msg;
    }

    virtual const char* what() const noexcept override
    {
        return error_info.c_str();
    }

protected:
    std::string error_info;
};

class memory_error : public base_error
{
public:
    memory_error(
            const std::string &file_name,
            const std::string &time,
            const std::string &class_name,
            const std::string &func_name,
            const int line,
            const std::string &info_msg = "Memory allocation error.") :
        base_error(file_name, time, class_name, func_name, line, info_msg) {}
};

class empty_error : public base_error
{
public:
    empty_error(
            const std::string &file_name,
            const std::string &time,
            const std::string &class_name,
            const std::string &func_name,
            const int line,
            const std::string &info_msg = "List is empty.") :
        base_error(file_name, time, class_name, func_name, line, info_msg) {}
};

class iterator_error : public base_error
{
public:
    iterator_error(
            const std::string &file_name,
            const std::string &time,
            const std::string &class_name,
            const std::string &func_name,
            const int line,
            const std::string &info_msg = "Incorrect iterator.") :
        base_error(file_name, time, class_name, func_name, line, info_msg) {}
};

class ptr_error : public base_error
{
public:
    ptr_error(
            const std::string &file_name,
            const std::string &time,
            const std::string &class_name,
            const std::string &func_name,
            const int line,
            const std::string &info_msg = "Incorrect pointer.") :
        base_error(file_name, time, class_name, func_name, line, info_msg) {}
};

#endif
