#include "../include/Plataforma.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma() :
            Obstaculo(),
            aceleracaoGelo(0.15f),
            velocidadeMaximaGelo(8.0f),
			empuxo(gravidade)
        {
            id = Id::Plataforma;

            danoso = false;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::plataforma));
            setFigura(&forma);
        }

        Plataforma::Plataforma(sf::Vector2f pos) :
            Obstaculo(pos),
            aceleracaoGelo(0.15f),
            velocidadeMaximaGelo(8.0f),
			empuxo(gravidade)
        {
            id = Id::Plataforma;

            danoso = false;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::plataforma));
            forma.setPosition(pos);

            setFigura(&forma);
        }

        Plataforma::Plataforma(sf::Vector2f pos, sf::Vector2f tamanho) :
            Obstaculo(pos),
            aceleracaoGelo(0.15f),
            velocidadeMaximaGelo(8.0f),
			empuxo(gravidade)
        {
            id = Id::Plataforma;

            danoso = false;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::plataforma));
            forma.setPosition(pos);

            sf::FloatRect limites = forma.getLocalBounds();

            if (limites.width > 0.f && limites.height > 0.f)
            {
                forma.setScale(
                    tamanho.x / limites.width,
                    tamanho.y / limites.height
                );
            }

            setFigura(&forma);
        }

        Plataforma::~Plataforma()
        {}

        void Plataforma::executar()
        {
            if (!ativo)
            {
                return;
            }

            aplicarGravidade();

            /*
                Empuxo cancela a gravidade.
                Assim a plataforma sofre gravidade por requisito,
                mas permanece suspensa/fixa no mapa.
            */
            vel.y -= empuxo;

            if (vel.y > -0.01f && vel.y < 0.01f)
            {
                vel.y = 0.f;
            }

            mover();
        }

        void Plataforma::obstaculizar(Personagens::Jogador* jogador)
        {
            if (!jogador || !jogador->ativado())
            {
                return;
            }

            /*
                Efeito de gelo:
                se o jogador já está se movendo para algum lado,
                aumenta um pouco a velocidade horizontal dele.

                Não zeramos velocidade Y aqui porque você pediu para não fazer isso.
                Quem resolve a colisão vertical é o GerenciadorColisao + Personagem::colidiu().
            */

            sf::Vector2f velJog = jogador->getVelocidade();

            if (velJog.x > 0.f)
            {
                velJog.x += aceleracaoGelo;

                if (velJog.x > velocidadeMaximaGelo)
                {
                    velJog.x = velocidadeMaximaGelo;
                }
            }
            else if (velJog.x < 0.f)
            {
                velJog.x -= aceleracaoGelo;

                if (velJog.x < -velocidadeMaximaGelo)
                {
                    velJog.x = -velocidadeMaximaGelo;
                }
            }

            jogador->setVelocidade(velJog);
        }

        std::string Plataforma::salvar()
        {
            salvarObstaculo();

            buffer << aceleracaoGelo << " ";
            buffer << velocidadeMaximaGelo << " ";
			buffer << empuxo << " ";

            return buffer.str();
        }
    }
}