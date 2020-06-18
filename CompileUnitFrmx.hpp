#pragma once

#include "pch.h"


using namespace std;

namespace Sodium {

	extern class SodiumCompiler;
	
	class CompileUnitFrmx : CompileUnitBase {

		
	public:
		CompileUnitFrmx(SodiumCompiler* compiler);

		~CompileUnitFrmx();

		BOOL	Parse();

		friend class SodiumCompiler;
	};

}
