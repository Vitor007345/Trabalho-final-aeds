
#ifndef CUSTOMIZABLEERROR_HPP_INCLUDED
#define CUSTOMIZABLEERROR_HPP_INCLUDED

#include <stdexcept>
#include <exception>
#include <string>
#include <vector>
#include <initializer_list>
#include <type_traits>
#include <utility>

class ErrorMessage{
public:
    std::string name;
    std::string text;
    ErrorMessage(const std::string& name, const std::string& text) : name(name), text(text) {}
};
//Classe criada para poder filtrar no catch, todas as classes de erro customizado independente do tipo
class BaseCustomizableError{
    protected:
        std::vector<ErrorMessage> msgs;
        std::string fullMsgStr;
        BaseCustomizableError(std::initializer_list<ErrorMessage> msgs) : msgs(msgs){}
        BaseCustomizableError(const std::vector<ErrorMessage>& msgs) : msgs(msgs) {}
        void buildFullMsg(const std::string& whatStr) noexcept{
            std::string fullStr;
            fullStr.reserve(150);
            fullStr.append("What: ");
            fullStr.append(whatStr);
            fullStr += "\n";
            for(const auto& msg: this->msgs){
                fullStr += msg.name + ": " + msg.text + "\n";
            }
            this->fullMsgStr = fullStr;
        }
        void buildFullMsg() noexcept{
            buildFullMsg(this->what());
        }
    public:
        virtual ~BaseCustomizableError() = default;
        virtual const std::vector<ErrorMessage>& getMsgs() const noexcept = 0;
        virtual const std::string& getMsg(const std::string& msgName) const = 0;
        const std::string& fullMsg() const{
            return this->fullMsgStr;
        };

        virtual const char* what() const noexcept = 0;
        virtual void addMsg(ErrorMessage&& msg) noexcept = 0;
        virtual void addMsg(const ErrorMessage& msg) noexcept = 0;

};

template<typename BaseException = std::runtime_error>
class CustomizableError: public BaseException, public BaseCustomizableError{
    static_assert(std::is_base_of<std::exception, BaseException>::value, "Error: CustomizableError needs to be derivated from another exception class");
    public:
        CustomizableError(
            const std::string& what,
            std::initializer_list<ErrorMessage> msgs
        ) :
            BaseException(what),
            BaseCustomizableError(msgs)
        {
            buildFullMsg(what);
        }

        CustomizableError(
            const std::string& what,
            const std::vector<ErrorMessage>& msgs
        ) :
            BaseException(what),
            BaseCustomizableError(msgs)
        {
            buildFullMsg(what);
        }

        const std::vector<ErrorMessage>& getMsgs() const noexcept override{
            return this->msgs;
        }

        const std::string& getMsg(const std::string& msgName) const override{
            for(const auto& msg : this->msgs){
                if(msg.name == msgName){
                    return msg.text;
                }
            }
            throw std::runtime_error("MSG NOT FOUND");
        }


        const char* what() const noexcept override{
            return BaseException::what();
        }

         void addMsg(ErrorMessage&& msg) noexcept override{
             this->msgs.push_back(std::move(msg));
         }
         void addMsg(const ErrorMessage& msg) noexcept override{
             this->msgs.push_back(msg);
         }

};

#endif // CUSTOMIZABLEERROR_HPP_INCLUDED
