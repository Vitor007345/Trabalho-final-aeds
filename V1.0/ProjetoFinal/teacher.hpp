#ifndef TEACHER_HPP_INCLUDED
#define TEACHER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include "utils.hpp"
#include "customizableError.hpp"
#include "person.hpp"

enum class Titulacao{
    Nenhuma = 0,
    Especialista = 1,
    Mestre = 2,
    Doutor = 3
};
class Teacher : public Person{
    private:
        Titulacao titulo;
        static const std::string titulacoes[4];
        static int qntOfInstances;


        template<typename StringCpf, typename StringName>
        struct checkTypes{
            static constexpr bool value =
                std::is_convertible<StringCpf, std::string>::value &&
                std::is_convertible<StringName, std::string>::value;
        };


        void basicConfigConstruction(Titulacao titulo = Titulacao::Nenhuma){
            if(!this->setTitulo(titulo)){
                throw CustomizableError<std::invalid_argument>("Teacher construction Error", {{"type", "invalid titulo"}, {"details", "invalid value: " + std::to_string((int)titulo)}});
            }
            qntOfInstances++;
        }

        void basicConfigConstruction(const std::string& titulo){
            if(!this->setTitulo(titulo)){
                throw CustomizableError<std::invalid_argument>("Teacher construction Error", {{"type", "invalid titulo"}, {"details", std::string("string ") + titulo + " invalid"}});
            }
            qntOfInstances++;
        }


        template<typename StringCpf, typename StringName>
        void configConstruction(Titulacao titulo){
            static_assert(
                checkTypes<StringCpf, StringName>::value,
                "cpf e nome devem ser conversiveis pra string e titulo deve ser Titulacao ou string"
            );
            this->basicConfigConstruction(titulo);
        }

        template<typename StringCpf, typename StringName>
        void configConstruction(const std::string& titulo){
            static_assert(
                checkTypes<StringCpf, StringName>::value,
                "cpf e nome devem ser conversiveis pra string e titulo deve ser Titulacao ou string"
            );
            this->basicConfigConstruction(titulo);
        }

    public:

        Type getType() const noexcept override{
            return Person::Type::TEACHER;
        }

        Teacher() : Person(){
            this->basicConfigConstruction();
        }

        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, Titulacao titulo = Titulacao::Nenhuma)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name))
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }
        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, const std::string& titulo)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name))
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }
        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, int day, int month, int year, Titulacao titulo = Titulacao::Nenhuma)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name), day, month, year)
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }
        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, int day, int month, int year, const std::string& titulo)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name), day, month, year)
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }
        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, const Date& birth, Titulacao titulo = Titulacao::Nenhuma)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name), birth)
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }
        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, const Date* birth, Titulacao titulo = Titulacao::Nenhuma)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name), birth)
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }
        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, const Date& birth, const std::string& titulo)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name), birth)
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }
        template<typename StringCpf, typename StringName>
        Teacher(StringCpf&& cpf, StringName&& name, const Date* birth, const std::string& titulo)
            : Person(std::forward<StringCpf>(cpf), std::forward<StringName>(name), birth)
        {
            this->configConstruction<StringCpf, StringName>(titulo);
        }

        ~Teacher(){
            qntOfInstances--;
        }

        Titulacao getTitulo() const noexcept{return this->titulo;}
        const std::string& getTituloStr() const noexcept{return titulacoes[(int)this->titulo];}
        static int getQntOfInstances() noexcept{return qntOfInstances;}

        bool setTitulo(Titulacao titulo) noexcept{
            this->titulo = titulo;
            return true;
        }
        bool setTitulo(const std::string& titulo) noexcept{
            bool success = true;

            if(equalStrIgnoreCase(titulo, titulacoes[(int)Titulacao::Nenhuma])){
                this->titulo = Titulacao::Nenhuma;
            }else if(equalStrIgnoreCase(titulo, titulacoes[(int)Titulacao::Especialista])){
                this->titulo = Titulacao::Especialista;
            }else if(equalStrIgnoreCase(titulo, titulacoes[(int)Titulacao::Mestre])){
                this->titulo = Titulacao::Mestre;
            }else if(equalStrIgnoreCase(titulo, titulacoes[(int)Titulacao::Doutor])){
                this->titulo = Titulacao::Doutor;
            }else{
                success = false;
            }
            return success;
        }

        std::string info() const noexcept override{
            return Person::info() + "\nTitulação: " + this->getTituloStr();
        }

        void cadastrar() noexcept override{
            Person::cadastrar();
            bool erro;
            std::string titulo;
            do{
                std::cout << "Digite o titulo(";
                bool primeiro = true;
                for(const std::string& t: titulacoes){
                    if(primeiro){
                        primeiro = false;
                    }else{
                        std::cout << ", ";
                    }
                    std::cout << t;
                }
                std::cout << "): ";
                std::cin >> titulo;
                erro = !this->setTitulo(titulo);
                if(erro){
                    std::cout << "Titulo invalido" << std::endl;
                }
            }while(erro);
        }

        void save(FILE* file) const override{
            Person::save(file);
            Titulacao titulo = this->getTitulo();
            if(!fwrite(&titulo, sizeof(Titulacao), 1, file)){
                throw CustomizableError<std::runtime_error>("Techer saving error", {{"type", "titulo save"}});
            }
        }
        void load(FILE* file) override{
            Person::load(file);
            Titulacao titulo;
            if(!fread(&titulo, sizeof(Titulacao), 1, file)){
                throw CustomizableError<std::runtime_error>("Teacher loading error", {{"type", "titulo load"}});
            }
            if(!this->setTitulo(titulo)){
                throw CustomizableError<std::runtime_error>("Teacher loading error", {{"type", "titulo atribution"}});
            }
        }


};
int Teacher::qntOfInstances = 0;
const std::string Teacher::titulacoes[] = {
    "Nenhuma",
    "Especialista",
    "Mestre",
    "Doutor"
};


#endif // TEACHER_HPP_INCLUDED
