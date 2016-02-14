/**********************************************************************
 *	SCAN CODE ==> ASCII CODE TABLE
 **********************************************************************
;
;The connector will be one of the following:
;5pin 180 deg DIN               6pin MINIDIN
;----------------               ------------
;                                
;                                    _
;       (2)      1 CLOCK          (5) (6)        1 DATA
;    (5)   (4)   2 DATA              |           2 
;   (3)     (1)  3              (3)     (4)      3 GND
;                4 GND                           4 +5V
;                5 5V             (1) (2)        5 CLOCK
;                                                6
;
;,-------,---,---,---,---,,---,---,---,---,,---,---,---,---,
;|ESC    |F1 |F2 |F3 |F4 ||F5 |F6 |F7 |F8 ||F9 |F10|F11|F12|
;|76     |05 |06 |04 |0c ||03 |0b |83 |0a ||01 |09 |78 |07 |
;'-------'---'---'---'---''---'---'---'---''---'---'---'---'
;,---,---,---,---,---,---,---,---,---,---,---,---,---,-----,
;|~  |1  |2  |3  |4  |5  |6  |7  |8  |9  |0  |-  |=  |BS   |
;|0e |16 |1e |26 |25 |2e |36 |3d |3e |46 |45 |4e |55 |66   |
;|---',--',--',--',--',--',--',--',--',--',--',--',--',----|
;|TAB |Q  |W  |E  |R  |T  |Y  |U  |I  |O  |P  |[  |]  |\   |
;|0d  |15 |1d |24 |2d |2c |35 |3c |43 |44 |4d |54 |5b |5d  |
;|----',--',--',--',--',--',--',--',--',--',--',--',--'----|
;|CAPS |A  |S  |D  |F  |G  |H  |J  |K  |L  |;  |,  |ENTER  |
;|58   |1c |1b |23 |2b |34 |33 |3b |42 |4b |4c |52 |5a     |
;|-----',--',--',--',--',--',--',--',--',--',--',----------|
;|SHIFT |Z  |X  |C  |V  |B  |N  |M  |,  |.  |/  |SHIFT     |
;|12    |1a |22 |21 |2a |32 |31 |3a |41 |49 |4a |59        |
;|----,-',--'--,'---'---'---'---'---'---'--,'--,'-----,----|
;|CTRL|  |ALT  |          SPACE            |ALT|      |CTRL|
;|14  |  |11   |          29               |e011      |e014|
;'----'--'-----'---------------------------'---'------'----'
; 
;,-----,-----,-----,
;|PSCRN|SLOCK|BREAK|
;|*2   |7e   |*4   |
;'-----'-----'-----'
;*2 is E012E07C
;*4 is E11477E1F014F077
;,-----,-----,-----,  ,-----,-----,-----,-----,
;|INS  |HOME |PGUP |  |NLOCK|/    |*    |-    |
;|e070 |e06c |e07d |  |77   |e04a |7c   |7b   |
;|-----|-----|-----|  |-----|-----|-----|-----|
;|DEL  |END  |PGDN |  |7    |8    |9    |+    |
;|e071 |e069 |e07a |  |6c   |75   |7d   |79   |
;'-----'-----'-----'  |-----|-----|-----|-----|
;                     |4    |5    |6    |     |
;                     |6b   |73   |74   |     |
;      ,-----,        |-----|-----|-----|-----|
;      |UP   |        |1    |2    |3    |ENTER|
;      |e075 |        |69   |72   |7a   |e05a |
;,-----|-----|-----,  |-----------|-----|     |
;|LEFT |DOWN |RIGHT|  |0          |.    |     |
;|e06b |e072 |e074 |  |70         |71   |     |
;'-----'-----'-----'  '-----------'-----'-----'
; 
;There are at least three options for the mapping of key numberss to
;keycodes.  The common usage seems to be as follows:
;
;F1 F2    `  1  2  3  4  5  6  7  8  9  0  -  =  \ BS   ESC NUML SCRL SYSR 
;-----   ---------------------------------------------  ------------------
;05 06   0E 16 1E 26 25 2E 36 3D 3E 46 45 4E 55 5D 66    76  77   7E   84
;
;F3 F4   TAB   Q  W  E  R  T  Y  U  I  O  P  [  ]       Home Up  PgUp PrtSc
;-----   -----------------------------------------      -------------------
;04 0C    0D  15 1D 24 2D 2C 35 3C 43 44 4D 54 5B        6C  75   7D   7C
;
;F5 F6   CNTL   A  S  D  F  G  H  J  K  L  ;  ' ENTER   Left  5  Right  -
;-----   --------------------------------------------   ------------------
;03 0B    14   1C 1B 23 28 34 33 38 42 4B 4C 52   5A     6B  73   74   7B
;
;F7 F8   LSHFT    Z  X  C  V  B  N  M  ,  .  /  RSHFT   End  Dn  PgDn   +
;-----   --------------------------------------------   ------------------
;83 0A     12    1A 22 21 2A 32 31 3A 41 49 4A   59      69  72   7A   79
;
;F9 F10  ALT                  SPC             CAPLOCK   Ins      Del
;------  --------------------------------------------   -------------
;01 09    11                   29               58       70       71

 */


