#pragma once

#include "common.h"
#include "stringhelper.h"

class Production
{

public:

    Production(const std::string& predecessor, const std::string& condition, const std::string& successor)
        : _predecessorString(StringHelper::removeAllSpaces(predecessor))
        , _conditionString(StringHelper::removeAllSpaces(condition))
        , _successorString(StringHelper::removeAllSpaces(successor))
    {
    }

    inline const std::string& getPredecessor() const { return _predecessorString; }
    inline const std::string& getCondition() const { return _conditionString; }
    inline const std::string& getProduction() const { return _successorString; }
    inline bool hasCondition() const { return !_conditionString.empty(); }

    bool operator<(const Production& other) const
    {
        return _predecessorString < other._predecessorString;
    }

private:

    std::string _predecessorString;
    std::string _conditionString;
    std::string _successorString;
};
