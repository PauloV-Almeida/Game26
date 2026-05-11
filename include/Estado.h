#pragma once

namespace Gerenciadores
{
	class GerenciadorEstado;
}

namespace Estados
{
	class Estado
	{
	protected:
		static Gerenciadores::GerenciadorEstado* pEG;
		const int id_estado;
	public:
		Estado(int id = -1);

		virtual ~Estado();

		void setGerenciadorEstado(Gerenciadores::GerenciadorEstado* p);

		int getId() const;

		const bool get_ativo();

		virtual void executar() = 0;
		virtual void reiniciar() {};
	};
}