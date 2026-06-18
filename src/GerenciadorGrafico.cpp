#include "../include/GerenciadorGrafico.h"
#include "../include/Ente.h"

#include <stdexcept>

namespace Gerenciadores
{
    GerenciadorGrafico* GerenciadorGrafico::instance = nullptr;

    GerenciadorGrafico* GerenciadorGrafico::get_instance()
    {
        if (instance == nullptr)
        {
            instance = new GerenciadorGrafico();
        }

        return instance;
    }

    GerenciadorGrafico::GerenciadorGrafico() :
        janLargura(LARGURA_JANELA),
        janAltura(ALTURA_JANELA),
        padraoView(sf::FloatRect(0.f, 0.f, janLargura, janAltura)),
        font(nullptr),
        janela(nullptr),
        mousePos(0, 0)
    {
        janela = new sf::RenderWindow(
            sf::VideoMode(static_cast<unsigned int>(janLargura), static_cast<unsigned int>(janAltura)),
            "Ragnarok++",
            sf::Style::Default
        );

        janela->setFramerateLimit(60);

        /*
            View padrão 1280x720.
            Mesmo que a janela seja redimensionada, a lógica do jogo continua
            trabalhando nessa resolução base.
        */
        sf::View view(sf::FloatRect(0.f, 0.f, janLargura, janAltura));
        janela->setView(view);

        font = new sf::Font();

        carregarTexturas();
    }

    GerenciadorGrafico::~GerenciadorGrafico()
    {
        if (janela)
        {
            delete janela;
            janela = nullptr;
        }

        if (font)
        {
            delete font;
            font = nullptr;
        }
    }

    void GerenciadorGrafico::mostrar()
    {
        if (janela)
        {
            janela->display();
        }
    }

    void GerenciadorGrafico::carregarTexturas()
    {
        carregarTexturaInimigos();
        carregarTexturaCenario();
        carregarProjeteis();
        carregarTexturaJogador();
        carregarFundo();
    }

    void GerenciadorGrafico::carregarTexturaInimigos()
    {
        sf::Texture tempText;

        try
        {
            if (!tempText.loadFromFile("texturas/valkiria.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura valkiria.PNG");
            }
            mapTexturas.insert({ Texturas::valkiria, tempText });

            if (!tempText.loadFromFile("texturas/andarilho.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura andarilho.PNG");
            }
            mapTexturas.insert({ Texturas::andarilho, tempText });

            if (!tempText.loadFromFile("texturas/thor.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura thor.PNG");
            }
            mapTexturas.insert({ Texturas::thor, tempText });
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exceção capturada durante o carregamento das texturas dos inimigos:\n"
                << e.what() << "\n";
            exit(1);
        }
    }

    void GerenciadorGrafico::carregarTexturaCenario()
    {
        sf::Texture tempText;

        try
        {
            if (!tempText.loadFromFile("texturas/espinho_venenoso.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura espinho_venenoso.PNG");
            }
            mapTexturas.insert({ Texturas::espinho, tempText });

            if (!tempText.loadFromFile("texturas/plataforma_gelo.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura plataforma_gelo.PNG");
            }
            mapTexturas.insert({ Texturas::plataforma, tempText });

            if (!tempText.loadFromFile("texturas/runa.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura runa.PNG");
            }
            mapTexturas.insert({ Texturas::runa, tempText });

            if (!tempText.loadFromFile("texturas/parede.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura parede.PNG");
            }
            mapTexturas.insert({ Texturas::parede, tempText });

            if (!tempText.loadFromFile("texturas/chao.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura chao.PNG");
            }
            mapTexturas.insert({ Texturas::chao, tempText });
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exceção capturada durante o carregamento das texturas do cenário:\n"
                << e.what() << "\n";
            exit(1);
        }
    }

    void GerenciadorGrafico::carregarProjeteis()
    {
        sf::Texture tempText;

        try
        {
            if (!tempText.loadFromFile("texturas/raio.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura raio.PNG");
            }

            mapTexturas.insert({ Texturas::projetil, tempText });
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exceção capturada durante o carregamento das texturas dos projeteis:\n"
                << e.what() << "\n";
            exit(1);
        }
    }

