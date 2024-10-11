#ifndef SIMPLE_VALIDATOR_H
#define SIMPLE_VALIDATOR_H

#include <string>
#include "validator.h"

class SimpleValidator : public LicenseValidator
{
private:
    const std::string _expected_key;

public:
    SimpleValidator(const std::string expected_key);
    bool validate(const std::string license_key) const override;
};

#endif /* SIMPLE_VALIDATOR_H */