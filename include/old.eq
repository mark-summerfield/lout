
###############################################################################
#                                                                             #
#  Lout @Eq package for equation formatting (Version 3.0)                     #
#                                                                             #
#  Version 1.0 by Jeffrey H. Kingston, December 1990.                         #
#  Version 2.0 by Jeffrey H. Kingston, 22 December 1992.                      #
#  Version 3.0 by Jeffrey H. Kingston and Robert Marsa, March 1996.           #
#                                                                             #
#  This package makes extensive use of the Adobe Systems Symbol font, and     #
#  it assumes that the font has not been recoded.  It could be rewritten      #
#  using the @Char symbol to be made independent of any recoding, but since   #
#  there seems no reason to ever recode this font, I haven't bothered.        #
#                                                                             #
#  See "Eq - a Lout package for typesetting mathematics" for user             #
#  information.  Acknowledgement:  the @Eq language is based closely on       #
#  the Eqn language of B. W. Kernighan and L. L. Cherry; the spacing rules    #
#  are similar to those of the TeX system by D. E. Knuth.                     #
#                                                                             #
#  Version 3.0 makes use of the new x and y units of measurement to improve   #
#  the spacing rules.                                                         #
#                                                                             #
###############################################################################

export	"`" "``" "```" bin rel punct non vctr big

	space exclam universal numbersign existential percent
	ampersand suchthat parenleft parenright asteriskmath
	plus comma minus period slash zero one two three four
	five six seven eight nine colon semicolon less equal
	greater question congruent Alpha Beta Chi Delta Epsilon
	Phi Gamma Eta Iota thetaone Kappa Lambda Mu Nu Omicron
	Pi Theta Rho Sigma Tau Upsilon sigmaone Omega Xi Psi Zeta
	bracketleft therefore bracketright perpendicular underscore
	radicalex alpha beta chi delta epsilon phi gamma eta iota
	phione kappa lambda mu nu omicron pi theta rho sigma tau
	upsilon omegaone omega xi psi zeta braceleft bar braceright
	similar Upsilonone minute lessequal fraction infinity florin
	club diamond heart spade arrowboth arrowleft arrowup
	arrowright arrowdown degree plusminus second greaterequal
	multiply proportional partialdiff bullet divide notequal
	equivalence approxequal ellipsis arrowvertex arrowhorizex
	carriagereturn aleph Ifraktur Rfraktur weierstrass
	circlemultiply circleplus emptyset intersection union
	propersuperset reflexsuperset notsubset propersubset
	reflexsubset element notelement angle gradient registerserif
	copyrightserif trademarkserif product radical dotmath
	logicalnot logicaland logicalor arrowdblboth arrowdblleft
	arrowdblup arrowdblright arrowdbldown lozenge angleleft
	registersans copyrightsans trademarksans summation parenlefttp
	parenleftex parenleftbt bracketlefttp bracketleftex
	bracketleftbt bracelefttp braceleftmid braceleftbt braceex
	angleright integral integraltp integralex integralbt
	parenrighttp parenrightex parenrightbt bracketrighttp
	bracketrightex bracketrightbt bracerighttp bracerightmid
	bracerightbt

	hbar Re Im partial infty prime nabla surd top bot dbar
	triangle backslash forall exists neg circle square

	"0" "1" "2" "3" "4" "5" "6" "7" "8" "9"

	sum prod coprod int oint bcap bcup bvee bwedge bodot botimes
	boplus buplus

	"+" "-" "+-" "-+" setminus cdot times "*" circ div cap cup uplus
	sqcap sqcup triangleleft triangleright wr bigcirc bigtriangleup
	bigtriangledown vee wedge oplus ominus otimes oslash odot dagger
	daggerdbl amalg

	"<" ">" "=" "<=" prec preceq "<<" subset subseteq sqsubseteq
	in vdash smile frown ">=" succ succeq ">>" supset supseteq
	sqsupseteq ni dashv mid parallel "==" "~" "-~" asymp "~~"
	"=~" bowtie propto models doteq perp notsub notin "!=" not
	"<->" "<--" "-->" up down "<=>" "<==" "==>" dblup dbldown
	":" "::" ":="

	lpar blpar rpar brpar lbrack blbrack rbrack brbrack lbrace blbrace
	rbrace brbrace lfloor blfloor rfloor brfloor lceil blceil
	rceil brceil langle blangle rangle brangle

	";" "," col
	
	"!" "?" "%" "(" ")" "[" "]"

	arccos arcsin arctan arg cos cosh cot coth csc deg det dim exp
	gcd hom inf ker lg lim liminf limsup ln log max min Pr sec sin
	sinh supr tan tanh mod ldots cdots vdots ddots del grad
	"..." ",...," "'" "''" "'''" "''''" empty
	
	leftarrow longleftarrow dblleftarrow dbllongleftarrow
	rightarrow longrightarrow dblrightarrow dbllongrightarrow
	leftrightarrow longleftrightarrow dblleftrightarrow dbllongleftrightarrow
	mapsto longmapsto hookleftarrow hookrightarrow leadsto
	leftharpoonup rightharpoonup leftharpoondown rightharpoondown
	rightleftharpoons
	uparrow dbluparrow downarrow dbldownarrow updownarrow dblupdownarrow
	nearrow searrow swarrow nwarrow

	sup sub tsub supp on ton frac half third over from to widefrom wideto
	dot dotdot hat tilde vec dyad overbar underbar sqrt root
	nextcol above labove cabove rabove mabove
	matrix pmatrix bmatrix brmatrix fmatrix cmatrix amatrix

def @Eq                  
    body @Body
