#include "token.h"

short int load_array[4096];

token_type previous_token = BAD_TOKEN;

bool next_token(FILE *j_file, token *output){

	int fscanf_result;
	char nextString[250];
	int fget_result = 0;
		fscanf_result = fscanf(j_file, "%s", nextString);
	int value;
	while (fscanf_result == 1) {
		//printf("%s", nextString);

		if (previous_token == DEFUN) { // how to check if identifier doesn't exist


			output -> type = IDENT;
			previous_token = IDENT;
			strcpy(output -> str, nextString);
			return true;
		}

		if (nextString[0] == ';') {
			while ((char) fget_result != '\n') {
				fget_result = fgetc(j_file); //read till new line character
				//printf("after comment %c\n", (char) fget_result);
			}
			fget_result = 0;
			fscanf_result = fscanf(j_file, "%s", nextString);
			//printf("nextString %s\n", nextString);
			continue;
		}

		// if (strcmp(nextString, ";;") == 0) {
		// 	while ((char) fget_result != '\n') {
		// 		fget_result = fgetc(j_file); //read till new line character
		// 	}
		// 	fscanf_result = fscanf(j_file, " %s ", nextString);
		// 	printf("nextString %s\n", nextString);
		// 	continue;
		// }

		if (nextString[0] =='0'&& nextString[1] == 'x') {
			
			sscanf(nextString, "%x", &value);

			output -> type = LITERAL;
			output -> literal_value = value;
			strcpy(output -> str, nextString);
			return true;
			
		}

		if (sscanf(nextString, "%d", &value) == 1) {
			output -> literal_value = value;
			strcpy(output -> str, nextString);
			output -> type = LITERAL;
			return true;
		}

		if (strcmp(nextString, "*") == 0) {
			output -> type = MUL;
			strcpy(output -> str, "MUL");
			return true;
		}

		if (strcmp(nextString, "+") == 0) {
			output -> type = PLUS;
			strcpy(output -> str, "PLUS");
			return true;
		}

		if (strcmp(nextString, "-") == 0) {
			output -> type = MINUS;
			strcpy(output -> str, "MINUS");
			return true;
		}
		if (strcmp(nextString, "/") == 0) {
			output -> type = DIV;
			strcpy(output -> str, "DIV");
			return true;
		}
		if (strcmp(nextString, "%") == 0) {
			output -> type = MOD;
			strcpy(output -> str, "MOD");
			return true;
		}

		if (strcmp(nextString,"defun") == 0) {
			//token DEFUN;
			output -> type = DEFUN;
			strcpy(output -> str, "defun");
			previous_token = DEFUN;
			return true;
		}

		if (strcmp(nextString,"return") == 0) {
			//token DEFUN;
			output -> type = RETURN;
			strcpy(output -> str, "return");
			return true;
		}

		if (strcmp(nextString,"and") == 0) {
			//token DEFUN;
			output -> type = AND;
			strcpy(output -> str, "and");
			return true;
		}

		if (strcmp(nextString,"or") == 0) {
			//token DEFUN;
			output -> type = OR;
			strcpy(output -> str, "or");
			return true;
		}

		if (strcmp(nextString,"not") == 0) {
			//token DEFUN;
			output -> type = NOT;
			strcpy(output -> str, "not");
			return true;
		}

		if (strcmp(nextString,"lt") == 0) {
			//token DEFUN;
			output -> type = LT;
			output -> literal_value = 12; 
			output -> arg_no = 2;
			strcpy(output -> str, "lt");
			return true;
		}

		if (strcmp(nextString,"le") == 0) {
			//token DEFUN;
			output -> type = LE;
			output -> literal_value = 13; 
			output -> arg_no = 2;
			strcpy(output -> str, "le");
			return true;
		}

		if (strcmp(nextString,"eq") == 0) {
			//token DEFUN;
			output -> type = EQ;
			output -> literal_value = 14; 
			output -> arg_no = 2;
			strcpy(output -> str, "eq");
			return true;
		}

		if (strcmp(nextString,"ge") == 0) {
			//token DEFUN;
			output -> type = GE;
			output -> literal_value = 15; 
			output -> arg_no = 2;
			strcpy(output -> str, "ge");
			return true;
		}
		if (strcmp(nextString,"gt") == 0) {
			//token DEFUN;
			output -> type = GT;
			output -> literal_value = 16; 
			output -> arg_no = 2;
			strcpy(output -> str, "gt");
			return true;
		}
		if (strcmp(nextString,"if") == 0) {
			//token DEFUN;
			output -> type = IF;
			strcpy(output -> str, "if");
			return true;
		}
		if (strcmp(nextString,"else") == 0) {
			//token DEFUN;
			output -> type = ELSE;
			strcpy(output -> str, "else");
			return true;
		}
		if (strcmp(nextString,"endif") == 0) {
			//token DEFUN;
			output -> type = ENDIF;
			strcpy(output -> str, "endif");
			return true;
		}
		if (strcmp(nextString,"while") == 0) {
			//token DEFUN;
			output -> type = WHILE;
			strcpy(output -> str, "while");
			return true;
		}
		if (strcmp(nextString,"endwhile") == 0) {
			//token DEFUN;
			output -> type = ENDWHILE;
			strcpy(output -> str, "endwhile");
			return true;
		}
		if (strcmp(nextString,"drop") == 0) {
			//token DEFUN;
			output -> type = DROP;
			strcpy(output -> str, "drop");
			return true;
		}
		if (strcmp(nextString,"dup") == 0) {
			//token DEFUN;
			output -> type = DUP;
			strcpy(output -> str, "dup");
			return true;
		}
		if (strcmp(nextString,"swap") == 0) {
			//token DEFUN;
			output -> type = SWAP;
			strcpy(output -> str, "swap");
			return true;
		}
		if (strcmp(nextString,"rot") == 0) {
			//token DEFUN;
			output -> type = ROT;
			strcpy(output -> str, "rot");
			return true;
		}
		if (sscanf(nextString, "arg%d", &value) == 1) {
			//token DEFUN;
			output -> type = ARG;
			output -> arg_no = value;
			strcpy(output -> str, nextString);
			return true;
		}

		// if (strcmp(nextString,"bad_token") == 0) {
		// 	//token DEFUN;
		// 	output -> type = BAD_TOKEN;
		// 	strcpy(output -> str, "bad_token");
		// 	return true;
		// }

		//if (strcmp(nextString, ";;") != 0 && strcmp(nextString, ";") != 0) 

		if (nextString[0] != ';') {
			//printf("in IDENT loop");
			output -> type = IDENT;
			strcpy(output -> str, nextString);

			return true;
		}

		// else {

		// fscanf_result = fscanf(j_file, "%s", nextString);

		// }

	}

	return false;

}

void print_token (FILE* f, token to_print) {

	printf("%s \n", to_print.str);

}