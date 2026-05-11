#include "../include/Deserto.h"

namespace Fases
{
	Deserto::Deserto() :
		Fase(1),
		fim(0)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

	}

	Deserto::Deserto(int n_jogadores) :
		Fase(6),
		fim(TEMPOFIM)
	{
		corpo.setSize(sf::Vector2f(900.f, 600.f));
		texturas = pGG->carregar_texturas("./assets/Deserto.png");
		corpo.setTexture(texturas);

	}

	Deserto::~Deserto()
	{
		if (carregado)
		{
			salvar();
		}
	}

	void Deserto::executar()
	{
		if (!carregado)
		{
			carregar();
		}

		jogadores.executar();
		obstaculos.executar();
		inimigos.executar();

		gColisoes.executar();

		desenhar();

		if (pEG->get_AtualEstadoID() == id_estado)
		{
			Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> it = jogadores.get_Primeiro();
			Entidades::Personagens::Jogador* p1 = dynamic_cast<Entidades::Personagens::Jogador*>(*it);
			it++;
			/*if (jogadores.get_tamanho() == 1)
			{
				pEG->set_AtualEstado(2);
				pEG->reseta_AtualEstado();
				
			}
			else
			{
				Entidades::Personagens::Jogador* p2 = dynamic_cast<Entidades::Personagens::Jogador*>(*it);
				if (fim < 0)
				{
					pEG->set_AtualEstado(5);
					pEG->reseta_AtualEstado();
				}
				if (fim < TEMPOFIM)
					fim--;
			}*/
		}
		jogadores.desenhar();
		inimigos.desenhar();
		obstaculos.desenhar();
	}//executar

	void Deserto::salvar()
	{
		std::ofstream jogadoresArq;
		std::ofstream inimigosArq;

		if (id_estado == 1)
		{
			jogadoresArq.open(ARQ_JOGADOR11);
			inimigosArq.open(ARQ_INIMIGOS11);
		}else if(id_estado == 6)
		{
			jogadoresArq.open(ARQ_JOGADOR12);
			inimigosArq.open(ARQ_INIMIGOS12);
		}

		if (!jogadoresArq)
		{
			std::cerr << "ERRO ARQUIVO JOGADOR\n";
			exit(1);
		}

		jogadoresArq << jogadores.get_tamanho() << std::endl;
		//jogadores.salvar(jogadoresArq);
		jogadoresArq.close();

		if (!inimigosArq)
		{
			std::cerr << "ERRO ARQUIVO INIMIGOS\n";
			exit(1);
		}
		inimigosArq << inimigos.get_tamanho() << std::endl;
		//inimigos.salvar(inimigosArq);
		inimigosArq.close();
	}
	void Deserto::carregar()
	{
		carregaCenario(SALVAR_CENARIO_1);

		int n, vivo, dano, vida;
		float vx, vy, px, py, tamx, tamy;
		std::string linha;
		std::ifstream jogadoresArq;
		std::ifstream inimigosArq;

		if (id_estado == 1)
		{
			jogadoresArq.open(ARQ_JOGADOR11);
			inimigosArq.open(ARQ_INIMIGOS11);
		}
		else if (id_estado == 6)
		{
			jogadoresArq.open(ARQ_JOGADOR12);
			inimigosArq.open(ARQ_INIMIGOS12);
		}
		if (!jogadoresArq)
		{
			std::cerr << "ERRO ARQUIVO JOGADOR\n";
			exit(1);
		}
		jogadoresArq >> n;

		// Se não há mais dados no arquivo além do número, criar jogadores padrão
		jogadoresArq >> std::ws;
		if (jogadoresArq.peek() == EOF)
		{
			for (int i = 0; i < n; i++)
			{
				// valores padrão — ajuste conforme necessário
				vivo = 1;
				vida = 100;
				px = 50.f + i * 50.f;
				py = 50.f;
				vx = 0.f; vy = 0.f;
				tamx = 32.f; tamy = 32.f;

				Entidades::Personagens::Jogador* pJog = new Entidades::Personagens::Jogador(i + 1, vivo, vida, sf::Vector2f(px, py), sf::Vector2f(vx, vy), sf::Vector2f(tamx, tamy));
				Entidades::Entidade* jogador = pJog;

				if (jogador)
				{
					jogadores.add(jogador);
					jogador->set_GerenciadorColisao(&gColisoes);
				}
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (!(jogadoresArq >> vivo >> vida >> px >> py >> vx >> vy >> tamx >> tamy))
				{
					// leitura falhou — criar restando com padrão
					vivo = 1; vida = 100; px = 50.f + i * 50.f; py = 50.f; vx = vy = 0.f; tamx = tamy = 32.f;
				}
				Entidades::Personagens::Jogador* pJog = new Entidades::Personagens::Jogador(i + 1, vivo, vida, sf::Vector2f(px, py), sf::Vector2f(vx, vy), sf::Vector2f(tamx, tamy));
				Entidades::Entidade* jogador = pJog;

				if (jogador)
				{
					jogadores.add(jogador);
					jogador->set_GerenciadorColisao(&gColisoes);
				}
			}
		}

		if (!inimigosArq)
		{
			std::cerr << "ERRO ARQUIVO INIMIGOS\n";
			exit(1);
		}
		inimigosArq >> n;
		for (int i = 0; i < n; i++)
		{
			criarEsqueleto(inimigosArq);
		}
		carregado = true;
	}
	void Deserto::resetar()
	{
		criarCenario(ARQUIVO_CENARIO_1, SALVAR_CENARIO_1);
		if(carregado)
			jogadores.limpar();
		if(carregado)
			inimigos.limpar();

		int n, vivo, dano, vida, vx, vy, px, py, tamx, tamy;
		std::string linha;

		std::ifstream jogadoresArq;
		std::ifstream inimigosArq;
		if (id_estado == 1)
		{
			jogadoresArq.open(RESET_ARQ_JOG11);
			inimigosArq.open(RESET_ARQ_INI11);
		}
		else if (id_estado == 6)
		{
			jogadoresArq.open(RESET_ARQ_JOG12);
			inimigosArq.open(RESET_ARQ_INI12);
		}
		if (!jogadoresArq)
		{
			std::cerr << "ERRO ARQUIVO JOGADOR\n";
			exit(1);
		}
		jogadoresArq >> n;
		for (int i = 0; i < n; i++)
		{
			jogadoresArq >> vivo >> vida >> px >> py >> vx >> vy >> tamx >> tamy;
			Entidades::Personagens::Jogador* pJog = new Entidades::Personagens::Jogador(i + 1, vivo, vida, sf::Vector2f(px, py), sf::Vector2f(vx, vy), sf::Vector2f(tamx, tamy));
			Entidades::Entidade* jogador = pJog;
			if (jogador)
			{
				jogadores.add(jogador);
				jogador->set_GerenciadorColisao(&gColisoes);
			}
		}
		if (!inimigosArq)
		{
			std::cerr << "ERRO ARQUIVO INIMIGOS\n";
			exit(1);
		}
		inimigosArq >> n;
		for (int i = 0; i < n; i++)
		{
			getline(inimigosArq, linha); // consumir a quebra de linha restante
			criarEsqueleto(inimigosArq);
		}
		carregado = true;
	}
}