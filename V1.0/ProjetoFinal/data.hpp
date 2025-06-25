#include <string>

#ifndef DATA_HPP_INCLUDED
#define DATA_HPP_INCLUDED

//classe data feita para ser sempre válida, por isso não tem o método para conferir se é valido
class Date{
    private:
        int day;
        int month;
        int year;

        static bool validateDay(int day, int month, int year);
        static bool validateMonth(int month);
        static bool validateYear(int year);
        static bool validateDate(int day, int month, int year);
        static bool isLeapYear(int year);
        static int numOfDaysInMonth(int month, int year);
    public:
        Date();
        Date(int day, int month, int year);
        Date(const std::string& dateStr);

        int getDay() const;
        int getMonth() const;
        int getYear() const;

        std::string stringify() const;

        bool setDay(int day);
        bool setMonth(int month);
        bool setYear(int year);

        bool setDate();
        bool setDate(int day, int month, int year);
        bool setDate(const std::string& dateStr);


        bool isLeap() const;
        int numOfDaysInMonth() const;
        std::string strMonth() const;
        std::string weekDay() const;

};

#endif // DATA_HPP_INCLUDED
