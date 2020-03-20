#include<unicode/ustdio.h>
#include<unicode/ustring.h>
#include<unicode/uchar.h>
#include<iostream>
#include<stdlib.h>

int main(int argc, char **argv){
	const int N = 100;

	UChar *chars = (UChar*)malloc(N * sizeof(UChar));

	UFILE *out = u_get_stdout();
	UFILE *in = u_fadopt(stdin, NULL, NULL);
	if(!in){
		fputs("Couldn't get the stdandard input stream.\n", stderr);
		return EXIT_FAILURE;
	}
	u_fgets(chars, N, in);
	int len = u_strlen(chars);
	for(int i = 0; i < len - 1; i++){
		UCharCategory cat = (UCharCategory)u_charType(chars[i]);
		if(cat == U_LOWERCASE_LETTER || cat == U_UPPERCASE_LETTER)
			std::cout << "C ";
		else
			std::cout << "X ";
		u_fputc(chars[i], out);
 	  	u_fputc('\n', out);
	}
	u_fclose(in);
	u_fclose(out);
	return EXIT_SUCCESS;
}
