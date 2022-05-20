/* GNU m4 -- A simple macro processor
   Copyright (C) 1989, 90, 91, 92, 93, 94 Free Software Foundation, Inc.
  
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* Handling of different input sources, and lexical analysis.  */

#include "m4.h"

/* Unread input can be either files, that should be read (eg. included
   files), strings, which should be rescanned (eg. macro expansion text),
   or quoted macro definitions (as returned by the builtin "defn").
   Unread input are organised in a stack, implemented with an obstack.
   Each input source is described by a "struct input_block".  The obstack
   is "input_stack".  The top of the input stack is "isp".
   
   The macro "m4wrap" places the text to be saved on another input stack,
   on the obstack "wrapup_stack", whose top is "wsp".  When EOF is seen
   on normal input (eg, when "input_stack" is empty), input is switched
   over to "wrapup_stack".  To make this easier, all references to the
   current input stack, whether it be "input_stack" or "wrapup_stack",
   are done through a pointer "current_input", which points to either
   "input_stack" or "wrapup_stack".
   
   Pushing new input on the input stack is done by push_file (),
   push_string (), push_wrapup () (for wrapup text), and push_macro ()
   (for macro definitions).  Because macro expansion needs direct access
   to the current input obstack (for optimisation), push_string () are
   split in two functions, push_string_init (), which returns a pointer
   to the current input stack, and push_string_finish (), which return a
   pointer to the final text.  The input_block *next is used to manage
   the coordination between the different push routines.
   
   The current file and line number are stored in two global variables,
   for use by the error handling functions in m4.c.  Whenever a file
   input_block is pushed, the current file name and line number is saved
   in the input_block, and the two variables are reset to match the new
   input file.  */
 
#ifdef ENABLE_CHANGEWORD
#include "regex.h"
#endif

enum input_type
{
  INPUT_FILE,
  INPUT_STRING,
  INPUT_MACRO
};

typedef enum input_type input_type;

struct input_block
{
  struct input_block *prev;	/* previous input_block on the input stack */
  input_type type;		/* INPUT_FILE, INPUT_STRING or INPUT_MACRO */
  union
    {
      struct
	{
	  char *string;		/* string value */
	}
      u_s;
      struct
	{
	  FILE *file;		/* input file handle */
	  const char *name;	/* name of PREVIOUS input file */
	  int lineno;		/* current line number for do */
	  /* Yet another attack of "The curse of global variables" (sic) */
	  int out_lineno;	/* current output line number do */
	  boolean advance_line;	/* start_of_input_line from next_char () */
	}
      u_f;
      struct
	{
	  builtin_func *func;	/* pointer to macros function */
	  boolean traced;	/* TRUE iff builtin is traced */
	}
      u_m;
    }
  u;
};

typedef struct input_block input_block;


/* Current input file name.  */
const char *current_file;

/* Current input line number.  */
int current_line;

/* Obstack for storing individual tokens.  */
static struct obstack token_stack;

/* Normal input stack.  */
static struct obstack input_stack;

/* Wrapup input stack.  */
static struct obstack wrapup_stack;

/* Input or wrapup.  */
static struct obstack *current_input;

/* Bottom of token_stack, for obstack_free.  */
static char *token_bottom;

/* Pointer to top of current_input.  */
static input_block *isp;

/* Pointer to top of wrapup_stack.  */
static input_block *wsp;

/* Aux. for handling split push_string ().  */
static input_block *next;

/* Flag for next_char () to increment current_line.  */
static boolean start_of_input_line;

#define CHAR_EOF	256	/* character return on EOF */
#define CHAR_MACRO	257	/* character return for MACRO token */

/* Quote chars.  */
STRING rquote;
STRING lquote;

/* Comment chars.  */
STRING bcomm;
STRING ecomm;
 
#ifdef ENABLE_CHANGEWORD

#define DEFAULT_WORD_REGEXP "[_a-zA-Z][_a-zA-Z0-9]*"

static char *word_start;
static struct re_pattern_buffer word_regexp;
static int default_word_regexp;
static struct re_registers regs;

