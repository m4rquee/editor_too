#include "String.h"

#include <iostream>
#include <stdlib.h>
#include <stdexcept>

#define Construtor String::String

Construtor() : str(new char[1]), tamVet(1) {
    this->str[0] = '\0';
}

Construtor(char* _palavra) {
    uint tam;
    for (tam = 0; *(_palavra + tam++) != '\0'; ) {}

    this->tamVet = tam;
    this->str = new char[tam];
    for (uint i = 0; i < tam; i++)
        this->str[i] = _palavra[i];
}

Construtor(const int& _tam) : tamVet(_tam + 1) {
    unsigned int aux = _tam;
    this->str = new char[this->tamVet];

    for (uint i = 0; i < aux; i++)
        *(this->str + i) = ' ';

    this->str[aux] = '\0';
}

Construtor(const String& _aux) : tamVet(_aux.tamVet) {
    this->str = new char[this->tamVet];
    this->cpyVet(this->str, _aux.str, 0, 0, _aux.tamVet);
}

String& String::operator=(const String& _aux) {
    if (this == &_aux)
        return *this;

    if (this->tamVet != _aux.tamVet) {
        this->tamVet = _aux.tamVet;
        this->str = new char[this->tamVet];
    }

    this->cpyVet(this->str, _aux.str, 0, 0, this->tamVet);

    return *this;
}

String String::operator+(const String& _aux) const {
    String ret(this->tamVet + _aux.tamVet - 2);

    ret.cpyVet(ret.str, this->str, 0, 0, this->tamVet - 1);
    ret.cpyVet(ret.str, _aux.str, this->tamVet - 1, 0, _aux.tamVet);

    return ret;
}

String String::operator+(const char& _novo) const throw(invalid_argument) {
    String ret(*this);

    ret.append(_novo);

    return ret;
}

String& String::operator+=(const String& _aux) {
    char* aux = new char[this->tamVet + _aux.tamVet - 1];

    this->cpyVet(aux, this->str, 0, 0, this->tamVet - 1);
    this->cpyVet(aux, _aux.str, this->tamVet - 1, 0, _aux.tamVet);

    this->tamVet += _aux.tamVet - 1;
    this->str = aux;

    return *this;
}

String& String::operator+=(const char& _novo) throw(invalid_argument) {
    this->append(_novo);

    return *this;
}

char& String::operator[](const uint& _pos) throw(out_of_range) {
    if (_pos >= this->tamVet || _pos < 0)
        throw out_of_range("Posicao invalida!!!");

    return *(this->str + _pos);
}

bool String::operator==(const String& _aux) const {
    return this->compareTo(_aux) == 0;
}

bool String::operator!=(const String& _aux) const {
    return this->compareTo(_aux) != 0;
}

bool String::operator>(const String& _aux) const {
    return this->compareTo(_aux) == 1;
}

bool String::operator<(const String& _aux) const {
    return this->compareTo(_aux) == -1;
}

bool String::operator>=(const String& _aux) const {
    return this->compareTo(_aux) >= 0;
}

bool String::operator<=(const String& _aux) const {
    return this->compareTo(_aux) <= 0;
}

char* String::toString() const {
    char* ret = new char[this->tamVet];

    for (uint i = 0; i < this->tamVet; i++)
        *(ret + i) = *(this->str + i);

    return ret;
}

ostream& operator<<(ostream& _os, const String& _aux) {
    return _os << _aux.toString();
}

istream& operator>>(istream& _is, String& _aux) {
    string str;
    getline(_is, str);

    const char* vet = str.data();

    delete(_aux.str);
    _aux.str = new char[str.size() + 1];
    _aux.tamVet = str.size() + 1;

    for (uint i = 0; i < _aux.tamVet; i++)
        *(_aux.str + i) = *(vet + i);

    return _is;
}

String::~String() {
    delete(this->str);
}

void String::append(const char& _novo) throw(invalid_argument) {
    if (_novo == '\0')
        throw invalid_argument("Char nulo!!!");

    char* novo = new char[this->tamVet + 1];

    this->cpyVet(novo, this->str, 0, 0, this->tamVet - 1);

    *(novo + this->tamVet - 1) = _novo;
    *(novo + this->tamVet++) = '\0';

    this->str = novo;
}

void String::deleteCharAt(const uint& _pos) throw(out_of_range) {
    if (_pos >= this->tamVet - 1 || _pos < 0)
        throw out_of_range("Posicao invalida!!!");

    char* novo = new char[this->tamVet - 1];

    this->cpyVet(novo, this->str, 0, 0, _pos);
    this->cpyVet(novo, this->str, _pos, _pos + 1, --this->tamVet - _pos);

    this->str = novo;
}

void String::deleteRange(const uint& _posI, const uint& _posF) throw(invalid_argument) {
    if (_posI > _posF || _posI < 0 || _posF >= this->tamVet)
        throw out_of_range("Posicao(s) invalida(s)!!!");

    char* novo = new char[this->tamVet - (_posF - _posI)];

    this->cpyVet(novo, this->str, 0, 0, _posI);
    this->cpyVet(novo, this->str, _posI, _posF + 1, this->tamVet - _posF + 1);

    this->tamVet -= _posF - _posI;

    this->str = novo;
}

void String::insertInto(const uint& _pos, const char& _novo) throw(invalid_argument) {
    if (_pos >= this->tamVet || _pos < 0)
       throw invalid_argument("Posicao invalida!!!");
    else if (_novo == '\0')
        throw invalid_argument("Char nulo!!!");

    char* novo = new char[this->tamVet + 1];

    this->cpyVet(novo, this->str, 0, 0, _pos);
    *(novo + _pos) = _novo;
    this->cpyVet(novo, this->str, _pos + 1, _pos, this->tamVet - _pos);

    this->tamVet++;

    this->str = novo;
}

void String::replaceAll(const char& _velho, const char& _novo) throw(invalid_argument) {
    if (_velho == '\0' || _novo == '\0')
        throw invalid_argument("Char(s) invalido(s)!!!");

    for (uint i = 0; i < this->tamVet; i++)
        if (*(this->str + i) == _velho)
            *(this->str + i) = _novo;
}

char* String::subStr(const uint& _inicio, const uint& _fim) const {
    char* ret = new char[_fim - _inicio + 2];

    uint d, p;
    for (d = 0, p = _inicio; p <= _fim; d++, p++)
        *(ret + d) = *(this->str + p);

    *(ret + _fim - _inicio + 1) = '\0';

    return ret;
}

char* String::subStr(const uint& _inicio) const {
    return subStr(_inicio, this->tamVet - 2);
}

void String::deletePos(const uint& _pos) {
    uint i;
    for (i = _pos; i < this->tamVet - 2; i++)
        *(this->str + i) = *(this->str + i + 1);

    *(this->str + i) = ' ';
}

uint String::length() const {
    return this->tamVet - 1;
}

char String::compareTo(const String& _aux) const {
    unsigned int tamMenor = (this->tamVet < _aux.tamVet ? this->tamVet : _aux.tamVet) - 1;

    for (uint i = 0; i < tamMenor; i++)
        if ((int) *(this->str + i) > (int) *(_aux.str + i))
            return 1;
        else if ((int) *(this->str + i) < (int) *(_aux.str + i))
            return -1;

    return 0;
}

void String::cpyVet(char* _vetDest, const char* _vetPart, const uint _posIDest, const uint _posIPart, const uint _numElems) {
    uint d, p;

    uint i;
    for (d = _posIDest, p = _posIPart, i = 0; i < _numElems; d++, p++, i++)
        *(_vetDest + d) = *(_vetPart + p);
}


