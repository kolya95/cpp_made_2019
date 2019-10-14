//
//  lexeme_parser.cpp
//  HomeWork-1
//
//  Created by Николай Попов on 14/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//
#include "lexeme_parser.h"


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
