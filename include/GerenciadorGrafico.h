#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

#define LARGURA_JANELA 1920
#define ALTURA_JANELA 1080

#define LARGURA_MUNDO 1920.f
#define ALTURA_MUNDO 1080.f

#define FONTE_PATH "./assets/PressStart2P-Regular.ttf"

namespace Gerenciadores
{
    class GerenciadorGrafico
    {
    private:
        sf::RenderWindow* janela;
        sf::View viewMundo;

        std::map<const std::string, sf::Texture*> texturas;
        sf::Font* fonte;

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

        void configurarView();
        sf::View getViewMundo() const;
    };
}