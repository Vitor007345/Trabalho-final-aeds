#include "utils.hpp"

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
