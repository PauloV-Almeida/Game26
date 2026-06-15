#include "../include/Inimigo.h"
#include "../include/Jogador.h"

#include <cmath>
#include <cstdlib>

namespace Entidades
{
    namespace Personagens
    {
        Inimigo::Inimigo() :
            Personagem(),
            nivel_maldade(1),
            danoBase(1),
            danoMaximo(4),
            raioVisao(280.f),
            raioAtaque(45.f),
            jogador1(nullptr),
            jogador2(nullptr),
            alvoAtual(nullptr),
            relogioAtaque(),
            relogioMovimentoAleatorio(),
            intervaloAtaque(1.0f),
            tempoTrocaDirecao(1.5f),
            direcaoAleatoria(1)
        {
            velocidadeMovimento = 1.2f;
            velocidadeMaxima = 3.0f;
            num_vidas = 3;
        }

        Inimigo::Inimigo(sf::Vector2f pos) :
            Personagem(pos),
            nivel_maldade(1),
            danoBase(1),
            danoMaximo(4),
            raioVisao(280.f),
            raioAtaque(45.f),
            jogador1(nullptr),
            jogador2(nullptr),
            alvoAtual(nullptr),
            relogioAtaque(),
            relogioMovimentoAleatorio(),
            intervaloAtaque(1.0f),
            tempoTrocaDirecao(1.5f),
            direcaoAleatoria(1)
        {
            velocidadeMovimento = 1.2f;
            velocidadeMaxima = 3.0f;
            num_vidas = 3;
        }

        Inimigo::Inimigo(sf::Vector2f pos, Jogador* j1, Jogador* j2) :
            Personagem(pos),
            nivel_maldade(1),
            danoBase(1),
            danoMaximo(4),
            raioVisao(280.f),
            raioAtaque(45.f),
            jogador1(j1),
            jogador2(j2),
            alvoAtual(nullptr),
            relogioAtaque(),
            relogioMovimentoAleatorio(),
            intervaloAtaque(1.0f),
            tempoTrocaDirecao(1.5f),
            direcaoAleatoria(1)
        {
            velocidadeMovimento = 1.2f;
            velocidadeMaxima = 3.0f;
            num_vidas = 3;
        }

        Inimigo::~Inimigo()
        {
            jogador1 = nullptr;
            jogador2 = nullptr;
            alvoAtual = nullptr;
        }

        int Inimigo::getNivelMaldade() const
        {
            return nivel_maldade;
        }

        int Inimigo::getDanoBase() const
        {
            return danoBase;
        }

        int Inimigo::getDanoMaximo() const
        {
            return danoMaximo;
        }

        float Inimigo::getRaioVisao() const
        {
            return raioVisao;
        }

        float Inimigo::getRaioAtaque() const
        {
            return raioAtaque;
        }

        Jogador* Inimigo::getAlvoAtual() const
        {
            return alvoAtual;
        }

        void Inimigo::setJogadores(Jogador* j1, Jogador* j2)
        {
            jogador1 = j1;
            jogador2 = j2;
        }

        void Inimigo::setNivelMaldade(int nivel)
        {
            if (nivel < 1)
            {
                nivel = 1;
            }

            nivel_maldade = nivel;
        }

        void Inimigo::setDanoBase(int dano)
        {
            if (dano < 0)
            {
                dano = 0;
            }

            danoBase = dano;
        }

        void Inimigo::setDanoMaximo(int dano)
        {
            if (dano < danoBase)
            {
                dano = danoBase;
            }

            danoMaximo = dano;
        }

        void Inimigo::setRaioVisao(float raio)
        {
            if (raio < 0.f)
            {
                raio = 0.f;
            }

            raioVisao = raio;
        }

        void Inimigo::setRaioAtaque(float raio)
        {
            if (raio < 0.f)
            {
                raio = 0.f;
            }

            raioAtaque = raio;
        }

        float Inimigo::calcularDistancia(Jogador* jogador) const
        {
            if (!jogador)
            {
                return 999999.f;
            }

            sf::Vector2f minhaPos = getCentro();
            sf::Vector2f posJog = jogador->getCentro();

            float dx = posJog.x - minhaPos.x;
            float dy = posJog.y - minhaPos.y;

            return std::sqrt(dx * dx + dy * dy);
        }

        Jogador* Inimigo::escolherAlvo()
        {
            Jogador* melhorAlvo = nullptr;
            float menorDistancia = 999999.f;

            if (jogador1 && jogador1->ativado() && jogador1->vivo())
            {
                float dist = calcularDistancia(jogador1);

                if (dist < menorDistancia)
                {
                    menorDistancia = dist;
                    melhorAlvo = jogador1;
                }
            }

            if (jogador2 && jogador2->ativado() && jogador2->vivo())
            {
                float dist = calcularDistancia(jogador2);

                if (dist < menorDistancia)
                {
                    menorDistancia = dist;
                    melhorAlvo = jogador2;
                }
            }

            alvoAtual = melhorAlvo;
            return melhorAlvo;
        }

        bool Inimigo::jogadorNoRaioVisao(Jogador* jogador) const
        {
            return calcularDistancia(jogador) <= raioVisao;
        }

        bool Inimigo::jogadorNoRaioAtaque(Jogador* jogador) const
        {
            return calcularDistancia(jogador) <= raioAtaque;
        }

        void Inimigo::perseguir(Jogador* jogador)
        {
            if (!jogador || travado)
            {
                return;
            }

            sf::Vector2f minhaPos = getCentro();
            sf::Vector2f posJog = jogador->getCentro();

            if (posJog.x < minhaPos.x)
            {
                vel.x -= velocidadeMovimento;
            }
            else if (posJog.x > minhaPos.x)
            {
                vel.x += velocidadeMovimento;
            }
        }

        void Inimigo::andarAleatorio()
        {
            if (travado)
            {
                return;
            }

            if (relogioMovimentoAleatorio.getElapsedTime().asSeconds() >= tempoTrocaDirecao)
            {
                int valor = std::rand() % 3;

                if (valor == 0)
                {
                    direcaoAleatoria = -1;
                }
                else if (valor == 1)
                {
                    direcaoAleatoria = 0;
                }
                else
                {
                    direcaoAleatoria = 1;
                }

                relogioMovimentoAleatorio.restart();
            }

            vel.x += direcaoAleatoria * velocidadeMovimento * 0.5f;
        }

        int Inimigo::calcularDanoAtual() const
        {
            int danoAtual = danoBase + nivel_maldade;

            if (danoAtual > danoMaximo)
            {
                danoAtual = danoMaximo;
            }

            return danoAtual;
        }

        void Inimigo::aumentarMaldade()
        {
            nivel_maldade++;

            if (nivel_maldade > 10)
            {
                nivel_maldade = 10;
            }
        }

        bool Inimigo::podeAtacar()
        {
            return relogioAtaque.getElapsedTime().asSeconds() >= intervaloAtaque;
        }

        void Inimigo::executar()
        {
            if (!ativo)
            {
                return;
            }

            Jogador* alvo = escolherAlvo();

            if (alvo && jogadorNoRaioVisao(alvo))
            {
                perseguir(alvo);
            }
            else
            {
                andarAleatorio();
            }

            atualizarFisica();
        }

        void Inimigo::salvarInimigo()
        {
            salvarPersonagem();

            buffer << nivel_maldade << " ";
            buffer << danoBase << " ";
            buffer << danoMaximo << " ";
            buffer << raioVisao << " ";
            buffer << raioAtaque << " ";
            buffer << intervaloAtaque << " ";
        }
    }
}