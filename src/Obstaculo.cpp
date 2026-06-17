#include "../include/Obstaculo.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Obstaculo::Obstaculo() :
            Entidade(),
            danoso(false),
            colidivel(true),
            empuxo(gravidade)
        {}

        Obstaculo::Obstaculo(sf::Vector2f pos) :
            Entidade(pos),
            danoso(false),
            colidivel(true),
            empuxo(gravidade)
        {}

        Obstaculo::~Obstaculo()
        {}

        bool Obstaculo::ehDanoso() const
        {
            return danoso;
        }

        bool Obstaculo::ehColidivel() const
        {
            return colidivel;
        }

        void Obstaculo::setDanoso(bool estado)
        {
            danoso = estado;
        }

        void Obstaculo::setColidivel(bool estado)
        {
            colidivel = estado;
        }

        void Obstaculo::atualizarFisicaObstaculo()
        {
            aplicarGravidade();

            // Empuxo anula a gravidade.
            velo.y -= empuxo;

            if (velo.y > -0.01f && velo.y < 0.01f)
            {
                velo.y = 0.f;
            }

            mover();
        }

        void Obstaculo::salvarDataBuffer()
        {
            Entidade::salvarDataBuffer();

            buffer << danoso << " ";
            buffer << colidivel << " ";
            buffer << empuxo << " ";
        }
    }
}