    void GerenciadorGrafico::carregarFundo()
    {
        sf::Texture tempText;

        try
        {
            if (!font->loadFromFile(FONTE_PATH))
            {
                throw std::runtime_error("Erro ao carregar a fonte");
            }

            if (!fundo1.loadFromFile("Fundo/Floresta_Gelo.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura Floresta_Gelo.PNG");
            }

            fundoSprite1.setTexture(fundo1);

            /*
                Ajusta o fundo para cobrir a janela 1280x720.
                Melhor do que usar setScale(4, 4) fixo.
            */
            if (fundo1.getSize().x > 0 && fundo1.getSize().y > 0)
            {
                fundoSprite1.setScale(
                    janLargura / static_cast<float>(fundo1.getSize().x),
                    janAltura / static_cast<float>(fundo1.getSize().y)
                );
            }

            if (!fundo2.loadFromFile("Fundo/Arena_Gelo.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura Arena_Gelo.PNG");
            }

            fundoSprite2.setTexture(fundo2);

            if (fundo2.getSize().x > 0 && fundo2.getSize().y > 0)
            {
                fundoSprite2.setScale(
                    janLargura / static_cast<float>(fundo2.getSize().x),
                    janAltura / static_cast<float>(fundo2.getSize().y)
                );
            }

            if (!tempText.loadFromFile("Fundo/imgMenu.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura imgMenu.PNG");
            }

            mapTexturas.insert({ Texturas::fundoMenu, tempText });
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exceção capturada durante o carregamento das texturas de background:\n"
                << e.what() << "\n";
            exit(1);
        }
    }

    void GerenciadorGrafico::carregarTexturaJogador()
    {
        sf::Texture tempText;
        sf::Image playerInvertido;

        try
        {
            if (!tempText.loadFromFile("texturas/jogador1.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura jogador1.PNG");
            }
            mapTexturas.insert({ Texturas::jogador1, tempText });

            if (!playerInvertido.loadFromFile("texturas/jogador1.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura jogador1.PNG para inverter");
            }

            playerInvertido.flipHorizontally();

            if (!tempText.loadFromImage(playerInvertido))
            {
                throw std::runtime_error("Falha ao inverter imagem do jogador1");
            }
            mapTexturas.insert({ Texturas::jogador1Esq, tempText });

            if (!tempText.loadFromFile("texturas/jogador2.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura jogador2.PNG");
            }
            mapTexturas.insert({ Texturas::jogador2, tempText });

            if (!playerInvertido.loadFromFile("texturas/jogador2.PNG"))
            {
                throw std::runtime_error("Falha ao carregar textura jogador2.PNG para inverter");
            }

            playerInvertido.flipHorizontally();

            if (!tempText.loadFromImage(playerInvertido))
            {
                throw std::runtime_error("Falha ao inverter imagem do jogador2");
            }
            mapTexturas.insert({ Texturas::jogador2Esq, tempText });
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exceção capturada durante o carregamento das texturas dos jogadores:\n"
                << e.what() << "\n";
            exit(1);
        }
    }

    void GerenciadorGrafico::desenharFundo(int idFase)
    {
        if (!janela)
        {
            return;
        }

        if (idFase == 1)
        {
            janela->draw(fundoSprite1);
        }
        else if (idFase == 2)
        {
            janela->draw(fundoSprite2);
        }
        else
        {
            janela->draw(fundoSprite1);
        }
    }

    void GerenciadorGrafico::desenhar(sf::Drawable* figura)
    {
        if (janela && figura)
        {
            janela->draw(*figura);
        }
    }

    void GerenciadorGrafico::desenharEnte(Ente* ente)
    {
        if (janela && ente && ente->getFigura())
        {
            janela->draw(*ente->getFigura());
        }
    }

    bool GerenciadorGrafico::estaAberto()
    {
        if (!janela)
        {
            return false;
        }

        return janela->isOpen();
    }

    sf::RenderWindow* GerenciadorGrafico::get_janela()
    {
        return janela;
    }

    sf::Texture* GerenciadorGrafico::getTextura(Texturas idText)
    {
        return &mapTexturas.at(idText);
    }

    void GerenciadorGrafico::limpar()
    {
        if (janela)
        {
            janela->clear();
        }
    }

    const sf::FloatRect GerenciadorGrafico::getPadraoView()
    {
        return padraoView;
    }

    sf::Vector2f* GerenciadorGrafico::getMousePos()
    {
        return &mousePos;
    }

    sf::Font* GerenciadorGrafico::getFont()
    {
        return font;
    }

    void GerenciadorGrafico::atualizarMousePos()
    {
        if (!janela)
        {
            return;
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(*janela);
        mousePos = janela->mapPixelToCoords(pixelPos);
    }

    void GerenciadorGrafico::setFrameLimit(int fps)
    {
        if (janela)
        {
            janela->setFramerateLimit(fps);
        }
    }

    void GerenciadorGrafico::fechar()
    {
        if (janela)
        {
            janela->close();
        }
    }

    void GerenciadorGrafico::setView(sf::View view)
    {
        if (janela)
        {
            janela->setView(view);
        }
    }
}