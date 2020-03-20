# Robust tokenisation --Apertium

## Coding Challenge

[classify-symbols.c](https://github.com/GavinWz/Apertium/blob/master/classify-symbols.c) is the previous version, which is wrong because of my misunderstanding of the [Coding Challenge](http://wiki.apertium.org/wiki/Ideas_for_Google_Summer_of_Code/Robust_tokenisation).    

At the suggestion of mentor Tino Didriksen, I used the ICU and C++ to complete my code.

[classify-symbols.cpp](https://github.com/GavinWz/Apertium/blob/master/classify-symbols.cpp) is the latest version of it. 

[classify-symbols.cc](https://github.com/GavinWz/Apertium/blob/master/classify-symbols.cc) is the update version of classify-symbol.cpp. There is no major changes, all are the little details. Besides, I used u_fadopt() instead of u_finit() to initialize the UFILE input stream to avoid mixing I/O by transferring the file stream ownership.

### Compile
To compile this code, first make sure the ICU environment is available, and then compile it with the following command:
```
c++ -o classify-symbols classify-symbols.cpp `pkg-config --libs --cflags icu-uc icu-io`
```
After compiling, we can get an executable file "classify-symbols".
### Run
Enter ``echo "This! Is a tešt тест ** % test." | ./classify-symbols`` to run and test the code, and then get the result.

The executable file "classify-symbols" is the result of my compilation on Linux, and there is a picture of the test results of my code.

![result](https://github.com/GavinWz/Apertium/blob/master/result.png)
