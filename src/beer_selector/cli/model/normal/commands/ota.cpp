#include "ota.h"
#include "../../../../online_version_manager.h"

static OnlineVersionManager ovm = OnlineVersionManager();

bool OTAGetVersions::execute(std::map<std::string, std::string> args)
{
    _factory->get_output_handler()->println("\r\nAvailable versions online:\r\n");

    try {
        ovm.update_versions();
    } catch (OnlineVersionManagerException &e) {
        _factory->get_output_handler()->println(std::string("Error: ") + std::string(e.what()));
        return false;
    }

    for (const auto& version : ovm.get_versions()) {
        _factory->get_output_handler()->print("" + version.first);
        _factory->get_output_handler()->print(" - " + std::string(version.second.date));
        _factory->get_output_handler()->print(" - " + std::string(version.second.name));
        if (version.second.latest)
            _factory->get_output_handler()->print(" - LATEST");
        _factory->get_output_handler()->println("");

    }
    _factory->get_output_handler()->println();

    return false;
}