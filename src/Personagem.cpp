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
            switch (direcao) {
                case Direcao::DOWN: {
                    velo.y = 0;
                    forma.setPosition(forma.getPosition().x, (entidade->getLimites().top - getLimites().height));
                    pulos = 2;
                    break;
                }
                case Direcao::UP: {
                    velo.y = 0;
                    forma.setPosition(forma.getPosition().x, entidade->getLimites().top + entidade->getLimites().height);
                    break;
                }
                case Direcao::LEFT: {
                    velo.x = 0;
                    forma.setPosition(entidade->getLimites().left + entidade->getLimites().width, getLimites().top);
                    if (pulos == 0) {
                        pulos = 1;
                    }
                    break;
                }
                case Direcao::RIGHT: {
                    velo.x = 0;
                    forma.setPosition(entidade->getLimites().left - getLimites().width, getLimites().top);
                    if (pulos == 0) {
                        pulos = 1;
                    }
                    break;
                }
                default: {
                    break;
                }
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