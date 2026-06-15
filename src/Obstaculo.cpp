#include "../include/Obstaculo.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Obstaculo::Obstaculo() :
            Entidade(),
            danoso(false),
            colidivel(true)
        {}

        Obstaculo::Obstaculo(sf::Vector2f pos) :
            Entidade(pos),
            danoso(false),
            colidivel(true)
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

        void Obstaculo::salvarObstaculo()
        {
            salvarEntidade();

            buffer << danoso << " ";
            buffer << colidivel << " ";
        }
    }
}