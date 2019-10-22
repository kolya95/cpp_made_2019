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

LinearAllocator::LinearAllocator(size_t maxSize)
{
    this->head = static_cast<char*>(malloc(maxSize));
    this->current_head = this->head;
    
    this->current_size = 0;
    this->max_size = maxSize;
    this->allocated_ = this->current_head - this->head;
}

LinearAllocator::~LinearAllocator()
{
    free(this->head);
}

void LinearAllocator::reset()
{
    this->current_head = this->head;
    this->current_size = 0;
    this->allocated_ = this->current_head - this->head;
}


char* LinearAllocator::alloc(size_t size)
{
    char* return_ptr = this->current_head;
    
    if (size + this->current_size > this->max_size)
        return nullptr;

    this->current_head = this->current_head + size;
    
    
    this->allocated_ = this->current_head - this->head;
    
    return return_ptr;
}
