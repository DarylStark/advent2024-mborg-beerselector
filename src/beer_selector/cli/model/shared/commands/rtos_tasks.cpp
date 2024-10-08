#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "rtos_tasks.h"

constexpr uint32_t COMMAND_COLUMN_LENGTH_FIELD = 32;
constexpr uint32_t COMMAND_COLUMN_LENGTH_INFO = 16;

bool RTOSTasks::execute(std::map<std::string, std::string> args)
{
        // Get the number of tasks
    UBaseType_t num_tasks = uxTaskGetNumberOfTasks();

    // Allocate memory for the task status array
    std::vector<TaskStatus_t> task_status_array(num_tasks);

    // Get the task status
    num_tasks = uxTaskGetSystemState(task_status_array.data(), num_tasks, NULL);

    // Sort the tasks on Task Number
    std::sort(task_status_array.begin(), task_status_array.end(), [](TaskStatus_t a, TaskStatus_t b) {
        return a.xTaskNumber < b.xTaskNumber;
    });

    // Create a string stream to format the output
    std::stringstream ss;
    ss << "\r\n"
        << std::left << std::setw(20) << "Task Name"
       << std::setw(12) << "State"
       << std::right << std::setw(10) << "Priority"
       << std::right << std::setw(10) << "Stack"
       << std::right << std::setw(16) << "Task Number"
       << std::right << std::setw(10) << "Core"
       << "\r\n";
    ss << std::string(79, '-') << "\r\n";

    // Iterate over the tasks and add their information to the string stream
    for (UBaseType_t i = 0; i < num_tasks; i++)
    {
        std::string status = "Invalid";
        switch (task_status_array[i].eCurrentState)
        {
        case eRunning:
            status = "Running";
            break;
        case eReady:
            status = "Ready";
            break;
        case eBlocked:
            status = "Blocked";
            break;
        case eSuspended:
            status = "Suspended";
            break;
        case eDeleted:
            status = "Deleted";
            break;
        case eInvalid:
            status = "Invalid";
            break;
        }

        ss << std::left << std::setw(20) << task_status_array[i].pcTaskName
           << std::setw(12) << status
           << std::right << std::setw(10) << task_status_array[i].uxCurrentPriority
           << std::right << std::setw(10) << task_status_array[i].usStackHighWaterMark
           << std::right << std::setw(16) << task_status_array[i].xTaskNumber
           << std::right << std::setw(10) << task_status_array[i].xCoreID
           << "\r\n";
    }

    _factory->get_output_handler()->println(ss.str());

    return true;
}