PROGMEM static uchar keycode_table[]={
	0x00,0x00,	/* 00 */
	0xF9,0x00,	/* 01 */
	0x00,0x00,	/* 02 */
	0xF5,0x00,	/* 03 */
	0xF3,0x00,	/* 04 */
	0xF1,0x00,	/* 05 */
	0xF2,0x00,	/* 06 */
	0xFC,0x00,	/* 07 */
	0x00,0x00,	/* 08 */
	0xFA,0x00,	/* 09 */
	0xF8,0x00,	/* 0a */
	0xF6,0x00,	/* 0b */
	0xF4,0x00,	/* 0c */
	0x09,0x09,	/* 0d */
	 '|',0xa7,	/* 0e */
	0x00,0x00,	/* 0f */
	0x00,0x00,	/* 10 */
	0x00,0x00,	/* 11 */
	0x00,0x00,	/* 12 */
	0x00,0x00,	/* 13 */
	0x00,0x00,	/* 14 */
	 'q', 'Q',	/* 15 */
	 '1', '!',	/* 16 */
	0x00,0x00,	/* 17 */
	0x00,0x00,	/* 18 */
	0x00,0x00,	/* 19 */
	 'z', 'Z',	/* 1a */
	 's', 'S',	/* 1b */
	 'a', 'A',	/* 1c */
	 'w', 'W',	/* 1d */
	 '2', '"',	/* 1e */
	0x00,0x00,	/* 1f */
	0x00,0x00,	/* 20 */
	 'c', 'C',	/* 21 */
	 'x', 'X',	/* 22 */
	 'd', 'D',	/* 23 */
	 'e', 'E',	/* 24 */
	 '4',0xa4,	/* 25 */
	 '3', '#',	/* 26 */
	0x00,0x00,	/* 27 */
	0x00,0x00,	/* 28 */
	 ' ', ' ',	/* 29 */
	 'v', 'V',	/* 2a */
	 'f', 'F',	/* 2b */
	 't', 'T',	/* 2c */
	 'r', 'R',	/* 2d */
	 '5', '%',	/* 2e */
	0x00,0x00,	/* 2f */
	0x00,0x00,	/* 30 */
	 'n', 'N',	/* 31 */
	 'b', 'B',	/* 32 */
	 'h', 'H',	/* 33 */
	 'g', 'G',	/* 34 */
	 'y', 'Y',	/* 35 */
	 '6', '&',	/* 36 */
	0x00,0x00,	/* 37 */
	0x00,0x00,	/* 38 */
	 ',', 'L',	/* 39 */
	 'm', 'M',	/* 3a */
	 'j', 'J',	/* 3b */
	 'u', 'U',	/* 3c */
	 '7', '/',	/* 3d */
	 '8', '(',	/* 3e */
	0x00,0x00,	/* 3f */
	0x00,0x00,	/* 40 */
	 ',', ';',	/* 41 */
	 'k', 'K',	/* 42 */
	 'i', 'I',	/* 43 */
	 'o', 'O',	/* 44 */
	 '0', '=',	/* 45 */
	 '9', ')',	/* 46 */
	0x00,0x00,	/* 47 */
	0x00,0x00,	/* 48 */
	 '.', ':',	/* 49 */
	 '-', '_',	/* 4a */
	 'l', 'L',	/* 4b */
	0xf8,0xd8,	/* 4c */
	 'p', 'P',	/* 4d */
	 '+', '?',	/* 4e */
	0x00,0x00,	/* 4f */
	0x00,0x00,	/* 50 */
	0x00,0x00,	/* 51 */
	0xe6,0xc6,	/* 52 */
	0x00,0x00,	/* 53 */
	0xe5,0xc5,	/* 54 */
	'\\', '`',	/* 55 */
	0x00,0x00,	/* 56 */
	0x00,0x00,	/* 57 */
	0x00,0x00,	/* 58 */
	0x00,0x00,	/* 59 */
	0x0d,0x0d,	/* 5a */
	0xa8, '^',	/* 5b */
	0x00,0x00,	/* 5c */
	0x27, '*',	/* 5d */
	0x00,0x00,	/* 5e */
	0x00,0x00,	/* 5f */
	0x00,0x00,	/* 60 */
	 '<', '>',	/* 61 */
	0x00,0x00,	/* 62 */
	0x00,0x00,	/* 63 */
	0x00,0x00,	/* 64 */
	0x00,0x00,	/* 65 */
	0x08,0x08,	/* 66 */
	0x00,0x00,	/* 67 */
	0x00,0x00,	/* 68 */
	 '1', '1',	/* 69 */
	0x00,0x00,	/* 6a */
	 '4', '4',	/* 6b */
	 '7', '7',	/* 6c */
	0x00,0x00,	/* 6d */
	0x00,0x00,	/* 6e */
	0x00,0x00,	/* 6f */
	 '0', '0',	/* 70 */
	 ',', ',',	/* 71 */
	 '2', '2',	/* 72 */
	 '5', '5',	/* 73 */
	 '6', '6',	/* 74 */
	 '8', '8',	/* 75 */
	0x1b,0x1b,	/* 76 */
	0x00,0x00,	/* 77 */
	0xFB,0x00,	/* 78 */
	 '+', '+',	/* 79 */
	 '3', '3',	/* 7a */
	 '-', '-',	/* 7b */
	 '*', '*',	/* 7c */
	 '9', '9',	/* 7d */
	0x00,0x00,	/* 7e */
	0x00,0x00,	/* 7f */

	0x00,0x00,	/* E0 00 = 80 */
	0x00,0x00,	/* E0 01 = 81 */
	0x00,0x00,	/* E0 02 = 82 */
	0xF7,0x00,	/* E0 03 = 83 */
	0x00,0x00,	/* E0 04 = 84 */
	0x00,0x00,	/* E0 05 = 85 */
	0x00,0x00,	/* E0 06 = 86 */
	0x00,0x00,	/* E0 07 = 87 */
	0x00,0x00,	/* E0 08 = 88 */
	0x00,0x00,	/* E0 09 = 89 */
	0x00,0x00,	/* E0 0A = 8a */
	0x00,0x00,	/* E0 0B = 8b */
	0x00,0x00,	/* E0 0C = 8c */
	0x00,0x00,	/* E0 0D = 8d */
	0x00,0x00,	/* E0 0E = 8e */
	0x00,0x00,	/* E0 0F = 8f */
	0x00,0x00,	/* E0 10 = 90 */
	0x00,0x00,	/* E0 11 = 91 */
	0x00,0x00,	/* E0 12 = 92 */
	0x00,0x00,	/* E0 13 = 93 */
	0x00,0x00,	/* E0 14 = 94 */
	0x00,0x00,	/* E0 15 = 95 */
	0x00,0x00,	/* E0 16 = 96 */
	0x00,0x00,	/* E0 17 = 97 */
	0x00,0x00,	/* E0 18 = 98 */
	0x00,0x00,	/* E0 19 = 99 */
	0x00,0x00,	/* E0 1A = 9a */
	0x00,0x00,	/* E0 1B = 9b */
	0x00,0x00,	/* E0 1C = 9c */
	0x00,0x00,	/* E0 1D = 9d */
	0x00,0x00,	/* E0 1E = 9e */
	0x00,0x00,	/* E0 1F = 9f */
	0x00,0x00,	/* E0 20 = a0 */
	0x00,0x00,	/* E0 21 = a1 */
	0x00,0x00,	/* E0 22 = a2 */
	0x00,0x00,	/* E0 23 = a3 */
	0x00,0x00,	/* E0 24 = a4 */
	0x00,0x00,	/* E0 25 = a5 */
	0x00,0x00,	/* E0 26 = a6 */
	0x00,0x00,	/* E0 27 = a7 */
	0x00,0x00,	/* E0 28 = a8 */
	0x00,0x00,	/* E0 29 = a9 */
	0x00,0x00,	/* E0 2A = aa */
	0x00,0x00,	/* E0 2B = ab */
	0x00,0x00,	/* E0 2C = ac */
	0x00,0x00,	/* E0 2D = ad */
	0x00,0x00,	/* E0 2E = ae */
	0x00,0x00,	/* E0 2F = af */
	0x00,0x00,	/* E0 30 = b0 */
	0x00,0x00,	/* E0 31 = b1 */
	0x00,0x00,	/* E0 32 = b2 */
	0x00,0x00,	/* E0 33 = b3 */
	0x00,0x00,	/* E0 34 = b4 */
	0x00,0x00,	/* E0 35 = b5 */
	0x00,0x00,	/* E0 36 = b6 */
	0x00,0x00,	/* E0 37 = b7 */
	0x00,0x00,	/* E0 38 = b8 */
	0x00,0x00,	/* E0 39 = b9 */
	0x00,0x00,	/* E0 3A = ba */
	0x00,0x00,	/* E0 3B = bb */
	0x00,0x00,	/* E0 3C = bc */
	0x00,0x00,	/* E0 3D = bd */
	0x00,0x00,	/* E0 3E = be */
	0x00,0x00,	/* E0 3F = bf */
	0x00,0x00,	/* E0 40 = c0 */
	0x00,0x00,	/* E0 41 = c1 */
	0x00,0x00,	/* E0 42 = c2 */
	0x00,0x00,	/* E0 43 = c3 */
	0x00,0x00,	/* E0 44 = c4 */
	0x00,0x00,	/* E0 45 = c5 */
	0x00,0x00,	/* E0 46 = c6 */
	0x00,0x00,	/* E0 47 = c7 */
	0x00,0x00,	/* E0 48 = c8 */
	0x00,0x00,	/* E0 49 = c9 */
	0x00,0x00,	/* E0 4A = ca */
	0x00,0x00,	/* E0 4B = cb */
	0x00,0x00,	/* E0 4C = cc */
	0x00,0x00,	/* E0 4D = cd */
	0x00,0x00,	/* E0 4E = ce */
	0x00,0x00,	/* E0 4F = cf */
	0x00,0x00,	/* E0 50 = d0 */
	0x00,0x00,	/* E0 51 = d1 */
	0x00,0x00,	/* E0 52 = d2 */
	0x00,0x00,	/* E0 53 = d3 */
	0x00,0x00,	/* E0 54 = d4 */
	0x00,0x00,	/* E0 55 = d5 */
	0x00,0x00,	/* E0 56 = d6 */
	0x00,0x00,	/* E0 57 = d7 */
	0x00,0x00,	/* E0 58 = d8 */
	0x00,0x00,	/* E0 59 = d9 */
	0x00,0x00,	/* E0 5A = da */
	0x00,0x00,	/* E0 5B = db */
	0x00,0x00,	/* E0 5C = dc */
	0x00,0x00,	/* E0 5D = dd */
	0x00,0x00,	/* E0 5E = de */
	0x00,0x00,	/* E0 5F = df */
	0x00,0x00,	/* E0 60 = e0 */
	0x00,0x00,	/* E0 61 = e1 */
	0x00,0x00,	/* E0 62 = e2 */
	0x00,0x00,	/* E0 63 = e3 */
	0x00,0x00,	/* E0 64 = e4 */
	0x00,0x00,	/* E0 65 = e5 */
	0x00,0x00,	/* E0 66 = e6 */
	0x00,0x00,	/* E0 67 = e7 */
	0x00,0x00,	/* E0 68 = e8 */
	0x00,0x00,	/* E0 69 = e9 */
	0x00,0x00,	/* E0 6A = ea */
	0x00,0x00,	/* E0 6B = eb */
	0x00,0x00,	/* E0 6C = ec */
	0x00,0x00,	/* E0 6D = ed */
	0x00,0x00,	/* E0 6E = ee */
	0x00,0x00,	/* E0 6F = ef */
	0x00,0x00,	/* E0 70 = f0 */
	0x00,0x00,	/* E0 71 = f1 */
	0x00,0x00,	/* E0 72 = f2 */
	0x00,0x00,	/* E0 73 = f3 */
	0x00,0x00,	/* E0 74 = f4 */
	0x00,0x00,	/* E0 75 = f5 */
	0x00,0x00,	/* E0 76 = f6 */
	0x00,0x00,	/* E0 77 = f7 */
	0x00,0x00,	/* E0 78 = f8 */
	0x00,0x00,	/* E0 79 = f9 */
	0x00,0x00,	/* E0 7A = fa */
	0x00,0x00,	/* E0 7B = fb */
	0x00,0x00,	/* E0 7C = fc */
	0x00,0x00,	/* E0 7D = fd */
	0x00,0x00,	/* E0 7E = fe */
	0x00,0x00,	/* E0 7F = ff */
};
/**********************************************************************
 *	
 **********************************************************************
 */
