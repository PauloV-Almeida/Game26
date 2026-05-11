#include "../include/Megabonk.h"

MegaBonk::MegaBonk() :
	pGG(Gerenciadores::GerenciadorGrafico::get_instance()),
	pGE(Gerenciadores::GerenciadorEventos::get_instance()),
	pGEst(Gerenciadores::GerenciadorEstado::get_instance()),
	fDeserto(),
	fDeserto_2p(2),
	main_menu()
{
	executar();
}



MegaBonk::~MegaBonk()
{
}

void MegaBonk::executar()
{
	
	while (pGG->abreJanela()) {
		pGG->limpar();

		pGE->executar();
		pGEst->executar();
		
		pGG->mostrar();
	}
}