#endif /* ENABLE_CHANGEWORD */


/*-------------------------------------------------------------------------.
| push_file () pushes an input file on the input stack, saving the current |
| file name and line number.  If next is non-NULL, this push invalidates a |
| call to push_string_init (), whose storage are consequentely released.   |
`-------------------------------------------------------------------------*/

void
push_file (FILE *fp, const char *title)
{
  input_block *i;

  if (next != NULL)
    {
      obstack_free (current_input, next);
      next = NULL;
    }

  if (debug_level & DEBUG_TRACE_INPUT)
    DEBUG_MESSAGE1 ("input read from %s", title);

  i = (input_block *) obstack_alloc (current_input,
				     sizeof (struct input_block));
  i->type = INPUT_FILE;

  i->u.u_f.name = current_file;
  i->u.u_f.lineno = current_line;
  i->u.u_f.out_lineno = output_current_line;
  i->u.u_f.advance_line = start_of_input_line;
  current_file = obstack_copy0 (current_input, title, strlen (title));
  current_line = 1;
  output_current_line = -1;

  i->u.u_f.file = fp;
  i->prev = isp;
  isp = i;
}

/*-------------------------------------------------------------------------.
| push_macro () pushes a builtin macros definition on the input stack.  If |
| next is non-NULL, this push invalidates a call to push_string_init (),   |
| whose storage are consequentely released.				   |
`-------------------------------------------------------------------------*/

void
push_macro (builtin_func *func, boolean traced)
{
  input_block *i;

  if (next != NULL)
    {
      obstack_free (current_input, next);
      next = NULL;
    }

  i = (input_block *) obstack_alloc (current_input,
				     sizeof (struct input_block));
  i->type = INPUT_MACRO;

  i->u.u_m.func = func;
  i->u.u_m.traced = traced;
  i->prev = isp;
  isp = i;
}

/*------------------------------------------------------------------.
| First half of push_string ().  The pointer next points to the new |
| input_block.							    |
`------------------------------------------------------------------*/

struct obstack *
push_string_init (void)
{
  if (next != NULL)
    {
      M4ERROR ((warning_status, 0,
		"INTERNAL ERROR: Recursive push_string!"));
      abort ();
    }

  next = (input_block *) obstack_alloc (current_input,
				        sizeof (struct input_block));
  next->type = INPUT_STRING;
  return current_input;
}

/*------------------------------------------------------------------------.
| Last half of push_string ().  If next is now NULL, a call to push_file  |
| () has invalidated the previous call to push_string_init (), so we just |
| give up.  If the new object is void, we do not push it.  The function	  |
| push_string_finish () returns a pointer to the finished object.  This	  |
| pointer is only for temporary use, since reading the next token might	  |
| release the memory used for the object.				  |
`------------------------------------------------------------------------*/

const char *
push_string_finish (void)
{
  const char *ret = NULL;

  if (next == NULL)
    return NULL;

  if (obstack_object_size (current_input) > 0)
    {
      obstack_1grow (current_input, '\0');
      next->u.u_s.string = obstack_finish (current_input);
      next->prev = isp;
      isp = next;
      ret = isp->u.u_s.string;	/* for immediate use only */
    }
  else
    obstack_free (current_input, next); /* people might leave garbage on it. */
  next = NULL;
  return ret;
}

/*--------------------------------------------------------------------------.
| The function push_wrapup () pushes a string on the wrapup stack.  When    |
| he normal input stack gets empty, the wrapup stack will become the input  |
| stack, and push_string () and push_file () will operate on wrapup_stack.  |
| Push_wrapup should be done as push_string (), but this will suffice, as   |
| long as arguments to m4_m4wrap () are moderate in size.		    |
`--------------------------------------------------------------------------*/

void
push_wrapup (const char *s)
{
  input_block *i = (input_block *) obstack_alloc (&wrapup_stack,
						  sizeof (struct input_block));
  i->prev = wsp;
  i->type = INPUT_STRING;
  i->u.u_s.string = obstack_copy0 (&wrapup_stack, s, strlen (s));
  wsp = i;
}


