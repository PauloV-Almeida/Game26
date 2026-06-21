#include "../include/Valkiria.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Valkiria::Valkiria(sf::Vector2f pos, Jogador* jogador) :
            Inimigo(pos, jogador),
            empurrar(4.f),
            empurraoForte(false),
            multiplicadorEmpurraoForte(2.5f)
        {
            id = Id::Valkiria;

            setNivelMaldade(1 + rand() % 10);

            num_vidas = 8 + getNivelMaldade();
            raioVisao = 350.f + getNivelMaldade() * 10.f;

            forma.setTexture(*pGG->getTextura(Texturas::valkiria));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));
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

            if (!ativado() || !vivo())
            {
                return;
            }

            if (danoContatoRelogio.getElapsedTime().asSeconds() >= danotempoContato)
            {
                jogador->tiraVida(getDanoBase());

                float forcaEmpurrao = empurrar + getNivelMaldade() * 0.5f;
                float forcaVertical = -2.f;

                if (empurraoForte)
                {
                    forcaEmpurrao *= multiplicadorEmpurraoForte;
                    forcaVertical = -5.f;
                }

                if (jogador->getCentro().x < getCentro().x)
                {
                    jogador->mudarVelocidade(
                        sf::Vector2f(-forcaEmpurrao, forcaVertical)
                    );
                }
                else
                {
                    jogador->mudarVelocidade(
                        sf::Vector2f(forcaEmpurrao, forcaVertical)
                    );
                }

                /*
                    Depois de usar o empurrão forte, volta ao normal.
                */
                empurraoForte = false;
               
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

             
                if (!empurraoForte && rand() % 100 == 1)
                {
                    empurraoForte = true;
                
                }
            }
            else
            {
                velo.x = 0.f;
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