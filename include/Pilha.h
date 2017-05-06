#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h>
#include <stdexcept>

#define uint unsigned int

using namespace std;

template <typename tipo> class Pilha {
    public:
        Pilha(const uint& _tam) {
            this->numElems = 0;
            this->tamMax = _tam;
            this->dados = (tipo*) malloc(_tam * sizeof(tipo));
        }

        Pilha(const Pilha<tipo>& _aux) {
            this->numElems = _aux.numElems;

            this->tamMax = _aux.tamMax;
            this->dados = (tipo*) malloc(this->tamMax * sizeof(tipo));

            uint i;
            for (i = 0; i < this->numElems; i++)
                *(this->dados + i) = *(_aux.dados + i);
        }

        Pilha<tipo>& operator=(const Pilha<tipo>& _aux) {
            if (this == &_aux)
                return *this;

            this->numElems = _aux.numElems;

            if (this->tamMax != _aux.tamMax) {
                this->tamMax = _aux.tamMax;

                free(this->dados);
                this->dados = (tipo*) malloc(this->tamMax * sizeof(tipo));
            }

            uint i;
            for (i = 0; i < this->numElems; i++)
                *(this->dados + i) = *(_aux.dados + i);

            return *this;
        }

        virtual ~Pilha() {
            free(this->dados);
        }

        bool vazia() {
            return this->numElems == 0;
        }

        bool cheia() {
            return this->numElems == this->tamMax;
        }

        tipo espie() throw(out_of_range) {
            if (this->vazia())
                throw out_of_range("Pilha vazia!!!");

            return *(this->dados + this->numElems - 1);
        }

        tipo desempilhar() throw(out_of_range) {
            if (this->vazia())
                throw out_of_range("Pilha vazia!!!");

            tipo ret = *(this->dados + --this->numElems);
            free(this->dados + this->numElems);

            return ret;
        }

        void empilhar(tipo _novo) {
            if (this->numElems == this->tamMax) {
                tipo* novoDados = (tipo*) malloc(this->tamMax * sizeof(tipo));

                uint i;
                for (i = 0; i < this->numElems - 1; i++)
                    *(novoDados + i) = *(this->dados + (i + 1));

                this->dados = novoDados;

                *(this->dados + (this->numElems - 1)) = _novo;
            } else
                *(this->dados + this->numElems++) = _novo;
        }
    protected:
        uint tamMax;
        tipo* dados;
        uint numElems;
    private:
};

#endif // PILHA_H


