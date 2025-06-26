#include <string>
#include <regex>
#include "person.hpp"

using namespace std;


int Person::qntOfInstances = 0;


string Person::getCpf() const{return this->cpf;}
string Person::getName() const{return this->name;}
const Date& Person::getBirth() const{return *(this->birth);};
int Person::getQntOfInstances() {return Person::qntOfInstances;}

bool Person::setCpf(const string& cpf){
    bool success = false;
    static const regex cpfToken(R"(\d{3}\.\d{3}\.\d{3}-\d{2})");
    if(regex_match(cpf, cpfToken)){
        this->cpf = cpf;
        success = true;
    }
    return success;
}
bool Person::setName(const string& name){
    this->name = name;
    return true;
}
