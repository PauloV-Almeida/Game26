#pragma once

#include "Ente.h"
#include "Direcao.h"
#include "Texturas.h"

#include <sstream>
#include <string>

namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        int idUni;
        static int contarEntidades;

		sf::Vector2f posicao;
        sf::Sprite forma;
        sf::Vector2f velo;

        bool ativo;
        std::ostringstream buffer;

        static constexpr float gravidade = 0.35f;
    protected:
        void salvarDataBuffer();
    public:
        Entidade();
        Entidade(sf::Vector2f pos);
        virtual ~Entidade();

        const sf::Vector2f getCentro();
        const sf::Vector2f getPosicao();
        const virtual sf::FloatRect getLimites();
        const int getIdUnico() const;
        void setIdUnico(int id);
        
        bool ativado() const;               
        virtual void setAtivo(bool at);
        void desativar();

        void setPosicao(float x, float y);
        void setVelocidade(float x, float y);
        
        void mudarVelocidade(sf::Vector2f addVel);

        virtual void aplicarGravidade();
        virtual void mover();

        virtual std::string salvar() = 0;
        virtual void executar() = 0;
    };
}