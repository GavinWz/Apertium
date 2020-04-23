# Robust tokenisation --Apertium

Idea: Robust tokenisation   
link: http://wiki.apertium.org/wiki/Ideas_for_Google_Summer_of_Code/Robust_tokenisation

## Coding Challenge

[classify-symbols.c](https://github.com/GavinWz/Apertium/blob/master/classify-symbols.c) is the ``previous version``, which is wrong because of my misunderstanding of the [Coding Challenge](http://wiki.apertium.org/wiki/Ideas_for_Google_Summer_of_Code/Robust_tokenisation).    

At the suggestion of mentor ``Tino Didriksen`` and ``Flammie``, I used the ``ICU`` and ``C++`` to complete my code.

[classify-symbols.cpp](https://github.com/GavinWz/Apertium/blob/master/classify-symbols.cpp) is the ``latest version`` of it. 

[classify-symbols.cc](https://github.com/GavinWz/Apertium/blob/master/classify-symbols.cc) is the ``update version`` of classify-symbol.cpp. There is no major changes, all are the little details. Besides, I used ``u_fadopt()`` instead of ``u_finit()`` to initialize the UFILE input stream to avoid ``mixing I/O`` by transferring the file stream ownership.

#### Compile

To compile this code, first make sure the ICU environment is available, and then compile it with the following command:
```
c++ -o classify-symbols classify-symbols.cpp `pkg-config --libs --cflags icu-uc icu-io`
```
After compiling, we can get an executable file "classify-symbols".

#### Run

Enter 
```
echo "This! Is a tešt тест `` % test." | ./classify-symbols
```
 to run and test the code, and then get the result.

The executable file "classify-symbols" is the result of my compilation on Linux, and there is a picture of the test results of my code.

![result](https://github.com/GavinWz/Apertium/blob/master/result.png?raw=true)

## My Idea of Tokenization Flow Path

It is mainly divided into several processes:

1. **Generate transducers based on dictionary content**

    Before reading the standard input stream of characters, lt-proc will open the compiled dictionary "apertium-zho.zho.bin", create a object ``fstp`` of class ``FSTProcessor`` and  initialize a object ``current_state`` of class ``State`` by ``FSTProcessor: : initAnalysis`` function (fst_processor.cc: 1150).

    Through the ``Alphabet::read`` function (Alphabet. cc: 152), program reads informations from the dictionary. The grammatical labels of the word information such as \<n>\<adj> are stored in "``slexicinv``"(vector\<wstring>). The negative of the slexicinv's indexes are regarded as the value of the labels. The words and their weights in the dictionary are stored in ``slexic``(map<wstring, int, Ltstr>).
    
    In the ``FSTProcessor::load``(fst_processor.cc: 845) function, program loads the dictionary and generate all the transducers. The transducers are stored in the ``transducers``(map<wstring, TransExe, Ltstr>). The first template parameter key is the transducer name of type wstring, and the second template parameter value is the transducer operating object of class ``TransExe``.  An important information in TransExe class is ``node_list`` -the vector of ``Node`` class object-. The  detail information and operating functions of transducers are contained in the Node and TransExe class.

2. **Generate transitions for each transducer**

    The ``State`` class object "``current_state``" is initialized in the ``FSTProcessor::calcInitial`` function (fst_processor.cc: 646). The program iterates over each transducer to generate some ``TNodeState`` objects for them, which are stored in the ``state`` -a vector of TNodeState-. TNodeState Class contains transitions for recording lexical information.

3. **Read the words in the standard input stream**

    The lexical analysis is start at ``Processor::analysis`` (fst_processior. cc: 1284).

    The program reads the Chinese words in the standard input stream one by one through the ``Processor::readAnalysis`` function(fst_processor.cc: 242), and stores the Unicode values and weights of the read words in the ``sequence``(*vector<pair<int, double>>)through the ``State::apply`` function(state.cc: 101).

4. **Query the part of speech information of the words read in the transitions**

    The current_state is rebuilt at here. In ``State::apply``(state.cc: 101), based on the words' Unicode values, the program searches in transitions for the corresponding word information and gets a integer value array of the grammatical labels, then the obtained words and labels are saved in ``current_state.where.transitions[0]``. The ``transitions``(map<int, Dest>) stores the outgoing transitions.

    Then the ``current_state.where.transitions[0]`` is read in the ``State::epsilonClosure`` function(state.cc: 302), and all labels of the label value array and their weights are saved in ``State::sequence`` list(*vector<pair<int, double>>). At this point, the tokenization is complete.

5. **Output**

    The ``State:: filterFinals`` function(state.cc: 564) iterates over the ``sequence`` list, reads the Unicode values and label values and converts them to the string they refer to by the ``Alphabet::getSymbol`` function(alphabet: 223). 

    The ``Alphabet::getSymbol`` function restores the Unicode value of the character to a wstring, and then restores the labels corresponding to the label value from ``slexicinv``.

    Then the result is saved to the wstring ``lf``. Finally print the standard output buffer.
