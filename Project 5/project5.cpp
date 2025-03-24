#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

int main() {
    //Creates the necessary variables for the program
    string token;
    char aChar;
    //Creates an array of strings with default size 50 to contain the tokens as they are read in
    string* token_array = new string[50];
    //Sets the current length of the array
    int token_array_length = 0;
    //Sets the max length of the array, which will be doubled as necessary
    int max_length = 50;
    //Creates the map which will contain the tokens as keys and frequncies as values.
    //A map is used instead of an unordered_map as the tokens need to be in alphabetical order for the multimapping to properly sort them
    map<string, int> token_map;
    //Creates a multimap which has the frequencies as the keys and tokens as the values, it is sorted in decreasing order
    multimap<int, string, greater<int> > sorted_token_map;
    //Continues to read in tokens until the end of the file is reached.
    while (cin >> token) {
        //Executes if array has reached max length
        if (token_array_length == max_length - 1) {
            //Resize the array and give it a new max length
            max_length = max_length * 2;
            //Create a temp array to store the values into
            string* temp = new string[max_length];
            for (int i = 0; i < token_array_length; i++) {
                //Stores each value in the proper place of the temp array
                temp[i] = token_array[i];
            }
            //Sets the token_array to be the temp array
            token_array = temp;
        }
        //Adds the current token to the proper place in the token_array
        token_array[token_array_length] = token;
        //Increment the length of the token array by 1
        token_array_length = token_array_length + 1;
    }

    //get each token and store them in the map and increment its frequencies.
    for (int i = 0; i < token_array_length; i++) {
        //Goes to the poper token in the token array, and then uses that to increment that position of the map
        token_map[token_array[i]]++;
    }

    //sort the myTokens in the decreasing order of VALUE which is frequencies
    for (auto x: token_map) {
        //Insert the pair for each map element into the multimap, sorting it by doing the insertions in alphabetical order which is
        //possible because the map stores the elements in alphabetical order
        sorted_token_map.insert(pair<int, string>(x.second, x.first));
    }

    //print the VALUES in the sorted token multimap separated by a space.
    for (auto x : sorted_token_map) {
        cout << x.second << " ";
    }

    //after you printed the KEYS Do this
    cout << endl;
    cout << "**********" << endl;

    //Create a variable to keep track of how many increments of the sorted_token_map must be done to find the given token
    int index = 0;
    //Go through the token_array and print the map's index value of each token
    for (int i = 0; i < token_array_length; i++) {
        //Go through the sorted_token_map multimap until you find the token at index i of the token_array
        for (auto x : sorted_token_map) {
            //Increment the index so the proper value is printed
            index = index + 1;
            //Executes if the VALUE, which is the token, of the current position in the multimap matches the token at index i of the token_array
            if (x.second == token_array[i]) {
                //Prints the current index value followed by a space
                cout << index << " ";
                //Exits the for loop for the sorted_token_map so the next token in the token_array can be done
                break;
            }
        }//End for loop
        //Sets the index back to 0 for the next iteration of the for loop
        index = 0;
    }//End for loop

    //Prints an endline.
    cout << endl;
    //Exits the program
    return 0;
}

