#pragma once

#include "Entidades.h"

namespace Entidades
{
    namespace Personagens
    {
        class Personagem : public Entidade
        {
        protected:
            sf::RectangleShape corpo;
            bool vivo;
            int n_vidas;
            bool noChao;

        public:
            Personagem(
                int indice = -1,
                sf::Vector2f pos = sf::Vector2f(0.f, 0.f),
                sf::Vector2f vel = sf::Vector2f(128.f, 128.f),
                sf::Vector2f tam = sf::Vector2f(0.f, 0.f)
            );

            virtual ~Personagem();

            virtual void executar() = 0;

            void receber_dano(int dmg)
            {
                n_vidas -= dmg;

                if (n_vidas <= 0)
                {
                    n_vidas = 0;
                    vivo = false;
                }
            }

            void set_vivo(bool a) { vivo = a; }
            void set_noChao(bool n) { noChao = n; }

            virtual void desenhar();

            sf::Vector2f get_posicao() { return corpo.getPosition(); }
            sf::Vector2f get_tamanho() { return corpo.getSize(); }

            void set_posicao(sf::Vector2f pos) { corpo.setPosition(pos); }

            const bool get_vivo() const { return vivo; }
            const int get_vidas() const { return n_vidas; }
            bool get_noChao() const { return noChao; }

            virtual void salvarDataBuffer();
            virtual void salvar(std::ostream& out) = 0;
        };
    }
}