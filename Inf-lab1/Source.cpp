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

int TranslateTo10(char *charArray, int arraySize, int systemBasis)
{
	int resultInt = 0;
	for (int i = arraySize - 1, j = 0; i > 0; i--, j++)
	{
		resultInt += CharToInt(charArray[i]) * pow(systemBasis, j);
	}

	int resultInt;
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


void TranslateFrom10(int r)
{
	int realPart = 0, IntPart = 0;

	fopen_s(&fileInput, "input.txt", "r");
	fopen_s(&fileOutput, "output.txt", "w");
	while (!feof(fileInput))
	{
		//fscanf(fileInput, "%i,%i\n", &IntPart, &realPart);
		//char *ret = Translate_IntPart_From10(r, IntPart);
		//fprintf(fileOutput, "%s", (Translate_IntPart_From10(r, IntPart)));

		//if (realPart != 0)
		//{
		//	fprintf(fileOutput, ",%s", Translate_RealPart_From10(r, realPart));
		//}
		//fprintf(fileOutput, "\n");

		//TODO TranslateTo10()

	}
	fclose(fileOutput);
	fclose(fileInput);
}

int main()
{
	int r;
	cout << "Enter number system: ";
	cin >> r;
	TranslateFrom10(r);
}