/*-------------------------------------------------------------------------.
| The function pop_input () pops one level of input sources.  If the	   |
| popped input_block is a file, current_file and current_line are reset to |
| the saved values before the memory for the input_block are released.	   |
`-------------------------------------------------------------------------*/

static void
pop_input (void)
{
  input_block *tmp = isp->prev;

  switch (isp->type)
    {
    case INPUT_STRING:
    case INPUT_MACRO:
      break;

    case INPUT_FILE:
      if (debug_level & DEBUG_TRACE_INPUT)
	DEBUG_MESSAGE2 ("input reverted to %s, line %d",
			isp->u.u_f.name, isp->u.u_f.lineno);

      fclose (isp->u.u_f.file);
      current_file = isp->u.u_f.name;
      current_line = isp->u.u_f.lineno;
      output_current_line = isp->u.u_f.out_lineno;
      start_of_input_line = isp->u.u_f.advance_line;
      if (tmp != NULL)
	output_current_line = -1;
      break;

    default:
      M4ERROR ((warning_status, 0,
		"INTERNAL ERROR: Input stack botch in pop_input ()"));
      abort ();
    }
  obstack_free (current_input, isp);
  next = NULL;			/* might be set in push_string_init () */

  isp = tmp;
}

/*------------------------------------------------------------------------.
| To switch input over to the wrapup stack, main () calls pop_wrapup ().  |
| Since wrapup text can install new wrapup text, pop_wrapup () returns	  |
| FALSE when there is no wrapup text on the stack, and TRUE otherwise.	  |
`------------------------------------------------------------------------*/

boolean
pop_wrapup (void)
{
  if (wsp == NULL)
    return FALSE;

  current_input = &wrapup_stack;
  isp = wsp;
  wsp = NULL;

  return TRUE;
}

/*--------------------------------------------------------------------.
| When a MACRO token is seen, next_token () uses init_macro_token () to |
| retrieve the value of the function pointer.			      |
`--------------------------------------------------------------------*/

static void
init_macro_token (token_data *td)
{
  if (isp->type != INPUT_MACRO)
    {
      M4ERROR ((warning_status, 0,
		"INTERNAL ERROR: Bad call to init_macro_token ()"));
      abort ();
    }

  TOKEN_DATA_TYPE (td) = TOKEN_FUNC;
  TOKEN_DATA_FUNC (td) = isp->u.u_m.func;
  TOKEN_DATA_FUNC_TRACED (td) = isp->u.u_m.traced;
}


/*------------------------------------------------------------------------.
| Low level input is done a character at a time.  The function peek_input |
| () is used to look at the next character in the input stream.  At any	  |
| given time, it reads from the input_block on the top of the current	  |
| input stack.								  |
`------------------------------------------------------------------------*/

int
peek_input (void)
{
  register int ch;

  while (1)
    {
      if (isp == NULL)
	return CHAR_EOF;

      switch (isp->type)
	{
	case INPUT_STRING:
	  ch = isp->u.u_s.string[0];
	  if (ch != '\0')
	    return ch;
	  break;

	case INPUT_FILE:
	  ch = getc (isp->u.u_f.file);
	  if (ch != EOF)
	    {
	      ungetc (ch, isp->u.u_f.file);
	      return ch;
	    }
	  break;

	case INPUT_MACRO:
	  return CHAR_MACRO;

	default:
	  M4ERROR ((warning_status, 0,
		    "INTERNAL ERROR: Input stack botch in peek_input ()"));
	  abort ();
	}
      /* End of input source --- pop one level.  */
      pop_input ();
    }
}

/*-------------------------------------------------------------------------.
| The function next_char () is used to read and advance the input to the   |
| next character.  It also manages line numbers for error messages, so	   |
| they do not get wrong, due to lookahead.  The token consisting of a	   |
| newline alone is taken as belonging to the line it ends, and the current |
| line number is not incremented until the next character is read.	   |
`-------------------------------------------------------------------------*/

