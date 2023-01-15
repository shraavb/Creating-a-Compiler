#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

void push_if(int if_count);

void pop_if();

int top_if();

void push_while(int while_count);

void pop_while();

int top_while();

#endif
