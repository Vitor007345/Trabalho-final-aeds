#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <initializer_list>
#include "menu.hpp"

using namespace std;

Option::Option(const string& text, function<void(void)> func){
    this->setOpText(text);
    this->setFunc(func);
}
const string& Option::getText() const noexcept{
    return this->text;
}
void Option::exec() const noexcept{
    this->func();
}

void Option::setOpText(const string& text) noexcept{
    this->text = text;
}
void Option::setFunc(function<void(void)> func) noexcept{
    this->func = func;
}




Menu::Menu(std::initializer_list<Option> options) : options(options) {}

void Menu::show(const string& msg) const noexcept{
    cout << "============" << msg << "============\n\n";
    for(int i = 0; i < this->options.size(); i++){
        cout << i << " - " << this->options[i].getText() << "\n";
    }
    cout << endl;
}
void Menu::scanOption() const{
    int opIndex;
    bool erro;
    do{
        cin >> opIndex;
        erro = opIndex < 0 || opIndex >= this->options.size();
        if(erro){
            cout << "Opção invalida\nOpções validas são de 0 a "
                 << this->options.size() - 1 << "\n"
                 << "Digite novamente: " << endl;

        }
    }while(erro);

    this->options[opIndex].exec();
}
int Menu::findOpIndex(const std::string& opText) const noexcept{
    int index = 0;
    bool encontrou = false;
    while(!encontrou && index < this->options.size()){
        if(this->options[index].getText() == opText){
            encontrou = true;
        }
        index++;
    }
    return encontrou? index : -1;
}
void Menu::addOp(Option option){
    this->options.push_back(option);
}
bool Menu::removeOp(const std::string& opText){
    int index = this->findOpIndex(opText);
    bool success = false;
    if(index != -1){
        success = this->removeOp(index);
    }
    return success;
}
bool Menu::removeOp(int opIndex){
    bool success = false;
    if(opIndex >= 0 && opIndex < this->options.size()){
        this->options.erase(this->options.begin() + opIndex);
        success = true;
    }
    return success;
}
