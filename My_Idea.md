## My Idea of Tokenization Flow Path

It is mainly divided into several processes:

1. **Generate transducers based on dictionary content**

    Before reading the standard input stream of characters, lt-proc will open the compiled dictionary "apertium-zho.zho.bin", create a class object **fstp** of class **FSTProcessor** and  initialize a class object **current_state** of class **State** by **FSTProcessor: : initAnalysis** function (fst_processor.cc: 1150).

    In the **FSTProcessor::load**(fst_processor.cc: 845) function, the grammatical labels of the word information such as \<n>\<adj> are stored in "**slexicinv**"(vector\<wstring>) through the **Alphabet::read** function (Alphabet. cc: 152). The  negative of the vector indexes  are regarded as the value of labels. The Unicode value of the word and its weight in the dictionary are stored in **slexic**(map<wstring, int, Ltstr>).
    
    Then program load the dictionary and generate all the transducers.  The transducers are stored in the **transducers**(map < wstring TransExe, Ltstr >). The first template parameter key is the transducer name of type wstring, and the second template parameter value is the transducer operating object of class **TransExe**.  An important information in TransExe class is   **node_list** -the vector of **Node** class object-. The  detail information of transducers are contained in the Node class.

2. **Generate transitions for each transducer**

    The **State** class object "current_state" is initialized in the **FSTProcessor::calcInitial** function (fst_processor.cc: 646). The program iterates over each transducer to generate some **TNodeState** objects for them, which are stored in the **state** -a vector of TNodeState -. TNodeState Class contains transitions for recording lexical information.

3. **Read the words in the standard input stream**

    The lexical analysis is start at **Processor::analysis** (fst_processior. cc: 1284).

    The program reads the Chinese words in the standard input stream one by one through the **Processor::readAnalysis** function(fst_processor.cc: 242), and stores the Unicode values and weights of the read words in the **sequence**(vector<pair<int, double>>)through the **State::apply** function(state.cc: 101).

4. **Query the part of speech information of the words read in the transitions**

    The current_state is rebuilt. In **State::apply**(state.cc: 101), based on the Unicode values, the program searches in transitions for the corresponding word information and gets a integer value array of the grammatical labels, then the obtained words and labels are saved in **current_state.where.transitions[0]**. The **transitions**(map<int, Dest>) stores the outgoing transitions.

    Then the **current_state.where.transitions[0]** will be read in the **State::epsilonClosure** function(state.cc: 302), and all labels of the label value array and their weights will be saved in **State::sequence** list(*vector<pair<int, double>>). At this point, the tokenization is complete.

5. **Output**

    The **State:: filterFinals** function(state.cc: 564) iterates over the **sequence** list, reads and restores Unicode values and label values by the **Alphabet::getSymbol** function(alphabet: 223). 

    The **Alphabet::getSymbol** function restores the Unicode value of the character to a wstring, and then restores the labels corresponding to the label value from **slexicinv**.

    Then the result is saved to the wstring **lf**. Finally flush the standard output buffer.
