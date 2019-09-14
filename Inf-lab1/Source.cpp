#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;
FILE *fileInput, *fileOutput;
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
	int realPart = 0, IntPart = 0;
	int systemBasis;

	fopen_s(&fileInput, "input1.txt", "r");
	fopen_s(&fileOutput, "output1.txt", "w");
	fscanf(fileInput, "%d\n", &systemBasis);
	while (!feof(fileInput))
	{
		fscanf(fileInput, "%i,%i\n", &IntPart, &realPart);
		char *ret = Translate_IntPart_From10(systemBasis, IntPart);
		fprintf(fileOutput, "%s", (Translate_IntPart_From10(systemBasis, IntPart)));

		if (realPart != 0)
		{
			fprintf(fileOutput, ",%s", Translate_RealPart_From10(systemBasis, realPart));
		}
		fprintf(fileOutput, "\n");
	}
	fclose(fileOutput);
	fclose(fileInput);
}



void TranslateTo10()
{
	char *intPart = new char;
	char *fullNumber = new char;
	string fullNumberString;
	string realPart = "";
	int systemBasis;
	FILE *fileInput, *fileOutput;

	fopen_s(&fileInput, "input2.txt", "r");
	fopen_s(&fileOutput, "output2.txt", "w");
	while (!feof(fileInput))
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
			fprintf(fileOutput, "%f\n", resultNumber);
		}
		else
		{
			fprintf(fileOutput, "%d\n", (int)resultNumber);
		}
	}
	fclose(fileOutput);
	fclose(fileInput);
}

int main()
{
	TranslateFrom10();
	TranslateTo10();
}