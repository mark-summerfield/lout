/*@z23.c:Galley Printer:ScaleFactor()@****************************************/
/*                                                                           */
/*  THE LOUT DOCUMENT FORMATTING SYSTEM (VERSION 3.06)                       */
/*  COPYRIGHT (C) 1994 Jeffrey H. Kingston                                   */
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
/*  FILE:         z23.c                                                      */
/*  MODULE:       Galley Printer                                             */
/*  EXTERNS:      FixAndPrintObject()                                        */
/*                                                                           */
/*****************************************************************************/
#include "externs"
#define	NO_SUPPRESS	FALSE
#define	SUPPRESS	TRUE
#define	LAST_ADJUST	1
#define	ALL_ADJUST	2

#define CountChild(y, link, i)						\
for( y=pred(link, PARENT), i=1; type(y)==LINK;  y = pred(y, PARENT), i++ )


/*****************************************************************************/
/*                                                                           */
/*  static float ScaleFactor(avail_size, inner_size)                         */
/*                                                                           */
/*  Return the scale factor for this scaling, or 0 if impossible.            */
/*                                                                           */
/*****************************************************************************/

static float ScaleFactor(LENGTH avail_size, LENGTH inner_size)
{ float scale_factor;
  scale_factor = avail_size <= 0 ? 0 :
		 inner_size <= 0 ? 0 : (float) avail_size / inner_size;
  return scale_factor;
}


/*@::FindAdjustIncrement()@***************************************************/
/*                                                                           */
/*  static LENGTH FindAdjustIncrement(x, frame_size, dim)                    */
/*                                                                           */
/*  Find the amount by which to increase the width of the subobjects of      */
/*  concatenation object x so that it is adjusted to fill size frame_size.   */
/*                                                                           */
/*****************************************************************************/

static LENGTH FindAdjustIncrement(OBJECT x, LENGTH frame_size, int dim)
{ OBJECT y, link, prev, g;
  int adjustable_gaps;  BOOLEAN jn;
  LENGTH inc, mk, actual_size;

  debug2(DGP, D, "FindAdjustIncrement(x, %s, %s)",
	EchoLength(frame_size), dimen(dim));
  FirstDefinite(x, link, prev, jn);
  if( link != x )
  { adjustable_gaps = 0;
    mk = back(prev, dim);
    NextDefiniteWithGap(x, link, y, g, jn);
    while( link != x )
    { if ( mode(gap(g)) == TAB_MODE || units(gap(g)) == AVAIL_UNIT
				    || units(gap(g)) == FRAME_UNIT )
      {	debug0(DGP, D, "FindAdjustIncrement returning 0 (tab gap)");
	return 0;
      }
      mk += ActualGap(fwd(prev, dim), back(y, dim), fwd(y, dim), &gap(g),
		frame_size, mk);
      prev = y;
      adjustable_gaps++;
      NextDefiniteWithGap(x, link, y, g, jn);
    }
    actual_size = mk + fwd(prev, dim);
    debug2(DGP, DD, "  actual_size = %s, adjustable_gaps = %d",
	EchoLength(actual_size), adjustable_gaps);
    inc = adjustable_gaps==0 ? 0 : (frame_size - actual_size) / adjustable_gaps;
  }
  else inc = 0;
  debug1(DGP, D, "FindAdjustIncrement returning %s", EchoLength(inc));
  return inc;
} /* end FindAdjustIncrement */


