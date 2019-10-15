//
//  lexeme_parser.cpp
//  HomeWork-1
//
//  Created by Николай Попов on 14/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//
#include "lexeme_parser.h"
#include <vector>
#include <stack>

Lexeme LexemeParser::get_next_lexeme()
{
    std::string curr_token = "";
    
    if (curr_position == max_len)
    {
        return Lexeme(END, NOT_OPERATION, 0, 0);
    }
    
    
    while( curr_position < max_len)
    {
        if (std::isspace(buf[curr_position]))
        {
            curr_position++;
            continue;
        }
        
        else if (std::isdigit(buf[curr_position])){
            curr_state = 1;
            curr_token += buf[curr_position];
            curr_position++;
            continue;
            
        }
        else if( (buf[curr_position] == '+'
            || buf[curr_position] == '*'
            || buf[curr_position] == '('
            || buf[curr_position] == ')'
            || buf[curr_position] == '/'
            || buf[curr_position] == '-'
                  )
            ){
            if (curr_state == 1) // number state
            {
                curr_state = -1;
                Lexeme return_value = Lexeme(NUMBER, NOT_OPERATION, atoi(curr_token.c_str()), 0);
                prev_lexeme = return_value;
                return return_value;
            }
            
            if (buf[curr_position] == '+')
            {
                curr_state = -1;
                Lexeme return_value = Lexeme(OPERATION, ADD, 0, 1);
                prev_lexeme = return_value;
                curr_position++;
                return return_value;
            }
            
            
            if (buf[curr_position] == '/')
            {
                curr_state = -1;
                Lexeme return_value = Lexeme(OPERATION, DIV, 0, 2);
                prev_lexeme = return_value;
                curr_position++;
                return return_value;
            }

            if (buf[curr_position] == '*')
            {
                curr_state = -1;
                Lexeme return_value = Lexeme(OPERATION, MUL, 0, 2);
                prev_lexeme = return_value;
                curr_position++;
                return return_value;
            }
            
            if (buf[curr_position] == '-')
            {
                curr_state = -1;
                if (prev_lexeme.lex_type_ == NUMBER ||
                    (prev_lexeme.lex_type_ == BRACKET &&
                     prev_lexeme.op_type_ == BR_CLOSE
                     )
                    ){
                    Lexeme return_value = Lexeme(OPERATION, SUB, 0, 1);
                    prev_lexeme = return_value;
                    curr_position++;
                    return return_value;
                }
                
                Lexeme return_value = Lexeme(OPERATION, UNARY_MINUS, 0, 3);
                prev_lexeme = return_value;
                curr_position++;
                return return_value;
            }
            
            if (buf[curr_position] == '(')
            {
                Lexeme return_value = Lexeme(BRACKET, BR_OPEN, 0, 0);
                prev_lexeme = return_value;
                curr_position++;
                return return_value;
            }
            
            if (buf[curr_position] == ')')
            {
                Lexeme return_value = Lexeme(BRACKET, BR_CLOSE, 0, 0);
                prev_lexeme = return_value;
                curr_position++;
                return return_value;
            }

        }
        return Lexeme(ERROR, NOT_OPERATION, 0, 0);
    }
    
    if (curr_state == 1) // number state
    {
        curr_state = -1;
        Lexeme return_value = Lexeme(NUMBER, NOT_OPERATION, atoi(curr_token.c_str()), 0);
        prev_lexeme = return_value;
        return return_value;
    }

    
    
    return Lexeme(ERROR, NOT_OPERATION, 0, 0);
};


int LexemeParser::calculate(){
    std::vector<Lexeme> POLIS;
    std::stack<Lexeme> OPERATIONS;
    
    Lexeme curr_lexeme = Lexeme(BEGIN, NOT_OPERATION, 0, 0);
    while (curr_lexeme.lex_type_ != END)
    {
        curr_lexeme = get_next_lexeme();
        if (curr_lexeme.lex_type_ == ERROR)
            throw 1;
        
        
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
                            throw 1;
                        POLIS.push_back(OPERATIONS.top());
                        OPERATIONS.pop();
                    }

                }
                if (!flag)
                    throw 1;
            }
        }
    }
    while (not OPERATIONS.empty())
    {
        if (OPERATIONS.top().lex_type_ == BRACKET)
            throw 1;
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
                throw 1;

            if (curr_lexeme.op_type_ == ADD)
            {
                int a = calculator.top();
                calculator.pop();
                
                if(calculator.empty())
                    throw 1;
                int b = calculator.top();
                calculator.pop();
                calculator.push(a+b);
            }
            
            else if (curr_lexeme.op_type_ == MUL)
            {
                int a = calculator.top();
                calculator.pop();
                
                if(calculator.empty())
                    throw 1;
                int b = calculator.top();
                calculator.pop();
                calculator.push(a*b);
            }
            
            else if (curr_lexeme.op_type_ == DIV)
            {
                int a = calculator.top();
                calculator.pop();
                
                if(calculator.empty())
                    throw 1;
                int b = calculator.top();
                calculator.pop();
                if(a == 0)
                     throw 1;
                   
                calculator.push(b/a);
            }
            else if (curr_lexeme.op_type_ == SUB)
            {
                int a = calculator.top();
                calculator.pop();
                if(calculator.empty())
                    throw 1;
                
                
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
        throw 1;
    return calculator.top();
}
