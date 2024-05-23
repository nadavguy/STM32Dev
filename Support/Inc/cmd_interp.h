#ifndef __CMD_INTERP_H__
#define __CMD_INTERP_H__
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <stdbool.h>

#define CI_MAX_PARAMETERS (5)
//-----------------------------------------------------------------------------

// Command interpreter results
typedef enum eCI_RESULT
{
  CI_OK = 0, // Command execution ok
  CI_COMMAND_ERROR, // Unknown command
  CI_PARAMETER_ERROR, // Invalid parameter
  CI_FUNCTION_ERROR, // Function error
  CI_MEMORY_ERROR, // Memory error
  CI_PERIPHERAL_ERROR, // Peripheral error
  CI_CHECKSUM_ERROR, // Invalid checksum
  CI_NO_UART_ACK // No UART acknowledge
} eCI_RESULT;

// Parameter types
typedef enum eCI_PARAM_TYPE
{
  CI_INT = 0, // Integer type
  CI_FLOAT, // Float type
  CI_STRING, // String type
  CI_UNKNOWN // Unknown type
} eCI_PARAM_TYPE;
//-----------------------------------------------------------------------------

// Command function pointer
typedef eCI_RESULT (*s32FUNCvoid)(void);

// Structure of a parameter item
typedef struct sCI_PARAM_ITEM
{
  float f; // Parameter of type float
  int32_t i; // Parameter of type integer
  char* s; // Parameter of type string
  eCI_PARAM_TYPE t; // Parameter type
} tCI_PARAM_ITEM;

// Structure of a command table item
typedef struct sCI_ITEM
{
  uint32_t ascii_image; // ASCII code of command string
  bool visible; // Flag if item is visible
  eCI_RESULT (*pFUNC)(void); // Pointer to command function
  const char* help_text; // Pointer to help text
} tCI_ITEM;

// Table and table-pointer typedefs
typedef tCI_ITEM* pCI_TABLE;
//-----------------------------------------------------------------------------

// Command table must be defined by the application
extern const tCI_ITEM CI_TABLE[];
//-----------------------------------------------------------------------------

// Class Command Interpreter
typedef struct
{
  uint8_t param_index; // Index of parameter in process
  uint8_t param_count; // Number of evaluated parameters
  uint8_t param_error; // Parameter error code (> 0 = index of bad parameter)
  bool param_hex_mode; // Flag for hexadecimal parameter input

  tCI_PARAM_ITEM params[CI_MAX_PARAMETERS]; // Parameter array
//  pCI_TABLE cmd_table; // Command table pointer
} cCMD_INTERP;


//UART / USB channel
typedef struct
{
		uint32_t numberOfChars;
		char lastChar;
		uint8_t channelArray[2048];
		bool receivedCR;
}tDATACHANNEL;

extern void init_params(void); // Initialization of parameter array
extern char* eval_params(char* s, uint8_t param_index); // Process line parameters
extern uint16_t get_hash(const char* s); // Calculate hash code of line command


  // // Constructor
  // cCMD_INTERP(void)
  // {
  //   pCI_TABLE cmd_table = (pCI_TABLE)&CI_TABLE; // Validate table pointer
  //   bool param_hex_mode = false; // Clear flag for hexadecimal parameter input
  // }
  //---------------------------------------------------------------------------

  // Parse an input line and execute command if present, return eCI_RESULT
extern uint32_t parse(char* s);

  // Display parser result
extern void disp_result(eCI_RESULT r);

  // Display command table help
extern void disp_help(void);

  // Set command table pointer
extern void set_table(pCI_TABLE tbl);

  // Get command table pointer
extern pCI_TABLE get_table(void);

  // Set or clear the flag for hexadecimal parameter input
extern void set_param_hex_mode(bool value);

  // Get the number of evaluated parameters
extern uint32_t get_param_count(void);

  // Get parameter error index (0 = no error, > 0 = parameter index + 1
extern uint8_t get_param_error(void);

  // Get integer parameter
extern int32_t get_param_int(uint8_t index);

  // Get float parameter
extern float get_param_float(uint8_t index);

  // Get string parameter
extern char* get_param_str(uint8_t index);

//-----------------------------------------------------------------------------

// Global instance of command interpreter class
extern cCMD_INTERP g_ci;

#endif
