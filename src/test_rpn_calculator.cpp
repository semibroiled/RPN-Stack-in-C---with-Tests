/**
 * This test file should run the RPNStackCalculator through testcases
 * as is done in main.cpp
 *
 * Assert that your values and test expressions align
 *
 * TODO: Add test cases for inline to rpn conversion
 * * Added test cases to protoype. Try to add in edge cases and
 * * Different forms here
 * TODO: Add decimal operations, add inline tests, add operation in between
 */
#include "rpn_calculator.h"
// ? This isn't getting imported properly from its own directory-
// ! temporary fix is putting in /src
#include "func_operator.h"
#include <iostream>
#include <cassert>
#include <sstream>

//* Include Inline to RPN for Testing
#include "infixToPostfix.h"

//* Include Validation Unit for Testing
#include "validateInput.h"

void runTests()
{
    //! Part 1 - Test for RPN Calculations
    // Store test cases in string array
    std::string expressions[] = {
        "5 3 +",     // * 5+3=8
        "3 9 4 * +", // * (4*9)+3=39
        "10 5 /",    // * 10/5=2
        "10 4 /"     // * 10/4=1.5
        // TODO: Add expressions to evaluate as neccessary
    };

    // Store answers to test cases in doubles array
    double expectResults[] = {8, 39, 2, 2.5}; // TODO: Append results

    // Run test cases
    for (int i = 0; i < (std::size(expectResults)); i++)
    {

        // Call calculator instance
        RPNStackCalculator tester;

        // Parse and tokenize through iss
        std::istringstream iss(expressions[i]);
        std::cout << expressions[i] << " => ";
        std::string token;

        while (iss >> token)
        {
            if (isdigit(token[0]))
            {
                double operand = std::stoi(token);
                //// std::cout << "Operand: " << operand << std::endl;
                tester.pushOperand(operand);
            }
            else if (isOperator(token[0]))
            {
                // If the token is an Operator, pop top 2 operands to compute
                char curOperator = token[0];
                //// std::cout << "Current Operator: " << curOperator << std::endl;
                tester.compute(curOperator);
            }
            else
            {
                std::cerr << "Invalid Token: " << token << std::endl;
            }
        };

        // Retrieve result after evaluating
        double result = tester.fetchResult();
        std::cout << result;
        assert(result == expectResults[i]);
        std::cout << " : TRUE (!)" << std::endl; //! Call only if assertion passes
    };

    //! Part 2 - Test for Inline to Postfix

    // Store test cases in string array
    std::string expressions_rpn[] = {
        "5 + 3",         //* 5 3 +
        "( 4 * 9 ) + 3", //* 4 9 * 3 +
        "10 / 5",        //* 10 5 /
        "10 / 4 "        //* 10 4 /
        // TODO: Add expressions to test evaluates as neccessary
    };

    // Store answers to test cases in doubles array
    std::string expectResults_rpn[] = {"5 3 + ", "4 9 * 3 + ", "10 5 / ", "10 4 / "}; // TODO: Append results
    // TODO: Expressions evaluated have an extra space at the end i need to trim in header function

    // Run test cases
    for (int i = 0; i < (std::size(expectResults_rpn)); i++)
    {
        // Call infix to postfix function
        std::string expression = infixToPostfix(expressions_rpn[i]);

        // Retrieve result after evaluating
        std::cout << "\"" << expression << "\"";
        assert(expression == expectResults_rpn[i]);
        std::cout << " is " << expectResults_rpn[i];
        std::cout << " : TRUE (!)" << std::endl; //! Call only if assertion passes
    };

    //! Part 3 - Test Validate Input function
    // TODO: Still need to implement this part, but its low priority.

    // Call on message if all cases pass
    std::cout << "All Tests Successfully Passed!" << std::endl;
}

// Pass Tests through main
int main()
{
    runTests();
    return 0;
}
