## My Idea of Tokenization Flow Path

It is mainly divided into several processes:

1. Generate transducers based on dictionary content

    Before reading the standard input stream of characters, lt-proc will open the compiled dictionary "apertium-zho.zho.bin", create a class object **fstp** of class FSTProcessor and  initialize a class object **current_state** of class **State** by **FSTProcessor: : initAnalysis** function (fst_processor. cc: 1150).

    In the **FSTProcessor::load**(fst_processor. cc: 845) function, the part of the word information such as \<n>\<adj> , are stored in "**slexicinv**"(vector<wstring>) through the **Alphabet::read** function (Alphabet. cc: 152), and the unicode value of the word and its negative weight in the dictionary are stored in **slexic**( map<wstring, int, Ltstr> ).Then program load the dictionary and generate all the transducers.  Transducer details are stored in the transducers(map < wstring TransExe, Ltstr >). The first parameter key is the transducer name of type wstring, and the second parameter value is the transducer operation variable of type TransExe.  An important information in TransExe class is  the vector of **Node** class object **node_list**, Node class detailed information contained in the transducers.

2. Generate transition for each transducer

    "current_state" is initialized in the **FSTProcessor::calcInitial** function (fst_processor.cc: 646). The program iterates over each transducer to generate a TNodeState object for them, which is stored in the**state** -a vector of TNodeState -. TNodeState
    Class contains transitions for recording lexical information

3. Read the words in the standard input stream

    The lexical analysis is start at Processor: : analysis () (fst_processior. Cc: 1284).

    The program reads the words in the standard input stream one by one through the **readAnalysis**(fst_processor.cc: 242) function, and stores the Unicode values and weights of the read words in the **sequence**(vector<pair<int, double>>)through the **State::apply**(state.cc: 101) function.

4. Query the part of speech information of the words read in the transitions

    The current_state reconstruction. In **State::apply**, based on the Unicode values of the characters read,  the program searches in transitions for the corresponding word information and a value array of the words' part of speech tags, and save them in **current_state.transitions[0]**.

    In **epsilonClosure**(state.cc: 302) function reads the current_state. Transitions [0], the tag in the array to save all the tags to the sequence in the container.At this point, the tokenization is complete

    Then the **current_state.transitions[0]** will be read in the **epsilonClosure**(state.cc: 302) function, and all tags of the tag value array will be saved in **sequence** list(*vector<pair<int, double>>). At this point, the tokenization is complete.

5. Output

    The program collates the input characters and their lexical tag values in the State::filterFinals function, record the characters that match the obtained Unicode value, and restore the corresponding tag from slexicinv, saving the result to the wstring **lf**(lexical form).Finally flush the output buffer.