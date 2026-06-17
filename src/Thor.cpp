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

            setNivelMaldade(1 + rand() % 10);

            /*
                Boss:
                nivel_maldade duplica/influencia muito a vida.
            */
            num_vidas = 10 + (getNivelMaldade() * 2);

            /*
                forca aumenta o alcance do Thor.
            */
            raioVisao = 450.f + static_cast<float>(forca * 2);

            forma.setTexture(*pGG->getTextura(Texturas::thor));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));

            /*
                Boss pode ser maior, mas cuidado com tile 64.
                1.1 deixa ele maior que inimigo comum sem ficar absurdo.
            */
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
                /*
                    Dano corpo a corpo do Thor:
                    usa dano base herdado.
                */
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

                /*
                    Disparo do raio:
                    Thor lança o projétil em direção à posição atual do jogador.
                    O projétil sobe primeiro e depois cai por gravidade.
                */
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

            if (direcao == Direcao::LEFT)
            {
                // Se tiver textura esquerda do Thor:
                // forma.setTexture(*pGG->getTextura(Texturas::thorEsq));
            }
            else
            {
                forma.setTexture(*pGG->getTextura(Texturas::thor));
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