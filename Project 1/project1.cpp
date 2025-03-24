#include <iostream>
using namespace std;

class SparseRow {
    protected:
        int row;
        int col;
        int value;
    public:
    //Constructors
    SparseRow();
    SparseRow(int r, int c, int v);
    //Display Method
    void display(); //Print Row#, Column#, value
    //Overloaded Operators
    friend ostream& operator<< (ostream& s, const SparseRow sr) {
        cout << sr.row << ", " << sr.col << ", " << sr.value;
    }
    //Method to check if the sparse row is equal to a specific point
    bool checkPoint(int r, int c);
    //Setter method
    void setValue(int v);
    //Getter methods
    int getRow();
    int getCol();
    int getValue();
    //Destructor
    ~SparseRow();
};

SparseRow::SparseRow() {
    row = -1;
    col = -1;
    value = 0;
}

SparseRow::SparseRow(int r, int c, int v) {
    row = r;
    col = c;
    value = v;
}

void SparseRow::display() {
    cout << row << ", " << col << ", " << value << endl; //Displays properly formatted SparseRow info
}
//Checks if the SparseRow object is also at the position (row, column)
bool SparseRow::checkPoint(int r, int c) {
    bool checkValue;
    if ((row == r) && (col == c)) {
        checkValue = true;
    }
    else {
        checkValue = false;
    }

    return checkValue;
}

void SparseRow::setValue(int v) {
    value = v;
}

int SparseRow::getRow() {
    return row;
}

int SparseRow::getCol() {
    return col;
}

int SparseRow::getValue() {
    return value;
}

SparseRow::~SparseRow() {}

class SparseMatrix {
    protected:
        int noRows; //Number of rows in the original matrix
        int noCols; //Number of columns in the original matrix
        int commonValue; //Read from input
        int noNonSparseValues;
        int arrayPosition = 0;
        SparseRow* myMatrix; //The array of SparseRow objects
        //Constants to denote failure cases
        const int addFail = -1;
        const int multFail = -2;
        const int transposeFail = -3;
    public:
    //Constructors
    SparseMatrix();
    SparseMatrix(int n, int m, int cv, int noNSV);
    //Matrix Manipulation Methods
    SparseMatrix* Transpose(); //Matrix Transpose
    SparseMatrix* Multiply(SparseMatrix& M); //Matrix Multiplication
    SparseMatrix* Add(SparseMatrix& M); //Matrix Addition
    //Overloaded Operators
    //Displays the matrix in sparse matrix format
    friend ostream& operator<< (ostream& s, const SparseMatrix& sm) {
        //Case for addition fail
        if (sm.noRows == sm.addFail) {
            cout << "Matrix addition is not possible" << endl;
        }
        //Case for multiplication fail
        else if (sm.noRows == sm.multFail) {
            cout << "Matrix multiplication is not possible" << endl;
        }
        //Case for transpose fail
        else if (sm.noRows == sm.transposeFail) {
            cout << "Matrix transposition is not possible" << endl;
        }
        //Display matrix in sparse matrix format
        else {
            for (int i = 0; i < sm.noNonSparseValues; i++) {
                sm.myMatrix[i].display(); //Call SparseRow display method for every non sparse value in the myMatrix array
            }
        }
    }
    //Display Method
    void displayMatrix(); //Displays the matrix in matrix format
    //Methods to check validity of matrix multiplication and matrix addition
    bool checkMultiply(const SparseMatrix& sm);
    bool checkAddition(const SparseMatrix& sm);
    //Method to add value to myMatrix
    void addSparseValue(const SparseRow& sr);
    //Getter methods
    int getNumRows();
    int getNumCols();
    int getCommonValue();
    int getNumNonSparseValues();
    int getArrayPos(); //Returns the arrayPosition variable which shows how many elements are currently in the myMatrix arraay. Will be equal to numNonSparseValues
    //Destructor Method
    ~SparseMatrix();
    private:
    //Setter Method
    void setNumNonSparseValues(int noNonSparse);
};

