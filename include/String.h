#include <iostream>
#include <stdexcept>

#ifndef STRING_H
#define STRING_H

#define uint unsigned int

using namespace std;

class String {
    public:
        String();
        String(char*);
        String(const int&);
        String(const String&);

        virtual ~String();

        uint length() const;
        char* toString() const;

        void deletePos(const uint&);
        char* subStr(const uint&) const;
        char* subStr(const uint&, const uint&) const;
        void append(const char&) throw(invalid_argument);
        void deleteCharAt(const uint&) throw(out_of_range);
        void insertInto(const uint&, const char&) throw(invalid_argument);
        void replaceAll(const char&, const char&) throw(invalid_argument);
        void deleteRange(const uint&, const uint&) throw(invalid_argument);

        char& operator[](const uint&) throw(out_of_range);

        String& operator=(const String&);
        String& operator+=(const String&);
        String operator+(const String&) const;
        String& operator+=(const char&) throw(invalid_argument);
        String operator+(const char&) const throw(invalid_argument);

        bool operator>(const String&) const;
        bool operator<(const String&) const;
        bool operator==(const String&) const;
        bool operator!=(const String&) const;
        bool operator>=(const String&) const;
        bool operator<=(const String&) const;

        friend istream& operator>>(istream&, String&);
        friend ostream& operator<<(ostream&, const String&);
    protected:
        char* str;
        uint tamVet;

        char compareTo(const String&) const;
        void cpyVet(char*, const char*, const uint, const uint, const uint);
    private:
};

#endif // STRING_H


