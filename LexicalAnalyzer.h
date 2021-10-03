#include <iostream>
#include <string>
#include <iomanip>
#ifndef LexicalAnalyzer_h
#define LexicalAnalyzer_h

int current_state = 0;
int previous_state = 0;

using namespace std;

string keywords[14] = { "true","function","integer","false",	
			            "boolean", "real","if",	"endif",
			            "else",	"return","put",	"get","while"} ;

string separators[7] = { "}",		"{",		"(",		")",
			",",	";"};

string operators[11] = {"<=",	 "+",		"-", 	"*",		
			"/",		 ">",		"<",		"=>",
			"!=",	 "=" };
        




void Lexer(char input, ofstream& opout){
    
    int DFSM[5][4];
    DFSM[0][0] = 0; DFSM[0][1] = 1; DFSM[0][2] = 2; DFSM[0][3] = 3;

    DFSM[1][0] = 1; DFSM[1][1] = 1; DFSM[1][2] = 1; DFSM[1][3] = 3;

    DFSM[2][0] = 2; DFSM[2][1] = 3; DFSM[2][2] = 2; DFSM[2][3] = 4;

    DFSM[3][0] = 3; DFSM[3][1] = 3; DFSM[3][2] = 3; DFSM[3][3] = 3; 

    DFSM[4][0] = 4; DFSM[4][1] = 3; DFSM[4][2] = 4; DFSM[4][3] = 3;
    

    static string source;
    char characterread = input;


//this if loop checks for separators
    if(!isalpha(characterread) && !isnumber(characterread)&& !isspace(characterread)) {
        //source = '\0';
        source += characterread;
    for(int i = 0; 0 < 7; i++ ){
        if(operators[i].compare(source) == 0){
            opout << setw(16) << "Separator" << "|" << setw(17) << source << '\n';
            source = "\0";
            characterread = '\0';
            break;
        }
    }
    }

//Starting State
     if(isalpha(characterread) && current_state == 0 ){
        current_state = DFSM[0][1];
        source += characterread;
        characterread = '\0';
    }
    if(isnumber(characterread) && current_state == 0 ){
        current_state = DFSM[0][2];
        source += characterread;
        characterread = '\0';
    }
    if((characterread == '.') && current_state == 0 ){
        current_state = DFSM[0][3];
        characterread = '\0';
    }


//If first input was a letter
    else if (isalpha(characterread) && current_state == 1){
        previous_state = current_state;
        current_state = DFSM[current_state][1];
        source += characterread;
        characterread = '\0';
    }

    else if (isnumber(characterread) && current_state == 1){
        previous_state = current_state;
        current_state = DFSM[current_state][2];
        source += characterread;
        characterread = '\0';
    }

    else if(characterread == '.' && current_state == 1){
        previous_state = current_state;
        current_state = DFSM[current_state][3];
        characterread = '\0';
    }


    else if (characterread == ' ' && current_state == 1 && (source.length() == 1)){
        current_state = 0;
        previous_state = 0;
        opout << setw(16) << "Identifier" << "|" << setw(17) << source << '\n';
        source = '\0';
        characterread = '\0';
    }

//If first input is number
    if (isnumber(characterread) && current_state == 2){
        previous_state = current_state;
        current_state = DFSM[current_state][2];
        source += characterread;
        characterread = '\0';
    }

    else if (isalpha(characterread) && current_state == 2){
        opout << setw(16) << "Integer" << "|" << setw(17) << source << '\n';
        source = '\0';
        source += characterread;
        characterread = '\0';
        current_state = 0;
        previous_state = 0;
    }

    else if(characterread == '.' && current_state == 2){
    previous_state = current_state;
    current_state = DFSM[current_state][3];
    source += characterread;
    characterread = '\0';
}

//When digits and a period has been entered

if (isnumber(characterread) && current_state == 4){
        previous_state = current_state;
        current_state = DFSM[current_state][2];
        source += characterread;
        characterread = '\0';
    }

if (isalpha(characterread) && current_state == 4){
        previous_state = current_state;
        current_state = DFSM[current_state][1];
        characterread = '\0';
    }

if (characterread == '.' && current_state == 4){
        previous_state = current_state;
        current_state = DFSM[current_state][3];
        characterread = '\0';
    }

//if a space is entered or reaches state 3
    else if ((isspace(characterread) && (source.length() != 1))|| current_state == 3){
        if (previous_state == 1){
            int passing = 0;

            for(int i = 0; i < 14; i++){
                if (keywords[i].compare(source) == 0){
                opout << setw(16) << "Keyword" << "|" << setw(17) << source << '\n';
                source = "\0";
                characterread = '\0';
                current_state = 0;
                previous_state = 0;
                break;
                }
                passing = i+1;
            }

            if(passing == 14){
            opout << setw(16) << "Identifier" << "|" << setw(17) << source << '\n';
            source = "\0";
            characterread = '\0';
            current_state = 0;
            previous_state = 0;
        }
        }
        if (previous_state == 2){
            opout << setw(16) << "Integer" << "|" << setw(17) << source << '\n';
            source = "\0";
            characterread = '\0';
            current_state = 0;
            previous_state = 0;
        }
        if (previous_state == 4){
            opout << setw(16) << "Real" << "|" << setw(17) << source << '\n';
            source = "\0";
            characterread = '\0';
            current_state = 0;
            previous_state = 0;
        }
    }


}
#endif /* LexicalAnalyzer_h */

//while if IF WHILE get put Josh josh 345 3.456 3.4.4.