SparseMatrix::SparseMatrix() {
    noRows = 0;
    noCols = 0;
    commonValue = 0;
    noNonSparseValues = 0;
    myMatrix = NULL;
}

SparseMatrix::SparseMatrix(int n, int m, int cv, int noNSV) {
    noRows = n;
    noCols = m;
    commonValue = cv;
    noNonSparseValues = noNSV;
    myMatrix = new SparseRow[noNSV];
}

SparseMatrix* SparseMatrix::Transpose() {
    SparseMatrix* transposeMatrix;

    //If the SparseMatrix attempting to be transposed is one of the fail cases, then set transposeMatrix equal to a SparseMatrix containing information marking it as a transpose
    //failure.
    if ((noRows == addFail) || (noRows == multFail) || (noRows == transposeFail)) {
        transposeMatrix = new SparseMatrix(transposeFail, transposeFail, 0, 1);
    }
    else {
        //Set transpose matrix equal to a SparseMatrix object that has the number of rows and the number of columns flipped.
        transposeMatrix = new SparseMatrix(noCols, noRows, commonValue, noNonSparseValues);
        SparseRow currRow;
        //For each SparseRow object in the myMatrix array create a SparseRow object that has swapped row and column information, and then store it in the transposeMatrix
        //SparseMatrix object.
        for (int i = 0; i < noNonSparseValues; i++) {
            currRow = SparseRow(myMatrix[i].getCol(), myMatrix[i].getRow(), myMatrix[i].getValue());
            //Call the addSparseValue method to add the created SparseRow object to the end of the transposeMatrix's myMatrix array.
            (*transposeMatrix).addSparseValue(currRow);
        }
    }
    //Return the created SparseMatrix
    return transposeMatrix;
}

SparseMatrix* SparseMatrix::Multiply(SparseMatrix& M) {
    SparseMatrix* multiplyMatrix;
    //Checks to see if the two matricies are able to be multiplied together.
    if ((*this).checkMultiply(M)) {
        //Creates a sparse matrix object with the number of rows from the first matrix, and the number of columns from the second.
        multiplyMatrix = new SparseMatrix(noRows, M.noCols, commonValue, (noNonSparseValues + M.noNonSparseValues));
        SparseRow currRow;
        bool pointCurrContained = false;
        //Loops through all the values stored in the first matrix
        for (int m1 = 0; m1 < noNonSparseValues; m1++) {
            //Loops through all the values stored in the second matrix
            for (int m2 = 0; m2 < M.noNonSparseValues; m2++) {
                //Checks to see if the column value of the current value in the first matrix is equal to the row value of the second matrix. If they are then
                //the two points will need to be multiplied together.
                if (myMatrix[m1].getCol() == M.myMatrix[m2].getRow()) {
                    int currVal = (myMatrix[m1].getValue()) * (M.myMatrix[m2].getValue());
                    //Loops through all the values currently stored in the multiplyMatrix SparseMatrix object
                    for (int m3 = 0; m3 < (*multiplyMatrix).getArrayPos(); m3++) {
                        //Checks to see if the current (row, col) point is already contained within the matrix, and adds the value to it if so.
                        if ((*multiplyMatrix).myMatrix[m3].checkPoint(myMatrix[m1].getRow(), M.myMatrix[m2].getCol())) {
                            currVal = currVal + (*multiplyMatrix).myMatrix[m3].getValue();
                            //Sets the value of the point to be equal to the old value plus the new value.
                            (*multiplyMatrix).myMatrix[m3].setValue((currVal));
                            //Sets point contained to true so that the point won't be added again.
                            pointCurrContained = true;
                        }
                    }
                    //Checks if the point isn't currently already contained within the matrix.
                    if (!(pointCurrContained)) {
                        //Creates a SparseRow object using the given information and adds it to the multiplyMatrix object.
                        currRow = SparseRow(myMatrix[m1].getRow(), M.myMatrix[m2].getCol(), currVal);
                        (*multiplyMatrix).addSparseValue(currRow);
                    }
                    //Sets the point contained variable back to false if it was true so that the loop will execue properly.
                    else {
                        pointCurrContained = false;
                    }
                }
            }
        }
        //Sets the noNonSparseVals variable equal to the number of elements added to the array to ensure proper output later.
        (*multiplyMatrix).setNumNonSparseValues((*multiplyMatrix).getArrayPos());
    }
    //Sets multiplyMatrix equal to a SparseMatrix object that is initialized with information to signify multiplcation failure.
    else {
        multiplyMatrix = new SparseMatrix(multFail, multFail, 0, 1);
    }
    //Return the created SparseMatrix
    return multiplyMatrix;
}

