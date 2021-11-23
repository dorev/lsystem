#pragma once

#include "common.h"

// Helpers to deal with std::variant<...>
enum class OperandTypeId
{
    Int,
    Float,
    Bool,
    Unsupported
};

template <class T, class... Ts>
OperandTypeId getOperandTypeId(const std::variant<T, Ts...>& variant)
{
    if(std::holds_alternative<int>(variant))
        return OperandTypeId::Int;
    if(std::holds_alternative<float>(variant))
        return OperandTypeId::Float;
    if(std::holds_alternative<bool>(variant))
        return OperandTypeId::Bool;
    return OperandTypeId::Unsupported;
}

class Operator
{

public:

    enum class Symbol
    {
        Add,
        Sub,
        Mul,
        Div,
        Exp,
        Or,
        And,
        Greater,
        GreaterOrEqual,
        Lesser,
        LesserOrEqual,
        Equal,
        Invalid
    };

    using Operand = std::variant<int, float, bool>;

    Operator(const std::string_view& operationSymbol)
    {
        // Store the appropriate function
        switch (deduceOperator(operationSymbol))
        {
            case Symbol::Add:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    switch (getOperandTypeCombination(lhs, rhs))
                    {
                        case OperandTypeCombination::IntInt: return addOperand<int,int>(lhs, rhs);
                        case OperandTypeCombination::FloatFloat: return addOperand<float, float>(lhs, rhs);
                        case OperandTypeCombination::FloatInt: return addOperand<float,int>(lhs, rhs);
                        case OperandTypeCombination::IntFloat: return addOperand<int,float>(lhs, rhs);
                        default: throw std::runtime_error("Unsupported operand combination");
                    }
                };
                break;
            case Symbol::Sub:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<float>(lhs) - std::get<float>(rhs);
                };
                break;
            case Symbol::Mul:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<float>(lhs) * std::get<float>(rhs);
                };
                break;
            case Symbol::Div:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<float>(lhs) / std::get<float>(rhs);
                };
                break;
            case Symbol::Exp:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::pow(std::get<float>(lhs), std::get<float>(rhs));
                };
                break;
            case Symbol::Greater:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<bool>(lhs) > std::get<bool>(rhs);
                };
                break;
            case Symbol::GreaterOrEqual:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<bool>(lhs) >= std::get<bool>(rhs);
                };
                break;
            case Symbol::Lesser:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<bool>(lhs) < std::get<bool>(rhs);
                };
                break;
            case Symbol::LesserOrEqual:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<float>(lhs) <= std::get<float>(rhs);
                };
                break;
            case Symbol::Or:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<bool>(lhs) || std::get<bool>(rhs);
                };
                break;
            case Symbol::And:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<bool>(lhs) && std::get<bool>(rhs);
                };
                break;
            case Symbol::Equal:
                _function = [](Operand lhs, Operand rhs) -> Operand
                {
                    return std::get<bool>(lhs) == std::get<bool>(rhs);
                };
                break;

            case Symbol::Invalid:
                std::cerr << "Invalid operation character: " << operationSymbol << '\n';
                throw std::runtime_error("Invalid operation character");
                break;
        }
    }

    template <class T, class U, class R = decltype(std::declval<T>() + std::declval<U>())>
    R operator()(T lhs, U rhs) const
    {
        return std::get<R>(_function(lhs, rhs));
    }

private:

    static Symbol deduceOperator(const std::string_view& operationSymbol)
    {
        if(operationSymbol == "+")
            return Symbol::Add;
        if(operationSymbol == "-")
            return Symbol::Sub;
        if(operationSymbol == "*")
            return Symbol::Mul;
        if(operationSymbol == "/")
            return Symbol::Div;
        if(operationSymbol == "^")
            return Symbol::Exp;
        if(operationSymbol == "|")
            return Symbol::Or;
        if(operationSymbol == "&")
            return Symbol::And;
        if(operationSymbol == ">")
            return Symbol::Greater;
        if(operationSymbol == ">=")
            return Symbol::GreaterOrEqual;
        if(operationSymbol == "<")
            return Symbol::Lesser;
        if(operationSymbol == "<=")
            return Symbol::LesserOrEqual;
        return Symbol::Invalid;
    }

    enum class OperandTypeCombination
    {
        IntInt,
        FloatFloat,
        IntFloat,
        FloatInt,
        Invalid
    };

    static OperandTypeCombination getOperandTypeCombination(const Operand& lhs, const Operand& rhs)
    {
        OperandTypeId lhsType = getOperandTypeId(lhs);
        OperandTypeId rhsType = getOperandTypeId(rhs);
        if (lhsType == rhsType)
        {
            if(lhsType == OperandTypeId::Int)
                return OperandTypeCombination::IntInt;
            else
                return OperandTypeCombination::FloatFloat;
        }
        else if (lhsType == OperandTypeId::Float)
            return OperandTypeCombination::FloatInt;
        else
            return OperandTypeCombination::IntFloat;
    }

    template <class T, class U>
    auto static addOperand(const Operand& lhs, const Operand& rhs)
    {
        return std::get<T>(lhs) + std::get<U>(rhs);
    }

    using OperatorFunction = Operand(*)(Operand, Operand);
    OperatorFunction _function;
};

