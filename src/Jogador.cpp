#include "../include/Jogador.h"
#include "../include/Inimigo.h"

namespace Entidades
{
    namespace Personagens
    {
        Jogador::Jogador() :
            Personagem(),
            pontos(0),
            velMax(6.f),
            atacando(false),
            danoAplicadoAtaque(false),
            jogadorDois(false),
            tempoAtaque(0.18f),
            intervaloAtaque(0.35f),
            empurraoAtaque(7.f),
            larguraAtaque(32.f),
            alturaAtaque(32.f)
        {
            ativo = true;
            id = Id::Jogador;

            num_vidas = 15;
            pulos = 2;
            direcao = Direcao::RIGHT;

            setPosicao(300.f, 0.f);
            setVelocidade(0.f, 0.f);

            forma.setTexture(*pGG->getTextura(Texturas::jogador1));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));
            forma.setScale(0.7f, 0.7f);

            spriteAtaque.setTexture(*pGG->getTextura(Texturas::ataque));
            spriteAtaque.setTextureRect(sf::IntRect(0, 0, 64, 64));
            spriteAtaque.setColor(sf::Color::White);

            setFigura(&forma);
        }

        Jogador::Jogador(sf::Vector2f pos) :
            Personagem(pos),
            pontos(0),
            velMax(6.f),
            atacando(false),
            danoAplicadoAtaque(false),
            jogadorDois(false),
            tempoAtaque(0.18f),
            intervaloAtaque(0.35f),
            empurraoAtaque(7.f),
            larguraAtaque(32.f),
            alturaAtaque(32.f)
        {
            ativo = true;
            id = Id::Jogador;

            num_vidas = 15;
            pulos = 2;
            direcao = Direcao::RIGHT;

            setVelocidade(0.f, 0.f);

            forma.setTexture(*pGG->getTextura(Texturas::jogador1));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));
            forma.setScale(0.7f, 0.7f);

            spriteAtaque.setTexture(*pGG->getTextura(Texturas::ataque));
            spriteAtaque.setTextureRect(sf::IntRect(0, 0, 64, 64));
            spriteAtaque.setColor(sf::Color::White);

            setFigura(&forma);
        }

        Jogador::~Jogador()
        {}

        sf::Vector2f Jogador::getPosicao()
        {
            return forma.getPosition();
        }

        void Jogador::setPontuacao(int pontos)
        {
            this->pontos = pontos;
        }

        void Jogador::aumentarPontos()
        {
            pontos++;
        }

        int Jogador::getPontos()
        {
            return pontos;
        }

        void Jogador::setJogadorDois(bool jg2)
        {
            jogadorDois = jg2;

            if (jogadorDois)
            {
                forma.setTexture(*pGG->getTextura(Texturas::jogador2));
            }
            else
            {
                forma.setTexture(*pGG->getTextura(Texturas::jogador1));
            }
        }

        void Jogador::movimentar(Direcao direcao)
        {
            switch (direcao)
            {
            case Direcao::UP:
            {
                
                if (pulos > 0)
                {
                    velo.y = -8.f;
                    pulos--;
                    noChao = false;
                }

                break;
            }

            case Direcao::DOWN:
            {
                this->direcao = Direcao::DOWN;
                velo.y += 0.3f;
                break;
            }

            case Direcao::LEFT:
            {
                this->direcao = Direcao::LEFT;

                if (velo.x >= -velMax)
                {
                    velo.x -= 0.4f;
                }

                break;
            }

            case Direcao::RIGHT:
            {
                this->direcao = Direcao::RIGHT;

                if (velo.x <= velMax)
                {
                    velo.x += 0.4f;
                }

                break;
            }

            default:
            {
                break;
            }
            }
        }

        void Jogador::pararEixoX()
        {
            if (velo.x > velMax)
            {
                velo.x -= 0.4f;
            }
            else if (velo.x < -velMax)
            {
                velo.x += 0.4f;
            }

            if (velo.x != 0.f)
            {
                if (velo.x > 0.f)
                {
                    if (velo.x - 0.2f < 0.f)
                    {
                        velo.x = 0.f;
                    }
                    else
                    {
                        velo.x -= 0.2f;
                    }
                }
                else
                {
                    if (velo.x + 0.2f > 0.f)
                    {
                        velo.x = 0.f;
                    }
                    else
                    {
                        velo.x += 0.2f;
                    }
                }
            }
        }

        void Jogador::posicaoInicial()
        {
            setPosicao(100.f, 100.f);
            setVelocidade(0.f, 0.f);
        }

        void Jogador::atacar()
        {
            if (relogioAtaque.getElapsedTime().asSeconds() >= intervaloAtaque)
            {
                atacando = true;
                danoAplicadoAtaque = false;

                posicionarSpriteAtaque();

                relogioAtaque.restart();
            }
        }

        sf::FloatRect Jogador::getAreaAtaque() const
        {
            sf::FloatRect corpo = forma.getGlobalBounds();

            float top = corpo.top + corpo.height * 0.25f;

            if (direcao == Direcao::LEFT)
            {
                return sf::FloatRect(
                    corpo.left - larguraAtaque,
                    top,
                    larguraAtaque,
                    alturaAtaque
                );
            }

            return sf::FloatRect(
                corpo.left + corpo.width,
                top,
                larguraAtaque,
                alturaAtaque
            );
        }

        void Jogador::posicionarSpriteAtaque()
        {
            sf::FloatRect area = getAreaAtaque();

            spriteAtaque.setPosition(area.left, area.top);

            sf::FloatRect local = spriteAtaque.getLocalBounds();

            if (local.width > 0.f && local.height > 0.f)
            {
                spriteAtaque.setScale(
                    area.width / local.width,
                    area.height / local.height
                );
            }
        }

        void Jogador::atualizarAtaque()
        {
            if (atacando)
            {
                posicionarSpriteAtaque();

                if (relogioAtaque.getElapsedTime().asSeconds() >= tempoAtaque)
                {
                    atacando = false;
                    danoAplicadoAtaque = false;
                }
            }
        }

        void Jogador::colidir(Inimigo* pInimigo)
        {
            if (!pInimigo)
            {
                return;
            }

            if (!pInimigo->ativado())
            {
                return;
            }

            if (!atacando)
            {
                return;
            }

            if (danoAplicadoAtaque)
            {
                return;
            }

            if (getAreaAtaque().intersects(pInimigo->getLimites()))
            {
                pInimigo->tiraVida(getDanoBase() + 3);

                float direcaoEmpurrao = 1.f;

                if (direcao == Direcao::LEFT)
                {
                    direcaoEmpurrao = -1.f;
                }

                pInimigo->mudarVelocidade(
                    sf::Vector2f(empurraoAtaque * direcaoEmpurrao, -2.5f)
                );

                danoAplicadoAtaque = true;

                if (!pInimigo->vivo())
                {
                    pInimigo->desativar();
                    aumentarPontos();
                }
            }
        }

        void Jogador::executar()
        {
            if (!ativado())
            {
                return;
            }

            if (estaTravado())
            {
                velo.x = 0.f;
                atualizarFisica();
                return;
            }

            if (jogadorDois)
            {
                if (direcao == Direcao::LEFT)
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador2Esq));
                }
                else
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador2));
                }
            }
            else
            {
                if (direcao == Direcao::LEFT)
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador1Esq));
                }
                else
                {
                    forma.setTexture(*pGG->getTextura(Texturas::jogador1));
                }
            }

            atualizarAtaque();

            // Aqui entra gravidade + movimento.
            atualizarFisica();
        }

        void Jogador::desenhar()
        {
            Ente::desenhar();

            if (atacando)
            {
                posicionarSpriteAtaque();
                pGG->desenhar(&spriteAtaque);
            }
        }

        std::string Jogador::salvar()
        {
            salvarDataBuffer();
            return buffer.str();
        }

        void Jogador::salvarDataBuffer()
        {
            Personagem::salvarDataBuffer();

            buffer << pontos << " ";
            buffer << jogadorDois << " ";
        }

        void Jogador::resetarJogador()
        {
            setAtivo(true);
            setVelocidade(0.f, 0.f);
            setNumVida(15);
            setPosicao(100.f, 100.f);
            setPontuacao(0);
            setPulos(2);

            atacando = false;
            danoAplicadoAtaque = false;
            direcao = Direcao::RIGHT;

            forma.setColor(sf::Color::White);
        }
    }
}