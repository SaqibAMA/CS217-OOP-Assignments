#include <iostream>

using namespace std;

// Part 01

// Custom strlen function
int stringLen(const char* str) {

    int i = 0;

    do {
        i++;
    } while(str[i] != '\0');

    return i;

}

// Function to concatenate two strings
void StringConcatenate (char *str1, char *str2) {

    int str1Len = stringLen(str1);
    int str2Len = stringLen(str2);

    int i = 0, j = str1Len;
    for (; str2[i] != '\0'; i++, j++)
        str1[j] = str2[i];
    str1[j] = '\0';
}

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

void plural(char** s) {

    int wordCount = sizeof(s);

    for (int i = 0; i < wordCount; i++) {

        int wordLen = stringLen(*(s + i));
        cout << wordLen << endl;

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
    //char* revString = ReverseSentence(str4);
    //cout << revString << endl;

    char* s[] = {"Student", "Party", "Quiz", "Ass"};
    plural(s);

    return 0;
}