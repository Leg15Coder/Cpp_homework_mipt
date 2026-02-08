export module exception;

import <stdexcept>;

export class Exception : public std::exception {
public:
    const char* what() const noexcept override {
        return "Denominator cannot be zero.";
    }
};
