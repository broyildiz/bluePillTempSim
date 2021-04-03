#include <stdio.h>
#include <string.h>

#define SIZE 512
#define MAX_ARGS 10

char str[SIZE];
char *arg_pointer_buffer[MAX_ARGS];
int arg_cnt;

char single_arg[100];

int main()
{
	memset(str, 0, sizeof(str));
	printf("Give input:\t");
	scanf("%s", str);
	printf("\n");
	
	
	char delim[2] = ","; 	// This string will be used to parse the main input string
	char *token;			// This pointer will hold current parsed string
	memset(arg_pointer_buffer, '\0', sizeof(arg_pointer_buffer));
	arg_cnt = 0;

	/* get the first token */
	token = strtok(str, delim);

	/* walk through other tokens */
	while( token != NULL ) {
		printf( " %s\n", token );
		arg_pointer_buffer[arg_cnt++] = token;
		token = strtok(NULL, delim);
	}

	int i;
	for(i = 0; i < arg_cnt; i++)
	{
		printf("Arg pointer buffer [%d] = %s\n", i, arg_pointer_buffer[i]);
	}
	
	for(i = 0; i < arg_cnt; i++)
	{
		strcpy(single_arg ,arg_pointer_buffer[i]);
		printf("single_arg  = %s\n", single_arg);
	}
}
