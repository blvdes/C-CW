#ifndef MODULE_H
#define MODULE_H

#include <string>

// Module container, structurally independant but to be used in map with code as key 
class Module {
    std::string _code;
    std::string _name;
    int _credits;

public: 
    // Constructor declaration and accessors
    Module(const std::string& code, const std::string& name, int credits);

    const std::string &name() const { return _name; };
    const std::string &code() const { return _code; };
    const int credits() const { return _credits; };
};

#endif 