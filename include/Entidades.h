#pragma once

#include "Ente.h"
#include <fstream>
#include <sstream>
#include <ostream>
#include "Texturas.h"


namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        int idUni;
        static int contarEntidades;
        sf::Vector2f posicao;
        sf::Sprite forma;
        sf::Vector2f vel;     
        
        bool ativo;
        std::ostringstream buffer;

    public:
        Entidade();
        Entidade(sf::Vector2f pos);
        virtual ~Entidade();
 

        sf::Vector2f getCentro() const;
        sf::Vector2f getPosicao() const;
        int getIdUnico() const;
        virtual sf::FloatRect getLimites() const;
        bool ativado() const;
        
        void setIdUni(int id);
        virtual void setAtivo(bool);
        void setPosicao(float x, float y);
        void setVelocidade(float x, float y);

        void desativar();
        void mover();
        void mudarVelocidade(sf::Vector2f addVelo);

        void salvarEntidade();
        virtual std::string salvar() = 0;
        virtual void executar() = 0;

    };
}