#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <vector>
#include <string>
#include <functional>
#include <initializer_list>

class Option{
    private:
        std::string text;
        std::function<void(void)> func;
    public:
        Option(const std::string& text, std::function<void(void)> func);

        const std::string& getText() const noexcept;
        void exec() const noexcept;

        void setOpText(const std::string& text) noexcept;
        void setFunc(std::function<void(void)> func) noexcept;
};

class Menu{
    private:
        std::string title;
        std::vector<Option> options;
    public:
        Menu(const std::string& title = std::string("MENU"));
        Menu(std::initializer_list<Option> options);
        Menu(const std::string& title, std::initializer_list<Option> options);

        void changeTitle(const std::string& title) noexcept;
        const std::string& getTitle() const noexcept;
        int findOpIndex(const std::string& opText) const noexcept;
        void show() const noexcept;
        void scanOption() const;
        void addOp(Option option);
        bool removeOp(const std::string& opText);
        bool removeOp(int opIndex);
        void go() const;


};


#endif // MENU_HPP_INCLUDED
