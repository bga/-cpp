#pragma once

#if __IAR_SYSTEMS_ICC__ <= 8
	//# IAR 8 does not support { override }
	#define override
	//# IAR 8 does not support { constexpr }
	#define MAYBE_CONSTEXPR
#endif
#define __asm__ asm