@Begin


    ###################################################################
    #                                                                 #
    #  Context-sensitive format changes.                              #
    #                                                                 #
    #  Equation formatting (according to Knuth) demands changes in    #
    #  the appearance of equations depending on context.  These are:  #
    #                                                                 #
    #     @Smaller x      Superscripts and subscripts are to be set   #
    #                     in a smaller font size.  The @Smaller       #
    #                     symbol implements this by changing the      #
    #                     f unit.                                     #
    #                                                                 #
    #     @HSqueeze x     The horizontal space surrounding binary     #
    #                     operators and relations is to be reduced    #
    #                     within superscripts and subscripts, etc.    #
    #                     The @HSqueeze symbol implements this by     #
    #                     changing the y unit, which is not used by   #
    #                     Lout but which is used by symbols @ThinGap, #
    #                     @MedGap and @ThickGap.                      #
    #                                                                 #
    #     @VSqueeze x     The vertical space taken by superscripts    #
    #                     and subscripts is to be reduced within      #
    #                     built-up fractions and under root signs.    #
    #                     The @VSqueeze symbol implements this by     #
    #                     changing the z unit, which is not used by   #
    #                     Lout but is used by the @SupGap symbol.     #
    #                                                                 #
    #  Knuth also recommends some changes that depend on whether the  #
    #  equation is displayed or inline; these are not implemented.    #
    #                                                                 #
    ###################################################################

    def @SpaceGap { 0.05f  }

    def @Smaller  right x { 0.7f @Font @SpaceGap @Space x }

    def @HSqueeze right x { 0.2f @YUnit x }

    def @VSqueeze right x { 0.7f @ZUnit x }

    def @SkewGap  { 0.05f  }
    def @SupGap   { 0.43zk }
    def @ThinGap  { 0.15y  }
    def @MedGap   { 0.20y  }
    def @ThickGap { 0.25y  }
    def @ColGap   { 0.8f   }
    def @RowGap   { 0.5f   }

    def "`"       { &@ThinGap  }
    def "``"      { &@MedGap   }
    def "```"     { &@ThickGap }

    def bin	right x { ``  x ``  }
    def rel	right x { ``` x ``` }
    def punct	right x {     x `   }
    def non	right x { 0c @YUnit x }
    def big	right x { 1.3f @Font @SpaceGap @Space x }

    def @Base   right x { Base @Font x }
    def @Sym    right x { {Symbol Base} @Font x }

    def @HLine
	named line { "0.05 ft setlinewidth" }
    {  
	{ "0 0 moveto xsize 0 lineto" line "stroke" } @Graphic {}
    }

    def @VLine
    {
	"0 0 moveto 0 ysize lineto 0.05 ft setlinewidth stroke" @Graphic {}
    }

    def vctr
	right x
    {
	0.5w @VShift x
    }

    def @Strut right x
    {
	@OneCol { x | @OneRow { 0.5f @High ^/ 0.5f @High } }
    }

    ###################################################################
    #                                                                 #
    #   Full names                                                    #
    #                                                                 #
    #   These symbols and their names are taken directly from the     #
    #   Adobe Systems Inc. Symbol font (see PostScript Language       #
    #   Reference Manual, pp. 256-257).  The only differences are:    #
    #                                                                 #
    #      Adobe:  theta1        Eq:  thetaone                        #
    #              sigma1             sigmaone                        #
    #              phi1               phione                          #
    #              omega1             omegaone                        #
    #                                                                 #
    #   These were needed since Lout identifiers do not have digits.  #
    #                                                                 #
    ###################################################################

    def space           { @Sym "\040"  }
    def exclam          { @Sym "\041"  }
    def universal       { @Sym "\042"  }
    def numbersign      { @Sym "\043"  }
    def existential     { @Sym "\044"  }
    def percent         { @Sym "\045"  }
    def ampersand       { @Sym "\046"  }
    def suchthat        { @Sym "\047"  }
    def parenleft       { @Sym "\050"  }
    def parenright      { @Sym "\051"  }
    def asteriskmath    { @Sym "\052"  }
    def plus            { @Sym "+"     }
    def comma           { @Sym "\054"  }
    def minus           { @Sym "-"     }
    def period          { @Sym "\056"  }
    def slash           { @Sym "\057"  }
    def zero            { @Sym "\060"  }
    def one             { @Sym "\061"  }
    def two             { @Sym "\062"  }
    def three           { @Sym "\063"  }
    def four            { @Sym "\064"  }
    def five            { @Sym "\065"  }
    def six             { @Sym "\066"  }
    def seven           { @Sym "\067"  }
    def eight           { @Sym "\070"  }
    def nine            { @Sym "\071"  }
    def colon           { @Sym "\072"  }
    def semicolon       { @Sym "\073"  }
    def less            { @Sym "\074"  }
    def equal           { @Sym "\075"  }
    def greater         { @Sym "\076"  }
    def question        { @Sym "\077"  }
    def congruent       { @Sym "\100"  }
    def Alpha           { @Sym "\101"  }
    def Beta            { @Sym "\102"  }
    def Chi             { @Sym "\103"  }
    def Delta           { @Sym "\104"  }
    def Epsilon         { @Sym "\105"  }
    def Phi             { @Sym "\106"  }
    def Gamma           { @Sym "\107"  }
    def Eta             { @Sym "\110"  }
    def Iota            { @Sym "\111"  }
    def thetaone        { @Sym "\112"  }
    def Kappa           { @Sym "\113"  }

    def Lambda          { @Sym "\114"  }
    def Mu              { @Sym "\115"  }
    def Nu              { @Sym "\116"  }
    def Omicron         { @Sym "\117"  }
    def Pi              { @Sym "\120"  }
    def Theta           { @Sym "\121"  }
    def Rho             { @Sym "\122"  }
    def Sigma           { @Sym "\123"  }
    def Tau             { @Sym "\124"  }
    def Upsilon         { @Sym "\125"  }
    def sigmaone        { @Sym "\126"  }
    def Omega           { @Sym "\127"  }
    def Xi              { @Sym "\130"  }
    def Psi             { @Sym "\131"  }
    def Zeta            { @Sym "\132"  }
    def bracketleft     { @Sym "\133"  }
    def therefore       { @Sym "\134"  }
    def bracketright    { @Sym "\135"  }
    def perpendicular   { @Sym "\136"  }
    def underscore      { @Sym "\137"  }
    def radicalex       { @Sym "\140"  }
    def alpha           { @Sym "\141"  }
    def beta            { @Sym "\142"  }
    def chi             { @Sym "\143"  }
    def delta           { @Sym "\144"  }
    def epsilon         { @Sym "\145"  }
    def phi             { @Sym "\146"  }
    def gamma           { @Sym "\147"  }
    def eta             { @Sym "\150"  }
    def iota            { @Sym "\151"  }
    def phione          { @Sym "\152"  }
    def kappa           { @Sym "\153"  }
    def lambda          { @Sym "\154"  }
    def mu              { @Sym "\155"  }
    def nu              { @Sym "\156"  }

    def omicron         { @Sym "\157"  }
    def pi              { @Sym "\160"  }
    def theta           { @Sym "\161"  }
    def rho             { @Sym "\162"  }
    def sigma           { @Sym "\163"  }
    def tau             { @Sym "\164"  }
    def upsilon         { @Sym "\165"  }
    def omegaone        { @Sym "\166"  }
    def omega           { @Sym "\167"  }
    def xi              { @Sym "\170"  }
    def psi             { @Sym "\171"  }
    def zeta            { @Sym "\172"  }
    def braceleft       { @Sym "\173"  }
    def bar             { @Sym "\174"  }
    def braceright      { @Sym "\175"  }
    def similar         { @Sym "\176"  }
    def Upsilonone      { @Sym "\241"  }
    def minute          { @Sym "\242"  }
    def lessequal       { @Sym "\243"  }
    def fraction        { @Sym "\244"  }
    def infinity        { "1.2f" @Font @Sym "\245"  }
    def florin          { @Sym "\246"  }
    def club            { @Sym "\247"  }
    def diamond         { @Sym "\250"  }
    def heart           { @Sym "\251"  }
    def spade           { @Sym "\252"  }
    def arrowboth       { @Sym "\253"  }
    def arrowleft       { @Sym "\254"  }
    def arrowup         { @Sym "\255"  }
    def arrowright      { @Sym "\256"  }
    def arrowdown       { @Sym "\257"  }
    def degree          { @Sym "\260"  }
    def plusminus       { @Sym "\261"  }
    def second          { @Sym "\262"  }
    def greaterequal    { @Sym "\263"  }

    def multiply        { @Sym "\264"  }
    def proportional    { @Sym "\265"  }
    def partialdiff     { @Sym "\266"  }
    def bullet          { @Sym "\267"  }
    def divide          { @Sym "\270"  }
    def notequal        { @Sym "\271"  }
    def equivalence     { @Sym "\272"  }
    def approxequal     { @Sym "\273"  }
    def ellipsis        { @Sym "\274"  }
    def arrowvertex     { @Sym "\275"  }
    def arrowhorizex    { @Sym "\276"  }
    def carriagereturn  { @Sym "\277"  }
    def aleph           { @Sym "\300"  }
    def Ifraktur        { @Sym "\301"  }
    def Rfraktur        { @Sym "\302"  }
    def weierstrass     { @Sym "\303"  }
    def circlemultiply  { @Sym "\304"  }
    def circleplus      { @Sym "\305"  }
    def emptyset        { @Sym "\306"  }
    def intersection    { @Sym "\307"  }
    def union           { @Sym "\310"  }
    def propersuperset  { @Sym "\311"  }
    def reflexsuperset  { @Sym "\312"  }
    def notsubset       { @Sym "\313"  }
    def propersubset    { @Sym "\314"  }
    def reflexsubset    { @Sym "\315"  }
    def element         { @Sym "\316"  }
    def notelement      { @Sym "\317"  }
    def angle           { @Sym "\320"  }
    def gradient        { @Sym "\321"  }
    def registerserif   { @Sym "\322"  }
    def copyrightserif  { @Sym "\323"  }
    def trademarkserif  { @Sym "\324"  }
    def product         { @Sym "\325"  }
    def radical         { @Sym "\326"  }
    def dotmath         { @Sym "\327"  }

    def @PureDot   # dot with no extra space
    {
	@HContract { &0io 0.4w @HShift dotmath }
    }

    def logicalnot      { @Sym "\330"  }
    def logicaland      { @Sym "\331"  }
    def logicalor       { @Sym "\332"  }
    def arrowdblboth    { @Sym "\333"  }
    def arrowdblleft    { @Sym "\334"  }
    def arrowdblup      { @Sym "\335"  }
    def arrowdblright   { @Sym "\336"  }
    def arrowdbldown    { @Sym "\337"  }
    def lozenge         { @Sym "\340"  }
    def angleleft       { @Sym "\341"  }
    def registersans    { @Sym "\342"  }
    def copyrightsans   { @Sym "\343"  }
    def trademarksans   { @Sym "\344"  }
    def summation       { @Sym "\345"  }
    def parenlefttp     { @Sym "\346"  }
    def parenleftex     { @Sym "\347"  }
    def parenleftbt     { @Sym "\350"  }
    def bracketlefttp   { @Sym "\351"  }
    def bracketleftex   { @Sym "\352"  }
    def bracketleftbt   { @Sym "\353"  }
    def bracelefttp     { @Sym "\354"  }
    def braceleftmid    { @Sym "\355"  }
    def braceleftbt     { @Sym "\356"  }
    def braceex         { @Sym "\357"  }
    def angleright      { @Sym "\361"  }
    def integral        { @Sym "\362"  }
    def integraltp      { @Sym "\363"  }
    def integralex      { @Sym "\364"  }
    def integralbt      { @Sym "\365"  }
    def parenrighttp    { @Sym "\366"  }
    def parenrightex    { @Sym "\367"  }
    def parenrightbt    { @Sym "\370"  }
    def bracketrighttp  { @Sym "\371"  }
    def bracketrightex  { @Sym "\372"  }
    def bracketrightbt  { @Sym "\373"  }
    def bracerighttp    { @Sym "\374"  }
    def bracerightmid   { @Sym "\375"  }
    def bracerightbt    { @Sym "\376"  }


    ###################################################################
    #                                                                 #
    #   Short names                                                   #
    #                                                                 #
    #   These symbols, their names, and their spacing, are based on   #
    #   the list in Appendix F of Donald E. Knuth's The TeXBook.      #
    #                                                                 #
    #   Group 1 (lowercase Greek letters):  see full names above      #
    #   Group 2 (uppercase Greek letters):  see full names above      #
    #   Group 3 (calligraphic capitals):    not provided by Eq        #
    #                                                                 #
    ###################################################################

    ###################################################################
    #                                                                 #
    #   Group 4 (miscellaneous Ord symbols)                           #
    #                                                                 #
    #   Not all of Knuth's symbols are available.  The four suits     #
    #   (heartsuit, etc.), have definitions above.                    #
    #                                                                 #
    ###################################################################

    def hbar         { @OneCol { &0.1f @Base "-" ^/0.25fo h }	}
    def Re           { Rfraktur					}
    def Im           { Ifraktur					}
    def partial      { partialdiff				}
    def infty        { infinity					}
    def prime        { minute        				}
   #def emptyset     { defined above				}
    def nabla        { gradient					}
    def surd         { radical					}
    def top          { 180d @Rotate perpendicular		}
    def bot          { perpendicular				}
    def dbar         { @Base "||"                         	}
   #def angle        { defined above				}
    def backslash    { "\\"					}
    def forall       { universal					}
    def exists       { existential				}
    def neg          { logicalnot				}

    def circle       { @HContract @VContract
		      { "xsize ysize 2 div moveto"
			"xsize 2 div ysize 2 div xsize 2 div 0 360 arc"
			"0.04 ft setlinewidth stroke"
		      }
		      @Graphic { 0.7f @Wide 0.3f @High ^/ 0.3f @High }
		     }

    def square       { @HContract @VContract
		      { "0 0 moveto xsize 0 lineto xsize ysize lineto"
			"0 ysize lineto closepath"
			"0.04 ft setlinewidth stroke"
		      }
		      @Graphic { 0.6f @Wide 0.3f @High ^/ 0.3f @High }
		     }

    def triangle     { @HContract @VContract
		      { "0 0 moveto xsize 0 lineto"
		        "xsize 2 div ysize lineto closepath"
			"0.04 ft setlinewidth stroke"
		      }
		      @Graphic
		      { 0.3f @Wide 0.3f @High ^| ^/
		        0.3f @Wide 0.3f @High
		      }
		     }

    ###################################################################
    #                                                                 #
    #   Group 5 (digits)                                              #
    #                                                                 #
    ###################################################################

    def "0" { zero            }
    def "1" { one             }
    def "2" { two             }
    def "3" { three           }
    def "4" { four            }
    def "5" { five            }
    def "6" { six             }
    def "7" { seven           }
    def "8" { eight           }
    def "9" { nine            }


    ###################################################################
    #                                                                 #
    #   Group 6 ("Large" operators)                                   #
    #                                                                 #
    #   Knuth's large operators automatically change size depending   #
    #   on whether the equation is display or inline.  Eq does not    #
    #   do this; instead, the `big' operator must be used.            #
    #                                                                 #
    ###################################################################

    def sum	{ summation					}
    def prod	{ product					}
    def coprod	{ 180d @Rotate vctr product			}
    def int	{ 1.3f @Font vctr integral			}
    def oint	{ @OneCol { vctr degree |0.015fo int }		}
    def bcap	{ 1.3f @Font intersection			}
    def bcup	{ 1.3f @Font union				}
    def bvee	{ 1.3f @Font logicalor				}
    def bwedge	{ 1.3f @Font logicaland				}
    def bodot	{ & 1.3f @Font @HContract { circle /0io &0.5rt @PureDot } }
    def botimes	{ 1.3f @Font circlemultiply			}
    def boplus	{ 1.3f @Font circleplus				}
    def buplus	{ & 1.3f @Font @HContract { &0.5rt 0.7f @Font plus ^/0.2fo union } }

    ###################################################################
    #                                                                 #
    #   Group 7 (binary operations)                                   #
    #                                                                 #
    #   All of Knuth's symbols are available except \star, \diamond   #
    #   and \bullet; a few have been given more mnemonic names.       #
    #                                                                 #
    ###################################################################

    def "+"		{ bin plus				}
    def "-"		{ bin minus				}
    def "+-"		{ bin plusminus				}
    def "-+"		{ bin 180d @Rotate plusminus		}
    def setminus		{ bin backslash				}
    def cdot		{ bin dotmath				}
    def times		{ bin multiply				}
    def "*"		{ bin asteriskmath			}
   #def diamond		{ name used above			}
    def circ		{ bin circle				}
   #def bullet		{ name used above			}
    def div		{ bin divide				}
    def cap		{ bin intersection			}
    def cup		{ bin union				}
    def uplus		{ bin @OneRow @HContract { &0.5rt 0.7f @Font plus ^/0.2fo union}}
    def sqcap		{ bin
			  { @HContract @VContract
			    {	"0 0 moveto 0 ysize lineto xsize ysize lineto"
				"xsize 0 lineto"
				"0.04 ft setlinewidth stroke"
			    }
			    @Graphic
			    {	0.3f @Wide 0.3f @High ^| ^/
				0.3f @Wide 0.3f @High
			    }
			  }
			}
    def sqcup		{ 180d @Rotate sqcap			}
    def triangleleft	{ bin 90d @Rotate 0.8f @Font triangle	}
    def triangleright	{ bin "-90d" @Rotate 0.8f @Font triangle}
    def wr		{ bin vctr {90d @Rotate similar}	}
    def bigcirc		{ bin 1.2f @Font circle			}
    def bigtriangleup	{ bin 1.2f @Font triangle		}
    def bigtriangledown	{ bin 180d @Rotate 1.2f @Font triangle	}
    def vee		{ bin logicalor				}
    def wedge		{ bin logicaland			}
    def oplus		{ bin circleplus			}
    def ominus		{ bin @OneRow @HContract { circle /0io &0.5rt minus}}
    def otimes		{ bin circlemultiply			}
    def oslash		{`vctr 60d @Rotate @HContract {circle /0io &0.5rt minus`}}
    def odot		{ bin @OneRow @HContract {circle /0io &0.5rt @PureDot }}
    def dagger		{ bin @Base @Char "dagger"		}
    def daggerdbl	{ bin @Base @Char "daggerdbl"		}
    def amalg		{ bin 180d @Rotate vctr product		}

    ###################################################################
    #                                                                 #
    #   Group 8 (relations)                                           #
    #                                                                 #
    #   All Knuth's operators are available, but many have been       #
    #   given different, more mnemonic names.  Also included is       #
    #   a not operator for negating the relations.                    #
    #                                                                 #
    ###################################################################

    def "<"		{ rel less				}
    def ">"		{ rel greater				}
    def "="		{ rel equal				}
    def "<="		{ rel lessequal				}
    def prec		{ rel { 0.45f @Font "-90d" @Rotate
				{ parenrighttp ^| parenlefttp }
			      }
			}
    def preceq		{ rel { @OneRow non prec /0.1f minus }	}
    def "<<"		{ rel {less less}			}
    def subset		{ rel propersubset			}
    def subseteq	{ rel reflexsubset			}
    def sqsubseteq	{ rel @HContract @VContract
			  {	{ "xsize 0 moveto"
				  "0 0 lineto"
				  "0 ysize lineto"
				  "xsize ysize lineto"
				  "0.04 ft setlinewidth stroke"
				}
				@Graphic
				{ 0.5f @Wide 0.25f @High ^/
				  0.25f @High
				}
			    /0.1f minus
			  }
			}

    def in		{ rel element				}
    def vdash		{ rel vctr{"-90d" @Rotate perpendicular}}
    def smile		{ rel vctr 90d @Rotate parenleft	}
    def frown		{ rel vctr 90d @Rotate parenright	}

    def ">="		{ rel greaterequal			}
    def succ		{ rel { 0.45f @Font 90d @Rotate
			        { parenrighttp ^| parenlefttp }
			      }
			}
    def succeq		{ rel { @OneRow non succ /0.1f minus }	}
    def ">>"		{ rel {greater greater}			}
    def supset		{ rel propersuperset			}
    def supseteq	{ rel reflexsuperset			}
    def sqsupseteq	{ rel @HContract @VContract
			  {	{ "0 0 moveto xsize 0 lineto"
				  "xsize ysize lineto"
				  "0 ysize lineto"
				  "0.04 ft setlinewidth stroke"
				}
				@Graphic
				{ 0.5f @Wide 0.25f @High ^/
				  0.25f @High
				}
			    /0.1f minus
			  }
			}
    def ni		{ rel 180d @Rotate element		}
    def dashv		{ rel vctr {90d @Rotate perpendicular}	}
    def mid		{ rel @Base "|"				}
    def parallel	{ rel @Base "||"			}

    def "=="		{ rel equivalence			}
    def "~"		{ rel similar				}
    def "-~"		{ rel @OneRow{similar^/0.07f/0.07f minus}}
    def asymp		{ rel 0.7f @Font @OneRow
			      { 90d @Rotate parenleft ^/0.008f
			      /0.008f 90d @Rotate parenright }
			}
    def "~~"		{ rel approxequal			}
    def "=~"		{ rel congruent				}
    def bowtie		{ rel{non triangleright non triangleleft}}
    def propto		{ rel proportional			}
    def models		{ rel{@Base vctr "|" &0.05fo vctr equal}}
    def doteq		{ rel @OneRow @HContract {&0.5rt dotmath^/0.15f equal}}
    def perp		{ rel perpendicular			}

    def notsub		{ rel notsubset				}
    def notin		{ rel notelement			}
    def "!="		{ rel notequal				}

    def "<->"		{ rel arrowboth				}
    def "<--"		{ rel arrowleft				}
    def "-->"		{ rel arrowright			}
    def up		{ rel arrowup				}
    def down		{ rel arrowdown				}
    def "<=>"		{ rel arrowdblboth			}
    def "<=="		{ rel arrowdblleft			}
    def "==>"		{ rel arrowdblright			}
    def dblup		{ rel arrowdblup			}
    def dbldown		{ rel arrowdbldown			}

    def ":"		{ rel colon				}
    def "::"		{ rel @OneCol {colon ` colon}		}
    def ":="		{ rel { colon{ //0.05fo equal} }	}

    def not right x	{ @HContract {@OneCol x /0co &0.5rt slash}}


    ###################################################################
    #                                                                 #
    #   Groups 11 and 12 - openings and closings.                     #
    #                                                                 #
    ###################################################################

    def lpar	{ parenleft				}
    def rpar	{ parenright				}
    def lbrack	{ bracketleft				}
    def rbrack	{ bracketright				}
    def lbrace	{ braceleft				}
    def rbrace	{ braceright				}
    def lfloor	{ ` "-0.15f" @VShift bracketleftbt	}
    def rfloor	{   "-0.15f" @VShift bracketrightbt `	}
    def lceil	{ ` "-0.1f"  @VShift bracketlefttp	}
    def rceil	{   "-0.1f"  @VShift bracketrighttp `	}
    def langle	{ angleleft				}
    def rangle	{ angleright				}

    def blpar	{ @OneRow {parenlefttp    ^/ parenleftex    / parenleftbt   } }
    def brpar	{ @OneRow {parenrighttp   ^/ parenrightex   / parenrightbt  } }
    def blbrack	{ @OneRow {bracketlefttp  ^/ bracketleftex  / bracketleftbt } }
    def brbrack	{ @OneRow {bracketrighttp ^/ bracketrightex / bracketrightbt} }
    def blbrace	{ @OneRow {bracelefttp    ^/ braceleftmid   / braceleftbt   } }
    def brbrace	{ @OneRow {bracerighttp   ^/ bracerightmid  / bracerightbt  } }
    def blfloor	{ @OneRow {bracketleftex  ^/ bracketleftex  / bracketleftbt } }
    def brfloor	{ @OneRow {bracketrightex ^/ bracketrightex / bracketrightbt} }
    def blceil	{ @OneRow {bracketlefttp  ^/ bracketleftex  / bracketleftex } }
    def brceil	{ @OneRow {bracketrighttp ^/ bracketrightex / bracketrightex} }
    def blangle	{ @HContract @VContract
		  { "xsize 0 moveto"
		    "0 ysize 2 div lineto"
		    "xsize ysize lineto"
		    "0.04 ft setlinewidth stroke"
	          }
	          @Graphic { 0.5f @Wide 2f @High ^/ 2f @High }
		}
    def brangle	{ @HContract @VContract
		  { "0 0 moveto"
		    "xsize ysize 2 div lineto"
		    "0 ysize lineto"
		    "0.04 ft setlinewidth stroke"
	          }
	          @Graphic { 0.5f @Wide 2f @High ^/ 2f @High }
		}


    ###################################################################
    #                                                                 #
    #   Group 13 - punctuation.                                       #
    #                                                                 #
    ###################################################################

    def ";"     { punct semicolon     }
    def ","     { punct comma         }
    def col     { punct colon         }


    ###################################################################
    #                                                                 #
    #   Additional short symbols (Knuth p. 132)                       #
    #                                                                 #
    ###################################################################

    def "!" { exclam          }
    def "?" { question        }
    def "%" { percent         }
    def "(" { parenleft       }
    def ")" { parenright      }
    def "[" { bracketleft     }
    def "]" { bracketright    }


    ###################################################################
    #                                                                 #
    #   Common mathematical functions (from Knuth p. 162).            #
    #   mod is included, since @Rel mod is easily typed if needed.    #
    #                                                                 #
    ###################################################################

    def arccos	{ @Base "arccos"	}
    def arcsin	{ @Base "arcsin"	}
    def arctan	{ @Base "arctan"	}
    def arg	{ @Base "arg"		}
    def cos	{ @Base "cos"		}
    def cosh	{ @Base "cosh"		}
    def cot	{ @Base "cot"		}
    def coth	{ @Base "coth"		}
    def csc	{ @Base "csc"		}
    def deg	{ @Base "deg"		}
    def det	{ @Base "det"		}
    def dim	{ @Base "dim"		}
    def exp	{ @Base "exp"		}
    def gcd	{ @Base "gcd"		}
    def hom	{ @Base "hom"		}
    def inf	{ @Base "inf"		}
    def ker	{ @Base "ker"		}
    def lg	{ @Base "lg"		}
    def lim	{ @Base "lim"		}
    def liminf	{ @OneCol { @Base "lim" ` @Base "inf" }	}
    def limsup	{ @OneCol { @Base "lim" ` @Base "sup" }	}
    def ln	{ @Base "ln"		}
    def log	{ @Base "log"		}
    def max	{ @Base "max"		}
    def min	{ @Base "min"		}
    def Pr	{ @Base "Pr"		}
    def sec	{ @Base "sec"		}
    def sin	{ @Base "sin"		}
    def sinh	{ @Base "sinh"		}
    def supr	{ @Base "sup"		}
    def tan	{ @Base "tan"		}
    def tanh	{ @Base "tanh"		}
    def mod	{ @Base "mod"		}


    ###################################################################
    #                                                                 #
    #  Arrow symbols.                                                 #
    #                                                                 #
    ###################################################################

    def leftarrow		{ arrowleft }
    def longleftarrow		{ { 1.6 1 } @Scale arrowleft }
    def dblleftarrow		{ arrowdblleft }
    def dbllongleftarrow	{ { 1.6 1 } @Scale arrowdblleft }
    def rightarrow		{ arrowright }
    def longrightarrow		{ { 1.6 1 } @Scale arrowright }
    def dblrightarrow		{ arrowdblright }
    def dbllongrightarrow	{ { 1.6 1 } @Scale arrowdblright }
    def leftrightarrow		{ arrowboth }
    def longleftrightarrow	{ { 1.6 1 } @Scale arrowboth }
    def dblleftrightarrow	{ arrowdblboth }
    def dbllongleftrightarrow	{ { 1.6 1 } @Scale arrowdblboth }

    def mapsto
    {
	@HContract @VContract {
	    "0 ymark 0.16 ft sub moveto 0 ymark 0.16 ft add lineto stroke"
	    @Graphic arrowright
	}
    }

    def longmapsto
    {
	@HContract @VContract {
	    "0 ymark 0.16 ft sub moveto 0 ymark 0.16 ft add lineto stroke"
	    @Graphic { { 1.6 1 } @Scale arrowright }
	}
    }

    def hookleftarrow
    {
	@HContract @VContract {
	    "xsize ymark moveto xsize ymark 0.1 ft add 0.1 ft -90 90 arc stroke"
	    @Graphic leftarrow
	}
    }

    def hookrightarrow
    {
	@HContract @VContract {
	    "0 ymark moveto 0 0.1 ft ymark add 0.1 ft -90 90 arcn stroke"
	    @Graphic rightarrow
	}
    }

    def @ClipToSize right x
    {
	@HContract @VContract
	{
	"grestore newpath 0 0 moveto xsize 0 lineto xsize ysize lineto"
	"0 ysize lineto closepath clip gsave"
	} @Graphic x
    }

    def @ClipAboveMark
	left amount
	right x
    {
	@ClipToSize { ^//{{amount}o} x }
    }

    def @ClipBelowMark
	left amount
	right x
    {
	@ClipToSize { x //{{amount}o} }
    }

    def leftharpoonup
    {
	0.04f @ClipBelowMark leftarrow
    }

    def rightharpoonup
    {
	0.04f @ClipBelowMark rightarrow
    }

    def leftharpoondown
    {
	0.02f @ClipAboveMark leftarrow
    }

    def rightharpoondown
    {
	0.02f @ClipAboveMark rightarrow
    }

    def rightleftharpoons
    {
	@HContract @VContract {
		rightharpoonup
		^//0.1fo
		 //0.1fo
		leftharpoondown
	}
    }

    def leadsto		{ @HContract { similar &0.4fo arrowright } }

    def uparrow		{ arrowup }
    def dbluparrow	{ arrowdblup }
    def downarrow	{ arrowdown }
    def dbldownarrow	{ arrowdbldown }
    def updownarrow	{ @HContract { arrowup &0io arrowdown } }
    def dblupdownarrow	{ @VContract { arrowdblup ^//0.2fo arrowdbldown } }
    def nearrow		{ 0.5w @VShift 0.5w @HShift  45d @Rotate arrowright }
    def searrow		{ 0.5w @VShift 0.5w @HShift 315d @Rotate arrowright }
    def swarrow		{ 0.5w @VShift 0.5w @HShift 225d @Rotate arrowright }
    def nwarrow		{ 0.5w @VShift 0.5w @HShift 135d @Rotate arrowright }


    ###################################################################
    #                                                                 #
    #   Other symbols taken from TeX.                                 #
    #                                                                 #
    ###################################################################

    def ldots { .       &0.3f .       &0.3f .			}
    def cdots { dotmath &0.3f dotmath &0.3f dotmath		}
    def vdots { @OneRow { dotmath ^/0.3f dotmath /0.3f dotmath } }
    def ddots { @OneCol @OneRow
	       {        dotmath
	         ^/0.3f |0.3f dotmath
                  /0.3f |     |0.3f dotmath
	       }
	      }


    ###################################################################
    #                                                                 #
    #   Symbols taken from eqn (Kernighan and Cherry 1975).           #
    #                                                                 #
    ###################################################################

    def del	{ gradient			}
    def grad	{ gradient			}
    def "..."	{ ellipsis			}
    def ",...,"	{ , ellipsis ``` ,		}
    def "'"	{ minute			}
    def "''"	{ minute minute			}
    def "'''"	{ minute minute minute		}
    def "''''"	{ minute minute minute minute	}
    def empty	{ emptyset			}



    ###################################################################
    #                                                                 #
    #   Miscellaneous                                                 #
    #                                                                 #
    ###################################################################

    ###################################################################
    #                                                                 #
    #   Symbols with parameters.                                      #
    #                                                                 #
    #   These symbols are essentially those of eqn, with some         #
    #   changes and additions.                                        #
    #                                                                 #
    ###################################################################

    def sup
	precedence 60
	associativity left
	left x
	named gap { @SupGap }
	right y
    {
	@HContract @VContract
	{          | 0.45w @VShift @Smaller @HSqueeze @VSqueeze y
	  ^/gap  x
	}
    }

    def sub
	precedence 60
	associativity left
	left x
	named gap { @SupGap }
	right y
    {
	@HContract @VContract
	{
	       # x
	       "." @KernShrink x
	  /gap    |  @Smaller @HSqueeze @VSqueeze y
	}
    }

    def tsub
	precedence 60
	associativity left
	left x
	named gap { @SupGap }
	right y
    {
	@HContract @VContract
	{
	       x
	  /gap    |  &0io 0.2f @HShift @Smaller @HSqueeze @VSqueeze y
	}
    }

    def supp
	precedence 60
	associativity left
	left x
	named gap { @SupGap }
	right y
    {
	@HContract @VContract
	{
	    { ^/gap x /gap } |  y
	}
    }

    def on
	precedence 61
	associativity left
	left x
	named gap { @SupGap }
	right y
    {
	@Smaller @HSqueeze @VSqueeze x ^/  /
	@Smaller @HSqueeze @VSqueeze y 
    }

    def ton
	precedence 61
	associativity left
	left x
	named gap { @SupGap }
	right y
    {
	@Smaller @HSqueeze @VSqueeze x ^/  /
	&0io 0.3f @HShift @Smaller @HSqueeze @VSqueeze y
    }

    def frac
	precedence 54
	associativity left
	left x
	named gap { 0.2f }
	right y
    {
	@HContract @VContract @Smaller @HSqueeze @VSqueeze
	{ 1w @VShift { x /gap } | fraction &0io | 0w @VShift { |gap y }
	}
    }

    def half { 1 frac 2 }
    def third { 1 frac 3 }

    def over
	precedence 54
	associativity left
	left x
	named gap { 0.2f }
	right y
    {  
	@HContract @VContract
	{          |0.5rt @OneCol @VSqueeze x
	  ^//gap   @HLine
	   //gap   |0.5rt @OneCol @VSqueeze @Strut y
	}
    }

    def from
	precedence 58
	associativity left
	left x
	named gap { @ThinGap  }
	named skew { 0c }
	right y
    {  
	@HContract @VContract
	{          |0.5rt x
	   //gap   |0.5rt &skew @Smaller @HSqueeze @VSqueeze y
	}
    }

    def to
	precedence 58
	associativity left
	left x
	named gap { @ThinGap  }
	named skew { 0c }
	right y
    {
	@HContract @VContract
	{          |0.5rt &skew @Smaller @HSqueeze @VSqueeze y
	  ^//gap   |0.5rt x
	}
    }

    def widefrom
	precedence 58
	associativity left
	left x
	named gap { @ThinGap  }
	right y
    {
	@HContract @VContract
	{
	    x //gap @HScale y
	}
    }

    def wideto
	precedence 58
	associativity left
	left x
	named gap { @ThinGap  }
	right y
    {
	@HContract @VContract
	{
	    @HScale y ^//gap x
	}
    }

    def dot
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x to gap { gap } skew { @SkewGap } .
    }

    def dotdot
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x to gap { gap } skew { @SkewGap } ..
    }

    def hat
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x to gap { gap } skew { @SkewGap } @Base "^"
    }

    def tilde
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x to gap { gap } skew { @SkewGap } @Base "~"
    }

    def vec
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x to gap { gap } skew { @SkewGap } arrowright
    }

    def dyad
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x to gap { gap } skew { @SkewGap } arrowboth
    }

    def overbar
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x wideto gap { gap } minus
    }

    def underbar
	precedence 62
	left x
	named gap { @ThinGap }
    {
	x widefrom gap { gap } minus
    }

    def sqrt
	precedence 56
	named gap { @ThinGap }
	right x
    {
	@HContract @VContract
	{
	    @VScale surd | @OneRow
	    {
		@HLine line { "0.03 ft setlinewidth 2 setlinecap" }
		^//gap  |gap  @VSqueeze @Strut x # //gap
	    }
	}
    }

    def root
	precedence 56
	left x
	right y
    {
	"" sup x &0io sqrt y
    }

    def above
	precedence 52
	left x
	named gap { @RowGap }
	right y
    {
	|0.5rt x //gap |0.5rt y
    }

    def labove
	precedence 52
	left x
	named gap { @RowGap }
	right y
    {
	x //gap y
    }

    def cabove
	precedence 52
	left x
	named gap { @RowGap }
	right y
    {
	|0.5rt x //gap |0.5rt y
    }

    def rabove
	precedence 52
	left x
	named gap { @RowGap }
	right y
    {
	|1rt x //gap |1rt y
    }

    def mabove
	precedence 52
	left x
	named gap { @RowGap }
	right y
    {
	x /gap y
    }

    def nextcol
	precedence 50
	left x
	named gap { @ColGap }
	right y
    {
	x |gap y
    }

    export row axisrow col lcol ccol rcol mcol
    def matrix
	precedence 100
	named gap { @MedGap }
	named strut
	    named no  { }
	    named No  { }
	    named yes { 0.5f }
	    named Yes { 0.5f }
	{ No }
	named atleft {}
	named atright {}
	named userow { No }
	named shiftdelim { Yes }
	body x
    { 
	def @Strut
	{
	    strut @Case {
		"" @Yield {}
		else @Yield { @OneRow { strut @High ^/ strut @High } }
	    }
	}

	def newrow
	    precedence 50
	    associativity left
	    left x
	    right y
	{
	    x @Case {
		"" @Yield { y | @Strut }
		else @Yield { x /@RowGap y | @Strut }
	    }
	}

	macro row { newrow "" }

	def newaxisrow
	    precedence 50
	    associativity left
	    left x
	    right y
	{
	    x @Case {
		"" @Yield { y | @Strut }
		else @Yield { x ^/@RowGap y | @Strut }
	    }
	}

	macro axisrow { newaxisrow "" }

	def col
	    precedence 52
	    associativity left
	    left x
	    named indent { 0.5rt }
	    right y
	{
	    x @Case {
		""   @Yield {            &indent @OneCol y }
		else @Yield { x |@ColGap &indent @OneCol y }
	    }
	}

	def lcol
	    precedence 52
	    associativity left
	    left x
	    right y
	{
	    x col indent { 0i } y
	}

	def ccol
	    precedence 52
	    associativity left
	    left x
	    right y
	{
	    x col indent { 0.5rt } y
	}

	def rcol
	    precedence 52
	    associativity left
	    left x
	    right y
	{
	    x col indent { 1rt } y
	}

	def mcol
	    precedence 52
	    associativity left
	    left x
	    right y
	{
	    x @Case {
		""   @Yield {            @OneCol y }
		else @Yield { x |@ColGap @OneCol y }
	    }
	}

	def delim right x
	{
	    x @Case
	    {
		""   @Yield @Null
		else @Yield
		{
		    shiftdelim @Case {
		    { Yes yes } @Yield { @VScale x }
		    else        @Yield { @VCover x }
		    }
		}
	    }
	}

	@HContract @VContract {
	    delim atleft &@ThinGap
	    userow @Case {
		{Yes yes} @Yield @HContract @VContract {^//gap @OneRow x //gap}
		else      @Yield vctr @HContract @VContract { //gap x //gap }
	    }
	    &@ThinGap delim atright
	}
    }

    macro pmatrix  { matrix atleft { "1.5f" @Font ( } atright { "1.5f" @Font ) }}
    macro bmatrix  { matrix atleft { blbrack } atright { brbrack } }
    macro brmatrix { matrix atleft { blbrace } atright { brbrace } }
    macro fmatrix  { matrix atleft { blfloor } atright { brfloor } }
    macro cmatrix  { matrix atleft { blceil  } atright { brceil  } }
    macro amatrix  { matrix atleft { blangle } atright { brangle } }

    Slope @Font { separate @SpaceGap } @Space 1f @ZUnit 1f @YUnit @Body

@End @Eq                  

macro @E { @OneCol @Eq }
