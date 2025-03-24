#include <iostream>
#include <vector>
using namespace std;

//The exception classes for the MTree class
class MTreeException : public exception { };
class duplicateInsertion : public MTreeException { };
class NotFoundException : public MTreeException { };

template <class DT>
class MTree {
    protected:
        int _M;  //Maximum number of children per node
        vector<DT> values;  //Values stores in the node
        vector<MTree*> children;    //Pointers to child MTrees
        vector<DT> completeValueList;   //Vector used by the collect_values method so non-leaf nodes can build their complete vector without using a local variable
    public:
        MTree(int M);   //Constructor
        ~MTree();   //Destructor
        bool is_leaf() const;   //Checks if the current node is a leaf
        void insert(const DT& value);   //Insert a value into the MTree
        void split_node();  //Splits the node if it exceeds capacity
        MTree* find_child(const DT& value); //Find the correct child tree to follow
        bool search(const DT& value);   //Search for a value in the MTree
        void remove(const DT& value);   //Delete a value from the MTree
        void buildTree(vector<DT>& input_values);   //Builds the MTree
        vector<DT>& collect_values();   //Collects the values from all the leaf nodes
        bool find(DT& value);   //Search through the proper child nodes to check if a value is stored in the proper leaf node
};
//Constructor method
template <class DT>
MTree<DT>::MTree(int M) {
    _M = M; //Sets the M Value of the tree to be equal to what was passed. The Vectors are initialized on creation, so they don't need any additional handling
}
//Destructor method
template <class DT>
MTree<DT>::~MTree() {
    //Calls the delete method on each of the children of the current MTree
    for (int i = 0; i < children.size(); i++) {
        delete (children[i]);
    }
}
//Checks if the given node is a leaf node
template <class DT>
bool MTree<DT>::is_leaf() const {
    //Check if the children vector is empty, if it is then the node is a leaf node
    return children.empty();
}
//Inserts the given value into the proper leaf node and preforms splitting if necessary.
template <class DT>
void MTree<DT>::insert(const DT& value) {
    //Base case for if the node is a leaf node
    if ((*this).is_leaf()) {
        //Searches for the value in the values array of the current tree and throws a duplicateInsertion exception if that value is already in the tree.
        if ((*this).search(value)) {
            throw duplicateInsertion();
        }

        if (values.empty()) {
            //If the values vector doesn't contain any elements, then add value that was passed to the insert method to the end
            values.push_back(value);
        }
        else {
            //Initializes the elements necessary for the while loop to run
            int i = 0;
            bool indexFound = false;
            //Continues to iterate until the end of the list is reached, or the proper index is found.
            while ((i < values.size()) && (!indexFound)) {
                //Checks if the value is less than the element stored at the current index of the values vector, if so then sets indexFound to true
                if (value < values[i]) {
                    indexFound = true;
                }
                else {
                    //Increments the index if the proper position isn't found
                    i = i + 1;
                }
            }
            //Inserts the element at the proper position of the vector
            values.insert(values.begin() + i, value);
            //Informs the user that the insert was successful
            cout << "The value = " << value << " has been inserted." << endl;

            //Check if value vector size is greater than M - 1, if so splits the node
            if (values.size() >= _M) {
                (*this).split_node();
            }
        }
    }
    else {
        //Finds the proper child tree and calls the insert method on it using the given value
        (*(*this).find_child(value)).insert(value);
    }
}

//Spilts the node when it is full.
template <class DT>
void MTree<DT>::split_node() {
    if ((*this).is_leaf()) {
        //Collect the values from the values vector.
        vector<DT> splitVals = values;
        //Use the vector to call the build method and rebuild the tree.
        (*this).buildTree(splitVals);
    }
    else {
        //Collect the values from each of the leaf nodes of the tree and store them in a vector
        vector<DT> splitVals = (*this).collect_values();
        //Use the vector to call the build method and rebuild the tree.
        (*this).buildTree(splitVals);
    }
}

//Finds the proper child node to continue traversal down the tree for the given value.
template <class DT>
MTree<DT>* MTree<DT>::find_child(const DT& value) {
    //Works through the list of children nodes and finds the proper one to navigate to for the given value
    for (int i = 0; i < children.size(); i++) {
        //If the end of the children vector has been reached, then return the last child node
        if (i == (_M - 1)) {
            return children[i];
        }
        else {
            //Checks if the value being searched for is less than the value stored in the values vector at index i, if so then return the child node at i as its the proper subtree
            if (value <= values[i]) {
                return children[i];
            }
        }
    }
    //Returns a nullptr if there are no children in the list
    return nullptr;
}

