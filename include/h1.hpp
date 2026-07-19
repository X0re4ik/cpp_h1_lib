#pragma once
#include "task.hpp"

namespace h1
{
inline void makeAddition(struct Task* task);
inline void makeSubtraction(struct Task* task);
inline void makeMultiplication(struct Task* task);
inline void makeDivision(struct Task* task);
inline void makeFactorial(struct Task* task);
inline void makePower(struct Task* task);
} // namespace h1

void h1::makeAddition(struct Task* task)
{
    auto result = task->left + task->right;

    //Проверка на переполнение
    if ((result - task->left) != task->right)
    {
        setError(task, "При сложении произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return;
    }

    setOk(task, result);
}

void h1::makeSubtraction(struct Task* task)
{
    auto result = task->left - task->right;
    //Проверка на переполнение
    if ((result + task->right) != task->left)
    {
        setError(task, "При вычитании произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return;
    }

    setOk(task, result);
}

void h1::makeMultiplication(struct Task* task)
{
    auto result = task->left * task->right;
    //Проверка на переполнение
    if ((result / task->left) != task->right)
    {
        setError(task, "При умножении произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return;
    }
    setOk(task, result);
}

void h1::makeDivision(struct Task* task)
{
    if (task->right == 0)
    {
        setError(task, "Запрещено производить деление на 0");
        return;
    }
    auto result = task->left / task->right;
    //Проверка на переполнение
    if ((result * task->right) != task->left)
    {
        setError(task, "При делении произошло переполнение базового типа",
                 OperationStatus::ERROR_OVERFLOW);
        return;
    }

    setOk(task, result);
}

void h1::makeFactorial(struct Task* task)
{
    if (task->left < 0)
    {
        setError(task, "Факториал не определен для отрицательных чисел");
        return;
    }

    auto value = static_cast<int>(task->left);
    int result = 1;
    for (int i = 1; i <= value; ++i)
    {
        MathDefault_t temp = result * i;

        // Проверка на переполнение
        if (i != 0 && temp / i != result)
        {
            setError(task,
                     "При вычислении факториала произошло переполнение "
                     "базового типа",
                     OperationStatus::ERROR_OVERFLOW);
            return;
        }

        result = temp;
    }
    setOk(task, result);
}

void h1::makePower(struct Task* task)
{
    if (task->right < 0)
    {
        setError(task, "Возведение в отрицательную степень не поддерживается");
        return;
    }
    auto exp = static_cast<int>(task->right);
    auto result = static_cast<MathDefault_t>(1.0);
    for (int i = 0; i < exp; ++i)
    {
        MathDefault_t temp = result * task->left;
        // Проверка на переполнение
        if (temp != 0 && temp / result != task->left)
        {
            setError(
                task,
                "При возведении в степень призошло переполнение базового типа",
                OperationStatus::ERROR_OVERFLOW);
            return;
        }
        result = temp;
    }

    setOk(task, result);
}