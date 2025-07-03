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
#include "utils.hpp"

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
void escrevePessoa(const Person* p, int pos){
    cout << "\nPessoa " << pos;
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

void listarPessoas(Person* pessoas[]){
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        escrevePessoa(pessoas[i], i + 1);
    }
}

void listarAlunos(Person* pessoas[]){
    int countStudent = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        const Person* p = pessoas[i];
        if(p->getType() == Person::Type::STUDENT){
            countStudent++;
            escrevePessoa(p, countStudent);
        }
    }
}

void listarProfessores(Person* pessoas[]){
    int countTeacher = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        const Person* p = pessoas[i];
        if(p->getType() == Person::Type::TEACHER){
            countTeacher++;
            escrevePessoa(p, countTeacher);
        }
    }
}

std::string searchValue(const string& initStr = "Search"){
    cout << "\n" << initStr << ": ";
    std::string valorBuscado;
    cin.ignore();
    getline(cin, valorBuscado);
    return valorBuscado;
}

int buscaPessoasPorNome(Person* pessoas[], const string& key){
    int countFiltered = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        const Person* p = pessoas[i];
        if(includesIgnoreCase(p->getName(), key)){
            countFiltered++;
            escrevePessoa(p, countFiltered);
        }
    }
    return countFiltered;
}

int buscaAlunosPorNome(Person* pessoas[], const string& key){
    int countFiltered = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        const Person* p = pessoas[i];
        if(p->getType() == Person::Type::STUDENT && includesIgnoreCase(p->getName(), key)){
            countFiltered++;
            escrevePessoa(p, countFiltered);
        }
    }
    return countFiltered;
}

int buscaProfessoresPorNome(Person* pessoas[], const string& key){
    int countFiltered = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        const Person* p = pessoas[i];
        if(p->getType() == Person::Type::TEACHER && includesIgnoreCase(p->getName(), key)){
            countFiltered++;
            escrevePessoa(p, countFiltered);
        }
    }
    return countFiltered;
}


int printAniversariantesDoMes(Person* pessoas[], int mes){
    int countFiltered = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        const Person* p = pessoas[i];
        if(p->getBirth() != nullptr && p->getBirth()->getMonth() == mes){
            countFiltered++;
            escrevePessoa(p, countFiltered);
        }
    }
    return countFiltered;
}

void excluirTodosPorTipo(Person* pessoas[], Person::Type tipo){
    const int oldTam = Person::getQntOfInstances();
    for(int i = 0; i < oldTam; i++){
        if(pessoas[i]->getType() == tipo){
            delete pessoas[i];
            pessoas[i] = nullptr;
        }
    }
    int newTam = compact(pessoas, oldTam);
    if(newTam != Person::getQntOfInstances()){
        throw CustomizableError<runtime_error>("Erro na compactação",
            {{"oldTam", to_string(oldTam)},
            {"newTam", to_string(newTam)},
            {"instances", to_string(Person::getQntOfInstances())}});
    }
}




void startApp(Person* pessoas[], Menu* menuInicial){
    FILE* arqTam = fopen(DIR_TAM, "rb");
    FILE* arqPessoas = fopen(DIR_P, "rb");
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
        for(int i = 0; i < tam; i++){

            int typeInt;
            if(!fread(&typeInt, sizeof(int), 1, arqPessoas)){
                throw CustomizableError<runtime_error>("Loading all persons error", {{"type", "type load"}, {"at", to_string(i)}});
            }
            Person::Type type = (Person::Type)typeInt;
            switch(type){
                case Person::Type::STUDENT:
                    pessoas[i] = new Student();
                    break;
                case Person::Type::TEACHER:
                    pessoas[i] = new Teacher();
                    break;
            }
            try{
                pessoas[i]->load(arqPessoas);
            }catch(BaseCustomizableError& e){
                e.addMsg({"at", to_string(i)});
                cout << e.fullMsg() << endl;
                throw;
            }
        }

        fclose(arqTam);
        fclose(arqPessoas);

        menuInicial->go();


    }

}


