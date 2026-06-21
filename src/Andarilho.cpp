#include "../include/Andarilho.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Andarilho::Andarilho(sf::Vector2f pos, Jogador* jogador) :
            Inimigo(pos, jogador),
            forca((1 + (rand() % 4)))
        {
            id = Id::Andarilho;


            num_vidas = 5 + getNivelMaldade();
            raioVisao = 250.f;

            forma.setTexture(*pGG->getTextura(Texturas::andarilho));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));
            forma.setScale(0.7f, 0.7f);

            setFigura(&forma);
        }

        Andarilho::~Andarilho()
        {}

        void Andarilho::danificar(Jogador* jogador)
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
               
                int danoFinal = getDanoBase() + forca;

                jogador->tiraVida(danoFinal);

                danoContatoRelogio.restart();
            }
        }

        void Andarilho::executar()
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

            atualizarFisica();
        }

        std::string Andarilho::salvar()
        {
            salvarDataBuffer();
            return buffer.str();
        }

        void Andarilho::salvarDataBuffer()
        {
            Inimigo::salvarDataBuffer();
            buffer << forca << " ";
        }
    }
}