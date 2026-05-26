#include "../include/Andarilho.h"

namespace Entidades
{
    namespace Personagens
    {
        Andarilho::Andarilho(
            int indice,
            sf::Vector2f pos,
            sf::Vector2f velo,
            sf::Vector2f tam,
            Jogador* pJ1,
            Jogador* pJ2
        ) :
            Inimigo(indice, pos, velo, tam, pJ1, pJ2),
            raio(45.f)
        {
            dano_base = 1;
            dano = dano_base;
            n_vidas = 3;

            texturas = pGG->carregar_texturas("./assets/andarilho.png");
            corpo.setTexture(texturas);
        }

        Andarilho::~Andarilho()
        {}

        void Andarilho::executar()
        {
            if (n_vidas <= 0)
            {
                vivo = false;
                return;
            }

            mover();
        }

        void Andarilho::danificar(Jogador* pJog)
        {
            if (!pJog || !pJog->get_vivo())
            {
                return;
            }

            if (jogadorNoRaioAtaque(pJog))
            {
                aumentarMaldade();
                pJog->receber_dano(calcularDanoAtual());
            }
        }

        void Andarilho::salvarDataBuffer()
        {
            Inimigo::salvarDataBuffer();

            bufferSalvar
                << "Andarilho" << ' '
                << raio << '\n';
        }

        void Andarilho::salvar(std::ostream& out)
        {
            salvarDataBuffer();
            out << getBufferSalvar();
        }
    }
}