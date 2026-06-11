#include "../include/Entidades.h"

int Entidades::Entidade::contarEntidades = 0;

namespace Entidades {

	Entidade::Entidade() :
		posicao(sf::Vector2f(0.f, 0.f)),
		vel(sf::Vector2f(0.f, 0.f)),
		ativo(true),
		buffer()
	{
		idUni = contarEntidades++;
		forma.scale(3, 3);
		forma.setPosition(posicao);
		//forma.setTexture(*pGG->getTextura(Texturas::projetil));
		setFigura(&forma);
	}

	Entidade::Entidade(sf::Vector2f pos) :
		posicao(pos),
		vel(sf::Vector2f(0.f, 0.f)),
		ativo(true),
		buffer()
	{

		idUni = contarEntidades++;
		forma.scale(3, 3);
		forma.setPosition(posicao);
		//forma.setTexture(*pGG->getTextura(Texturas::projetil));
		setFigura(&forma);
	}

	Entidade::~Entidade()
	{}


	sf::Vector2f Entidade::getCentro() const
	{
		sf::Vector2f centro;

		centro.x = forma.getGlobalBounds().left + forma.getGlobalBounds().width / 2.f;

		centro.y = forma.getGlobalBounds().top + forma.getGlobalBounds().height / 2.f;

		return centro;
	}
	sf::Vector2f Entidade::getPosicao()	const
	{

		return forma.getPosition();
	}
	int Entidade::getIdUnico() const
	{
		return idUni;
	}
	sf::FloatRect Entidade::getLimites() const
	{
	
		return forma.getGlobalBounds();
	}

	void Entidade::mover()
	{
		
		forma.move(vel);
	}
	void Entidade::mudarVelocidade(sf::Vector2f addVelo)
	{
		
		vel += addVelo;
	}

	void Entidade::salvarEntidade()
	{
		std::stringstream novoBuffer;
		buffer.str("");
		buffer.clear();
		switch (getId()) {
		case Id::Jogador: {
			buffer << "JOGADOR" << " ";
			break;
		}
		case Id::Valkiria: {
			buffer << "VALKIRIA" << " ";
			break;
		}
		case Id::Andarilho: {
			buffer << "ANDARILHO" << " ";
			break;
		}
		case Id::Espinho: {
			buffer << "ESPINHO" << " ";
			break;
		}
		case Id::Thor: {
			buffer << "THOR" << " ";
			break;
		}
		case Id::Runa: {
			buffer << "RUNA" << " ";
			break;
		}
		case Id::Projetil: {
			buffer << "PROJETIL" << " ";
			break;
		}
		case Id::Plataforma: {
			buffer << "PLATAFORMA" << " ";
			break;
		}
		case Id::Estrutura: {
			buffer << "ESTRUTURA" << " ";
			break;
		}
		default: {
			break;
		}
		}

		buffer << idUni << " ";
		buffer << ativo << " ";
		buffer << getPosicao().x << " ";
		buffer << getPosicao().y << " ";

		buffer << vel.x << " ";
		buffer << vel.y << " ";
	}

	void Entidade::desativar() {
		ativo = 0;
	}
	bool Entidade::ativado() const
	{
		return ativo;
	}

	void Entidade::setIdUni(int id)
	{
		idUni = id;
	}

	void Entidade::setAtivo(bool at)
	{
		ativo = at;
	}

	void Entidade::setPosicao(float x, float y)
	{
		forma.setPosition(x, y);
	}

	void Entidade::setVelocidade(float x, float y)
	{
		vel.x = x;
		vel.y = y;
	}



}