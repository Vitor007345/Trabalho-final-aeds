#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include <cstddef>
#include "customizableError.hpp"
#include "person.hpp"


using namespace std;


int Person::qntOfInstances = 0;

template<typename T1, typename T2>
void Person::personConstructionLogic(T1&& cpf, T2&& name){
    if(!this->setCpf(forward<T1>(cpf))){
        throw CustomizableError<invalid_argument>("Person Construction error", {{"type", "Invalid cpf"}});
    }else if(!this->setName(forward<T2>(name))){
        throw CustomizableError<invalid_argument>("Person Construction error", {{"type", "Invalid name"}});
    }
}

Person::Person(): cpf(""), name(""), birth(nullptr) {
    qntOfInstances++;
}


Person::Person(const string& cpf, const string& name): Person(){
    this->personConstructionLogic(cpf, name);
}
Person::Person(string&& cpf, string&& name) : Person(){
    this->personConstructionLogic(move(cpf), move(name));
}
Person::Person(const std::string& cpf, std::string&& name) : Person(){
    this->personConstructionLogic(cpf, move(name));
}
Person::Person(std::string&& cpf, const std::string& name) : Person(){
    this->personConstructionLogic(move(cpf), name);
}



Person::Person(const std::string& cpf, const std::string& name, int day, int month, int year): Person(cpf, name) {
    this->birth = new Date(day, month, year);
}
Person::Person(std::string&& cpf, std::string&& name, int day, int month, int year) : Person(move(cpf), move(name)) {
    this->birth = new Date(day, month, year);
}
Person::Person(const std::string& cpf, std::string&& name, int day, int month, int year) : Person(cpf, move(name)){
    this->birth = new Date(day, month, year);
}
Person::Person(std::string&& cpf, const std::string& name, int day, int month, int year) : Person(move(cpf), name){
    this->birth = new Date(day, month, year);
}




Person::Person(const std::string& cpf, const std::string& name, const Date& birth) : Person(cpf, name){
    this->setBirth(birth);
}
Person::Person(std::string&& cpf,  std::string&& name, const Date& birth):Person(move(cpf), move(name)){
    this->setBirth(birth);
}
Person::Person(std::string&& cpf, const std::string& name, const Date& birth):Person(move(cpf), name){
    this->setBirth(birth);
}
Person::Person(const std::string& cpf,  std::string&& name, const Date& birth):Person(cpf, move(name)){
    this->setBirth(birth);
}


Person::Person(const string& cpf, const string& name, const Date* birth): Person(cpf, name, *birth) {}
Person::Person(std::string&& cpf,  std::string&& name, const Date* birth): Person(move(cpf), move(name), *birth) {}
Person::Person(std::string&& cpf, const std::string& name, const Date* birth): Person(move(cpf), name, *birth) {}
Person::Person(const std::string& cpf,  std::string&& name, const Date* birth): Person(cpf, move(name), *birth) {}



Person::~Person(){
    qntOfInstances--;
    if(this->getBirth() != nullptr){
        delete this->birth;
    }
}

const string& Person::getCpf() const noexcept{return this->cpf;}
const string& Person::getName() const noexcept{return this->name;}
const Date* Person::getBirth() const noexcept{return this->birth;};
int Person::getQntOfInstances() noexcept{return Person::qntOfInstances;}



bool Person::setCpf(const string& cpf) noexcept{
    string copy = cpf;
    return this->setCpf(move(copy));
}
bool Person::setName(const string& name) noexcept{
    string copy = name;
    return this->setName(move(copy));
}

