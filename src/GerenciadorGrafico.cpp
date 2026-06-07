#include "../include/GerenciadorGrafico.h"
#include "../include/Ente.h"


namespace Gerenciadores
{
	GerenciadorGrafico* GerenciadorGrafico::instance = nullptr;


	GerenciadorGrafico* GerenciadorGrafico::get_instance() {
		if (instance == nullptr) {
			instance = new GerenciadorGrafico();
		}
		return instance;
	}

	GerenciadorGrafico::GerenciadorGrafico() :
		janLargura(LARGURA_JANELA),
		janAltura(ALTURA_JANELA),
		padraoView(sf::FloatRect(0.f, 0.f, janLargura, janAltura))
	{
		janela = new sf::RenderWindow(sf::VideoMode(janLargura, janAltura), "Ragnarok++", sf::Style::Close | sf::Style::Titlebar);
		font = new sf::Font();
		carregarTexturas();
	
	}

	GerenciadorGrafico::~GerenciadorGrafico()
	{
		if (janela)
			delete janela;
		if (font)
			delete font;
	}

	void GerenciadorGrafico::mostrar() {
		janela->display();
	}

	void GerenciadorGrafico::carregarTexturas()
	{
		carregarTexturaInimigos();
		carregarTexturaCenario();
		//carregarProjeteis();
		carregarTexturaJogador();
		carregarFundo();	
	}
	
	void GerenciadorGrafico::carregarTexturaInimigos()
	{
		sf::Texture tempText;
		try {
			if (!tempText.loadFromFile("../texturas/valkiria.PNG")) {
				throw std::exception("Falha ao carregar textura Valkiria.PNG");
			}
			mapTexturas.insert({ Texturas::valkiria, tempText });

			if (!tempText.loadFromFile("../texturas/andarilho.PNG")) {
				throw std::exception("Falha ao carregar textura andarilho.PNG");
			}
			mapTexturas.insert({ Texturas::andarilho, tempText });

			if (!tempText.loadFromFile("../texturas/boss.PNG")) {
				throw std::exception("Falha ao carregar textura boss.PNG");
			}
			mapTexturas.insert({ Texturas::thor, tempText });

		}
		catch (const std::exception& e) {
			std::cerr << "Exceção capturada durante o carregamento das texturas dos inimigos: \n" << e.what() << "\n";
			exit(1);
		}
	}

	void GerenciadorGrafico::carregarTexturaCenario()
	{
		sf::Texture tempText;
		try {
			if (!tempText.loadFromFile("../texturas/espinho_venenoso.PNG")) {
				throw std::exception("Falha ao carregar textura espinho_venenoso.PNG");
			}
			mapTexturas.insert({ Texturas::espinho, tempText });

			if (!tempText.loadFromFile("../texturas/arvore.PNG")) {
				throw std::exception("Falha ao carregar textura arvore.PNG");
			}
			mapTexturas.insert({ Texturas::parede, tempText });

			if (!tempText.loadFromFile("../texturas/tileset_32x32.PNG")) {
				throw std::exception("Falha ao carregar textura tileset_32x32.PNG");
			}
			mapTexturas.insert({ Texturas::chao, tempText });

		}
		catch (const std::exception& e) {
			std::cerr << "Exceção capturada durante o carregamento das texturas do cenário:\n " << e.what() << "\n";
			exit(1);
		}
	}

	/*void GerenciadorGrafico::carregarProjeteis()
	{
		sf::Texture tempText;
		try {
			if (!tempText.loadFromFile("..//textures//fireball.PNG")) {
				throw std::exception("Falha ao carregar textura fireball.PNG");
			}
			mapTexturas.insert({ Texturas::fireball, tempText });

			if (!tempText.loadFromFile("..//textures//orb.PNG")) {

				throw std::exception("Falha ao carregar textura orb");
			}
			mapTexturas.insert({ Texturas::projetil, tempText });
		}
		catch (const std::exception& e) {
			std::cerr << "Exceção capturada durante o carregamento das texturas dos projeteis:\n " << e.what() << "\n";
			exit(1);
		}

	}*/

	void GerenciadorGrafico::carregarFundo()
	{
		sf::Texture tempText;
		try {
			if (!font->loadFromFile(FONTE_PATH)) {
				throw std::exception("Erro ao carregar a fonte");
			}
			if (!fundo1.loadFromFile(("../Fundo/Floresta_Gelo.PNG"))) {
				throw std::exception("Falha ao carregar textura Floresta_Gelo");
			}
			fundoSprite1.setTexture(fundo1);
			fundoSprite1.setScale(4, 4);

			if (!fundo2.loadFromFile(("../Fundo/Arena_Gelo.PNG"))) {
				throw std::exception("Falha ao carregar textura Arena_Gelo");
			}
			fundoSprite2.setTexture(fundo2);
			fundoSprite2.setScale(4, 4);

			if (!tempText.loadFromFile("../Fundo/imgMenu.PNG")) {
				std::cout << "Falha ao carregar imgMenu.png";
			}
			mapTexturas.insert({ Texturas::fundoMenu, tempText });
		}
		catch (const std::exception& e) {
			std::cerr << "Exceção capturada durante o carregamento das texturas de background: " << e.what() << "\n";
			exit(1);
		}
	}

	void GerenciadorGrafico::carregarTexturaJogador()
	{
		sf::Texture tempText;
		try {
			if (!tempText.loadFromFile("../texturas/jogador1.PNG")) {
				throw std::exception("Falha ao carregar textura jogador1.PNG");
			}
			mapTexturas.insert({ Texturas::jogador, tempText });
			sf::Image playerInvertido;
			if (!playerInvertido.loadFromFile("../texturas/jogador1.PNG")) {
				throw std::exception("Falha ao carregar textura jogador1.PNG");
			}
			playerInvertido.flipHorizontally();
			if (!tempText.loadFromImage(playerInvertido)) {
				throw std::exception("Falha ao inverter imagem do jogador");
			}
			mapTexturas.insert({ Texturas::jogadorEsq, tempText });
		}
		catch (const std::exception& e) {
			std::cerr << "Exceção capturada durante o carregamento das texturas do jogador:\n " << e.what() << "\n";
			exit(1);
		}

	}

	void GerenciadorGrafico::desenharFundo()
	{
		janela->draw(fundoSprite1);
		janela->draw(fundoSprite2);
	}

	void GerenciadorGrafico::desenharEnte(Ente* ente)
	{
		if (janela && ente && ente->getFigura())
		{
			janela->draw(*ente->getFigura());
		}
	}

	bool GerenciadorGrafico::estaAberto()
	{
		return janela->isOpen();
	}

	sf::RenderWindow* GerenciadorGrafico::get_janela()
	{
		return janela;
	}

	sf::Texture* GerenciadorGrafico::getTextura(Texturas idText)
	{
		return &mapTexturas.at(idText);
	}

	void GerenciadorGrafico::limpar() {
		janela->clear();
	}

	const sf::FloatRect GerenciadorGrafico::getPadraoView()
	{
		return padraoView;
	}

	sf::Font* GerenciadorGrafico::getFont()
	{
		return font;
	}

	void GerenciadorGrafico::setFrameLimit(int fps)
	{
		janela->setFramerateLimit(fps);
	}

	void GerenciadorGrafico::fechar()
	{
		janela->close();
	}

	void GerenciadorGrafico::setView(sf::View view)
	{
		janela->setView(view);
	}
}