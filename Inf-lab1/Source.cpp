#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
FILE* fileInput1, * fileInput2, * fileInput3, * fileInput4, * fileOutput1, * fileOutput2, * fileOutput3, * fileOutput4;
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

string Translate_RealPart_From10(int r, int Real)
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
	string returnReal;
	while (real != 0)
	{
		mod = realPart * r;
		realPart = mod - real;
		returnReal += IntToChar(mod);
		modf((double)(realPart * r), &real);
	}

	return returnReal;
}
string Translate_IntPart_From10(int r, int Integer)
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
	string returnInt;

	while (!IsEmpty(stack))
	{
		returnInt += pop(&stack);
	}

	return returnInt;
}
string TranslateFrom10(int systemBasis, int IntPart, int realPart)
{
	string returnValue = Translate_IntPart_From10(systemBasis, IntPart);

	if (realPart != 0)
	{
		returnValue += "," + Translate_RealPart_From10(systemBasis, realPart);
	}

	return returnValue;
}

double TranslateTo10(int systemBasis, string fullNumber)
{
	int commaPosition = fullNumber.find(',');
	int lowerDegree = 0;
	if (commaPosition != -1)//double
	{
		lowerDegree = commaPosition - fullNumber.length() + 1;
		fullNumber.erase(commaPosition, 1);
	}

	double resultNumber = 0;
	for (int i = fullNumber.length() - 1, j = lowerDegree; i >= 0; i--, j++)
	{
		resultNumber += CharToInt(fullNumber[i]) * pow(systemBasis, j);
	}
	return resultNumber;
}

unsigned char* Multiply(int systemBasis, string fullNumber1, string fullNumber2)
{
	unsigned char result[100];

	int commaPosition1 = fullNumber1.find(',');
	int lowerDegree = 0;
	if (commaPosition1 != -1)//double
	{
		lowerDegree += commaPosition1 - fullNumber1.length() + 1;
		fullNumber1.erase(commaPosition1, 1);
	}

	int commaPosition2 = fullNumber2.find(',');
	if (commaPosition2 != -1)//double
	{
		lowerDegree += commaPosition2 - fullNumber2.length() + 1;
		fullNumber2.erase(commaPosition2, 1);
	}


	int length1 = fullNumber1.length();

	int length2 = fullNumber2.length();

	for (int i = 0; i < length1 + length2; i++)
	{
		result[i] = 0;
	}
	for (int i = length2 - 1; i >= 0; i--)
	{
		for (int j = length1 - 1; j >= 0; j--)
		{
			result[j + i + 1] += (char)(CharToInt(fullNumber1[j]) * CharToInt(fullNumber2[i]));
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

	return result;
}

double Sum(int systembasis, string fullNumberSum1, string fullNumberSum2)
{
	double result;
	double number1 = TranslateTo10(systembasis, fullNumberSum1);
	double number2 = TranslateTo10(systembasis, fullNumberSum2);
	result = number1 + number2;
	//TranslateFrom10(systembasis, result);
	return result;
}

int main()
{
	int systembasis, intPart, realPart = 0;

	FILE* fileInput1;
	fopen_s(&fileInput1, "input1.txt", "r");
	fopen_s(&fileOutput1, "output1.txt", "w");
	fscanf(fileInput1, "%i", &systembasis);
	while (!feof(fileInput1))
	{
		fscanf(fileInput1, "%i,%i\n", &intPart, &realPart);

		fprintf(fileOutput1, "%s\n", TranslateFrom10(systembasis, intPart, realPart).c_str());
	}
	fclose(fileInput1);
	fclose(fileOutput1);

	char *fullNumber = new char;
	fopen_s(&fileInput2, "input2.txt", "r");
	fopen_s(&fileOutput2, "output2.txt", "w");
	while (!feof(fileInput2))
	{
		fscanf(fileInput2, "%d %s", &systembasis, fullNumber);

		string fullnumberS(fullNumber);
		fprintf(fileOutput2, "%f\n", TranslateTo10(systembasis, fullnumberS));
	} 
	fclose(fileInput2);
	fclose(fileOutput2);


	char* fullNumber2 = new char;
	fopen_s(&fileInput3, "input3.txt", "r");
	fopen_s(&fileOutput3, "output3.txt", "w");
	while (!feof(fileInput3))
	{
		fscanf(fileInput3, "%d %s %s", &systembasis, fullNumber, fullNumber2);


		string fullnumberS(fullNumber);
		string fullnumberS2(fullNumber2);
		string result(reinterpret_cast<char*>(Multiply(systembasis, fullnumberS, fullnumberS2)));

		//fprintf(fileOutput3, "%s", result.c_str());
		fprintf(fileOutput3, "%s", Multiply(systembasis, fullnumberS, fullnumberS2));
	}
	fclose(fileInput3);
	fclose(fileOutput3);

	//string fullNumber1, fullNumber2;
	//fopen_s(&fileOutput2, "output2.txt", "w");
	//do
	//{
	//	fscanf(fileInput, "%d %s %s", &systembasis, fullNumber1, fullNumber2);
	//	fprintf(fileOutput1, "%s", Multiply(systembasis, fullNumber1, fullNumber2));
	//	symbol = fgetc(fileInput);
	//} while (symbol != '/');

	//string fullNumberSum1, fullNumberSum2;
	//fopen_s(&fileOutputM, "outputMultiply.txt", "w");
	//do
	//{
	//	fscanf(fileInput, "%d %s %s", &systembasis, fullNumberSum1, fullNumberSum2);
	//	fprintf(fileOutput1, "%s", Sum(systembasis, fullNumberSum1, fullNumberSum2));
	//	symbol = fgetc(fileInput);
	//} while (symbol != '/');

	//fclose(fileOutputM);
}