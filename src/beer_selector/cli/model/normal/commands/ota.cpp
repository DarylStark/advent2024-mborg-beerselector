#include "ota.h"
#include "../../../../online_version_manager.h"

static OnlineVersionManager ovm = OnlineVersionManager();

bool OTAGetVersions::execute(std::map<std::string, std::string> args)
{
    // TODO: Check if online

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

std::string OTAInstall::_get_filename(std::string version) const
{
    if (version == "latest")
        return(ovm.get_latest().download_url());

    const auto &version_file = ovm.get_versions().find(version);
    if (version_file != ovm.get_versions().end())
    {
        return version_file->second.download_url();
    }

    return "";
}

bool OTAInstall::execute(std::map<std::string, std::string> args)
{
    // TODO: Check if online
    // TODO: Compare current version

    std::string version = args["version"];
    std::string bin_file;

    try {
        ovm.update_versions();
    } catch (OnlineVersionManagerException &e) {
        _factory->get_output_handler()->println(std::string("Error: ") + std::string(e.what()));
        return false;
    }

    std::string filename = _get_filename(version);
    if (filename.empty())
    {
        _factory->get_output_handler()->println("Error: version not found");
        return false;
    }

    _factory->get_output_handler()->println("\r\nInstalling software. Please wait...");
    _factory->get_output_handler()->println("Don't diconnect your device.\r\n");

    // Do the OTA
    try {
        ovm.do_ota(filename);
    } catch (OnlineVersionManagerException &e) {
        // TODO: The error looks weird. It has weird characters in it.
        _factory->get_output_handler()->println(std::string("Error: ") + std::string(e.what()));
        return false;
    }

    _factory->get_output_handler()->println("Installation successful! Please reboot to start the new version.\r\n");

    return false;
}