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

    //Creates the final_map map which will be used for easy printing of the input
    map<int, string> final_map;
    int final_map_index = 1; //Creates the final_map_index variable which keeps track of the current index in the final_map map
    for (auto x : sorted_token_map) {
        //Inserts the VALUE, which is the token, from the given index of the sorted_token_map multimap into the final_map map using the proper index.
        final_map.insert(pair<int, string>(final_map_index, x.second));
        //Increments the final_map_index by 1
        final_map_index = final_map_index + 1;
    }

    //Creates an int array which is the same length as the token_array. This will store what the output would have been.
    int* index_array = new int[token_array_length];
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
                //Stores the correct index value for the element at index i into the index_array
                index_array[i] = index;
                //Exits the for loop for the sorted_token_map so the next token in the token_array can be done
                break;
            }
        }//End for loop
        //Sets the index back to 0 for the next iteration of the for loop
        index = 0;
    }//End for loop

    //Works through the entire index_array and prints out the corresponding token for tha index value stored in the index_array
    for (int i = 0; i < token_array_length; i++) {
        cout << final_map[index_array[i]] << " ";
    }

    //Prints an endline.
    cout << endl;
    //Exits the program
    return 0;
}