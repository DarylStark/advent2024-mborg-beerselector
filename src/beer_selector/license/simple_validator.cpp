#include "simple_validator.h"

SimpleValidator::SimpleValidator(const std::string expected_key)
    : _expected_key(expected_key)
{
}

bool SimpleValidator::validate(const std::string license_key) const
{
    return license_key == _expected_key;
}
