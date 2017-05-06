#include "String.h"

#ifndef LISTA_H
#define LISTA_H

#define uint unsigned int

typedef struct NoLista {
    NoLista* prox;
    NoLista* ant;

    String info;
} NoLista;

typedef NoLista* pNoLista;

class Lista {
    public:
        Lista();
        Lista(const Lista&);

        virtual ~Lista();

        uint qntos() const;
        String toString() const;
        String* infoAtual() const;
        bool estaNoUltimo() const;
        bool estaNoPrimeiro() const;
        String toStringSemPula() const;

        void avance();
        void retroceda();
        void paraUltimo();
        void paraPrimeiro();

        void remova();
        void removaDepois();
        void insira(const String);
        void insiraDepois(const String);

        Lista operator=(const Lista&);

        friend ostream& operator<<(ostream&, const Lista&);
    protected:
        uint qntsNos;
        pNoLista noAtual;
        pNoLista primeiro;
    private:
};

#endif // LISTA_H
