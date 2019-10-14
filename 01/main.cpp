//
//  main.cpp
//  HomeWork-1
//
//  Created by Николай Попов on 11/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
#include "lexeme_parser.h"

using namespace std;


int main(int argc, const char * argv[]) {
    if (argc > 2){
        return 1;
    }
    std::string calc = "";
    if (argc == 2)
    {
        calc = argv[1];
    }
    else{
        cin>>calc;
    }
    
    
    
    if (calc.length() == 0)
        return 1;
    
    LexemeParser parser = LexemeParser(calc);
    
    std::vector<Lexeme> POLIS;
    std::stack<Lexeme> OPERATIONS;
    
    Lexeme curr_lexeme = Lexeme(BEGIN, NOT_OPERATION, 0, 0);
    while (curr_lexeme.lex_type_ != END)
    {
        curr_lexeme = parser.get_next_lexeme();
        if (curr_lexeme.lex_type_ == ERROR)
            return 1;
        
        
        if(curr_lexeme.lex_type_ == NUMBER)
        {
            POLIS.push_back(curr_lexeme);
        }
        else if (curr_lexeme.lex_type_ == OPERATION)
        {
            while( (not OPERATIONS.empty())
                  && ((
                      (OPERATIONS.top().priority_ >= curr_lexeme.priority_)
                      && (OPERATIONS.top().op_type_ != UNARY_MINUS)
                      )
                  || ((OPERATIONS.top().priority_ > curr_lexeme.priority_) && (OPERATIONS.top().op_type_ == UNARY_MINUS)))
                  )
            {
                POLIS.push_back(OPERATIONS.top());
                OPERATIONS.pop();
            }
            OPERATIONS.push(curr_lexeme);
        }
        else if (curr_lexeme.lex_type_ == BRACKET)
        {
            if (curr_lexeme.op_type_ == BR_OPEN)
                OPERATIONS.push(curr_lexeme);
            else if (curr_lexeme.op_type_ == BR_CLOSE)
            {
                bool flag = false;
                while ((not OPERATIONS.empty()))
                {
                    if (OPERATIONS.top().op_type_ == BR_OPEN)
                    {
                        OPERATIONS.pop();
                        flag = true;
                        break;
                    }
                    else
                    {
                        if (OPERATIONS.empty())
                            return 1;
                        POLIS.push_back(OPERATIONS.top());
                        OPERATIONS.pop();
                    }

                }
                if (!flag)
                    return -1;
            }
        }
    }
    while (not OPERATIONS.empty())
    {
        if (OPERATIONS.top().lex_type_ == BRACKET)
            return 2;
        POLIS.push_back(OPERATIONS.top());
        OPERATIONS.pop();
    }
        
    std::stack<int> calculator;
    
    
    for(int i = 0; i<POLIS.size(); i++)
    {
        curr_lexeme = POLIS[i];
        
        if (curr_lexeme.lex_type_ == NUMBER)
            calculator.push(curr_lexeme.value_);
        else if (curr_lexeme.lex_type_ == OPERATION){
            
            if(calculator.empty())
                return 1;

            if (curr_lexeme.op_type_ == ADD)
            {
                int a = calculator.top();
                calculator.pop();
                
                if(calculator.empty())
                    return 1;
                int b = calculator.top();
                calculator.pop();
                calculator.push(a+b);
            }
            
            else if (curr_lexeme.op_type_ == MUL)
            {
                int a = calculator.top();
                calculator.pop();
                
                if(calculator.empty())
                    return 1;
                int b = calculator.top();
                calculator.pop();
                calculator.push(a*b);
            }
            
            else if (curr_lexeme.op_type_ == DIV)
            {
                int a = calculator.top();
                calculator.pop();
                
                if(calculator.empty())
                    return 1;
                int b = calculator.top();
                calculator.pop();
                calculator.push(b/a);
            }
            else if (curr_lexeme.op_type_ == SUB)
            {
                int a = calculator.top();
                calculator.pop();
                if(calculator.empty())
                    return 1;
                
                
                int b = calculator.top();
                calculator.pop();
                calculator.push(b-a);
            }
            else if (curr_lexeme.op_type_ == UNARY_MINUS)
            {
                int a = calculator.top();
                calculator.pop();
                calculator.push(-a);
            }
        }
        
        
    }
    if(calculator.size() > 1)
        return 1;

    std::cout << calculator.top();
    return 0;
}
