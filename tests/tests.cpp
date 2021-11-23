#include "gtest/gtest.h"
#include "lsystem/rule.h"
#include "lsystem/lsystem.h"

class LSystemTest : public ::testing::Test
{
protected:

    LSystemTest()
    {
    }

    ~LSystemTest() override
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};


TEST_F(LSystemTest, DISABLED_Basic)
{
    // Config
    std::string axiom{"F-F-F-F"};
    std::set<Production> rules = {
        { "F", "", "F+F"}
    };
    unsigned n = 4;

    // Log
    std::cout << "Axiom: " << axiom << "\nProductions:\n";
    for (const auto& production : rules)
    {
        std::cout << production.getPredecessor();
        if (production.hasCondition())
            std::cout << " : " << production.getCondition();
        std::cout << " -> " << production.getProduction() << '\n';
    }

    // Process
    for(unsigned i = 0; i < n; ++i)
    {
        std::cout << "n = " << i + 1 << '\n';
        std::stringstream result;
        for (unsigned c = 0; c < axiom.size(); ++c)
        {
            unsigned applicableProduction = 0;
            std::string module{axiom[c]};
            for (const auto& production : rules)
            {
                if (production.getPredecessor() == module)
                {
                    ++applicableProduction;
                    if (applicableProduction > 1)
                    {
                        std::cerr << "Predecessor " << production.getPredecessor() << " matches more than one rule\n";
                        throw std::runtime_error("Predecessor matches more than one rule");
                    }
                    result << production.getProduction();
                }
            }
            if (applicableProduction == 0)
                result << axiom[c];
        }
        axiom = result.str();
        std::cout << axiom << '\n';
    }
}

TEST_F(LSystemTest, NewImpl)
{
    Matrix m({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 0, 1, 2}, {2, 3, 4, 5}});

}


