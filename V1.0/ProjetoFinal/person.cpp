#include <string>
#include "person.hpp"


int Person::qntOfInstances = 0;


std::string Person::getCpf() const{return this->cpf;}
std::string Person::getName() const{return this->name;}
const Date& Person::getBirth() const{return *(this->birth);};
int Person::getQntOfInstances() {return Person::qntOfInstances;}
