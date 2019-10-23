//
//  LinearAllocator.cpp
//  02
//
//  Created by Николай Попов on 22/10/2019.
//  Copyright © 2019 Николай Попов. All rights reserved.
//

#include "LinearAllocator.hpp"
#include  <stdlib.h>
#include <exception>

LinearAllocator::LinearAllocator(size_t maxSize) : max_size(maxSize), current_size(0)
{
    head = static_cast<char*>(malloc(maxSize));
    if (head)
    {
        current_head = head;
        allocated_ = current_head - head;
    }
    else{
        head = nullptr;
        current_head = nullptr;
        max_size = 0;
        allocated_ = 0;
    }
}

LinearAllocator::~LinearAllocator()
{
    if(head != nullptr)
        free(head);
}

void LinearAllocator::reset()
{
    current_head = head;
    current_size = 0;
    allocated_ = current_head - head;
}

char* LinearAllocator::alloc(size_t size)
{
    char* return_ptr = current_head;
    if (size + current_size > max_size)
        return nullptr;
    current_head = current_head + size;
    current_size = current_size + size;
    allocated_ = current_head - head;
    return return_ptr;
}

LinearAllocator::LinearAllocator(LinearAllocator&& other): head(other.head), current_head(other.current_head), allocated_(other.allocated_), max_size(other.max_size), current_size(other.current_size)
{
    other.head = nullptr;
    other.max_size = 0;
    other.current_size = 0;
    other.current_head  = nullptr;
    other.allocated_ = 0;
}
