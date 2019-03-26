#include<stdio.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define size_arr 16

int bin_to_decimal(char input[])
{
	int result = 0;
	int cknum = 1;
	int count = strlen(input) -1;
	for (; count >= 0; count--)
	{
		if (input[count] == '1')
		{
			result += cknum;
		}
		cknum *= 2;
	}
	return result;
}

//거듭제곱 함수
int exponential(int a, int b)
{
	int count = 0;
	int result = 1;
	for (; count < b; count++)
	{
		result = result * a;
	}
	return result;
}

int hex_to_decimal(char input[])
{
	int result = 0;
	int check = 0;
	int index = strlen(input) - 1;
	for (; index >= 0; index--)
	{
		char op = input[index];
		if (op >= 48 && op <= 57)
		{
			result += (op - 48) * exponential(16, check);
		}
		else if (op >= 65 && op <= 70)
		{
			result += (op - (65 - 10)) * exponential(16, check);
		}
		else
		{
			result += (op - (97 - 10)) * exponential(16, check);
		}
		check++;
	}
	return result;
}

int decimal_to_bin(int input)
{
	long int result = 0;
	int bin = 1;
	int ckp = 0;
	while (input > 0)
	{
		ckp = input % 2;
		result += ckp * bin;
		input = input / 2;
		bin *= 10;
	}
	return result;
}

int main()
{
	char input_bin[size_arr];//입력된 2진수값
	char input_hex[size_arr];//입력된 16진수값

	int bin_to_decim = 0; 
	long int hex_to_decim = 0, decim_to_bin = 0;
	int count = 0;

	//2진수, 16진수 받기
	printf("Type a binary number :");
	scanf_s("%s", input_bin, size_arr);
	printf("Type a Hexademical number : ");
	scanf_s("%s", input_hex, size_arr);

	//2진법 -> 10진법 변환 함수
	bin_to_decim = bin_to_decimal(input_bin);
	//16진수 -> 10진수
	hex_to_decim = hex_to_decimal(input_hex);
	//10진수 -> 2진수
	decim_to_bin = decimal_to_bin(hex_to_decim);

	FILE *fp = fopen("B889047_윤준호.txt", "w");
	fprintf(fp,"Decimal number of %s is %d\n", input_bin, bin_to_decim);
	fprintf(fp,"Hexadecimal number of %s is %X\n", input_bin, bin_to_decim);
	fprintf(fp,"Decimal number of %s is %d\n", input_hex, hex_to_decim);
	fprintf(fp,"Binary number of %s is %d\n", input_hex, decim_to_bin);
	fclose(fp);
	return 0;
}
