#pragma once

#include "Fase.h"

#define TEMPOFIM 1000

#define ARQ_INIMIGOS11 "./salvar/fase1/inimigo_1jog.dat"
#define ARQ_INIMIGOS12 "./salvar/fase1/inimigo_2jog.dat"

#define RESET_ARQ_JOG11 "./salvar/fase1/reset_jog1.dat"
#define RESET_ARQ_JOG12 "./salvar/fase1/reset_jog2.dat"

#define RESET_ARQ_INI11 "./salvar/fase1/reset_ini_1jog.dat"
#define RESET_ARQ_INI12 "./salvar/fase1/reset_ini_2jog.dat"

#define ARQUIVO_CENARIO_1 "./salvar/fase1/cenario.dat"
#define SALVAR_CENARIO_1 "./salvar/fase1/seed.dat"

#define ARQ_JOGADOR11 "./salvar/fase1/jogador1.dat"
#define ARQ_JOGADOR12 "./salvar/fase1/jogador2.dat"

namespace Fases
{
	class Deserto : public Fase
	{
	private:
		int fim;

	public:
		Deserto(int n_jogadores);
		Deserto();
		~Deserto();

		void executar();
		void salvar();
		void carregar();
		void resetar();

	};
}
