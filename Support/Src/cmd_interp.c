// Module..: CMD_INTERP.CPP
// Chip....: STM32F40x
//-----------------------------------------------------------------------------

// Global instance of command interpreter class

#include "main.h"
#include "ci_func.h"
#include "str_util.h"

cCMD_INTERP g_ci;

char CommandsArray[5] = "";
char* sp;
uint8_t cmd_str_len = 0;
uint32_t ascii_image = 0;

void init_params(void)
{
  for (g_ci.param_count = 0; g_ci.param_count < CI_MAX_PARAMETERS; g_ci.param_count++)
  {
    g_ci.params[g_ci.param_count].f = 0.0f;
    g_ci.params[g_ci.param_count].i = 0;
    g_ci.params[g_ci.param_count].t = CI_UNKNOWN;
  }

  g_ci.param_error = 0;
  g_ci.param_count = 0;
}
//-----------------------------------------------------------------------------

void set_table(pCI_TABLE tbl)
{
//  g_ci.cmd_table = (pCI_TABLE)tbl;
}
//-----------------------------------------------------------------------------

void set_param_hex_mode(bool value)
{
  g_ci.param_hex_mode = value;
}
//-----------------------------------------------------------------------------

uint32_t get_param_count(void)
{
  return (g_ci.param_count);
}
//-----------------------------------------------------------------------------

uint8_t get_param_error(void)
{
  return (g_ci.param_error);
}
//-----------------------------------------------------------------------------

int32_t get_param_int(uint8_t index)
{
  if (index < CI_MAX_PARAMETERS)
  {
    return (g_ci.params[index].i);
  }
  else
  {
    return (g_ci.params[0].i);
  }
}
//-----------------------------------------------------------------------------

float get_param_float(uint8_t index)
{
  if (index < CI_MAX_PARAMETERS)
  {
    return (g_ci.params[index].f);
  }
  else
  {
    return (g_ci.params[0].f);
  }
}
//-----------------------------------------------------------------------------

char* get_param_str(uint8_t index)
{
  if (index < CI_MAX_PARAMETERS)
  {
    return ((char*)g_ci.params[index].i);
  }
  else
  {
    return ((char*)g_ci.params[0].i);
  }
}
//-----------------------------------------------------------------------------

char* eval_params(char* s, uint8_t param_index)
{
  int32_t num;
  char* stmp = s;
  bool negative = false;
  unsigned char c;

  if (param_index >= CI_MAX_PARAMETERS)
  {
    return (s);
  }

  if (*s == '"')
  {
    g_ci.params[param_index].i = (int32_t)++s;

    g_ci.params[param_index].t = CI_STRING;

    while (*s > 0 && *s++ != '"')
    {
    }

    *(s - 1) = 0;

    return (s);
  }
  else if (isfloat(s))
  {
    g_ci.params[param_index].f = (float)atof(s);
    g_ci.params[param_index].i = (int32_t)g_ci.params[param_index].f;
    g_ci.params[param_index].t = CI_FLOAT;

    return (s);
  }

  s = stmp;

  if (*s == '-')
  {
    negative = true;
    s++;
  }

  for (num = 0; isdigit(c = *s); s++)
  {
    num = num * 10 + (c - '0');
  }

  if (c > 0 && c != ',' && c != ' ' && c != 0x0a)
  {
    g_ci.param_error = param_index + 1;
  }

  if (negative)
  {
    num = -num;
  }

  g_ci.params[param_index].i = num;

  g_ci.params[param_index].f = (float)num;

  g_ci.params[param_index].t = CI_INT;

  return (s);
}
//-----------------------------------------------------------------------------

uint32_t parse(char* s)
{
  ascii_image = 0;
  uint8_t n;
  cmd_str_len = 0;
  memset(CommandsArray, 0, 5);

  init_params();
  s = remove_CRLF((char*)s);
  s = skip_blanks((char*)s);

  sp = s;

  s = skip_chars(s);

  cmd_str_len = (uint8_t)(s - sp);

  *s++ = 0;

  if (cmd_str_len > 4)
  {
    cmd_str_len = 4;
  }

  sp += cmd_str_len - 1;

  for (n = cmd_str_len; n-1; n--)
  {
    ascii_image <<= 8;
    ascii_image += *sp--;
  }
  memcpy(CommandsArray,sp,cmd_str_len);
  ascii_image += *sp--;

  init_params();


  while (*s && g_ci.param_count < CI_MAX_PARAMETERS)
  {
    s = skip_blanks(s);

   if (*s != 0)
    {
      s = eval_params(s, g_ci.param_count++);

      s = skip_chars(s);
    }
  }
  uint8_t ret = funcTable(CommandsArray);
//  if (!ee_validate1())
//  {
//
//  }

  return ret;
}
//-----------------------------------------------------------------------------

void disp_help(void)
{
//  uint8_t cmd_index = 0;
//
//  while ((g_ci.cmd_table)[cmd_index].ascii_image > 0)
//  {
//    if ((g_ci.cmd_table)[cmd_index].visible)
//    {
//      // g_term.putstr((char*)(cmd_table)[cmd_index].help_text);
//      // g_term.putstr("\r\n");
//    }
//
//    cmd_index++;
//  }
}
