#include "../include/GerenciadorEstado.h"

namespace Gerenciadores
{
    void GerenciadorEstado::setJogador1(Entidades::Personagens::Jogador* jogador)
    {
        jogador1 = jogador;
    }

    void GerenciadorEstado::setJogador2(Entidades::Personagens::Jogador* jogador)
    {
        jogador2 = jogador;
    }

    GerenciadorEstado::GerenciadorEstado(
        Entidades::Personagens::Jogador* jogador_1,
        Entidades::Personagens::Jogador* jogador_2
    ) :
        jogador1(jogador_1),
        jogador2(jogador_2),
        janela(nullptr),
        stack(),
        pendingChange(Actions::NADA)
    {
        mediadorEventos::getMediadorEventos()->incluirSubject(this);

        push(new MenuPrincipal());
    }

    GerenciadorEstado::~GerenciadorEstado()
    {
        clear();

        jogador1 = nullptr;
        jogador2 = nullptr;
        janela = nullptr;
    }

    void GerenciadorEstado::aplicarMudancas()
    {
        if (pendingChange == Actions::NADA)
        {
            return;
        }

        if (pendingChange == Actions::VOLTAR_1_MENU)
        {
            pop();
        }
        else if (pendingChange == Actions::VOLTAR_2_MENUS)
        {
            while (stack.size() > 1)
            {
                pop();
            }

            if (jogador1)
            {
                jogador1->resetarJogador();
                jogador1->setJogadorDois(false);
            }

            if (jogador2)
            {
                jogador2->resetarJogador();
                jogador2->setJogadorDois(true);
            }
        }
        else if (pendingChange == Actions::FASE_1)
        {
            /*
                Volta para o menu principal e remove qualquer fase,
                tela de game over, pause ou menu de seleção que esteja aberta.
            */
            while (stack.size() > 1)
            {
                pop();
            }

            /*
                Novo jogo precisa resetar os jogadores.
                Se não resetar, eles podem continuar mortos/desativados
                do jogo anterior e a fase já começa em GAME_OVER.
            */
            if (jogador1)
            {
                jogador1->resetarJogador();
                jogador1->setJogadorDois(false);
            }

            if (jogador2)
            {
                jogador2->resetarJogador();
                jogador2->setJogadorDois(true);
            }

            /*
                false = começa pelo mapa TXT, sem carregar save.
            */
            push(new Fases::FlorestaGelo(jogador1, jogador2, false));
        }
        else if (pendingChange == Actions::FASE_2)
        {
            while (stack.size() > 1)
            {
                pop();
            }

            if (jogador1)
            {
                jogador1->resetarJogador();
                jogador1->setJogadorDois(false);
            }

            if (jogador2)
            {
                jogador2->resetarJogador();
                jogador2->setJogadorDois(true);
            }

            push(new Fases::ArenaGelo(jogador1, jogador2, false));
        }
        else if (pendingChange == Actions::PASSOU_DE_FASE)
        {
            /*
                Remove a fase atual.
            */
            pop();

            /*
                Ao passar para a fase 2, mantém os jogadores,
                mas recoloca eles ativos e sem velocidade.
            */
            if (jogador1)
            {
                jogador1->resetarJogador();
                jogador1->setJogadorDois(false);
            }

            if (jogador2)
            {
                jogador2->resetarJogador();
                jogador2->setJogadorDois(true);
            }

            push(new Fases::ArenaGelo(jogador1, jogador2, false));
        }
        else if (pendingChange == Actions::CARREGAR_SAVE)
        {
            while (stack.size() > 1)
            {
                pop();
            }

            if (jogador1)
            {
                jogador1->resetarJogador();
                jogador1->setJogadorDois(false);
            }

            if (jogador2)
            {
                jogador2->resetarJogador();
                jogador2->setJogadorDois(true);
            }

            std::ifstream arquivoLeitura("salvar/salvar.txt");
            std::string linha;

            if (arquivoLeitura.is_open())
            {
                std::getline(arquivoLeitura, linha);

                if (!linha.empty() && linha[0] == '1')
                {
                    push(new Fases::FlorestaGelo(jogador1, jogador2, true));
                }
                else if (!linha.empty() && linha[0] == '2')
                {
                    push(new Fases::ArenaGelo(jogador1, jogador2, true));
                }

                arquivoLeitura.close();
            }
        }

        pendingChange = Actions::NADA;
    }

    void GerenciadorEstado::update(Actions act)
    {
        switch (act)
        {
        case Actions::SALVAR:
        {
            if (stack.size() >= 2)
            {
                Fases::Fase* fase = dynamic_cast<Fases::Fase*>(stack[stack.size() - 2]);

                if (fase)
                {
                    fase->salvar();
                }
            }

            break;
        }

        case Actions::VOLTAR_1_MENU:
        {
            pendingChange = Actions::VOLTAR_1_MENU;
            break;
        }

        case Actions::VOLTAR_2_MENUS:
        {
            pendingChange = Actions::VOLTAR_2_MENUS;
            break;
        }

        case Actions::MENU_RANKING:
        {
            push(new MenuRanking());
            break;
        }

        case Actions::SELECIONAR_FASE:
        {
            push(new MenuSelecionar());
            break;
        }

        case Actions::FASE_1:
        {
            /*
                Não cria a fase aqui direto.
                Apenas marca para criar depois que o estado atual terminar de executar.
            */
            pendingChange = Actions::FASE_1;
            break;
        }

        case Actions::FASE_2:
        {
            pendingChange = Actions::FASE_2;
            break;
        }

        case Actions::PAUSE:
        {
            Fases::Fase* faseAtual = dynamic_cast<Fases::Fase*>(stack.back());

            if (faseAtual)
            {
                push(new EstadoPause(faseAtual));
            }

            break;
        }

        case Actions::GAME_OVER:
        {
            Fases::Fase* faseAtual = dynamic_cast<Fases::Fase*>(stack.back());

            if (faseAtual)
            {
                push(new FimJogo(faseAtual));
            }

            break;
        }

        case Actions::PASSOU_DE_FASE:
        {
            pendingChange = Actions::PASSOU_DE_FASE;
            break;
        }

        case Actions::CARREGAR_SAVE:
        {
            /*
                Continuar também fica pendente.
                Assim evita criar fase no meio da execução do menu.
            */
            pendingChange = Actions::CARREGAR_SAVE;
            break;
        }

        default:
            break;
        }
    }

    void GerenciadorEstado::executar()
    {
        if (stack.empty())
        {
            pGG->fechar();
            return;
        }

        stack.back()->executar();

        aplicarMudancas();
    }

    void GerenciadorEstado::pop()
    {
        if (!stack.empty())
        {
            delete stack.back();
            stack.pop_back();
        }
    }

    void GerenciadorEstado::push(State* newState)
    {
        if (newState)
        {
            stack.emplace_back(newState);
        }
    }

    void GerenciadorEstado::clear()
    {
        while (!stack.empty())
        {
            pop();
        }
    }
}