static int
next_char (void)
{
  register int ch;

  if (start_of_input_line)
    {
      start_of_input_line = FALSE;
      current_line++;
    }

  while (1)
    {
      if (isp == NULL)
	return CHAR_EOF;

      switch (isp->type)
	{
	case INPUT_STRING:
	  ch = *isp->u.u_s.string++;
	  if (ch != '\0')
	    return ch;
	  break;

	case INPUT_FILE:
	  ch = getc (isp->u.u_f.file);
	  if (ch != EOF)
	    {
	      if (ch == '\n')
		start_of_input_line = TRUE;
	      return ch;
	    }
	  break;

	case INPUT_MACRO:
	  pop_input ();		/* INPUT_MACRO input sources has only one
				   token */
	  return CHAR_MACRO;

	default:
	  M4ERROR ((warning_status, 0,
		    "INTERNAL ERROR: Input stack botch in next_char ()"));
	  abort ();
	}

      /* End of input source --- pop one level.  */
      pop_input ();
    }
}

/*------------------------------------------------------------------------.
| skip_line () simply discards all immediately following characters, upto |
| the first newline.  It is only used from m4_dnl ().			  |
`------------------------------------------------------------------------*/

void
skip_line (void)
{
  int ch;

  while ((ch = next_char ()) != CHAR_EOF && ch != '\n')
    ;
}


/*----------------------------------------------------------------------.
| This function is for matching a string against a prefix of the input  |
| stream.  If the string matches the input, the input is discarded,     |
| otherwise the characters read are pushed back again.  The function is |
| used only when multicharacter quotes or comment delimiters are used.  |
`----------------------------------------------------------------------*/

static int
match_input (const char *s)
{
  int n;			/* number of characters matched */
  int ch;			/* input character */
  const char *t;

  ch = peek_input ();
  if (ch != *s)
    return 0;			/* fail */
  (void) next_char ();

  if (s[1] == '\0')
    return 1;			/* short match */

  for (n = 1, t = s++; (ch = peek_input ()) == *s++; n++)
    {
      (void) next_char ();
      if (*s == '\0')		/* long match */
	return 1;
    }

  /* Failed, push back input.  */
  obstack_grow (push_string_init (), t, n);
  push_string_finish ();
  return 0;
}

/*------------------------------------------------------------------------.
| The macro MATCH() is used to match a string against the input.  The	  |
| first character is handled inline, for speed.  Hopefully, this will not |
| hurt efficiency too much when single character quotes and comment	  |
| delimiters are used.							  |
`------------------------------------------------------------------------*/

#define MATCH(ch, s) \
  ((s)[0] == (ch) \
   && (ch) != '\0' \
   && ((s)[1] == '\0' \
       || (match_input ((s) + 1) ? (ch) = peek_input (), 1 : 0)))


/*----------------------------------------------------------.
| Inititialise input stacks, and quote/comment characters.  |
`----------------------------------------------------------*/

void
input_init (void)
{
  current_file = "NONE";
  current_line = 0;

  obstack_init (&token_stack);
  obstack_init (&input_stack);
  obstack_init (&wrapup_stack);

  current_input = &input_stack;

  obstack_1grow (&token_stack, '\0');
  token_bottom = obstack_finish (&token_stack);

  isp = NULL;
  wsp = NULL;
  next = NULL;

  start_of_input_line = FALSE;

  lquote.string = xstrdup (DEF_LQUOTE);
  lquote.length = strlen (lquote.string);
  rquote.string = xstrdup (DEF_RQUOTE);
  rquote.length = strlen (rquote.string);
  bcomm.string = xstrdup (DEF_BCOMM);
  bcomm.length = strlen (bcomm.string);
  ecomm.string = xstrdup (DEF_ECOMM);
  ecomm.length = strlen (ecomm.string);

#ifdef ENABLE_CHANGEWORD
  if (user_word_regexp)
    set_word_regexp (user_word_regexp);
  else
    set_word_regexp (DEFAULT_WORD_REGEXP);
#endif
}


