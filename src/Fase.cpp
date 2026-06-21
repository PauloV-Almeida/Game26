#include "../include/Fase.h"

#include <vector>

namespace Fases
{
    Fase::Fase(
        Entidades::Personagens::Jogador* jogador1,
        Entidades::Personagens::Jogador* jogador2,
        bool carregaArquivo
    ) :
        State(),
        jogador1(jogador1),
        jogador2(jogador2),
        jogador2Ativo(false),
        view(pGG->getPadraoView()),
        areaPassagem(),
        possuiPassagem(false),
        caminhoMapa("assets/mapaFloGelo.txt")
    {
        mediador = mediadorEventos::getMediadorEventos();
        pontuacaoTotal = 0;
        id = 0;

        Entidades::Personagens::Inimigo::setJogador2Global(jogador2);

        if (jogador1)
        {
            gC.incluirJogador1(jogador1);
            listaEntidades.inserirNoFim(jogador1);
            hub.setPlayer(jogador1);
        }

        if (jogador2)
        {
            jogador2->setAtivo(false);
        }

        pGG->setView(view);
    }

    Fase::~Fase()
    {
        listaEntidades.desalocar();
    }

    int Fase::sortearQuantidade(int minimo, int maximo)
    {
        return minimo + rand() % (maximo - minimo + 1);
    }

