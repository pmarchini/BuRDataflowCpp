
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

extern DataFlow test;

void _INIT ProgramInit(void)
{

}

void _CYCLIC ProgramCyclic(void)
{
	
}

void _EXIT ProgramExit(void)
{
	test.O_Out = 1;
}

