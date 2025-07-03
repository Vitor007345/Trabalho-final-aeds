#include "utils.hpp"
#include <cctype>
using namespace std;

int numDigits(int num){
    int numOfDigits = 0;
    if(num < 0)num *= -1;
    if(num == 0){
        numOfDigits = 1;
    }else{
        while(num != 0){
            num/= 10;
            numOfDigits++;
        }
    }
    return numOfDigits;

}

string tolowerStr(string str){
    for(char& c : str){
        c = tolower(c);
    }
    return str;
}


bool equalStrIgnoreCase(const string& str1, const string& str2){
    bool igual = false;
    if(str1.size() == str2.size()){
        igual = true;
        int i = 0;
        while(igual && i < str1.size()){
            if(tolower(str1[i]) != tolower(str2[i])){
                igual = false;
            }
            i++;
        }
    }

    return igual;
}


bool includesIgnoreCase(const string& texto, const string& busca){
    bool includes = false;
    if(busca.empty()){
        includes = true;
    }else if(texto.size() < busca.size()){
        includes = false;
    }else{
        int i = 0;
        while(!includes && i <= texto.size() - busca.size()){
            int j = 0;
            includes = true;
            while(includes && j < busca.size()){
                if(tolower(texto[i + j]) != tolower(busca[j])) includes = false;
                j++;
            }
            i++;
        }
    }

    return includes;
}
