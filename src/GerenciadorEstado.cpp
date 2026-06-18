#include "../include/GerenciadorEstado.h"

namespace Gerenciadores {
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
        if (pendingChange == Actions::VOLTAR_1_MENU)
        {
            pop();
        }
        else if (pendingChange == Actions::PASSOU_DE_FASE)
        {
            pop();

            if (jogador1)
            {
                jogador1->setPosicao(100.f, 100.f);
                jogador1->setVelocidade(0.f, 0.f);
                jogador1->setAtivo(true);
            }

            if (jogador2)
            {
                jogador2->setPosicao(140.f, 100.f);
                jogador2->setVelocidade(0.f, 0.f);
                jogador2->setAtivo(true);
            }

            push(new Fases::ArenaGelo(jogador1, jogador2, false));
        }
        else if (pendingChange == Actions::VOLTAR_2_MENUS)
        {
            while (stack.size() > 1)
            {
                pop();
            }

            if (jogador1)
            {
                jogador1->setPosicao(100.f, 100.f);
                jogador1->setVelocidade(0.f, 0.f);
                jogador1->setAtivo(true);
                
            }

            if (jogador2)
            {
                jogador2->setPosicao(140.f, 100.f);
                jogador2->setVelocidade(0.f, 0.f);
                jogador2->setAtivo(true);
                
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

        case Actions::MENU_RANKING:
        {
            push(new MenuRanking());
            break;
        }

        case Actions::FASE_1:
        {
            push(new Fases::FlorestaGelo(jogador1, jogador2, false));
            break;
        }

        case Actions::FASE_2:
        {
            push(new Fases::ArenaGelo(jogador1, jogador2, false));
            break;
        }

        case Actions::VOLTAR_2_MENUS:
        {
            pendingChange = Actions::VOLTAR_2_MENUS;
            break;
        }

        case Actions::SELECIONAR_FASE:
        {
            push(new MenuSelecionar());
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
            std::ifstream arquivoLeitura("save.txt");
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

            break;
        }

        default:
            break;
        }
    }

	void GerenciadorEstado::executar()
	{
		

		if (stack.empty()) {
			pGG->fechar();
			return;
		}
		if (!stack.empty()) {
			stack.back()->executar();
		}

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
	
		stack.emplace_back(newState);
	}

    void GerenciadorEstado::clear()
    {
        while (!stack.empty())
        {
            pop();
        }
    }

}