//Searches the values vector of the MTree to see if the value is located within
template <class DT>
bool MTree<DT>::search(const DT& value) {
    //Searches through the values vector to see if the given value is located within it
    for (int i = 0; i < values.size(); i++) {
        //If the value is found, then return true
        if (value == values[i]) {
            return true;
        }
    }
    //If the value isn't found in the values vector, then return false
    return false;
}
//Navigates to the proper leaf node in the MTree and searches for the given value, if its there remove it otherwise throw and exception
template <class DT>
void MTree<DT>::remove(const DT& value) {
    //Executes if the given node is a leaf node
    if ((*this).is_leaf()) {
        //Initializes the values for the while loop
        int i = 0;
        bool indexFound = false;
        //Loops until either the end of the values vector is reached, or if the proper index to be removed from is found
        while ((i < values.size()) && (!indexFound)) {
            //If the value is found, set it indexFound to true
            if (value == values[i]) {
                indexFound = true;
            }
            //Increments the current index if the value isn't found
            else {
                i = i + 1;
            }
        }
        //If the element wasn't found in the vector, then throw a NotFoundException
        if (!indexFound) {
            throw NotFoundException();
        }

        //Remove the element at that index of the vector
        values.erase(values.begin() + i);
        //Informs the user that the value was removed
        cout << "The value = " << value << " has been removed." << endl;
    }
    //Executes if the current node isn't a child node
    else {
        //Calls the remove method on the proper child node with the given value
        (*(*this).find_child(value)).remove(value);
        //Rebuilds the tree after remove is called to ensure that it stays balanced.
        vector<DT> valsAfterRemoval = (*this).collect_values();
        (*this).buildTree(valsAfterRemoval);
    } 
}
//Builds the tree using the vector passed to the tree as its values
template <class DT>
void MTree<DT>::buildTree(vector<DT>& input_values) {
    //Clears the old information from the tree so the new info can be properly stored
    values.clear();
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
    children.clear();
    completeValueList.clear();
    //If input_value's size is less than or equal to M - 1, then the values are stored in the values vector
    if (input_values.size() <= (_M - 1)) {
        values = input_values;
    }
    else {
        //Finds the D value so that the split values and child trees can be properly stored.
        int D = (input_values.size() / _M);
        //Iterates through the Vector so that M-1 values are stored in the values vector
        for (int i = 0; i < _M; i++) {
            //Finds the start of the current set of values.
            int start = D * i;
            int end;
            //If its the last iteration then end will be equal to the end of the list
            if (i == (_M - 1)) {
                end = input_values.size() - 1;
            }
            //Otherwise determine the end value by adding the results from dividing to the start value and subtract by 1
            else {
                end = start + D - 1;
                //Push the element at the input_values vector at the end index to the end of the values vector
                values.push_back(input_values[end]);
            }
            //Creates the vector that will store the values to be passed to the proper child node
            vector<DT> child_values(input_values.begin() + start, input_values.begin() + end + 1);
            //Creates the child MTree with the given M value
            MTree<DT>* child = new MTree<DT>(_M);
            //Builds the tree using the child_values vector
            (*child).buildTree(child_values);
            //Pushes the created child tree to the rear of the children vector
            children.push_back(child);
        }
    }
}

template <class DT>
vector<DT>& MTree<DT>::collect_values() {
    //Clears the completeValueList vector to ensure that the returned vector is correct
    completeValueList.clear();

    //Return the values vector if the current node is a leaf node.
    if ((*this).is_leaf()) {
        return values;
    }

    //Go through each of the nodes in the children vector and collect the values from each of their leaf nodes
    for (int i = 0; i < children.size(); i++) {
        //Create a vector to store the info got from the current child node
        vector<DT> childValueList;
        childValueList = (*children[i]).collect_values();
        //Inserts the gotten vector into the end of the completeValueList vector
        if (!(childValueList.empty())) {
            completeValueList.insert(completeValueList.end(), childValueList.begin(), childValueList.end());
        }
    }
    //Return the complete value list vector
    return completeValueList;
}
//Method that checks if the given value is located within a leaf node in the MTree
template <class DT>
bool MTree<DT>::find(DT& value) {
    //Executes if the current node is a leaf node
    if ((*this).is_leaf()) {
        //Calls the search method using the given value and returns the result
        return (*this).search(value);
    }
    //Calls the find method on the proper child node and returns the result
    return (*(*this).find_child(value)).find(value);
}

