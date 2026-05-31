#pragma once
#include <algorithm>
#include <random>

#include "Jogador.h"
#include "Andarilho.h"
#include "Plataforma.h"

#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "Estado.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#define TAMANHO_TILE 32
#define MAPA_COLUNAS 60
#define MAPA_LINHAS 34

namespace Fases
{
    class Fase : public Ente, public Estados::Estado
    {
    protected:
        int pontucaoTotal;

        Gerenciadores::GerenciadorColisoes gColisoes;
        Gerenciadores::GerenciadorEventos* pGE;

        Listas::ListaEntidades listaEntidades;

        Entidades::Personagens::Jogador* pJog1;
        Entidades::Personagens::Jogador* pJog2;

        std::string caminhoMapa;

        std::vector<sf::FloatRect> colisoresMapa;
        std::vector<sf::RectangleShape> tilesMapa;

        std::vector<sf::Vector2f> posicoesInimigosFaceis;

        sf::FloatRect portalProximaFase;
        bool temPortal;
        bool faseConcluida;

    protected:
        void criarAndarilho(sf::Vector2f pos);
        void criarPlataforma(sf::Vector2f pos);
        void criarBlocoSolido(sf::Vector2f pos);
        void criarPortal(sf::Vector2f pos);

        void definirSpawnJogador1(sf::Vector2f pos);
        void definirSpawnJogador2(sf::Vector2f pos);

        virtual void criarInimigos() = 0;
        virtual void criarObstaculos() = 0;

        virtual void tratarElementoMapa(int valor, sf::Vector2f pos);

        void carregarMapaTXT(const std::string& caminho);
        void criarCenario();

        void verificarPortal();
        void desenharMapa();

    public:
        Fase(
            int id,
            Entidades::Personagens::Jogador* j1,
            Entidades::Personagens::Jogador* j2 = nullptr,
            const std::string& mapa = ""
        );

        virtual ~Fase();

        virtual void executar() = 0;

        virtual void desenhar();

        void salvar();
        void carregarSalvamente();
        virtual void reiniciar();

        int getPontuacaoTotal() const { return pontucaoTotal; }
        bool getFaseConcluida() const { return faseConcluida; }
    };
}