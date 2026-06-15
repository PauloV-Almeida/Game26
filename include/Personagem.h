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

            bool noChao;
            bool travado;

            float velocidadeMovimento;
            float velocidadeMaxima;
            float forcaPulo;

        protected:
            void limitarVelocidade();
            void salvarPersonagem();

        public:
            Personagem();
            Personagem(sf::Vector2f pos);
            virtual ~Personagem();

            int getNumVidas() const;
            bool vivo() const;

            bool getNoChao() const;
            bool estaTravado() const;

            float getVelocidadeMovimento() const;
            float getVelocidadeMaxima() const;
            float getForcaPulo() const;

            void setNumVidas(int vidas);
            void setNoChao(bool estado);
            void setTravado(bool estado);

            void setVelocidadeMovimento(float velocidade);
            void setVelocidadeMaxima(float velocidade);
            void setForcaPulo(float forca);

            void tirarVida(int dano);
            void recuperarVida(int qtd);

            virtual void aplicarGravidade();
            virtual void atualizarFisica();

            virtual void colidiu(Direcao direcao);
            virtual void colidiu(Entidade* entidade, Direcao direcao);

            virtual void executar() = 0;
            virtual std::string salvar() = 0;
        };
    }
}