int main() {
    int n;  //Number of numbers in the initial sorted array
    int MValue;
    int numCommands;
    char command;
    int value;

    //Read in n from the file
    cin >> n;

    vector<int> mySortedValues(n);

    //Read n numbers from the input and add them to the mySortedValues vector
    for (int i = 0; i < n; i++) {
        cin >> value;   //Read in the next number from the input
        mySortedValues[i] = value;    //Adds the input to the end of the mySortedValues vector
    }

    //Get the M value
    cin >> MValue;
    MTree<int>* myTree = new MTree<int>(MValue);

    //Build the tree
    (*myTree).buildTree(mySortedValues);

    cin >> numCommands; //Read the number of commands

    /************ Read each command Process ******************/
    for (int i = 0; i < numCommands; i++) {
        cin >> command; //Read the command type

        switch (command) {
            case 'I': {     //Insert
                cin >> value;
                try {
                    (*myTree).insert(value);
                }
                catch (duplicateInsertion& e) {
                    cout << "The value = " << value << " already in the tree." << endl;
                }
                break;
            }
            case 'R': {     //Remove
                cin >> value;
                try {
                    (*myTree).remove(value);
                }
                catch (NotFoundException& e) {
                    cout << "The value = " << value << " not found." << endl;
                }
                break;
            }
            case 'F': {     //Find
                cin >> value;
                if ((*myTree).find(value)) cout << "The element with value = " << value << " was found.";
                else cout << "The element with value = " << value << " not found.";
                cout << endl;
                break;
            }
            case 'B': {     //Build
                vector<int> myValues = (*myTree).collect_values();
                (*myTree).buildTree(myValues);
                cout << "The tree has been rebuilt." << endl;
                break;
            }
            default:
                cout << "Invalid command!" << endl;
        }
    }
    
    //Collects the values from the tree and displays them in a formatted manner
    vector<int> finalValueList = (*myTree).collect_values();
    cout << "Final list: ";
    for (int i = 0; i < finalValueList.size(); i++) {
        if ((i + 1) % 20 == 0) {
            cout << finalValueList[i] << endl;
        }
        else {
            cout << finalValueList[i] << " ";
        }
    }
    //Deletes the myTree MTree.
    delete myTree;
    return 0;
}


