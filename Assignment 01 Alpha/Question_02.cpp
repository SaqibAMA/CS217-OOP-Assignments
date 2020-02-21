#include <iostream>

using namespace std;

// Question 02
// Helper functions for string manipulation.
int stringLen(const char* str) {

    int i = 0;

    do {
        i++;
    } while(str[i] != '\0');

    return i;

}

// Converts the string into lower case characters
// for uniform checking
void convertToLower(char* &s) {

    char* lowerS = new char[stringLen(s)];
    int i;
    for (i = 0; s[i] != '\0'; i++){
        if (s[i] >= 'A' && s[i] <= 'Z')
            lowerS[i] = s[i] + 32;
        else
            lowerS[i] = s[i];
    }
    lowerS[i] = '\0';

    delete[] s;
    s = lowerS;

}

// To copy one string into another string
void copyString(char* str1, char* str2) {

    int i;
    for (i = 0; str2[i] != '\0'; i++)
        str1[i] = str2[i];
    str1[i] = '\0';

}

// Appends a string at the tail of the other
// also handles deletion of last characters
void appendString(char* str1, char* str2, int n = 0) {

    int i, j;
    for (i = stringLen(str1) - n, j = 0; str2[j] != '\0'; i++, j++) {
        str1[i] = str2[j];
    }
    str1[i] = '\0';

}

// Checks for vowels
bool isVowel (char c) {
    return (c == 'a' ||
           c == 'e' ||
           c == 'i' ||
           c == 'o' ||
           c == 'u');
}

// Checks if the string is
bool isEqual(char* str1, char* str2) {

    int str1Len = stringLen(str1), str2Len = stringLen(str2);

    if (str1Len == str2Len) {
        int i = 0;

        while (str1[i] != '\0') {
            if (str1[i] != str2[i])
                return false;
            i++;
        }
    }
    else {
        return false;
    }

    return true;
}

// Question 2, Part 01. Function to concatenate two strings.
void StringConcatenate (char *str1, char *str2) {

    int str1Len = stringLen(str1);
    int str2Len = stringLen(str2);

    int i = 0, j = str1Len;
    for (; str2[i] != '\0'; i++, j++)
        str1[j] = str2[i];
    str1[j] = '\0';
}

// Question 2, Part 02. Function to compress a string.
// i.e. aaaaaabbbbdd => abd
void CompressString(char* str){

    int strSize = stringLen(str);
    char cChar;

    for (int i = 0; i < strSize; i++){
        cChar = str[i];

        for (int j = 0; j < strSize;) {

            if (str[j] == cChar && i != j) {

                int k = j;
                for (; k < strSize; k++) {
                    str[k] = str[k + 1];
                }
                str[k] = '\0';
                strSize--;
                j--;

            } else {
                j++;
            }


        }

    }

}

// Question 2, Part 03. Function to reverse a sentence.
// i.e. I am Pakistani => Pakistan am I
char* ReverseSentence(char* str) {

    int strSize = stringLen(str);

    char* revString = new char[strSize];

    int revInd = 0;

    int i = strSize - 1, j = 0;

    bool trav = false;

    while (!trav) {
        j = 0;
        while (str[i] != ' ' && i >= 0) {
            i--;
            j++;
        }

        if (i > 0) {
            for (int k = i + 1; k <= i + j; k++)
                revString[revInd++] = str[k];
            revString[revInd++] = ' ';
        } else {
            for (int k = 0; k <= i + j; k++)
                revString[revInd++] = str[k];
            trav = true;
        }
        i--;
    }

    revString[revInd] = '\0';

    return revString;

}

// Question 2, Part 04. Function to convert a 2D
// array of words into plurals.
// i.e. blunt => blunts, cat => cats
void plural(char** s, int wCount) {

    for (int i = 0; i < wCount; i++) {
        convertToLower(*(s + i));

        // Requirement 01
        if (s[i][stringLen(s[i]) - 1] == 'h' &&
                (s[i][stringLen(s[i]) - 2] == 'c' ||
                s[i][stringLen(s[i]) - 2] == 's')) {
            appendString(s[i], "es");
        } // Requirement 02
        else if (s[i][stringLen(s[i]) - 1] == 's') {
            appendString(s[i], "es");
        } // Requirement 03
        else if (s[i][stringLen(s[i]) - 1] == 'y') {

            if (isVowel(s[i][stringLen(s[i]) - 2])) {
                appendString(s[i], "s");
            }
            else {
                appendString(s[i], "ies", 1);
            }

        } // Requirement 04
        else if (s[i][stringLen(s[i]) - 1] == 'z') {

            if (isVowel(s[i][stringLen(s[i]) - 2])) {
                appendString(s[i], "zes");
            }
            else {
                appendString(s[i], "es");
            }

        }
        else {

            // Special cases
            char* sCases[] = {"child", "goose", "man", "woman",
                              "tooth", "foot", "mouse", "person"};

            char* sCasesP[] = {"children", "geese", "men", "women",
                               "teeth", "feet", "mice", "people"};

            int sCount = sizeof(sCases) / sizeof(sCases[0]);
            bool isSpecial = false;

            for (int j = 0; j < sCount; j++){
                if (isEqual(s[i], sCases[j])) {
                    copyString(s[i], sCasesP[j]);
                    isSpecial = true;
                }
            }

            // Simply appending "s" if no special case is found
            if(!isSpecial) {
                appendString(s[i], "s");
            }

        }

    }

}

int main(){

    char str1[] = "Saqib";
    char str2[] = "Ali";

    // String Concatenation function
    //StringConcatenate(str1, str2);


    char str3[] = "aaaaaaaaabbaad";

    // String Compression function
    // CompressString(str3);

    char str4[] = "I am Pakistani";

    // String reversal function
    // char* revString = ReverseSentence(str4);
    // cout << revString << endl;

    char* s[] = {"Student", "Party", "Quiz", "Bat", "Man", "Lunch"};
    int wCount = sizeof(s) / sizeof(s[0]);

    /*cout << "The words before conversion: " << endl;
    for (int i = 0; i < wCount; i++)
        cout << s[i] << endl;

    plural(s, wCount);

    cout << "The words after conversion: " << endl;
    for (int i = 0; i < wCount; i++)
        cout << s[i] << endl;*/

    return 0;
}