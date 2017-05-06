#include "Acao.h"

Acao::Acao(const uint& _pos, String _linha) : pos(_pos) {
    this->linha = linha;
}

String Acao::getLinha() const {
    return this->linha;
}