/*@::FixAndPrintObject()@*****************************************************/
/*                                                                           */
/*  FixAndPrintObject(x, xmk, xb, xf, dim, adjust, suppress, padj, pg,count) */
/*                                                                           */
/*  Fix the absolute position of object x in dimension dim, in such a way    */
/*  that the principal mark of x has coordinate xmk, and x has actual size   */
/*  (xb, xf), where xb >= back(x, dim) and xf >= fwd(x, dim).                */
/*                                                                           */
/*  Actually, in the case where x includes an object lying on a thread       */
/*  leading outside x, the final size of x may be different.  Because        */
/*  of this, the procedure sets back(x, dim) and fwd(x, dim) to the actual   */
/*  size of x upon return.  The caller assumes that x will exactly occupy    */
/*  this space back(x, dim), fwd(x, dim).                                    */
/*                                                                           */
/*  If x does not fill the forward part of the space allocated to it, the    */
/*  adjust parameter determines what, if anything, to do about this.  The    */
/*  two possible values of this parameter are:                               */
/*                                                                           */
/*    LAST_ADJUST        Adjust x to fill the forward space available to     */
/*                       it, by adjusting the last component if x is a       */
/*                       CAT object, or adjusting the child otherwise.       */
/*                                                                           */
/*    ALL_ADJUST         Adjust x to fill the forward space available to     */
/*                       it, by adjusting all the components if x is a       */
/*                       CAT object, or adjusting the child otherwise.       */
/*                                                                           */
/*  The suppress parameter is true if a temporary suppression of adjustment  */
/*  is in effect (because a neighbouring adjustment has already been done).  */
/*                                                                           */
/*  The padj parameter is analogous to the adjust parameter, but it          */
/*  applies only to & adjustment, not to | or / adjustment.                  */
/*                                                                           */
/*  If dim == COL, the coordinate information is merely stored; but if       */
/*  dim == ROW, it is used to generate PostScript for printing x.            */
/*                                                                           */
/*  Parameter pg records the height of the current page.  This is used       */
/*  to correct for the fact that Lout places its origin at the top left,     */
/*  while PostScript places its origin at the bottom left.  This correction  */
/*  cannot be made by transforming user space.                               */
/*                                                                           */
/*  x is child number count of its parent (used by COL_THR and ROW_THR only) */
/*                                                                           */
/*****************************************************************************/

