#pragma once

#include "Ente.h"
//#include "../observers/Observer.h"
#include <fstream>
#include <sstream>
#include <ostream>

namespace Gerenciadores
{
    class GerenciadorColisoes;
}

namespace Entidades
{
    class Entidade : public Ente
    {
    protected:
        const int id;
        static int contar;

        static float velocidade;
        sf::Vector2f vel;
        static sf::Vector2f posJogador;

        bool deCastigo;
        float massa;
        int dano;

        std::ostringstream bufferSalvar;

        Gerenciadores::GerenciadorColisoes* gColisao;

    public:
        Entidade(int indice = -1, sf::Vector2f velo = sf::Vector2f(0.f, 0.f));
        virtual ~Entidade();

        virtual void desenhar() = 0;
        virtual void executar() = 0;

        virtual void mover(char direcao = ' ')
        {
            vel.y += GRAVIDADE;
        }

        virtual void set_posicao(sf::Vector2f pos) = 0;
        virtual sf::Vector2f get_posicao() = 0;
        virtual sf::Vector2f get_tamanho() = 0;

        virtual void set_vivo(bool a) = 0;
        virtual const bool get_vivo() const { return true; }

        virtual void salvarDataBuffer() = 0;
        virtual void salvar(std::ostream& out) = 0;

        void limparBufferSalvar()
        {
            bufferSalvar.str("");
            bufferSalvar.clear();
        }

        std::string getBufferSalvar() const
        {
            return bufferSalvar.str();
        }

        void set_deCastigo(bool deCast) { deCastigo = deCast; }
        void set_vel(sf::Vector2f v) { vel = v; }
        void set_GerenciadorColisao(Gerenciadores::GerenciadorColisoes* cm) { gColisao = cm; }

        sf::Vector2f get_vel() { return vel; }
        static float get_velocidade() { return velocidade; }

        const int get_id() const { return id; }
        const float get_massa() const { return massa; }

        void set_dano(int d) { dano = d; }
        int get_dano() const { return dano; }
    };
}