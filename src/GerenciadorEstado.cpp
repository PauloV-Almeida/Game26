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
	GerenciadorEstado::GerenciadorEstado(Entidades::Personagens::Jogador* jogador_1, Entidades::Personagens::Jogador* jogador_2)
	{
		/**
		* @brief Inicializa o gerenciador de estados com o menu principal.
		*/
		jogador1 = jogador_1;
		jogador2 = jogador_2;
		push(new MenuPrincipal());
	}

	void GerenciadorEstado::aplicarMudancas()
	{
		if (pendingChange == Actions::VOLTAR_1_MENU) {
			pop();
		}
		else if (pendingChange == Actions::PASSOU_DE_FASE) {
			pop();
			jogador1->setPosicao(100, 100);
			jogador2->setPosicao(100, 100);
			push(new Fases::ArenaGelo(jogador1, jogador2, 0));
		}
		else if (pendingChange == Actions::VOLTAR_2_MENUS) {
			jogador1->resetarJogador();
			jogador2->resetarJogador();
			pop();
			pop();
		}


		pendingChange = Actions::NADA;
	}
	void GerenciadorEstado::update(Actions act) {
		switch (act) {
		case Actions::SALVAR: {
			Fases::Fase* pEstadoAnterior = static_cast<Fases::Fase*>(stack[stack.size() - 2]);
			pEstadoAnterior->salvar();
		}
		case Actions::VOLTAR_1_MENU: {
			pendingChange = act;
			break;
		}
		case Actions::MENU_RANKING: {
			push(new MenuRanking());
			break;
		}
		case Actions::FASE_1: {
			push(new Fases::Fase1(jogador1, jogador2, 0));
			break;
		}
		case Actions::FASE_2: {
			push(new Fases::Fase2(jogador1, jogador2, 0));
			break;
		}
		case Actions::VOLTAR_2_MENUS: {
			pendingChange = Actions::VOLTAR_2_MENUS;
			break;
		}
		case Actions::SELECIONAR_FASE: {
			push(new MenuSelectLvl());
			break;
		}
		case Actions::PAUSE: {
			push(new PauseState(static_cast<Fases::Fase*>(stack.back())));
			break;
		}
		case Actions::GAME_OVER:
		{
			push(new FimJogo(static_cast<Fases::Fase*>(stack.back())));
			jogador1->resetarJogador();
			jogador2->resetarJogador();
			break;
		}
		case Actions::PASSOU_DE_FASE:
		{
			pendingChange = Actions::PASSOU_DE_FASE;
			break;
		}
		case Actions::CARREGAR_SAVE: {
			push(new MenuSelectLvl());
			std::ifstream arquivoLeitura("save.txt");
			std::string linha;

			if (arquivoLeitura.is_open()) {
				std::getline(arquivoLeitura, linha);
				if (linha[0] == '1') {
					push(new Fases::Fase1(jogador1, jogador2, 1));
				}
				else if (linha[0] == '2') {
					push(new Fases::Fase2(jogador1, jogador2, 1));
				}
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
		
		if (!stack.empty()) {
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
		
		int i;
		for (i = stack.size() - 1; i >= 0; i--) {
			delete (*stack.begin() + i);
			stack.pop_back();
		}
	}

}