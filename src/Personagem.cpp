#include "../include/Personagem.h"

namespace Entidades
{
    namespace Personagens
    {
        Personagem::Personagem() : 
            Entidade()
        {
			num_vidas = 5;
			maxVelocidade = 5;
            velMovimento = 3;
			pulos = 2;
            velo.x = 0;
            velo.y = 0;
			travado = false;
			direcao = Direcao::RIGHT;
        }

        Personagem::Personagem(sf::Vector2f pos) :
            Entidade(pos)
        {
            num_vidas = 5;
            maxVelocidade = 5;
            velMovimento = 3;
            pulos = 2;
            velo.x = 0;
            velo.y = 0;
			travado = false;
            direcao = Direcao::RIGHT;
			setFigura(&forma);
        }

		Personagem::~Personagem()
		{
        }

        const bool Personagem::vivo() const
        {
            return (num_vidas> 0);
        }
        const int Personagem::getDanoBase() const
        {
            return dano;
        }
        void Personagem::setNumVida(int vida)
        {
            num_vidas = vida;

            if (num_vidas < 0)
            {
                num_vidas = 0;
            }
        }
        void Personagem::setPulos(int nP)
        {
            pulos = nP;
        }
        const Direcao Personagem::getDirecao() const
        {
            return direcao;
        }
        const int Personagem::getNumVidas() const
        {
            return num_vidas;
        }

        void Personagem::colidiu(Entidade* entidade, Direcao direcao)
        {
            switch (direcao)
            {
            case Direcao::DOWN:
            {
                velo.y = 0.f;

                setPosicao(
                    getPosicao().x,
                    entidade->getLimites().top - getLimites().height
                );

                /*
                    Tocou no chão/plataforma:
                    recupera os dois pulos.
                */
                pulos = 2;
                noChao = true;

                break;
            }

            case Direcao::UP:
            {
                velo.y = 0.f;

                setPosicao(
                    getPosicao().x,
                    entidade->getLimites().top + entidade->getLimites().height
                );

                break;
            }

            case Direcao::LEFT:
            {
                velo.x = 0.f;

                setPosicao(
                    entidade->getLimites().left + entidade->getLimites().width,
                    getPosicao().y
                );

                break;
            }

            case Direcao::RIGHT:
            {
                velo.x = 0.f;

                setPosicao(
                    entidade->getLimites().left - getLimites().width,
                    getPosicao().y
                );

                break;
            }

            default:
            {
                break;
            }
            }
        }

        bool Personagem::estaTravado() const
        {
            return travado;
        }

        void Personagem::setTravado(bool estado)
        {
            travado = estado;

            if (travado)
            {
                velo.x = 0.f;
            }
        }

        void Personagem::atualizarFisica()
        {
            aplicarGravidade();
            mover();
        }

        void Personagem::tiraVida(int dano)
        {
            num_vidas -= dano;

            if (num_vidas < 0)
            {
                num_vidas = 0;
            }
        }
        void Personagem::setMoveVelocidade(float veloMovi)

        {
            this->velMovimento = veloMovi;
        }

        void Personagem::salvarDataBuffer()
        {
            Entidade::salvarDataBuffer();
            buffer << num_vidas << " ";
            buffer << pulos << " ";
        }


    }
}