/*--------------------------------------------------------------.
| Functions for setting quotes and comment delimiters.  Used by |
| m4_changecom () and m4_changequote ().		        |
`--------------------------------------------------------------*/

void
set_quotes (const char *lq, const char *rq)
{
  xfree (lquote.string);
  xfree (rquote.string);

  lquote.string = xstrdup (lq ? lq : DEF_LQUOTE);
  lquote.length = strlen (lquote.string);
  rquote.string = xstrdup (rq ? rq : DEF_RQUOTE);
  rquote.length = strlen (rquote.string);
}

void
set_comment (const char *bc, const char *ec)
{
  xfree (bcomm.string);
  xfree (ecomm.string);

  bcomm.string = xstrdup (bc ? bc : DEF_BCOMM);
  bcomm.length = strlen (bcomm.string);
  ecomm.string = xstrdup (ec ? ec : DEF_ECOMM);
  ecomm.length = strlen (ecomm.string);
}

#ifdef ENABLE_CHANGEWORD

void
set_word_regexp (const char *regexp)
{
  int i;
  char test[2];
  const char *msg;

  if (!strcmp (regexp, DEFAULT_WORD_REGEXP))
    {
      default_word_regexp = TRUE;
      return;
    }

  default_word_regexp = FALSE;

  msg = re_compile_pattern (regexp, strlen (regexp), &word_regexp);

  if (msg != NULL)
    {
      M4ERROR ((warning_status, 0,
		"Bad regular expression `%s': %s", regexp, msg));
      return;
    }

  if (word_start == NULL)
    word_start = xmalloc (256);

  word_start[0] = '\0';
  test[1] = '\0';
  for (i = 1; i < 256; i++)
    {
      test[0] = i;
      if (re_search (&word_regexp, test, 1, 0, 0, &regs) >= 0)
	strcat (word_start, test);
    }
}

#endif /* ENABLE_CHANGEWORD */


/*-------------------------------------------------------------------------.
| Parse and return a single token from the input stream.  A token can	   |
| either be TOKEN_EOF, if the input_stack is empty; it can be TOKEN_STRING |
| for a quoted string; TOKEN_WORD for something that is a potential macro  |
| name; and TOKEN_SIMPLE for any single character that is not a part of	   |
| any of the previous types.						   |
| 									   |
| Next_token () return the token type, and passes back a pointer to the	   |
| token data through TD.  The token text is collected on the obstack	   |
| token_stack, which never contains more than one token text at a time.	   |
| The storage pointed to by the fields in TD is therefore subject to	   |
| change the next time next_token () is called.				   |
`-------------------------------------------------------------------------*/

