#pragma once

#include "common.h"
#include "stringhelper.h"

class Module
{

public:

    Module(const std::string& name)
        : _name(StringHelper::removeAllSpaces(name))
    {
    }

    Module(const std::string& name, const std::vector<float> parameters)
        : _name(StringHelper::removeAllSpaces(name))
        , _parameters(parameters)
    {
    }

    float operator[](size_t index)
    {
        if (index >= _parameters.size())
        {
            std::cerr << "Index out of module parameters bound: " << index << " against size of " << _parameters.size() << '\n';
            throw std::out_of_range("Index out of module parameters bound");
        }
        return _parameters[index];
    }

    inline const std::vector<float>& getParameters() { return _parameters; }

private:

    std::string _name;
    std::vector<float> _parameters;
};