SparseMatrix* SparseMatrix::Add(SparseMatrix& M) {
    SparseMatrix* additionMatrix;
    //Checks if addition between the two matrices is possible before attempting it
    if ((*this).checkAddition(M)) {
        //Adds the number of nonSparseValues from matrix 1 and matrix 2 and uses that as the number of non sparse values for the addition matrix so that the 
        //created array is guarenteed to be long enough to store all the values. The number of nonSparseValues will be changed to be correct once the exact number of them
        //has been determined.
        additionMatrix = new SparseMatrix(noRows, noCols, commonValue, (noNonSparseValues + M.noNonSparseValues));
        SparseRow currRow;
        int totalValAtPoint = 0;

        for (int row = 0; row < noRows; row++) {
            for (int col = 0; col < noCols; col++) {
                //Check if either matrix has an element at the given row and column position. If there exists an element in only one matrix then add it to a variable set to 0, and
                //then use this variable to make a SparseRow object with the given value and position to be stored in the array. If there exists an element with that position 
                //in both matricies, then add both SparseRow values to the same variable and then store it in a SparseRow object at the current position.
                for (int m1 = 0; m1 < noNonSparseValues; m1++) {
                    if (myMatrix[m1].checkPoint(row, col)) {
                        totalValAtPoint = totalValAtPoint + myMatrix[m1].getValue();
                    }
                }

                for (int m2 = 0; m2 < M.getNumNonSparseValues(); m2++) {
                    if (M.myMatrix[m2].checkPoint(row, col)) {
                        totalValAtPoint = totalValAtPoint + M.myMatrix[m2].getValue();
                    }
                }
                //Checks if the value at the current point isn't 0 before creating a SparseRow object and adding it to the additionMatrix SparseMatrix object
                if (totalValAtPoint != 0) {
                    currRow = SparseRow(row, col, totalValAtPoint);
                    (*additionMatrix).addSparseValue(currRow);
                }
                //Sets totalValAtPoint to 0 for the next loop.
                totalValAtPoint = 0;
            }
        }
        //Sets the noNonSparseVals variable equal to the number of elements added to the array to ensure proper output later.
        (*additionMatrix).setNumNonSparseValues((*additionMatrix).getArrayPos());
    }
    //Sets additionMatrix equal to a SparseMatrix object that is initialized with information to signify addition failure.
    else {
        additionMatrix = new SparseMatrix(addFail, addFail, 0, 1);
    }
    //Return the created SparseMatrix
    return additionMatrix;
}

