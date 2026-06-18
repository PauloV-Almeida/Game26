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

            /*
                Nivel de maldade:
                usado para aumentar a vida do boss.
            */
            setNivelMaldade(1 + rand() % 10);

            /*
                Boss:
                vida maior que inimigo comum.
                Exemplo:
                nivel 1  -> 22 de vida
                nivel 10 -> 40 de vida
            */
            num_vidas = 20 + (getNivelMaldade() * 2);

            /*
                Forca:
                aumenta o alcance do Thor.
                Como forca vai de 3 a 7:
                alcance vai de 570 a 730 pixels.
            */
            raioVisao = 450.f + static_cast<float>(forca * 40);

            forma.setTexture(*pGG->getTextura(Texturas::thor));
            forma.setTextureRect(sf::IntRect(0, 0, 81, 89));

            /*
                Boss pode ser um pouco maior que os outros inimigos.
                81x89 com escala 1.1 fica aproximadamente 89x98 px.
            */
            forma.setScale(1.1f, 1.1f);

            setFigura(&forma);
        }

        Thor::~Thor()
        {
            /*
                Thor não deleta o projétil.
                Quem desaloca é a listaEntidades da fase.
            */
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

            /*
                Dano corpo a corpo do Thor.
                Usa apenas o dano base herdado de Personagem.
            */
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

                /*
                    Lançamento do raio:
                    - O projétil é criado pela ArenaGelo.
                    - O Thor apenas usa o ponteiro.
                    - O projétil recebe velocidade inicial para cima.
                    - Depois ele cai por causa da gravidade no executar() dele.
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
                /*
                    Se depois você criar textura do Thor olhando para esquerda,
                    pode trocar aqui.

                    Exemplo:
                    forma.setTexture(*pGG->getTextura(Texturas::thorEsq));
                */
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