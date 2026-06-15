#include "../include/Jogador.h"
#include "../include/Inimigo.h"

namespace Entidades
{
    namespace Personagens
    {
        Jogador::Jogador() :
            Personagem(),
            idJogador(1),
            danoAtaque(1),
            maxPulos(2),
            pulosRestantes(2),
            atacando(false),
            olhandoDireita(true),
            venceu(false),
            areaAtaque(),
            relogioAtaque(),
            tempoAtaque(0.25f)
        {
            id = Id::Jogador;

            num_vidas = 5;
            velocidadeMovimento = 3.5f;
            velocidadeMaxima = 6.0f;
            forcaPulo = 9.0f;

            forma.setTexture(*pGG->getTextura(Texturas::jogador1));
            forma.setPosition(0.f, 0.f);

            areaAtaque.setSize(sf::Vector2f(35.f, 35.f));
            areaAtaque.setFillColor(sf::Color(255, 255, 255, 80));

            setFigura(&forma);
        }

        Jogador::Jogador(int idJogador, sf::Vector2f pos) :
            Personagem(pos),
            idJogador(idJogador),
            danoAtaque(1),
            maxPulos(2),
            pulosRestantes(2),
            atacando(false),
            olhandoDireita(true),
            venceu(false),
            areaAtaque(),
            relogioAtaque(),
            tempoAtaque(0.25f)
        {
            id = Id::Jogador;

            num_vidas = 5;
            velocidadeMovimento = 3.5f;
            velocidadeMaxima = 6.0f;
            forcaPulo = 9.0f;

            atualizarTextura();
            forma.setPosition(pos);

            areaAtaque.setSize(sf::Vector2f(35.f, 35.f));
            areaAtaque.setFillColor(sf::Color(255, 255, 255, 80));

            setFigura(&forma);
        }

        Jogador::~Jogador()
        {}

        int Jogador::getIdJogador() const
        {
            return idJogador;
        }

        int Jogador::getDanoAtaque() const
        {
            return danoAtaque;
        }

        bool Jogador::estaAtacando() const
        {
            return atacando;
        }

        bool Jogador::getVenceu() const
        {
            return venceu;
        }

        void Jogador::setVenceu(bool venceu)
        {
            this->venceu = venceu;
        }

        void Jogador::setDanoAtaque(int dano)
        {
            if (dano < 0)
            {
                dano = 0;
            }

            danoAtaque = dano;
        }

        void Jogador::moverEsquerda()
        {
            if (travado)
            {
                return;
            }

            vel.x -= velocidadeMovimento;
            olhandoDireita = false;
            atualizarTextura();
        }

        void Jogador::moverDireita()
        {
            if (travado)
            {
                return;
            }

            vel.x += velocidadeMovimento;
            olhandoDireita = true;
            atualizarTextura();
        }

        void Jogador::pular()
        {
            if (travado)
            {
                return;
            }

            if (pulosRestantes > 0)
            {
                vel.y = -forcaPulo;
                noChao = false;
                pulosRestantes--;
            }
        }

        void Jogador::atacar()
        {
            if (travado)
            {
                return;
            }

            if (!atacando)
            {
                atacando = true;
                relogioAtaque.restart();
                atualizarAreaAtaque();
            }
        }

        void Jogador::tratarEntrada()
        {
            if (idJogador == 1)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    moverEsquerda();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    moverDireita();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    pular();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    atacar();
                }
            }
            else if (idJogador == 2)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    moverEsquerda();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    moverDireita();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    pular();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    atacar();
                }
            }
        }

        void Jogador::atualizarTextura()
        {
            if (idJogador == 1)
            {
                if (olhandoDireita)
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador1));
                }
                else
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador1Esq));
                }
            }
            else
            {
                if (olhandoDireita)
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador2));
                }
                else
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador2Esq));
                }
            }
        }

        void Jogador::atualizarAreaAtaque()
        {
            sf::FloatRect limites = getLimites();

            if (olhandoDireita)
            {
                areaAtaque.setPosition(
                    limites.left + limites.width,
                    limites.top + limites.height / 4.f
                );
            }
            else
            {
                areaAtaque.setPosition(
                    limites.left - areaAtaque.getSize().x,
                    limites.top + limites.height / 4.f
                );
            }
        }

        void Jogador::colidir(Inimigo* inimigo)
        {
            if (!inimigo || !inimigo->ativado())
            {
                return;
            }

            if (!atacando)
            {
                return;
            }

            if (areaAtaque.getGlobalBounds().intersects(inimigo->getLimites()))
            {
                inimigo->tirarVida(danoAtaque);
            }
        }

        void Jogador::executar()
        {
            if (!ativo)
            {
                return;
            }

            tratarEntrada();

            if (atacando)
            {
                atualizarAreaAtaque();

                if (relogioAtaque.getElapsedTime().asSeconds() >= tempoAtaque)
                {
                    atacando = false;
                }
            }

            if (noChao)
            {
                pulosRestantes = maxPulos;
            }

            atualizarFisica();
        }

        void Jogador::desenhar()
        {
            if (!ativo)
            {
                return;
            }

            Ente::desenhar();

            if (atacando)
            {
                pGG->desenhar(&areaAtaque);
            }
        }

        std::string Jogador::salvar()
        {
            salvarPersonagem();

            buffer << idJogador << " ";
            buffer << danoAtaque << " ";
            buffer << maxPulos << " ";
            buffer << pulosRestantes << " ";
            buffer << atacando << " ";
            buffer << olhandoDireita << " ";
            buffer << venceu << " ";

            return buffer.str();
        }
    }
}