void FixAndPrintObject(OBJECT x, LENGTH xmk, LENGTH xb, LENGTH xf, int dim,
int adjust, BOOLEAN suppress, int padj, LENGTH pg, int count)
{ OBJECT y, link, prev, g, uplink, z, face;
  LENGTH mk, ymk, frame_size, back_edge, yb, yf, inc, f;
  int i; float scale_factor;  BOOLEAN jn;
  debug8(DGP, D, "[ FixAndPrintObject(%s, %s, %s,%s, %s, %s, %s, %s, pg )",
    Image(type(x)), EchoLength(xmk), EchoLength(xb), EchoLength(xf), dimen(dim),
    (adjust == LAST_ADJUST ? "last_adjust" : "all_adjust"),
    (suppress == SUPPRESS ? "suppress" : "no_suppress"),
    (padj   == LAST_ADJUST ? "last_adjust" : "all_adjust"));
  debug2(DGP, D, "  size(x) = %s,%s;  x =",
    EchoLength(back(x, dim)), EchoLength(fwd(x, dim)));
  ifdebug(DGP, DD, DebugObject(x));

  switch( type(x) )
  {

    case CLOSURE:
    case NULL_CLOS:
    case PAGE_LABEL:
    case CROSS:
    
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case WORD:
    case QWORD:
    
      if( dim == COL )
      {
	/* save horizontal position for PrintWord below */
	word_save_mark(x) = xmk;

	/* if first occurrence of this font on this page, notify font */
	if( string(x)[0] != '\0' )
	{ face = finfo[word_font(x)].original_font;
	  if( font_page(face) < font_curr_page )
	  { debug3(DFT, DD, "FAPO: x = %s, word_font = %d, face = %s",
	      string(x), word_font(x), EchoObject(face));
	    FontPageUsed(face);
	  }
	}
      }
      else
      { if( string(x)[0] != '\0' )
	{ PrintWord(x, word_save_mark(x), pg - xmk);
	  if( underline(x) )
	  { FontWordSize(x);  /* to restore fwd(x, COL) */
	    PrintUnderline(word_font(x), word_save_mark(x),
	      word_save_mark(x) + fwd(x, COL), pg - xmk);
	  }
	}
      }
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case WIDE:
    case HIGH:
    
      CountChild(y, Down(x), count);
      if( (dim == COL) == (type(x) == WIDE) )
      { yf = bfc(constraint(x)) - back(y, dim);
        FixAndPrintObject(y, xmk, back(y,dim), yf, dim, LAST_ADJUST,
		NO_SUPPRESS, padj, pg, count);
        back(x, dim) = xb;  fwd(x, dim) = xf;
      }
      else
      {	FixAndPrintObject(y, xmk, xb, xf, dim, adjust, suppress,
	  padj, pg, count);
	back(x, dim) = back(y, dim);  fwd(x, dim) = fwd(y, dim);
      }
      break;


    case HSHIFT:
    case VSHIFT:

      CountChild(y, Down(x), count);
      if( (dim == COL) == (type(x) == HSHIFT) )
      {
	/* work out the size of the shift depending on the units */
	f = FindShift(x, y, dim);
	ymk = xmk - f;
	yb = max(0, xb - f);
	yf = max(0, xf + f);
	FixAndPrintObject(y, ymk, yb, yf, dim, adjust, suppress,
	  padj, pg, count);

	/* recalculate the size of x as in MinSize */
	f = FindShift(x, y, dim);
	back(x, dim) = min(MAX_LEN, max(0, back(y, dim) + f));
	fwd(x, dim)  = min(MAX_LEN, max(0, fwd(y, dim)  - f));
      }
      else
      {	FixAndPrintObject(y, xmk, xb, xf, dim, adjust, suppress,
	  padj, pg, count);
	back(x, dim) = back(y, dim);  fwd(x, dim) = fwd(y, dim);
      }
      break;


    case HCONTRACT:
    case VCONTRACT:
    
      CountChild(y, Down(x), count);
      if( (dim == COL) == (type(x) == HCONTRACT) )
      {	FixAndPrintObject(y, xmk, back(y,dim), fwd(y,dim), dim, LAST_ADJUST,
	  NO_SUPPRESS, padj, pg, count);
        back(x, dim) = xb;  fwd(x, dim) = xf;
      }
      else
      {	FixAndPrintObject(y, xmk, xb, xf, dim, adjust, suppress,padj,pg,count);
        back(x, dim) = back(y, dim);  fwd(x, dim) = fwd(y, dim);
      }
      break;


    case ONE_COL:
    case ONE_ROW:
    case HEXPAND:
    case VEXPAND:
    
      CountChild(y, Down(x), count);
      if( (dim == COL) == (type(x) == ONE_COL || type(x) == HEXPAND) )
      { FixAndPrintObject(y, xmk, xb, xf, dim, LAST_ADJUST,
		NO_SUPPRESS, padj, pg, count);
        back(x, dim) = xb;  fwd(x, dim) = xf;
      }
      else
      {	FixAndPrintObject(y, xmk, xb, xf, dim, adjust, suppress,padj,pg,count);
	back(x, dim) = back(y, dim);  fwd(x, dim) = fwd(y, dim);
      }
      break;


    case PADJUST:
    
      CountChild(y, Down(x), count);
      FixAndPrintObject(y, xmk, xb, xf, dim, adjust, suppress,
	ALL_ADJUST, pg, count);
      back(x, dim) = back(y, dim);  fwd(x, dim) = fwd(y, dim);
      break;


    case HADJUST:
    case VADJUST:
    
      CountChild(y, Down(x), count);
      if( (dim == COL) == (type(x) == HADJUST) )
      {	FixAndPrintObject(y, xmk, xb, xf, dim, ALL_ADJUST, suppress,
	  padj, pg, count);
        back(x, dim) = xb;  fwd(x, dim) = xf;
      }
      else
      {	FixAndPrintObject(y, xmk, xb, xf, dim, adjust, suppress,
	  padj, pg, count);
	back(x, dim) = back(y, dim);  fwd(x, dim) = fwd(y, dim);
      }
      break;


    case VSCALE:

      debug0(DRS, D, "FixAndPrintObject at VSCALE");
      CountChild(y, Down(x), count);
      switch( BackEnd )
      {
	case PLAINTEXT:

	  break;


	case POSTSCRIPT:

          if( dim == COL )
            FixAndPrintObject(y, xmk, xb, xf, dim, LAST_ADJUST, NO_SUPPRESS,
		    padj,pg,count);
          else if( (scale_factor = ScaleFactor(xb+xf, size(y, ROW))) > 0 )
          { SaveGraphicState();
	    CoordTranslate(0, pg-(xmk-xb+(LENGTH) (back(y,ROW)*scale_factor)));
	    CoordScale(1.0, scale_factor);
            FixAndPrintObject(y, 0, back(y,ROW), fwd(y,ROW), dim, LAST_ADJUST,
	      NO_SUPPRESS, padj, 0, count);
	    RestoreGraphicState();
          }
          else if( !is_word(type(y)) || string(y)[0] != '\0' )
            Error(23, 1, "object deleted (it cannot be scaled vertically)",
	      WARN, &fpos(x));
	  break;
      }
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case HSCALE:
    
      debug0(DRS, DD, "FixAndPrintObject at HSCALE");
      CountChild(y, Down(x), count);
      switch( BackEnd )
      {
	case PLAINTEXT:

	  break;


	case POSTSCRIPT:

          if( dim == COL )
          { save_mark(x) = xmk;
	    bc(constraint(x)) = xb;
	    fc(constraint(x)) = xf;
            if( (scale_factor = ScaleFactor(xb+xf, size(y, COL))) > 0 )
	      FixAndPrintObject(y, 0, back(y, COL), fwd(y, COL), dim,
		LAST_ADJUST, NO_SUPPRESS, LAST_ADJUST, pg, count);
            else if( !is_word(type(y)) || string(y)[0] != '\0' )
	      Error(23, 2, "object deleted (it cannot be scaled horizontally)",
		WARN, &fpos(y));
          }
          else if( (scale_factor =
	    ScaleFactor(bc(constraint(x))+fc(constraint(x)),size(y,COL))) > 0 )
          { SaveGraphicState();
	    CoordTranslate(save_mark(x) - bc(constraint(x))
	       + (LENGTH) (back(y, COL)*scale_factor), 0);
	    CoordScale(scale_factor, 1.0);
            FixAndPrintObject(y, xmk, xb, xf, dim, LAST_ADJUST,
	      NO_SUPPRESS, padj, pg, count);
	    RestoreGraphicState();
          }
	  break;
      }
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case SCALE:

      CountChild(y, Down(x), count);
      switch( BackEnd )
      {
	case PLAINTEXT:

	  /* printable only if scale factor is one */
	  if( bc(constraint(x)) == SF && fc(constraint(x)) == SF )
	  {
	    FixAndPrintObject(y, xmk, xb, xf, dim, adjust,
	      suppress, padj, pg, count);
	  }
	  break;


	case POSTSCRIPT:

          if( dim == COL )
          { assert( bc(constraint(x)) > 0, "FAPO: horizontal scale factor!" );
	    save_mark(x) = xmk;
	    yb = xb * SF / bc(constraint(x));
	    yf = xf * SF / bc(constraint(x));
            FixAndPrintObject(y, 0, yb, yf, dim, LAST_ADJUST, NO_SUPPRESS,
		    padj, pg, count);
          }
          else
          { assert( fc(constraint(x)) > 0, "FAPO: vertical scale factor!" );
	    yb = xb * SF / fc(constraint(x));
	    yf = xf * SF / fc(constraint(x));
	    SaveGraphicState();
	    CoordTranslate(save_mark(x), pg - xmk);
	    CoordScale( (float) bc(constraint(x))/SF,
	      (float) fc(constraint(x))/SF);
            FixAndPrintObject(y, 0, yb, yf, dim, LAST_ADJUST, NO_SUPPRESS,
	      padj,0,count);
	    RestoreGraphicState();
          }
	  break;
      }
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case ROTATE:
    
      CountChild(y, Down(x), count);
      switch( BackEnd )
      {
	case PLAINTEXT:

	  /* printable only if angle is zero */
	  if( sparec(constraint(x)) == 0 )
	  {
	    FixAndPrintObject(y, xmk, xb, xf, dim, adjust,
	      suppress, padj, pg, count);
	  }
	  break;


	case POSTSCRIPT:

          if( dim == COL )
          { CONSTRAINT colc, rowc, yc;
            save_mark(x) = xmk;
	    SetConstraint(colc, back(x,COL), MAX_LEN, fwd(x,COL));
	    SetConstraint(rowc, back(x,ROW), MAX_LEN, fwd(x,ROW));
	    RotateConstraint(&yc, y, sparec(constraint(x)), &colc, &rowc, COL);
	    FixAndPrintObject(y, 0, bc(yc), fc(yc), COL, LAST_ADJUST,
		    NO_SUPPRESS, padj, pg, count);
          }
          else
          { CONSTRAINT colc, rowc, yc;
	    SaveGraphicState();
	    CoordTranslate(save_mark(x), pg - xmk);
	    CoordRotate(sparec(constraint(x)));
	    SetConstraint(colc, back(x,COL), MAX_LEN, fwd(x,COL));
	    SetConstraint(rowc, back(x,ROW), MAX_LEN, fwd(x,ROW));
	    RotateConstraint(&yc, y, sparec(constraint(x)), &colc, &rowc, ROW);
	    FixAndPrintObject(y, 0, bc(yc), fc(yc), ROW, LAST_ADJUST,
		    NO_SUPPRESS, padj, 0, count);
	    RestoreGraphicState();
          }
	  break;
      }
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case GRAPHIC:
    
      CountChild(y, LastDown(x), count);
      switch( BackEnd )
      {
	case PLAINTEXT:

          FixAndPrintObject(y, xmk, xb, xf,dim,adjust,suppress,padj,pg,count);
	  break;


	case POSTSCRIPT:

          if( dim == COL )
          {
	    /* if first occurrence of this font on this page, notify font */
	    if( font(save_style(x)) > 0 )
	    { face = finfo[font(save_style(x))].original_font;
	      if( font_page(face) < font_curr_page )  FontPageUsed(face);
	    }

	    back(x, dim) = xb;
	    fwd(x, dim)  = xf;
	    debug2(DGP, DD, "GRAPHIC COL storing size %s, %s",
	      EchoLength(back(x, dim)), EchoLength(fwd(x, dim)));
	    save_mark(x) = xmk - back(x, COL);
            FixAndPrintObject(y, xb, xb, xf, dim, LAST_ADJUST,
		    NO_SUPPRESS, padj, pg, count);
          }
          else
          { OBJECT tmp, pre, post;
            Child(tmp, Down(x));
            if( type(tmp) == VCAT )
            { Child(pre, Down(tmp));
              Child(post, LastDown(tmp));
            }
            else pre = tmp, post = nilobj;
	    back(x, dim) = xb;
	    fwd(x, dim)  = xf;
            SaveGraphicState();
            CoordTranslate(save_mark(x), pg - (xmk + fwd(x, ROW)));
	    debug4(DGP, DD, "GRAPHIC ROW calling %s,%s %s,%s",
	      EchoLength(back(x, COL)), EchoLength(fwd(x, COL)),
	      EchoLength(back(x, ROW)), EchoLength(fwd(x, ROW)));
            DefineGraphicNames(x);
            SaveGraphicState();
            PrintGraphicObject(pre);
            RestoreGraphicState();
            FixAndPrintObject(y, xb, xb, xf, dim, LAST_ADJUST,
		    NO_SUPPRESS, padj, xb + xf, count);
            if( post != nilobj )  PrintGraphicObject(post);
            RestoreGraphicState();
          }
	  break;

      } /* end switch */
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case INCGRAPHIC:
    case SINCGRAPHIC:

      CountChild(y, Down(x), count);
      switch( BackEnd )
      {
	case PLAINTEXT:

	  break;


	case POSTSCRIPT:

          if( dim == COL )
	  { save_mark(x) = xmk;
	    if( sparec(constraint(x)) )
	    { face = finfo[font(save_style(x))].original_font;
	      if( font_page(face) < font_curr_page )
	      {	debug3(DFT, DD, "FAPO-IG: x = %s, font = %d, face = %s",
		  string(x), font(save_style(x)), EchoObject(face));
		FontPageUsed(face);
	      }
	    }
	  }
          else if( sparec(constraint(x)) )
	    PrintGraphicInclude(x, save_mark(x), pg - xmk);
	  break;

      }
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case SPLIT:
    
      link = DownDim(x, dim);  CountChild(y, link, count);
      FixAndPrintObject(y, xmk, xb, xf, dim, adjust, suppress,padj,pg,count);
      back(x, dim) = back(y, dim);  fwd(x, dim) = fwd(y, dim);
      break;


    case VCAT:
    case HCAT:

      if( (type(x) == VCAT) == (dim == ROW) )
      { 
	/* find adjustment increment if required */
	frame_size = xb + xf;
	if( adjust == ALL_ADJUST && !suppress )
	  inc = FindAdjustIncrement(x, frame_size, dim);
	else inc = 0;

	FirstDefinite(x, link, prev, jn);
	if( link != x )
	{ back_edge = xmk - back(x, dim);
	  mk = back_edge + back(prev, dim);
	  NextDefiniteWithGap(x, link, y, g, jn);
	  while( link != x )
	  {
	    FixAndPrintObject(prev, mk, back(prev, dim), fwd(prev, dim) + inc,
	      dim, adjust, NO_SUPPRESS, padj, pg, count);
	    /* NB fwd(prev, dim) may be changed by the call to FAPO */
	    mk += ActualGap(fwd(prev, dim), back(y, dim), fwd(y, dim), &gap(g),
		    frame_size, mk - back_edge);
	    prev = y;
	    NextDefiniteWithGap(x, link, y, g, jn);
	  }
	  if( suppress )
	    FixAndPrintObject(prev, mk, back(prev, dim), fwd(prev, dim),
	      dim, adjust, NO_SUPPRESS, padj, pg, count);
	  else
	    FixAndPrintObject(prev, mk, back(prev,dim),
	      max(fwd(prev, dim), back_edge+frame_size-mk),
	      dim, adjust, NO_SUPPRESS, padj, pg, count);
	  back(x, dim) = max(back(x, dim), xb);
	  fwd(x, dim) = mk + fwd(prev, dim) - back_edge - back(x, dim);
	}
	else back(x, dim) = xb, fwd(x, dim) = xf;
      }
      else
      { OBJECT start_group, zlink, m;  BOOLEAN dble_found;  LENGTH b, f, dlen;
	start_group = nilobj;  dble_found = FALSE;  dlen = 0;
	debug0(DGP, DD, "  groups beginning.");
	FirstDefinite(x, link, y, jn);
	if( link != x )
	{
	  /* start first group, with or without join */
	  b = back(y, dim);
	  f = fwd(y, dim);
	  m = y;
	  start_group = link;
	  dble_found = !jn;
	  debug2(DGP, DD, "  starting first group: b = %s, f = %s",
	    EchoLength(b), EchoLength(f));
	
	  NextDefiniteWithGap(x, link, y, g, jn);
	  while( link != x )
	  {
	    if( !jn )
	    {
	      /* finish off and fix the group ending just before g */
	      debug2(DGP, DD, "  finishing group: b = %s, f = %s",
		EchoLength(b), EchoLength(f));
	      FixAndPrintObject(m, xmk+b, b, xf-b, dim, adjust,
		NO_SUPPRESS, padj, pg, count);
	      b = back(m, dim);  f = fwd(m, dim);
	      for( zlink = start_group;  zlink != link;  zlink=NextDown(zlink) )
	      { CountChild(z, zlink, count);
		if( !is_definite(type(z)) || z == m )  continue;
		FixAndPrintObject(z, xmk + b, b, xf - b, dim,
		  adjust, SUPPRESS, padj, pg, count);
		b = max(b, back(z, dim));  f = max(f, fwd(z, dim));
	      }
	      dlen = max(dlen, b + f);
	      dble_found = TRUE;
	      start_group = nilobj;

	      /* start new group */
	      b = back(y, dim);
	      f = fwd(y, dim);
	      m = y;
	      start_group = link;
	      debug2(DGP, DD, "  starting group: b = %s, f = %s",
		EchoLength(b), EchoLength(f));
	    }
	    else
	    {
	      /* continue with current group */
	      b = max(b, back(y, dim));
	      f = max(f, fwd(y, dim));
	      if( fwd(y, dim) > fwd(m, dim) )  m = y;
	      debug2(DGP, DD, "  continuing group: b = %s, f = %s",
		EchoLength(b), EchoLength(f));
	    }

	    NextDefiniteWithGap(x, link, y, g, jn);
	  }
	}
	assert( start_group != nilobj, "FAPO: final start_group!" );

	if( dble_found || !jn )
	{
	  /* finish off and fix this last group */
	  debug2(DGP, DD, "  finishing last group: b = %s, f = %s",
	      EchoLength(b), EchoLength(f));
	  FixAndPrintObject(m, xmk + b, b, xf - b, dim, adjust,
		NO_SUPPRESS, padj, pg, count);
	  b = back(m, dim);  f = fwd(m, dim);
	  for( zlink = start_group;  zlink != x;  zlink = NextDown(zlink) )
	  { CountChild(z, zlink, count);
	    if( !is_definite(type(z)) || z == m )  continue;
	    FixAndPrintObject(z, xmk + b, b, xf - b, dim, adjust,
		SUPPRESS, padj, pg, count);
	    b = max(b, back(z, dim));  f = max(f, fwd(z, dim));
	  }
	  dlen = max(dlen, b + f);
	  back(x, dim) = 0;  fwd(x, dim) = dlen;
	}
	else
	{
	  /* finish off and fix this last and only group */
	  debug2(DGP, DD, "  finishing last and only group: b = %s, f = %s",
	      EchoLength(b), EchoLength(f));
	  FixAndPrintObject(m, xmk, xb, xf, dim, adjust,
		 NO_SUPPRESS, padj, pg, count);
	  b = back(m, dim);  f = fwd(m, dim);
	  for( zlink = start_group;  zlink != x;  zlink = NextDown(zlink) )
	  { CountChild(z, zlink, count);
	    if( !is_definite(type(z)) || z == m )  continue;
	    FixAndPrintObject(z, xmk, xb, xf, dim, adjust,
		SUPPRESS, padj, pg, count);
	    b = max(b, back(z, dim));  f = max(f, fwd(z, dim));
	  }
	  back(x, dim) = b;  fwd(x, dim) = f;
	}
      }
      break;


    case ACAT:

      if( dim == COL )
      { BOOLEAN bad_gap, adjusting;
	LENGTH actual_size,
	adjust_indent, frame_size, back_edge, adjust_inc, inc, adjust_sofar;
	int adjustable_gaps, gaps_sofar;
	BOOLEAN underlining; int underline_xstart; FONT_NUM underline_font;
	OBJECT urec;
      

	/*********************************************************************/
	/*                                                                   */
	/*  The first step is to calculate the following values:             */
	/*                                                                   */
	/*    bad_gap          TRUE if an adjust-preventing gap is found     */
	/*                                                                   */
	/*    actual_size      the actual size of x;                         */
	/*                                                                   */
	/*    adjustable_gaps  the number of gaps to the right of the        */
	/*                     right-most tab gap.                           */
	/*                                                                   */
	/*  These make it easy to perform adjustment on a second pass, if    */
	/*  required.                                                        */
	/*                                                                   */
	/*********************************************************************/

	FirstDefinite(x, link, y, jn);
	if( link == x )  break;  /* no definite children, nothing to print */
	bad_gap = FALSE;
	adjustable_gaps = 0;
	back_edge = xmk - xb;
	mk = back_edge + back(y, dim);
	frame_size = xb + xf;
	prev = y;
	NextDefiniteWithGap(x, link, y, g, jn);
	while( link != x )
	{
	  save_actual_gap(g) = ActualGap(fwd(prev, dim), back(y, dim),
		fwd(y, dim), &gap(g), frame_size, mk - back_edge);
	  mk += save_actual_gap(g);
	  if( mode(gap(g)) == TAB_MODE || units(gap(g)) == AVAIL_UNIT
				       || units(gap(g)) == FRAME_UNIT )
	  { bad_gap = TRUE;
	  }
	  else if( width(gap(g)) > 0 )  adjustable_gaps += 1;
	  prev = y;
	  NextDefiniteWithGap(x, link, y, g, jn);
	}
	actual_size = mk + fwd(prev, dim) - back_edge;

	/*********************************************************************/
	/*                                                                   */
	/*  The second step is to work out whether adjusting is required     */
	/*  or not, and if so by how much, using the following variables:    */
	/*                                                                   */
	/*    adjusting        TRUE iff we are adjusting                     */
	/*                                                                   */
	/*    adjust_inc       The amount of adjustment to apply initially.  */
	/*                                                                   */
	/*    adjust_indent    initial indent for centring etc.              */
	/*                                                                   */
	/*  NB adjust_inc may be negative, if the optimal paragraph          */
	/*  breaker has chosen to shrink some gaps.                          */
	/*                                                                   */
	/*********************************************************************/

	adjust_indent = 0;
	switch( display_style(save_style(x)) )
	{
	  case DO_ADJUST:	padj = ALL_ADJUST;
				break;
	
	  case DISPLAY_CENTRE:	if( actual_size <= frame_size )
				{ adjust_indent = (frame_size - actual_size)/2;
				  padj = LAST_ADJUST;
				}
				else padj = ALL_ADJUST;
				debug1(DGP, DD, "cdisp %s", EchoObject(x));
				break;

	  case DISPLAY_RIGHT:	if( actual_size <= frame_size )
				{ adjust_indent = frame_size - actual_size;
				  padj = LAST_ADJUST;
				}
				else padj = ALL_ADJUST;
				debug1(DGP, DD, "rdisp %s", EchoObject(x));
				break;
	}

	if( padj == ALL_ADJUST && adjustable_gaps > 0 && !bad_gap )
	{ adjusting = TRUE;
	  adjust_inc = (frame_size - actual_size) / adjustable_gaps;
	  inc = max(adjust_inc, 0);
	  gaps_sofar = 0;	/* number of gaps adjusted so far */
	  adjust_sofar = 0;	/* total width of adjustments so far */
	}
	else
	{ adjusting = FALSE;
	  adjust_inc = inc = 0;
	}

	debug2(DGP, DD, "ACAT %s %s",
	  EchoStyle(&save_style(x)), EchoObject(x));
	debug3(DGP,DD,"frame_size = %s, actual_size = %s, adjustable_gaps = %d",
	  EchoLength(frame_size), EchoLength(actual_size), adjustable_gaps);
	debug2(DGP,DD,"bad_gap = %s, adjust_inc = %s",
	  bool(bad_gap), EchoLength(adjust_inc));
	debug3(DGP, DD, "frame_size = %d, actual_size = %d, adjust_inc = %d",
	  frame_size, actual_size, adjust_inc);

	/*********************************************************************/
	/*                                                                   */
	/*  The third and final step is to traverse x, fixing subobjects.    */
	/*                                                                   */
	/*********************************************************************/

	underlining = FALSE;
	FirstDefinite(x, link, y, jn);
	prev = y;
	mk = xmk - back(x, dim) + back(y, dim) + adjust_indent;
	NextDefiniteWithGap(x, link, y, g, jn);
	while( link != x )
	{
	  /* check for underlining */
	  if( underline(prev) )
	  { underline(prev) = FALSE;
	    if( !underlining )
	    {
	      /* underlining begins here */
	      underlining = TRUE;
	      underline_font = is_word(type(prev)) ? word_font(prev) :
		  font(save_style(x));
	      underline_xstart = mk - back(prev, dim);
	    }
	    if( !underline(g) )
	    {
	      /* underlining ends here */
	      urec = New(UNDER_REC);
	      back(urec, COL) = underline_xstart;
	      fwd(urec, COL) = mk + fwd(prev, dim);
	      back(urec, ROW) = underline_font;
	      underlining = FALSE;
	      Link(Up(prev), urec);
	    }
	  }

	  /* fix previous definite now we know it is not the last one  */
	  FixAndPrintObject(prev, mk, back(prev, dim),
	      fwd(prev, dim) + (width(gap(g)) > 0 ? inc : 0),
	      dim, adjust, NO_SUPPRESS, LAST_ADJUST, pg, count);

	  /* move on to next subobject */
	  if( adjusting && width(gap(g)) > 0 )
	  { int tmp;
	    gaps_sofar++;
	    tmp = ((frame_size - actual_size) * gaps_sofar) / adjustable_gaps;
	    mk += save_actual_gap(g) + (tmp - adjust_sofar);
	    adjust_sofar = tmp;
	  }
	  else
	    mk += save_actual_gap(g);
	  prev = y;
	  NextDefiniteWithGap(x, link, y, g, jn);
	}

	/* check for underlining */
	if( underline(prev) )
	{ underline(prev) = FALSE;
	  if( !underlining )
	  {
	    /* underlining begins here */
	    underlining = TRUE;
	    underline_font = is_word(type(prev)) ? word_font(prev) :
		  font(save_style(x));
	    underline_xstart = mk - back(prev, dim);
	  }

	  /* underlining must end here */
	  urec = New(UNDER_REC);
	  back(urec, COL) = underline_xstart;
	  fwd(urec, COL) = mk + fwd(prev, dim);
	  back(urec, ROW) = underline_font;
	  underlining = FALSE;
	  Link(Up(prev), urec);
	}

	/* fix the last definite subobject, prev, which must exist */
	FixAndPrintObject(prev, mk, back(prev, dim),
	  frame_size - (mk - xmk) - back(x, dim),
	  dim, adjust, NO_SUPPRESS, LAST_ADJUST, pg, count);

      }
      else for( link = Down(x);  link != x;  link = NextDown(link) )
      {	Child(y, link);
	if( !is_definite(type(y)) )
	{
	  if( type(y) == UNDER_REC )   /* generate an underline now */
	    PrintUnderline(back(y, ROW), back(y, COL), fwd(y, COL), pg - xmk);
	  continue;
	}
	FixAndPrintObject(y, xmk, xb, xf, dim, adjust, NO_SUPPRESS,
		padj,pg,count);
      }
      back(x, dim) = xb;  fwd(x, dim) = xf;
      break;


    case COL_THR:
    case ROW_THR:

      /* find and delete the child number count of y */
      assert( (type(x) == COL_THR) == (dim == COL), "FixAndPrintObject: thr!" );
      for( link = Down(x), uplink = Up(x), i = 1;
	link != x && uplink != x && i < count;
	link = NextDown(link), uplink = NextUp(uplink), i++ );
      assert( link != x && uplink != x, "FixAndPrintObject: link or uplink!" );
      CountChild(y, link, count);
      MoveLink(uplink, link, CHILD);  DeleteLink(link);  /* IMPORTANT!!! */
      assert( type(y) != GAP_OBJ, "FAPO: THR!");

      /* assign size if not done previously */
      if( thr_state(x) != FINALSIZE )
      {	back(x, dim) = xb;  fwd(x, dim) = xf;
	thr_state(x) = FINALSIZE;
      }

      /* fix y */
      FixAndPrintObject(y, xmk, back(x, dim), fwd(x, dim), dim, LAST_ADJUST,
	NO_SUPPRESS, padj, pg, count);
      if( Up(x) == x )  Dispose(x);
      break;


    default:
    
      Error(23, 3, "FixAndPrintObject: %s", INTERN, no_fpos, Image(type(x)));
      break;

  } /* end switch */
  debug2(DGP, D, "] FixAndPrintObject returning (size now %s,%s).",
	EchoLength(back(x, dim)), EchoLength(fwd(x, dim)));
} /* end FixAndPrintObject */
