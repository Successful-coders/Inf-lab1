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

string Translate_RealPart_From10(int r, int real)
{
	double  realPart, mod;
	int intPart = real, count = 0;

	while (intPart != 0) {
		intPart /= 10;
		count++;
	}

	realPart = (double)real / pow(10.0, count);;

	int i = 0;
	string returnReal;
	mod = realPart;
	while (i != 5)
	{
		mod = mod * r;
		int intPart = mod;
		if (intPart != 0)
		{
			mod = modf(mod, &realPart);
		}

		returnReal += to_string(intPart);
		i++;
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

string Multiply(int systemBasis, string fullNumber1, string fullNumber2)
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

	string resultS(reinterpret_cast<char*>(result), sizeof(result));
	return resultS;
}

string Sum(int systemBasis, string fullNumberSum1, string fullNumberSum2)
{
	double resultDouble = TranslateTo10(systemBasis, fullNumberSum1) + TranslateTo10(systemBasis, fullNumberSum2);
	int intPart = (int)resultDouble;
	int realPart = (int)(resultDouble * 1000000) - (intPart * 1000000);
	string result = TranslateFrom10(systemBasis, intPart, realPart);

	return result;
}

int main()
{
	int systemBasis, intPart, realPart = 0;

	FILE* fileInput1;
	fopen_s(&fileInput1, "input1.txt", "r");
	fopen_s(&fileOutput1, "output1.txt", "w");
	fscanf(fileInput1, "%i", &systemBasis);
	while (!feof(fileInput1))
	{
		fscanf(fileInput1, "%i,%i\n", &intPart, &realPart);

		fprintf(fileOutput1, "%s\n", TranslateFrom10(systemBasis, intPart, realPart).c_str());
	}
	fclose(fileInput1);
	fclose(fileOutput1);

	char *fullNumber = new char[256];
	fopen_s(&fileInput2, "input2.txt", "r");
	fopen_s(&fileOutput2, "output2.txt", "w");
	while (!feof(fileInput2))
	{
		fscanf(fileInput2, "%d %s", &systemBasis, fullNumber);

		string fullnumberS(fullNumber);
		fprintf(fileOutput2, "%f\n", TranslateTo10(systemBasis, fullnumberS));
	} 
	fclose(fileInput2);
	fclose(fileOutput2);


	char* fullNumber2 = new char[256];
	fopen_s(&fileInput3, "input3.txt", "r");
	fopen_s(&fileOutput3, "output3.txt", "w");
	while (!feof(fileInput3))
	{
		fscanf(fileInput3, "%d %s %s", &systemBasis, fullNumber, fullNumber2);

		string fullnumberS(fullNumber);
		string fullnumberS2(fullNumber2);
		string result = Multiply(systemBasis, fullnumberS, fullnumberS2);

		fprintf(fileOutput3, "%s\n", result.c_str());
	}
	fclose(fileInput3);
	fclose(fileOutput3);


	fopen_s(&fileInput4, "input4.txt", "r");
	fopen_s(&fileOutput4, "output4.txt", "w");
	while (!feof(fileInput4))
	{
		fscanf(fileInput4, "%d %s %s", &systemBasis, fullNumber, fullNumber2);

		string fullnumberS(fullNumber);
		string fullnumberS2(fullNumber2);

		string result = Sum(systemBasis, fullnumberS, fullnumberS2);

		fprintf(fileOutput4, "%s\n", result.c_str());
	}
	fclose(fileInput4);
	fclose(fileOutput4);
}