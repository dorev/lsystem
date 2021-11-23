#pragma once

#include "common.h"
#include "stringhelper.h"
#include "operator.h"

class Expression
{

public:

    using VariablesMap = std::map<std::string, std::optional<float>>;

    explicit operator bool() const
    {
        return true;
    }

    explicit operator float() const
    {
        return 1.0f;
    }

    Expression(const std::string& expressionString)
        : _expressionString(StringHelper::removeAllSpaces(expressionString))
    {
        if (!StringHelper::isValidExpression(_expressionString))
        {
            std::cerr << "Invalid expression string: " << _expressionString << '\n';
            throw std::runtime_error("Invalid expression string");
        }
        parseSequence();
    }

    void parseSequence()
    {
        for (unsigned i = 0; i < _expressionString.size(); ++i)
        {
            
        }
    }

    VariablesMap getVariablesMap()
    {
        return {};
    }

    void setVariablesMap(const VariablesMap& variables)
    {
    }

private:

    using Term = std::variant<int, float, bool, Expression, Operator>;
    enum class TermTypeId
    {
        Float,
        Bool,
        Expression,
        Operator,
        Invalid
    };

    TermTypeId getTermTypeId(const Term& term)
    {
        if(std::holds_alternative<float>(term))
            return TermTypeId::Float;
        if(std::holds_alternative<bool>(term))
            return TermTypeId::Bool;
        if(std::holds_alternative<Expression>(term))
            return TermTypeId::Expression;
        if(std::holds_alternative<Operator>(term))
            return TermTypeId::Operator;
        return TermTypeId::Invalid;
    }

    std::vector<Term> _expressionSequence;
    std::string _expressionString;
};


class PredecessorExpression
{

};

class ConditionExpression
{

};

class SuccessorExpression
{
};

