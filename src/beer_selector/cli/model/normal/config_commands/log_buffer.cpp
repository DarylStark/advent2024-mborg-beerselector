#include "log_buffer.h"
#include "../../../../logging.h"

bool LogBufferSetSize::execute(std::map<std::string, std::string> args)
{
    _factory->get_configuration_manager()->set("log.buf.len", args["max_items"]);
    log_buffer.set_max_size(std::stoi(args["max_items"]));
    log_buffer_size = std::stoi(args["max_items"]);
    return false;
}