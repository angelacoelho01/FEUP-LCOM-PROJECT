#pragma once

static xpm_row_t const pause_title[] = {
"280 95 32 1",
" 	c None",
".	c #060D35",
"+	c #110B2E",
"@	c #8C3613",
"#	c #D95100",
"$	c #3C1A26",
"%	c #EB5700",
"&	c #B24306",
"*	c #FF6B00",
"=	c #FF6500",
"-	c #FD5E00",
";	c #27132B",
">	c #E5814B",
",	c #793019",
"'	c #C54B00",
")	c #D49172",
"!	c #FFFFFF",
"~	c #CCB0A7",
"{	c #502122",
"]	c #DC885E",
"^	c #CCA697",
"/	c #E5E2E4",
"(	c #FF751A",
"_	c #D3C6C7",
":	c #F17A33",
"<	c #F0F0F2",
"[	c #CFBAB8",
"}	c #DBD4D6",
"|	c #FF6E00",
"1	c #65281D",
"2	c #A03D0E",
"3	c #D09984",
"..........................................................................................+@............................................................................................................................................................................................",
".............................+#$.........................................................+%&............................................................................................................................................................................................",
"............................+%*=$.......................................................+%*&............................................................................................................................................................................................",
"............................#***-;.....................................................+%**&............................................................................................................................................................................................",
"...........................#**>**-;...................................................+%***&............................................................................................................................................................................................",
",*********************;...'**)!~**-;.................................................+%****&,********************@...........&********************;.......................&*****************************={........{********************************************************************@",
",*********************;..&**]!!!~**-;...............................................+%**)>*&,********************@...........&********************;......................&*****************************=$.........{*******************************************************************{.",
",*********************;.&**>!!!!!^**-;.............................................+%**)!>*&,********************@...........&********************;.....................&*****************************=$..........{******************************************************************{..",
",**/!!!!!!!!!!!!!!!~**;@**>!!!!!!!^**-;...........................................+%**)!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;....................&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$...........{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)**=$...",
",**/!!!!!!!!!!!!!!!~**&**:!!!!!!!!!^**-;.........................................+%**)!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;...................&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)**-$....",
",**/!!!!!!!!!!!!!!!~****:<!!!!!!!!!!^**-;.......................................+%**)!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;..................&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$.............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>**-;.....",
",**/!!!!!!!!!!!!!!!~***:<!!!!!!!!!!!!^**-;.....................................+%**)!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.................&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$..............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>**%;......",
",**/!!!!!!!!!!!!!!!~**(/!!!!!!!!!!!!!!^**%+...................................+%**)!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;................&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$...............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!<:**%+.......",
",**/!!!!!!!!!!!!!!!~*(/!!!!!!!!!!!!!!!!^**%+.................................+%**)!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;...............&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!<:**#+........",
",**/!!!!!!!!!!!!!!!~(/!!!!!!!!!!!!!!!!!!)**%+...............................+%**)!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;..............&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$.................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!/(**#..........",
",**/!!!!!!!!!!!!!!![}!!!!!!!!!!!!!!!!!!!!)**%+.............................+%**)!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.............&**)!!!!!!!!!!!!!!!!!!!!!!!_**=$..................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!/(**'...........",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)**%+...........................+%**)!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;............&**)!!!!!!!!!!!!!!!!!!!!!!!}|*=$...................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}|**&............",
",**/!!!!!!!!!!!!!!!}<!!!!!!!!!!!!!!!!!!!!!!)**%+.........................+%**^!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;...........&**)!!!!!!!!!!!!!!!!!!!!!!!}|*=$....................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}|**@.............",
",**/!!!!!!!!!!!!!!!~:<!!!!!!!!!!!!!!!!!!!!!!)**%+.......................+%**^!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;..........&**)!!!!!!!!!!!!!!!!!!!!!!!}|*=$.....................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_***@..............",
",**/!!!!!!!!!!!!!!!~*:<!!!!!!!!!!!!!!!!!!!!!!)**%+.....................+%**^!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.........&**)!!!!!!!!!!!!!!!!!!!!!!!}|*=$......................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_***,...............",
",**/!!!!!!!!!!!!!!!~**:<!!!!!!!!!!!!!!!!!!!!!!)**%....................+%**^!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;........&**)!!!!!!!!!!!!!!!!!!!!!!!}|*=$.......................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~***,................",
",**/!!!!!!!!!!!!!!!~***:<!!!!!!!!!!!!!!!!!!!!!!]**#..................+%**^!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.......&**)!!!!!!!!!!!!!!!!!!!!!!!}|**{........................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~***{.................",
",**/!!!!!!!!!!!!!!!~****:<!!!!!!!!!!!!!!!!!!!!!!>**#................+%**^!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;......&**)!!!!!!!!!!!!!!!!!!!!!!!}|**{.........................{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**={..................",
",**/!!!!!!!!!!!!!!!~**#**:<!!!!!!!!!!!!!!!!!!!!!!>**#..............+%**^!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.....&**)!!!!!!!!!!!!!!!!!!!!!!!}|**{..........................{**/!!!!!!!!!!!!!!!_*****************************=$...................",
",**/!!!!!!!!!!!!!!!~**;&**:<!!!!!!!!!!!!!!!!!!!!!!>**#............+%**^!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;....&**)!!!!!!!!!!!!!!!!!!!!!!!}|**{...........................{**/!!!!!!!!!!!!!!!_****************************-$....................",
",**/!!!!!!!!!!!!!!!~**;.&**:<!!!!!!!!!!!!!!!!!!!!!!>**#..........+%**^!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;...&**)!!!!!!!!!!!!!!!!!!!!!!!}|**{............................{**/!!!!!!!!!!!!!!!_***************************-;.....................",
",**/!!!!!!!!!!!!!!!~**;..@**:<!!!!!!!!!!!!!!!!!!!!!!>**#........+%**^!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;..&**)!!!!!!!!!!!!!!!!!!!!!!!}|**{.............................{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!~**;...@**:<!!!!!!!!!!!!!!!!!!!!!!>**#......+%**^!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.@**)!!!!!!!!!!!!!!!!!!!!!!!}|**{..............................{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!~**;....@**:<!!!!!!!!!!!!!!!!!!!!!!:**#....+%**^!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*:!!!!!!!!!!!!!!!!!!!!!!!}|**{...............................{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!~**;....$=**_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!}|**{................................{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!~**;...$=**_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!}|**{.................................{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!~**;..$=**_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!}|**{..................................{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!~**;.$=**_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!/(**{...................................{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!~**;$=**_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!/(**************************************,{**/!!!!!!!!!!!!!!!_*********-;.......................................",
",**/!!!!!!!!!!!!!!!~**1=**_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!/(***************************************,{**/!!!!!!!!!!!!!!!_**********-;......................................",
",**/!!!!!!!!!!!!!!!~*****_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!/(****************************************,{**/!!!!!!!!!!!!!!!_***********-;.....................................",
",**/!!!!!!!!!!!!!!!~****_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!^**-;....................................",
",**/!!!!!!!!!!!!!!!~***_!!!!!!!!!!!!!!!!!!!!!!^**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!^**-;...................................",
",**/!!!!!!!!!!!!!!!~**_!!!!!!!!!!!!!!!!!!!!!!~**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!^**-;..................................",
",**/!!!!!!!!!!!!!!!~*_!!!!!!!!!!!!!!!!!!!!!!~**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**-;.................................",
",**/!!!!!!!!!!!!!!!~_!!!!!!!!!!!!!!!!!!!!!!~**=$..+%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*@...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**-;................................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(*2...........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**-;...............................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!(**,..........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**=$..............................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!}|**,.........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**=$.............................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!!}|**,........&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**=$............................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!!!}|**,.......&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**=$...........................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/^!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!!!!}|**,......&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**=$..........................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/()!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!!!!!}|**,.....&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$.........................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(*)!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!!!!!!}|**,....&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$........................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**)!!!!!!!!!!!!!!!!>*&,**!!!!!!!!!!!!!!!!!!!!!!}|**,...&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$.......................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(***)!!!!!!!!!!!!!!!!>*&,**~!!!!!!!!!!!!!!!!!!!!!!}|**,..&*>!!!!!!!!!!!!!!!_**;.&*>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$......................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**=*)!!!!!!!!!!!!!!!!>*&;-**~!!!!!!!!!!!!!!!!!!!!!!}|**,.&*>!!!!!!!!!!!!!!!_**;.&****************************************^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_***************************=$.....................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,#*)!!!!!!!!!!!!!!!!>*&.;-**~!!!!!!!!!!!!!!!!!!!!!!}|**,&*>!!!!!!!!!!!!!!!_**;.&****************************************^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_****************************={....................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,.#*)!!!!!!!!!!!!!!!!>*&..;-**~!!!!!!!!!!!!!!!!!!!!!!}|**-*>!!!!!!!!!!!!!!!_**;.&****************************************^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_******************************{...................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,..#*)!!!!!!!!!!!!!!!!>*&...;-**~!!!!!!!!!!!!!!!!!!!!!!}|***>!!!!!!!!!!!!!!!_**;........................................&*^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_**;...........................+...................",
",**/!!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,...#*)!!!!!!!!!!!!!!!!>*&....;-**~!!!!!!!!!!!!!!!!!!!!!!}|**>!!!!!!!!!!!!!!!_**;........................................&*^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,....#*)!!!!!!!!!!!!!!!!>*&.....;=**[!!!!!!!!!!!!!!!!!!!!!!}|*>!!!!!!!!!!!!!!!_**;........................................&*^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,.....#*)!!!!!!!!!!!!!!!!>*&......$=**_!!!!!!!!!!!!!!!!!!!!!!}|>!!!!!!!!!!!!!!!_**;........................................&*^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,......#*)!!!!!!!!!!!!!!!!>*&.......$=**_!!!!!!!!!!!!!!!!!!!!!!}]!!!!!!!!!!!!!!!_**;........................................#*^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,.......#*)!!!!!!!!!!!!!!!!>*&........$=**_!!!!!!!!!!!!!!!!!!!!!!<!!!!!!!!!!!!!!!_**;.......................................#**^!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,........#*)!!!!!!!!!!!!!!!!>*&.........$=**_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**;......................................#**|}!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_**;...............................................",
",**/!!!!!!!!!!!!!!!!!!~**=$..;-**^!!!!!!!!!!!!!!!!!!!!!!/(**,.........#*)!!!!!!!!!!!!!!!!>*&..........$=**_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**;..............,**************************}!!!!!!!!!!!!!!!!!!**,{**/!!!!!!!!!!!!!!!_***************************-$.....................",
",**/!!!!!!!!!!!!!!!!!~**=$....&**)!!!!!!!!!!!!!!!!!!!!!!!>**#.........#*)!!!!!!!!!!!!!!!!>*&...........$=**_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**;.............@**************************_!!!!!!!!!!!!!!!!!!~**,{**/!!!!!!!!!!!!!!!_****************************=$....................",
",**/!!!!!!!!!!!!!!!!~**=$......&**)!!!!!!!!!!!!!!!!!!!!!!!>**#........#*)!!!!!!!!!!!!!!!!>*&............$***_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**;............@**************************~!!!!!!!!!!!!!!!!!!~**-;{**/!!!!!!!!!!!!!!!_*****************************={...................",
",**/!!!!!!!!!!!!!!!_**=$........&**)!!!!!!!!!!!!!!!!!!!!!!!>**#.......#*)!!!!!!!!!!!!!!!!>*&.............{***}!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**;...........2**:<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**-;.{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!![***{..................",
",**/!!!!!!!!!!!!!!!~**{..........&**)!!!!!!!!!!!!!!!!!!!!!!!>**#......#*)!!!!!!!!!!!!!!!!>*&..............{**|}!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**;..........&**:<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**-;..{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_***1.................",
",**/!!!!!!!!!!!!!!!~**;...........'**)!!!!!!!!!!!!!!!!!!!!!!!>**#.....#*)!!!!!!!!!!!!!!!!>*&...............{**|}!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**-+.........'**>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**-;...{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_|**,................",
",**/!!!!!!!!!!!!!!!~**;............#**)!!!!!!!!!!!!!!!!!!!!!!!>**&....#*)!!!!!!!!!!!!!!!!>*&................{**|}!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**-;.........#**>!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**-;....{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}|**@...............",
",**/!!!!!!!!!!!!!!!~**;.............#**)!!!!!!!!!!!!!!!!!!!!!!!>**&...#*)!!!!!!!!!!!!!!!!>*&.................{**|}!!!!!!!!!!!!!!!!!!!!!!!!!!~**-;........+#**)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~**-;.....{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}(**@..............",
",**/!!!!!!!!!!!!!!!~**;..............#**)!!!!!!!!!!!!!!!!!!!!!!!>**&..#*)!!!!!!!!!!!!!!!!>*&..................{**|}!!!!!!!!!!!!!!!!!!!!!!!!~**-;........+%**)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;......{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!/(**2.............",
",**/!!!!!!!!!!!!!!!~**;...............#**)!!!!!!!!!!!!!!!!!!!!!!!>**&.#*)!!!!!!!!!!!!!!!!>*&...................{**|}!!!!!!!!!!!!!!!!!!!!!![**-;........;%**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;.......{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!/:**&............",
",**/!!!!!!!!!!!!!!!~**;................#**)!!!!!!!!!!!!!!!!!!!!!!!>**&#*)!!!!!!!!!!!!!!!!>*&....................,**|}!!!!!!!!!!!!!!!!!!!!_**=;........;-**^!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;........{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!<:**'...........",
",**/!!!!!!!!!!!!!!!~**;.................#**)!!!!!!!!!!!!!!!!!!!!!!!>****)!!!!!!!!!!!!!!!!>*&.....................,**|}!!!!!!!!!!!!!!!!!!_**=$........$=**~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;.........{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!<>**#..........",
",**/!!!!!!!!!!!!!!!~**;..................#**)!!!!!!!!!!!!!!!!!!!!!!!>***)!!!!!!!!!!!!!!!!>*&......................,**(/!!!!!!!!!!!!!!!!_**=$........$=**~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;..........{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>**#+........",
",**/!!!!!!!!!!!!!!!~**;...................#**)!!!!!!!!!!!!!!!!!!!!!!!>**)!!!!!!!!!!!!!!!!>*&.......................,**(/!!!!!!!!!!!!!!_**=$........{***_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;...........{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!]**%+.......",
",**/!!!!!!!!!!!!!!!~**;....................#**)!!!!!!!!!!!!!!!!!!!!!!!>*)!!!!!!!!!!!!!!!!>*&........................,**(/!!!!!!!!!!!!_**=$........{**|_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)**%;......",
",**/!!!!!!!!!!!!!!!~**;.....................#**)!!!!!!!!!!!!!!!!!!!!!!!>)!!!!!!!!!!!!!!!!>*&.........................,**(/!!!!!!!!!!_***$........,**|}!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;.............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!3**-;.....",
",**/!!!!!!!!!!!!!!!~**;......................#**)!!!!!!!!!!!!!!!!!!!!!!!~!!!!!!!!!!!!!!!!>*&..........................,**(/!!!!!!!!}|**{........,**(}!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;..............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**-$....",
",**/!!!!!!!!!!!!!!!~**;.......................#**)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>*&...........................@**(/!!!!!!}|**{........@**-/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!_**-;...............{**/!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!^**=$...",
",*********************;........................#**)!!!!!!!!!!!!!!!!!!!!!~******************&............................@**(/!!!!}|**{........@*************************************************-;................{*****************************************************************={..",
",*********************;.........................#**)!!!!!!!!!!!!!!!!!!!~*******************&.............................@**(/!!}|**{........&*************************************************-;.................{*******************************************************************{.",
",*********************;..........................#**)!!!!!!!!!!!!!!!!!~********************&..............................@**(<}|**1.......+'*************************************************-;..................{********************************************************************,",
"..................................................#**)!!!!!!!!!!!!!!!~**-;.................................................@**%=**,.....................................................................................................................................................",
"...................................................#**)!!!!!!!!!!!!!~**-;...................................................@****,......................................................................................................................................................",
"....................................................#**)!!!!!!!!!!!~**-;.....................................................@**,.......................................................................................................................................................",
"....................................................+%**)!!!!!!!!!~**-;.......................................................&,........................................................................................................................................................",
".....................................................+%**)!!!!!!!~**-;..................................................................................................................................................................................................................",
"......................................................+%**)!!!!!~**-;...................................................................................................................................................................................................................",
".......................................................+%**)!!!~**-;....................................................................................................................................................................................................................",
"........................................................+%**)!~**=$.....................................................................................................................................................................................................................",
".........................................................+%**>**=$......................................................................................................................................................................................................................",
"..........................................................+%***=$.......................................................................................................................................................................................................................",
"...........................................................+%*=$........................................................................................................................................................................................................................",
"............................................................+#$.........................................................................................................................................................................................................................",
"........................................................................................................................................................................................................................................................................................"};
