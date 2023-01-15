#include "stack.h"
//Updating stack 
int elseif[250];
int endif[250];
int whileif[250];


void push_if(int if_count) {
	int i = 248;
	while(i != -1) {
		elseif[i + 1] = elseif[i];
		endif[i + 1] = endif[i];
		i--;
	}
	elseif[0] = if_count;
	endif[0] = if_count;
	//return if_count;
}

void pop_if() {
	int i = 0;
	//int top_of_stack = elseif[0];
	while(i != 249) {
		elseif[i] = elseif[i + 1];
		endif[i] = endif[i + 1];
		i++;
	}
	elseif[i] = 0;
	endif[i] = 0;
}

int top_if() {
	int top_of_stack = elseif[0];
	return top_of_stack;
}

void push_while(int while_count) {
	int i = 248;
	while(i != -1) {
		whileif[i + 1] = whileif[i];
		i--;
	}
	whileif[0] = while_count;
}

void pop_while() {
	int i = 0;
	//int top_of_stack = elseif[0];
	while(i != 249) {
		whileif[i] = whileif[i + 1];
		i++;
	}
	whileif[i] = 0;
}

int top_while() {
	int top_of_stack = whileif[0];
	return top_of_stack;
}




