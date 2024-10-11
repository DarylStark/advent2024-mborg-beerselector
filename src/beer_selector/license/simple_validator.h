#ifndef SIMPLE_VALIDATOR_H
#define SIMPLE_VALIDATOR_H

#include <string>
#include "validator.h"

class SimpleValidator : public LicenseValidator
{
private:
    const std::string _expected_code;
    const std::string _license_code;

public:
    SimpleValidator(const std::string expected_code, const std::string license_code);
    bool validate() const override;
};

#endif /* SIMPLE_VALIDATOR_H */