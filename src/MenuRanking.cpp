#include "../include/MenuRanking.h"

MenuRanking::MenuRanking()
    :menuEstado()
{
    carregarBotoes();
    textoRanking.setPosition(300, 300);
    textoRanking.setFont(*(pGG->getFont()));
    textoRanking.setString("O RANKING SERÁ EXIBIDO AQUI");
    carregarRanking();
}

MenuRanking::~MenuRanking()
{

}

void MenuRanking::carregarBotoes()
{
    botaoVector.push_back(new Entidades::Button(sf::Vector2f(50.f, 100.f), "Voltar", Actions::VOLTAR_1_MENU));
}
void MenuRanking::executar() {
   
    pGG->limpar();
    pGG->updateMousePosition();
    setFigura(&fundoMenu);
    desenhar();
    handleEvent();
    execBotoes();
    setFigura(&textoRanking);
    desenhar();
}


void MenuRanking::carregarRanking()
{
    std::string linha;
    std::ifstream arquivo("ranking.txt");
    std::multimap<int, std::string> mapLeitura;

    if (arquivo.is_open()) {
        std::string nome;
        int pontos;
        while (std::getline(arquivo, linha)) {
            std::istringstream arquivoOutput(linha);
            if (arquivoOutput >> nome >> pontos) {
                mapLeitura.insert({ pontos, nome });
            }
        }
        arquivo.close();
    }

    std::vector<std::pair<int, std::string>> rankingsOrdenados;

    for (auto it = mapLeitura.rbegin(); it != mapLeitura.rend(); ++it) {
        rankingsOrdenados.push_back({ it->first, it->second });
    }
    std::stringstream texto("");
    int count = 0;

    for (const auto& rank : rankingsOrdenados) {
        if (count < 5) {
            texto << "Pontos: " << rank.first << " Nome: " << rank.second << "\n";
            count++;
        }
        else {
            break;
        }
    }
    textoRanking.setString(texto.str());
}