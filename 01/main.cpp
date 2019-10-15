//
//  main.cpp
//  HomeWork-1
//
//  Created by Николай Попов on 11/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//

#include <iostream>
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
    try {
        parser.create_polis();
        std::cout << parser.calculate();
    } catch (const std::exception& e) {
        return 1;
    }

    
    return 0;
}
