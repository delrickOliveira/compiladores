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
		if (c)
		{
			char buffer[255];
			FILE* file = fopen(argument, "r");
			FILE* outFile = fopen(OUTFILENAME, "w");
			if (file && outFile)
			{
				float result;
				char resultString[MAXDIGITSNUM];
				while (fgets(buffer, 255, file))
				{
					result = evaluate(buffer);
					sprintf(resultString, "%f", result);
					strcat(resultString, "\n");
					fputs(resultString, outFile);
				}
				fclose(file);
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

    Returns:
    float -> result of the operation
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
                // in case actual operator has bigger precedence than 
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

	while (!isEmpty(operators))
	{
		float prev = pop(values);
		float operator = pop(operators);
		if (!isEmpty(operators))
		{
			float prevOperator = peek(operators);
			if (getPrecedence((int)operator) > getPrecedence((int)prevOperator))
			{
				calculateSentence(prev, val, (int)operator, &val);
				push(values, val);
			}
			else
			{
				float beforePrev = pop(values);
				prevOperator = pop(operators);
				float result;
				calculateSentence(beforePrev, prev, (int)prevOperator, &result);
				push(operators, operator);
				push(values, result);
				push(values, val);
				val = pop(values);
			}
		}
		else
		{
			calculateSentence(prev, val, (int)operator, &val);
		}
	}

	return val;
}