#include <iostream>
#include <type_traits>
#include <cctype>
#include <cstddef>
#include <string>
#include "data.hpp"
#include "person.hpp"
#include "customizableError.hpp"
#include "student.hpp"
#include "teacher.hpp"
#include "menu.hpp"

using namespace std;
#define MAX_P 100
#define DIR_TAM "data/tam.dat"
#define DIR_P "data/pessoas.dat"

template<typename TypePessoa, typename... Args>
Person* adicionarPessoa(Person* pessoas[], Args&&... argsPessoa){
    static_assert(is_base_of<Person, TypePessoa>::value, "TypePessoa deve ser um tipo derivqado de Person");
    int oldQnt = Person::getQntOfInstances();
    Person* newP = new TypePessoa(forward<Args>(argsPessoa)...);
    if(newP != nullptr) pessoas[oldQnt] = newP;
    return newP;
}
template<typename TypePessoa>
Person* adicionarPessoa(Person* pessoas[]){
    static_assert(is_base_of<Person, TypePessoa>::value, "TypePessoa deve ser um tipo derivqado de Person");
    int oldQnt = Person::getQntOfInstances();
    Person* newP = new TypePessoa();
    if(newP != nullptr)pessoas[oldQnt] = newP;
    return newP;
}


void listarPessoas(Person* pessoas[]){
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        Person* p = pessoas[i];
        cout << "\nPessoa " << i + 1;
        switch(p->getType()){
            case Person::Type::STUDENT:
                cout << " (Aluno):\n";
                break;
            case Person::Type::TEACHER:
                cout << " (Professor):\n";
                break;
        }
        cout << p->info() << "\n" << endl;
    }
}

void listarAlunos(Person* pessoas[]){
    int countStudent = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        Person* p = pessoas[i];
        if(p->getType() == Person::Type::STUDENT){
            countStudent++;
            cout << "\nAluno "
                 << countStudent << ":\n"
                 << p->info() << "\n" << endl;
        }
    }
}

void listarProfessores(Person* pessoas[]){
    int countTeacher = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        Person* p = pessoas[i];
        if(p->getType() == Person::Type::TEACHER){
            countTeacher++;
            cout << "\nProfessor "
                 << countTeacher << ":\n"
                 << p->info() << "\n" << endl;
        }
    }
}



void startApp(Person* pessoas[], Menu* menuInicial){
    FILE* arqTam = fopen(DIR_TAM, "r");
    FILE* arqPessoas = fopen(DIR_P, "r");
    if(arqTam == nullptr || arqPessoas == nullptr){
        cout << "Arquivos de dados não encontrados\n"
             << "Se essa for sua primeira vez digite S para prosseguir, se não digite qualquer tecla para encerrar o programa"
             << endl;
        char resposta;
        cin >> resposta;
        if(toupper(resposta) == 'S'){
            menuInicial->go();
        }
    }else{

        int tam;
        if(!fread(&tam, sizeof(int), 1, arqTam)){
            throw CustomizableError<runtime_error>("Loading all persons error", {{"type", "size load"}});
        }
        cout << tam << endl;
        for(int i = 0; i < tam; i++){
            cout << "ccc" << i <<endl;
            Person::Type type;
            if(!fread(&type, sizeof(Person::Type), 1, arqPessoas)){
                throw CustomizableError<runtime_error>("Loading all persons error", {{"type", "type load"}, {"at", to_string(i)}});
            }
            cout << "ddd" << i <<endl;
            switch(type){
                case Person::Type::STUDENT:
                    pessoas[i] = new Student();
                    break;
                case Person::Type::TEACHER:
                    pessoas[i] = new Teacher();
                    break;
            }
            cout << "eee" << i <<endl;
            try{
                cout << pessoas[i]->info() <<endl;
                pessoas[i]->load(arqPessoas);
                cout << "fff" << i <<endl;
            }catch(BaseCustomizableError& e){
                e.addMsg({"at", to_string(i)});
                throw;
            }
        }

        fclose(arqTam);
        fclose(arqPessoas);

        menuInicial->go();


    }

}


void endApp(Person* pessoas[]){
    FILE* arqTam = fopen(DIR_TAM, "w");
    FILE* arqPessoas = fopen(DIR_P, "w");

    if(arqTam == nullptr || arqPessoas == nullptr){
        throw CustomizableError<runtime_error>("Saving all persons error", {{"type", "opening files"}});
    }


    int tam = Person::getQntOfInstances();
    if(!fwrite(&tam, sizeof(int), 1, arqTam)){
        throw CustomizableError<runtime_error>("Saving all persons error", {{"type", "size save"}});
    }
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        try{
            pessoas[i]->save(arqPessoas);
            delete pessoas[i];
        }catch(BaseCustomizableError& e){
            e.addMsg({"at", to_string(i)});
            throw;
        }
    }

    fclose(arqTam);
    fclose(arqPessoas);
}


void configMenus(Person* pessoas[]){
    //menus
    Menu* menuPrincipal = new Menu();
    Menu* menuCadastro = new Menu("Cadastro");
    Menu* menuListar = new Menu("Listar");

    //opção geral que aparece em quase todos
    Option opVoltar("Voltar ao menu principal", [&menuPrincipal](){
        menuPrincipal->go();
    });

    //menu cadastro
    menuCadastro->addOp(opVoltar);
    menuCadastro->addOp({"Cadastrar Professor", [&menuCadastro, &pessoas](){
        Person* newTeacher = adicionarPessoa<Teacher>(pessoas);
        newTeacher->cadastrar();
        cout << "\nProfessor cadastrado com sucesso\n"
            << "Informações cadastradas:\n"
            << newTeacher->info() << "\n\n" << endl;

        menuCadastro->go();
    }});
    menuCadastro->addOp({"Cadastrar Aluno", [&menuCadastro, &pessoas](){
        Person* newStudent = adicionarPessoa<Student>(pessoas);
        newStudent->cadastrar();
        cout << "\nAluno cadastrado com sucesso\n"
            << "Informações cadastradas:\n"
            << newStudent->info() << "\n\n" << endl;

        menuCadastro->go();
    }});

    //menu listar pessoas
    menuListar->addOp(opVoltar);
    menuListar->addOp({"Listar todos", [&menuListar, &pessoas](){
        listarPessoas(pessoas);
        menuListar->go();
    }});
    menuListar->addOp({"Listar Professores", [&menuListar, &pessoas](){
        listarProfessores(pessoas);
        menuListar->go();
    }});
    menuListar->addOp({"Listar Alunos", [&menuListar, &pessoas](){
        listarAlunos(pessoas);
        menuListar->go();
    }});


    //menu principal
    menuPrincipal->addOp({"Sair do programa", [](){
        cout << "aqui a função pra sair" << endl;
    }});
    menuPrincipal->addOp({"Cadastrar uma pessoa", [&menuCadastro](){
        menuCadastro->go();
    }});
    menuPrincipal->addOp({"Listar pessoas", [&menuListar](){
        menuListar->go();
    }});


    startApp(pessoas, menuPrincipal);

    endApp(pessoas);

    delete menuPrincipal;
    delete menuCadastro;
    delete menuListar;

}




int main(){
    Person* pessoas[MAX_P];

    configMenus(pessoas);













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