/*
LLM Usage Documentation:

    -Prompt #1: "How do I create a map in c++?"
        -Rationale: Seeing as this was the first time I was working with the map data structure, and we never really talked about it in class, I decided
        to go and try to prompt the LLM for help with how to use the data structure for this program. In doing so I was able to figure out how to set
        up my maps for this program
    
    -Prompt #2: "How do I increment through a map to access each element?"
        -Rationale: Still not entirely sure of how the map data structure worked, I once again turned to LLMs for help with understanding how to use it. By
        turning to them I was able to figure out a couple of different ways that I could iterate through a map and was able to pick the one that best fit
        what I needed my program to do.

    -Prompt #3: "How do I sort a map using the sort function from the algorithm include?"
        -Rationale: The project guide mentioned potentially using this in order sort the map in descending order of frequencies. I attemted to use the LLM 
        to find a way to use it that fit the constraints of the project but was unable to find anyway to do it that wouldn't require an include of the 
        Vector library.

    -Prompt #4: "What is multimapping?"
        -Rationale: Seeing as I was unable to use the sort function from the algorithm include given the constraints of the project, I instead looked back
        over the project guidlines. Upon doing so I saw mentions of multimapping, which upon prompting the LLM for help with understanding what it is, I
        was able to realize it was the way for me to sort the map properly.

    -Prompt #5: "What is the difference between map and unordered_map?"
        -Rationale: When I was first trying to multimap the keys were ending up printing out in the incorrect order even though they were being bunched up
        by frequency correcty. Trying to find a solution for this I prompted the LLM for help with understanding the difference between the two data structures
        as both were mentioned as potential possibilites. In doing so I was able to realize that the problem I was encountering was that the unordered_map
        was storing the elements in a random order while map stored them in alphabetical order. Changing my unordered_map to a map was enough to get my 
        program to work properly.

    Incremental Development:
        The program had a very easy flow with how the coding needed to be done for it to all end up working properly as each step needed to be completed
        before the next step was able to be worked on. To start I first made sure that the information was being read into the file correctly, upon seeing
        that it was I moved onto the next step which was storing everything into the map. Upon ensuring that was done I was able to move onto sorting the
        map based on the frequency of the tokens. To do so I used a mutlimap which is where I ran into the first problem with my program, that being that
        the unordered_map needed to be a map so that the elements were stored in alphabetical order which then made the multimap save the info properly.
        The final step I needed to do was to print out the encoded version of the original text using the map index of the given tokens, and upon doing so
        and ensuring that it was giving the proper output, I turned it into gradescope and let the autograder grade it.

---------------------------

Debugging and Testing Plan:

    -Test #1: Ensuring the elements were read in correctly
        -In order to do so I read from the file until the end of the file was reached and stored each token in its own position of the token_array, and
        then I printed out the array to ensure the file was being read properly. Once I was sure it was I moved on to the next step.

    -Test #2: Ensuring the map stored the elements properly
        -In order to do so I went and worked through the map using a for loop and printed out the token and its frequencies after having read everything
        into the map. Once I had ensured that tokens were coming out of it with the right frequncies I moved on to the next step.

    -Test #3: Ensuring the map is sorted properly
        -In order to do so I first stored everything into a multimap which had the frequncies as the KEYS and the tokens as the VALUES, which would
        automatically sort the elements based on the insertion into the multimap. At first I ran into issues because I was using an unordered_map
        which didn't store the elements in alphabetical order. Upon changing to using a map instead the multimap was storing the information properly
        and was ready to be used for the last step.

    -Test #4: Putting it all together and doing the encoding
        -In order to do this I needed to turn the token input that was stored in the string array at the start of the program into the tokens index
        position in the sorted_map. I did so by incrementing through the sorted_map until I reached where the token was stored as the VALUE, once I had
        done so I printed out the index for that item and then moved onto the next one. With both this and the original portion of my code that displayed the
        elements in the map in sorted order, I was able to test out each of the files and see if what I was getting was matching the output files. 

    -Issue #1: Items weren't being stored properly in the multimap
        -The reasoning for this issue occuring was that originally I was using a unordered_map instead of a map, which caused the elements to not be 
        stored in alphabetical order. This became an issue when trying to move things over to the multimap as there were getting stored out of order
        thanks to the way the insert method determines the order of the elements. In order to fix this I changed my unordered_map to a map and my
        program began to work as intended.

    -Issue #2: Gradescope was failing my code with an error I was unable to figure out.
        -Gradescope was giving me an error where in the autograder was just displaying the list of files and telling me it was failing somewhere in the
        bats file. Unsure of how to fix this, I went to the TA's for help and with their help was able to determine that the reason that my gradescope was
        producing that error was because I had only used 8 *'s to seperate the two sections instead of 10, and upon changing that my program would submit
        properly.

*/