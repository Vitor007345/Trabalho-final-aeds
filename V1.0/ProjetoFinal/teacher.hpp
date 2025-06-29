#ifndef TEACHER_HPP_INCLUDED
#define TEACHER_HPP_INCLUDED

#include <string>
#include <type_traits>
#include <utility>
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
        static const std::string titulacoes[];
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

            if(titulo == titulacoes[(int)Titulacao::Nenhuma]){
                this->titulo = Titulacao::Nenhuma;
            }else if(titulo == titulacoes[(int)Titulacao::Especialista]){
                this->titulo = Titulacao::Especialista;
            }else if(titulo == titulacoes[(int)Titulacao::Mestre]){
                this->titulo = Titulacao::Mestre;
            }else if(titulo == titulacoes[(int)Titulacao::Doutor]){
                this->titulo = Titulacao::Doutor;
            }else{
                success = false;
            }
            return success;
        }

        std::string info() const noexcept override{
            return Person::info() + "\nTitulação: " + this->getTituloStr();
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
