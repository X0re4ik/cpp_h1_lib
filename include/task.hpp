#include <stdio.h>
#include <string.h>

#include <cfloat>
#include <cstdint>

using MathDefault_t = int;

enum class OperationEnum : uint8_t
{
    ADDITION = 1,
    SUBTRACTION = 2,
    MULTIPLICATION = 3,
    DIVISION = 4,
    FACTORIAL = 5,
    POWER = 6,
};

enum class OperationStatus : uint16_t
{
    NOT_STATE = 0,
    OK = 200,
    ERROR = 500,
    ERROR_OVERFLOW = 520
};

struct Task
{
    MathDefault_t left;
    MathDefault_t right;
    MathDefault_t result;
    bool isValidResult;
    OperationEnum* operation;
    OperationStatus status;
    // NOLINTNEXTLINE (modernize-avoid-c-array)
    char errorMessage[100];
};

inline Task* createTask()
{
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto* newTask = new Task{
        -1, -1, -1, false, nullptr, OperationStatus::NOT_STATE,
    };
    return newTask;
}

inline void deleteTask(Task* task)
{
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete task->operation;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    memset(task->errorMessage, 0, sizeof(task->errorMessage));

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete task;
}

inline void setErrorMessage(Task* task, const char* errorMessage)
{
    // NOLINTNEXTLINE (cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    strncpy(task->errorMessage, errorMessage, sizeof(task->errorMessage) - 1);
    task->errorMessage[sizeof(task->errorMessage) - 1] = '\0';
}

inline void setError(Task* task, const char* errorMessage,
                     OperationStatus errorCode = OperationStatus::ERROR)
{
    setErrorMessage(task, errorMessage);
    task->status = errorCode;
    task->isValidResult = false;
}

inline void setOk(Task* task, MathDefault_t result)
{
    task->result = result;
    task->isValidResult = true;
    task->status = OperationStatus::OK;
}
