#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <string>
#include <functional>

int numDigits(int num);
std::string tolowerStr(std::string str);
bool equalStrIgnoreCase(const std::string& str1, const std::string& str2);
bool includesIgnoreCase(const std::string& texto, const std::string& busca);

template<typename T>
T find(T vetor[], int tam, std::function<bool(T)> funcTest, T errorValue){
    bool encontrou = false;
    T valueFounded = errorValue;
    int i = 0;
    while(!encontrou && i < tam){
        if(funcTest(vetor[i])){
            encontrou = true;
            valueFounded = vetor[i];
        }
        i++;
    }
    return valueFounded;
}

template<typename T>
T find(T vetor[], int tam, std::function<bool(T, int)> funcTest, T errorValue){
    bool encontrou = false;
    T valueFounded = errorValue;
    int i = 0;
    while(!encontrou && i < tam){
        if(funcTest(vetor[i], i)){
            encontrou = true;
            valueFounded = vetor[i];
        }
        i++;
    }
    return valueFounded;
}


template<typename T>
void shiftMenusUm(T vetor[], int tam, int pos){
    for(int i = pos; i < tam - 1; i++){
        vetor[i] = vetor[i + 1];
    }
}

template<typename T>
int compact(T* vetor[], int tam){
    int qntNull = 0;
    for(int i = 0; i < tam - qntNull; i++){
        while(vetor[i + qntNull] == nullptr && i + qntNull < tam){ //prescisa verificar dnv, pq o valor mudou
            qntNull++;
        }
        if(qntNull > 0 && i + qntNull < tam){ //prescisa verificar dnv, pq o valor mudou
            vetor[i] = vetor[i + qntNull];
        }
    }
    return tam - qntNull; //retorna o novo tamanho
}

#endif // UTILS_HPP_INCLUDED
