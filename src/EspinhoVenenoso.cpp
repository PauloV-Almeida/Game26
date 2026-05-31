#include "../include/EspinhoVenenoso.h"

namespace Entidades
{
    namespace Obstaculos
    {
        EspinhoVenenoso::EspinhoVenenoso(int indice, sf::Vector2f pos, sf::Vector2f tam) :
            Obstaculo(indice, pos, tam),
            largura(tam.x),
            jogadorEnvenenado1(nullptr),
            jogadorEnvenenado2(nullptr)
        {
            danoso = true;
            dano = DANO_ESPINHO;

            texturas = pGG->carregar_texturas("./assets/espinho_venenoso1.png");
            corpo.setTexture(texturas);
        }

        EspinhoVenenoso::~EspinhoVenenoso()
        {
            jogadorEnvenenado1 = nullptr;
            jogadorEnvenenado2 = nullptr;
        }

        void EspinhoVenenoso::executar()
        {
            atualizarVenenoJogador(jogadorEnvenenado1, relogioVeneno1, relogioDano1);
            atualizarVenenoJogador(jogadorEnvenenado2, relogioVeneno2, relogioDano2);
        }

        void EspinhoVenenoso::aplicarVeneno(Entidades::Personagens::Jogador* pJog)
        {
            if (!pJog || !pJog->get_vivo())
            {
                return;
            }

            if (jogadorEnvenenado1 == pJog)
            {
                relogioVeneno1.restart();
                return;
            }

            if (jogadorEnvenenado2 == pJog)
            {
                relogioVeneno2.restart();
                return;
            }

            if (!jogadorEnvenenado1)
            {
                jogadorEnvenenado1 = pJog;
                relogioVeneno1.restart();
                relogioDano1.restart();
                return;
            }

            if (!jogadorEnvenenado2)
            {
                jogadorEnvenenado2 = pJog;
                relogioVeneno2.restart();
                relogioDano2.restart();
                return;
            }
        }

        void EspinhoVenenoso::atualizarVenenoJogador(
            Entidades::Personagens::Jogador*& pJog,
            sf::Clock& relogioVeneno,
            sf::Clock& relogioDano
        )
        {
            if (!pJog)
            {
                return;
            }

            if (!pJog->get_vivo())
            {
                pJog = nullptr;
                return;
            }

            if (relogioVeneno.getElapsedTime().asSeconds() >= DURACAO_VENENO_SEGUNDOS)
            {
                pJog = nullptr;
                return;
            }

            if (relogioDano.getElapsedTime().asSeconds() >= INTERVALO_DANO_VENENO)
            {
                pJog->receber_dano(dano);
                relogioDano.restart();
            }
        }

        void EspinhoVenenoso::obstaculizar(Entidades::Entidade* outro, std::string direcao)
        {
            if (!outro || !outro->get_vivo())
            {
                return;
            }

            sf::Vector2f vel = outro->get_vel();

            Entidades::Personagens::Personagem* personagem =
                dynamic_cast<Entidades::Personagens::Personagem*>(outro);

            Entidades::Personagens::Jogador* jogador =
                dynamic_cast<Entidades::Personagens::Jogador*>(outro);

            if (direcao == "Embaixo")
            {
                vel.y = 0.0f;

                if (personagem)
                {
                    personagem->set_noChao(true);
                }

                if (jogador)
                {
                    jogador->receber_dano(dano);
                    aplicarVeneno(jogador);
                }
            }
            else if (direcao == "Emcima" || direcao == "Cima")
            {
                vel.y = 0.0f;

                if (jogador)
                {
                    jogador->receber_dano(dano);
                    aplicarVeneno(jogador);
                }
            }
            else if (direcao == "Esquerda" || direcao == "Direita")
            {
                vel.x = 0.0f;

                if (jogador)
                {
                    jogador->receber_dano(dano);
                    aplicarVeneno(jogador);
                }
            }

            outro->set_vel(vel);
        }

        void EspinhoVenenoso::salvarDataBuffer()
        {
            Obstaculo::salvarDataBuffer();

            bufferSalvar
                << "EspinhoVenenoso" << ' '
                << largura << ' '
                << dano << '\n';
        }

        void EspinhoVenenoso::salvar(std::ostream& out)
        {
            salvarDataBuffer();
            out << getBufferSalvar();
        }
    }
}