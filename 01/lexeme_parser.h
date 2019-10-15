//
//  lexeme_parser.h
//  HomeWork-1
//
//  Created by Николай Попов on 14/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//

#ifndef lexeme_parser_h
#define lexeme_parser_h
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <vector>
#include <stack>
#include <stdexcept>

enum LexType{
    NUMBER,
    OPERATION,
    BRACKET,
    END,
    BEGIN,
    ERROR
};

enum OperationType{
    ADD,
    SUB,
    MUL,
    DIV,
    UNARY_MINUS,
    BR_OPEN,
    BR_CLOSE,
    NOT_OPERATION
};

struct Lexeme{
public:
    Lexeme(LexType lex_type,
           OperationType op_type,
           int value,
           int priority): lex_type_(lex_type), op_type_(op_type), value_(value), priority_(priority){};
    LexType lex_type_;
    OperationType op_type_;
    int value_;
    int priority_;
};


class LexemeParser{
public:
    
    std::string buf;
    size_t max_len;
    size_t curr_position;
    
    Lexeme prev_lexeme = Lexeme(BEGIN, NOT_OPERATION, 0, 0);
    std::stack<int> calculator;
    std::vector<Lexeme> POLIS;
    std::stack<Lexeme> OPERATIONS;

    int curr_state;
    
    LexemeParser(const std::string& buf_){
        buf = buf_;
        max_len = buf_.length();
        curr_position = 0;
        curr_state = -1;
    }
    ~LexemeParser(){
    }
    
    Lexeme get_next_lexeme();
    int calculate();
    void create_polis();
};


#endif /* lexeme_parser_h */
