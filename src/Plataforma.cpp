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
            setPosicao(pos.x, pos.y);

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
            setPosicao(pos.x, pos.y);

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

            atualizarFisicaObstaculo();
        }

        void Plataforma::obstaculizar(Personagens::Jogador* jogador)
        {
            if (!jogador || !jogador->ativado())
            {
                return;
            }

            /*
                A plataforma só deve fazer o jogador escorregar
                se ele estiver por cima dela.
            */
            sf::FloatRect limJogador = jogador->getLimites();
            sf::FloatRect limPlataforma = getLimites();

            float baixoJogador = limJogador.top + limJogador.height;
            float topoPlataforma = limPlataforma.top;

            bool jogadorEmCima =
                baixoJogador <= topoPlataforma + 5.f &&
                baixoJogador >= topoPlataforma - 8.f;

            if (!jogadorEmCima)
            {
                return;
            }

            if (jogador->getDirecao() == Direcao::RIGHT)
            {
                jogador->mudarVelocidade(sf::Vector2f(aceleracaoGelo, 0.f));
            }
            else if (jogador->getDirecao() == Direcao::LEFT)
            {
                jogador->mudarVelocidade(sf::Vector2f(-aceleracaoGelo, 0.f));
            }

            /*
                Limite de velocidade horizontal.
                Como velo é protected em Entidade/Personagem,
                o ideal seria ter getVelocidade().
                Se você já adicionou getVelocidade(), pode limitar aqui.
            */
            sf::Vector2f velJogador = jogador->getVelocidade();

            if (velJogador.x > velocidadeMaximaGelo)
            {
                jogador->setVelocidade(velocidadeMaximaGelo, velJogador.y);
            }
            else if (velJogador.x < -velocidadeMaximaGelo)
            {
                jogador->setVelocidade(-velocidadeMaximaGelo, velJogador.y);
            }
        }

        void Plataforma::salvarDataBuffer()
        {
            Obstaculo::salvarDataBuffer();

            buffer << aceleracaoGelo << " ";
            buffer << velocidadeMaximaGelo << " ";
            buffer << empuxo << " ";
        }

        std::string Plataforma::salvar()
        {
            salvarDataBuffer();
            return buffer.str();
        }
    }
}