token_type
next_token (token_data *td)
{
  int ch;
  int quote_level;
  token_type type;
#ifdef ENABLE_CHANGEWORD
  int startpos;
  char *orig_text = 0;
#endif

  obstack_free (&token_stack, token_bottom);
  obstack_1grow (&token_stack, '\0');
  token_bottom = obstack_finish (&token_stack);

  ch = peek_input ();
  if (ch == CHAR_EOF)
    {
      return TOKEN_EOF;
#ifdef DEBUG_INPUT
      fprintf (stderr, "next_token -> EOF\n");
#endif
    }
  if (ch == CHAR_MACRO)
    {
      init_macro_token (td);
      (void) next_char ();
      return TOKEN_MACDEF;
    }

  (void) next_char ();
  if (MATCH (ch, bcomm.string))
    {
      obstack_grow (&token_stack, bcomm.string, bcomm.length);
      while ((ch = next_char ()) != CHAR_EOF && !MATCH (ch, ecomm.string))
	obstack_1grow (&token_stack, ch);
      if (ch != CHAR_EOF)
	obstack_grow (&token_stack, ecomm.string, ecomm.length);
      type = TOKEN_STRING;
    }
#ifdef ENABLE_CHANGEWORD
  else if (default_word_regexp && (isalpha (ch) || ch == '_'))
#else
  else if (isalpha (ch) || ch == '_')
#endif
    {
      obstack_1grow (&token_stack, ch);
      while ((ch = peek_input ()) != CHAR_EOF && (isalnum (ch) || ch == '_'))
	{
	  obstack_1grow (&token_stack, ch);
	  (void) next_char ();
	}
      type = TOKEN_WORD;
    }

#ifdef ENABLE_CHANGEWORD

  else if (!default_word_regexp && strchr (word_start, ch))
    {
      obstack_1grow (&token_stack, ch);
      while (1)
        {
	  ch = peek_input ();
	  if (ch == CHAR_EOF)
	    break;
	  obstack_1grow (&token_stack, ch);
	  startpos = re_search (&word_regexp, obstack_base (&token_stack),
				obstack_object_size (&token_stack), 0, 0,
				&regs);
	  if (startpos != 0 ||
	      regs.end [0] != obstack_object_size (&token_stack))
	    {
	      *(((char *) obstack_base (&token_stack)
		 + obstack_object_size (&token_stack)) - 1) = '\0';
	      break;
	    }
	  next_char ();
	}

      obstack_1grow (&token_stack, '\0');
      orig_text = obstack_finish (&token_stack);

      if (regs.start[1] != -1)
	obstack_grow (&token_stack,orig_text + regs.start[1],
		      regs.end[1] - regs.start[1]);
      else
	obstack_grow (&token_stack, orig_text,regs.end[0]);

      type = TOKEN_WORD;
    }

#endif /* ENABLE_CHANGEWORD */

  else if (!MATCH (ch, lquote.string))
    {
      type = TOKEN_SIMPLE;
      obstack_1grow (&token_stack, ch);
    }
  else
    {
      quote_level = 1;
      while (1)
	{
	  ch = next_char ();
	  if (ch == CHAR_EOF)
	    M4ERROR ((EXIT_FAILURE, 0,
		      "ERROR: EOF in string"));

	  if (MATCH (ch, rquote.string))
	    {
	      if (--quote_level == 0)
		break;
	      obstack_grow (&token_stack, rquote.string, rquote.length);
	    }
	  else if (MATCH (ch, lquote.string))
	    {
	      quote_level++;
	      obstack_grow (&token_stack, lquote.string, lquote.length);
	    }
	  else
	    obstack_1grow (&token_stack, ch);
	}
      type = TOKEN_STRING;
    }

  obstack_1grow (&token_stack, '\0');

  TOKEN_DATA_TYPE (td) = TOKEN_TEXT;
  TOKEN_DATA_TEXT (td) = obstack_finish (&token_stack);
#ifdef ENABLE_CHANGEWORD
  if (orig_text == NULL)
    orig_text = TOKEN_DATA_TEXT (td);
  TOKEN_DATA_ORIG_TEXT (td) = orig_text;
#endif
#ifdef DEBUG_INPUT
  fprintf (stderr, "next_token -> %d (%s)\n", type, TOKEN_DATA_TEXT (td));
#endif
  return type;
}


#ifdef DEBUG_INPUT

static void
print_token (const char *s, token_type t, token_data *td)
{
  fprintf (stderr, "%s: ", s);
  switch (t)
    {				/* TOKSW */
    case TOKEN_SIMPLE:
      fprintf (stderr, "char:");
      break;

    case TOKEN_WORD:
      fprintf (stderr, "word:");
      break;

    case TOKEN_STRING:
      fprintf (stderr, "string:");
      break;

    case TOKEN_MACDEF:
      fprintf (stderr, "macro: 0x%x\n", TOKEN_DATA_FUNC (td));
      break;

    case TOKEN_EOF:
      fprintf (stderr, "eof\n");
      break;
    }
  fprintf (stderr, "\t\"%s\"\n", TOKEN_DATA_TEXT (td));
}

static void
lex_debug (void)
{
  token_type t;
  token_data td;

  while ((t = next_token (&td)) != NULL)
    print_token ("lex", t, &td);
}
#endif
