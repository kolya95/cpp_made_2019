//
//  LinearAllocator.hpp
//  02
//
//  Created by Николай Попов on 22/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//

#ifndef LinearAllocator_hpp
#define LinearAllocator_hpp
#include <stdlib.h>
#include <stdio.h>
#include <exception>

class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize);
    ~LinearAllocator();
    char* alloc(size_t size);
    void reset();
    
    LinearAllocator() = delete;
    LinearAllocator(const LinearAllocator& other) = delete;
    LinearAllocator& operator=(const LinearAllocator& other) = delete;
    LinearAllocator(LinearAllocator&& other) = delete;
    LinearAllocator& operator=(LinearAllocator&& other) = delete;

private:
    char* head;
    char* current_head;
    size_t current_size;
    size_t max_size;
    
};
#endif /* LinearAllocator_hpp */
