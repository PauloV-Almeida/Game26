#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>


#define LARGURA 800
#define ALTURA 600
#define FONTE_PATH "./assets/PressStart2P-Regular.ttf"

namespace Gerenciadores
{
	class GerenciadorGrafico
	{
	private:
		sf::RenderWindow* janela;	
		std::map<const std::string, sf::Texture*> texturas;
		sf::Font* fonte;

		//Sigleton
		static GerenciadorGrafico* instance;
		GerenciadorGrafico();
	public:
		~GerenciadorGrafico();
		static GerenciadorGrafico* get_instance();
		sf::RenderWindow* get_janela() const;

		void mostrar();
		void limpar();
		void desenhar(sf::RectangleShape* corpo);
		void desenhar(sf::CircleShape* corpo);
		void desenhar(sf::Text* texto);
		sf::Texture* carregar_texturas(std::string path);

		void fechaJanela();
		const bool abreJanela();
		sf::Font* getFonte() const;
	};
}


