#include "simple_validator.h"

SimpleValidator::SimpleValidator(const std::string expected_code, const std::string license_code)
    : _expected_code(expected_code), _license_code(license_code)
{
}

bool SimpleValidator::validate() const
{
    return _license_code == _expected_code;
}
