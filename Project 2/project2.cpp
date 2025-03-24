#include <iostream>
using namespace std;

class Chip {
private:
    char _chipType; //Character that denotes the type of Chip object
    string _id; //String object that denotes the ID of the Chip object
    Chip* _input1; //A pointer to a Chip Object that denotes the first Input Chip
    Chip* _input2; //A pointer to a Chip Object that denotes the second Input Chip
    Chip* _output; //A pointer to a Chip Object that denotes the Output Chip
    double _inputValue; //Double that holds the value that will be given to other Chips in order to execute their functions
public:
    //Constructor
    Chip(char type, const string& id);
    //Setters
    void setInput1(Chip* inputChip);
    void setInput2(Chip* inputChip); //Will be NULL for Negation Chips and Output Chips
    void setOutput(Chip* outputChip); //Will be NULL for Output Chips
    void setInputValue(int inputValue); //Sets the Input Values for the Input Chips of the circut
    void compute(); //Recursive method that preforms the necessary operations based on Chip types

    void display() const; //Displays the Chip object's information
    string getID() const; //Returns the Chip ID
    double getValue(); //Returns the value of the Chip
    //Destructor
    ~Chip();
};

Chip::Chip(char type, const string& id){
    //Sets the necessary variables of the Chip object to match the paramaters that were passed.
    _chipType = type;
    _id = id;
}

void Chip::setInput1(Chip *inputChip){
    _input1 = inputChip; //Makes the first Input Chip point to the Input Chip reference that was passed to it.
}

void Chip::setInput2(Chip* inputChip) {
    _input2 = inputChip; //Makes the second Input Chip point to the Input Chip reference that was passed to it.
}

void Chip::setOutput(Chip* outputChip) {
    _output = outputChip; //Makes the Output Chip point to the Input Chip reference that was passed to it.
}

void Chip::setInputValue(int inputValue) {
    _inputValue = inputValue; //Sets the input value of the Input Chips to be their proper value so that calculations can be preformed
}

void Chip::compute() {
    //Check if its an I type chip, if so recursion done.
    //Check if the first input chip has been solved, if it hasn't execute its compute method.
    //Check if the second input chip exists. If it does, check if it has been solved, then execute the compute method if it hasn't
    //Once both input chips have been handled, preform the proper operation on the two input values they provide and store it in this Chip object.
    if (_chipType == 'I') return; //Base case, nothing further needs to be done if it is an I type Chip
    (*_input1).compute();   //Execute the Compute method on the first Input Chip of the current Chip, every Chip type besides the base case type will have an input Chip to call this on
    if (_input2 != NULL) (*_input2).compute(); //Executes the Compute method if there is a second Input Chip for the current Chip
    if (_chipType == 'A') (_inputValue = (*_input1).getValue() + (*_input2).getValue()); //Preforms addition using the input values if it is an Addition Chip
    if (_chipType == 'S') (_inputValue = (*_input1).getValue() - (*_input2).getValue()); //Preforms subtraction using the input values if it is a Subtraction Chip
    if (_chipType == 'M') (_inputValue = (*_input1).getValue() * (*_input2).getValue()); //Preforms multiplication using the input values if it is a Multiplication Chip
    if (_chipType == 'D') (_inputValue = (*_input1).getValue() / (*_input2).getValue()); //Preforms division using the input values if it is a Division Chip
    if (_chipType == 'N') (_inputValue = -(*_input1).getValue()); //Preforms negation on the input value if it is a Negation Chip
    if (_chipType == 'O') cout << "The output value from this circuit is " << (*_input1).getValue() << endl; //Displays the output from the circiut if its an Output Chip
}

void Chip::display() const {
    cout << _id << ", "; //Prints the ID of the chip followed by a comma, every Chip object displays this.

    //Case for Input Chips
    if (_chipType == 'I') {
        cout << "Output = " << (*_output).getID() << endl; //Prints the Output Chip that the Input Chip is connected to
    }
    //Case for Output Chips
    else if (_chipType == 'O') {
        cout << "Input 1 = " << (*_input1).getID() << endl; //Prints the Input Chip that the Output Chip is connected to
    }
    //Case for all other Chip types
    else {
        cout << "Input 1 = " << (*_input1).getID() << ", "; //Prints the first Input Chip that the given Chip is connected to
        if (_input2 != NULL) cout << "Input 2 = " << (*_input2).getID() << ", "; //Prints the second Input Chip that the given Chip is connected to, if it exists
        else cout << "Input 2 = None, "; //If there is no second Input Chip, print that instead
        cout << "Output = " << (*_output).getID() << endl; //Prints the Output Chip that the given Chip is connected to
    }
}

string Chip::getID() const {
    return _id; //Returns the ID of the Chip
}

