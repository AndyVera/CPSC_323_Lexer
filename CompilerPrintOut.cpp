//
//  CompilerPrintOut.cpp
//  Compiler_Project_Print_Out
//
//  Created by Andy Vera and Nurhaliza Hassan on 9/26/21.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "LexicalAnalyzer.h"

using namespace std;

int main(int argc, const char * argv[]) {

    // Checks that the program has the appropriate number and types of statements
    if (argc != 3)  {
        cout << "Entered wrong number of statements\n It should be in the format of ' <exe file> <input text file> <output text file> \n";
        return 0;
    }

    ifstream inputfile (argv [1]);
    ofstream opout (argv[2]);

    // Checks if the files were opened correctly
    if (inputfile.is_open() != 1){
        cout << "The input file could not be opened!\n";
        return 1;
    }

    if (opout.is_open() != 1){
        cout << "The output file could not be opened!\n";
        return 1;
    } 


    string SOURCE ((istreambuf_iterator<char>(inputfile)),istreambuf_iterator<char>());

    char source;
    // Prints out the header of table containing the Tokens and Lexemes 
    cout << "    Token(s)    |    Lexeme(s)    \n------------------------------------" << '\n';


    string::iterator ptr = SOURCE.begin();
    // While Loop that keeps calling the Lexer to read character by character until it reaches the end of the file
    while(ptr != SOURCE.end()) {
    source = *ptr;
    Lexer(source, opout);
    ++ptr;
}
    
    // Closes input and output stream
    inputfile.close();
    opout.close();
    
    //Message that indicates successful run of program
    cout << "\nLexical Analyzer Done! Check Output file for results!\n";
    return 0;
}
