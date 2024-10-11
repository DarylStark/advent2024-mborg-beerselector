#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class LicenseValidator
{
public:
    virtual bool validate(const std::string license_key) const = 0;
};

#endif /* VALIDATOR_H */