double Chip::getValue() {
    return _inputValue; //Returns the input value of the Chip
}

Chip::~Chip() {} //Destructor for the Chip class, nothing in the class needs to be handled so there is nothing inside it.

int main() {
    //Put necessary variables below here
    string chipID; //Stores the ID of the Chips that are read in from the file
    char commandType; //Stores the type of command that will be preformed by the given Chips
    int chip1Index; //Stores the index of the first Chip that is read in from the command
    int chip2Index; //Stores the index of the second Chip that is read in from the command
    bool input1Filled = false; //Stores a bool value that denotes if the first input has been filled when reading in the commands and making connections between the Chips.
    int inputValue; //Stores the value for each of the Input Chips of the circut
    int outputChipIndex; //Stores the index of the Output Chip so that unnecessary searching is avoided, and to ensure that the display method for the Chips is called properly

    int numChips; //int to store the number of chips in the file
    Chip** allChips; //Array of pointers to Chip objects
    int numCommands; //int to store the number of commands in the file

    cin >> numChips; //Reads in the number of chips
    allChips = new Chip*[numChips]; //Creates the array based on the number of chips in the file

    //Reads in each of the chips and stores then in the array.
    for (int i = 0; i < numChips; i++) {
        cin >> chipID;
        allChips[i] = new Chip(chipID[0], chipID); //Stores a pointer to a Chip object made using the information from chipID at the index i in the allChips array.
    }
    
    cin >> numCommands; //Reads in the number of commands

    //Works through the list of commands and establishes the proper connections based on the commands
    for (int i = 0; i < numCommands; i++) {
        cin >> commandType; //Reads the type of Command that will be preformed and stores it to determine how to store the given Chips

        cin >> chipID; //Reads in the ID of the first Chip

        //Works through the allChips array list to find out which index position has an object that matched the ID of the Chip being read in
        for (int index = 0; index < numChips; index++) {
            if ((*allChips[index]).getID() == chipID) chip1Index = index; //Stores the index for the Chip in chip1Index so connections can be made later
        }
        //Case for if the commandType is for adding connections between chips.
        if (commandType == 'A') {
            cin >> chipID; //Reads in the ID for the second Chip in the command. Only occurs in this command type as other command types only have 1 Chip in the line

            //Works through the allChips array list to find out which index position has an object that matched the ID of the Chip being read in
            for (int index = 0; index < numChips; index++) {
                if ((*allChips[index]).getID() == chipID) chip2Index = index; //Stores the index for the Chip in chip2Index so connections can be made later
            }

            (*allChips[chip1Index]).setOutput(allChips[chip2Index]); //Sets the output for the first Chip read in to be the second Chip in the command line

            //Case that executes if the second chip is a Negation Chip or an Output Chip
            if ((chipID[0] == 'N') || chipID[0] == 'O') {
                (*allChips[chip2Index]).setInput1(allChips[chip1Index]); //Sets the first Input Chip for the Negation Chip to be the Chip at chip1Index
                (*allChips[chip2Index]).setInput2(NULL); //Sets the second Input Chip to NULL as Negation and Output Chips only have 1 Input Chip
            }
            //Case for all other Chip Types
            else {
                //Checks if the first input of the Chip has been filled
                //If it hasn't then set the Chip at chip1Index to be the first Input Chip for the second Chip in the command.
                if (!(input1Filled)) {
                    (*allChips[chip2Index]).setInput1(allChips[chip1Index]);
                    input1Filled = true; //Sets the value of input1Filled to true so that the next line will store the new Input Chip in the second Input Chip position
                }
                //If it has then set the Chip at chip1Index to be the second Input Chip for the Output Chip in the command.
                else {
                    (*allChips[chip2Index]).setInput2(allChips[chip1Index]);
                    input1Filled = false; //Sets the value of input1Filled to false so that the next line will be reset for the next Output Chip
                }
            }
        }
        //Executes if the commandType is an Input command
        if (commandType == 'I') {
            cin >> inputValue; //Reads in the input value for the Input Chip and stores it in an int variable
            (*allChips[chip1Index]).setInputValue(inputValue); //Sets the input value for the Input Chip so that calculations can be preformed
        }
        //Executes if the commandType is an Output command
        if (commandType == 'O') {
            (*allChips[chip1Index]).setOutput(NULL); //Sets the Output of the Output Chip to NULL as it will have no Output Chip associated with it
            outputChipIndex = chip1Index; //Stores the index of the Output Chip of the Circut so that the Connections can be properly displayed at the end
        }
    }

    cout << "Computation Starts" << endl;
    (*allChips[outputChipIndex]).compute(); //Executes the compute method on the Output Chip of the circiut

    cout << "***** Showing the connections that were established" << endl;
    //Call the display method on each chip object that was created as long as it isn't an Output Chip. This is to ensure the Output Chip is displayed at the end
    for (int i = 0; i < numChips; i++) {
        if (i != outputChipIndex) (*allChips[i]).display();
    }
    (*allChips[outputChipIndex]).display(); //Calls the display method for the Output Chip

    //Preforms the necessary delete operations to take care of the dynamically created array of pointers.
    for (int i = 0; i < numChips; i++) {
        delete allChips[i];
    }
    delete[] allChips;

    return 0;
}

