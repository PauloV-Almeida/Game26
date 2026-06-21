#include "../include/Thor.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Thor::Thor(sf::Vector2f pos, Jogador* jogador, Projetil* projetil) :
            Inimigo(pos, jogador),
            forca(3 + rand() % 5),
            projetil(projetil),
            relogioProjetil(),
            intervaloProjetil(2.f)
        {
            id = Id::Thor;

            if (this->projetil)
            {
                this->projetil->setThor(this);
            }

            setNivelMaldade(1 + rand() % 10);

            num_vidas = 20 + (getNivelMaldade() * 2);
            raioVisao = 450.f + static_cast<float>(forca * 40);

            forma.setTexture(*pGG->getTextura(Texturas::thor));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));
            forma.setScale(1.1f, 1.1f);

            setFigura(&forma);
        }

        Thor::~Thor()
        {
            projetil = nullptr;
        }

        void Thor::setProjetil(Projetil* pProjetil)
        {
            projetil = pProjetil;

            if (projetil)
            {
                projetil->setThor(this);
            }
        }

        void Thor::danificar(Jogador* jogador)
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
                danoContatoRelogio.restart();
            }
        }

        void Thor::executar()
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

                
                if (projetil && !projetil->foiLancado())
                {
                    if (relogioProjetil.getElapsedTime().asSeconds() >= intervaloProjetil)
                    {
                        sf::Vector2f origem = getCentro();
                        sf::Vector2f alvo = pJogador->getCentro();

                        projetil->setDano(getDanoBase());
                        projetil->lancar(origem, alvo, forca);

                        relogioProjetil.restart();
                    }
                }
            }
            else
            {
                velo.x = 0.f;
            }

            atualizarFisica();
        }

        std::string Thor::salvar()
        {
            salvarDataBuffer();
            return buffer.str();
        }

        void Thor::salvarDataBuffer()
        {
            Inimigo::salvarDataBuffer();

            buffer << forca << " ";

            if (projetil)
            {
                buffer << projetil->getIdUnico() << " ";
            }
            else
            {
                buffer << -1 << " ";
            }
        }
    }
}