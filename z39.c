/*@z39.c:String Handler:AsciiToFull(), StringEqual(), etc.@*******************/
/*                                                                           */
/*  LOUT: A HIGH-LEVEL LANGUAGE FOR DOCUMENT FORMATTING (VERSION 2.05)       */
/*  COPYRIGHT (C) 1993 Jeffrey H. Kingston                                   */
/*                                                                           */
/*  Jeffrey H. Kingston (jeff@cs.su.oz.au)                                   */
/*  Basser Department of Computer Science                                    */
/*  The University of Sydney 2006                                            */
/*  AUSTRALIA                                                                */
/*                                                                           */
/*  This program is free software; you can redistribute it and/or modify     */
/*  it under the terms of the GNU General Public License as published by     */
/*  the Free Software Foundation; either version 1, or (at your option)      */
/*  any later version.                                                       */
/*                                                                           */
/*  This program is distributed in the hope that it will be useful,          */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*  GNU General Public License for more details.                             */
/*                                                                           */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program; if not, write to the Free Software              */
/*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
/*                                                                           */
/*  FILE:         z39.c                                                      */
/*  MODULE:       String Handler                                             */
/*  EXTERNS:      AsciiToFull(), StringEqual(), StringLessEqual(),           */
/*                StringCat(), StringCopy(), StringLength(),                 */
/*                StringFOpen(), StringFPuts(), StringFGets(),               */
/*                StringUnlink(), StringLink(), StringBeginsWith(),          */
/*                StringContains(), StringInt(), StringFiveInt(),            */
/*                StringQuotedWord()                                         */
/*                                                                           */
/*****************************************************************************/
#include "externs"


/*****************************************************************************/
/*                                                                           */
/*          AsciiToFull(str)          Returns ASCII string as FULL_CHARs.    */
/*  BOOLEAN StringEqual(a, b)         TRUE if strings a and b are equal      */
/*  BOOLEAN StringLessEqual(a, b)     TRUE if string a <= string b           */
/*          StringCat(a, b)           Catenate string b onto end of a        */
/*          StringCopy(a, b)          Overwrite string a with string b       */
/*          StringLength(a)           Length of string a                     */
/*          StringFOpen(str, mode)    Equivalent to fopen(str, mode)         */
/*          StringFPuts(str, fp)      Equivalent to fputs(str, fp)           */
/*          StringFGets(str, n, fp)   Equivalent to fgets(str, n, fp)        */
/*          StringUnlink(a)           Equivalent to unlink(a)                */
/*          StringLink(a, b)          Equivalent to link(a, b)               */
/*                                                                           */
/*  These procedures are defined as macros in file externs.                  */
/*                                                                           */
/*****************************************************************************/


/*@::StringBeginsWith(), StringContains(), StringInt(), StringFiveInt()@******/
/*                                                                           */
/*  BOOLEAN StringBeginsWith(str, pattern)                                   */
/*                                                                           */
/*  Check whether str begins with pattern.                                   */
/*                                                                           */
/*****************************************************************************/

BOOLEAN StringBeginsWith(str, pattern)
FULL_CHAR *str, *pattern;
{ FULL_CHAR *sp, *pp;
  sp = str;  pp = pattern;
  while( *sp != '\0' && *pp != '\0' )
  { if( *sp++ != *pp++ )  return FALSE;
  }
  return (*pp == '\0');
} /* end StringBeginsWith */


/*****************************************************************************/
/*                                                                           */
/*  BOOLEAN StringContains(str, pattern)                                     */
/*                                                                           */
/*  Check whether str contains pattern.                                      */
/*                                                                           */
/*****************************************************************************/

BOOLEAN StringContains(str, pattern)
FULL_CHAR *str, *pattern;
{ FULL_CHAR *sp;
  for( sp = str;  *sp != '\0';  sp++ )
  { if( StringBeginsWith(sp, pattern) )  return TRUE;
  }
  return FALSE;
} /* end StringContains */


/*****************************************************************************/
/*                                                                           */
/*  FULL_CHAR *StringInt(i)                                                  */
/*  FULL_CHAR *StringFiveInt(i)                                              */
/*                                                                           */
/*  Returns a string version of integer i.                                   */
/*                                                                           */
/*****************************************************************************/

FULL_CHAR *StringInt(i)
int i;
{ static FULL_CHAR buff[20];
  sprintf( (char *) buff, "%d", i);
  return buff;
} /* end StringInt */

FULL_CHAR *StringFiveInt(i)
int i;
{ static FULL_CHAR buff[20];
  sprintf( (char *) buff, "%.5d", i);
  return buff;
} /* end StringInt */


