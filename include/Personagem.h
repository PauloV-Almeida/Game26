#pragma once

#include "Entidades.h"
#include "Direcao.h"

namespace Entidades
{
    namespace Personagens
    {
        class Personagem : public Entidade
        {
        protected:
            int num_vidas;
			
            float velMovimento;

            int pulos = 2;
            int dano = 2;
            bool travado;
            
			Direcao direcao;
        public:
            Personagem();
            Personagem(sf::Vector2f pos);
            virtual ~Personagem();

            virtual void colidiu(Entidade* entidade, Direcao direcao);

            const Direcao getDirecao() const;
            const int getNumVidas() const;
            const bool vivo() const;
            const int getDanoBase() const;

            void setNumVida(int vida);
            void setPulos(int pulos);

            bool estaTravado() const;
            void setTravado(bool estado);
            
            void tiraVida(int dano);
            
			void atualizarFisica();

            void salvarDataBuffer();
            virtual void executar() = 0;
            virtual std::string salvar() = 0;
        };
    }
}