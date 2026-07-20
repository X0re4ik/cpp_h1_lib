#ifndef H_H1
#define H_H1
#include "task.hpp"

// NOLINTNEXTLINE (modernize-deprecated-headers)
#include <limits.h>

namespace h1
{
/**
 * @brief Выполнить суммирование
 * 
 * @param task - Задача struct Task* 
 * @return int - {-1} - Ошибка переполнения; {-2} - Общая ошибка; {1} - Успешно расчитано
 */
inline int makeAddition(struct Task* task);

/**
 * @brief Выполнить вычитание
 * 
 * @param task - Задача struct Task* 
 * @return int - {-1} - Ошибка переполнения; {-2} - Общая ошибка; {1} - Успешно расчитано
 */
inline int makeSubtraction(struct Task* task);

/**
 * @brief Выполнить умножение
 * 
 * @param task - Задача struct Task* 
 * @return int - {-1} - Ошибка переполнения; {-2} - Общая ошибка; {1} - Успешно расчитано
 */
inline int makeMultiplication(struct Task* task);

/**
 * @brief Выполнить деление
 * 
 * @param task - Задача struct Task* 
 * @return int - {-1} - Ошибка переполнения; {-2} - Общая ошибка; {1} - Успешно расчитано
 */
inline int makeDivision(struct Task* task);

/**
 * @brief Выполнить расчёт факториала
 * 
 * @param task - Задача struct Task* 
 * @return int - {-1} - Ошибка переполнения; {-2} - Общая ошибка; {1} - Успешно расчитано
 */
inline int makeFactorial(struct Task* task);

/**
 * @brief Выполнить возведение в степень
 * 
 * @param task - Задача struct Task* 
 * @return int - {-1} - Ошибка переполнения; {-2} - Общая ошибка; {1} - Успешно расчитано
 */
inline int makePower(struct Task* task);

inline MathDefault_t toFactorial(MathDefault_t value, MathDefault_t accumulator,
                                 int& isOverflow);

} // namespace h1

int h1::makeAddition(struct Task* task)
{

    MathDefault_t result = 0;

    // Проверка на переполнение
    if (__builtin_add_overflow(task->left, task->right, &result))
    {
        setError(task, "При сложении произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return -1;
    }

    setOk(task, result);
    return 1;
}

int h1::makeSubtraction(struct Task* task)
{
    MathDefault_t result = 0;

    // Проверка на переполнение
    if (__builtin_sub_overflow(task->left, task->right, &result))
    {
        setError(task, "При вычитании произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return -1;
    }

    setOk(task, result);
    return 1;
}

int h1::makeMultiplication(struct Task* task)
{
    MathDefault_t result = 0;
    // Проверка на переполнение
    if (__builtin_mul_overflow(task->left, task->right, &result))
    {
        setError(task, "При умножении произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return -1;
    }

    setOk(task, result);
    return 1;
}

int h1::makeDivision(struct Task* task)
{
    if (task->right == 0)
    {
        setError(task, "Запрещено производить деление на 0");
        return -2;
    }
    //Проверка на переполнение
    if (task->left == INT_MIN && task->right == -1)
    {
        setError(task, "При делении произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return -1;
    }

    auto result = static_cast<MathResultDefault_t>(task->left) /
                  static_cast<MathResultDefault_t>(task->right);
    setOk(task, result);
    return 1;
}

// NOLINTNEXTLINE (misc-no-recursion)
inline MathDefault_t h1::toFactorial(MathDefault_t value,
                                     MathDefault_t accumulator, int& isOverflow)
{
    if (value == 0)
    {
        return accumulator;
    }

    MathDefault_t temp = 0;
    if (__builtin_mul_overflow(accumulator, value, &temp))
    {
        isOverflow = 1;
        return -1;
    }

    return h1::toFactorial(value - 1, temp, isOverflow);
}

int h1::makeFactorial(struct Task* task)
{
    if (task->left < 0)
    {
        setError(task, "Факториал не определен для отрицательных чисел");
        return -2;
    }

    auto value = static_cast<int>(task->left);
    int isOverflow = 0;
    auto result = toFactorial(value, 1, isOverflow);

    if (isOverflow == 1)
    {
        setError(task,
                 "При расчёте факториала произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return -1;
    }
    setOk(task, result);
    return 1;
}

int h1::makePower(struct Task* task)
{
    if (task->right < 0)
    {
        setError(task, "Возведение в отрицательную степень не поддерживается");
        return -2;
    }

    auto exp = static_cast<int>(task->right);
    auto result = 1;
    for (int i = 0; i < exp; ++i)
    {
        MathDefault_t temp = 0;
        // Проверка на переполнение
        if (__builtin_mul_overflow(result, task->left, &temp))
        {
            setError(
                task,
                "При возведении в степень произошло переполнение базового типа",
                OperationStatus::ERROR_OVERFLOW);
            return -1;
        }
        result = temp;
    }

    setOk(task, result);
    return 1;
}

#endif // H_H1