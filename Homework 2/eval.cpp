//
//  main.cpp
//  eval
//
//  Created by Rajiv Anisetti on 2/6/17.
//  Copyright © 2017 Rajiv Anisetti. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, const bool values[], string& postfix, bool& result);
string switchToPostfix(string inFix);
int calculatePrecedence(char op);
bool isValid(string str);
string takeOutSpaces(string str);

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    if (!isValid(infix))
        return 1;
    
    postfix = switchToPostfix(infix);

    stack<bool> istack;
    
    for (int k = 0; k < postfix.size(); k++)
    {
        if (isdigit(postfix[k]))
        {
            int num = postfix[k] - '0';
            istack.push(values[num]);
        }
        
        bool tempResult;
        
        if (postfix[k] == '!')
        {
            tempResult = istack.top();
            istack.pop();
            istack.push(!tempResult);
        }
        
        if (postfix[k] == '&')
        {
            bool operandOne = istack.top();
            istack.pop();
            bool operandTwo = istack.top();
            istack.pop();
            tempResult = (operandOne && operandTwo);
            istack.push(tempResult);
        }
        
        if (postfix[k] == '|')
        {
            bool operandOne = istack.top();
            istack.pop();
            bool operandTwo = istack.top();
            istack.pop();
            tempResult = (operandOne || operandTwo);
            istack.push(tempResult);
        }
    }

    result = istack.top();
    
    return 0;
}

int main()
{
    
     
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
           &&  pf == "43!03&&|"  &&  !answer);
    
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("(()))))))", ba, pf, answer) == 1);
    assert(evaluate(")))((((", ba, pf, answer) == 1);
    assert(evaluate("((((((((())", ba, pf, answer) == 1);
    assert(evaluate("*", ba, pf, answer) == 1);
    assert(evaluate("X", ba, pf, answer) == 1);
    assert(evaluate("&", ba, pf, answer) == 1);
    assert(evaluate("!", ba, pf, answer) == 1);
    assert(evaluate("34", ba, pf, answer) == 1);
    assert(evaluate("!5&6&9", ba, pf, answer) == 0);
    assert(evaluate("(1)", ba, pf, answer) == 0);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("3&|4", ba, pf, answer) == 1);
    
    assert(evaluate("(3&|4", ba, pf, answer) == 1);
    assert(evaluate("3&|)4)", ba, pf, answer) == 1);
    assert(evaluate("3&|4", ba, pf, answer) == 1);
    
    assert(evaluate("!!!!!!4", ba, pf, answer) == 0);
    assert(evaluate("!!!!!", ba, pf, answer) == 1);
    
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}


string switchToPostfix(string inFix)
{
    string tempPostFix = "";
    stack<char> operatorStack;
    
    for (int k = 0; k < inFix.size(); k++)
    {
        char ch = inFix[k];
        switch (ch)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                tempPostFix += ch;
                break;
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                while (operatorStack.top() != '(')
                {
                    char temp = operatorStack.top();
                    tempPostFix += temp;
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '!':
                operatorStack.push(ch);
                break;
            case '&':
            case '|':
                while (!operatorStack.empty() && operatorStack.top() != '(' && calculatePrecedence(ch) <= calculatePrecedence(operatorStack.top()))
                {
                    tempPostFix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
            default:
                break;
        }
    }
    while (!operatorStack.empty())
    {
        tempPostFix += operatorStack.top();
        operatorStack.pop();
    }
    
    return tempPostFix;
}

int calculatePrecedence(char op)
{
    switch (op)
    {
        case '!':
            return 3;
            break;
        case '&':
            return 2;
            break;
        case '|':
            return 1;
            break;
        default:
            return -1;
    }
    
}

bool isValid(string infix)
{
    bool valid = true;
    
    string str = takeOutSpaces(infix);
    
    if (str.size() == 0)
        return false;
    
    for (int k = 0; k < str.size() - 1; k++)
    {
        if (str[str.size() - 1] == '&' || str[str.size() - 1] == '|' || str[str.size() - 1] == '!' || str[str.size() - 1] == '(')
            return false;
        if (!isdigit(str[k]) && str[k] != '&' && str[k] != '|' && str[k] != '!' && str[k] != '(' && str[k] != ')')
            return false;
        if (!isdigit(str[str.size() - 1]) && str[str.size() - 1] != '&' && str[str.size() - 1] != '|' && str[str.size() - 1] != '!' && str[str.size() - 1] != ')')
            return false;
        if (str[k] == '&' || str[k] == '|')
        {
            if (k == 0 || k == str.size() -1)
                return false;
            if (!isdigit(str[k-1]) && str[k-1] != ')')
                return false;
            if (str[k+1] == '&' || str[k+1] == '|')
                return false;
        }
        if (isdigit(str[k]))
            if (str[k+1] != '&' && str[k+1] != '|' && str[k+1] != ')')
                return false;
    }
    
    int digitCount = 0;
    int operatorCount = 0;
    int openParenCount = 0;
    int closeParenCount = 0;
    for (int k = 0; k < str.size(); k++)
    {
        if (isdigit(str[k]))
            digitCount++;
        if (str[k] == '&' || str[k] == '|')
            operatorCount++;
        if (str[k] == '(')
        {
            openParenCount++;
            int count = k;
            for (int w = k + 1; str[k] != ')' && w < str.size(); w++)
            {
                    count++;
            }
            if (count == str.size())
                return false;
        }
        if (str[k] == ')')
        {
            closeParenCount++;
            int count = k;
            for (int w = k; str[w] != '(' && w > 0 ; w--)
            {
                    count--;
            }
            if (count == -1)
                return false;
        }
    }
    
    if (digitCount == 0 || openParenCount != closeParenCount)
        return false;
    
    if (operatorCount != digitCount - 1)
        return false;
    
    return valid;
}

string takeOutSpaces(string str)
{
    string temp = "";
    
    for (int k = 0; k < str.size(); k++)
        if (str[k] != ' ')
            temp += str[k];
    
    return temp;
}
