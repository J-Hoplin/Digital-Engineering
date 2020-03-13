#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<memory.h>
#define size_arr 100
//프로젝트 속성 - C/C++ - 전처리기 부분에 _CRT_SECURE_NO_WARNINGS 를 넣어주었습니다.

void XOR_F(char CRC_Val,char GCODE_Val, int index, char remainder[])
{

	if (CRC_Val == GCODE_Val)
	{
		remainder[index] = 48;//0의 ASCII : 48
	}
	else
	{
		remainder[index] = 49;//1의 ASCII : 49
	}
}

int count_remainder(char *remain)
{
	int total = 0;
	int count = 0;
	while (remain[count] == 48 || remain[count] == 49)
	{
		total++;
		count++;
	}
	return total;
}

void add_zero(char *arr, char *arr2, int length)
{
	int count = 0;
	int index = strlen(arr);
	char zero[size_arr]; 

	for (; count < length; count++)
	{
		zero[count] = 48;
	}
	zero[count] = NULL;
	strcat(arr, zero);
}

void del_zero(char *remainder,int *index_CRC, char *bin,char *sum_CRC, char *Generation_Code,char *remaind_cpy)
{
	int index_count = 0;
	int count2 = 0;
	int total_index = strlen(remainder);
	//0개수 세기
	while (remainder[index_count] == 48)
	{
		index_count++;
	}
	int index_count_cpy = index_count;
	//값내리기
	for (; count2 < index_count_cpy; count2++)
	{
		remaind_cpy[count2] = remainder[count2];
	}
	remaind_cpy[count2] = NULL;
	for (; index_count < total_index; index_count++)
	{
		remainder[index_count - index_count_cpy] = remainder[index_count];
		count2++;
	}
	remainder[index_count - index_count_cpy] = NULL;
	int index = *index_CRC;
	static int plus = 0;
	for (index_count = 0; index_count < index_count_cpy; index_count++)
	{
		sum_CRC[index_count] = bin[index + plus + index_count];
	}
	plus += index_count;
	sum_CRC[index_count] = NULL;
	strcat(remainder, sum_CRC);
}

void CRC_Cal(char *remainder,char *Generation_Code, int *index_CRC, char *bin)
{
	char sum_CRC[size_arr];
	char cpy_remaind[size_arr]; 
	char mem[size_arr];
	del_zero(remainder, index_CRC, bin, sum_CRC,Generation_Code,cpy_remaind);//11001
	while (1)
	{ 
		int inCRC = 0;
		int inGCODE = 0;
		int count;
		for (; inGCODE < strlen(Generation_Code); inGCODE++)
		{
			XOR_F(remainder[inCRC], Generation_Code[inGCODE], inGCODE, remainder);
			inCRC++;
		}
		del_zero(remainder,index_CRC,bin,sum_CRC,Generation_Code,cpy_remaind);
		
		int count_remain = count_remainder(remainder);
		int count_GCODE = count_remainder(Generation_Code);
		if (count_remain != count_GCODE)
		{
			int min = count_GCODE - count_remain;
			int min_1 = min - 1;
			for (count = 0; count < min; count++)
			{
				mem[min_1] = cpy_remaind[count_remainder(cpy_remaind) - 1 - count];
				min_1--;
			}
			mem[min] = NULL;
			strcat(mem, remainder);
			for (count = 0; count < count_remainder(mem); count++)
			{
				remainder[count] = mem[count];
			}
			remainder[count] = NULL;
			break;
		}
	}
}

void First_Cal(char *Generation_Code, char *bin, char *result)
{
	int index_CRC = 0;
	int index_GCODE = 0;
	char remainder[size_arr];
	int count;

	//초기 계산
	for (; index_GCODE < strlen(Generation_Code); index_GCODE++)
	{
		XOR_F(bin[index_CRC], Generation_Code[index_GCODE], index_GCODE,remainder);
		index_CRC++;
	}
	remainder[index_GCODE] = NULL; //00110
	CRC_Cal(remainder,Generation_Code ,&index_CRC,bin);
	for (count = 0; count < count_remainder(remainder); count++)
	{
		result[count] = remainder[count];
	}
	result[count] = NULL;
}
int main()
{
	char Generation_Code[] = "10011"; // This variable is for test case. You need to open file to solve this question.
	char bin[size_arr];
	char bin_cpy[size_arr];
	char n_data[size_arr] = { 0, };
	char result[size_arr] = { 0, };
	int length_GCODE = strlen(Generation_Code);

	FILE *fp;
	fp = fopen("data.txt", "r");
	fgets(bin, size_arr, fp);//fgets의 paraeter순서 : (배열, 배열크기, 파일포인터)

	memcpy(bin_cpy, bin, sizeof(bin));

	add_zero(bin,Generation_Code,length_GCODE);// 초기 CRC코드 뒤애 0붙이기
	First_Cal(Generation_Code, bin,result);// CRC Calculation
	strcat(bin_cpy, result);
	
	
	fp = fopen("A_B889047_윤준호.txt", "w");
	fprintf(fp, "The data with CRC is %s", bin_cpy);
	fclose(fp);
	return 0;
}
