#include <stdint.h>
#include "cmd_interp.h"

extern bool isReportParametersActive;
extern bool isInfwUpdateMode;

extern eCI_RESULT func_debug(void);
extern eCI_RESULT func_versionReport(void);
extern eCI_RESULT func_reset(void);
extern eCI_RESULT func_showAvailableCommands(void);
extern eCI_RESULT func_systemConfiguration(void);

extern uint8_t funcTable( char* token );
