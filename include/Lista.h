#pragma once

#include <iostream>

namespace Listas
{
    template<class TL>
    class Lista
    {
    public:
        template<class TE>
        class Elemento
        {
        private:
            TE* pInfo;
            Elemento<TE>* pProx;

        public:
            Elemento() :
                pInfo(nullptr),
                pProx(nullptr)
            {}

            ~Elemento()
            {
                delete pInfo;
                pInfo = nullptr;
                pProx = nullptr;
            }

            void setInfo(TE* info)
            {
                pInfo = info;
            }

            TE* getInfo() const
            {
                return pInfo;
            }

            void setProx(Elemento<TE>* prox)
            {
                pProx = prox;
            }

            Elemento<TE>* getProx() const
            {
                return pProx;
            }
        };

        template<class TE>
        class Iterator
        {
        private:
            Elemento<TE>* atual;

        public:
            Iterator(Elemento<TE>* elemento = nullptr) :
                atual(elemento)
            {}

            ~Iterator()
            {
                atual = nullptr;
            }

            Iterator& operator++()
            {
                if (atual)
                {
                    atual = atual->getProx();
                }

                return *this;
            }

            Iterator operator++(int)
            {
                Iterator copia = *this;

                if (atual)
                {
                    atual = atual->getProx();
                }

                return copia;
            }

            bool operator==(const Iterator<TE>& outro) const
            {
                return atual == outro.atual;
            }

            bool operator!=(const Iterator<TE>& outro) const
            {
                return atual != outro.atual;
            }

            TE* operator*() const
            {
                if (atual)
                {
                    return atual->getInfo();
                }

                return nullptr;
            }

            Elemento<TE>* getAtual() const
            {
                return atual;
            }
        };

    private:
        Elemento<TL>* pPrimeiro;
        Elemento<TL>* pUltimo;
        int tamanho;

    public:
        Lista() :
            pPrimeiro(nullptr),
            pUltimo(nullptr),
            tamanho(0)
        {}

        ~Lista()
        {
            limpar();
        }

        Lista(const Lista&) = delete;
        Lista& operator=(const Lista&) = delete;

        void incluir(TL* info)
        {
            if (!info)
            {
                return;
            }

            Elemento<TL>* novo = new Elemento<TL>();

            novo->setInfo(info);
            novo->setProx(nullptr);

            if (pPrimeiro == nullptr)
            {
                pPrimeiro = novo;
                pUltimo = novo;
            }
            else
            {
                pUltimo->setProx(novo);
                pUltimo = novo;
            }

            tamanho++;
        }

        void limpar()
        {
            Elemento<TL>* aux = nullptr;

            while (pPrimeiro)
            {
                aux = pPrimeiro;
                pPrimeiro = pPrimeiro->getProx();

                delete aux;
            }

            pPrimeiro = nullptr;
            pUltimo = nullptr;
            tamanho = 0;
        }

        int getTamanho() const
        {
            return tamanho;
        }

        Iterator<TL> getPrimeiro()
        {
            return Iterator<TL>(pPrimeiro);
        }

        Iterator<TL> get_Primeiro()
        {
            return getPrimeiro();
        }

        Iterator<TL> getFim()
        {
            return Iterator<TL>(nullptr);
        }

        Iterator<TL> get_Fim()
        {
            return getFim();
        }

        TL* operator[](int indice)
        {
            if (indice < 0 || indice >= tamanho)
            {
                return nullptr;
            }

            Elemento<TL>* aux = pPrimeiro;
            int contador = 0;

            while (aux)
            {
                if (contador == indice)
                {
                    return aux->getInfo();
                }

                aux = aux->getProx();
                contador++;
            }

            return nullptr;
        }
    };
}