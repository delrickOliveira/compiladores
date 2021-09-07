#include <stdio.h>
#include <string.h>

// Created modules
#include "Stack.h"

#define TRUE 1
#define FALSE 0
#define OUTFILENAME "out.txt"
#define MAXDIGITSNUM 21

enum Operator
{
	sum, subtraction, times, division, openParenthesis, closeParenthesis
};

int isDigit(char c);
int isOperator(char c);
int getPrecedence(int operator);
int calculateSentence(float val1, float val2, int operator, float* result);
float convertToEnumOperation(char c);
float evaluate(char string[]);

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		char* argument = argv[1];
		char* c = strstr(argument, ".txt");
		if (c) // if it's a file
		{
			char buffer[255];
			FILE* inputFile = fopen(argument, "r");
			FILE* outFile = fopen(OUTFILENAME, "w");
			
			if (inputFile && outFile) // if the two files are sucessfuly linked, input files exists and out file was successfully created 
			{
				float result;
				char resultString[MAXDIGITSNUM];
				while (fgets(buffer, 255, inputFile)) // reading line after line until EOF
				{
					result = evaluate(buffer);
					sprintf(resultString, "%f", result);
					strcat(resultString, "\n");
					fputs(resultString, outFile);
				}
				fclose(inputFile);
				fclose(outFile);
				printf("Success ! Result is in %s file .\n", OUTFILENAME);
				return 1;
			}
			else
			{
				printf("File not found!");
				return 0;
			}
		}
		else
		{
			printf("result of expression is: %f \n", evaluate(argument));
			return 1;
		}
	}
	else
	{
		printf("No argument was found!");
		return 0;
	}
}

/* 
    Check if char is a digit

    Parameters:
    char c -> character that will be evaluated

    Returns: 
    int -> 1 for true and 0 for false.
*/
int isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return TRUE;
	else
		return FALSE;
}

/*
    Check if char is an operator.
    
    Parameters:
    char c -> character that will be evaluated

    Returns: 
    int -> 1 for true and 0 for false.
*/
int isOperator(char c)
{
	char operators[] = { '+', '-', '*', '/', '(', ')' };
	unsigned short lenght = sizeof(operators) / sizeof(operators[0]);
	for (unsigned short i = 0; i < lenght; i++)
	{
		if (c == operators[i]) return TRUE;
	}
	return FALSE;
}

/*
    Checks precedence of operator. 

    Parameters:
    char c -> character that will be evaluated

    Returns:
    int -> value representing the precedence of operator. Bigger the value higher it is.
*/
int getPrecedence(int operator)
{
	switch (operator)
	{
	case sum:
	case subtraction:
		return 1;
	case times:
	case division:
		return 2;
	case openParenthesis:
	case closeParenthesis:
		return 3;
	default:
		return -1;
	}
}

/* 
    Calculates the result of a sentence. Ex: 3+3 

    Parameters:
    int val1 -> first value of sentence
    int val2 -> second value of sentence
    int operator -> operator to apply
	float * result -> reference to out result variable

    Returns:
    int -> number indicating the sentence was sucessfull calculated or not
*/
int calculateSentence(float val1, float val2, int operator, float* result)
{
	switch (operator)
	{
	case sum:
		*result = val1 + val2;
		return TRUE;

	case subtraction:
		*result = val1 - val2;
		return TRUE;

	case times:
		*result = val1 * val2;
		return TRUE;

	case division:
		*result = val1 / val2;
		return TRUE;

	default:
		return FALSE;
	}
}

/* 
    Calculates the result of a sentence. Ex: 3+3 

    Parameters:
    char c -> char to be converted

    Returns:
    float -> value representing the char in enum
*/
float convertToEnumOperation(char c)
{
	switch (c)
	{
	case '+':
		return sum;
	case '-':
		return subtraction;
	case '*':
		return times;
	case '/':
		return division;
	case '(':
		return openParenthesis;
	case ')':
		return closeParenthesis;
	default:
		return -1;
	}
}


/*
	Evaluates the expression in string and after give the result

	Parameters:
	char [] string  -> string to be evaluated. Ex "3+3-5"

	Return:
	float -> result of given expression

*/
float evaluate(char string[])
{
	Stack* values, * operators;
	unsigned lenght = strlen(string);
	values = createStack(lenght);
	operators = createStack(lenght);

	float val = 0;
	int pos = 0;

	while (pos < lenght)
	{
		char spot = string[pos];
        //mouting number if it's digit
		if (isDigit(spot))
		{
			val = (val * 10) + (float)(spot - '0');
		}
		else if (isOperator(spot))
		{
			float enumOperator = convertToEnumOperation(spot);
			if (enumOperator == openParenthesis)
			{
				push(operators, enumOperator);
				val = 0;
			}
			else if (isEmpty(values))
			{
                // if values is empty it's the beggining of sentence so, just push value and operator
				push(values, val);
				push(operators, enumOperator);
				val = 0;
			}
			else if (enumOperator == closeParenthesis)
			{
				push(values, val);
                // solve everything before open parenthesis
				while (peek(operators) != openParenthesis)
				{
					val = pop(values);
					enumOperator = pop(operators);
					float prevValue = pop(values);
					calculateSentence(prevValue, val, (int)enumOperator, &val);
					push(values, val);
				}
				pop(operators); // pop the open parenthesis operator
				pop(values); // the top of values is already in variable val, so pop it
			}
			else
			{
				float prevOp = peek(operators);
                // in case actual operator has bigger precedence than previous operator just push it to stack, else
				// calculate the previous operation and store result and operator
				if (getPrecedence((int)enumOperator) > getPrecedence((int)prevOp) || prevOp == openParenthesis)
				{
					push(values, val);
					push(operators, enumOperator);
					val = 0;
				}
				else
				{
					float prevVal = pop(values);
					prevOp = pop(operators);
					calculateSentence(prevVal, val, (int)prevOp, &prevVal);
					push(values, prevVal);
					push(operators, enumOperator);
					val = 0;
				}
			}
		}
		pos++;
	}

	//After finishing evaluating the string, use remaing operations with remaining values
	while (!isEmpty(operators))
	{
		float prev = pop(values);
		float operator = pop(operators);
		if (!isEmpty(operators))
		{
			float prevOperator = peek(operators); // just looking the top, but not removing it
			// comparing precedence of top two operators
			if (getPrecedence((int)operator) > getPrecedence((int)prevOperator))
			{
				calculateSentence(prev, val, (int)operator, &val);
				push(values, val);
			}
			else
			{
				float beforePrev = pop(values);// working with two top values of stack, val stay the same
				prevOperator = pop(operators); //poping it if it has higher precedence
				float result;
				calculateSentence(beforePrev, prev, (int)prevOperator, &result);
				push(operators, operator); // push operator with lower precedence
				push(values, result);// storing the result
			}
		}
		else
		{
			calculateSentence(prev, val, (int)operator, &val);
		}
	}

	return val;
}