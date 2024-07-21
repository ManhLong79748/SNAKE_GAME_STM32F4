
#include"systick.h"

uint32_t * SYST_CTRL = (uint32_t *) (0xE000E010);
uint32_t * SYST_LOAD = (uint32_t *) (0xE000E014);
uint32_t * SYST_VAL  = (uint32_t *) (0xE000E018);

void systick_init(void)
{
	*SYST_CTRL = 0;
	*SYST_LOAD = 0x00FFFFFF;
	*SYST_VAL  = 0;
	*SYST_CTRL = 5;
}
void DelayMillis(void)
{
	*SYST_LOAD = 8000 - 1;
	*SYST_VAL  = 0;
	while((*SYST_CTRL & 0x00010000)  == 0);
}
void DelayMs(unsigned long t)
{
	for ( ; t>0; t--)
	{
		DelayMillis();
	}
}
