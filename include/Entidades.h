#pragma once

#include "Ente.h"
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

        sf::Sprite forma;
        sf::Vector2f vel;

        bool ativo;
        std::ostringstream buffer;

        static constexpr float gravidade = 0.35f;

    public:
        Entidade();
        Entidade(sf::Vector2f pos);
        virtual ~Entidade();

        sf::Vector2f getCentro() const;
        sf::Vector2f getPosicao() const;
        sf::Vector2f getVelocidade() const;
        sf::FloatRect getLimites() const;

        int getIdUnico() const;
        bool ativado() const;

        void setIdUnico(int id);
        virtual void setAtivo(bool at);
        void desativar();

        void setPosicao(float x, float y);
        void setPosicao(sf::Vector2f pos);

        void setVelocidade(float x, float y);
        void setVelocidade(sf::Vector2f novaVel);

        void mudarVelocidade(sf::Vector2f addVel);

        virtual void aplicarGravidade();
        virtual void mover();

        void salvarEntidade();

        virtual std::string salvar() = 0;
        virtual void executar() = 0;
    };
}