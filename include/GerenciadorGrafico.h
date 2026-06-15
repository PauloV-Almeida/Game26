#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "Texturas.h"
 

#define LARGURA_JANELA 1280
#define ALTURA_JANELA 720


#define FONTE_PATH "./assets/PressStart2P-Regular.ttf"

class Ente;

namespace Gerenciadores
{
    class GerenciadorGrafico
    {
    private:
		std::map<Texturas, sf::Texture> mapTexturas;

        //Texturas e fundos
        sf::Texture fundo1;
        sf::Sprite fundoSprite1;
        sf::Texture fundo2;
        sf::Sprite fundoSprite2;
        


		float janLargura;
		float janAltura;
        sf::FloatRect padraoView;
        sf::Font* font;
        sf::RenderWindow* janela;
		sf::Vector2i mousePos;
        
        static GerenciadorGrafico* instance;
        GerenciadorGrafico();

    public:
        ~GerenciadorGrafico();

        static GerenciadorGrafico* get_instance();
		const sf::FloatRect getPadraoView();
		sf::Vector2i* getMousePos();
		sf::Font* getFont();
		bool estaAberto();
		sf::RenderWindow* get_janela();
		sf::Texture* getTextura(Texturas);
		
		void setFrameLimit(int fps);
		void setView(sf::View);

		
		void limpar();
		void fechar();
		void mostrar();
		void carregarTexturas();
		void carregarTexturaInimigos();
		void carregarTexturaCenario();
		void carregarProjeteis();
		void carregarFundo();
		void carregarTexturaJogador();
		void desenharFundo();
		void desenhar(sf::Drawable* figura);
		void desenharEnte(Ente* ente);
		void atualizarMousePos();
    };
}