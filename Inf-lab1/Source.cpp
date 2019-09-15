#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
FILE* fileInput, * fileOutput1, *fileOutput2, *fileOutputM ;
using namespace std;

struct Stack {
	char data[200];
	int size = 0;
};

void push(Stack* stack, const char value)
{
	stack->data[stack->size] = value;
	stack->size++;

}

char pop(Stack* stack) {
	if (stack->size == 0) {
		exit(0);
	}
	stack->size--;
	return stack->data[stack->size];
}

bool IsEmpty(Stack stack)
{
	return stack.size == 0;
}

char IntToChar(int number)
{
	if (number > 9)
	{
		return 65 + (number - 10);
	}
	else
	{
		return number + '0';
	}
}
int CharToInt(char letter)
{
	if (letter >= '0' && letter <= '9')
	{
		return letter - '0';
	}
	else
	{
		return letter - 'A' + 10;
	}
}

char* Translate_RealPart_From10(int r, int Real)
{
	Stack stack1;
	double  realPart, s = 10.0, real, mod;
	int intPart = Real, count = 0;

	while (intPart != 0) {
		intPart /= 10;
		count++;
	}
	s = pow((double)s, count);
	realPart = (double)Real / s;

	modf((double)(realPart * r), &real);
	char *returnReal = new char[5];
	int i = 0;
	while (real != 0)
	{
		mod = realPart * r;
		realPart = mod - real;
		returnReal[i] = IntToChar(mod);
		modf((double)(realPart * r), &real);
		i++;
	}
	returnReal[i] = '\0';
	return returnReal;

}

char* Translate_IntPart_From10(int r, int Integer)
{
	Stack stack;
	int intPart, residue;
	do
	{
		intPart = Integer / r;
		residue = Integer % r;
		push(&stack, IntToChar(residue));
		Integer = intPart;
	} while (intPart != 0);

	int stackSize = stack.size;
	char *returnInt = new char[stackSize];
	int i = 0;
	while (!IsEmpty(stack))
	{
		returnInt[i] = pop(&stack);
		i++;
	}

	returnInt[i] = '\0';
	return returnInt;
}


void TranslateFrom10()
{
	//FILE *fileInput, *fileOutput;
	int realPart = 0, IntPart = 0;
	int systemBasis;


	fscanf(fileInput, "%d\n", &systemBasis);
	char symbol;

	do
	{
		fscanf(fileInput, "%i,%i\n", &IntPart, &realPart);
		char *ret = Translate_IntPart_From10(systemBasis, IntPart);
		fprintf(fileOutput1, "%s", (Translate_IntPart_From10(systemBasis, IntPart)));

		if (realPart != 0)
		{
			fprintf(fileOutput1, ",%s", Translate_RealPart_From10(systemBasis, realPart));
		}
		fprintf(fileOutput1, "\n");
		symbol = fgetc(fileInput);
	} while (symbol != '/');

}



void TranslateTo10()
{
	char* intPart = new char;
	char* fullNumber = new char;
	string fullNumberString;
	string realPart = "";
	int systemBasis;

	char symbol;

	do
	{
		fscanf(fileInput, "%d %s", &systemBasis, fullNumber);
		string fullNumberString = fullNumber;
		int commaPosition = fullNumberString.find(',');
		int lowerDegree = 0;
		if (commaPosition != -1)//double
		{
			lowerDegree = commaPosition - fullNumberString.length() + 1;
			fullNumberString.erase(commaPosition, 1);
		}

		double resultNumber = 0;
		for (int i = fullNumberString.length() - 1, j = lowerDegree; i >= 0; i--, j++)
		{
			resultNumber += CharToInt(fullNumberString[i]) * pow(systemBasis, j);
		}
		if (lowerDegree < 0)
		{
			fprintf(fileOutput2, "%f\n", resultNumber);
		}
		else
		{
			fprintf(fileOutput2, "%d\n", (int)resultNumber);
		}
		symbol = fgetc(fileInput);
	} while (symbol != '/');
}

void Multiply()
{
//	FILE *fileInput, *fileOutput;

	

	char *fullNumber1 = new char [sizeof(char*)];
	char *fullNumber2 = new char[sizeof(char*)];
	int systemBasis;
	unsigned char result[100];
	char symbol;

	do
	{
		fscanf(fileInput, "%d %s %s", &systemBasis, fullNumber1, fullNumber2);


		string fullNumberString1 = fullNumber1;
		int commaPosition1 = fullNumberString1.find(',');
		int lowerDegree = 0;
		if (commaPosition1 != -1)//double
		{
			lowerDegree += commaPosition1 - fullNumberString1.length() + 1;
			fullNumberString1.erase(commaPosition1, 1);
		}

		string fullNumberString2 = fullNumber2;
		int commaPosition2 = fullNumberString2.find(',');
		if (commaPosition2 != -1)//double
		{
			lowerDegree += commaPosition2 - fullNumberString2.length() + 1;
			fullNumberString2.erase(commaPosition2, 1);
		}


		int length1 = fullNumberString1.length();

		int length2 = fullNumberString2.length();

		for (int i = 0; i < length1 + length2; i++)
		{
			result[i] = 0;
		}
		for (int i = length2 - 1; i >= 0; i--)
		{
			for (int j = length1 - 1; j >= 0; j--)
			{
				result[j + i + 1] += (char)(CharToInt(fullNumberString1[j]) * CharToInt(fullNumberString2[i]));
				if (result[j + i + 1] > systemBasis - 1) {
					result[i + j] += result[j + i + 1] / systemBasis;
					result[j + i + 1] %= systemBasis;
				}

			}		
			result[length1 + i] = IntToChar(result[length1 + i]);
		}
		result[length1 + length2] = '\0';
		for (int i = 0; i < length1; i++)
		{
			result[i] = IntToChar(result[i]);
		}
			   
		if (lowerDegree != 0)
		{
			for (int i = length1 + length2; i >= length1 + length2 + lowerDegree; i--)
			{
				result[i + 1] = result[i];
			}
			result[length1 + length2 + lowerDegree] = ',';
		}

		fprintf(fileOutputM, "%s\n", result);
		symbol = fgetc(fileInput);
	} while (symbol != '/');

}

int main()
{
	fopen_s(&fileInput, "input1.txt", "r");
	fopen_s(&fileOutput1, "output1.txt", "w");
	fopen_s(&fileOutput2, "output2.txt", "w");
	fopen_s(&fileOutputM, "outputMyltiply.txt", "w");
	TranslateFrom10();


	TranslateTo10();

	Multiply();

	fclose(fileInput);
	fclose(fileOutput1);
	fclose(fileOutput2);
	fclose(fileOutputM);
}