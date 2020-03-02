#include<unicode/ustdio.h>
#include<unicode/ustring.h>
#include<unicode/uchar.h>
#include<iostream>
#include<stdlib.h>

#define N 100

int main(int argc, char **argv){
	UChar *chars = (UChar*)malloc(N * sizeof(UChar));
	UFILE *out, *in;
	UCharCategory cat;
	int i, len;

	out = u_get_stdout();
	in = u_finit(stdin, NULL, NULL);
	u_fgets(chars, N, in);
	len = u_strlen(chars);
	for(i = 0; i < len - 1; i++){
		cat = (UCharCategory)u_charType(chars[i]);
		if(cat == U_LOWERCASE_LETTER || cat == U_UPPERCASE_LETTER)
			std::cout << "C ";
		else
			std::cout << "X ";
		u_fputc(chars[i], out);
 	  	u_fputc('\n', out);
	}
}
