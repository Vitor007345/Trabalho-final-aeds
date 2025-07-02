/*

#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED


#include "person.hpp"
#include "menu.hpp"

class APP{
    private:
        static Person* pessoas[];


        static Menu* menuPrincipal;
        static Menu* menuCadastro;
        static Menu* menuListar;
        static Menu* menuPesquisaNome;
        static Menu* menuPesquisaCPF;
        static Menu* menuExcluir;
        static Menu* menuExcluirTudo;
        static Menu* menuAniversarianteMes;

        static Option opVoltar;

        //funções das funcionalidades
        template<typename TypePessoa, typename... Args>
        static Person* adicionarPessoa(Args&&... argsPessoa);

        template<typename TypePessoa>
        static Person* adicionarPessoa();

        static void listarPessoas() noexcept;
        static void listarAlunos() noexcept;
        static void listarProfessores() noexcept;

        //config de cada menu
        //static void configMenuPrinciapal();
        static void configMenuCadastro();
        //static void configMenuListar();

    public:

        static void createMenus();
        //static void configMenus();
        //static void start();
        //static void end();
};


#endif // APP_HPP_INCLUDED

*/
