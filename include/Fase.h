#pragma once

#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>


#include "State.h"

#include "Jogador.h"
#include "Estrutura.h"
#include "Plataforma.h"
#include "EspinhoVenenoso.h"
#include "Runa.h"
#include "Andarilho.h"
#include "Valkiria.h"
#include "Thor.h"
#include "Projetil.h"

#include "GerenciadorColisao.h"
#include "Hub.h"
#include "ListaEntidades.h"
#include "TipoEstrutura.h"

#define MIN 3
#define MAX 7

namespace Fases
{
    class Fase : public State
    {
    protected:
        static constexpr float TAM_TILE = 64.f;

		std::string caminhoMapa;

        int pontuacaoTotal;
        int id;

        sf::View view;
        Hub hub;

        Gerenciadores::GerenciadorColisao gC;
        Listas::ListaEntidades listaEntidades;

        bool jogador2Ativo;

        Entidades::Personagens::Jogador* jogador1;
        Entidades::Personagens::Jogador* jogador2;

        sf::FloatRect areaPassagem;
		bool possuiPassagem;

    protected:
        virtual void lidarEvent();

        void executarJanela();

        void criarAndarilhos();
        void criarPlataformas();
        void criarCenario();

        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;

        int sortearQuantidade(int minimo, int maximo);
        bool jogadorChegouNaPassagem() const;
        void controladorEstado(int idFase);
        int verificarQuantidadeInimigos();

    public:
        Fase(
            Entidades::Personagens::Jogador* jg1,
            Entidades::Personagens::Jogador* jg2,
            bool carregaArquivo
        );

        virtual ~Fase();

        virtual void executar() = 0;

        void salvar();
        void carregarSalvamento();
        virtual void carregamentoPadrao();

        int getPontuacaoTotal() const;
    };
}