void endApp(Person* pessoas[]){
    FILE* arqTam = fopen(DIR_TAM, "wb");
    FILE* arqPessoas = fopen(DIR_P, "wb");

    if(arqTam == nullptr || arqPessoas == nullptr){
        throw CustomizableError<runtime_error>("Saving all persons error", {{"type", "opening files"}});
    }


    int tam = Person::getQntOfInstances();
    if(!fwrite(&tam, sizeof(int), 1, arqTam)){
        throw CustomizableError<runtime_error>("Saving all persons error", {{"type", "size save"}});
    }
    for(int i = 0; i < tam; i++){
        try{
            pessoas[i]->save(arqPessoas);
            delete pessoas[i];
        }catch(BaseCustomizableError& e){
            e.addMsg({"at", to_string(i)});
            cout << e.fullMsg() << endl;
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
    Menu* menuBuscaNome =  new Menu("Busca por Nome");
    Menu* menuBuscaCpf = new Menu("Busca por cpf");
    Menu* menuExcluir = new Menu ("Excluir pessoas");
    Menu* menuExcluirTudo = new Menu("Apagar tudo");
    Menu* menuAniversarianteMes = new Menu("Aniversariantes do mes");


    //opção geral que aparece em quase todos
    Option opVoltar("Voltar ao menu principal", [&menuPrincipal](){
        menuPrincipal->go();
    });

    //menu cadastro
    menuCadastro->addOp(opVoltar);
    menuCadastro->addOp({"Cadastrar Professor", [&menuCadastro, &pessoas](){
        Person* newTeacher = adicionarPessoa<Teacher>(pessoas);
        newTeacher->cadastrar(pessoas);
        cout << "\nProfessor cadastrado com sucesso\n"
            << "Informações cadastradas:\n"
            << newTeacher->info() << "\n\n" << endl;

        menuCadastro->go();
    }});
    menuCadastro->addOp({"Cadastrar Aluno", [&menuCadastro, &pessoas](){
        Person* newStudent = adicionarPessoa<Student>(pessoas);
        newStudent->cadastrar(pessoas);
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

    //menu Pesquisar por nome
    menuBuscaNome->addOp(opVoltar);
    menuBuscaNome->addOp({"Pesquisar todos por nome", [&menuBuscaNome, &pessoas](){
        cout << buscaPessoasPorNome(pessoas, searchValue())
             << " resultados encontrados"
             << endl;
        menuBuscaNome->go();
    }});
    menuBuscaNome->addOp({"Pesquisar professores por nome", [&menuBuscaNome, &pessoas](){
        cout << buscaProfessoresPorNome(pessoas, searchValue())
             << " resultados encontrados"
             << endl;
        menuBuscaNome->go();
    }});

    menuBuscaNome->addOp({"Pesquisar alunos por nome", [&menuBuscaNome, &pessoas](){
        cout << buscaAlunosPorNome(pessoas, searchValue())
             << " resultados encontrados"
             << endl;
        menuBuscaNome->go();
    }});

    //menu busca cpf
    menuBuscaCpf->addOp(opVoltar);
    menuBuscaCpf->addOp({"Pesquisar todos por CPF", [&menuBuscaCpf, &pessoas](){
        std::string cpfBuscado = searchValue("Digite o cpf que quer buscar");
        Person* pBuscado = find<Person*>(pessoas, Person::getQntOfInstances(), [&cpfBuscado](Person* elem){
            return elem->getCpf() == cpfBuscado;
        }, nullptr);
        if(pBuscado != nullptr){
            escrevePessoa(pBuscado, 1);
        }else{
            cout << "Não existe uma pessoa com esse cpf" << endl;
        }
        menuBuscaCpf->go();
    }});

    menuBuscaCpf->addOp({"Pesquisar Professores por CPF", [&menuBuscaCpf, &pessoas](){
        std::string cpfBuscado = searchValue("Digite o cpf que quer buscar");
        Person* pBuscado = find<Person*>(pessoas, Person::getQntOfInstances(), [&cpfBuscado](Person* elem){
            return elem->getType() == Person::Type::TEACHER && elem->getCpf() == cpfBuscado;
        }, nullptr);
        if(pBuscado != nullptr){
            escrevePessoa(pBuscado, 1);
        }else{
            cout << "Não existe um Professor com esse cpf" << endl;
        }
        menuBuscaCpf->go();
    }});

    menuBuscaCpf->addOp({"Pesquisar Alunos por CPF", [&menuBuscaCpf, &pessoas](){
        std::string cpfBuscado = searchValue("Digite o cpf que quer buscar");
        Person* pBuscado = find<Person*>(pessoas, Person::getQntOfInstances(), [&cpfBuscado](Person* elem){
            return elem->getType() == Person::Type::STUDENT && elem->getCpf() == cpfBuscado;
        }, nullptr);
        if(pBuscado != nullptr){
            escrevePessoa(pBuscado, 1);
        }else{
            cout << "Não existe um Aluno com esse cpf" << endl;
        }
        menuBuscaCpf->go();
    }});

    //menu excluir pessoas
    menuExcluir->addOp(opVoltar);
    menuExcluir->addOp({"Excluir Professor (Por CPF)", [&menuExcluir, &pessoas](){
        std::string cpfBuscado = searchValue("Digite o cpf da pessoa que quer excluir");
        int pos;
        Person* pBuscado = find<Person*>(pessoas, Person::getQntOfInstances(), [&cpfBuscado, &pos](Person* elem, int i){
            pos = i;
            return elem->getType() == Person::Type::TEACHER && elem->getCpf() == cpfBuscado;
        }, nullptr);
        if(pBuscado != nullptr){
            int tam = Person::getQntOfInstances();
            delete pBuscado;
            shiftMenusUm(pessoas, tam, pos);
            cout << "Professor deletado com sucesso" << endl;
        }else{
            cout << "Não existe um Professor com esse cpf" << endl;
        }
        menuExcluir->go();
    }});

    menuExcluir->addOp({"Excluir Aluno (Por CPF)", [&menuExcluir, &pessoas](){
        std::string cpfBuscado = searchValue("Digite o cpf da pessoa que quer excluir");
        int pos;
        Person* pBuscado = find<Person*>(pessoas, Person::getQntOfInstances(), [&cpfBuscado, &pos](Person* elem, int i){
            pos = i;
            return elem->getType() == Person::Type::STUDENT && elem->getCpf() == cpfBuscado;
        }, nullptr);
        if(pBuscado != nullptr){
            int tam = Person::getQntOfInstances();
            delete pBuscado;
            shiftMenusUm(pessoas, tam, pos);
            cout << "Aluno deletado com sucesso" << endl;
        }else{
            cout << "Não existe um Aluno com esse cpf" << endl;
        }
        menuExcluir->go();
    }});

    //menu apagarTudo
    menuExcluirTudo->addOp(opVoltar);
    menuExcluirTudo->addOp({"Excluir todos os professores", [&pessoas, &menuExcluirTudo, &menuPrincipal](){
        try{
            excluirTodosPorTipo(pessoas, Person::Type::TEACHER);
            cout << "Todos professores excluidos com sucesso" << endl;
            menuExcluirTudo->go();
        }catch(const BaseCustomizableError& e){
            cout << "Erro ao excluir professores:\n"
                 << e.fullMsg()
                 << endl;
            menuPrincipal->go();
        }
    }});
    menuExcluirTudo->addOp({"Excluir todos os alunos", [&pessoas, &menuExcluirTudo, &menuPrincipal](){
        try{
            excluirTodosPorTipo(pessoas, Person::Type::STUDENT);
            cout << "Todos alunos excluidos com sucesso" << endl;
            menuExcluirTudo->go();
        }catch(const BaseCustomizableError& e){
            cout << "Erro ao excluir alunos:\n"
                 << e.fullMsg()
                 << endl;
            menuPrincipal->go();
        }
    }});

    //menu aniversariantes do mes
    int mesAbuscar = Date().getMonth(); //começa com o mês atual
    menuAniversarianteMes->addOp(opVoltar);
    menuAniversarianteMes->addOp({"Informar mês a ser pesquisado", [&menuAniversarianteMes, &mesAbuscar](){
        cout << "Digite o mês: ";
        cin >> mesAbuscar;
        menuAniversarianteMes->go();
    }});
    menuAniversarianteMes->addOp({"Listar aniversáriantes do mês", [&menuAniversarianteMes, &mesAbuscar, &pessoas](){
        cout << printAniversariantesDoMes(pessoas, mesAbuscar)
             << " resultados encontrados"
             << endl;
        menuAniversarianteMes->go();
    }});



    //menu principal
    menuPrincipal->addOp({"Sair do programa", [&pessoas](){
        endApp(pessoas);
    }});
    menuPrincipal->addOp({"Cadastrar uma pessoa", [&menuCadastro](){
        menuCadastro->go();
    }});
    menuPrincipal->addOp({"Listar pessoas", [&menuListar](){
        menuListar->go();
    }});
    menuPrincipal->addOp({"Pesquisar por nome", [&menuBuscaNome](){
        menuBuscaNome->go();
    }});
    menuPrincipal->addOp({"Pesquisar por CPF", [&menuBuscaCpf](){
        menuBuscaCpf->go();
    }});
    menuPrincipal->addOp({"Excluir pessoa", [&menuExcluir](){
        menuExcluir->go();
    }});
    menuPrincipal->addOp({"Apagar todas as pessoas cadastradas", [&menuExcluirTudo](){
        menuExcluirTudo->go();
    }});

    menuPrincipal->addOp({"Aniversariante do mês", [&menuAniversarianteMes](){
        menuAniversarianteMes->go();
    }});

    startApp(pessoas, menuPrincipal);



    delete menuPrincipal;
    delete menuCadastro;
    delete menuListar;
    delete menuBuscaNome;
    delete menuBuscaCpf;
    delete menuExcluir;
    delete menuExcluirTudo;
    delete menuAniversarianteMes;

}




int main(){
    Person* pessoas[MAX_P];
    configMenus(pessoas);
    return 0;
}

