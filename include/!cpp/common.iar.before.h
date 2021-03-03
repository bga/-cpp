#pragma once

#if __IAR_SYSTEMS_ICC__ <= 8
	//# IAR 8 does not support { override }
	#define override
#endif
#define __asm__ asm
