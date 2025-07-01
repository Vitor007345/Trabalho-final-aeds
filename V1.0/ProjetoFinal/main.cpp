#include <iostream>
#include <type_traits>
#include "data.hpp"
#include "person.hpp"
#include "customizableError.hpp"
#include "student.hpp"
#include "teacher.hpp"
#include "menu.hpp"
using namespace std;
#define MAX_P 100
template<typename... Args>
void adicionarPessoa(Person* pessoas[], Args&&... argsPessoa){
    pessoas[Person::getQntOfInstances()] = new Person(forward<Args>(argsPessoa)...);
}
void adicionarPessoa(Person* pessoas[]){
    pessoas[Person::getQntOfInstances()] = new Person();
}


int main(){
    Person* pessoas[MAX_P];


    Menu* menuPrincipal = new Menu();

    //opção geral que aparece em quase todos
    Option opVoltar("Voltar ao menu principal", [&menuPrincipal](){
        menuPrincipal->go();
    });

    menuPrincipal->addOp({"Sair do programa", [](){
        cout << "aqui a função pra sair" << endl;
    }});

    //Menu cadastro
    Menu* menuCadastro = new Menu("Cadastro");
    menuCadastro->addOp(opVoltar);

    menuCadastro->addOp({"Cadastrar Professor", [&menuCadastro](){
        cout << "aqui o processo de cadastrar professor" << endl;
        menuCadastro->go();
    }});
    menuCadastro->addOp({"Cadastrar Aluno", [&menuCadastro](){
        cout << "aqui o processo de cadastrar aluno" << endl;
        menuCadastro->go();
    }});

    menuPrincipal->addOp({"Cadastrar uma pessoa", [&menuCadastro](){
        menuCadastro->go();
    }});

    //menu listar pessoas
    Menu* menuListar = new Menu("Listar");
    menuListar->addOp(opVoltar);
    menuListar->addOp({"Listar Professores", [&menuListar](){
        cout << "aqui o processo de listar professor" << endl;
        menuListar->go();
    }});
    menuListar->addOp({"Listar Alunos", [&menuListar](){
        cout << "aqui o processo de listar alunos" << endl;
        menuListar->go();
    }});

    menuPrincipal->addOp({"Listar pessoas", [&menuListar](){
        menuListar->go();
    }});


    menuPrincipal->go();



    delete menuPrincipal;
    delete menuCadastro;


    return 0;
}


/*
try{
        cout << "Person:" <<Person::getQntOfInstances() <<endl;
        cout <<"Student: " <<Student::getQntOfInstances() <<endl;
        Person* p1 = new Person("000.000.000-00", "joaquim", {"11/09/2001"});
        Person* s1 = new Student("111.000.000-00", "irineu", 28, 2, 2001, 123456);
        Person* t1 = new Teacher("111.001.690-12", "josoares", 12, 2, 1940, "Mestre");
        p1->setCpf("000.000.111-00");
        cout << "Person: " << endl;
        cout << p1->info() << endl;
        cout << "Student: " << endl;
        cout << s1->info() << endl;

        cout << "Teacher: " << endl;
        cout << t1->info() << endl;



    }catch(const BaseCustomizableError& e){
        cout << e.fullMsg();
    }

    cout << "Person:" <<Person::getQntOfInstances() <<endl;
    cout <<"Student: " <<Student::getQntOfInstances() <<endl;
    cout << "Teacher: "<<Teacher::getQntOfInstances() <<endl;
*/