/*
LLM Usage Documentation:

    -Prompt #1: "Do you need to initialize a vector in the constructor to use it if you've included it in the class definition in c++?"
        -Rationale: As this was the first time I was working with vectors in c++ I had a couple questions that I needed answered while I was working on the code. In
        order to get these answers I turned to an LLM to see what it might say, and in doing so I was able to learn about the different ways you could initialize
        a vector in a class's constructor. The list of options that the LLM gave me helped me to pick the one that best fit the needs of this project, that being leaving it
        at its default.

    -Prompt #2: "What does this warning given by visual studio code mean? "reference to local variable 'valueList' returned [-Wreturn-local-addr]""
        -Rationale: This was the first time I had ever encountered an error like this, and as I was unsure as to what exactly it meant I decided to prompt the LLM to see
        what reasons there could be that I was getting it. After doing so I was able to determine that the reason this warning was occuring was because I had created the
        vector in the method and trying to return it after doing so would end up causing memory issues. Instead I placed the vector in the class definition which caused it to
        no longer be giving that error.

    -Prompt #3: "When you create a vector that initially contains n elements, does it initialize those elements to a default if no default value is given during creation?"
        -Rationale: When I had first tried displaying the vector that was returned by the collect_values method I had found that it had contained as many 0's at the beginning as it
        did elements in the list. In asking the LLM I was able to determine that the reason behind this was because vectors created with initial sizes have default elements placed
        at each of those indexes. A change to how I read in the initial list was enough to fix the problem I had been encountering.

    -Prompt #4: "How do I insert an element into a specific position of a vector in c++?"
        -Rationale: With this being the first time I had been working with vectors in C++ I was unsure how exactly I should insert an element into a vector once I had
        found the proper index position for it. Once I prompted the LLM I was able to find out a multitude of ways that you were able to insert an element into a vector
        and was able to pick the proper one to use for the given situation.

    -Prompt #5: "How do I remove an element at a specific position in a vector?"
        -Rationale: I was unsure of how to remove an element from a vector when I knew its index postion, so I went and prompted the LLM for how to do it. In doing so
        I was able to learn multiple ways to remove elements and was able to determine which of them was best for the scope of this project.

    -Prompt #6: "Why might my program be exiting instead of going the whole way through the removal method?"
        -Rationale: I was encountering problems with my removal method not executing all the way through so I went to the LLM to promt it to see what muight be causing this
        problem. After giving my method to the LLM to look over it was able to pinpoint a few possible reasons for this, and the one that it ended up beign was because I hadn't
        included an else statement after checking if the node was a leaf node, thus causing the leaf node to attempt to call the method which caused the program to exit.

    Incremental Development:
            The first step I took in developing this program was to begin by developing the outline of the project, this included copying the main function over as it was wrote in
        the project desription, writing the different exception classes that would be used by the program, and writing the class definition for the MTree class. Once I had all of
        that wrote I began to develop the project in increments based on what would be needed next. The first thing I knew I needed to work on was that I needed to ensure that
        the MTree could be built and that the values stored in each of the leaf nodes could be collected. To ensure this would be possible I first got the build and collect_values
        methods tested and working. This had some hiccups along the way with me having an incorrect list at first, but prompts to the LLM and adjustments to my code was enough to
        fix the list that was being returned so that it was correct.

            After this I began working on the next key part of this project, ensuring that values could be searched for and found within the list. To do this I wrote the 3 search
        methods used by the MTree class, the Find method, the Search method, and the find_child method. The reason I needed to do these next was because both the Insert and Remove
        methods needed to be able to search down the proper children nodes in order to attempt insertion or deletion on the proper leaf node. The code I had wrote seemed to work
        after I had adjusted the find_child method to use <= instead of <, but after writing and testing my insert and delete methods I noticed a few errors that were easy enough 
        to correct. The issue that I had encountered with these methods was that I hadn't been clearing the vectors I was using at the proper times, this was causing the MTree to
        have its values, children, and completeValuesList vectors to contain data that they had no reason to. Inserting a few lines to clear them, and to delete all the unnecessar 
        child trees, was enough to get my whole program functioning correctly.

---------------------------

Debugging and Testing Plan:

    -Test #1: Ensure that the MTree is being built correctly when the rebuild method is called.
        The first test that I did on the MTree class was to check and be sure that the tree was being built correctly. In order to do so I called the build method on the
        tree using the vector that I read in from the input value. I then called the collect_values method and stored the vector that was returned in a vector, and then
        displayed it. Once it was displayed I proceeded to check it against the list that was used as the input and ensured it was correct. I then proceeded to check with
        different M values and lists to ensure it worked properly.

    -Test #2: Ensuring the destructor works properly.
        With past projects having encountered errors because of my destructor causing segmentation faults, I put extra time into ensuring that there were none caused by
        this program. In order to do so I had the program print out a line saying the destructor worked properly, and once I saw it did so I knew that it was working properly.
    
    -Test #3: Ensuring that the find methods were working.
        After writing the 3 different methods for searching through the MTree I proceeded to test them by calling the Find method with multiple different values as the input,
        as the Find method uses eaach of the search functions at different points. I kept trying the Find method with more and more inputs until I was sure that they were all
        working.

    -Test #4: Ensuring the insert and remove methods threw their given exceptions when expected to.
        Before I wrote the insert and remove methods I first wrote the cases in which the exceptions would need to be thrown and checked to be sure that they were thrown
        when the conditions were being met. Once I was sure the exceptions were being properly thrown I moved onto writing the insert and remove methods themselves.

    -Test #5: Ensuring the insert function was working properly and that spillting was being preformed as intended.
        After I finished writing the insert function I attempted to insert values into the the MTree and then afterwards I called the collect_values method and then
        printed out the vector that was returned to be sure that the values had been inserted into the proper position, and to ensure that the split method wasn't causing any
        loss of data.

    -Test #6: Ensuring the remove function was working as intended.
        In order to test the remove method I preformed the same process that I had when testing the insert method, but this time I kept calling the remove method using different
        values that were in the list as input. Once I was sure that the vector that was being returned by the collect_values method was displaying properly after remove was called
        I began to move on to the next step of testing.

    -Test #7: Testing everything all together to ensure the program is functioning as it should.
        Once I was sure that each method was working individually I proceeded to test my MTree class using the different input files we had been given with the project. After I
        checked the different outputs with the corresponding output files and made some slight adjustments to my cout statements I knew that my program was working and was then able
        to turn it into gradescope.        

    -Issue #1: The vector was double the intended size and contained n number of 0s at the front.
        When I had first been building and checking the output of the MTree I found that the vector being returned contained a number of 0's at the front equal to the n value that
        had been read in. After prompting LLMs some and checking back over my code I was able to determine that the reason for this was because the way I had initialized the vector
        and read values in caused the values being read in to be appended to the end of the list of n 0's instead of being appended to the end of an empty list like I thought. A quick
        change in how I handled this was enough to cause my program to begin returning the correct information in the vector.

    -Issue #2: My search method wasn't able to find elements that should have been in the values.
        Was because find_child method only had < and not <= making it return wrong child
        When I had been testing my search method I noticed that it was unable to locate elements that should have been in the MTree's child nodes, and with some cout statements
        to display the information at the given node I was able to find out why this was. In the end this was because I had been searching the values vector for the right child using
        < instead of <=, which was causing it to go to the node past the one I needed to. A quick change to that was all it took to cause my program to begin functioning correctly.

    -Issue #3: Final list had the wrong size and was displaying too many elements.
        The final vector that was being returned by the collect_values method of the MTree was containing repeat elements and was the wrong size. After taking a closer look over my
        code I realized that the reason for this was because I never cleared the vectors that I was using in my MTrees after the rebuild method was called. After I added the necessary
        code to clear out the information in each of the vectors my final list began to display properly.

*/