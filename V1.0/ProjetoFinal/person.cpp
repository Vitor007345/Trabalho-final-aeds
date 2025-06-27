#include <iostream>
#include <string>
#include <regex>
#include "customizableError.hpp"
#include "person.hpp"

using namespace std;


int Person::qntOfInstances = 0;


Person::Person(): cpf(""), name(""), birth(nullptr) {}

Person::Person(const string& cpf, const string& name): Person(){
    if(!this->setCpf(cpf)){
        throw CustomizableError<invalid_argument>("Person Construction error", {{"type", "Invalid cpf"}});
    }else if(!this->setName(name)){
        throw CustomizableError<invalid_argument>("Person Construction error", {{"type", "Invalid name"}});
    }
}
Person::Person(const std::string& cpf, const std::string& name, int day, int month, int year): Person(cpf, name) {
    this->birth = new Date(day, month, year);
}

Person::Person(const std::string& cpf, const std::string& name, const Date& birth) : Person(cpf, name){
    this->setBirth(birth);
}
Person::Person(const string& cpf, const string& name, const Date* birth): Person(cpf, name, *birth) {}

Person::~Person(){
    if(this->getBirth() != nullptr){
        delete this->birth;
    }
}

string Person::getCpf() const noexcept{return this->cpf;}
string Person::getName() const noexcept{return this->name;}
const Date* Person::getBirth() const noexcept{return this->birth;};
int Person::getQntOfInstances() noexcept{return Person::qntOfInstances;}

bool Person::setCpf(const string& cpf) noexcept{
    bool success = false;
    static const regex cpfRegex(R"(\d{3}\.\d{3}\.\d{3}-\d{2})");
    if(regex_match(cpf, cpfRegex)){
        this->cpf = cpf;
        success = true;
    }
    return success;
}
bool Person::setName(const string& name) noexcept{
    this->name = name;
    return true;
}

std::string Person::info() const noexcept{
    std::string info;
    info.reserve(100);
    info.append("Cpf: ");
    info.append(this->getCpf());
    info.append("\nNome: ");
    info.append(this->getName());
    info.append("\nData de nascimento: ");
    if(this->getBirth() != nullptr){
        info.append(this->getBirth()->stringify());
    }

    return info;
}