bool Person::setCpf(string&& cpf) noexcept{
    bool success = false;
    static const regex cpfRegex1(R"(\d{3}\.\d{3}\.\d{3}-\d{2})");
    static const regex cpfRegex2(R"(\d{11})");
    if(regex_match(cpf, cpfRegex1)){
        this->cpf = move(cpf);
        success = true;
    }else if(regex_match(cpf, cpfRegex2)){
        this->cpf = "";
        for(int i = 0; i < cpf.size(); i++){
            if(i == 9) this->cpf += '-';
            else if(i != 0 && i % 3 == 0) this->cpf += '.';
            this->cpf += cpf[i];
        }
        success = true;
    }
    return success;
}
bool Person::setName(string&& name) noexcept{
    this->name = move(name);
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

void Person::cadastrar(Person* pessoas[]) noexcept{
    bool erro;
    string cpf;
    do{
        cout << "Digite o cpf: ";
        cin >> cpf;
        erro = !this->setCpf(move(cpf));
        if(erro){
            cout << "Cpf invalido" << endl;
        }
        if(!erro){
            int i = 0;
            while(!erro && i < Person::getQntOfInstances()){
                if(pessoas[i] != this && pessoas[i]->getCpf() == this->getCpf()){
                    erro = true;
                    cout << "Já existe uma pessoa cadastrada com esse cpf" << endl;
                }
                i++;
            }
        }
    }while(erro);
    string name;
    do{
        cout << "Digite o nome: ";
        cin.ignore();
        getline(cin, name);
        erro = !this->setName(move(name));
        if(erro){
            cout << "Nome invalido" << endl;
        }
    }while(erro);
    string birthStr;
    do{
        cout << "Digite a data de nascimento(xx/xx/xxxx): ";
        cin >> birthStr;
        erro = !this->setBirth(birthStr);
        if(erro){
            cout << "Data invalida" << endl;
        }
    }while(erro);
}

void Person::save(FILE* file) const{
    if(file == nullptr){
        throw CustomizableError<invalid_argument>("Person saving error",  {{"type", "file cant be null"}});
    }

    //salvar tipo
    int pType = (int)this->getType();
    if(!fwrite(&pType, sizeof(int), 1, file)){
        throw CustomizableError<runtime_error>("Person saving error", {{"type", "Person::Type save"}});
    }

    //salvar cpf
    size_t sizeCpf = this->getCpf().size();
    if(!fwrite(&sizeCpf, sizeof(size_t), 1, file)){
        throw CustomizableError<runtime_error>("Person saving error", {{"type", "cpf save"}, {"details", "size save"}});
    }
    if(!fwrite(this->getCpf().c_str(), sizeof(char), sizeCpf, file)){
        throw CustomizableError<runtime_error>("Person saving error", {{"type", "cpf save"}, {"details", "content save"}});
    }
    //salvar nome
    size_t sizeName = this->getName().size();
    if(!fwrite(&sizeName, sizeof(size_t), 1, file)){
        throw CustomizableError<runtime_error>("Person saving error", {{"type", "name save"}, {"details", "size save"}});
    }
    if(!fwrite(this->getName().c_str(), sizeof(char), sizeName, file)){
        throw CustomizableError<runtime_error>("Person saving error", {{"type", "name save"}, {"details", "content save"}});
    }
    //salvar nascimento
    bool hasBirth = this->getBirth() != nullptr;
    if(!fwrite(&hasBirth, sizeof(bool), 1, file)){
        throw CustomizableError<runtime_error>("Person saving error", {{"type", "birth save"}, {"details", "existance save"}});
    }
    if(hasBirth){
        if(!fwrite(this->getBirth(), sizeof(Date), 1, file)){
            throw CustomizableError<runtime_error>("Person saving error", {{"type", "birth save"}, {"details", "content save"}});
        }
    }
}

void Person::load(FILE* file){
    if(file == nullptr){
        throw CustomizableError<invalid_argument>("Person loading error",  {{"type", "file cant be null"}});
    }

    //leitura cpf
    size_t cpfSize;
    if(!fread(&cpfSize, sizeof(size_t), 1, file)){
        throw CustomizableError<runtime_error>("Person loading error", {{"type", "cpf load"}, {"details", "size load"}});
    }
    char* cpfBuffer = new char[cpfSize];
    if(!fread(cpfBuffer, sizeof(char), cpfSize, file)){
        throw CustomizableError<runtime_error>("Person loading error", {{"type", "cpf load"}, {"details", "content load"}});
    }
    string cpf(cpfBuffer, cpfSize);

    //leitura nome
    size_t nameSize;
    if(!fread(&nameSize, sizeof(size_t), 1, file)){
        throw CustomizableError<runtime_error>("Person loading error", {{"type", "name load"}, {"details", "size load"}});
    }
    char* nameBuffer = new char[nameSize];
    if(!fread(nameBuffer, sizeof(char), nameSize, file)){
        throw CustomizableError<runtime_error>("Person loading error", {{"type", "name load"}, {"details", "content load"}});
    }
    string name(nameBuffer, nameSize);

    //leitura data
    bool hasBirth;
    Date birth;
    if(!fread(&hasBirth, sizeof(bool), 1, file)){
        throw CustomizableError<runtime_error>("Person loading error", {{"type", "birth load"}, {"details", "existance load"}});
    }
    if(hasBirth){
        if(!fread(&birth, sizeof(Date), 1, file)){
            throw CustomizableError<runtime_error>("Person loading error", {{"type", "birth load"}, {"details", "content load"}});
        }
    }

    //atribuições
    if(!this->setCpf(move(cpf))){
        throw CustomizableError<runtime_error>("Person loading error", {{"type", "cpf atribution"}});
    }
    if(!this->setName(move(name))){
        throw CustomizableError<runtime_error>("Person loading error", {{"type", "name atribution"}});
    }
    if(hasBirth){
        if(!this->setBirth(birth)){
            throw CustomizableError<runtime_error>("Person loading error", {{"type", "birth atribution"}});
        }
    }else {
        this->birth = nullptr;
    }

}