/*@::StringQuotedWord()@******************************************************/
/*                                                                           */
/*  static char *quoted_string[]                                             */
/*                                                                           */
/*  quoted_string[ch] is a string containing the representation of the       */
/*  8-bit character ch within a quoted string in a Lout source file.         */
/*                                                                           */
/*****************************************************************************/

static char *quoted_string[] = {
    "\\000", "\\001", "\\002", "\\003", "\\004", "\\005", "\\006", "\\007",
    "\\010", "\\011", "\\012", "\\013", "\\014", "\\015", "\\016", "\\017",
    "\\020", "\\021", "\\022", "\\023", "\\024", "\\025", "\\026", "\\027",
    "\\030", "\\031", "\\032", "\\033", "\\034", "\\035", "\\036", "\\037",
    " ",     "!",     "\\\"",  "#",     "$",     "%",     "&",     "'",
    "(",     ")",     "*",     "+",     ",",     "-",     ".",     "/",
    "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",
    "8",     "9",     ":",     ";",     "<",     "=",     ">",     "?",

    "@",     "A",     "B",     "C",     "D",     "E",     "F",     "G",
    "H",     "I",     "J",     "K",     "L",     "M",     "N",     "O",
    "P",     "Q",     "R",     "S",     "T",     "U",     "V",     "W",
    "X",     "Y",     "Z",     "[",     "\\\\",  "]",     "^",     "_",
    "`",     "a",     "b",     "c",     "d",     "e",     "f",     "g",
    "h",     "i",     "j",     "k",     "l",     "m",     "n",     "o",
    "p",     "q",     "r",     "s",     "t",     "u",     "v",     "w",
    "x",     "y",     "z",     "{",     "|",     "}",     "~",     "\\177",

    "\\200", "\\201", "\\202", "\\203", "\\204", "\\205", "\\206", "\\207",
    "\\210", "\\211", "\\212", "\\213", "\\214", "\\215", "\\216", "\\217",
    "\\220", "\\221", "\\222", "\\223", "\\224", "\\225", "\\226", "\\227",
    "\\230", "\\231", "\\232", "\\233", "\\234", "\\235", "\\236", "\\237",
    "\\240", "\\241", "\\242", "\\243", "\\244", "\\245", "\\246", "\\247",
    "\\250", "\\251", "\\252", "\\253", "\\254", "\\255", "\\256", "\\257",
    "\\260", "\\261", "\\262", "\\263", "\\264", "\\265", "\\266", "\\267",
    "\\270", "\\271", "\\272", "\\273", "\\274", "\\275", "\\276", "\\277",

    "\\300", "\\301", "\\302", "\\303", "\\304", "\\305", "\\306", "\\307",
    "\\310", "\\311", "\\312", "\\313", "\\314", "\\315", "\\316", "\\317",
    "\\320", "\\321", "\\322", "\\323", "\\324", "\\325", "\\326", "\\327",
    "\\330", "\\331", "\\332", "\\333", "\\334", "\\335", "\\336", "\\337",
    "\\340", "\\341", "\\342", "\\343", "\\344", "\\345", "\\346", "\\347",
    "\\350", "\\351", "\\352", "\\353", "\\354", "\\355", "\\356", "\\357",
    "\\360", "\\361", "\\362", "\\363", "\\364", "\\365", "\\366", "\\367",
    "\\370", "\\371", "\\372", "\\373", "\\374", "\\375", "\\376", "\\377",
};


/*****************************************************************************/
/*                                                                           */
/*  FULL_CHAR *StringQuotedWord(x)                                           */
/*                                                                           */
/*  Returns the string in QWORD x in the form it would need to take if it    */
/*  was a quoted word in a Lout source file.  Note that the result is        */
/*  returned in a static variable so it needs to be copied before a          */
/*  subsequent call to StringQuotedWord is made.                             */
/*                                                                           */
/*****************************************************************************/

FULL_CHAR *StringQuotedWord(x)
OBJECT x;
{ FULL_CHAR *p, *q, *r;
  static FULL_CHAR buff[MAX_LINE];
  assert( type(x) == QWORD, "StringQuotedWord: type(x) != QWORD!" );
  q = buff;
  *q++ = CH_QUOTE;
  for( p = string(x);  *p != '\0';  p++ )
  { 
    for( r = (FULL_CHAR *) quoted_string[*p];  *r != '\0';  *q++ = *r++ );
  }
  *q++ = CH_QUOTE;
  *q++ = '\0';
  return buff;
} /* StringQuotedWord */