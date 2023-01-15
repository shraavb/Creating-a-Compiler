#include "jc.h"
#include "token.h"
#include "stack.h"
token output;
short int load_array[4096];

int main(int argc, char* argv[]) {
	// While loop updates tokenc
	// While next_tokentrue
	if (argc > 1) {
	FILE *j_file = fopen(argv[1], "r");
	char* output_file = malloc((strlen(argv[1]) + 3)*sizeof(char));
	strcpy(output_file, argv[1]);
	output_file[strlen(argv[1]) - 1] = '\0';
	strcat(output_file,"asm");
	FILE *asm_file = fopen(output_file, "w");
	bool seen_defun = false;
	int num_cmp_func = 0;
	int if_count = 0;
	int while_count = 0;
	//REMOVE CODE 
	// char* curr_function = malloc(strlen("main") + 1);
	// strcpy(curr_function, "main");

		while (next_token(j_file, &output) == true) {
			print_token(j_file, output);

			//if literal then push 
			//else pop

			if (output.type == IF) {
				if_count++;
				push_if(if_count);
				push_if(-1);

				fprintf(asm_file, "; IF Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #-1\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "CMPI R4, #0\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRnp IF_%d\n", if_count);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRz ELSE_%d\n", if_count);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "IF_%d\n", if_count);
				//not needed

			}

			if (output.type == WHILE) {

				while_count++;
				push_while(while_count);

				fprintf(asm_file, "; while count %d\n", while_count);
				fprintf(asm_file, "; top_while %d\n", top_while());

				fprintf(asm_file, "; WHILE Token  \n");

				fprintf(asm_file, "        ");

				fprintf(asm_file, "WHILE_%d\n", while_count);

				fprintf(asm_file, "        ");

				fprintf(asm_file, "ADD R6, R6, #1\n");

				fprintf(asm_file, "        ");

				fprintf(asm_file, "LDR R3, R6, #-1\n");

				fprintf(asm_file, "        ");
				
				fprintf(asm_file, "CMPI R3, #0\n");

				fprintf(asm_file, "        ");

				fprintf(asm_file, "BRz ENDWHILE_%d\n", while_count);




				//calls writing function inside while - until end while
			}

			if (output.type == ENDWHILE) {
				fprintf(asm_file, "; while count %d\n", while_count);
				fprintf(asm_file, "; top_while %d\n", top_while());


				fprintf(asm_file, "; ENDWHILE Token  \n");
				
				//if (top_while() == -1) {
				//pop_while();
				fprintf(asm_file, "        ");
				fprintf(asm_file, "JMP WHILE_%d\n", top_while());
				//}
				
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ENDWHILE_%d\n", top_while());
				pop_while();


				fprintf(asm_file, "; top of while stack %d\n", top_while());
				fprintf(asm_file, "; while count %d\n", while_count);
				fprintf(asm_file, "; top_while %d\n", top_while());
			}

			if (output.type == ELSE) {
				fprintf(asm_file, "; ELSE Token\n");
				pop_if(); //remove -1
				fprintf(asm_file, "        ");
				fprintf(asm_file, "JMP ENDIF_%d \n", top_if());
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ELSE_%d\n", top_if());
				
				//NOT NEEDED
				// fprintf(asm_file, "        ");
				// fprintf(asm_file, "ADD R6, R6, #1 \n");
			}

			if (output.type == ENDIF) {
				fprintf(asm_file, "; ENDIF Token  \n");
				//if there wasn't an else then you want to print an else label before end if 
				if (top_if() == -1) {
					pop_if();
					fprintf(asm_file, "        ");
					fprintf(asm_file, "ELSE_%d\n", top_if());
				}

				//if there is an else then dont want to print else again 
				else {

				}

				fprintf(asm_file, "        ");
				fprintf(asm_file, "ENDIF_%d\n", top_if());
				pop_if();
			}

			if (output.type == MUL) {

				fprintf(asm_file, "; MUL Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "MUL R1, R1, R4 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #0 \n");
			}

			if (output.type == PLUS) {
				fprintf(asm_file, "; PLUS Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R1, R1, R4 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #0 \n");
			}

			if (output.type == MINUS) {
				fprintf(asm_file, "; MINUS Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "SUB R1, R1, R4 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #0 \n");
			}

			if (output.type == AND) {
				fprintf(asm_file, "; AND Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "AND R1, R1, R4 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #0 \n");
			}

			if (output.type == OR) {
				fprintf(asm_file, "; OR Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "OR R1, R1, R4 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #0 \n");
			}

			if (output.type == DIV) {
				fprintf(asm_file, "; DIV Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "DIV R1, R1, R4 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #0 \n");
			}

			if (output.type == MOD) {
				fprintf(asm_file, "; MOD Token  \n");
				//pop(load_array, &output, asm_file);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "MOD R1, R1, R4 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #0 \n");
			}


			if (output.type == LITERAL) { //not literal
				fprintf(asm_file, "; LITERAL Token  \n");
				int IMM9 = output.literal_value & 0x00FF;

				int IMM8 = (output.literal_value & 0xFF00) >> 8;
				fprintf(asm_file, "        ");
				fprintf(asm_file, "CONST R7, #%d\n", IMM9);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "HICONST R7, #%u\n", IMM8);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #-1\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R7, R6, #0\n");

			}

			if (output.type == NOT) { //not literal
				fprintf(asm_file, "; NOT Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R7, R6, #0 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "NOT R7, R7 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R7, R6, #0 \n");

			}

			if (output.type == LT) {
				num_cmp_func++;
				fprintf(asm_file, "; LT Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0\n");


				fprintf(asm_file, "        ");
				fprintf(asm_file, "CMP R2, R4\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRn ONE_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRzp ZERO_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ONE_%d CONST R1 #1 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "JMP GE_END_%d \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ZERO_%d CONST R1 #0 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "GE_END_%d STR R1, R6 #0 \n", num_cmp_func);

			}

			if (output.type == LE) {
				fprintf(asm_file, "; LE Token  \n");
				num_cmp_func++;
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "CMP R2, R4\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRnz ONE_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRp ZERO_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ONE_%d CONST R1 #1 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "JMP GE_END_%d \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ZERO_%d CONST R1 #0 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "GE_END_%d STR R1, R6 #0 \n", num_cmp_func);

			}

			if (output.type == EQ) {
				fprintf(asm_file, "; EQ Token  \n");
				num_cmp_func++;
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "CMP R2, R4\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRz ONE_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRnp ZERO_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ONE_%d CONST R1 #1 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "JMP GE_END_%d \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ZERO_%d CONST R1 #0 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "GE_END_%d STR R1, R6 #0 \n", num_cmp_func);

			}

			if (output.type == GE) {
				fprintf(asm_file, "; GE Token  \n");
				num_cmp_func++;
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "CMP R2, R4\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRzp ONE_%d \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRn ZERO_%d \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ONE_%d CONST R1, #1 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "JMP GE_END_%d \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ZERO_%d CONST R1 #0 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "GE_END_%d STR R1, R6 #0 \n", num_cmp_func);

			}

			if (output.type == GT) {
				fprintf(asm_file, "; GT Token  \n");
				num_cmp_func++;
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R4, R6, #0\n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, "CMP R2, R4\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRp ONE_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "BRnz ZERO_%d\n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ONE_%d CONST R1 #1 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "JMP GE_END_%d \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ZERO_%d CONST R1 #0 \n", num_cmp_func);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "GE_END_%d STR R1, R6 #0 \n", num_cmp_func);

			}

			if (output.type == ARG) {
				fprintf(asm_file, "; ARG Token  \n");
				//\t - indentation
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R5, #%d \n", 2 + output.arg_no);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #-1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R2, R6, #0 \n ");

				//fprintf(asm_file, "; n = %d", output.arg_no);

			}


			if (output.type == ROT) {
				fprintf(asm_file, "; ROT Token  \n");
				//pop(load_array, &output, asm_file);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R3, R6, #2\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #1\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #1\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R2, R6, #2\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R3, R6, #0\n");

				//fprintf(asm_file, "number of rot %d", while_count);
			}

			if (output.type == DUP) {
				fprintf(asm_file, "; DUP Token  \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #0\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #-1 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R2, R6, #0\n");
			}

			if (output.type == SWAP) {
				fprintf(asm_file, "; SWAP Token  \n");
				//pop(load_array, &output, asm_file);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R1, R6, #0\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "LDR R2, R6, #1\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R1, R6, #1\n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R2, R6, #0\n");

			}

			if (output.type == DROP) {
				fprintf(asm_file, "; DROP Token  \n");
				//pop(load_array, &output, asm_file);
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #1\n");

			}

			if (output.type == DEFUN) {
				seen_defun = true;

			}

			if (seen_defun == true && output.type == IDENT) {
				fprintf(asm_file, "        ");
				fprintf(asm_file, ".CODE \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, ".FALIGN \n");
				fprintf(asm_file, "%s\n", output.str);
				fprintf(asm_file, "        ");
				fprintf(asm_file, ";; Prologue \n");


				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R7, R6, #-2 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "STR R5, R6, #-3 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #-3 \n");
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R5, R6, #0 \n");

				//we do this for each literal
				// fprintf(asm_file, "        ");
				// fprintf(asm_file, "ADD R6, R6, #-1 \n");

				fprintf(asm_file, "        ");
				fprintf(asm_file, ";; Body \n");

				seen_defun = false;
				continue;
				}

			if (output.type == IDENT && seen_defun == false) {

				fprintf(asm_file, "; FUNCTION CALL Token  \n");



				fprintf(asm_file, "        ");
				fprintf(asm_file, "JSR %s \n", output.str);

				//expand stack for return value of function
				fprintf(asm_file, "        ");
				fprintf(asm_file, "ADD R6, R6, #-1 \n");

				//set seen defun to false
			}

			//return is not working

			if (output.type == RETURN) { //any other operation or token
				fprintf(asm_file, "        ");
				fprintf(asm_file, ";; Epilogue \n");

					fprintf(asm_file, "        ");
					fprintf(asm_file, "LDR R7, R6, #0 \n");
					fprintf(asm_file, "        ");
					fprintf(asm_file, "ADD R6, R5, #0 \n");
					fprintf(asm_file, "        ");
					fprintf(asm_file, "ADD R6, R6, #3 \n");
					fprintf(asm_file, "        ");
					fprintf(asm_file, "STR R7, R6, #-1 \n");
					fprintf(asm_file, "        ");
					fprintf(asm_file, "LDR R5, R6, #-3 \n");
					fprintf(asm_file, "        ");
					fprintf(asm_file, "LDR R7, R6, #-2 \n");


					fprintf(asm_file, "        ");
					fprintf(asm_file, "RET \n");
				//}
			}
		}
		free(output_file);
		fclose(j_file);
		fclose(asm_file);
		//REMOVED CODE
		//free(curr_function);

	}
}