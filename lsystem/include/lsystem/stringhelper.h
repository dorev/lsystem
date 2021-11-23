#pragma once

#include "common.h"

struct StringHelper
{
    static std::string removeAllSpaces(const std::string_view input)
    {
        std::string output;
        for (unsigned i = 0; i < input.size(); ++i)
        {
            if(input[i] != ' ')
                output += input[i];
        }
        return output;
    }

    static bool isValidExpression(const std::string_view expression)
    {
        // Parenthesis 
        return conjunction(
            validateParenthesis(expression),
            noConsecutiveVariables(expression),
            operatorsAreBetweenVariables(expression));
    }

    static bool validateParenthesis(const std::string_view string)
    {
        int parenthesis = 0;
        for (const char c : string)
        {
            if (c == '(')
                ++parenthesis;
            else if(c == ')')
                --parenthesis;
            if(parenthesis < 0)
                return false;
        }
        return true;
    }

    static bool noConsecutiveVariables(const std::string_view string)
    {
        bool previousIsVariable = false;
        bool currentIsVariable = false;
        for (const char c : string)
        {
            currentIsVariable = isLetter(c);
            if(currentIsVariable && previousIsVariable)
                return false;
            previousIsVariable = currentIsVariable;
        }
        return true;
    }
    static bool operatorsAreBetweenVariables(const std::string_view string)
    {
        bool currentIsVariable = false;
        bool previousIsOperator = false;
        bool currentIsOperator = false;
        char previousCharacter = 0;

        for (const char currentCharacter : string)
        {
            currentIsOperator = isOperatorCharacter(currentCharacter);
            currentIsVariable = disjunction(
                isLetter(currentCharacter),
                currentCharacter == '(',
                currentCharacter == ')');

            if(!currentIsOperator && !currentIsVariable)
                return false;

            if (previousIsOperator && currentIsOperator)
            {
                if(currentCharacter != '=')
                    return false;
                if (currentCharacter == '<' || currentCharacter == '>')
                {
                    previousCharacter = currentCharacter;
                    continue;
                }
            }

            previousCharacter = currentCharacter;
            previousIsOperator = currentIsOperator;
        }
        return true;
    }

    static unsigned countCharacter(const std::string_view string, const char& character)
    {
        unsigned count = 0;
        for (const char c : string)
        {
            if(c == character)
                ++count;
        }
        return count;
    }

    static bool isOperatorCharacter(const char& character)
    {
        return disjunction(
            character == '+',
            character == '-',
            character == '*',
            character == '/',
            character == '^',
            character == '<',
            character == '>',
            character == '=');
    }

    static bool isLetter(const char& character)
    {
        return character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z';
    }
};
