#pragma once

#include <iostream>

namespace Listas
{
    template<class TYPE>
    class Lista
    {
    public:
        Lista() :
            pPrimeiro(NULL),
            tamanho(0)
        {
        }
        ~Lista()
        {
            clear();
            pPrimeiro = NULL;
        }
        template <class TE>
        class Elemento
        {
        private:
            TE* data;
            Elemento<TE>* pProximo;
        public:
            Elemento() :data(NULL), pProximo(NULL)
            {
            }
            ~Elemento()
            {
                if (data)
                {
                    delete data;
                }
                data = NULL;
            }
            TE* get_data() {if(data) return data; }
            Elemento<TE>* get_Proximo() { return pProximo; }

            void set_data(TE* dt) { data = dt; }
            void set_Proximo(Elemento<TE>* prox) { pProximo = prox; }
        };
        template <class TE>
        class Iterator
        {
        private:
            Elemento<TE>* atual;
        public:
            Iterator(Elemento<TE>* c = nullptr) :
                atual(c) {
            }
            ~Iterator() {}

            Iterator& operator++()
            {
                atual = atual->prox;
                return *this;
            }
            Iterator& operator++(int)
            {
                atual = atual->get_Proximo();
                return *this;
            }
            bool operator==(const Elemento<TE>* outro) const
            {
                return atual == outro;
            }

            bool operator!=(const Elemento<TE>* outro) const
            {
                return !(atual == outro);
            }
            void operator=(const Elemento<TE>* outro)
            {
                atual = outro;
            }
            TE* operator*()
            {
                if(atual)
                 return atual->get_data();
            }
            const Elemento<TE>* get_atual() const { return atual; }
        };
    private:
        Elemento<TYPE>* pPrimeiro;
        int tamanho;
    public:
        Iterator<TYPE> get_Primeiro() { return Iterator<TYPE>(pPrimeiro); }
        void clear()
        {
            Elemento<TYPE>* aux = NULL;
            while (pPrimeiro)
            {
                aux = pPrimeiro;
                pPrimeiro = pPrimeiro->get_Proximo();
                if (aux)
                    delete aux;
            }
            tamanho = 0;
            //novo:
            pPrimeiro = nullptr;
        }
        const int get_Tamanho() const
        {
            return tamanho;
        }
        void empurrar(TYPE* elem)
        {
            if (!elem)
                return;
            Elemento<TYPE>* aux = new Elemento<TYPE>();
            if (aux)
            {
                aux->set_data(elem);
                aux->set_Proximo(pPrimeiro);
                pPrimeiro = aux;
                tamanho++;
            }
        }
    };
}
