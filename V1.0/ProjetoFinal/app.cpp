


/*
#include "person.hpp"
#include "menu.hpp"


#define MAX_P 100

using namespace std;

Person* APP::pessoas[MAX_P];
Menu* APP::menuPrincipal = nullptr;
Menu* APP::menuCadastro = nullptr;
Menu* APP::menuListar = nullptr;
Menu* APP::menuPesquisaNome = nullptr;
Menu* APP::menuPesquisaCPF = nullptr;
Menu* APP::menuExcluir = nullptr;
Menu* APP::menuExcluirTudo = nullptr;
Menu* APP::menuAniversarianteMes = nullptr;
//funções das funcionalidades

template<typename TypePessoa, typename... Args>
Person* APP::adicionarPessoa(Args&&... argsPessoa){
    static_assert(is_base_of<Person, TypePessoa>::value, "TypePessoa deve ser um tipo derivqado de Person");
    int oldQnt = Person::getQntOfInstances();
    Person* newP = new TypePessoa(forward<Args>(argsPessoa)...);
    if(newP != nullptr) APP::pessoas[oldQnt] = newP;
    return newP;
}
template<typename TypePessoa>
Person* APP::adicionarPessoa(){
    static_assert(is_base_of<Person, TypePessoa>::value, "TypePessoa deve ser um tipo derivqado de Person");
    int oldQnt = Person::getQntOfInstances();
    Person* newP = new TypePessoa();
    if(newP != nullptr) APP::pessoas[oldQnt] = newP;
    return newP;
}


void APP::listarPessoas() noexcept{
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        Person* p = APP::pessoas[i];
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

void APP::listarAlunos() noexcept{
    int countStudent = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        Person* p = APP::pessoas[i];
        if(p->getType() == Person::Type::STUDENT){
            countStudent++;
            cout << "\nAluno "
                 << countStudent << ":\n"
                 << p->info() << "\n" << endl;
        }
    }
}

void APP::listarProfessores() noexcept{
    int countTeacher = 0;
    for(int i = 0; i < Person::getQntOfInstances(); i++){
        Person* p = APP::pessoas[i];
        if(p->getType() == Person::Type::TEACHER){
            countTeacher++;
            cout << "\nProfessor "
                 << countTeacher << ":\n"
                 << p->info() << "\n" << endl;
        }
    }
}

//opção geral que aparece em quase todos
Option APP::opVoltar("Voltar ao menu principal", [&menuPrincipal](){
    menuPrincipal->go();
});


//funções da config
void APP::createMenus(){
    menuPrincipal = new Menu();
    menuCadastro = new Menu("Cadastro");
    menuListar = new Menu("Listar");
    menuPesquisaNome = new Menu("Pesquisa por nome");
    menuPesquisaCPF = new Menu("Pesquisa por CPF");
    menuExcluir = new Menu("Excluir pessoa");
    menuExcluirTudo = new Menu("Apagar todos");
    menuAniversarianteMes = new Menu("Aniversariante do mês");
}

void APP::configMenuCadastro(){
    menuCadastro->addOp(opVoltar);
    menuCadastro->addOp({"Cadastrar Professor", [&menuCadastro, &pessoas](){
        Person* newTeacher = adicionarPessoa<Teacher>();
        newTeacher->cadastrar();
        cout << "\nProfessor cadastrado com sucesso\n"
            << "Informações cadastradas:\n"
            << newTeacher->info() << "\n\n" << endl;

        menuCadastro->go();
    }});
    menuCadastro->addOp({"Cadastrar Aluno", [&menuCadastro, &pessoas](){
        Person* newStudent = adicionarPessoa<Student>();
        newStudent->cadastrar();
        cout << "\nAluno cadastrado com sucesso\n"
            << "Informações cadastradas:\n"
            << newStudent->info() << "\n\n" << endl;

        menuCadastro->go();
    }});
}
*/



