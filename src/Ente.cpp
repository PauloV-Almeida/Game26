#include "../include/Ente.h"

Gerenciadores::GerenciadorGrafico* Ente::pGG = Gerenciadores::GerenciadorGrafico::get_instance();

Ente::Ente() : id()
{

}

Ente::~Ente()
{
}