#include "../include/Valkiria.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Valkiria::Valkiria(sf::Vector2f pos, Jogador* jogador) :
            Inimigo(pos, jogador),
            empurrar(4.f)
        {
            id = Id::Valkiria;

            /*
                nivel_maldade:
                - influencia a vida
                - influencia o empurrão
                - não aumenta diretamente o dano
            */
            setNivelMaldade(1 + (rand() % 10));

            num_vidas = 8 + getNivelMaldade();

            /*
                A Valkiria pode enxergar um pouco mais que o Andarilho.
                Se quiser mais difícil, aumenta esse valor.
            */
            raioVisao = 350.f + static_cast<float>(getNivelMaldade() * 10);

            forma.setTexture(*pGG->getTextura(Texturas::valkiria));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));

            /*
                Escala fixa para não bugar com mapa 1920x1080 e tile 64x64.
                Se o sprite ficar pequeno/grande, ajuste aqui.
            */
            forma.setScale(0.7f, 0.7f);

            setFigura(&forma);
        }

        Valkiria::~Valkiria()
        {}

        void Valkiria::danificar(Jogador* jogador)
        {
            if (!jogador)
            {
                return;
            }

            if (!ativado())
            {
                return;
            }

            if (!vivo())
            {
                return;
            }

            if (danoContatoRelogio.getElapsedTime().asSeconds() >= danotempoContato)
            {
                /*
                    Dano:
                    usa apenas o dano base herdado de Personagem.
                */
                jogador->tiraVida(getDanoBase());

                /*
                    Empurrão:
                    empurrar é a força base.
                    nivel_maldade aumenta o knockback.
                */
                float forcaEmpurrao = empurrar + static_cast<float>(getNivelMaldade()) * 0.5f;

                if (jogador->getCentro().x < getCentro().x)
                {
                    jogador->mudarVelocidade(sf::Vector2f(-forcaEmpurrao, -2.f));
                }
                else
                {
                    jogador->mudarVelocidade(sf::Vector2f(forcaEmpurrao, -2.f));
                }

                danoContatoRelogio.restart();
            }
        }

        void Valkiria::executar()
        {
            if (!ativado())
            {
                return;
            }

            if (!vivo())
            {
                setAtivo(false);
                return;
            }

            if (jogadorNoAlcance())
            {
                perseguirJogador();
            }
            else
            {
                velo.x = 0.f;
            }

            if (direcao == Direcao::LEFT)
            {
                // Se depois tiver textura esquerda:
                // forma.setTexture(*pGG->getTextura(Texturas::valkiriaEsq));
            }
            else
            {
                forma.setTexture(*pGG->getTextura(Texturas::valkiria));
            }

            atualizarFisica();
        }

        std::string Valkiria::salvar()
        {
            salvarDataBuffer();
            return buffer.str();
        }

        void Valkiria::salvarDataBuffer()
        {
            Inimigo::salvarDataBuffer();
            buffer << empurrar << " ";
        }
    }
}