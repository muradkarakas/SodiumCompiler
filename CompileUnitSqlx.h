#pragma once

#include "pch.h"


using namespace std;

namespace Sodium {

	extern class SodiumCompiler;

	class CompileUnitSqlx : CompileUnitBase {


	public:
		CompileUnitSqlx(SodiumCompiler* compiler);

		~CompileUnitSqlx();

		BOOL	Parse();

		friend class SodiumCompiler;
	};

}
