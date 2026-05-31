#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Jogador::Jogador(int indice, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
            Personagem(indice, pos, velo, tam),
            ataque_corpo(sf::Vector2f(tam.x * 2.f, tam.y * 2.f)),
            atacando(false),
            id_jogador(indice),
            venceu(false),
            direita(true),
            ataque_direcao("Direita")
        {
            dano = DMG;
            n_vidas = 20;

            ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2.f, ataque_corpo.getSize().y / 2.f);

            if (id_jogador == 1)
            {
                texturas = pGG->carregar_texturas("./assets/jogador1.png");
            }
            else if (id_jogador == 2)
            {
                texturas = pGG->carregar_texturas("./assets/jogador2.png");
            }
            else
            {
                texturas = pGG->carregar_texturas("./assets/jogador1.png");
            }

            corpo.setTexture(texturas);
            ataque_corpo.setTexture(texturas);
        }

        Jogador::Jogador(int indice, bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
            Personagem(indice, pos, velo, tam),
            ataque_corpo(sf::Vector2f(tam.x * 2.f, tam.y * 2.f)),
            atacando(false),
            id_jogador(indice),
            venceu(false),
            direita(true),
            ataque_direcao("Direita")
        {
            dano = DMG;
            vivo = viv;
            n_vidas = nV;

            ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2.f, ataque_corpo.getSize().y / 2.f);

            if (id_jogador == 1)
            {
                texturas = pGG->carregar_texturas("./assets/jogador1.png");
            }
            else if (id_jogador == 2)
            {
                texturas = pGG->carregar_texturas("./assets/jogador2.png");
            }
            else
            {
                texturas = pGG->carregar_texturas("./assets/jogador1.png");
            }

            corpo.setTexture(texturas);
            ataque_corpo.setTexture(texturas);
        }

        Jogador::~Jogador()
        {}

        bool Jogador::teclaEsquerdaPressionada() const
        {
            if (id_jogador == 1)
            {
                return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
            }

            return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        }

        bool Jogador::teclaDireitaPressionada() const
        {
            if (id_jogador == 1)
            {
                return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
            }

            return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        }

        bool Jogador::teclaPuloPressionada() const
        {
            if (id_jogador == 1)
            {
                return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
            }

            return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        }

        bool Jogador::teclaAtaquePressionada() const
        {
            if (id_jogador == 1)
            {
                return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            }

            return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        }

        std::string Jogador::obterDirecaoAtaque() const
        {
            if (id_jogador == 1)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    return "Acima";

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    return "Abaixo";

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    return "Esquerda";

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    return "Direita";
            }
            else if (id_jogador == 2)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    return "Acima";

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    return "Abaixo";

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    return "Esquerda";

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    return "Direita";
            }

            if (direita)
                return "Direita";

            return "Esquerda";
        }

        void Jogador::atualizarTexturaMovimento()
        {
            if (id_jogador == 1)
            {
                if (direita)
                    corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-direita.png"));
                else
                    corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-esquerda.png"));
            }
            else if (id_jogador == 2)
            {
                if (direita)
                    corpo.setTexture(pGG->carregar_texturas("./assets/jogador2-direita.png"));
                else
                    corpo.setTexture(pGG->carregar_texturas("./assets/jogador2-esquerda.png"));
            }
        }

        void Jogador::limitarVelocidadeHorizontal()
        {
            if (vel.x > VEL_MAX)
            {
                vel.x = VEL_MAX;
            }
            else if (vel.x < -VEL_MAX)
            {
                vel.x = -VEL_MAX;
            }
        }

        void Jogador::atualizarCorpoAtaque(const std::string& direcao)
        {
            sf::Vector2f pos = corpo.getPosition();
            sf::Vector2f tam = corpo.getSize();
            sf::Vector2f tamAtaque = ataque_corpo.getSize();

            if (direcao == "Acima")
            {
                ataque_corpo.setPosition(
                    sf::Vector2f(
                        pos.x,
                        pos.y - tam.y / 2.f - tamAtaque.y / 2.f
                    )
                );
            }
            else if (direcao == "Abaixo")
            {
                ataque_corpo.setPosition(
                    sf::Vector2f(
                        pos.x,
                        pos.y + tam.y / 2.f + tamAtaque.y / 2.f
                    )
                );
            }
            else if (direcao == "Direita")
            {
                ataque_corpo.setPosition(
                    sf::Vector2f(
                        pos.x + tam.x / 2.f + tamAtaque.x / 2.f,
                        pos.y
                    )
                );
            }
            else if (direcao == "Esquerda")
            {
                ataque_corpo.setPosition(
                    sf::Vector2f(
                        pos.x - tam.x / 2.f - tamAtaque.x / 2.f,
                        pos.y
                    )
                );
            }
        }

        void Jogador::executar()
        {
            if (n_vidas <= 0)
            {
                vivo = false;
                return;
            }

            mover();
            ataque();
        }

        void Jogador::mover(char direcao)
        {
            if (!vivo)
            {
                return;
            }

            if (!noChao)
            {
                vel.y += GRAVIDADE;
            }

            if (teclaEsquerdaPressionada())
            {
                vel.x -= VELOCIDADE;
                direita = false;
                atualizarTexturaMovimento();
            }
            else if (teclaDireitaPressionada())
            {
                vel.x += VELOCIDADE;
                direita = true;
                atualizarTexturaMovimento();
            }
            else
            {
                vel.x *= 0.8f;
            }

            limitarVelocidadeHorizontal();

            if (teclaPuloPressionada() && noChao)
            {
                vel.y = -6.0f;
                noChao = false;
            }

            corpo.move(vel.x, vel.y);

            /*
                Depois que o jogador se move, ele começa assumindo que não está no chão.
                Se ele realmente estiver em cima de uma plataforma, o GerenciadorColisoes
                vai detectar a colisão e a Plataforma::obstaculizar() vai marcar noChao = true.
            */
            noChao = false;
        }

        void Jogador::colidir(Inimigo* pIni, std::string direcao)
        {
            if (!pIni)
            {
                return;
            }

            if (direcao == "Embaixo")
            {
                noChao = true;
                vel.y = 0.0f;
            }
            else if (direcao == "Cima" || direcao == "Emcima")
            {
                vel.y = 0.0f;
            }
            else if (direcao == "Esquerda" || direcao == "Direita")
            {
                vel.x = 0.0f;
            }
        }

        void Jogador::ataque()
        {
            if (!vivo)
            {
                return;
            }

            if (!teclaAtaquePressionada())
            {
                atacando = false;
                dano = 0;
                return;
            }

            dano = DMG;
            atacando = true;

            ataque_direcao = obterDirecaoAtaque();
            atualizarCorpoAtaque(ataque_direcao);
        }

        void Jogador::desenhar()
        {
            if (!vivo)
            {
                return;
            }

            pGG->desenhar(&corpo);

            if (atacando)
            {
                if (ataque_direcao == "Direita")
                {
                    ataque_corpo.rotate(90);
                    pGG->desenhar(&ataque_corpo);
                    ataque_corpo.rotate(-90);
                }
                else if (ataque_direcao == "Esquerda")
                {
                    ataque_corpo.rotate(-90);
                    pGG->desenhar(&ataque_corpo);
                    ataque_corpo.rotate(90);
                }
                else if (ataque_direcao == "Abaixo")
                {
                    ataque_corpo.rotate(180);
                    pGG->desenhar(&ataque_corpo);
                    ataque_corpo.rotate(180);
                }
                else
                {
                    pGG->desenhar(&ataque_corpo);
                }
            }
        }
        void Jogador::salvarDataBuffer()
        {
            Personagem::salvarDataBuffer();

            bufferSalvar
                << "Jogador" << ' '
                << id_jogador << ' '
                << venceu << ' '
                << direita << ' '
                << atacando << ' '
                << ataque_direcao << '\n';
        }

        void Jogador::salvar(std::ostream& out)
        {
            salvarDataBuffer();
            out << getBufferSalvar();
        }
    }
}