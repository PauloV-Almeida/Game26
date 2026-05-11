#include "../include/GerenciadorGrafico.h"
#include <windows.h>
#include <direct.h>
#include <vector>
#include <fstream>
#include <iostream>

#define GETCWD_BUF_SIZE 1024

namespace Gerenciadores
{
	GerenciadorGrafico* GerenciadorGrafico::instance = nullptr;


	GerenciadorGrafico* GerenciadorGrafico::get_instance() {
		if (instance == nullptr) {
			instance = new GerenciadorGrafico();
		}
		return instance;
	}

	GerenciadorGrafico::GerenciadorGrafico(): 
		janela(new sf::RenderWindow(sf::VideoMode(LARGURA, ALTURA), "Megabonk++")),
		texturas()

	{
		janela->setFramerateLimit(120);
		fonte = new sf::Font;
		if (!fonte->loadFromFile(FONTE_PATH))
		{
			std::cout << "ERROR: FONTE N CARREGADA" << std::endl;
			exit(1);
		}
	}

	GerenciadorGrafico::~GerenciadorGrafico()
	{
		for (std::map<const std::string, sf::Texture*>::iterator it = texturas.begin(); it != texturas.end(); it++)
			delete it->second;
		texturas.clear();
		delete(janela);
		delete(fonte);
	}

	sf::RenderWindow* GerenciadorGrafico::get_janela() const {
		return janela;
	}

	void GerenciadorGrafico::mostrar() {
		if(abreJanela())
			janela->display();
	}

	void GerenciadorGrafico::limpar() {
		if(abreJanela())
			janela->clear();
	}

	void GerenciadorGrafico::desenhar(sf::RectangleShape* corpo) {
		janela->draw(*corpo);
	}

	void GerenciadorGrafico::desenhar(sf::CircleShape* corpo) {
		janela->draw(*corpo);
	}

	void GerenciadorGrafico::desenhar(sf::Text* texto) {
		janela->draw(*texto);
	}

	sf::Texture* GerenciadorGrafico::carregar_texturas(std::string path)
	{
		std::map<const std::string, sf::Texture*>::iterator it = texturas.find(path);
		if (it != texturas.end())
			return it->second;

		sf::Texture* text = new sf::Texture();

		if (!text->loadFromFile(path))
		{
			std::cout << "Erro ao carregar textura: " << path << std::endl;
		}
		texturas[path] = text;

		return text;
	}
	void GerenciadorGrafico::fechaJanela() {
		janela->close();
	}

	const bool GerenciadorGrafico::abreJanela() {
		return (janela->isOpen());
	}

	sf::Font* GerenciadorGrafico::getFonte() const {
		return fonte;
	}

}