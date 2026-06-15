#include "../include/Personagem.h"

namespace Entidades
{
    namespace Personagens
    {
        Personagem::Personagem() :
            Entidade(),
            num_vidas(5),
            noChao(false),
            travado(false),
            velocidadeMovimento(3.0f),
            velocidadeMaxima(6.0f),
            forcaPulo(9.0f)
        {}

        Personagem::Personagem(sf::Vector2f pos) :
            Entidade(pos),
            num_vidas(5),
            noChao(false),
            travado(false),
            velocidadeMovimento(3.0f),
            velocidadeMaxima(6.0f),
            forcaPulo(9.0f)
        {}

        Personagem::~Personagem()
        {}

        int Personagem::getNumVidas() const
        {
            return num_vidas;
        }

        bool Personagem::vivo() const
        {
            return num_vidas > 0 && ativo;
        }

        bool Personagem::getNoChao() const
        {
            return noChao;
        }

        bool Personagem::estaTravado() const
        {
            return travado;
        }

        float Personagem::getVelocidadeMovimento() const
        {
            return velocidadeMovimento;
        }

        float Personagem::getVelocidadeMaxima() const
        {
            return velocidadeMaxima;
        }

        float Personagem::getForcaPulo() const
        {
            return forcaPulo;
        }

        void Personagem::setNumVidas(int vidas)
        {
            num_vidas = vidas;

            if (num_vidas <= 0)
            {
                num_vidas = 0;
                desativar();
            }
        }

        void Personagem::setNoChao(bool estado)
        {
            noChao = estado;
        }

        void Personagem::setTravado(bool estado)
        {
            travado = estado;

            if (travado)
            {
                vel.x = 0.f;
            }
        }

        void Personagem::setVelocidadeMovimento(float velocidade)
        {
            velocidadeMovimento = velocidade;
        }

        void Personagem::setVelocidadeMaxima(float velocidade)
        {
            velocidadeMaxima = velocidade;
        }

        void Personagem::setForcaPulo(float forca)
        {
            forcaPulo = forca;
        }

        void Personagem::tirarVida(int dano)
        {
            if (dano <= 0 || !ativo)
            {
                return;
            }

            num_vidas -= dano;

            if (num_vidas <= 0)
            {
                num_vidas = 0;
                desativar();
            }
        }

        void Personagem::recuperarVida(int qtd)
        {
            if (qtd <= 0 || !ativo)
            {
                return;
            }

            num_vidas += qtd;
        }

        void Personagem::aplicarGravidade()
        {
            if (!noChao)
            {
                vel.y += gravidade;
            }
            else if (vel.y > 0.f)
            {
                vel.y = 0.f;
            }
        }

        void Personagem::limitarVelocidade()
        {
            if (vel.x > velocidadeMaxima)
            {
                vel.x = velocidadeMaxima;
            }
            else if (vel.x < -velocidadeMaxima)
            {
                vel.x = -velocidadeMaxima;
            }

            if (vel.y > 18.f)
            {
                vel.y = 18.f;
            }
            else if (vel.y < -18.f)
            {
                vel.y = -18.f;
            }
        }

        void Personagem::atualizarFisica()
        {
            if (travado)
            {
                vel.x = 0.f;
            }

            aplicarGravidade();
            limitarVelocidade();
            mover();

            /*
                Importante:
                O noChao é marcado como true pelo GerenciadorColisao
                quando o personagem colide com chão/plataforma por baixo.

                Depois do movimento, deixamos false para que, no próximo frame,
                a colisão confirme novamente se ele ainda está no chão.
            */
            noChao = false;
        }

        void Personagem::colidiu(Direcao direcao)
        {
            switch (direcao)
            {
            case Direcao::DOWN:
                noChao = true;

                if (vel.y > 0.f)
                {
                    vel.y = 0.f;
                }
                break;

            case Direcao::UP:
                if (vel.y < 0.f)
                {
                    vel.y = 0.f;
                }
                break;

            case Direcao::LEFT:
            case Direcao::RIGHT:
                vel.x = 0.f;
                break;

            default:
                break;
            }
        }

        void Personagem::colidiu(Entidade* entidade, Direcao direcao)
        {
            if (!entidade)
            {
                colidiu(direcao);
                return;
            }

            sf::FloatRect personagemBounds = getLimites();
            sf::FloatRect entidadeBounds = entidade->getLimites();

            switch (direcao)
            {
            case Direcao::DOWN:
                /*
                    Personagem está em cima da entidade.
                    Exemplo: jogador pisando no chão.
                */
                setPosicao(
                    personagemBounds.left,
                    entidadeBounds.top - personagemBounds.height
                );

                noChao = true;

                if (vel.y > 0.f)
                {
                    vel.y = 0.f;
                }
                break;

            case Direcao::UP:
                /*
                    Personagem bateu a cabeça em algo.
                */
                setPosicao(
                    personagemBounds.left,
                    entidadeBounds.top + entidadeBounds.height
                );

                if (vel.y < 0.f)
                {
                    vel.y = 0.f;
                }
                break;

            case Direcao::RIGHT:
                /*
                    Entidade está à direita do personagem.
                */
                setPosicao(
                    entidadeBounds.left - personagemBounds.width,
                    personagemBounds.top
                );

                vel.x = 0.f;
                break;

            case Direcao::LEFT:
                /*
                    Entidade está à esquerda do personagem.
                */
                setPosicao(
                    entidadeBounds.left + entidadeBounds.width,
                    personagemBounds.top
                );

                vel.x = 0.f;
                break;

            default:
                break;
            }
        }

        void Personagem::salvarPersonagem()
        {
            salvarEntidade();

            buffer << num_vidas << " ";
            buffer << noChao << " ";
            buffer << travado << " ";
            buffer << velocidadeMovimento << " ";
            buffer << velocidadeMaxima << " ";
            buffer << forcaPulo << " ";
        }
    }
}