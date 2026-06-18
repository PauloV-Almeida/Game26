#include "../include/FimDeJogo.h"

FimJogo::FimJogo(Fases::Fase* fase) :
    menuEstado(),
    pFase(fase),
    textoNomeJogador(),
    pontuacao(0),
    nomeJogador()
{
    if (pFase)
    {
        pontuacao = pFase->getPontuacaoTotal();
    }

    carregarBotoes();

    textoNomeJogador.setPosition(300.f, 300.f);
    textoNomeJogador.setCharacterSize(35);
    textoNomeJogador.setFont(*(pGG->getFont()));
    textoNomeJogador.setFillColor(sf::Color::White);
    textoNomeJogador.setString("NOME: ");

    setFigura(&textoNomeJogador);
}

FimJogo::~FimJogo()
{
    pFase = nullptr;
}

void FimJogo::salvarRanking()
{
    if (nomeJogador.empty())
    {
        nomeJogador = "JOGADOR";
    }

    std::ofstream arquivo("salvar/ranking.txt", std::ios::app);

    if (arquivo.is_open())
    {
        arquivo << nomeJogador << " " << pontuacao << std::endl;
        arquivo.close();
    }
}

void FimJogo::carregarBotoes()
{
    botaoVector.push_back(
        new Entidades::Button(
            sf::Vector2f(300.f, 450.f),
            "Salvar e voltar",
            Actions::VOLTAR_2_MENUS
        )
    );
}

void FimJogo::lidarEvent()
{
    sf::Event ev;

    while (pGG->get_janela()->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            pGG->fechar();
            break;

        case sf::Event::KeyPressed:
            if (ev.key.code >= sf::Keyboard::A && ev.key.code <= sf::Keyboard::Z)
            {
                if (nomeJogador.size() < 12)
                {
                    char letra = static_cast<char>('A' + (ev.key.code - sf::Keyboard::A));
                    nomeJogador.push_back(letra);
                }
            }
            else if (ev.key.code == sf::Keyboard::BackSpace)
            {
                if (!nomeJogador.empty())
                {
                    nomeJogador.pop_back();
                }
            }
            else if (ev.key.code == sf::Keyboard::Enter)
            {
                salvarRanking();
                mediador->notify(Actions::VOLTAR_2_MENUS);
            }
            else if (ev.key.code == sf::Keyboard::Escape)
            {
                mediador->notify(Actions::VOLTAR_2_MENUS);
            }
            break;

        case sf::Event::MouseButtonPressed:
            if (ev.mouseButton.button == sf::Mouse::Left)
            {
                salvarRanking();
                mouseClick();
            }
            break;

        default:
            break;
        }
    }
}

void FimJogo::executar()
{
    pGG->limpar();

    setFigura(&fundoMenu);
    desenhar();

    lidarEvent();
    execBotoes();

    std::stringstream texto;
    texto << "FIM DE JOGO\n";
    texto << "PONTOS: " << pontuacao << "\n";
    texto << "NOME: " << nomeJogador << "\n";
    texto << "ENTER para salvar";

    textoNomeJogador.setString(texto.str());

    setFigura(&textoNomeJogador);
    desenhar();
}