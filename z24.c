/*@z24.c:Print Service:PrintInit()@*******************************************/
/*                                                                           */
/*  THE LOUT DOCUMENT FORMATTING SYSTEM (VERSION 3.26)                       */
/*  COPYRIGHT (C) 1991, 2002 Jeffrey H. Kingston                             */
/*                                                                           */
/*  Jeffrey H. Kingston (jeff@cs.usyd.edu.au)                                */
/*  Basser Department of Computer Science                                    */
/*  The University of Sydney 2006                                            */
/*  AUSTRALIA                                                                */
/*                                                                           */
/*  PDF Back End by Vincent Tan, February 1998.                              */
/*                                                                           */
/*  This program is free software; you can redistribute it and/or modify     */
/*  it under the terms of the GNU General Public License as published by     */
/*  the Free Software Foundation; either Version 2, or (at your option)      */
/*  any later version.                                                       */
/*                                                                           */
/*  This program is distributed in the hope that it will be useful,          */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*  GNU General Public License for more details.                             */
/*                                                                           */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program; if not, write to the Free Software              */
/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston MA 02111-1307 USA   */
/*                                                                           */
/*  FILE:         z24.c                                                      */
/*  MODULE:       Print Service                                              */
/*  EXTERNS:      EightBitToPrintForm                                        */
/*                                                                           */
/*  This module used to be a combined implementation of all the back         */
/*  ends.  Now these have been split off into separate files, there is       */
/*  very little left in this module.                                         */
/*                                                                           */
/*****************************************************************************/
#include "externs.h"


/*@::EightBitToPrintForm()@***************************************************/
/*                                                                           */
/*  char *EightBitToPrintForm[]                                              */
/*                                                                           */
/*  Given 8-bit character i, returns a string of characters that will be     */
/*  interpreted by PostScript as character i when read within a string.      */
/*                                                                           */
/*      CHAR_OUT==1    Printable ASCII literal, others as escape sequences   */
/*      CHAR_OUT==2    Printable ISO-LATIN-1 literal, others escaped         */
/*                                                                           */
/*****************************************************************************/

char *EightBitToPrintForm[] = {
#if CHAR_OUT==0
    "",      "\\001", "\\002", "\\003", "\\004", "\\005", "\\006", "\\007",
    "\\010", "\\011", "\\012", "\\013", "\\014", "\\015", "\\016", "\\017",
    "\\020", "\\021", "\\022", "\\023", "\\024", "\\025", "\\026", "\\027",
    "\\030", "\\031", "\\032", "\\033", "\\034", "\\035", "\\036", "\\037",
    " ",     "!",     "\"",    "#",     "$",     "%",     "&",     "'",
    "\\(",   "\\)",   "*",     "+",     ",",     "-",     ".",     "/",
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
    "\\370", "\\371", "\\372", "\\373", "\\374", "\\375", "\\376", "\\377"
#else
#if CHAR_OUT==1
    "",      "\\001", "\\002", "\\003", "\\004", "\\005", "\\006", "\\007",
    "\\010", "\\011", "\\012", "\\013", "\\014", "\\015", "\\016", "\\017",
    "\\020", "\\021", "\\022", "\\023", "\\024", "\\025", "\\026", "\\027",
    "\\030", "\\031", "\\032", "\\033", "\\034", "\\035", "\\036", "\\037",
    " ",     "!",     "\"",    "#",     "$",     "%",     "&",     "'",
    "\\(",   "\\)",   "*",     "+",     ",",     "-",     ".",     "/",
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
    "\220",  "\221",  "\222",  "\223",  "\224",  "\225",  "\226",  "\227",
    "\230",  "\\231", "\232",  "\233",  "\\234", "\235",  "\236",  "\237",
    "\240",  "\241",  "\242",  "\243",  "\244",  "\245",  "\246",  "\247",
    "\250",  "\251",  "\252",  "\253",  "\254",  "\255",  "\256",  "\257",
    "\260",  "\261",  "\262",  "\263",  "\264",  "\265",  "\266",  "\267",
    "\270",  "\271",  "\272",  "\273",  "\274",  "\275",  "\276",  "\277",
    "\300",  "\301",  "\302",  "\303",  "\304",  "\305",  "\306",  "\307",
    "\310",  "\311",  "\312",  "\313",  "\314",  "\315",  "\316",  "\317",
    "\320",  "\321",  "\322",  "\323",  "\324",  "\325",  "\326",  "\327",
    "\330",  "\331",  "\332",  "\333",  "\334",  "\335",  "\336",  "\337",
    "\340",  "\341",  "\342",  "\343",  "\344",  "\345",  "\346",  "\347",
    "\350",  "\351",  "\352",  "\353",  "\354",  "\355",  "\356",  "\357",
    "\360",  "\361",  "\362",  "\363",  "\364",  "\365",  "\366",  "\367",
    "\370",  "\371",  "\372",  "\373",  "\374",  "\375",  "\376",  "\377"
#else
If you are trying to compile this you have the wrong CHAR_OUT value!
#endif
#endif
};
