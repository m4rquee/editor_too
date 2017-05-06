#include "String.h"

#ifndef ACAO_H
#define ACAO_H

#define uint unsigned int

class Acao
{
    public:
        Acao(const uint&, String);

        String getLinha() const;
    protected:
        uint pos;
        String linha;
    private:
};

#endif // ACAO_H