void SparseMatrix::displayMatrix() {
    //Case for addition fail.
    if (noRows == addFail) {
        cout << "Matrix addition is not possible" << endl;
    }
    //Case for multiplication fail.
    else if (noRows == multFail) {
        cout << "Matrix multiplication is not possible" << endl;
    }
    //Case for transpose fail.
    else if (noRows == transposeFail) {
        cout << "Matrix transposition is not possible" << endl;
    }
    //Display the Matrix in Matrix format
    else {
        bool sparseRowAtIndex = false;
        //Loops through the number of rows.
        for (int row = 0; row < noRows; row++) {
            //Loops through number of columns.
            for (int col = 0; col < noCols; col++) {
                //Loops through the number of non sparse values in the matrix.
                for (int arrayPos = 0; arrayPos < noNonSparseValues; arrayPos++) {
                    //Checks if the current (row, col) point is contained within the matrix.
                    if (myMatrix[arrayPos].checkPoint(row, col)) {
                        sparseRowAtIndex = true;
                        //If its the first column of the row, print the current value of the myMatrix array without spaces.
                        if (col == 0) {
                            cout << myMatrix[arrayPos].getValue();
                        }
                        //If it is not the first column of the array, then print the value with a space in front.
                        else {
                            cout << " " << myMatrix[arrayPos].getValue();
                        }
                    }
                }
                //Checks to see if there is no sparseRow object at the current index.
                if (!(sparseRowAtIndex)) {
                    //If it is the first column of the row, prints the common value of the array without spaces.
                    if (col == 0) {
                        cout << commonValue;
                    }
                    //If it is not the first column of the row, then print the common value with a space in front.
                    else {
                        cout << " " << commonValue;
                    }
                }
                sparseRowAtIndex = false; //Sets sparse row index to false to ensure the loop executes properly.
            }
            cout << endl; //Starts a new line at the end of each row.
        }
    }
}

bool SparseMatrix::checkMultiply(const SparseMatrix& sm) {
    bool checkValue;
    //Checks if matrix multiplication is possible by checking that matrix 1 has the same number of columns as matrix 2 does rows, and returns the result.
    if (noCols == sm.noRows) {
        checkValue = true;
    }
    else {
        checkValue = false;
    }

    return checkValue;
}

bool SparseMatrix::checkAddition(const SparseMatrix& sm) {
    bool checkValue;
    //Checks if matrix addition is possible by checking that the two matricies have the same dimensions, and returns the result.
    if ((sm.noRows == noRows) && (sm.noCols == noCols)) {
        checkValue = true;
    }
    else {
        checkValue = false;
    }

    return checkValue;
}

void SparseMatrix::addSparseValue(const SparseRow& sr) {
    //Adds a SparseRow object to the myMatrix array so long as the current arrayPos is less than the size of the array.
    if (arrayPosition < noNonSparseValues) {
        myMatrix[arrayPosition] = sr;
        arrayPosition++;
    }
}

int SparseMatrix::getNumRows() {
    return noRows;
}

int SparseMatrix::getNumCols() {
    return noCols;
}

int SparseMatrix::getCommonValue() {
    return commonValue;
}

int SparseMatrix::getNumNonSparseValues() {
    return noNonSparseValues;
}

int SparseMatrix::getArrayPos() {
    return arrayPosition;
}

SparseMatrix::~SparseMatrix() {
    //Deletes the myMMatrix array which is dynamically allocated
    delete[] myMatrix;
}

void SparseMatrix::setNumNonSparseValues(int noNonSparse) {
    noNonSparseValues = noNonSparse;
}

int main() {

    int n, m, cv, noNSV;
    int currValue; //Variable to hold the current value being read from the user's input of the matrix content
    SparseRow currRowValue;
    SparseMatrix* temp;

    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> currValue;
            if (!(currValue == cv)) {
                //Creates a SparseRow object at the current point of the Matrix and then stores it in the SparseRow array of the SparseMatrix object that called the 
                //addSparseValue method.
                currRowValue = SparseRow(i, j, currValue);
                (*firstOne).addSparseValue(currRowValue);
            }
        }
    }

    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);

    //Write the statements to read the second matrix here
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> currValue;
            if (!(currValue == cv)) {
                //Creates a SparseRow object at the current point of the Matrix and then stores it in the SparseRow array of the SparseMatrix object that called the 
                //addSparseValue method.
                currRowValue = SparseRow(i, j, currValue);
                (*secondOne).addSparseValue(currRowValue);
            }
        }
    }

    cout << "First one in sparse matrix format" << endl;
    cout << (*firstOne);

    cout << "After transpose" << endl;
    cout << (*(*firstOne).Transpose());
    
    cout << "First one in matrix format" << endl;
    (*firstOne).displayMatrix();

    cout << "Second one in sparse matrix format" << endl;
    cout << (*secondOne);

    cout << "After transpose" << endl;
    cout << (*(*secondOne).Transpose());

    cout << "Second one in matrix format" << endl;
    (*secondOne).displayMatrix();

    cout << "Matrix addition result" << endl;

    temp = (*firstOne).Add((*secondOne));
    (*temp).displayMatrix();

    cout << "Matrix multiplication result" << endl;

    temp = (*firstOne).Multiply((*secondOne));
    (*temp).displayMatrix();

    return 0;
}

