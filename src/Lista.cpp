#include "Lista.h"

using namespace std;

Lista::Lista() {
    this->qntsNos = 0;
    this->primeiro = this->noAtual = NULL;
}

Lista::Lista(const Lista& _aux) {
    this->qntsNos = 0;

    this->primeiro = this->noAtual = NULL;

    pNoLista atual = _aux.primeiro;
    for (uint i = 0; i < _aux.qntsNos; i++) {
        insiraDepois(atual->info);
        atual = atual->prox;
    }
}

Lista Lista::operator=(const Lista& _aux) {
    if (this == &_aux)
        return *this;

    if (this->noAtual != NULL && this->primeiro != NULL) {
        delete(this->noAtual);
        delete(this->primeiro);
    }

    this->qntsNos = 0;

    pNoLista atual = _aux.primeiro;
    for (uint i = 0; i < _aux.qntsNos; i++) {
        insiraDepois(atual->info);
        atual = atual->prox;
    }

    return *this;
}

String Lista::toString() const {
    String ret;

    if (this->primeiro != NULL) {
        pNoLista atual = this->primeiro;

        for (uint i = 1; i < this->qntsNos; i++) {
            ret += atual->info + '\n';
            atual = atual->prox;
        }

        ret += atual->info;
    }

    return ret;
}

String Lista::toStringSemPula() const {
    String ret;

    if (this->primeiro != NULL) {
        pNoLista atual = this->primeiro;
        for (uint i = 0; i < this->qntsNos; i++) {
            ret += atual->info;
            atual = atual->prox;
        }
    }

    return ret;
}

ostream& operator<<(ostream& _os, const Lista& _aux) {
    return _os << _aux.toString();
}

Lista::~Lista() {
    delete(this->noAtual);
    delete(this->primeiro);
}

void Lista::insira(const String linha) {
    pNoLista novo = new NoLista;
    novo->info = linha;

    if (qntsNos == 0) {
        this->primeiro = this->noAtual = novo;

        novo->ant = novo;
        novo->prox = novo;
    } else {
        pNoLista ant = this->noAtual->ant;

        //Arruma as ligações:
        novo->prox = this->noAtual;
        novo->ant = ant;

        this->noAtual->ant = novo;
        ant->prox = novo;

        if (this->primeiro == this->noAtual)
            this->primeiro = novo;

        this->noAtual = novo;
    }

    this->qntsNos++;
}

void Lista::insiraDepois(const String linha) {
    pNoLista novo = new NoLista;
    novo->info = linha;

    if (this->qntsNos == 0) {
        this->primeiro = this->noAtual = novo;

        novo->ant = novo;
        novo->prox = novo;
    } else {
        //Arruma as ligações:
        novo->ant = this->noAtual;
        novo->prox = this->noAtual->prox;

        this->noAtual->prox = novo;
        avance();
        this->noAtual->prox->ant = novo;
    }

    this->qntsNos++;
}

void Lista::remova() {
    if (this->qntsNos == 0)
        return;

    if (this->qntsNos == 1) {
        delete(this->noAtual);
        delete(this->primeiro);

        this->primeiro = this->noAtual = NULL;
        return;
    }

    pNoLista ant = this->noAtual->ant;
    pNoLista prox = this->noAtual->prox;
    ant->prox = prox;
    prox->ant = ant;

    delete(this->noAtual);

    if (this->noAtual == this->primeiro) {
        this->primeiro = prox;
        this->noAtual = prox;
    } else
        this->noAtual = ant;

    this->qntsNos--;
}

void Lista::removaDepois() {
    if (!estaNoUltimo()) {
        avance();
        remova();
    }
}

String* Lista::infoAtual() const {
    if (this->qntsNos > 0)
        return &(this->noAtual->info);

    return NULL;
}

void Lista::avance() {
    if (this->qntsNos > 0)
        this->noAtual = this->noAtual->prox;
}

void Lista::retroceda() {
    if (this->qntsNos > 0)
        this->noAtual = this->noAtual->ant;
}

void Lista::paraPrimeiro() {
    this->noAtual = this->primeiro;
}

void Lista::paraUltimo() {
    this->noAtual = this->primeiro->ant;
}

bool Lista::estaNoPrimeiro() const {
    return this->noAtual == this->primeiro;
}

bool Lista::estaNoUltimo() const {
    return this->noAtual == this->primeiro->ant;
}

uint Lista::qntos() const {
    return this->qntsNos;
}











