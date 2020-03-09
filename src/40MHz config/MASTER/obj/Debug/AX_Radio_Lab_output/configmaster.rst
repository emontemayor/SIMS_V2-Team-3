                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.6.0 #9615 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module configmaster
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _lpxosc_settlingtime
                                     12 	.globl _demo_packet
                                     13 	.globl _framing_counter_pos
                                     14 	.globl _framing_insert_counter
                                     15 	.globl _localaddr
                                     16 	.globl _remoteaddr
                                     17 ;--------------------------------------------------------
                                     18 ; special function registers
                                     19 ;--------------------------------------------------------
                                     20 	.area RSEG    (ABS,DATA)
      000000                         21 	.org 0x0000
                                     22 ;--------------------------------------------------------
                                     23 ; special function bits
                                     24 ;--------------------------------------------------------
                                     25 	.area RSEG    (ABS,DATA)
      000000                         26 	.org 0x0000
                                     27 ;--------------------------------------------------------
                                     28 ; overlayable register banks
                                     29 ;--------------------------------------------------------
                                     30 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                         31 	.ds 8
                                     32 ;--------------------------------------------------------
                                     33 ; internal ram data
                                     34 ;--------------------------------------------------------
                                     35 	.area DSEG    (DATA)
                                     36 ;--------------------------------------------------------
                                     37 ; overlayable items in internal ram 
                                     38 ;--------------------------------------------------------
                                     39 ;--------------------------------------------------------
                                     40 ; indirectly addressable internal ram data
                                     41 ;--------------------------------------------------------
                                     42 	.area ISEG    (DATA)
                                     43 ;--------------------------------------------------------
                                     44 ; absolute internal ram data
                                     45 ;--------------------------------------------------------
                                     46 	.area IABS    (ABS,DATA)
                                     47 	.area IABS    (ABS,DATA)
                                     48 ;--------------------------------------------------------
                                     49 ; bit data
                                     50 ;--------------------------------------------------------
                                     51 	.area BSEG    (BIT)
                                     52 ;--------------------------------------------------------
                                     53 ; paged external ram data
                                     54 ;--------------------------------------------------------
                                     55 	.area PSEG    (PAG,XDATA)
                                     56 ;--------------------------------------------------------
                                     57 ; external ram data
                                     58 ;--------------------------------------------------------
                                     59 	.area XSEG    (XDATA)
                                     60 ;--------------------------------------------------------
                                     61 ; absolute external ram data
                                     62 ;--------------------------------------------------------
                                     63 	.area XABS    (ABS,XDATA)
                                     64 ;--------------------------------------------------------
                                     65 ; external initialized ram data
                                     66 ;--------------------------------------------------------
                                     67 	.area XISEG   (XDATA)
                                     68 	.area HOME    (CODE)
                                     69 	.area GSINIT0 (CODE)
                                     70 	.area GSINIT1 (CODE)
                                     71 	.area GSINIT2 (CODE)
                                     72 	.area GSINIT3 (CODE)
                                     73 	.area GSINIT4 (CODE)
                                     74 	.area GSINIT5 (CODE)
                                     75 	.area GSINIT  (CODE)
                                     76 	.area GSFINAL (CODE)
                                     77 	.area CSEG    (CODE)
                                     78 ;--------------------------------------------------------
                                     79 ; global & static initialisations
                                     80 ;--------------------------------------------------------
                                     81 	.area HOME    (CODE)
                                     82 	.area GSINIT  (CODE)
                                     83 	.area GSFINAL (CODE)
                                     84 	.area GSINIT  (CODE)
                                     85 ;--------------------------------------------------------
                                     86 ; Home
                                     87 ;--------------------------------------------------------
                                     88 	.area HOME    (CODE)
                                     89 	.area HOME    (CODE)
                                     90 ;--------------------------------------------------------
                                     91 ; code
                                     92 ;--------------------------------------------------------
                                     93 	.area CSEG    (CODE)
                                     94 	.area CSEG    (CODE)
                                     95 	.area CONST   (CODE)
                           000000    96 G$remoteaddr$0$0 == .
      005676                         97 _remoteaddr:
      005676 33                      98 	.db #0x33	; 51	'3'
      005677 34                      99 	.db #0x34	; 52	'4'
      005678 00                     100 	.db #0x00	; 0
      005679 00                     101 	.db #0x00	; 0
                           000004   102 G$localaddr$0$0 == .
      00567A                        103 _localaddr:
      00567A 32                     104 	.db #0x32	; 50	'2'
      00567B 34                     105 	.db #0x34	; 52	'4'
      00567C 00                     106 	.db #0x00	; 0
      00567D 00                     107 	.db #0x00	; 0
      00567E 00                     108 	.db #0x00	; 0
      00567F 00                     109 	.db #0x00	; 0
      005680 00                     110 	.db #0x00	; 0
      005681 00                     111 	.db #0x00	; 0
                           00000C   112 G$framing_insert_counter$0$0 == .
      005682                        113 _framing_insert_counter:
      005682 00                     114 	.db #0x00	; 0
                           00000D   115 G$framing_counter_pos$0$0 == .
      005683                        116 _framing_counter_pos:
      005683 02                     117 	.db #0x02	; 2
                           00000E   118 G$demo_packet$0$0 == .
      005684                        119 _demo_packet:
      005684 11                     120 	.db #0x11	; 17
      005685 22                     121 	.db #0x22	; 34
      005686 33                     122 	.db #0x33	; 51	'3'
      005687 44                     123 	.db #0x44	; 68	'D'
                           000012   124 G$lpxosc_settlingtime$0$0 == .
      005688                        125 _lpxosc_settlingtime:
      005688 B8 0B                  126 	.byte #0xb8,#0x0b	; 3000
                                    127 	.area XINIT   (CODE)
                                    128 	.area CABS    (ABS,CODE)