/*
LLM Usage Documantation:

    -Prompt 1: "Why am I being told that the definition for the constructor for my c++ class can't be found despite me having wrote it?"
        -Rationale: My program was telling me that the definition for my constructor couldn't be found despite me clearly seeing it there, so I gave
        chatGPT the subsection of my code that was causing issues and asked it for help. The reccomended change that it gave me, to add a semicolon to
        the end of my class definition, immidiately fixed my problem and reminded me that class definitions need to end with a semicolon in c++.

    -Prompt 2: "How do I get the first character of a string in c++?"
        -Rationale: I know how you can break a string apart and get specific characters from it in Java, but I wasn't sure which of those ways carried over to c++. In
        order to be safe I decided to ask the LLM how it would handle getting the first character of a string. Upon seeing that I could use [] like I do in Java, I 
        implemented that into my program so that I could call the constructor for the Chip class usinf the information gotten from it.

    -Prompt 3: "How would you write a c++ function for a class called Chip that contains pointers to up to three other Chip objects, that would display the information 
    for the given object in a format like "A100, Input 1 = I1, Input 2 = I2, Output = M200"?"
        -Rationale: Looking for some help with deciding on how to start my display function, I prompted a LLM to write me a function with the specifications above. It
        wrote something that was much different than what I ended up writing, but in the end I was able to decide that the easiest way to handle display was by
        incrementally printing it to cout in the order given in the examples, using if statements as necessary to display the proper output.

    -Prompt 4: "How would you recursively work through a circuit of chips, starting from the output chip, until you reach the input chips which will let you solve 
    the previous Chips?"
        -Rationale: When first starting on my Compute method I looked to the LLM for help with beginning to think recursively as I would need to in order to write 
        a function that would work. The simple program that was wrote helped me to determine how to begin coding the Compute method as I figured out how I would
        handle the base case in this program and it helped me determine how I would handle cases like Negation Chips where one of the Input Chips is NULL.

    -Promt 5: "When writing a recursive function in c++, should you include a base case if it isn't necessary for your program to be called an additional time 
    to reach it? As in instead of calling the function when you know the base case has been reached to prove it, you don't make that call and work with the knowledge 
    that the base case was reached."
        -Rationale: When I was writing the Compute method for this program I noticed that if I checked if the Inputs for a Chip were Input Chips before calling the 
        function again, then I could avoid making a function call. I decided to promt a LLM to see if it thought this was a good idea, and upon doing so I realized
        that making that change would make it harder to read my code and follow my logic. It also helped me realize that even if I could, its generally safer to include
        the base case in the function so that no unforseen errors may occur.

    -Prompt 6: "What is the best way to negate a double value in c++?"
        -Rationale: I was unsure how exactly the best way to handle negating the double value given to Negation Chips, so I prompted a LLM to tell me how it would. It told
        me that using the negation symbol (-) was the best way to handle it, so I implemented that into my program.

    -Prompt 7: "Why might a function working with doubles be returning a number like 9.56363e-299?"
        -Rationale: I was running into an issue where the value I was expecting from the Compute method was not what I was expecting, and was instead a value like above. Upon
        reviewing the list of possible reasons that the LLM gave me from this prompt, and looking closer at my code. I realized that I never called the Compute method in the
        main class. After remedying this I changed the line that displayed the output value of the circiut from in the main function to inside the Compute method instead.

    -Prompt 8: "What is the best way to delete an array of pointers which is initialized like "int** intArray = new int*[10]"?"
        -Rationale: In order to preform the necessary cleanup of dynamiclly created objects at the end of the program, I prompted a LLM for the way that it would do it. Upon
        reviewing the code and remembering what we talked about in class because of it, I realized that they were the same and promptly used that way to handle garbage collection.

    -Prompt 9: "What is a Segmentation Fault?"
        -Rationale: I had never encountered a segmentation fault before so I prompted a LLM to help me understand what it might mean. Upon doing so I learned that segmentation faults
        occur when there are problems with the way memory is being handled by the code. Further review of my code helped me then realize that the way I had wrote for the program to delete
        dynamically created objects was causing an error in the program that wasn't being displayed on my machine. After changing the way deletion was handled at the end of my program, the
        autograder marked my program as working.

    Incremental Development:
        The first step to developing this program was to write the necessary methods of the Chip class for me to begin working on setting up my main function to read in the
        information from the files. This involved writing almost everything that was given in the project outline, the only exception was the compute method which I saved for later.
        After a small hiccup with my constructor, which a prompt to a LLM was able to help me solve, I was able to move on to writing the main function. In the main function I
        wrote the portion that added each of the Chips to the allChips array, which a prompt to a LLM was able to help me with determining how to best get a char for the
        constructor with the string I pulled from cin, and then got to work on getting the portion covering the commands wrote once I was sure it worked. It didn't take me
        much longer to write out the code for reading in the commands once I understood how they worked, and upon using the display method to check that it was working
        as intended I moved onto the tricker part of this project.

        The compute method is where most of my prompts came from as it was where I needed the most assistance with solving unforseen issues and with understanding how
        would be best to set it up in c++. Once I had an understanding of how I should set it up, it didn't take me long to write a working method, but I was encountering
        an odd result that I wasn't sure how it was happening at first. I prompted a LLM about what might be causing me to be getting a weird e value, and using the
        information I learned from that I ended up being able to determine that I hadn't ever called the compute method in my main function. Upon realizing this I rewrote the
        compute method and the main funtion so that this mistake would be corrected and avoided. Once I made that change the program began properly displaying the files, and
        from there I just ensured that the garbage being created from Dynamically creating objects was being cleaned up, and I prompted a LLM to help me with writing that code
        in the most efficient way possible.

---------------------------

Debugging and Testing Plan:

    -Test 1: Ensuring the constructor and display methods works correctly.
        To do this I wrote the constructor for the Chip class, the display method for the Chip class, and all other necessary methods in order to implement it. I then constructed
        and connected different Chip objects in my main function and called the display method on each of them. After ensuring that the proper information was being displayed for
        a couple different sets of Chips, I moved on to working on the main function.

    -Test 2: Ensuring the getters and setters return / store the correct information depending on the function being called.
        These tests tie into the testing done above as I used getters inside my Display method, and I needed to use my setters to connect the constructed Chips to test the
        Display method. I was sure that they were working as intended as they worked for setting up my display method.

    -Test 3: Ensuring the allChips array properly saved the Chip objects.
        In order to be sure that the information about the Chips from the file was being read correctly, I wrote some code to read them into the allChips array in the
        main function. I then connected the chips to random Chips in the array to ensure that they were all read in, and in the proper order. I tested with each file input
        that was given to us and compared them to the output. I saw that the Output Chip was out of place on the third file, so I added a variable that tracks the index of the
        Output Chip so that I can ensure that it always displays last.

    -Test 4: Ensuring that the Chip objects are properly connected to each other based on the input.
        After writing the code that handles reading in the different commands for the Chips and preforming the necessary connections, I tested it by running the program with
        each of the input files that we were given. I then compared the output of the program to the output file, and moved onto the next portion of code after seeing that
        they both were.

    -Test 5: Ensuring that each part of the Compute method works properly.
        Once I was done writing the Compute method I set about cheking its output. At first I was getting a very incorrect value because I hadn't called the Compute method
        before checking the output value like I thought I had. Upon prompting a LLM for help, and rewriting my code so that I would avoid that problem happening again, I
        ran the Compute method using each of the input files as input, and found that it came to the correct result on each of them.

    -Test 6: Ensuring that the entire program functions as expected when given one of the input files.
        Now that I had the whole program wrote, I tested it with each of the input files and ensured that the output matched the output files, and once I saw that it did
        I knew I had a working program.

    -Issue 1: The Display Method was encountering an error and not displaying correctly when working with Negation Chips.
        The Display method was calling incorrectly for Negation Chips as I had forgotten to set the first Input Chip, and only set the second Input Chip to NULL. This meant that
        the method had nothing to call there and the program was terminating instead. Upon closer inspection of my code I realized this mistake and swiftly corrected it, after 
        which my Display method functioned perfectly.

    -Issue 2: Getting a value such as "9.56363e-299" from the compute method when I was expecting a double value.
        I incorrectly believed that the Compute method of the Chip class was giving me an incorrect value upon being executed. It was upon promting a LLM about it, and
        rewriting my Compute method so that it would display the input value at each step that I realized that I never called the Compute method in the main function.
        Once I called it there and moved the output value display from the main function to the compute method, the program began workign as intended.

    -Issue 3: Autograder telling me segmentation fault when running my program.
        After turning my code into the autograder it told me that it was encountering a segmentation fault and I was unsure why exactly that was happening. After prompting
        a LLM I was able to learn more about segmentation faults and what exactly they meant. Once I knew that I was able to change the way my code handled deleting the dynamically
        crated objects, which fixed the segmentation fault that was occuring.
*/