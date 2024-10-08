#include <sstream>
#include <iomanip>
#include <map>

#include "memory_info.h"
#include "esp_heap_caps.h"

constexpr uint32_t COMMAND_COLUMN_LENGTH_FIELD = 32;
constexpr uint32_t COMMAND_COLUMN_LENGTH_INFO = 16;

bool MemoryInfo::execute(std::map<std::string, std::string> args)
{
    // Get heap information
    multi_heap_info_t heap_info;
    heap_caps_get_info(&heap_info, MALLOC_CAP_DEFAULT);

    // Get PSRAM information
    multi_heap_info_t psram_info;
    heap_caps_get_info(&psram_info, MALLOC_CAP_SPIRAM);

    // Create output stream
    std::stringstream ss;

    // Add heap information to the output stream
    std::map<std::string, size_t> heap_info_map = {
        {"1-Total capacity", heap_info.total_free_bytes + heap_info.total_allocated_bytes},
        {"2-Total free bytes", heap_info.total_free_bytes},
        {"3-Total allocated bytes", heap_info.total_allocated_bytes},
        {"4-Minimum free bytes ever", heap_info.minimum_free_bytes},
        {"5-Total blocks", heap_info.total_blocks},
        {"6-Number of free blocks", heap_info.free_blocks},
        {"7-Number of allocated blocks", heap_info.allocated_blocks},
        {"8-Largest free block", heap_info.largest_free_block}
    };

    ss << "\r\nHeap information:\r\n";
    ss << std::string(COMMAND_COLUMN_LENGTH_FIELD + COMMAND_COLUMN_LENGTH_INFO + 1, '-') << "\r\n";
    for (const auto &entry : heap_info_map)
    {
        ss << std::left << std::setw(COMMAND_COLUMN_LENGTH_FIELD)
           << entry.first.substr(2)
           << std::right << std::setw(COMMAND_COLUMN_LENGTH_INFO)
           << entry.second
           << "\r\n";
    }

    // Add PSRAM information to the output stream
    std::map<std::string, size_t> psram_info_map = {
        {"1-Total capacity", psram_info.total_free_bytes + psram_info.total_allocated_bytes},
        {"2-Total free bytes", psram_info.total_free_bytes},
        {"3-Total allocated bytes", psram_info.total_allocated_bytes},
        {"4-Minimum free bytes ever", psram_info.minimum_free_bytes},
        {"5-Total blocks", psram_info.total_blocks},
        {"6-Number of free blocks", psram_info.free_blocks},
        {"7-Number of allocated blocks", psram_info.allocated_blocks},
        {"8-Largest free block", psram_info.largest_free_block}
    };

    ss << "\r\nPSRAM information:\r\n";
    ss << std::string(COMMAND_COLUMN_LENGTH_FIELD + COMMAND_COLUMN_LENGTH_INFO + 1, '-') << "\r\n";
    for (const auto &entry : psram_info_map)
    {
        ss << std::left << std::setw(COMMAND_COLUMN_LENGTH_FIELD)
           << entry.first.substr(2)
           << std::right << std::setw(COMMAND_COLUMN_LENGTH_INFO)
           << entry.second
           << "\r\n";
    }

    // Print the output
    _factory->get_output_handler()->println(ss.str());

    return true;
}