/*
LLM Usage Documentation:

    -Prompt #1: "How to I make a c++ program use redirected input to read from a text file in the same directory in visual studio code?"
        -Rationale: I could not set up redirected input for my program following the guide provided in the project 1 handout, and seeing as how I was unable to
        make the office hours I decided to prompt chatGPT for help. This allowed me to attempt to figure out how to set up my program in Visual Studio Code so that it 
        can make use of redirected input from files.

    -Prompt #2: "How might I implement a multiplication function to multiply two matrices in SRM format?"
        -Rationale: While I am able to understand how to handle matrix multiplication when given a standard matrix, figuring out how to translate that to
        matrices in SRM format was giving me some trouble, specifically on where the values that were multiplied should be stored in the new matrix. Upon reading and understanding 
        the process behind the code that was wrote by the LLM I was able to determine a way for me to write the matrix Multiplication method. This is because I was able to 
        determine that after multiplying two SparseRow objects the value would need to be stored on the matrix made from multiplication at the row value of the first SRM matrix,
        and the column value of the second.

    -Prompt #3: "What are some things to consider when writing methods working with matrices in SRM format?"
        -Rationale: This is the first time I have ever worked with matricies in this kind of format so I decided to get some help from chat gpt regarding
        what sort of things would be good to consider. In the end it helped me consider the time complexities of my methods more carefully, and to start thinking
        of ways to lower any of them where possible.

    -Prompt #4: "How would you handle displaying a matrix in SRM format in c++ if its stored in a SparseRow array in which the SparseRow class 
     holds the row, column, and value information of each point in the matrix?"
        -Rationale: As this is the first time using matricies in SRM format, I wanted to see how chatGPT would handle writing this part of the code so that I might be able
        to write more efficient code, while also helping me to consider how I should handle displaying the common values of the matrix as they aren't stored in the array.

    -Promt #5: "What things should be considered when writing destructors in c++?"
        -Rationale: Destructors are still a new concept to me as this is my first time writing a program in c++, so I prompted chatGPT for help with considering what
        all I would need to write. In the end I was able to figure out which pieces of data needed additional handling given the response I was given, and it also 
        helped me to learn more about destructors in general.

    Incremental Development:
        In order to begin working on this project I first wrote the SparseRow class and then wrote enough of the necessary methods of the SparseMatrix class to read in the
        matrix information from the user. After I was sure the information about the matrix was being stored properly, I began to focus on displaying the matrix correctly
        to the user. Once I had the display methods working properly I began to work on getting the Matrix Manipulation methods to properly carry out their given functions.
        In order to do so I did some research online about when you can add or multiply matrices, and upon learning of the constraints I wrote two additional methods to
        check if the two matricies had the correct number of rows and columns to preform the given functions. 
        
        After writing and testing that code I started working on the matrix Transpose method as it was the first to appear on the output files, thus making 
        it the easiest to put at the end of the main method without having to edit later. Once I completed and tested the transpose method I set about on 
        writing the addition one next. Upon completing it I found myself unable to test it at the time as I was running into an issue that I had not been able to 
        solve at the time. Deciding to move on for the moment instead of attempting to focus on a problem I couldn't understand, I wrote the method for multiplying two
        matrices together and found that I was running into the same problem again there. After consulting with the Professor I was able to figure out that my issue was coming
        from a lack of understanding on how to work with pointers properly, and that upon getting a quick refresher I was able to solve the error I was encountering. Once I
        could test these methods, I found that both needed some slight adjustments but were able to function properly in the end.

---------------------------

Debugging and Testing Plan:

    -Test #1: Ensure proper display of Sparesly Represented Matrix format.
        In order to ensure the proper display of the given information I passed a couple different inputs to the program to ensure that it would create and display the 
        correct number of SparseRow objects from a given matrix.

    -Test #2: Ensuring the displayMatrix method of the SparseMatrix class properly output the information.
        After I finished writing my displayMatrix method I began to test that it would properly display the given matrix. After my first tests I had found that after the first
        non sparse value in the matrix, my program would stop printing zeroes. Upon closer examination I realized that this was because I didn't set the bool variable that
        determines if a zero needs to be printed back to false after setting it to true upon finding a proper value. After adding the line of code to set the bool variable back
        to false the displayMatrix method began to display correctly

    -Test #3: Ensuring matrix Transpose has been properly implemented.
        In order to be sure that the matrix Transpose method was implemented properly I gave the program each of the matricies that are in the input files
        and I used the output file results to check to make sure that matrix Transpose had been carried out as intended. This was to ensure that rows and columns 
        had been swapped as intended.

    -Test #4: Ensuring that the methods to check if matrices were allowed to be added / multiplied were functioning correctly.
        To achieve this I tested with the matrices in the input files and ensured that the true / false output from the method is what was expected with the given input.

    -Test #5: Ensuring that Matrix Addition computed correctly.
        I tested the matrix addition method with each of the inputs from the input files and ensured that they displayed the proper amount of values in the correct places using
        different combinations of matricies that had different sizes and numbers of non sparse values. I would check the output against what the output files said it should
        be, and guarenteed that they matched up.

    -Test #6: Ensuring that Matrix Multiplication computes correctly.
        I tested the matrix multiplication method using the same testing plan as what I used on the matrix addition method. I gave it the information from each of the input
        files and then would check that the operation was only carried out when matrix multiplication was possible, and that the output would match after the operation is
        completed. The input had multiple combinations of arrays that would accound for testing with different sparsities and dimensions.

    -Issue #1: Only default values storing inside the SparseRow array myMatrix.
        In order to come to a resolution on this issue I went through a series of different tests to see if I could solve this problem. First I tried to tackle this 
        problem by ensuring that the program was creating unique SparseRow objects based on the input to send to the addSparseValue method. Once I verified that new
        objects were being created I instead turned to look at the addSparseValue method itself and tried changing the way I determined the number of values in the array, which
        cuased the program to begin working as soon as I changed it.
    
    - Issue #2: Properly displaying if matrix addition / multiplication failed when the display functions are called.
        In order to solve this I established constant variables inside the SparseMatrix class that are set for the row and column values to denote which kind of matrix
        manipulation failed. I also included one for if Matrix Transpose could not be completed in case of the edge case where someone attempts to do Matrix Transpose on a
        Matrix that had the addition / multiplication fail.
    
    -Issuse #3: No matching function calls for the Add and Multiply methods of the SparseMatrix class when attempted to be called with pointers.
        In order to resolve this problem I had to take a closer take a closer look at how pointers work, and had to realize that the way my methods are wrote
        required me to handle the pointers differently in the main program so that they would be able to be given to the methods.

    -Issue #4: Matrix addition displying the matrix incorrectly
        When I attempted to test matrix addition I noticed that instead of adding just the values at the given point and using that to 
        determine the values of the SparseRow object, it was instead adding every value from across the matrix together which caused an incorrect result
        to be displayed. In order to fix this I edited the code to make it so that the int variable used to track the value at a given point was set to 0
        again after being used.

    -Issue #5: Matrix multiplication not outputting the proper matrix.
        I had attempted to test matrix multiplication and found that it was only making it part way through the multiplication process before it quit storing
        new values. To fix this I first simplified the method I had wrote to only add values to the array without caring if any matching point values were
        already inside. Upon doing so I saw that not only was my handling of two same point values working properly, I saw that the number of non sparse values being
        saved to the myMatrix array was the same across both outputs. This lead to me taking a closer look at how I initialized the multiplyMatrix object, where upon
        doing so I found that I created the array to only be able to hold a number of values equal to the length of the first matrix which lead to values not being stored.
*/