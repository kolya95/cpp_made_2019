//
//  main.cpp
//  02
//
//  Created by Николай Попов on 16/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//

#include <chrono>
#include <iostream>
#include "LinearAllocator.hpp"

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us =
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};


int main(int argc, char* argv[])
{
    size_t alloc_size_block = std::stoi(argv[1]);
    size_t allocator_maxsize = std::stoi(argv[2]);
    std::cout<<"alloc size block: "<< alloc_size_block<<std::endl;
    std::cout<<"allocator_maxsize: "<< allocator_maxsize<<std::endl;
    
    LinearAllocator my_alloc(allocator_maxsize);
     
    {
        Timer t;
        for(int i = 0; i < 100000; i++)
        {
            
            char* tmp = my_alloc.alloc(alloc_size_block);
            if (tmp == nullptr)
                my_alloc.reset();
        }
    }
    
    
    std::cout<<"kek";
    
    
    return 0;
}
