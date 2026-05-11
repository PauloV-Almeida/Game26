#pragma once

#include "Entidades.h"

#define OBSTACULO_TAMANHO 20

namespace Entidades
{
    namespace Obstaculos
    {
        class Obstaculo : public Entidade
        {
        protected:
            sf::RectangleShape corpo;
            bool existir;
            bool danoso;
        public:
            Obstaculo(int index = -1, sf::Vector2f pos = sf::Vector2f(100.f, 600.f));
            ~Obstaculo();
            virtual void executar() = 0;
            virtual void mover();
            void desenhar();
            //virtual void obstaculizar(Entidades::Entidade* outro, std::string  direcao = "") = 0;
            
            void set_vivo(bool a) { existir = a; }
            const bool get_vivo() const { return existir; }
            sf::Vector2f get_posicao() { return corpo.getPosition(); }
            sf::Vector2f get_tamanho() { return corpo.getSize(); }
            void set_posicao(sf::Vector2f pos) { corpo.setPosition(pos); }
			void set_danoso(bool d) { danoso = d; }
            const bool get_danoso() const { return danoso; }
			virtual void obstaculizar(Entidades::Entidade* outro, std::string  direcao = "") = 0;
        };
    }

}