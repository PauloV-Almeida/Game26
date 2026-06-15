#include "../include/Botao.h"

namespace Entidades
{
    Button::Button(sf::Vector2f pos, std::string txt, Actions action) :
        Ente(),
        mediador(mediadorEventos::getMediadorEventos()),
        buttonText(),
        buttonAction(action)
    {
        buttonText.setFont(*pGG->getFont());
        buttonText.setString(txt);
        buttonText.setCharacterSize(28);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(pos);

        setFigura(&buttonText);
    }

    Button::~Button()
    {}

    void Button::getClicked(sf::Vector2i* mousePos)
    {
        if (!mousePos)
        {
            return;
        }

        sf::FloatRect bounds = buttonText.getGlobalBounds();

        sf::Vector2f mouseWorld(
            static_cast<float>(mousePos->x),
            static_cast<float>(mousePos->y)
        );

        if (bounds.contains(mouseWorld))
        {
            mediador->notify(buttonAction);
        }
    }

    void Button::executar()
    {
        desenhar();
    }
}