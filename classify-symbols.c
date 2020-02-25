#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define N 100000

int main(int argc, char **argv)
{
	wchar_t string_uncd[N];
	while(_getws(string_uncd))
	{
		int len = wcslen(string_uncd);
		for(int i = 0; i < len; i++)
		{
			int judge = 0;
		    if((string_uncd[i] < 'A' || (string_uncd[i] > 'Z' && 
				 string_uncd[i] < 'a') || string_uncd[i] > 'z'))
				wprintf(L"X %hc\n", string_uncd[i]);
			
			else
				wprintf(L"C %hc\n", string_uncd[i]);
		}
	}
	return 0;
}