    void Fase::lidarEvent()
    {
        if (jogador1 && jogador1->ativado())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                jogador1->movimentar(Direcao::LEFT);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                jogador1->movimentar(Direcao::RIGHT);
            }
            else
            {
                jogador1->pararEixoX();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                jogador1->atacar();
            }
        }

        if (jogador2Ativo && jogador2 && jogador2->ativado())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                jogador2->movimentar(Direcao::LEFT);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                jogador2->movimentar(Direcao::RIGHT);
            }
            else
            {
                jogador2->pararEixoX();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                jogador2->atacar();
            }
        }

        sf::Event ev;

        while (pGG->get_janela()->pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
            {
                pGG->fechar();
                break;
            }

            case sf::Event::KeyPressed:
            {
                if (ev.key.code == sf::Keyboard::W)
                {
                    if (jogador1 && jogador1->ativado())
                    {
                        jogador1->movimentar(Direcao::UP);
                    }
                }

                if (ev.key.code == sf::Keyboard::Up)
                {
                    if (jogador2Ativo && jogador2 && jogador2->ativado())
                    {
                        jogador2->movimentar(Direcao::UP);
                    }
                }

                if (ev.key.code == sf::Keyboard::J)
                {
                    if (jogador2 && !jogador2Ativo)
                    {
                        jogador2->setAtivo(true);

                        Entidades::Personagens::Inimigo::setJogador2Global(jogador2);

                        hub.setPlayer2(jogador2);
                        jogador2Ativo = true;

                        listaEntidades.inserirNoFim(jogador2);
                        gC.incluirJogador2(jogador2);
                    }
                }

                if (ev.key.code == sf::Keyboard::Escape)
                {
                    mediador->notify(Actions::PAUSE);
                }

                break;
            }

            default:
            {
                break;
            }
            }
        }
    }

    void Fase::executarJanela()
    {
        bool jogador1Vivo = jogador1 && jogador1->ativado() && jogador1->vivo();
        bool jogador2Vivo = jogador2Ativo && jogador2 && jogador2->ativado() && jogador2->vivo();

        if (jogador1Vivo && jogador2Vivo)
        {
            sf::Vector2f centro;
            centro.x = (jogador1->getCentro().x + jogador2->getCentro().x) / 2.f;
            centro.y = (jogador1->getCentro().y + jogador2->getCentro().y) / 2.f;

            view.setCenter(centro);
        }
        else if (jogador1Vivo)
        {
            view.setCenter(jogador1->getCentro());
        }
        else if (jogador2Vivo)
        {
            view.setCenter(jogador2->getCentro());
        }

        pGG->limpar();
        pGG->setView(view);
        pGG->desenharFundo(id);
    }

    int Fase::getPontuacaoTotal() const
    {
        int total = 0;

        if (jogador1)
        {
            total += jogador1->getPontos();
        }

        if (jogador2)
        {
            total += jogador2->getPontos();
        }

        return total;
    }

    void Fase::carregarSalvamento()
    {
        hub.setPlayer(jogador1);
        pGG->setView(view);

     
        possuiPassagem = false;
        areaPassagem = sf::FloatRect();

        {
            std::ifstream arquivoMapa(caminhoMapa);
            std::string linhaMapa;

            int y = 0;

            while (std::getline(arquivoMapa, linhaMapa))
            {
                std::istringstream entradaMapa(linhaMapa);

                int tile;
                int x = 0;

                while (entradaMapa >> tile)
                {
                    if (tile == 9)
                    {
                        float posX = TAM_TILE * x;
                        float posY = TAM_TILE * y;

                        sf::FloatRect novaArea(posX, posY, TAM_TILE, TAM_TILE);

                        if (!possuiPassagem)
                        {
                            areaPassagem = novaArea;
                            possuiPassagem = true;
                        }
                        else
                        {
                            float esquerda = areaPassagem.left < novaArea.left
                                ? areaPassagem.left
                                : novaArea.left;

                            float topo = areaPassagem.top < novaArea.top
                                ? areaPassagem.top
                                : novaArea.top;

                            float direitaAtual = areaPassagem.left + areaPassagem.width;
                            float direitaNova = novaArea.left + novaArea.width;

                            float direita = direitaAtual > direitaNova
                                ? direitaAtual
                                : direitaNova;

                            float baixoAtual = areaPassagem.top + areaPassagem.height;
                            float baixoNovo = novaArea.top + novaArea.height;

                            float baixo = baixoAtual > baixoNovo
                                ? baixoAtual
                                : baixoNovo;

                            areaPassagem = sf::FloatRect(
                                esquerda,
                                topo,
                                direita - esquerda,
                                baixo - topo
                            );
                        }
                    }

                    x++;
                }

                y++;
            }

            arquivoMapa.close();
        }

        std::ifstream arquivo("salvar/salvar.txt");
        std::string linha;

        if (!arquivo.is_open())
        {
            return;
        }

      
        std::unordered_map<int, Entidades::Projetil*> projeteisSalvos;
        std::vector<std::pair<Entidades::Personagens::Thor*, int>> thorsAguardandoProjetil;

      
        std::getline(arquivo, linha);

        if (std::getline(arquivo, linha))
        {
            std::istringstream entradaJogador2(linha);
            entradaJogador2 >> jogador2Ativo;
        }

        while (std::getline(arquivo, linha))
        {
            if (linha.empty())
            {
                continue;
            }

            std::istringstream entrada(linha);

            std::string tipoEntidade;

            int idEntidade = -1;
            int ativo = 0;

            float posicaoX = 0.f;
            float posicaoY = 0.f;
            float velocidadeX = 0.f;
            float velocidadeY = 0.f;

            entrada >> tipoEntidade;

            if (tipoEntidade.empty())
            {
                continue;
            }

            entrada >> idEntidade;
            entrada >> ativo;
            entrada >> posicaoX;
            entrada >> posicaoY;
            entrada >> velocidadeX;
            entrada >> velocidadeY;

            if (tipoEntidade == "JOGADOR")
            {
                int vida = 15;
                int pulosRestantes = 2;
                int pontos = 0;
                int jogadorDoisSalvo = 0;

             
                entrada >> vida;
                entrada >> pulosRestantes;
                entrada >> pontos;
                entrada >> jogadorDoisSalvo;

                Entidades::Personagens::Jogador* jogador = nullptr;

                if (jogadorDoisSalvo)
                {
                    jogador = jogador2;
                }
                else
                {
                    jogador = jogador1;
                }

                if (jogador)
                {
                    jogador->setIdUnico(idEntidade);
                    jogador->setAtivo(ativo != 0);
                    jogador->setPosicao(posicaoX, posicaoY);
                    jogador->setVelocidade(velocidadeX, velocidadeY);
                    jogador->setNumVida(vida);
                    jogador->setPulos(pulosRestantes);
                    jogador->setPontuacao(pontos);
                    jogador->setTravado(false);
                    jogador->setJogadorDois(jogadorDoisSalvo != 0);
                }
            }
            else if (tipoEntidade == "ANDARILHO")
            {
                int vida = 5;
                int pulosRestantes = 2;
                int nivelMaldade = 1;
                int forca = 1;

              
                entrada >> vida;
                entrada >> pulosRestantes;
                entrada >> nivelMaldade;
                entrada >> forca;

                Entidades::Personagens::Andarilho* andarilho =
                    new Entidades::Personagens::Andarilho(
                        sf::Vector2f(posicaoX, posicaoY),
                        jogador1
                    );

                andarilho->setIdUnico(idEntidade);
                andarilho->setNumVida(vida);
                andarilho->setPulos(pulosRestantes);
                andarilho->setNivelMaldade(nivelMaldade);
                andarilho->setVelocidade(velocidadeX, velocidadeY);
                andarilho->setAtivo(ativo != 0);

                listaEntidades.inserirNoFim(andarilho);
                gC.incluirInimigo(andarilho);
            }
            else if (tipoEntidade == "VALKIRIA")
            {
                int vida = 5;
                int pulosRestantes = 2;
                int nivelMaldade = 1;
                float empurrar = 4.f;

                entrada >> vida;
                entrada >> pulosRestantes;
                entrada >> nivelMaldade;
                entrada >> empurrar;

                Entidades::Personagens::Valkiria* valkiria =
                    new Entidades::Personagens::Valkiria(
                        sf::Vector2f(posicaoX, posicaoY),
                        jogador1
                    );

                valkiria->setIdUnico(idEntidade);
                valkiria->setNumVida(vida);
                valkiria->setPulos(pulosRestantes);
                valkiria->setNivelMaldade(nivelMaldade);
                valkiria->setVelocidade(velocidadeX, velocidadeY);
                valkiria->setAtivo(ativo != 0);

                listaEntidades.inserirNoFim(valkiria);
                gC.incluirInimigo(valkiria);
            }
            else if (tipoEntidade == "THOR")
            {
                int vida = 20;
                int pulosRestantes = 2;
                int nivelMaldade = 1;
                int forca = 3;
                int idProjetilSalvo = -1;

              
                entrada >> vida;
                entrada >> pulosRestantes;
                entrada >> nivelMaldade;
                entrada >> forca;
                entrada >> idProjetilSalvo;

            
                Entidades::Personagens::Thor* thor =
                    new Entidades::Personagens::Thor(
                        sf::Vector2f(posicaoX, posicaoY),
                        jogador1,
                        nullptr
                    );

                thor->setIdUnico(idEntidade);
                thor->setNumVida(vida);
                thor->setPulos(pulosRestantes);
                thor->setNivelMaldade(nivelMaldade);
                thor->setVelocidade(velocidadeX, velocidadeY);
                thor->setAtivo(ativo != 0);

                listaEntidades.inserirNoFim(thor);
                gC.incluirInimigo(thor);

                thorsAguardandoProjetil.push_back(
                    std::make_pair(thor, idProjetilSalvo)
                );
            }
            else if (tipoEntidade == "PROJETIL")
            {
                int dano = 2;
                int velocidadeInicial = 6;
                float alvoX = 0.f;
                float alvoY = 0.f;
                int lancado = 0;

                entrada >> dano;
                entrada >> velocidadeInicial;
                entrada >> alvoX;
                entrada >> alvoY;
                entrada >> lancado;

                Entidades::Projetil* projetil =
                    new Entidades::Projetil(sf::Vector2f(posicaoX, posicaoY));

                projetil->setIdUnico(idEntidade);
                projetil->setAtivo(ativo != 0);
                projetil->setVelocidade(velocidadeX, velocidadeY);
                projetil->setDano(dano);
                projetil->setVelocidadeInicial(velocidadeInicial);
                projetil->setPosicaoAlvo(sf::Vector2f(alvoX, alvoY));
                projetil->setLancado(lancado != 0);

                listaEntidades.inserirNoFim(projetil);
                gC.incluirProjetil(projetil);

                projeteisSalvos[idEntidade] = projetil;
            }
            else if (tipoEntidade == "PLATAFORMA")
            {
                int danoso = 0;
                int colidivel = 1;
                float empuxo = 0.f;
                float aceleracaoGelo = 0.f;
                float velocidadeMaximaGelo = 0.f;
                float empuxoDuplicado = 0.f;

                
                entrada >> danoso;
                entrada >> colidivel;
                entrada >> empuxo;
                entrada >> aceleracaoGelo;
                entrada >> velocidadeMaximaGelo;
                entrada >> empuxoDuplicado;

                Entidades::Obstaculos::Plataforma* plataforma =
                    new Entidades::Obstaculos::Plataforma(
                        sf::Vector2f(posicaoX, posicaoY),
                        sf::Vector2f(TAM_TILE, TAM_TILE)
                    );

                plataforma->setIdUnico(idEntidade);
                plataforma->setVelocidade(velocidadeX, velocidadeY);
                plataforma->setAtivo(ativo != 0);
                plataforma->setDanoso(danoso != 0);
                plataforma->setColidivel(colidivel != 0);

                listaEntidades.inserirNoFim(plataforma);
                gC.incluirObstaculo(plataforma);
            }
            else if (tipoEntidade == "ESPINHO")
            {
                int danoso = 1;
                int colidivel = 1;
                float empuxo = 0.f;
                int dano = 1;
                float intervaloDano = 1.f;

               
                entrada >> danoso;
                entrada >> colidivel;
                entrada >> empuxo;
                entrada >> dano;
                entrada >> intervaloDano;

                Entidades::Obstaculos::EspinhoVenenoso* espinho =
                    new Entidades::Obstaculos::EspinhoVenenoso(
                        sf::Vector2f(posicaoX, posicaoY),
                        sf::Vector2f(TAM_TILE, TAM_TILE)
                    );

                espinho->setIdUnico(idEntidade);
                espinho->setVelocidade(velocidadeX, velocidadeY);
                espinho->setAtivo(ativo != 0);
                espinho->setDanoso(danoso != 0);
                espinho->setColidivel(colidivel != 0);

                listaEntidades.inserirNoFim(espinho);
                gC.incluirObstaculo(espinho);
            }
            else if (tipoEntidade == "RUNA")
            {
                int danoso = 0;
                int colidivel = 1;
                float empuxo = 0.f;
                float tempoTravamento = 2.f;
                int travandoJogador = 0;
                int jaAtivada = 0;
                int idJogadorTravado = -1;

                
                entrada >> danoso;
                entrada >> colidivel;
                entrada >> empuxo;
                entrada >> tempoTravamento;
                entrada >> travandoJogador;
                entrada >> jaAtivada;
                entrada >> idJogadorTravado;

                Entidades::Obstaculos::Runa* runa =
                    new Entidades::Obstaculos::Runa(
                        sf::Vector2f(posicaoX, posicaoY),
                        sf::Vector2f(TAM_TILE, TAM_TILE)
                    );

                runa->setIdUnico(idEntidade);
                runa->setVelocidade(velocidadeX, velocidadeY);
                runa->setAtivo(ativo != 0);
                runa->setDanoso(danoso != 0);
                runa->setColidivel(colidivel != 0);

                listaEntidades.inserirNoFim(runa);
                gC.incluirObstaculo(runa);
            }
            else if (tipoEntidade == "ESTRUTURA")
            {
                std::string tipoEstruturaTexto;
                entrada >> tipoEstruturaTexto;

                TipoEstrutura tipoEstrutura = TipoEstrutura::CHAO;

                if (tipoEstruturaTexto == "PAREDE")
                {
                    tipoEstrutura = TipoEstrutura::PAREDE;
                }
                else if (tipoEstruturaTexto == "NULO")
                {
                    tipoEstrutura = TipoEstrutura::NULO;
                }

                Entidades::Estrutura* estrutura =
                    new Entidades::Estrutura(
                        sf::Vector2f(posicaoX, posicaoY),
                        tipoEstrutura,
                        sf::Vector2f(TAM_TILE, TAM_TILE)
                    );

                estrutura->setIdUnico(idEntidade);
                estrutura->setVelocidade(velocidadeX, velocidadeY);
                estrutura->setAtivo(ativo != 0);

                listaEntidades.inserirNoFim(estrutura);
                gC.incluirEstrutura(estrutura);
            }
        }

       
        for (auto& par : thorsAguardandoProjetil)
        {
            Entidades::Personagens::Thor* thor = par.first;
            int idProjetil = par.second;

            Entidades::Projetil* projetil = nullptr;

            auto it = projeteisSalvos.find(idProjetil);

            if (it != projeteisSalvos.end())
            {
                projetil = it->second;
            }
            else
            {
                
                projetil = new Entidades::Projetil();
                projetil->setAtivo(false);

                listaEntidades.inserirNoFim(projetil);
                gC.incluirProjetil(projetil);
            }

            if (thor)
            {
                thor->setProjetil(projetil);
            }
        }

        arquivo.close();

        hub.setPlayer(jogador1);

        if (jogador2Ativo && jogador2)
        {
            jogador2->setAtivo(true);

            listaEntidades.inserirNoFim(jogador2);
            gC.incluirJogador2(jogador2);
            hub.setPlayer2(jogador2);

            Entidades::Personagens::Inimigo::setJogador2Global(jogador2);
        }
    }

    void Fase::carregamentoPadrao()
    {
        criarInimigos();
        criarObstaculo();
    }

    void Fase::criarAndarilhos()
    {
        std::ifstream arquivo(caminhoMapa);
        std::string linha;

        if (!arquivo.is_open())
        {
            return;
        }

        std::vector<sf::Vector2f> posicoes;

        int y = 0;

        while (std::getline(arquivo, linha))
        {
            std::istringstream entrada(linha);

            int tile;
            int x = 0;

            while (entrada >> tile)
            {
                if (tile == 6)
                {
                    posicoes.push_back(
                        sf::Vector2f(TAM_TILE * x, TAM_TILE * y)
                    );
                }

                x++;
            }

            y++;
        }

        arquivo.close();

        if (posicoes.empty())
        {
            return;
        }

        int quantidade = sortearQuantidade(MIN, MAX);

        int criados = 0;

        while (!posicoes.empty() && criados < quantidade)
        {
            int indice = rand() % posicoes.size();

            Entidades::Personagens::Andarilho* andarilho =
                new Entidades::Personagens::Andarilho(
                    posicoes[indice],
                    jogador1
                );

            listaEntidades.inserirNoFim(andarilho);
            gC.incluirInimigo(andarilho);

            posicoes.erase(posicoes.begin() + indice);
            criados++;
        }
    }

    void Fase::criarPlataformas()
    {
        std::ifstream arquivo(caminhoMapa);
        std::string linha;

        if (!arquivo.is_open())
        {
            return;
        }

        std::vector<sf::Vector2f> posicoes;

        int y = 0;

        while (std::getline(arquivo, linha))
        {
            std::istringstream entrada(linha);

            int tile;
            int x = 0;

            while (entrada >> tile)
            {
                if (tile == 2)
                {
                    posicoes.push_back(
                        sf::Vector2f(TAM_TILE * x, TAM_TILE * y)
                    );
                }

                x++;
            }

            y++;
        }

        arquivo.close();

        if (posicoes.empty())
        {
            return;
        }

        int quantidade = sortearQuantidade(MIN, MAX);

        int criadas = 0;

        while (!posicoes.empty() && criadas < quantidade)
        {
            int indice = rand() % posicoes.size();

            Entidades::Obstaculos::Plataforma* plataforma =
                new Entidades::Obstaculos::Plataforma(
                    posicoes[indice],
                    sf::Vector2f(TAM_TILE, TAM_TILE)
                );

            listaEntidades.inserirNoFim(plataforma);
            gC.incluirObstaculo(plataforma);

            posicoes.erase(posicoes.begin() + indice);
            criadas++;
        }
    }

    bool Fase::jogadorChegouNaPassagem() const
    {
        if (!possuiPassagem)
        {
            return false;
        }

        if (jogador1 && jogador1->ativado())
        {
            if (jogador1->getLimites().intersects(areaPassagem))
            {
                return true;
            }
        }

        if (jogador2Ativo && jogador2 && jogador2->ativado())
        {
            if (jogador2->getLimites().intersects(areaPassagem))
            {
                return true;
            }
        }

        return false;
    }

    void Fase::controladorEstado(int idFase)
    {
        bool jogador1Morreu = jogador1 && !jogador1->vivo();
        bool jogador2Morreu = jogador2Ativo && jogador2 && !jogador2->vivo();

        if (jogador1Morreu && jogador1->ativado())
        {
            jogador1->setAtivo(false);
            jogador1->setVelocidade(0.f, 0.f);
        }

        if (jogador2Morreu && jogador2->ativado())
        {
            jogador2->setAtivo(false);
            jogador2->setVelocidade(0.f, 0.f);
        }

        if (!jogador2Ativo)
        {
            if (!jogador1 || !jogador1->ativado())
            {
                mediador->notify(Actions::GAME_OVER);
                return;
            }
        }
        else
        {
            bool jogador1Fora = !jogador1 || !jogador1->ativado();
            bool jogador2Fora = !jogador2 || !jogador2->ativado();

            if (jogador1Fora && jogador2Fora)
            {
                mediador->notify(Actions::GAME_OVER);
                return;
            }
        }

        if (idFase == 1)
        {
            if (jogadorChegouNaPassagem())
            {
                mediador->notify(Actions::PASSOU_DE_FASE);
                return;
            }
        }
        else if (idFase == 2)
        {
            if (verificarQuantidadeInimigos() == 0) {
                mediador->notify(Actions::GAME_OVER);
                return;
            }
        }
    }

    void Fase::salvar()
    {
        std::ofstream arquivo("salvar/salvar.txt");

        if (arquivo.is_open())
        {
            arquivo << id << std::endl;
            arquivo << jogador2Ativo << std::endl;
            arquivo.close();
        }

        listaEntidades.salvar();
    }

    void Fase::criarCenario()
    {
        std::ifstream arquivo(caminhoMapa);
        std::string linha;

        if (!arquivo.is_open())
        {
            return;
        }

        int y = 0;

        while (std::getline(arquivo, linha))
        {
            std::istringstream entrada(linha);

            int tile;
            int x = 0;

            while (entrada >> tile)
            {
                float posX = TAM_TILE * x;
                float posY = TAM_TILE * y;

                if (tile == 1)
                {
                    Entidades::Estrutura* estrutura =
                        new Entidades::Estrutura(
                            sf::Vector2f(posX, posY),
                            TipoEstrutura::CHAO,
                            sf::Vector2f(TAM_TILE, TAM_TILE)
                        );

                    listaEntidades.inserirNoFim(estrutura);
                    gC.incluirEstrutura(estrutura);
                }
                else if (tile == 3)
                {
                    if (jogador1)
                    {
                        jogador1->setPosicao(posX, posY);
                    }
                }
                else if (tile == 4)
                {
                    if (jogador2)
                    {
                        jogador2->setPosicao(posX, posY);
                    }
                }
                else if (tile == 9)
                {
                    sf::FloatRect novaArea(posX, posY, TAM_TILE, TAM_TILE);

                    if (!possuiPassagem)
                    {
                        areaPassagem = novaArea;
                        possuiPassagem = true;
                    }
                    else
                    {
                        float esquerda = areaPassagem.left < novaArea.left
                            ? areaPassagem.left
                            : novaArea.left;

                        float topo = areaPassagem.top < novaArea.top
                            ? areaPassagem.top
                            : novaArea.top;

                        float direitaAtual = areaPassagem.left + areaPassagem.width;
                        float direitaNova = novaArea.left + novaArea.width;

                        float direita = direitaAtual > direitaNova
                            ? direitaAtual
                            : direitaNova;

                        float baixoAtual = areaPassagem.top + areaPassagem.height;
                        float baixoNovo = novaArea.top + novaArea.height;

                        float baixo = baixoAtual > baixoNovo
                            ? baixoAtual
                            : baixoNovo;

                        areaPassagem = sf::FloatRect(
                            esquerda,
                            topo,
                            direita - esquerda,
                            baixo - topo
                        );
                    }
                }

                x++;
            }

            y++;
        }

        arquivo.close();
    }

    int Fase::verificarQuantidadeInimigos()
    {
        return gC.getQuantidadeInimigosAtivos();
    }
}