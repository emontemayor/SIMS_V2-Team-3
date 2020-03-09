                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.6.0 #9615 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _onepattern
                                     12 	.globl _txpattern
                                     13 	.globl _main
                                     14 	.globl __sdcc_external_startup
                                     15 	.globl _set_receiveber
                                     16 	.globl _set_transmit
                                     17 	.globl _set_cw
                                     18 	.globl _dbglink_display_radio_error
                                     19 	.globl _axradio_setup_pincfg2
                                     20 	.globl _axradio_setup_pincfg1
                                     21 	.globl _axradio_agc_thaw
                                     22 	.globl _axradio_agc_freeze
                                     23 	.globl _axradio_transmit
                                     24 	.globl _axradio_conv_freq_tohz
                                     25 	.globl _axradio_get_pllvcoi
                                     26 	.globl _axradio_get_pllrange
                                     27 	.globl _axradio_set_mode
                                     28 	.globl _axradio_cansleep
                                     29 	.globl _axradio_init
                                     30 	.globl _dbglink_writenum32
                                     31 	.globl _dbglink_writehex16
                                     32 	.globl _dbglink_writenum16
                                     33 	.globl _dbglink_writestr
                                     34 	.globl _dbglink_tx
                                     35 	.globl _dbglink_init
                                     36 	.globl _dbglink_txidle
                                     37 	.globl _pn15_output
                                     38 	.globl _pn15_advance
                                     39 	.globl _pn9_advance
                                     40 	.globl _wtimer_runcallbacks
                                     41 	.globl _wtimer_idle
                                     42 	.globl _wtimer_init
                                     43 	.globl _wtimer1_setconfig
                                     44 	.globl _wtimer0_setconfig
                                     45 	.globl _flash_apply_calibration
                                     46 	.globl _enter_sleep
                                     47 	.globl _hweight8
                                     48 	.globl _PORTC_7
                                     49 	.globl _PORTC_6
                                     50 	.globl _PORTC_5
                                     51 	.globl _PORTC_4
                                     52 	.globl _PORTC_3
                                     53 	.globl _PORTC_2
                                     54 	.globl _PORTC_1
                                     55 	.globl _PORTC_0
                                     56 	.globl _PORTB_7
                                     57 	.globl _PORTB_6
                                     58 	.globl _PORTB_5
                                     59 	.globl _PORTB_4
                                     60 	.globl _PORTB_3
                                     61 	.globl _PORTB_2
                                     62 	.globl _PORTB_1
                                     63 	.globl _PORTB_0
                                     64 	.globl _PORTA_7
                                     65 	.globl _PORTA_6
                                     66 	.globl _PORTA_5
                                     67 	.globl _PORTA_4
                                     68 	.globl _PORTA_3
                                     69 	.globl _PORTA_2
                                     70 	.globl _PORTA_1
                                     71 	.globl _PORTA_0
                                     72 	.globl _PINC_7
                                     73 	.globl _PINC_6
                                     74 	.globl _PINC_5
                                     75 	.globl _PINC_4
                                     76 	.globl _PINC_3
                                     77 	.globl _PINC_2
                                     78 	.globl _PINC_1
                                     79 	.globl _PINC_0
                                     80 	.globl _PINB_7
                                     81 	.globl _PINB_6
                                     82 	.globl _PINB_5
                                     83 	.globl _PINB_4
                                     84 	.globl _PINB_3
                                     85 	.globl _PINB_2
                                     86 	.globl _PINB_1
                                     87 	.globl _PINB_0
                                     88 	.globl _PINA_7
                                     89 	.globl _PINA_6
                                     90 	.globl _PINA_5
                                     91 	.globl _PINA_4
                                     92 	.globl _PINA_3
                                     93 	.globl _PINA_2
                                     94 	.globl _PINA_1
                                     95 	.globl _PINA_0
                                     96 	.globl _CY
                                     97 	.globl _AC
                                     98 	.globl _F0
                                     99 	.globl _RS1
                                    100 	.globl _RS0
                                    101 	.globl _OV
                                    102 	.globl _F1
                                    103 	.globl _P
                                    104 	.globl _IP_7
                                    105 	.globl _IP_6
                                    106 	.globl _IP_5
                                    107 	.globl _IP_4
                                    108 	.globl _IP_3
                                    109 	.globl _IP_2
                                    110 	.globl _IP_1
                                    111 	.globl _IP_0
                                    112 	.globl _EA
                                    113 	.globl _IE_7
                                    114 	.globl _IE_6
                                    115 	.globl _IE_5
                                    116 	.globl _IE_4
                                    117 	.globl _IE_3
                                    118 	.globl _IE_2
                                    119 	.globl _IE_1
                                    120 	.globl _IE_0
                                    121 	.globl _EIP_7
                                    122 	.globl _EIP_6
                                    123 	.globl _EIP_5
                                    124 	.globl _EIP_4
                                    125 	.globl _EIP_3
                                    126 	.globl _EIP_2
                                    127 	.globl _EIP_1
                                    128 	.globl _EIP_0
                                    129 	.globl _EIE_7
                                    130 	.globl _EIE_6
                                    131 	.globl _EIE_5
                                    132 	.globl _EIE_4
                                    133 	.globl _EIE_3
                                    134 	.globl _EIE_2
                                    135 	.globl _EIE_1
                                    136 	.globl _EIE_0
                                    137 	.globl _E2IP_7
                                    138 	.globl _E2IP_6
                                    139 	.globl _E2IP_5
                                    140 	.globl _E2IP_4
                                    141 	.globl _E2IP_3
                                    142 	.globl _E2IP_2
                                    143 	.globl _E2IP_1
                                    144 	.globl _E2IP_0
                                    145 	.globl _E2IE_7
                                    146 	.globl _E2IE_6
                                    147 	.globl _E2IE_5
                                    148 	.globl _E2IE_4
                                    149 	.globl _E2IE_3
                                    150 	.globl _E2IE_2
                                    151 	.globl _E2IE_1
                                    152 	.globl _E2IE_0
                                    153 	.globl _B_7
                                    154 	.globl _B_6
                                    155 	.globl _B_5
                                    156 	.globl _B_4
                                    157 	.globl _B_3
                                    158 	.globl _B_2
                                    159 	.globl _B_1
                                    160 	.globl _B_0
                                    161 	.globl _ACC_7
                                    162 	.globl _ACC_6
                                    163 	.globl _ACC_5
                                    164 	.globl _ACC_4
                                    165 	.globl _ACC_3
                                    166 	.globl _ACC_2
                                    167 	.globl _ACC_1
                                    168 	.globl _ACC_0
                                    169 	.globl _WTSTAT
                                    170 	.globl _WTIRQEN
                                    171 	.globl _WTEVTD
                                    172 	.globl _WTEVTD1
                                    173 	.globl _WTEVTD0
                                    174 	.globl _WTEVTC
                                    175 	.globl _WTEVTC1
                                    176 	.globl _WTEVTC0
                                    177 	.globl _WTEVTB
                                    178 	.globl _WTEVTB1
                                    179 	.globl _WTEVTB0
                                    180 	.globl _WTEVTA
                                    181 	.globl _WTEVTA1
                                    182 	.globl _WTEVTA0
                                    183 	.globl _WTCNTR1
                                    184 	.globl _WTCNTB
                                    185 	.globl _WTCNTB1
                                    186 	.globl _WTCNTB0
                                    187 	.globl _WTCNTA
                                    188 	.globl _WTCNTA1
                                    189 	.globl _WTCNTA0
                                    190 	.globl _WTCFGB
                                    191 	.globl _WTCFGA
                                    192 	.globl _WDTRESET
                                    193 	.globl _WDTCFG
                                    194 	.globl _U1STATUS
                                    195 	.globl _U1SHREG
                                    196 	.globl _U1MODE
                                    197 	.globl _U1CTRL
                                    198 	.globl _U0STATUS
                                    199 	.globl _U0SHREG
                                    200 	.globl _U0MODE
                                    201 	.globl _U0CTRL
                                    202 	.globl _T2STATUS
                                    203 	.globl _T2PERIOD
                                    204 	.globl _T2PERIOD1
                                    205 	.globl _T2PERIOD0
                                    206 	.globl _T2MODE
                                    207 	.globl _T2CNT
                                    208 	.globl _T2CNT1
                                    209 	.globl _T2CNT0
                                    210 	.globl _T2CLKSRC
                                    211 	.globl _T1STATUS
                                    212 	.globl _T1PERIOD
                                    213 	.globl _T1PERIOD1
                                    214 	.globl _T1PERIOD0
                                    215 	.globl _T1MODE
                                    216 	.globl _T1CNT
                                    217 	.globl _T1CNT1
                                    218 	.globl _T1CNT0
                                    219 	.globl _T1CLKSRC
                                    220 	.globl _T0STATUS
                                    221 	.globl _T0PERIOD
                                    222 	.globl _T0PERIOD1
                                    223 	.globl _T0PERIOD0
                                    224 	.globl _T0MODE
                                    225 	.globl _T0CNT
                                    226 	.globl _T0CNT1
                                    227 	.globl _T0CNT0
                                    228 	.globl _T0CLKSRC
                                    229 	.globl _SPSTATUS
                                    230 	.globl _SPSHREG
                                    231 	.globl _SPMODE
                                    232 	.globl _SPCLKSRC
                                    233 	.globl _RADIOSTAT
                                    234 	.globl _RADIOSTAT1
                                    235 	.globl _RADIOSTAT0
                                    236 	.globl _RADIODATA
                                    237 	.globl _RADIODATA3
                                    238 	.globl _RADIODATA2
                                    239 	.globl _RADIODATA1
                                    240 	.globl _RADIODATA0
                                    241 	.globl _RADIOADDR
                                    242 	.globl _RADIOADDR1
                                    243 	.globl _RADIOADDR0
                                    244 	.globl _RADIOACC
                                    245 	.globl _OC1STATUS
                                    246 	.globl _OC1PIN
                                    247 	.globl _OC1MODE
                                    248 	.globl _OC1COMP
                                    249 	.globl _OC1COMP1
                                    250 	.globl _OC1COMP0
                                    251 	.globl _OC0STATUS
                                    252 	.globl _OC0PIN
                                    253 	.globl _OC0MODE
                                    254 	.globl _OC0COMP
                                    255 	.globl _OC0COMP1
                                    256 	.globl _OC0COMP0
                                    257 	.globl _NVSTATUS
                                    258 	.globl _NVKEY
                                    259 	.globl _NVDATA
                                    260 	.globl _NVDATA1
                                    261 	.globl _NVDATA0
                                    262 	.globl _NVADDR
                                    263 	.globl _NVADDR1
                                    264 	.globl _NVADDR0
                                    265 	.globl _IC1STATUS
                                    266 	.globl _IC1MODE
                                    267 	.globl _IC1CAPT
                                    268 	.globl _IC1CAPT1
                                    269 	.globl _IC1CAPT0
                                    270 	.globl _IC0STATUS
                                    271 	.globl _IC0MODE
                                    272 	.globl _IC0CAPT
                                    273 	.globl _IC0CAPT1
                                    274 	.globl _IC0CAPT0
                                    275 	.globl _PORTR
                                    276 	.globl _PORTC
                                    277 	.globl _PORTB
                                    278 	.globl _PORTA
                                    279 	.globl _PINR
                                    280 	.globl _PINC
                                    281 	.globl _PINB
                                    282 	.globl _PINA
                                    283 	.globl _DIRR
                                    284 	.globl _DIRC
                                    285 	.globl _DIRB
                                    286 	.globl _DIRA
                                    287 	.globl _DBGLNKSTAT
                                    288 	.globl _DBGLNKBUF
                                    289 	.globl _CODECONFIG
                                    290 	.globl _CLKSTAT
                                    291 	.globl _CLKCON
                                    292 	.globl _ANALOGCOMP
                                    293 	.globl _ADCCONV
                                    294 	.globl _ADCCLKSRC
                                    295 	.globl _ADCCH3CONFIG
                                    296 	.globl _ADCCH2CONFIG
                                    297 	.globl _ADCCH1CONFIG
                                    298 	.globl _ADCCH0CONFIG
                                    299 	.globl __XPAGE
                                    300 	.globl _XPAGE
                                    301 	.globl _SP
                                    302 	.globl _PSW
                                    303 	.globl _PCON
                                    304 	.globl _IP
                                    305 	.globl _IE
                                    306 	.globl _EIP
                                    307 	.globl _EIE
                                    308 	.globl _E2IP
                                    309 	.globl _E2IE
                                    310 	.globl _DPS
                                    311 	.globl _DPTR1
                                    312 	.globl _DPTR0
                                    313 	.globl _DPL1
                                    314 	.globl _DPL
                                    315 	.globl _DPH1
                                    316 	.globl _DPH
                                    317 	.globl _B
                                    318 	.globl _ACC
                                    319 	.globl _txdata
                                    320 	.globl _AX5043_XTALAMPL
                                    321 	.globl _AX5043_XTALOSC
                                    322 	.globl _AX5043_MODCFGP
                                    323 	.globl _AX5043_POWCTRL1
                                    324 	.globl _AX5043_REF
                                    325 	.globl _AX5043_0xF44
                                    326 	.globl _AX5043_0xF35
                                    327 	.globl _AX5043_0xF34
                                    328 	.globl _AX5043_0xF33
                                    329 	.globl _AX5043_0xF32
                                    330 	.globl _AX5043_0xF31
                                    331 	.globl _AX5043_0xF30
                                    332 	.globl _AX5043_0xF26
                                    333 	.globl _AX5043_0xF23
                                    334 	.globl _AX5043_0xF22
                                    335 	.globl _AX5043_0xF21
                                    336 	.globl _AX5043_0xF1C
                                    337 	.globl _AX5043_0xF18
                                    338 	.globl _AX5043_0xF11
                                    339 	.globl _AX5043_0xF10
                                    340 	.globl _AX5043_0xF0C
                                    341 	.globl _AX5043_0xF00
                                    342 	.globl _AX5043_TIMEGAIN3NB
                                    343 	.globl _AX5043_TIMEGAIN2NB
                                    344 	.globl _AX5043_TIMEGAIN1NB
                                    345 	.globl _AX5043_TIMEGAIN0NB
                                    346 	.globl _AX5043_RXPARAMSETSNB
                                    347 	.globl _AX5043_RXPARAMCURSETNB
                                    348 	.globl _AX5043_PKTMAXLENNB
                                    349 	.globl _AX5043_PKTLENOFFSETNB
                                    350 	.globl _AX5043_PKTLENCFGNB
                                    351 	.globl _AX5043_PKTADDRMASK3NB
                                    352 	.globl _AX5043_PKTADDRMASK2NB
                                    353 	.globl _AX5043_PKTADDRMASK1NB
                                    354 	.globl _AX5043_PKTADDRMASK0NB
                                    355 	.globl _AX5043_PKTADDRCFGNB
                                    356 	.globl _AX5043_PKTADDR3NB
                                    357 	.globl _AX5043_PKTADDR2NB
                                    358 	.globl _AX5043_PKTADDR1NB
                                    359 	.globl _AX5043_PKTADDR0NB
                                    360 	.globl _AX5043_PHASEGAIN3NB
                                    361 	.globl _AX5043_PHASEGAIN2NB
                                    362 	.globl _AX5043_PHASEGAIN1NB
                                    363 	.globl _AX5043_PHASEGAIN0NB
                                    364 	.globl _AX5043_FREQUENCYLEAKNB
                                    365 	.globl _AX5043_FREQUENCYGAIND3NB
                                    366 	.globl _AX5043_FREQUENCYGAIND2NB
                                    367 	.globl _AX5043_FREQUENCYGAIND1NB
                                    368 	.globl _AX5043_FREQUENCYGAIND0NB
                                    369 	.globl _AX5043_FREQUENCYGAINC3NB
                                    370 	.globl _AX5043_FREQUENCYGAINC2NB
                                    371 	.globl _AX5043_FREQUENCYGAINC1NB
                                    372 	.globl _AX5043_FREQUENCYGAINC0NB
                                    373 	.globl _AX5043_FREQUENCYGAINB3NB
                                    374 	.globl _AX5043_FREQUENCYGAINB2NB
                                    375 	.globl _AX5043_FREQUENCYGAINB1NB
                                    376 	.globl _AX5043_FREQUENCYGAINB0NB
                                    377 	.globl _AX5043_FREQUENCYGAINA3NB
                                    378 	.globl _AX5043_FREQUENCYGAINA2NB
                                    379 	.globl _AX5043_FREQUENCYGAINA1NB
                                    380 	.globl _AX5043_FREQUENCYGAINA0NB
                                    381 	.globl _AX5043_FREQDEV13NB
                                    382 	.globl _AX5043_FREQDEV12NB
                                    383 	.globl _AX5043_FREQDEV11NB
                                    384 	.globl _AX5043_FREQDEV10NB
                                    385 	.globl _AX5043_FREQDEV03NB
                                    386 	.globl _AX5043_FREQDEV02NB
                                    387 	.globl _AX5043_FREQDEV01NB
                                    388 	.globl _AX5043_FREQDEV00NB
                                    389 	.globl _AX5043_FOURFSK3NB
                                    390 	.globl _AX5043_FOURFSK2NB
                                    391 	.globl _AX5043_FOURFSK1NB
                                    392 	.globl _AX5043_FOURFSK0NB
                                    393 	.globl _AX5043_DRGAIN3NB
                                    394 	.globl _AX5043_DRGAIN2NB
                                    395 	.globl _AX5043_DRGAIN1NB
                                    396 	.globl _AX5043_DRGAIN0NB
                                    397 	.globl _AX5043_BBOFFSRES3NB
                                    398 	.globl _AX5043_BBOFFSRES2NB
                                    399 	.globl _AX5043_BBOFFSRES1NB
                                    400 	.globl _AX5043_BBOFFSRES0NB
                                    401 	.globl _AX5043_AMPLITUDEGAIN3NB
                                    402 	.globl _AX5043_AMPLITUDEGAIN2NB
                                    403 	.globl _AX5043_AMPLITUDEGAIN1NB
                                    404 	.globl _AX5043_AMPLITUDEGAIN0NB
                                    405 	.globl _AX5043_AGCTARGET3NB
                                    406 	.globl _AX5043_AGCTARGET2NB
                                    407 	.globl _AX5043_AGCTARGET1NB
                                    408 	.globl _AX5043_AGCTARGET0NB
                                    409 	.globl _AX5043_AGCMINMAX3NB
                                    410 	.globl _AX5043_AGCMINMAX2NB
                                    411 	.globl _AX5043_AGCMINMAX1NB
                                    412 	.globl _AX5043_AGCMINMAX0NB
                                    413 	.globl _AX5043_AGCGAIN3NB
                                    414 	.globl _AX5043_AGCGAIN2NB
                                    415 	.globl _AX5043_AGCGAIN1NB
                                    416 	.globl _AX5043_AGCGAIN0NB
                                    417 	.globl _AX5043_AGCAHYST3NB
                                    418 	.globl _AX5043_AGCAHYST2NB
                                    419 	.globl _AX5043_AGCAHYST1NB
                                    420 	.globl _AX5043_AGCAHYST0NB
                                    421 	.globl _AX5043_0xF44NB
                                    422 	.globl _AX5043_0xF35NB
                                    423 	.globl _AX5043_0xF34NB
                                    424 	.globl _AX5043_0xF33NB
                                    425 	.globl _AX5043_0xF32NB
                                    426 	.globl _AX5043_0xF31NB
                                    427 	.globl _AX5043_0xF30NB
                                    428 	.globl _AX5043_0xF26NB
                                    429 	.globl _AX5043_0xF23NB
                                    430 	.globl _AX5043_0xF22NB
                                    431 	.globl _AX5043_0xF21NB
                                    432 	.globl _AX5043_0xF1CNB
                                    433 	.globl _AX5043_0xF18NB
                                    434 	.globl _AX5043_0xF0CNB
                                    435 	.globl _AX5043_0xF00NB
                                    436 	.globl _AX5043_XTALSTATUSNB
                                    437 	.globl _AX5043_XTALOSCNB
                                    438 	.globl _AX5043_XTALCAPNB
                                    439 	.globl _AX5043_XTALAMPLNB
                                    440 	.globl _AX5043_WAKEUPXOEARLYNB
                                    441 	.globl _AX5043_WAKEUPTIMER1NB
                                    442 	.globl _AX5043_WAKEUPTIMER0NB
                                    443 	.globl _AX5043_WAKEUPFREQ1NB
                                    444 	.globl _AX5043_WAKEUPFREQ0NB
                                    445 	.globl _AX5043_WAKEUP1NB
                                    446 	.globl _AX5043_WAKEUP0NB
                                    447 	.globl _AX5043_TXRATE2NB
                                    448 	.globl _AX5043_TXRATE1NB
                                    449 	.globl _AX5043_TXRATE0NB
                                    450 	.globl _AX5043_TXPWRCOEFFE1NB
                                    451 	.globl _AX5043_TXPWRCOEFFE0NB
                                    452 	.globl _AX5043_TXPWRCOEFFD1NB
                                    453 	.globl _AX5043_TXPWRCOEFFD0NB
                                    454 	.globl _AX5043_TXPWRCOEFFC1NB
                                    455 	.globl _AX5043_TXPWRCOEFFC0NB
                                    456 	.globl _AX5043_TXPWRCOEFFB1NB
                                    457 	.globl _AX5043_TXPWRCOEFFB0NB
                                    458 	.globl _AX5043_TXPWRCOEFFA1NB
                                    459 	.globl _AX5043_TXPWRCOEFFA0NB
                                    460 	.globl _AX5043_TRKRFFREQ2NB
                                    461 	.globl _AX5043_TRKRFFREQ1NB
                                    462 	.globl _AX5043_TRKRFFREQ0NB
                                    463 	.globl _AX5043_TRKPHASE1NB
                                    464 	.globl _AX5043_TRKPHASE0NB
                                    465 	.globl _AX5043_TRKFSKDEMOD1NB
                                    466 	.globl _AX5043_TRKFSKDEMOD0NB
                                    467 	.globl _AX5043_TRKFREQ1NB
                                    468 	.globl _AX5043_TRKFREQ0NB
                                    469 	.globl _AX5043_TRKDATARATE2NB
                                    470 	.globl _AX5043_TRKDATARATE1NB
                                    471 	.globl _AX5043_TRKDATARATE0NB
                                    472 	.globl _AX5043_TRKAMPLITUDE1NB
                                    473 	.globl _AX5043_TRKAMPLITUDE0NB
                                    474 	.globl _AX5043_TRKAFSKDEMOD1NB
                                    475 	.globl _AX5043_TRKAFSKDEMOD0NB
                                    476 	.globl _AX5043_TMGTXSETTLENB
                                    477 	.globl _AX5043_TMGTXBOOSTNB
                                    478 	.globl _AX5043_TMGRXSETTLENB
                                    479 	.globl _AX5043_TMGRXRSSINB
                                    480 	.globl _AX5043_TMGRXPREAMBLE3NB
                                    481 	.globl _AX5043_TMGRXPREAMBLE2NB
                                    482 	.globl _AX5043_TMGRXPREAMBLE1NB
                                    483 	.globl _AX5043_TMGRXOFFSACQNB
                                    484 	.globl _AX5043_TMGRXCOARSEAGCNB
                                    485 	.globl _AX5043_TMGRXBOOSTNB
                                    486 	.globl _AX5043_TMGRXAGCNB
                                    487 	.globl _AX5043_TIMER2NB
                                    488 	.globl _AX5043_TIMER1NB
                                    489 	.globl _AX5043_TIMER0NB
                                    490 	.globl _AX5043_SILICONREVISIONNB
                                    491 	.globl _AX5043_SCRATCHNB
                                    492 	.globl _AX5043_RXDATARATE2NB
                                    493 	.globl _AX5043_RXDATARATE1NB
                                    494 	.globl _AX5043_RXDATARATE0NB
                                    495 	.globl _AX5043_RSSIREFERENCENB
                                    496 	.globl _AX5043_RSSIABSTHRNB
                                    497 	.globl _AX5043_RSSINB
                                    498 	.globl _AX5043_REFNB
                                    499 	.globl _AX5043_RADIOSTATENB
                                    500 	.globl _AX5043_RADIOEVENTREQ1NB
                                    501 	.globl _AX5043_RADIOEVENTREQ0NB
                                    502 	.globl _AX5043_RADIOEVENTMASK1NB
                                    503 	.globl _AX5043_RADIOEVENTMASK0NB
                                    504 	.globl _AX5043_PWRMODENB
                                    505 	.globl _AX5043_PWRAMPNB
                                    506 	.globl _AX5043_POWSTICKYSTATNB
                                    507 	.globl _AX5043_POWSTATNB
                                    508 	.globl _AX5043_POWIRQMASKNB
                                    509 	.globl _AX5043_POWCTRL1NB
                                    510 	.globl _AX5043_PLLVCOIRNB
                                    511 	.globl _AX5043_PLLVCOINB
                                    512 	.globl _AX5043_PLLVCODIVNB
                                    513 	.globl _AX5043_PLLRNGCLKNB
                                    514 	.globl _AX5043_PLLRANGINGBNB
                                    515 	.globl _AX5043_PLLRANGINGANB
                                    516 	.globl _AX5043_PLLLOOPBOOSTNB
                                    517 	.globl _AX5043_PLLLOOPNB
                                    518 	.globl _AX5043_PLLLOCKDETNB
                                    519 	.globl _AX5043_PLLCPIBOOSTNB
                                    520 	.globl _AX5043_PLLCPINB
                                    521 	.globl _AX5043_PKTSTOREFLAGSNB
                                    522 	.globl _AX5043_PKTMISCFLAGSNB
                                    523 	.globl _AX5043_PKTCHUNKSIZENB
                                    524 	.globl _AX5043_PKTACCEPTFLAGSNB
                                    525 	.globl _AX5043_PINSTATENB
                                    526 	.globl _AX5043_PINFUNCSYSCLKNB
                                    527 	.globl _AX5043_PINFUNCPWRAMPNB
                                    528 	.globl _AX5043_PINFUNCIRQNB
                                    529 	.globl _AX5043_PINFUNCDCLKNB
                                    530 	.globl _AX5043_PINFUNCDATANB
                                    531 	.globl _AX5043_PINFUNCANTSELNB
                                    532 	.globl _AX5043_MODULATIONNB
                                    533 	.globl _AX5043_MODCFGPNB
                                    534 	.globl _AX5043_MODCFGFNB
                                    535 	.globl _AX5043_MODCFGANB
                                    536 	.globl _AX5043_MAXRFOFFSET2NB
                                    537 	.globl _AX5043_MAXRFOFFSET1NB
                                    538 	.globl _AX5043_MAXRFOFFSET0NB
                                    539 	.globl _AX5043_MAXDROFFSET2NB
                                    540 	.globl _AX5043_MAXDROFFSET1NB
                                    541 	.globl _AX5043_MAXDROFFSET0NB
                                    542 	.globl _AX5043_MATCH1PAT1NB
                                    543 	.globl _AX5043_MATCH1PAT0NB
                                    544 	.globl _AX5043_MATCH1MINNB
                                    545 	.globl _AX5043_MATCH1MAXNB
                                    546 	.globl _AX5043_MATCH1LENNB
                                    547 	.globl _AX5043_MATCH0PAT3NB
                                    548 	.globl _AX5043_MATCH0PAT2NB
                                    549 	.globl _AX5043_MATCH0PAT1NB
                                    550 	.globl _AX5043_MATCH0PAT0NB
                                    551 	.globl _AX5043_MATCH0MINNB
                                    552 	.globl _AX5043_MATCH0MAXNB
                                    553 	.globl _AX5043_MATCH0LENNB
                                    554 	.globl _AX5043_LPOSCSTATUSNB
                                    555 	.globl _AX5043_LPOSCREF1NB
                                    556 	.globl _AX5043_LPOSCREF0NB
                                    557 	.globl _AX5043_LPOSCPER1NB
                                    558 	.globl _AX5043_LPOSCPER0NB
                                    559 	.globl _AX5043_LPOSCKFILT1NB
                                    560 	.globl _AX5043_LPOSCKFILT0NB
                                    561 	.globl _AX5043_LPOSCFREQ1NB
                                    562 	.globl _AX5043_LPOSCFREQ0NB
                                    563 	.globl _AX5043_LPOSCCONFIGNB
                                    564 	.globl _AX5043_IRQREQUEST1NB
                                    565 	.globl _AX5043_IRQREQUEST0NB
                                    566 	.globl _AX5043_IRQMASK1NB
                                    567 	.globl _AX5043_IRQMASK0NB
                                    568 	.globl _AX5043_IRQINVERSION1NB
                                    569 	.globl _AX5043_IRQINVERSION0NB
                                    570 	.globl _AX5043_IFFREQ1NB
                                    571 	.globl _AX5043_IFFREQ0NB
                                    572 	.globl _AX5043_GPADCPERIODNB
                                    573 	.globl _AX5043_GPADCCTRLNB
                                    574 	.globl _AX5043_GPADC13VALUE1NB
                                    575 	.globl _AX5043_GPADC13VALUE0NB
                                    576 	.globl _AX5043_FSKDMIN1NB
                                    577 	.globl _AX5043_FSKDMIN0NB
                                    578 	.globl _AX5043_FSKDMAX1NB
                                    579 	.globl _AX5043_FSKDMAX0NB
                                    580 	.globl _AX5043_FSKDEV2NB
                                    581 	.globl _AX5043_FSKDEV1NB
                                    582 	.globl _AX5043_FSKDEV0NB
                                    583 	.globl _AX5043_FREQB3NB
                                    584 	.globl _AX5043_FREQB2NB
                                    585 	.globl _AX5043_FREQB1NB
                                    586 	.globl _AX5043_FREQB0NB
                                    587 	.globl _AX5043_FREQA3NB
                                    588 	.globl _AX5043_FREQA2NB
                                    589 	.globl _AX5043_FREQA1NB
                                    590 	.globl _AX5043_FREQA0NB
                                    591 	.globl _AX5043_FRAMINGNB
                                    592 	.globl _AX5043_FIFOTHRESH1NB
                                    593 	.globl _AX5043_FIFOTHRESH0NB
                                    594 	.globl _AX5043_FIFOSTATNB
                                    595 	.globl _AX5043_FIFOFREE1NB
                                    596 	.globl _AX5043_FIFOFREE0NB
                                    597 	.globl _AX5043_FIFODATANB
                                    598 	.globl _AX5043_FIFOCOUNT1NB
                                    599 	.globl _AX5043_FIFOCOUNT0NB
                                    600 	.globl _AX5043_FECSYNCNB
                                    601 	.globl _AX5043_FECSTATUSNB
                                    602 	.globl _AX5043_FECNB
                                    603 	.globl _AX5043_ENCODINGNB
                                    604 	.globl _AX5043_DIVERSITYNB
                                    605 	.globl _AX5043_DECIMATIONNB
                                    606 	.globl _AX5043_DACVALUE1NB
                                    607 	.globl _AX5043_DACVALUE0NB
                                    608 	.globl _AX5043_DACCONFIGNB
                                    609 	.globl _AX5043_CRCINIT3NB
                                    610 	.globl _AX5043_CRCINIT2NB
                                    611 	.globl _AX5043_CRCINIT1NB
                                    612 	.globl _AX5043_CRCINIT0NB
                                    613 	.globl _AX5043_BGNDRSSITHRNB
                                    614 	.globl _AX5043_BGNDRSSIGAINNB
                                    615 	.globl _AX5043_BGNDRSSINB
                                    616 	.globl _AX5043_BBTUNENB
                                    617 	.globl _AX5043_BBOFFSCAPNB
                                    618 	.globl _AX5043_AMPLFILTERNB
                                    619 	.globl _AX5043_AGCCOUNTERNB
                                    620 	.globl _AX5043_AFSKSPACE1NB
                                    621 	.globl _AX5043_AFSKSPACE0NB
                                    622 	.globl _AX5043_AFSKMARK1NB
                                    623 	.globl _AX5043_AFSKMARK0NB
                                    624 	.globl _AX5043_AFSKCTRLNB
                                    625 	.globl _AX5043_TIMEGAIN3
                                    626 	.globl _AX5043_TIMEGAIN2
                                    627 	.globl _AX5043_TIMEGAIN1
                                    628 	.globl _AX5043_TIMEGAIN0
                                    629 	.globl _AX5043_RXPARAMSETS
                                    630 	.globl _AX5043_RXPARAMCURSET
                                    631 	.globl _AX5043_PKTMAXLEN
                                    632 	.globl _AX5043_PKTLENOFFSET
                                    633 	.globl _AX5043_PKTLENCFG
                                    634 	.globl _AX5043_PKTADDRMASK3
                                    635 	.globl _AX5043_PKTADDRMASK2
                                    636 	.globl _AX5043_PKTADDRMASK1
                                    637 	.globl _AX5043_PKTADDRMASK0
                                    638 	.globl _AX5043_PKTADDRCFG
                                    639 	.globl _AX5043_PKTADDR3
                                    640 	.globl _AX5043_PKTADDR2
                                    641 	.globl _AX5043_PKTADDR1
                                    642 	.globl _AX5043_PKTADDR0
                                    643 	.globl _AX5043_PHASEGAIN3
                                    644 	.globl _AX5043_PHASEGAIN2
                                    645 	.globl _AX5043_PHASEGAIN1
                                    646 	.globl _AX5043_PHASEGAIN0
                                    647 	.globl _AX5043_FREQUENCYLEAK
                                    648 	.globl _AX5043_FREQUENCYGAIND3
                                    649 	.globl _AX5043_FREQUENCYGAIND2
                                    650 	.globl _AX5043_FREQUENCYGAIND1
                                    651 	.globl _AX5043_FREQUENCYGAIND0
                                    652 	.globl _AX5043_FREQUENCYGAINC3
                                    653 	.globl _AX5043_FREQUENCYGAINC2
                                    654 	.globl _AX5043_FREQUENCYGAINC1
                                    655 	.globl _AX5043_FREQUENCYGAINC0
                                    656 	.globl _AX5043_FREQUENCYGAINB3
                                    657 	.globl _AX5043_FREQUENCYGAINB2
                                    658 	.globl _AX5043_FREQUENCYGAINB1
                                    659 	.globl _AX5043_FREQUENCYGAINB0
                                    660 	.globl _AX5043_FREQUENCYGAINA3
                                    661 	.globl _AX5043_FREQUENCYGAINA2
                                    662 	.globl _AX5043_FREQUENCYGAINA1
                                    663 	.globl _AX5043_FREQUENCYGAINA0
                                    664 	.globl _AX5043_FREQDEV13
                                    665 	.globl _AX5043_FREQDEV12
                                    666 	.globl _AX5043_FREQDEV11
                                    667 	.globl _AX5043_FREQDEV10
                                    668 	.globl _AX5043_FREQDEV03
                                    669 	.globl _AX5043_FREQDEV02
                                    670 	.globl _AX5043_FREQDEV01
                                    671 	.globl _AX5043_FREQDEV00
                                    672 	.globl _AX5043_FOURFSK3
                                    673 	.globl _AX5043_FOURFSK2
                                    674 	.globl _AX5043_FOURFSK1
                                    675 	.globl _AX5043_FOURFSK0
                                    676 	.globl _AX5043_DRGAIN3
                                    677 	.globl _AX5043_DRGAIN2
                                    678 	.globl _AX5043_DRGAIN1
                                    679 	.globl _AX5043_DRGAIN0
                                    680 	.globl _AX5043_BBOFFSRES3
                                    681 	.globl _AX5043_BBOFFSRES2
                                    682 	.globl _AX5043_BBOFFSRES1
                                    683 	.globl _AX5043_BBOFFSRES0
                                    684 	.globl _AX5043_AMPLITUDEGAIN3
                                    685 	.globl _AX5043_AMPLITUDEGAIN2
                                    686 	.globl _AX5043_AMPLITUDEGAIN1
                                    687 	.globl _AX5043_AMPLITUDEGAIN0
                                    688 	.globl _AX5043_AGCTARGET3
                                    689 	.globl _AX5043_AGCTARGET2
                                    690 	.globl _AX5043_AGCTARGET1
                                    691 	.globl _AX5043_AGCTARGET0
                                    692 	.globl _AX5043_AGCMINMAX3
                                    693 	.globl _AX5043_AGCMINMAX2
                                    694 	.globl _AX5043_AGCMINMAX1
                                    695 	.globl _AX5043_AGCMINMAX0
                                    696 	.globl _AX5043_AGCGAIN3
                                    697 	.globl _AX5043_AGCGAIN2
                                    698 	.globl _AX5043_AGCGAIN1
                                    699 	.globl _AX5043_AGCGAIN0
                                    700 	.globl _AX5043_AGCAHYST3
                                    701 	.globl _AX5043_AGCAHYST2
                                    702 	.globl _AX5043_AGCAHYST1
                                    703 	.globl _AX5043_AGCAHYST0
                                    704 	.globl _AX5043_XTALSTATUS
                                    705 	.globl _AX5043_XTALCAP
                                    706 	.globl _AX5043_WAKEUPXOEARLY
                                    707 	.globl _AX5043_WAKEUPTIMER1
                                    708 	.globl _AX5043_WAKEUPTIMER0
                                    709 	.globl _AX5043_WAKEUPFREQ1
                                    710 	.globl _AX5043_WAKEUPFREQ0
                                    711 	.globl _AX5043_WAKEUP1
                                    712 	.globl _AX5043_WAKEUP0
                                    713 	.globl _AX5043_TXRATE2
                                    714 	.globl _AX5043_TXRATE1
                                    715 	.globl _AX5043_TXRATE0
                                    716 	.globl _AX5043_TXPWRCOEFFE1
                                    717 	.globl _AX5043_TXPWRCOEFFE0
                                    718 	.globl _AX5043_TXPWRCOEFFD1
                                    719 	.globl _AX5043_TXPWRCOEFFD0
                                    720 	.globl _AX5043_TXPWRCOEFFC1
                                    721 	.globl _AX5043_TXPWRCOEFFC0
                                    722 	.globl _AX5043_TXPWRCOEFFB1
                                    723 	.globl _AX5043_TXPWRCOEFFB0
                                    724 	.globl _AX5043_TXPWRCOEFFA1
                                    725 	.globl _AX5043_TXPWRCOEFFA0
                                    726 	.globl _AX5043_TRKRFFREQ2
                                    727 	.globl _AX5043_TRKRFFREQ1
                                    728 	.globl _AX5043_TRKRFFREQ0
                                    729 	.globl _AX5043_TRKPHASE1
                                    730 	.globl _AX5043_TRKPHASE0
                                    731 	.globl _AX5043_TRKFSKDEMOD1
                                    732 	.globl _AX5043_TRKFSKDEMOD0
                                    733 	.globl _AX5043_TRKFREQ1
                                    734 	.globl _AX5043_TRKFREQ0
                                    735 	.globl _AX5043_TRKDATARATE2
                                    736 	.globl _AX5043_TRKDATARATE1
                                    737 	.globl _AX5043_TRKDATARATE0
                                    738 	.globl _AX5043_TRKAMPLITUDE1
                                    739 	.globl _AX5043_TRKAMPLITUDE0
                                    740 	.globl _AX5043_TRKAFSKDEMOD1
                                    741 	.globl _AX5043_TRKAFSKDEMOD0
                                    742 	.globl _AX5043_TMGTXSETTLE
                                    743 	.globl _AX5043_TMGTXBOOST
                                    744 	.globl _AX5043_TMGRXSETTLE
                                    745 	.globl _AX5043_TMGRXRSSI
                                    746 	.globl _AX5043_TMGRXPREAMBLE3
                                    747 	.globl _AX5043_TMGRXPREAMBLE2
                                    748 	.globl _AX5043_TMGRXPREAMBLE1
                                    749 	.globl _AX5043_TMGRXOFFSACQ
                                    750 	.globl _AX5043_TMGRXCOARSEAGC
                                    751 	.globl _AX5043_TMGRXBOOST
                                    752 	.globl _AX5043_TMGRXAGC
                                    753 	.globl _AX5043_TIMER2
                                    754 	.globl _AX5043_TIMER1
                                    755 	.globl _AX5043_TIMER0
                                    756 	.globl _AX5043_SILICONREVISION
                                    757 	.globl _AX5043_SCRATCH
                                    758 	.globl _AX5043_RXDATARATE2
                                    759 	.globl _AX5043_RXDATARATE1
                                    760 	.globl _AX5043_RXDATARATE0
                                    761 	.globl _AX5043_RSSIREFERENCE
                                    762 	.globl _AX5043_RSSIABSTHR
                                    763 	.globl _AX5043_RSSI
                                    764 	.globl _AX5043_RADIOSTATE
                                    765 	.globl _AX5043_RADIOEVENTREQ1
                                    766 	.globl _AX5043_RADIOEVENTREQ0
                                    767 	.globl _AX5043_RADIOEVENTMASK1
                                    768 	.globl _AX5043_RADIOEVENTMASK0
                                    769 	.globl _AX5043_PWRMODE
                                    770 	.globl _AX5043_PWRAMP
                                    771 	.globl _AX5043_POWSTICKYSTAT
                                    772 	.globl _AX5043_POWSTAT
                                    773 	.globl _AX5043_POWIRQMASK
                                    774 	.globl _AX5043_PLLVCOIR
                                    775 	.globl _AX5043_PLLVCOI
                                    776 	.globl _AX5043_PLLVCODIV
                                    777 	.globl _AX5043_PLLRNGCLK
                                    778 	.globl _AX5043_PLLRANGINGB
                                    779 	.globl _AX5043_PLLRANGINGA
                                    780 	.globl _AX5043_PLLLOOPBOOST
                                    781 	.globl _AX5043_PLLLOOP
                                    782 	.globl _AX5043_PLLLOCKDET
                                    783 	.globl _AX5043_PLLCPIBOOST
                                    784 	.globl _AX5043_PLLCPI
                                    785 	.globl _AX5043_PKTSTOREFLAGS
                                    786 	.globl _AX5043_PKTMISCFLAGS
                                    787 	.globl _AX5043_PKTCHUNKSIZE
                                    788 	.globl _AX5043_PKTACCEPTFLAGS
                                    789 	.globl _AX5043_PINSTATE
                                    790 	.globl _AX5043_PINFUNCSYSCLK
                                    791 	.globl _AX5043_PINFUNCPWRAMP
                                    792 	.globl _AX5043_PINFUNCIRQ
                                    793 	.globl _AX5043_PINFUNCDCLK
                                    794 	.globl _AX5043_PINFUNCDATA
                                    795 	.globl _AX5043_PINFUNCANTSEL
                                    796 	.globl _AX5043_MODULATION
                                    797 	.globl _AX5043_MODCFGF
                                    798 	.globl _AX5043_MODCFGA
                                    799 	.globl _AX5043_MAXRFOFFSET2
                                    800 	.globl _AX5043_MAXRFOFFSET1
                                    801 	.globl _AX5043_MAXRFOFFSET0
                                    802 	.globl _AX5043_MAXDROFFSET2
                                    803 	.globl _AX5043_MAXDROFFSET1
                                    804 	.globl _AX5043_MAXDROFFSET0
                                    805 	.globl _AX5043_MATCH1PAT1
                                    806 	.globl _AX5043_MATCH1PAT0
                                    807 	.globl _AX5043_MATCH1MIN
                                    808 	.globl _AX5043_MATCH1MAX
                                    809 	.globl _AX5043_MATCH1LEN
                                    810 	.globl _AX5043_MATCH0PAT3
                                    811 	.globl _AX5043_MATCH0PAT2
                                    812 	.globl _AX5043_MATCH0PAT1
                                    813 	.globl _AX5043_MATCH0PAT0
                                    814 	.globl _AX5043_MATCH0MIN
                                    815 	.globl _AX5043_MATCH0MAX
                                    816 	.globl _AX5043_MATCH0LEN
                                    817 	.globl _AX5043_LPOSCSTATUS
                                    818 	.globl _AX5043_LPOSCREF1
                                    819 	.globl _AX5043_LPOSCREF0
                                    820 	.globl _AX5043_LPOSCPER1
                                    821 	.globl _AX5043_LPOSCPER0
                                    822 	.globl _AX5043_LPOSCKFILT1
                                    823 	.globl _AX5043_LPOSCKFILT0
                                    824 	.globl _AX5043_LPOSCFREQ1
                                    825 	.globl _AX5043_LPOSCFREQ0
                                    826 	.globl _AX5043_LPOSCCONFIG
                                    827 	.globl _AX5043_IRQREQUEST1
                                    828 	.globl _AX5043_IRQREQUEST0
                                    829 	.globl _AX5043_IRQMASK1
                                    830 	.globl _AX5043_IRQMASK0
                                    831 	.globl _AX5043_IRQINVERSION1
                                    832 	.globl _AX5043_IRQINVERSION0
                                    833 	.globl _AX5043_IFFREQ1
                                    834 	.globl _AX5043_IFFREQ0
                                    835 	.globl _AX5043_GPADCPERIOD
                                    836 	.globl _AX5043_GPADCCTRL
                                    837 	.globl _AX5043_GPADC13VALUE1
                                    838 	.globl _AX5043_GPADC13VALUE0
                                    839 	.globl _AX5043_FSKDMIN1
                                    840 	.globl _AX5043_FSKDMIN0
                                    841 	.globl _AX5043_FSKDMAX1
                                    842 	.globl _AX5043_FSKDMAX0
                                    843 	.globl _AX5043_FSKDEV2
                                    844 	.globl _AX5043_FSKDEV1
                                    845 	.globl _AX5043_FSKDEV0
                                    846 	.globl _AX5043_FREQB3
                                    847 	.globl _AX5043_FREQB2
                                    848 	.globl _AX5043_FREQB1
                                    849 	.globl _AX5043_FREQB0
                                    850 	.globl _AX5043_FREQA3
                                    851 	.globl _AX5043_FREQA2
                                    852 	.globl _AX5043_FREQA1
                                    853 	.globl _AX5043_FREQA0
                                    854 	.globl _AX5043_FRAMING
                                    855 	.globl _AX5043_FIFOTHRESH1
                                    856 	.globl _AX5043_FIFOTHRESH0
                                    857 	.globl _AX5043_FIFOSTAT
                                    858 	.globl _AX5043_FIFOFREE1
                                    859 	.globl _AX5043_FIFOFREE0
                                    860 	.globl _AX5043_FIFODATA
                                    861 	.globl _AX5043_FIFOCOUNT1
                                    862 	.globl _AX5043_FIFOCOUNT0
                                    863 	.globl _AX5043_FECSYNC
                                    864 	.globl _AX5043_FECSTATUS
                                    865 	.globl _AX5043_FEC
                                    866 	.globl _AX5043_ENCODING
                                    867 	.globl _AX5043_DIVERSITY
                                    868 	.globl _AX5043_DECIMATION
                                    869 	.globl _AX5043_DACVALUE1
                                    870 	.globl _AX5043_DACVALUE0
                                    871 	.globl _AX5043_DACCONFIG
                                    872 	.globl _AX5043_CRCINIT3
                                    873 	.globl _AX5043_CRCINIT2
                                    874 	.globl _AX5043_CRCINIT1
                                    875 	.globl _AX5043_CRCINIT0
                                    876 	.globl _AX5043_BGNDRSSITHR
                                    877 	.globl _AX5043_BGNDRSSIGAIN
                                    878 	.globl _AX5043_BGNDRSSI
                                    879 	.globl _AX5043_BBTUNE
                                    880 	.globl _AX5043_BBOFFSCAP
                                    881 	.globl _AX5043_AMPLFILTER
                                    882 	.globl _AX5043_AGCCOUNTER
                                    883 	.globl _AX5043_AFSKSPACE1
                                    884 	.globl _AX5043_AFSKSPACE0
                                    885 	.globl _AX5043_AFSKMARK1
                                    886 	.globl _AX5043_AFSKMARK0
                                    887 	.globl _AX5043_AFSKCTRL
                                    888 	.globl _XWTSTAT
                                    889 	.globl _XWTIRQEN
                                    890 	.globl _XWTEVTD
                                    891 	.globl _XWTEVTD1
                                    892 	.globl _XWTEVTD0
                                    893 	.globl _XWTEVTC
                                    894 	.globl _XWTEVTC1
                                    895 	.globl _XWTEVTC0
                                    896 	.globl _XWTEVTB
                                    897 	.globl _XWTEVTB1
                                    898 	.globl _XWTEVTB0
                                    899 	.globl _XWTEVTA
                                    900 	.globl _XWTEVTA1
                                    901 	.globl _XWTEVTA0
                                    902 	.globl _XWTCNTR1
                                    903 	.globl _XWTCNTB
                                    904 	.globl _XWTCNTB1
                                    905 	.globl _XWTCNTB0
                                    906 	.globl _XWTCNTA
                                    907 	.globl _XWTCNTA1
                                    908 	.globl _XWTCNTA0
                                    909 	.globl _XWTCFGB
                                    910 	.globl _XWTCFGA
                                    911 	.globl _XWDTRESET
                                    912 	.globl _XWDTCFG
                                    913 	.globl _XU1STATUS
                                    914 	.globl _XU1SHREG
                                    915 	.globl _XU1MODE
                                    916 	.globl _XU1CTRL
                                    917 	.globl _XU0STATUS
                                    918 	.globl _XU0SHREG
                                    919 	.globl _XU0MODE
                                    920 	.globl _XU0CTRL
                                    921 	.globl _XT2STATUS
                                    922 	.globl _XT2PERIOD
                                    923 	.globl _XT2PERIOD1
                                    924 	.globl _XT2PERIOD0
                                    925 	.globl _XT2MODE
                                    926 	.globl _XT2CNT
                                    927 	.globl _XT2CNT1
                                    928 	.globl _XT2CNT0
                                    929 	.globl _XT2CLKSRC
                                    930 	.globl _XT1STATUS
                                    931 	.globl _XT1PERIOD
                                    932 	.globl _XT1PERIOD1
                                    933 	.globl _XT1PERIOD0
                                    934 	.globl _XT1MODE
                                    935 	.globl _XT1CNT
                                    936 	.globl _XT1CNT1
                                    937 	.globl _XT1CNT0
                                    938 	.globl _XT1CLKSRC
                                    939 	.globl _XT0STATUS
                                    940 	.globl _XT0PERIOD
                                    941 	.globl _XT0PERIOD1
                                    942 	.globl _XT0PERIOD0
                                    943 	.globl _XT0MODE
                                    944 	.globl _XT0CNT
                                    945 	.globl _XT0CNT1
                                    946 	.globl _XT0CNT0
                                    947 	.globl _XT0CLKSRC
                                    948 	.globl _XSPSTATUS
                                    949 	.globl _XSPSHREG
                                    950 	.globl _XSPMODE
                                    951 	.globl _XSPCLKSRC
                                    952 	.globl _XRADIOSTAT
                                    953 	.globl _XRADIOSTAT1
                                    954 	.globl _XRADIOSTAT0
                                    955 	.globl _XRADIODATA3
                                    956 	.globl _XRADIODATA2
                                    957 	.globl _XRADIODATA1
                                    958 	.globl _XRADIODATA0
                                    959 	.globl _XRADIOADDR1
                                    960 	.globl _XRADIOADDR0
                                    961 	.globl _XRADIOACC
                                    962 	.globl _XOC1STATUS
                                    963 	.globl _XOC1PIN
                                    964 	.globl _XOC1MODE
                                    965 	.globl _XOC1COMP
                                    966 	.globl _XOC1COMP1
                                    967 	.globl _XOC1COMP0
                                    968 	.globl _XOC0STATUS
                                    969 	.globl _XOC0PIN
                                    970 	.globl _XOC0MODE
                                    971 	.globl _XOC0COMP
                                    972 	.globl _XOC0COMP1
                                    973 	.globl _XOC0COMP0
                                    974 	.globl _XNVSTATUS
                                    975 	.globl _XNVKEY
                                    976 	.globl _XNVDATA
                                    977 	.globl _XNVDATA1
                                    978 	.globl _XNVDATA0
                                    979 	.globl _XNVADDR
                                    980 	.globl _XNVADDR1
                                    981 	.globl _XNVADDR0
                                    982 	.globl _XIC1STATUS
                                    983 	.globl _XIC1MODE
                                    984 	.globl _XIC1CAPT
                                    985 	.globl _XIC1CAPT1
                                    986 	.globl _XIC1CAPT0
                                    987 	.globl _XIC0STATUS
                                    988 	.globl _XIC0MODE
                                    989 	.globl _XIC0CAPT
                                    990 	.globl _XIC0CAPT1
                                    991 	.globl _XIC0CAPT0
                                    992 	.globl _XPORTR
                                    993 	.globl _XPORTC
                                    994 	.globl _XPORTB
                                    995 	.globl _XPORTA
                                    996 	.globl _XPINR
                                    997 	.globl _XPINC
                                    998 	.globl _XPINB
                                    999 	.globl _XPINA
                                   1000 	.globl _XDIRR
                                   1001 	.globl _XDIRC
                                   1002 	.globl _XDIRB
                                   1003 	.globl _XDIRA
                                   1004 	.globl _XDBGLNKSTAT
                                   1005 	.globl _XDBGLNKBUF
                                   1006 	.globl _XCODECONFIG
                                   1007 	.globl _XCLKSTAT
                                   1008 	.globl _XCLKCON
                                   1009 	.globl _XANALOGCOMP
                                   1010 	.globl _XADCCONV
                                   1011 	.globl _XADCCLKSRC
                                   1012 	.globl _XADCCH3CONFIG
                                   1013 	.globl _XADCCH2CONFIG
                                   1014 	.globl _XADCCH1CONFIG
                                   1015 	.globl _XADCCH0CONFIG
                                   1016 	.globl _XPCON
                                   1017 	.globl _XIP
                                   1018 	.globl _XIE
                                   1019 	.globl _XDPTR1
                                   1020 	.globl _XDPTR0
                                   1021 	.globl _XTALREADY
                                   1022 	.globl _XTALOSC
                                   1023 	.globl _XTALAMPL
                                   1024 	.globl _SILICONREV
                                   1025 	.globl _SCRATCH3
                                   1026 	.globl _SCRATCH2
                                   1027 	.globl _SCRATCH1
                                   1028 	.globl _SCRATCH0
                                   1029 	.globl _RADIOMUX
                                   1030 	.globl _RADIOFSTATADDR
                                   1031 	.globl _RADIOFSTATADDR1
                                   1032 	.globl _RADIOFSTATADDR0
                                   1033 	.globl _RADIOFDATAADDR
                                   1034 	.globl _RADIOFDATAADDR1
                                   1035 	.globl _RADIOFDATAADDR0
                                   1036 	.globl _OSCRUN
                                   1037 	.globl _OSCREADY
                                   1038 	.globl _OSCFORCERUN
                                   1039 	.globl _OSCCALIB
                                   1040 	.globl _MISCCTRL
                                   1041 	.globl _LPXOSCGM
                                   1042 	.globl _LPOSCREF
                                   1043 	.globl _LPOSCREF1
                                   1044 	.globl _LPOSCREF0
                                   1045 	.globl _LPOSCPER
                                   1046 	.globl _LPOSCPER1
                                   1047 	.globl _LPOSCPER0
                                   1048 	.globl _LPOSCKFILT
                                   1049 	.globl _LPOSCKFILT1
                                   1050 	.globl _LPOSCKFILT0
                                   1051 	.globl _LPOSCFREQ
                                   1052 	.globl _LPOSCFREQ1
                                   1053 	.globl _LPOSCFREQ0
                                   1054 	.globl _LPOSCCONFIG
                                   1055 	.globl _PINSEL
                                   1056 	.globl _PINCHGC
                                   1057 	.globl _PINCHGB
                                   1058 	.globl _PINCHGA
                                   1059 	.globl _PALTRADIO
                                   1060 	.globl _PALTC
                                   1061 	.globl _PALTB
                                   1062 	.globl _PALTA
                                   1063 	.globl _INTCHGC
                                   1064 	.globl _INTCHGB
                                   1065 	.globl _INTCHGA
                                   1066 	.globl _EXTIRQ
                                   1067 	.globl _GPIOENABLE
                                   1068 	.globl _ANALOGA
                                   1069 	.globl _FRCOSCREF
                                   1070 	.globl _FRCOSCREF1
                                   1071 	.globl _FRCOSCREF0
                                   1072 	.globl _FRCOSCPER
                                   1073 	.globl _FRCOSCPER1
                                   1074 	.globl _FRCOSCPER0
                                   1075 	.globl _FRCOSCKFILT
                                   1076 	.globl _FRCOSCKFILT1
                                   1077 	.globl _FRCOSCKFILT0
                                   1078 	.globl _FRCOSCFREQ
                                   1079 	.globl _FRCOSCFREQ1
                                   1080 	.globl _FRCOSCFREQ0
                                   1081 	.globl _FRCOSCCTRL
                                   1082 	.globl _FRCOSCCONFIG
                                   1083 	.globl _DMA1CONFIG
                                   1084 	.globl _DMA1ADDR
                                   1085 	.globl _DMA1ADDR1
                                   1086 	.globl _DMA1ADDR0
                                   1087 	.globl _DMA0CONFIG
                                   1088 	.globl _DMA0ADDR
                                   1089 	.globl _DMA0ADDR1
                                   1090 	.globl _DMA0ADDR0
                                   1091 	.globl _ADCTUNE2
                                   1092 	.globl _ADCTUNE1
                                   1093 	.globl _ADCTUNE0
                                   1094 	.globl _ADCCH3VAL
                                   1095 	.globl _ADCCH3VAL1
                                   1096 	.globl _ADCCH3VAL0
                                   1097 	.globl _ADCCH2VAL
                                   1098 	.globl _ADCCH2VAL1
                                   1099 	.globl _ADCCH2VAL0
                                   1100 	.globl _ADCCH1VAL
                                   1101 	.globl _ADCCH1VAL1
                                   1102 	.globl _ADCCH1VAL0
                                   1103 	.globl _ADCCH0VAL
                                   1104 	.globl _ADCCH0VAL1
                                   1105 	.globl _ADCCH0VAL0
                                   1106 	.globl _acquire_agc
                                   1107 	.globl _errors2
                                   1108 	.globl _errors
                                   1109 	.globl _bytes
                                   1110 	.globl _scr
                                   1111 	.globl _coldstart
                                   1112 	.globl _axradio_statuschange
                                   1113 ;--------------------------------------------------------
                                   1114 ; special function registers
                                   1115 ;--------------------------------------------------------
                                   1116 	.area RSEG    (ABS,DATA)
      000000                       1117 	.org 0x0000
                           0000E0  1118 G$ACC$0$0 == 0x00e0
                           0000E0  1119 _ACC	=	0x00e0
                           0000F0  1120 G$B$0$0 == 0x00f0
                           0000F0  1121 _B	=	0x00f0
                           000083  1122 G$DPH$0$0 == 0x0083
                           000083  1123 _DPH	=	0x0083
                           000085  1124 G$DPH1$0$0 == 0x0085
                           000085  1125 _DPH1	=	0x0085
                           000082  1126 G$DPL$0$0 == 0x0082
                           000082  1127 _DPL	=	0x0082
                           000084  1128 G$DPL1$0$0 == 0x0084
                           000084  1129 _DPL1	=	0x0084
                           008382  1130 G$DPTR0$0$0 == 0x8382
                           008382  1131 _DPTR0	=	0x8382
                           008584  1132 G$DPTR1$0$0 == 0x8584
                           008584  1133 _DPTR1	=	0x8584
                           000086  1134 G$DPS$0$0 == 0x0086
                           000086  1135 _DPS	=	0x0086
                           0000A0  1136 G$E2IE$0$0 == 0x00a0
                           0000A0  1137 _E2IE	=	0x00a0
                           0000C0  1138 G$E2IP$0$0 == 0x00c0
                           0000C0  1139 _E2IP	=	0x00c0
                           000098  1140 G$EIE$0$0 == 0x0098
                           000098  1141 _EIE	=	0x0098
                           0000B0  1142 G$EIP$0$0 == 0x00b0
                           0000B0  1143 _EIP	=	0x00b0
                           0000A8  1144 G$IE$0$0 == 0x00a8
                           0000A8  1145 _IE	=	0x00a8
                           0000B8  1146 G$IP$0$0 == 0x00b8
                           0000B8  1147 _IP	=	0x00b8
                           000087  1148 G$PCON$0$0 == 0x0087
                           000087  1149 _PCON	=	0x0087
                           0000D0  1150 G$PSW$0$0 == 0x00d0
                           0000D0  1151 _PSW	=	0x00d0
                           000081  1152 G$SP$0$0 == 0x0081
                           000081  1153 _SP	=	0x0081
                           0000D9  1154 G$XPAGE$0$0 == 0x00d9
                           0000D9  1155 _XPAGE	=	0x00d9
                           0000D9  1156 G$_XPAGE$0$0 == 0x00d9
                           0000D9  1157 __XPAGE	=	0x00d9
                           0000CA  1158 G$ADCCH0CONFIG$0$0 == 0x00ca
                           0000CA  1159 _ADCCH0CONFIG	=	0x00ca
                           0000CB  1160 G$ADCCH1CONFIG$0$0 == 0x00cb
                           0000CB  1161 _ADCCH1CONFIG	=	0x00cb
                           0000D2  1162 G$ADCCH2CONFIG$0$0 == 0x00d2
                           0000D2  1163 _ADCCH2CONFIG	=	0x00d2
                           0000D3  1164 G$ADCCH3CONFIG$0$0 == 0x00d3
                           0000D3  1165 _ADCCH3CONFIG	=	0x00d3
                           0000D1  1166 G$ADCCLKSRC$0$0 == 0x00d1
                           0000D1  1167 _ADCCLKSRC	=	0x00d1
                           0000C9  1168 G$ADCCONV$0$0 == 0x00c9
                           0000C9  1169 _ADCCONV	=	0x00c9
                           0000E1  1170 G$ANALOGCOMP$0$0 == 0x00e1
                           0000E1  1171 _ANALOGCOMP	=	0x00e1
                           0000C6  1172 G$CLKCON$0$0 == 0x00c6
                           0000C6  1173 _CLKCON	=	0x00c6
                           0000C7  1174 G$CLKSTAT$0$0 == 0x00c7
                           0000C7  1175 _CLKSTAT	=	0x00c7
                           000097  1176 G$CODECONFIG$0$0 == 0x0097
                           000097  1177 _CODECONFIG	=	0x0097
                           0000E3  1178 G$DBGLNKBUF$0$0 == 0x00e3
                           0000E3  1179 _DBGLNKBUF	=	0x00e3
                           0000E2  1180 G$DBGLNKSTAT$0$0 == 0x00e2
                           0000E2  1181 _DBGLNKSTAT	=	0x00e2
                           000089  1182 G$DIRA$0$0 == 0x0089
                           000089  1183 _DIRA	=	0x0089
                           00008A  1184 G$DIRB$0$0 == 0x008a
                           00008A  1185 _DIRB	=	0x008a
                           00008B  1186 G$DIRC$0$0 == 0x008b
                           00008B  1187 _DIRC	=	0x008b
                           00008E  1188 G$DIRR$0$0 == 0x008e
                           00008E  1189 _DIRR	=	0x008e
                           0000C8  1190 G$PINA$0$0 == 0x00c8
                           0000C8  1191 _PINA	=	0x00c8
                           0000E8  1192 G$PINB$0$0 == 0x00e8
                           0000E8  1193 _PINB	=	0x00e8
                           0000F8  1194 G$PINC$0$0 == 0x00f8
                           0000F8  1195 _PINC	=	0x00f8
                           00008D  1196 G$PINR$0$0 == 0x008d
                           00008D  1197 _PINR	=	0x008d
                           000080  1198 G$PORTA$0$0 == 0x0080
                           000080  1199 _PORTA	=	0x0080
                           000088  1200 G$PORTB$0$0 == 0x0088
                           000088  1201 _PORTB	=	0x0088
                           000090  1202 G$PORTC$0$0 == 0x0090
                           000090  1203 _PORTC	=	0x0090
                           00008C  1204 G$PORTR$0$0 == 0x008c
                           00008C  1205 _PORTR	=	0x008c
                           0000CE  1206 G$IC0CAPT0$0$0 == 0x00ce
                           0000CE  1207 _IC0CAPT0	=	0x00ce
                           0000CF  1208 G$IC0CAPT1$0$0 == 0x00cf
                           0000CF  1209 _IC0CAPT1	=	0x00cf
                           00CFCE  1210 G$IC0CAPT$0$0 == 0xcfce
                           00CFCE  1211 _IC0CAPT	=	0xcfce
                           0000CC  1212 G$IC0MODE$0$0 == 0x00cc
                           0000CC  1213 _IC0MODE	=	0x00cc
                           0000CD  1214 G$IC0STATUS$0$0 == 0x00cd
                           0000CD  1215 _IC0STATUS	=	0x00cd
                           0000D6  1216 G$IC1CAPT0$0$0 == 0x00d6
                           0000D6  1217 _IC1CAPT0	=	0x00d6
                           0000D7  1218 G$IC1CAPT1$0$0 == 0x00d7
                           0000D7  1219 _IC1CAPT1	=	0x00d7
                           00D7D6  1220 G$IC1CAPT$0$0 == 0xd7d6
                           00D7D6  1221 _IC1CAPT	=	0xd7d6
                           0000D4  1222 G$IC1MODE$0$0 == 0x00d4
                           0000D4  1223 _IC1MODE	=	0x00d4
                           0000D5  1224 G$IC1STATUS$0$0 == 0x00d5
                           0000D5  1225 _IC1STATUS	=	0x00d5
                           000092  1226 G$NVADDR0$0$0 == 0x0092
                           000092  1227 _NVADDR0	=	0x0092
                           000093  1228 G$NVADDR1$0$0 == 0x0093
                           000093  1229 _NVADDR1	=	0x0093
                           009392  1230 G$NVADDR$0$0 == 0x9392
                           009392  1231 _NVADDR	=	0x9392
                           000094  1232 G$NVDATA0$0$0 == 0x0094
                           000094  1233 _NVDATA0	=	0x0094
                           000095  1234 G$NVDATA1$0$0 == 0x0095
                           000095  1235 _NVDATA1	=	0x0095
                           009594  1236 G$NVDATA$0$0 == 0x9594
                           009594  1237 _NVDATA	=	0x9594
                           000096  1238 G$NVKEY$0$0 == 0x0096
                           000096  1239 _NVKEY	=	0x0096
                           000091  1240 G$NVSTATUS$0$0 == 0x0091
                           000091  1241 _NVSTATUS	=	0x0091
                           0000BC  1242 G$OC0COMP0$0$0 == 0x00bc
                           0000BC  1243 _OC0COMP0	=	0x00bc
                           0000BD  1244 G$OC0COMP1$0$0 == 0x00bd
                           0000BD  1245 _OC0COMP1	=	0x00bd
                           00BDBC  1246 G$OC0COMP$0$0 == 0xbdbc
                           00BDBC  1247 _OC0COMP	=	0xbdbc
                           0000B9  1248 G$OC0MODE$0$0 == 0x00b9
                           0000B9  1249 _OC0MODE	=	0x00b9
                           0000BA  1250 G$OC0PIN$0$0 == 0x00ba
                           0000BA  1251 _OC0PIN	=	0x00ba
                           0000BB  1252 G$OC0STATUS$0$0 == 0x00bb
                           0000BB  1253 _OC0STATUS	=	0x00bb
                           0000C4  1254 G$OC1COMP0$0$0 == 0x00c4
                           0000C4  1255 _OC1COMP0	=	0x00c4
                           0000C5  1256 G$OC1COMP1$0$0 == 0x00c5
                           0000C5  1257 _OC1COMP1	=	0x00c5
                           00C5C4  1258 G$OC1COMP$0$0 == 0xc5c4
                           00C5C4  1259 _OC1COMP	=	0xc5c4
                           0000C1  1260 G$OC1MODE$0$0 == 0x00c1
                           0000C1  1261 _OC1MODE	=	0x00c1
                           0000C2  1262 G$OC1PIN$0$0 == 0x00c2
                           0000C2  1263 _OC1PIN	=	0x00c2
                           0000C3  1264 G$OC1STATUS$0$0 == 0x00c3
                           0000C3  1265 _OC1STATUS	=	0x00c3
                           0000B1  1266 G$RADIOACC$0$0 == 0x00b1
                           0000B1  1267 _RADIOACC	=	0x00b1
                           0000B3  1268 G$RADIOADDR0$0$0 == 0x00b3
                           0000B3  1269 _RADIOADDR0	=	0x00b3
                           0000B2  1270 G$RADIOADDR1$0$0 == 0x00b2
                           0000B2  1271 _RADIOADDR1	=	0x00b2
                           00B2B3  1272 G$RADIOADDR$0$0 == 0xb2b3
                           00B2B3  1273 _RADIOADDR	=	0xb2b3
                           0000B7  1274 G$RADIODATA0$0$0 == 0x00b7
                           0000B7  1275 _RADIODATA0	=	0x00b7
                           0000B6  1276 G$RADIODATA1$0$0 == 0x00b6
                           0000B6  1277 _RADIODATA1	=	0x00b6
                           0000B5  1278 G$RADIODATA2$0$0 == 0x00b5
                           0000B5  1279 _RADIODATA2	=	0x00b5
                           0000B4  1280 G$RADIODATA3$0$0 == 0x00b4
                           0000B4  1281 _RADIODATA3	=	0x00b4
                           B4B5B6B7  1282 G$RADIODATA$0$0 == 0xb4b5b6b7
                           B4B5B6B7  1283 _RADIODATA	=	0xb4b5b6b7
                           0000BE  1284 G$RADIOSTAT0$0$0 == 0x00be
                           0000BE  1285 _RADIOSTAT0	=	0x00be
                           0000BF  1286 G$RADIOSTAT1$0$0 == 0x00bf
                           0000BF  1287 _RADIOSTAT1	=	0x00bf
                           00BFBE  1288 G$RADIOSTAT$0$0 == 0xbfbe
                           00BFBE  1289 _RADIOSTAT	=	0xbfbe
                           0000DF  1290 G$SPCLKSRC$0$0 == 0x00df
                           0000DF  1291 _SPCLKSRC	=	0x00df
                           0000DC  1292 G$SPMODE$0$0 == 0x00dc
                           0000DC  1293 _SPMODE	=	0x00dc
                           0000DE  1294 G$SPSHREG$0$0 == 0x00de
                           0000DE  1295 _SPSHREG	=	0x00de
                           0000DD  1296 G$SPSTATUS$0$0 == 0x00dd
                           0000DD  1297 _SPSTATUS	=	0x00dd
                           00009A  1298 G$T0CLKSRC$0$0 == 0x009a
                           00009A  1299 _T0CLKSRC	=	0x009a
                           00009C  1300 G$T0CNT0$0$0 == 0x009c
                           00009C  1301 _T0CNT0	=	0x009c
                           00009D  1302 G$T0CNT1$0$0 == 0x009d
                           00009D  1303 _T0CNT1	=	0x009d
                           009D9C  1304 G$T0CNT$0$0 == 0x9d9c
                           009D9C  1305 _T0CNT	=	0x9d9c
                           000099  1306 G$T0MODE$0$0 == 0x0099
                           000099  1307 _T0MODE	=	0x0099
                           00009E  1308 G$T0PERIOD0$0$0 == 0x009e
                           00009E  1309 _T0PERIOD0	=	0x009e
                           00009F  1310 G$T0PERIOD1$0$0 == 0x009f
                           00009F  1311 _T0PERIOD1	=	0x009f
                           009F9E  1312 G$T0PERIOD$0$0 == 0x9f9e
                           009F9E  1313 _T0PERIOD	=	0x9f9e
                           00009B  1314 G$T0STATUS$0$0 == 0x009b
                           00009B  1315 _T0STATUS	=	0x009b
                           0000A2  1316 G$T1CLKSRC$0$0 == 0x00a2
                           0000A2  1317 _T1CLKSRC	=	0x00a2
                           0000A4  1318 G$T1CNT0$0$0 == 0x00a4
                           0000A4  1319 _T1CNT0	=	0x00a4
                           0000A5  1320 G$T1CNT1$0$0 == 0x00a5
                           0000A5  1321 _T1CNT1	=	0x00a5
                           00A5A4  1322 G$T1CNT$0$0 == 0xa5a4
                           00A5A4  1323 _T1CNT	=	0xa5a4
                           0000A1  1324 G$T1MODE$0$0 == 0x00a1
                           0000A1  1325 _T1MODE	=	0x00a1
                           0000A6  1326 G$T1PERIOD0$0$0 == 0x00a6
                           0000A6  1327 _T1PERIOD0	=	0x00a6
                           0000A7  1328 G$T1PERIOD1$0$0 == 0x00a7
                           0000A7  1329 _T1PERIOD1	=	0x00a7
                           00A7A6  1330 G$T1PERIOD$0$0 == 0xa7a6
                           00A7A6  1331 _T1PERIOD	=	0xa7a6
                           0000A3  1332 G$T1STATUS$0$0 == 0x00a3
                           0000A3  1333 _T1STATUS	=	0x00a3
                           0000AA  1334 G$T2CLKSRC$0$0 == 0x00aa
                           0000AA  1335 _T2CLKSRC	=	0x00aa
                           0000AC  1336 G$T2CNT0$0$0 == 0x00ac
                           0000AC  1337 _T2CNT0	=	0x00ac
                           0000AD  1338 G$T2CNT1$0$0 == 0x00ad
                           0000AD  1339 _T2CNT1	=	0x00ad
                           00ADAC  1340 G$T2CNT$0$0 == 0xadac
                           00ADAC  1341 _T2CNT	=	0xadac
                           0000A9  1342 G$T2MODE$0$0 == 0x00a9
                           0000A9  1343 _T2MODE	=	0x00a9
                           0000AE  1344 G$T2PERIOD0$0$0 == 0x00ae
                           0000AE  1345 _T2PERIOD0	=	0x00ae
                           0000AF  1346 G$T2PERIOD1$0$0 == 0x00af
                           0000AF  1347 _T2PERIOD1	=	0x00af
                           00AFAE  1348 G$T2PERIOD$0$0 == 0xafae
                           00AFAE  1349 _T2PERIOD	=	0xafae
                           0000AB  1350 G$T2STATUS$0$0 == 0x00ab
                           0000AB  1351 _T2STATUS	=	0x00ab
                           0000E4  1352 G$U0CTRL$0$0 == 0x00e4
                           0000E4  1353 _U0CTRL	=	0x00e4
                           0000E7  1354 G$U0MODE$0$0 == 0x00e7
                           0000E7  1355 _U0MODE	=	0x00e7
                           0000E6  1356 G$U0SHREG$0$0 == 0x00e6
                           0000E6  1357 _U0SHREG	=	0x00e6
                           0000E5  1358 G$U0STATUS$0$0 == 0x00e5
                           0000E5  1359 _U0STATUS	=	0x00e5
                           0000EC  1360 G$U1CTRL$0$0 == 0x00ec
                           0000EC  1361 _U1CTRL	=	0x00ec
                           0000EF  1362 G$U1MODE$0$0 == 0x00ef
                           0000EF  1363 _U1MODE	=	0x00ef
                           0000EE  1364 G$U1SHREG$0$0 == 0x00ee
                           0000EE  1365 _U1SHREG	=	0x00ee
                           0000ED  1366 G$U1STATUS$0$0 == 0x00ed
                           0000ED  1367 _U1STATUS	=	0x00ed
                           0000DA  1368 G$WDTCFG$0$0 == 0x00da
                           0000DA  1369 _WDTCFG	=	0x00da
                           0000DB  1370 G$WDTRESET$0$0 == 0x00db
                           0000DB  1371 _WDTRESET	=	0x00db
                           0000F1  1372 G$WTCFGA$0$0 == 0x00f1
                           0000F1  1373 _WTCFGA	=	0x00f1
                           0000F9  1374 G$WTCFGB$0$0 == 0x00f9
                           0000F9  1375 _WTCFGB	=	0x00f9
                           0000F2  1376 G$WTCNTA0$0$0 == 0x00f2
                           0000F2  1377 _WTCNTA0	=	0x00f2
                           0000F3  1378 G$WTCNTA1$0$0 == 0x00f3
                           0000F3  1379 _WTCNTA1	=	0x00f3
                           00F3F2  1380 G$WTCNTA$0$0 == 0xf3f2
                           00F3F2  1381 _WTCNTA	=	0xf3f2
                           0000FA  1382 G$WTCNTB0$0$0 == 0x00fa
                           0000FA  1383 _WTCNTB0	=	0x00fa
                           0000FB  1384 G$WTCNTB1$0$0 == 0x00fb
                           0000FB  1385 _WTCNTB1	=	0x00fb
                           00FBFA  1386 G$WTCNTB$0$0 == 0xfbfa
                           00FBFA  1387 _WTCNTB	=	0xfbfa
                           0000EB  1388 G$WTCNTR1$0$0 == 0x00eb
                           0000EB  1389 _WTCNTR1	=	0x00eb
                           0000F4  1390 G$WTEVTA0$0$0 == 0x00f4
                           0000F4  1391 _WTEVTA0	=	0x00f4
                           0000F5  1392 G$WTEVTA1$0$0 == 0x00f5
                           0000F5  1393 _WTEVTA1	=	0x00f5
                           00F5F4  1394 G$WTEVTA$0$0 == 0xf5f4
                           00F5F4  1395 _WTEVTA	=	0xf5f4
                           0000F6  1396 G$WTEVTB0$0$0 == 0x00f6
                           0000F6  1397 _WTEVTB0	=	0x00f6
                           0000F7  1398 G$WTEVTB1$0$0 == 0x00f7
                           0000F7  1399 _WTEVTB1	=	0x00f7
                           00F7F6  1400 G$WTEVTB$0$0 == 0xf7f6
                           00F7F6  1401 _WTEVTB	=	0xf7f6
                           0000FC  1402 G$WTEVTC0$0$0 == 0x00fc
                           0000FC  1403 _WTEVTC0	=	0x00fc
                           0000FD  1404 G$WTEVTC1$0$0 == 0x00fd
                           0000FD  1405 _WTEVTC1	=	0x00fd
                           00FDFC  1406 G$WTEVTC$0$0 == 0xfdfc
                           00FDFC  1407 _WTEVTC	=	0xfdfc
                           0000FE  1408 G$WTEVTD0$0$0 == 0x00fe
                           0000FE  1409 _WTEVTD0	=	0x00fe
                           0000FF  1410 G$WTEVTD1$0$0 == 0x00ff
                           0000FF  1411 _WTEVTD1	=	0x00ff
                           00FFFE  1412 G$WTEVTD$0$0 == 0xfffe
                           00FFFE  1413 _WTEVTD	=	0xfffe
                           0000E9  1414 G$WTIRQEN$0$0 == 0x00e9
                           0000E9  1415 _WTIRQEN	=	0x00e9
                           0000EA  1416 G$WTSTAT$0$0 == 0x00ea
                           0000EA  1417 _WTSTAT	=	0x00ea
                                   1418 ;--------------------------------------------------------
                                   1419 ; special function bits
                                   1420 ;--------------------------------------------------------
                                   1421 	.area RSEG    (ABS,DATA)
      000000                       1422 	.org 0x0000
                           0000E0  1423 G$ACC_0$0$0 == 0x00e0
                           0000E0  1424 _ACC_0	=	0x00e0
                           0000E1  1425 G$ACC_1$0$0 == 0x00e1
                           0000E1  1426 _ACC_1	=	0x00e1
                           0000E2  1427 G$ACC_2$0$0 == 0x00e2
                           0000E2  1428 _ACC_2	=	0x00e2
                           0000E3  1429 G$ACC_3$0$0 == 0x00e3
                           0000E3  1430 _ACC_3	=	0x00e3
                           0000E4  1431 G$ACC_4$0$0 == 0x00e4
                           0000E4  1432 _ACC_4	=	0x00e4
                           0000E5  1433 G$ACC_5$0$0 == 0x00e5
                           0000E5  1434 _ACC_5	=	0x00e5
                           0000E6  1435 G$ACC_6$0$0 == 0x00e6
                           0000E6  1436 _ACC_6	=	0x00e6
                           0000E7  1437 G$ACC_7$0$0 == 0x00e7
                           0000E7  1438 _ACC_7	=	0x00e7
                           0000F0  1439 G$B_0$0$0 == 0x00f0
                           0000F0  1440 _B_0	=	0x00f0
                           0000F1  1441 G$B_1$0$0 == 0x00f1
                           0000F1  1442 _B_1	=	0x00f1
                           0000F2  1443 G$B_2$0$0 == 0x00f2
                           0000F2  1444 _B_2	=	0x00f2
                           0000F3  1445 G$B_3$0$0 == 0x00f3
                           0000F3  1446 _B_3	=	0x00f3
                           0000F4  1447 G$B_4$0$0 == 0x00f4
                           0000F4  1448 _B_4	=	0x00f4
                           0000F5  1449 G$B_5$0$0 == 0x00f5
                           0000F5  1450 _B_5	=	0x00f5
                           0000F6  1451 G$B_6$0$0 == 0x00f6
                           0000F6  1452 _B_6	=	0x00f6
                           0000F7  1453 G$B_7$0$0 == 0x00f7
                           0000F7  1454 _B_7	=	0x00f7
                           0000A0  1455 G$E2IE_0$0$0 == 0x00a0
                           0000A0  1456 _E2IE_0	=	0x00a0
                           0000A1  1457 G$E2IE_1$0$0 == 0x00a1
                           0000A1  1458 _E2IE_1	=	0x00a1
                           0000A2  1459 G$E2IE_2$0$0 == 0x00a2
                           0000A2  1460 _E2IE_2	=	0x00a2
                           0000A3  1461 G$E2IE_3$0$0 == 0x00a3
                           0000A3  1462 _E2IE_3	=	0x00a3
                           0000A4  1463 G$E2IE_4$0$0 == 0x00a4
                           0000A4  1464 _E2IE_4	=	0x00a4
                           0000A5  1465 G$E2IE_5$0$0 == 0x00a5
                           0000A5  1466 _E2IE_5	=	0x00a5
                           0000A6  1467 G$E2IE_6$0$0 == 0x00a6
                           0000A6  1468 _E2IE_6	=	0x00a6
                           0000A7  1469 G$E2IE_7$0$0 == 0x00a7
                           0000A7  1470 _E2IE_7	=	0x00a7
                           0000C0  1471 G$E2IP_0$0$0 == 0x00c0
                           0000C0  1472 _E2IP_0	=	0x00c0
                           0000C1  1473 G$E2IP_1$0$0 == 0x00c1
                           0000C1  1474 _E2IP_1	=	0x00c1
                           0000C2  1475 G$E2IP_2$0$0 == 0x00c2
                           0000C2  1476 _E2IP_2	=	0x00c2
                           0000C3  1477 G$E2IP_3$0$0 == 0x00c3
                           0000C3  1478 _E2IP_3	=	0x00c3
                           0000C4  1479 G$E2IP_4$0$0 == 0x00c4
                           0000C4  1480 _E2IP_4	=	0x00c4
                           0000C5  1481 G$E2IP_5$0$0 == 0x00c5
                           0000C5  1482 _E2IP_5	=	0x00c5
                           0000C6  1483 G$E2IP_6$0$0 == 0x00c6
                           0000C6  1484 _E2IP_6	=	0x00c6
                           0000C7  1485 G$E2IP_7$0$0 == 0x00c7
                           0000C7  1486 _E2IP_7	=	0x00c7
                           000098  1487 G$EIE_0$0$0 == 0x0098
                           000098  1488 _EIE_0	=	0x0098
                           000099  1489 G$EIE_1$0$0 == 0x0099
                           000099  1490 _EIE_1	=	0x0099
                           00009A  1491 G$EIE_2$0$0 == 0x009a
                           00009A  1492 _EIE_2	=	0x009a
                           00009B  1493 G$EIE_3$0$0 == 0x009b
                           00009B  1494 _EIE_3	=	0x009b
                           00009C  1495 G$EIE_4$0$0 == 0x009c
                           00009C  1496 _EIE_4	=	0x009c
                           00009D  1497 G$EIE_5$0$0 == 0x009d
                           00009D  1498 _EIE_5	=	0x009d
                           00009E  1499 G$EIE_6$0$0 == 0x009e
                           00009E  1500 _EIE_6	=	0x009e
                           00009F  1501 G$EIE_7$0$0 == 0x009f
                           00009F  1502 _EIE_7	=	0x009f
                           0000B0  1503 G$EIP_0$0$0 == 0x00b0
                           0000B0  1504 _EIP_0	=	0x00b0
                           0000B1  1505 G$EIP_1$0$0 == 0x00b1
                           0000B1  1506 _EIP_1	=	0x00b1
                           0000B2  1507 G$EIP_2$0$0 == 0x00b2
                           0000B2  1508 _EIP_2	=	0x00b2
                           0000B3  1509 G$EIP_3$0$0 == 0x00b3
                           0000B3  1510 _EIP_3	=	0x00b3
                           0000B4  1511 G$EIP_4$0$0 == 0x00b4
                           0000B4  1512 _EIP_4	=	0x00b4
                           0000B5  1513 G$EIP_5$0$0 == 0x00b5
                           0000B5  1514 _EIP_5	=	0x00b5
                           0000B6  1515 G$EIP_6$0$0 == 0x00b6
                           0000B6  1516 _EIP_6	=	0x00b6
                           0000B7  1517 G$EIP_7$0$0 == 0x00b7
                           0000B7  1518 _EIP_7	=	0x00b7
                           0000A8  1519 G$IE_0$0$0 == 0x00a8
                           0000A8  1520 _IE_0	=	0x00a8
                           0000A9  1521 G$IE_1$0$0 == 0x00a9
                           0000A9  1522 _IE_1	=	0x00a9
                           0000AA  1523 G$IE_2$0$0 == 0x00aa
                           0000AA  1524 _IE_2	=	0x00aa
                           0000AB  1525 G$IE_3$0$0 == 0x00ab
                           0000AB  1526 _IE_3	=	0x00ab
                           0000AC  1527 G$IE_4$0$0 == 0x00ac
                           0000AC  1528 _IE_4	=	0x00ac
                           0000AD  1529 G$IE_5$0$0 == 0x00ad
                           0000AD  1530 _IE_5	=	0x00ad
                           0000AE  1531 G$IE_6$0$0 == 0x00ae
                           0000AE  1532 _IE_6	=	0x00ae
                           0000AF  1533 G$IE_7$0$0 == 0x00af
                           0000AF  1534 _IE_7	=	0x00af
                           0000AF  1535 G$EA$0$0 == 0x00af
                           0000AF  1536 _EA	=	0x00af
                           0000B8  1537 G$IP_0$0$0 == 0x00b8
                           0000B8  1538 _IP_0	=	0x00b8
                           0000B9  1539 G$IP_1$0$0 == 0x00b9
                           0000B9  1540 _IP_1	=	0x00b9
                           0000BA  1541 G$IP_2$0$0 == 0x00ba
                           0000BA  1542 _IP_2	=	0x00ba
                           0000BB  1543 G$IP_3$0$0 == 0x00bb
                           0000BB  1544 _IP_3	=	0x00bb
                           0000BC  1545 G$IP_4$0$0 == 0x00bc
                           0000BC  1546 _IP_4	=	0x00bc
                           0000BD  1547 G$IP_5$0$0 == 0x00bd
                           0000BD  1548 _IP_5	=	0x00bd
                           0000BE  1549 G$IP_6$0$0 == 0x00be
                           0000BE  1550 _IP_6	=	0x00be
                           0000BF  1551 G$IP_7$0$0 == 0x00bf
                           0000BF  1552 _IP_7	=	0x00bf
                           0000D0  1553 G$P$0$0 == 0x00d0
                           0000D0  1554 _P	=	0x00d0
                           0000D1  1555 G$F1$0$0 == 0x00d1
                           0000D1  1556 _F1	=	0x00d1
                           0000D2  1557 G$OV$0$0 == 0x00d2
                           0000D2  1558 _OV	=	0x00d2
                           0000D3  1559 G$RS0$0$0 == 0x00d3
                           0000D3  1560 _RS0	=	0x00d3
                           0000D4  1561 G$RS1$0$0 == 0x00d4
                           0000D4  1562 _RS1	=	0x00d4
                           0000D5  1563 G$F0$0$0 == 0x00d5
                           0000D5  1564 _F0	=	0x00d5
                           0000D6  1565 G$AC$0$0 == 0x00d6
                           0000D6  1566 _AC	=	0x00d6
                           0000D7  1567 G$CY$0$0 == 0x00d7
                           0000D7  1568 _CY	=	0x00d7
                           0000C8  1569 G$PINA_0$0$0 == 0x00c8
                           0000C8  1570 _PINA_0	=	0x00c8
                           0000C9  1571 G$PINA_1$0$0 == 0x00c9
                           0000C9  1572 _PINA_1	=	0x00c9
                           0000CA  1573 G$PINA_2$0$0 == 0x00ca
                           0000CA  1574 _PINA_2	=	0x00ca
                           0000CB  1575 G$PINA_3$0$0 == 0x00cb
                           0000CB  1576 _PINA_3	=	0x00cb
                           0000CC  1577 G$PINA_4$0$0 == 0x00cc
                           0000CC  1578 _PINA_4	=	0x00cc
                           0000CD  1579 G$PINA_5$0$0 == 0x00cd
                           0000CD  1580 _PINA_5	=	0x00cd
                           0000CE  1581 G$PINA_6$0$0 == 0x00ce
                           0000CE  1582 _PINA_6	=	0x00ce
                           0000CF  1583 G$PINA_7$0$0 == 0x00cf
                           0000CF  1584 _PINA_7	=	0x00cf
                           0000E8  1585 G$PINB_0$0$0 == 0x00e8
                           0000E8  1586 _PINB_0	=	0x00e8
                           0000E9  1587 G$PINB_1$0$0 == 0x00e9
                           0000E9  1588 _PINB_1	=	0x00e9
                           0000EA  1589 G$PINB_2$0$0 == 0x00ea
                           0000EA  1590 _PINB_2	=	0x00ea
                           0000EB  1591 G$PINB_3$0$0 == 0x00eb
                           0000EB  1592 _PINB_3	=	0x00eb
                           0000EC  1593 G$PINB_4$0$0 == 0x00ec
                           0000EC  1594 _PINB_4	=	0x00ec
                           0000ED  1595 G$PINB_5$0$0 == 0x00ed
                           0000ED  1596 _PINB_5	=	0x00ed
                           0000EE  1597 G$PINB_6$0$0 == 0x00ee
                           0000EE  1598 _PINB_6	=	0x00ee
                           0000EF  1599 G$PINB_7$0$0 == 0x00ef
                           0000EF  1600 _PINB_7	=	0x00ef
                           0000F8  1601 G$PINC_0$0$0 == 0x00f8
                           0000F8  1602 _PINC_0	=	0x00f8
                           0000F9  1603 G$PINC_1$0$0 == 0x00f9
                           0000F9  1604 _PINC_1	=	0x00f9
                           0000FA  1605 G$PINC_2$0$0 == 0x00fa
                           0000FA  1606 _PINC_2	=	0x00fa
                           0000FB  1607 G$PINC_3$0$0 == 0x00fb
                           0000FB  1608 _PINC_3	=	0x00fb
                           0000FC  1609 G$PINC_4$0$0 == 0x00fc
                           0000FC  1610 _PINC_4	=	0x00fc
                           0000FD  1611 G$PINC_5$0$0 == 0x00fd
                           0000FD  1612 _PINC_5	=	0x00fd
                           0000FE  1613 G$PINC_6$0$0 == 0x00fe
                           0000FE  1614 _PINC_6	=	0x00fe
                           0000FF  1615 G$PINC_7$0$0 == 0x00ff
                           0000FF  1616 _PINC_7	=	0x00ff
                           000080  1617 G$PORTA_0$0$0 == 0x0080
                           000080  1618 _PORTA_0	=	0x0080
                           000081  1619 G$PORTA_1$0$0 == 0x0081
                           000081  1620 _PORTA_1	=	0x0081
                           000082  1621 G$PORTA_2$0$0 == 0x0082
                           000082  1622 _PORTA_2	=	0x0082
                           000083  1623 G$PORTA_3$0$0 == 0x0083
                           000083  1624 _PORTA_3	=	0x0083
                           000084  1625 G$PORTA_4$0$0 == 0x0084
                           000084  1626 _PORTA_4	=	0x0084
                           000085  1627 G$PORTA_5$0$0 == 0x0085
                           000085  1628 _PORTA_5	=	0x0085
                           000086  1629 G$PORTA_6$0$0 == 0x0086
                           000086  1630 _PORTA_6	=	0x0086
                           000087  1631 G$PORTA_7$0$0 == 0x0087
                           000087  1632 _PORTA_7	=	0x0087
                           000088  1633 G$PORTB_0$0$0 == 0x0088
                           000088  1634 _PORTB_0	=	0x0088
                           000089  1635 G$PORTB_1$0$0 == 0x0089
                           000089  1636 _PORTB_1	=	0x0089
                           00008A  1637 G$PORTB_2$0$0 == 0x008a
                           00008A  1638 _PORTB_2	=	0x008a
                           00008B  1639 G$PORTB_3$0$0 == 0x008b
                           00008B  1640 _PORTB_3	=	0x008b
                           00008C  1641 G$PORTB_4$0$0 == 0x008c
                           00008C  1642 _PORTB_4	=	0x008c
                           00008D  1643 G$PORTB_5$0$0 == 0x008d
                           00008D  1644 _PORTB_5	=	0x008d
                           00008E  1645 G$PORTB_6$0$0 == 0x008e
                           00008E  1646 _PORTB_6	=	0x008e
                           00008F  1647 G$PORTB_7$0$0 == 0x008f
                           00008F  1648 _PORTB_7	=	0x008f
                           000090  1649 G$PORTC_0$0$0 == 0x0090
                           000090  1650 _PORTC_0	=	0x0090
                           000091  1651 G$PORTC_1$0$0 == 0x0091
                           000091  1652 _PORTC_1	=	0x0091
                           000092  1653 G$PORTC_2$0$0 == 0x0092
                           000092  1654 _PORTC_2	=	0x0092
                           000093  1655 G$PORTC_3$0$0 == 0x0093
                           000093  1656 _PORTC_3	=	0x0093
                           000094  1657 G$PORTC_4$0$0 == 0x0094
                           000094  1658 _PORTC_4	=	0x0094
                           000095  1659 G$PORTC_5$0$0 == 0x0095
                           000095  1660 _PORTC_5	=	0x0095
                           000096  1661 G$PORTC_6$0$0 == 0x0096
                           000096  1662 _PORTC_6	=	0x0096
                           000097  1663 G$PORTC_7$0$0 == 0x0097
                           000097  1664 _PORTC_7	=	0x0097
                                   1665 ;--------------------------------------------------------
                                   1666 ; overlayable register banks
                                   1667 ;--------------------------------------------------------
                                   1668 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                       1669 	.ds 8
                                   1670 ;--------------------------------------------------------
                                   1671 ; internal ram data
                                   1672 ;--------------------------------------------------------
                                   1673 	.area DSEG    (DATA)
                           000000  1674 G$coldstart$0$0==.
      000022                       1675 _coldstart::
      000022                       1676 	.ds 1
                           000001  1677 G$scr$0$0==.
      000023                       1678 _scr::
      000023                       1679 	.ds 4
                           000005  1680 G$bytes$0$0==.
      000027                       1681 _bytes::
      000027                       1682 	.ds 4
                           000009  1683 G$errors$0$0==.
      00002B                       1684 _errors::
      00002B                       1685 	.ds 4
                           00000D  1686 G$errors2$0$0==.
      00002F                       1687 _errors2::
      00002F                       1688 	.ds 4
                           000011  1689 G$acquire_agc$0$0==.
      000033                       1690 _acquire_agc::
      000033                       1691 	.ds 1
                           000012  1692 Lmain.process_ber$fourfsk$1$234==.
      000034                       1693 _process_ber_fourfsk_1_234:
      000034                       1694 	.ds 1
                           000013  1695 Lmain.process_ber$databyte$6$240==.
      000035                       1696 _process_ber_databyte_6_240:
      000035                       1697 	.ds 1
                           000014  1698 Lmain.process_ber$sloc0$1$0==.
      000036                       1699 _process_ber_sloc0_1_0:
      000036                       1700 	.ds 1
                           000015  1701 Lmain.process_ber$sloc1$1$0==.
      000037                       1702 _process_ber_sloc1_1_0:
      000037                       1703 	.ds 2
                                   1704 ;--------------------------------------------------------
                                   1705 ; overlayable items in internal ram 
                                   1706 ;--------------------------------------------------------
                                   1707 	.area	OSEG    (OVR,DATA)
                                   1708 ;--------------------------------------------------------
                                   1709 ; Stack segment in internal ram 
                                   1710 ;--------------------------------------------------------
                                   1711 	.area	SSEG
      000044                       1712 __start__stack:
      000044                       1713 	.ds	1
                                   1714 
                                   1715 ;--------------------------------------------------------
                                   1716 ; indirectly addressable internal ram data
                                   1717 ;--------------------------------------------------------
                                   1718 	.area ISEG    (DATA)
                                   1719 ;--------------------------------------------------------
                                   1720 ; absolute internal ram data
                                   1721 ;--------------------------------------------------------
                                   1722 	.area IABS    (ABS,DATA)
                                   1723 	.area IABS    (ABS,DATA)
                                   1724 ;--------------------------------------------------------
                                   1725 ; bit data
                                   1726 ;--------------------------------------------------------
                                   1727 	.area BSEG    (BIT)
                           000000  1728 Lmain._sdcc_external_startup$sloc0$1$0==.
      000002                       1729 __sdcc_external_startup_sloc0_1_0:
      000002                       1730 	.ds 1
                                   1731 ;--------------------------------------------------------
                                   1732 ; paged external ram data
                                   1733 ;--------------------------------------------------------
                                   1734 	.area PSEG    (PAG,XDATA)
                                   1735 ;--------------------------------------------------------
                                   1736 ; external ram data
                                   1737 ;--------------------------------------------------------
                                   1738 	.area XSEG    (XDATA)
                           007020  1739 G$ADCCH0VAL0$0$0 == 0x7020
                           007020  1740 _ADCCH0VAL0	=	0x7020
                           007021  1741 G$ADCCH0VAL1$0$0 == 0x7021
                           007021  1742 _ADCCH0VAL1	=	0x7021
                           007020  1743 G$ADCCH0VAL$0$0 == 0x7020
                           007020  1744 _ADCCH0VAL	=	0x7020
                           007022  1745 G$ADCCH1VAL0$0$0 == 0x7022
                           007022  1746 _ADCCH1VAL0	=	0x7022
                           007023  1747 G$ADCCH1VAL1$0$0 == 0x7023
                           007023  1748 _ADCCH1VAL1	=	0x7023
                           007022  1749 G$ADCCH1VAL$0$0 == 0x7022
                           007022  1750 _ADCCH1VAL	=	0x7022
                           007024  1751 G$ADCCH2VAL0$0$0 == 0x7024
                           007024  1752 _ADCCH2VAL0	=	0x7024
                           007025  1753 G$ADCCH2VAL1$0$0 == 0x7025
                           007025  1754 _ADCCH2VAL1	=	0x7025
                           007024  1755 G$ADCCH2VAL$0$0 == 0x7024
                           007024  1756 _ADCCH2VAL	=	0x7024
                           007026  1757 G$ADCCH3VAL0$0$0 == 0x7026
                           007026  1758 _ADCCH3VAL0	=	0x7026
                           007027  1759 G$ADCCH3VAL1$0$0 == 0x7027
                           007027  1760 _ADCCH3VAL1	=	0x7027
                           007026  1761 G$ADCCH3VAL$0$0 == 0x7026
                           007026  1762 _ADCCH3VAL	=	0x7026
                           007028  1763 G$ADCTUNE0$0$0 == 0x7028
                           007028  1764 _ADCTUNE0	=	0x7028
                           007029  1765 G$ADCTUNE1$0$0 == 0x7029
                           007029  1766 _ADCTUNE1	=	0x7029
                           00702A  1767 G$ADCTUNE2$0$0 == 0x702a
                           00702A  1768 _ADCTUNE2	=	0x702a
                           007010  1769 G$DMA0ADDR0$0$0 == 0x7010
                           007010  1770 _DMA0ADDR0	=	0x7010
                           007011  1771 G$DMA0ADDR1$0$0 == 0x7011
                           007011  1772 _DMA0ADDR1	=	0x7011
                           007010  1773 G$DMA0ADDR$0$0 == 0x7010
                           007010  1774 _DMA0ADDR	=	0x7010
                           007014  1775 G$DMA0CONFIG$0$0 == 0x7014
                           007014  1776 _DMA0CONFIG	=	0x7014
                           007012  1777 G$DMA1ADDR0$0$0 == 0x7012
                           007012  1778 _DMA1ADDR0	=	0x7012
                           007013  1779 G$DMA1ADDR1$0$0 == 0x7013
                           007013  1780 _DMA1ADDR1	=	0x7013
                           007012  1781 G$DMA1ADDR$0$0 == 0x7012
                           007012  1782 _DMA1ADDR	=	0x7012
                           007015  1783 G$DMA1CONFIG$0$0 == 0x7015
                           007015  1784 _DMA1CONFIG	=	0x7015
                           007070  1785 G$FRCOSCCONFIG$0$0 == 0x7070
                           007070  1786 _FRCOSCCONFIG	=	0x7070
                           007071  1787 G$FRCOSCCTRL$0$0 == 0x7071
                           007071  1788 _FRCOSCCTRL	=	0x7071
                           007076  1789 G$FRCOSCFREQ0$0$0 == 0x7076
                           007076  1790 _FRCOSCFREQ0	=	0x7076
                           007077  1791 G$FRCOSCFREQ1$0$0 == 0x7077
                           007077  1792 _FRCOSCFREQ1	=	0x7077
                           007076  1793 G$FRCOSCFREQ$0$0 == 0x7076
                           007076  1794 _FRCOSCFREQ	=	0x7076
                           007072  1795 G$FRCOSCKFILT0$0$0 == 0x7072
                           007072  1796 _FRCOSCKFILT0	=	0x7072
                           007073  1797 G$FRCOSCKFILT1$0$0 == 0x7073
                           007073  1798 _FRCOSCKFILT1	=	0x7073
                           007072  1799 G$FRCOSCKFILT$0$0 == 0x7072
                           007072  1800 _FRCOSCKFILT	=	0x7072
                           007078  1801 G$FRCOSCPER0$0$0 == 0x7078
                           007078  1802 _FRCOSCPER0	=	0x7078
                           007079  1803 G$FRCOSCPER1$0$0 == 0x7079
                           007079  1804 _FRCOSCPER1	=	0x7079
                           007078  1805 G$FRCOSCPER$0$0 == 0x7078
                           007078  1806 _FRCOSCPER	=	0x7078
                           007074  1807 G$FRCOSCREF0$0$0 == 0x7074
                           007074  1808 _FRCOSCREF0	=	0x7074
                           007075  1809 G$FRCOSCREF1$0$0 == 0x7075
                           007075  1810 _FRCOSCREF1	=	0x7075
                           007074  1811 G$FRCOSCREF$0$0 == 0x7074
                           007074  1812 _FRCOSCREF	=	0x7074
                           007007  1813 G$ANALOGA$0$0 == 0x7007
                           007007  1814 _ANALOGA	=	0x7007
                           00700C  1815 G$GPIOENABLE$0$0 == 0x700c
                           00700C  1816 _GPIOENABLE	=	0x700c
                           007003  1817 G$EXTIRQ$0$0 == 0x7003
                           007003  1818 _EXTIRQ	=	0x7003
                           007000  1819 G$INTCHGA$0$0 == 0x7000
                           007000  1820 _INTCHGA	=	0x7000
                           007001  1821 G$INTCHGB$0$0 == 0x7001
                           007001  1822 _INTCHGB	=	0x7001
                           007002  1823 G$INTCHGC$0$0 == 0x7002
                           007002  1824 _INTCHGC	=	0x7002
                           007008  1825 G$PALTA$0$0 == 0x7008
                           007008  1826 _PALTA	=	0x7008
                           007009  1827 G$PALTB$0$0 == 0x7009
                           007009  1828 _PALTB	=	0x7009
                           00700A  1829 G$PALTC$0$0 == 0x700a
                           00700A  1830 _PALTC	=	0x700a
                           007046  1831 G$PALTRADIO$0$0 == 0x7046
                           007046  1832 _PALTRADIO	=	0x7046
                           007004  1833 G$PINCHGA$0$0 == 0x7004
                           007004  1834 _PINCHGA	=	0x7004
                           007005  1835 G$PINCHGB$0$0 == 0x7005
                           007005  1836 _PINCHGB	=	0x7005
                           007006  1837 G$PINCHGC$0$0 == 0x7006
                           007006  1838 _PINCHGC	=	0x7006
                           00700B  1839 G$PINSEL$0$0 == 0x700b
                           00700B  1840 _PINSEL	=	0x700b
                           007060  1841 G$LPOSCCONFIG$0$0 == 0x7060
                           007060  1842 _LPOSCCONFIG	=	0x7060
                           007066  1843 G$LPOSCFREQ0$0$0 == 0x7066
                           007066  1844 _LPOSCFREQ0	=	0x7066
                           007067  1845 G$LPOSCFREQ1$0$0 == 0x7067
                           007067  1846 _LPOSCFREQ1	=	0x7067
                           007066  1847 G$LPOSCFREQ$0$0 == 0x7066
                           007066  1848 _LPOSCFREQ	=	0x7066
                           007062  1849 G$LPOSCKFILT0$0$0 == 0x7062
                           007062  1850 _LPOSCKFILT0	=	0x7062
                           007063  1851 G$LPOSCKFILT1$0$0 == 0x7063
                           007063  1852 _LPOSCKFILT1	=	0x7063
                           007062  1853 G$LPOSCKFILT$0$0 == 0x7062
                           007062  1854 _LPOSCKFILT	=	0x7062
                           007068  1855 G$LPOSCPER0$0$0 == 0x7068
                           007068  1856 _LPOSCPER0	=	0x7068
                           007069  1857 G$LPOSCPER1$0$0 == 0x7069
                           007069  1858 _LPOSCPER1	=	0x7069
                           007068  1859 G$LPOSCPER$0$0 == 0x7068
                           007068  1860 _LPOSCPER	=	0x7068
                           007064  1861 G$LPOSCREF0$0$0 == 0x7064
                           007064  1862 _LPOSCREF0	=	0x7064
                           007065  1863 G$LPOSCREF1$0$0 == 0x7065
                           007065  1864 _LPOSCREF1	=	0x7065
                           007064  1865 G$LPOSCREF$0$0 == 0x7064
                           007064  1866 _LPOSCREF	=	0x7064
                           007054  1867 G$LPXOSCGM$0$0 == 0x7054
                           007054  1868 _LPXOSCGM	=	0x7054
                           007F01  1869 G$MISCCTRL$0$0 == 0x7f01
                           007F01  1870 _MISCCTRL	=	0x7f01
                           007053  1871 G$OSCCALIB$0$0 == 0x7053
                           007053  1872 _OSCCALIB	=	0x7053
                           007050  1873 G$OSCFORCERUN$0$0 == 0x7050
                           007050  1874 _OSCFORCERUN	=	0x7050
                           007052  1875 G$OSCREADY$0$0 == 0x7052
                           007052  1876 _OSCREADY	=	0x7052
                           007051  1877 G$OSCRUN$0$0 == 0x7051
                           007051  1878 _OSCRUN	=	0x7051
                           007040  1879 G$RADIOFDATAADDR0$0$0 == 0x7040
                           007040  1880 _RADIOFDATAADDR0	=	0x7040
                           007041  1881 G$RADIOFDATAADDR1$0$0 == 0x7041
                           007041  1882 _RADIOFDATAADDR1	=	0x7041
                           007040  1883 G$RADIOFDATAADDR$0$0 == 0x7040
                           007040  1884 _RADIOFDATAADDR	=	0x7040
                           007042  1885 G$RADIOFSTATADDR0$0$0 == 0x7042
                           007042  1886 _RADIOFSTATADDR0	=	0x7042
                           007043  1887 G$RADIOFSTATADDR1$0$0 == 0x7043
                           007043  1888 _RADIOFSTATADDR1	=	0x7043
                           007042  1889 G$RADIOFSTATADDR$0$0 == 0x7042
                           007042  1890 _RADIOFSTATADDR	=	0x7042
                           007044  1891 G$RADIOMUX$0$0 == 0x7044
                           007044  1892 _RADIOMUX	=	0x7044
                           007084  1893 G$SCRATCH0$0$0 == 0x7084
                           007084  1894 _SCRATCH0	=	0x7084
                           007085  1895 G$SCRATCH1$0$0 == 0x7085
                           007085  1896 _SCRATCH1	=	0x7085
                           007086  1897 G$SCRATCH2$0$0 == 0x7086
                           007086  1898 _SCRATCH2	=	0x7086
                           007087  1899 G$SCRATCH3$0$0 == 0x7087
                           007087  1900 _SCRATCH3	=	0x7087
                           007F00  1901 G$SILICONREV$0$0 == 0x7f00
                           007F00  1902 _SILICONREV	=	0x7f00
                           007F19  1903 G$XTALAMPL$0$0 == 0x7f19
                           007F19  1904 _XTALAMPL	=	0x7f19
                           007F18  1905 G$XTALOSC$0$0 == 0x7f18
                           007F18  1906 _XTALOSC	=	0x7f18
                           007F1A  1907 G$XTALREADY$0$0 == 0x7f1a
                           007F1A  1908 _XTALREADY	=	0x7f1a
                           003F82  1909 G$XDPTR0$0$0 == 0x3f82
                           003F82  1910 _XDPTR0	=	0x3f82
                           003F84  1911 G$XDPTR1$0$0 == 0x3f84
                           003F84  1912 _XDPTR1	=	0x3f84
                           003FA8  1913 G$XIE$0$0 == 0x3fa8
                           003FA8  1914 _XIE	=	0x3fa8
                           003FB8  1915 G$XIP$0$0 == 0x3fb8
                           003FB8  1916 _XIP	=	0x3fb8
                           003F87  1917 G$XPCON$0$0 == 0x3f87
                           003F87  1918 _XPCON	=	0x3f87
                           003FCA  1919 G$XADCCH0CONFIG$0$0 == 0x3fca
                           003FCA  1920 _XADCCH0CONFIG	=	0x3fca
                           003FCB  1921 G$XADCCH1CONFIG$0$0 == 0x3fcb
                           003FCB  1922 _XADCCH1CONFIG	=	0x3fcb
                           003FD2  1923 G$XADCCH2CONFIG$0$0 == 0x3fd2
                           003FD2  1924 _XADCCH2CONFIG	=	0x3fd2
                           003FD3  1925 G$XADCCH3CONFIG$0$0 == 0x3fd3
                           003FD3  1926 _XADCCH3CONFIG	=	0x3fd3
                           003FD1  1927 G$XADCCLKSRC$0$0 == 0x3fd1
                           003FD1  1928 _XADCCLKSRC	=	0x3fd1
                           003FC9  1929 G$XADCCONV$0$0 == 0x3fc9
                           003FC9  1930 _XADCCONV	=	0x3fc9
                           003FE1  1931 G$XANALOGCOMP$0$0 == 0x3fe1
                           003FE1  1932 _XANALOGCOMP	=	0x3fe1
                           003FC6  1933 G$XCLKCON$0$0 == 0x3fc6
                           003FC6  1934 _XCLKCON	=	0x3fc6
                           003FC7  1935 G$XCLKSTAT$0$0 == 0x3fc7
                           003FC7  1936 _XCLKSTAT	=	0x3fc7
                           003F97  1937 G$XCODECONFIG$0$0 == 0x3f97
                           003F97  1938 _XCODECONFIG	=	0x3f97
                           003FE3  1939 G$XDBGLNKBUF$0$0 == 0x3fe3
                           003FE3  1940 _XDBGLNKBUF	=	0x3fe3
                           003FE2  1941 G$XDBGLNKSTAT$0$0 == 0x3fe2
                           003FE2  1942 _XDBGLNKSTAT	=	0x3fe2
                           003F89  1943 G$XDIRA$0$0 == 0x3f89
                           003F89  1944 _XDIRA	=	0x3f89
                           003F8A  1945 G$XDIRB$0$0 == 0x3f8a
                           003F8A  1946 _XDIRB	=	0x3f8a
                           003F8B  1947 G$XDIRC$0$0 == 0x3f8b
                           003F8B  1948 _XDIRC	=	0x3f8b
                           003F8E  1949 G$XDIRR$0$0 == 0x3f8e
                           003F8E  1950 _XDIRR	=	0x3f8e
                           003FC8  1951 G$XPINA$0$0 == 0x3fc8
                           003FC8  1952 _XPINA	=	0x3fc8
                           003FE8  1953 G$XPINB$0$0 == 0x3fe8
                           003FE8  1954 _XPINB	=	0x3fe8
                           003FF8  1955 G$XPINC$0$0 == 0x3ff8
                           003FF8  1956 _XPINC	=	0x3ff8
                           003F8D  1957 G$XPINR$0$0 == 0x3f8d
                           003F8D  1958 _XPINR	=	0x3f8d
                           003F80  1959 G$XPORTA$0$0 == 0x3f80
                           003F80  1960 _XPORTA	=	0x3f80
                           003F88  1961 G$XPORTB$0$0 == 0x3f88
                           003F88  1962 _XPORTB	=	0x3f88
                           003F90  1963 G$XPORTC$0$0 == 0x3f90
                           003F90  1964 _XPORTC	=	0x3f90
                           003F8C  1965 G$XPORTR$0$0 == 0x3f8c
                           003F8C  1966 _XPORTR	=	0x3f8c
                           003FCE  1967 G$XIC0CAPT0$0$0 == 0x3fce
                           003FCE  1968 _XIC0CAPT0	=	0x3fce
                           003FCF  1969 G$XIC0CAPT1$0$0 == 0x3fcf
                           003FCF  1970 _XIC0CAPT1	=	0x3fcf
                           003FCE  1971 G$XIC0CAPT$0$0 == 0x3fce
                           003FCE  1972 _XIC0CAPT	=	0x3fce
                           003FCC  1973 G$XIC0MODE$0$0 == 0x3fcc
                           003FCC  1974 _XIC0MODE	=	0x3fcc
                           003FCD  1975 G$XIC0STATUS$0$0 == 0x3fcd
                           003FCD  1976 _XIC0STATUS	=	0x3fcd
                           003FD6  1977 G$XIC1CAPT0$0$0 == 0x3fd6
                           003FD6  1978 _XIC1CAPT0	=	0x3fd6
                           003FD7  1979 G$XIC1CAPT1$0$0 == 0x3fd7
                           003FD7  1980 _XIC1CAPT1	=	0x3fd7
                           003FD6  1981 G$XIC1CAPT$0$0 == 0x3fd6
                           003FD6  1982 _XIC1CAPT	=	0x3fd6
                           003FD4  1983 G$XIC1MODE$0$0 == 0x3fd4
                           003FD4  1984 _XIC1MODE	=	0x3fd4
                           003FD5  1985 G$XIC1STATUS$0$0 == 0x3fd5
                           003FD5  1986 _XIC1STATUS	=	0x3fd5
                           003F92  1987 G$XNVADDR0$0$0 == 0x3f92
                           003F92  1988 _XNVADDR0	=	0x3f92
                           003F93  1989 G$XNVADDR1$0$0 == 0x3f93
                           003F93  1990 _XNVADDR1	=	0x3f93
                           003F92  1991 G$XNVADDR$0$0 == 0x3f92
                           003F92  1992 _XNVADDR	=	0x3f92
                           003F94  1993 G$XNVDATA0$0$0 == 0x3f94
                           003F94  1994 _XNVDATA0	=	0x3f94
                           003F95  1995 G$XNVDATA1$0$0 == 0x3f95
                           003F95  1996 _XNVDATA1	=	0x3f95
                           003F94  1997 G$XNVDATA$0$0 == 0x3f94
                           003F94  1998 _XNVDATA	=	0x3f94
                           003F96  1999 G$XNVKEY$0$0 == 0x3f96
                           003F96  2000 _XNVKEY	=	0x3f96
                           003F91  2001 G$XNVSTATUS$0$0 == 0x3f91
                           003F91  2002 _XNVSTATUS	=	0x3f91
                           003FBC  2003 G$XOC0COMP0$0$0 == 0x3fbc
                           003FBC  2004 _XOC0COMP0	=	0x3fbc
                           003FBD  2005 G$XOC0COMP1$0$0 == 0x3fbd
                           003FBD  2006 _XOC0COMP1	=	0x3fbd
                           003FBC  2007 G$XOC0COMP$0$0 == 0x3fbc
                           003FBC  2008 _XOC0COMP	=	0x3fbc
                           003FB9  2009 G$XOC0MODE$0$0 == 0x3fb9
                           003FB9  2010 _XOC0MODE	=	0x3fb9
                           003FBA  2011 G$XOC0PIN$0$0 == 0x3fba
                           003FBA  2012 _XOC0PIN	=	0x3fba
                           003FBB  2013 G$XOC0STATUS$0$0 == 0x3fbb
                           003FBB  2014 _XOC0STATUS	=	0x3fbb
                           003FC4  2015 G$XOC1COMP0$0$0 == 0x3fc4
                           003FC4  2016 _XOC1COMP0	=	0x3fc4
                           003FC5  2017 G$XOC1COMP1$0$0 == 0x3fc5
                           003FC5  2018 _XOC1COMP1	=	0x3fc5
                           003FC4  2019 G$XOC1COMP$0$0 == 0x3fc4
                           003FC4  2020 _XOC1COMP	=	0x3fc4
                           003FC1  2021 G$XOC1MODE$0$0 == 0x3fc1
                           003FC1  2022 _XOC1MODE	=	0x3fc1
                           003FC2  2023 G$XOC1PIN$0$0 == 0x3fc2
                           003FC2  2024 _XOC1PIN	=	0x3fc2
                           003FC3  2025 G$XOC1STATUS$0$0 == 0x3fc3
                           003FC3  2026 _XOC1STATUS	=	0x3fc3
                           003FB1  2027 G$XRADIOACC$0$0 == 0x3fb1
                           003FB1  2028 _XRADIOACC	=	0x3fb1
                           003FB3  2029 G$XRADIOADDR0$0$0 == 0x3fb3
                           003FB3  2030 _XRADIOADDR0	=	0x3fb3
                           003FB2  2031 G$XRADIOADDR1$0$0 == 0x3fb2
                           003FB2  2032 _XRADIOADDR1	=	0x3fb2
                           003FB7  2033 G$XRADIODATA0$0$0 == 0x3fb7
                           003FB7  2034 _XRADIODATA0	=	0x3fb7
                           003FB6  2035 G$XRADIODATA1$0$0 == 0x3fb6
                           003FB6  2036 _XRADIODATA1	=	0x3fb6
                           003FB5  2037 G$XRADIODATA2$0$0 == 0x3fb5
                           003FB5  2038 _XRADIODATA2	=	0x3fb5
                           003FB4  2039 G$XRADIODATA3$0$0 == 0x3fb4
                           003FB4  2040 _XRADIODATA3	=	0x3fb4
                           003FBE  2041 G$XRADIOSTAT0$0$0 == 0x3fbe
                           003FBE  2042 _XRADIOSTAT0	=	0x3fbe
                           003FBF  2043 G$XRADIOSTAT1$0$0 == 0x3fbf
                           003FBF  2044 _XRADIOSTAT1	=	0x3fbf
                           003FBE  2045 G$XRADIOSTAT$0$0 == 0x3fbe
                           003FBE  2046 _XRADIOSTAT	=	0x3fbe
                           003FDF  2047 G$XSPCLKSRC$0$0 == 0x3fdf
                           003FDF  2048 _XSPCLKSRC	=	0x3fdf
                           003FDC  2049 G$XSPMODE$0$0 == 0x3fdc
                           003FDC  2050 _XSPMODE	=	0x3fdc
                           003FDE  2051 G$XSPSHREG$0$0 == 0x3fde
                           003FDE  2052 _XSPSHREG	=	0x3fde
                           003FDD  2053 G$XSPSTATUS$0$0 == 0x3fdd
                           003FDD  2054 _XSPSTATUS	=	0x3fdd
                           003F9A  2055 G$XT0CLKSRC$0$0 == 0x3f9a
                           003F9A  2056 _XT0CLKSRC	=	0x3f9a
                           003F9C  2057 G$XT0CNT0$0$0 == 0x3f9c
                           003F9C  2058 _XT0CNT0	=	0x3f9c
                           003F9D  2059 G$XT0CNT1$0$0 == 0x3f9d
                           003F9D  2060 _XT0CNT1	=	0x3f9d
                           003F9C  2061 G$XT0CNT$0$0 == 0x3f9c
                           003F9C  2062 _XT0CNT	=	0x3f9c
                           003F99  2063 G$XT0MODE$0$0 == 0x3f99
                           003F99  2064 _XT0MODE	=	0x3f99
                           003F9E  2065 G$XT0PERIOD0$0$0 == 0x3f9e
                           003F9E  2066 _XT0PERIOD0	=	0x3f9e
                           003F9F  2067 G$XT0PERIOD1$0$0 == 0x3f9f
                           003F9F  2068 _XT0PERIOD1	=	0x3f9f
                           003F9E  2069 G$XT0PERIOD$0$0 == 0x3f9e
                           003F9E  2070 _XT0PERIOD	=	0x3f9e
                           003F9B  2071 G$XT0STATUS$0$0 == 0x3f9b
                           003F9B  2072 _XT0STATUS	=	0x3f9b
                           003FA2  2073 G$XT1CLKSRC$0$0 == 0x3fa2
                           003FA2  2074 _XT1CLKSRC	=	0x3fa2
                           003FA4  2075 G$XT1CNT0$0$0 == 0x3fa4
                           003FA4  2076 _XT1CNT0	=	0x3fa4
                           003FA5  2077 G$XT1CNT1$0$0 == 0x3fa5
                           003FA5  2078 _XT1CNT1	=	0x3fa5
                           003FA4  2079 G$XT1CNT$0$0 == 0x3fa4
                           003FA4  2080 _XT1CNT	=	0x3fa4
                           003FA1  2081 G$XT1MODE$0$0 == 0x3fa1
                           003FA1  2082 _XT1MODE	=	0x3fa1
                           003FA6  2083 G$XT1PERIOD0$0$0 == 0x3fa6
                           003FA6  2084 _XT1PERIOD0	=	0x3fa6
                           003FA7  2085 G$XT1PERIOD1$0$0 == 0x3fa7
                           003FA7  2086 _XT1PERIOD1	=	0x3fa7
                           003FA6  2087 G$XT1PERIOD$0$0 == 0x3fa6
                           003FA6  2088 _XT1PERIOD	=	0x3fa6
                           003FA3  2089 G$XT1STATUS$0$0 == 0x3fa3
                           003FA3  2090 _XT1STATUS	=	0x3fa3
                           003FAA  2091 G$XT2CLKSRC$0$0 == 0x3faa
                           003FAA  2092 _XT2CLKSRC	=	0x3faa
                           003FAC  2093 G$XT2CNT0$0$0 == 0x3fac
                           003FAC  2094 _XT2CNT0	=	0x3fac
                           003FAD  2095 G$XT2CNT1$0$0 == 0x3fad
                           003FAD  2096 _XT2CNT1	=	0x3fad
                           003FAC  2097 G$XT2CNT$0$0 == 0x3fac
                           003FAC  2098 _XT2CNT	=	0x3fac
                           003FA9  2099 G$XT2MODE$0$0 == 0x3fa9
                           003FA9  2100 _XT2MODE	=	0x3fa9
                           003FAE  2101 G$XT2PERIOD0$0$0 == 0x3fae
                           003FAE  2102 _XT2PERIOD0	=	0x3fae
                           003FAF  2103 G$XT2PERIOD1$0$0 == 0x3faf
                           003FAF  2104 _XT2PERIOD1	=	0x3faf
                           003FAE  2105 G$XT2PERIOD$0$0 == 0x3fae
                           003FAE  2106 _XT2PERIOD	=	0x3fae
                           003FAB  2107 G$XT2STATUS$0$0 == 0x3fab
                           003FAB  2108 _XT2STATUS	=	0x3fab
                           003FE4  2109 G$XU0CTRL$0$0 == 0x3fe4
                           003FE4  2110 _XU0CTRL	=	0x3fe4
                           003FE7  2111 G$XU0MODE$0$0 == 0x3fe7
                           003FE7  2112 _XU0MODE	=	0x3fe7
                           003FE6  2113 G$XU0SHREG$0$0 == 0x3fe6
                           003FE6  2114 _XU0SHREG	=	0x3fe6
                           003FE5  2115 G$XU0STATUS$0$0 == 0x3fe5
                           003FE5  2116 _XU0STATUS	=	0x3fe5
                           003FEC  2117 G$XU1CTRL$0$0 == 0x3fec
                           003FEC  2118 _XU1CTRL	=	0x3fec
                           003FEF  2119 G$XU1MODE$0$0 == 0x3fef
                           003FEF  2120 _XU1MODE	=	0x3fef
                           003FEE  2121 G$XU1SHREG$0$0 == 0x3fee
                           003FEE  2122 _XU1SHREG	=	0x3fee
                           003FED  2123 G$XU1STATUS$0$0 == 0x3fed
                           003FED  2124 _XU1STATUS	=	0x3fed
                           003FDA  2125 G$XWDTCFG$0$0 == 0x3fda
                           003FDA  2126 _XWDTCFG	=	0x3fda
                           003FDB  2127 G$XWDTRESET$0$0 == 0x3fdb
                           003FDB  2128 _XWDTRESET	=	0x3fdb
                           003FF1  2129 G$XWTCFGA$0$0 == 0x3ff1
                           003FF1  2130 _XWTCFGA	=	0x3ff1
                           003FF9  2131 G$XWTCFGB$0$0 == 0x3ff9
                           003FF9  2132 _XWTCFGB	=	0x3ff9
                           003FF2  2133 G$XWTCNTA0$0$0 == 0x3ff2
                           003FF2  2134 _XWTCNTA0	=	0x3ff2
                           003FF3  2135 G$XWTCNTA1$0$0 == 0x3ff3
                           003FF3  2136 _XWTCNTA1	=	0x3ff3
                           003FF2  2137 G$XWTCNTA$0$0 == 0x3ff2
                           003FF2  2138 _XWTCNTA	=	0x3ff2
                           003FFA  2139 G$XWTCNTB0$0$0 == 0x3ffa
                           003FFA  2140 _XWTCNTB0	=	0x3ffa
                           003FFB  2141 G$XWTCNTB1$0$0 == 0x3ffb
                           003FFB  2142 _XWTCNTB1	=	0x3ffb
                           003FFA  2143 G$XWTCNTB$0$0 == 0x3ffa
                           003FFA  2144 _XWTCNTB	=	0x3ffa
                           003FEB  2145 G$XWTCNTR1$0$0 == 0x3feb
                           003FEB  2146 _XWTCNTR1	=	0x3feb
                           003FF4  2147 G$XWTEVTA0$0$0 == 0x3ff4
                           003FF4  2148 _XWTEVTA0	=	0x3ff4
                           003FF5  2149 G$XWTEVTA1$0$0 == 0x3ff5
                           003FF5  2150 _XWTEVTA1	=	0x3ff5
                           003FF4  2151 G$XWTEVTA$0$0 == 0x3ff4
                           003FF4  2152 _XWTEVTA	=	0x3ff4
                           003FF6  2153 G$XWTEVTB0$0$0 == 0x3ff6
                           003FF6  2154 _XWTEVTB0	=	0x3ff6
                           003FF7  2155 G$XWTEVTB1$0$0 == 0x3ff7
                           003FF7  2156 _XWTEVTB1	=	0x3ff7
                           003FF6  2157 G$XWTEVTB$0$0 == 0x3ff6
                           003FF6  2158 _XWTEVTB	=	0x3ff6
                           003FFC  2159 G$XWTEVTC0$0$0 == 0x3ffc
                           003FFC  2160 _XWTEVTC0	=	0x3ffc
                           003FFD  2161 G$XWTEVTC1$0$0 == 0x3ffd
                           003FFD  2162 _XWTEVTC1	=	0x3ffd
                           003FFC  2163 G$XWTEVTC$0$0 == 0x3ffc
                           003FFC  2164 _XWTEVTC	=	0x3ffc
                           003FFE  2165 G$XWTEVTD0$0$0 == 0x3ffe
                           003FFE  2166 _XWTEVTD0	=	0x3ffe
                           003FFF  2167 G$XWTEVTD1$0$0 == 0x3fff
                           003FFF  2168 _XWTEVTD1	=	0x3fff
                           003FFE  2169 G$XWTEVTD$0$0 == 0x3ffe
                           003FFE  2170 _XWTEVTD	=	0x3ffe
                           003FE9  2171 G$XWTIRQEN$0$0 == 0x3fe9
                           003FE9  2172 _XWTIRQEN	=	0x3fe9
                           003FEA  2173 G$XWTSTAT$0$0 == 0x3fea
                           003FEA  2174 _XWTSTAT	=	0x3fea
                           004114  2175 G$AX5043_AFSKCTRL$0$0 == 0x4114
                           004114  2176 _AX5043_AFSKCTRL	=	0x4114
                           004113  2177 G$AX5043_AFSKMARK0$0$0 == 0x4113
                           004113  2178 _AX5043_AFSKMARK0	=	0x4113
                           004112  2179 G$AX5043_AFSKMARK1$0$0 == 0x4112
                           004112  2180 _AX5043_AFSKMARK1	=	0x4112
                           004111  2181 G$AX5043_AFSKSPACE0$0$0 == 0x4111
                           004111  2182 _AX5043_AFSKSPACE0	=	0x4111
                           004110  2183 G$AX5043_AFSKSPACE1$0$0 == 0x4110
                           004110  2184 _AX5043_AFSKSPACE1	=	0x4110
                           004043  2185 G$AX5043_AGCCOUNTER$0$0 == 0x4043
                           004043  2186 _AX5043_AGCCOUNTER	=	0x4043
                           004115  2187 G$AX5043_AMPLFILTER$0$0 == 0x4115
                           004115  2188 _AX5043_AMPLFILTER	=	0x4115
                           004189  2189 G$AX5043_BBOFFSCAP$0$0 == 0x4189
                           004189  2190 _AX5043_BBOFFSCAP	=	0x4189
                           004188  2191 G$AX5043_BBTUNE$0$0 == 0x4188
                           004188  2192 _AX5043_BBTUNE	=	0x4188
                           004041  2193 G$AX5043_BGNDRSSI$0$0 == 0x4041
                           004041  2194 _AX5043_BGNDRSSI	=	0x4041
                           00422E  2195 G$AX5043_BGNDRSSIGAIN$0$0 == 0x422e
                           00422E  2196 _AX5043_BGNDRSSIGAIN	=	0x422e
                           00422F  2197 G$AX5043_BGNDRSSITHR$0$0 == 0x422f
                           00422F  2198 _AX5043_BGNDRSSITHR	=	0x422f
                           004017  2199 G$AX5043_CRCINIT0$0$0 == 0x4017
                           004017  2200 _AX5043_CRCINIT0	=	0x4017
                           004016  2201 G$AX5043_CRCINIT1$0$0 == 0x4016
                           004016  2202 _AX5043_CRCINIT1	=	0x4016
                           004015  2203 G$AX5043_CRCINIT2$0$0 == 0x4015
                           004015  2204 _AX5043_CRCINIT2	=	0x4015
                           004014  2205 G$AX5043_CRCINIT3$0$0 == 0x4014
                           004014  2206 _AX5043_CRCINIT3	=	0x4014
                           004332  2207 G$AX5043_DACCONFIG$0$0 == 0x4332
                           004332  2208 _AX5043_DACCONFIG	=	0x4332
                           004331  2209 G$AX5043_DACVALUE0$0$0 == 0x4331
                           004331  2210 _AX5043_DACVALUE0	=	0x4331
                           004330  2211 G$AX5043_DACVALUE1$0$0 == 0x4330
                           004330  2212 _AX5043_DACVALUE1	=	0x4330
                           004102  2213 G$AX5043_DECIMATION$0$0 == 0x4102
                           004102  2214 _AX5043_DECIMATION	=	0x4102
                           004042  2215 G$AX5043_DIVERSITY$0$0 == 0x4042
                           004042  2216 _AX5043_DIVERSITY	=	0x4042
                           004011  2217 G$AX5043_ENCODING$0$0 == 0x4011
                           004011  2218 _AX5043_ENCODING	=	0x4011
                           004018  2219 G$AX5043_FEC$0$0 == 0x4018
                           004018  2220 _AX5043_FEC	=	0x4018
                           00401A  2221 G$AX5043_FECSTATUS$0$0 == 0x401a
                           00401A  2222 _AX5043_FECSTATUS	=	0x401a
                           004019  2223 G$AX5043_FECSYNC$0$0 == 0x4019
                           004019  2224 _AX5043_FECSYNC	=	0x4019
                           00402B  2225 G$AX5043_FIFOCOUNT0$0$0 == 0x402b
                           00402B  2226 _AX5043_FIFOCOUNT0	=	0x402b
                           00402A  2227 G$AX5043_FIFOCOUNT1$0$0 == 0x402a
                           00402A  2228 _AX5043_FIFOCOUNT1	=	0x402a
                           004029  2229 G$AX5043_FIFODATA$0$0 == 0x4029
                           004029  2230 _AX5043_FIFODATA	=	0x4029
                           00402D  2231 G$AX5043_FIFOFREE0$0$0 == 0x402d
                           00402D  2232 _AX5043_FIFOFREE0	=	0x402d
                           00402C  2233 G$AX5043_FIFOFREE1$0$0 == 0x402c
                           00402C  2234 _AX5043_FIFOFREE1	=	0x402c
                           004028  2235 G$AX5043_FIFOSTAT$0$0 == 0x4028
                           004028  2236 _AX5043_FIFOSTAT	=	0x4028
                           00402F  2237 G$AX5043_FIFOTHRESH0$0$0 == 0x402f
                           00402F  2238 _AX5043_FIFOTHRESH0	=	0x402f
                           00402E  2239 G$AX5043_FIFOTHRESH1$0$0 == 0x402e
                           00402E  2240 _AX5043_FIFOTHRESH1	=	0x402e
                           004012  2241 G$AX5043_FRAMING$0$0 == 0x4012
                           004012  2242 _AX5043_FRAMING	=	0x4012
                           004037  2243 G$AX5043_FREQA0$0$0 == 0x4037
                           004037  2244 _AX5043_FREQA0	=	0x4037
                           004036  2245 G$AX5043_FREQA1$0$0 == 0x4036
                           004036  2246 _AX5043_FREQA1	=	0x4036
                           004035  2247 G$AX5043_FREQA2$0$0 == 0x4035
                           004035  2248 _AX5043_FREQA2	=	0x4035
                           004034  2249 G$AX5043_FREQA3$0$0 == 0x4034
                           004034  2250 _AX5043_FREQA3	=	0x4034
                           00403F  2251 G$AX5043_FREQB0$0$0 == 0x403f
                           00403F  2252 _AX5043_FREQB0	=	0x403f
                           00403E  2253 G$AX5043_FREQB1$0$0 == 0x403e
                           00403E  2254 _AX5043_FREQB1	=	0x403e
                           00403D  2255 G$AX5043_FREQB2$0$0 == 0x403d
                           00403D  2256 _AX5043_FREQB2	=	0x403d
                           00403C  2257 G$AX5043_FREQB3$0$0 == 0x403c
                           00403C  2258 _AX5043_FREQB3	=	0x403c
                           004163  2259 G$AX5043_FSKDEV0$0$0 == 0x4163
                           004163  2260 _AX5043_FSKDEV0	=	0x4163
                           004162  2261 G$AX5043_FSKDEV1$0$0 == 0x4162
                           004162  2262 _AX5043_FSKDEV1	=	0x4162
                           004161  2263 G$AX5043_FSKDEV2$0$0 == 0x4161
                           004161  2264 _AX5043_FSKDEV2	=	0x4161
                           00410D  2265 G$AX5043_FSKDMAX0$0$0 == 0x410d
                           00410D  2266 _AX5043_FSKDMAX0	=	0x410d
                           00410C  2267 G$AX5043_FSKDMAX1$0$0 == 0x410c
                           00410C  2268 _AX5043_FSKDMAX1	=	0x410c
                           00410F  2269 G$AX5043_FSKDMIN0$0$0 == 0x410f
                           00410F  2270 _AX5043_FSKDMIN0	=	0x410f
                           00410E  2271 G$AX5043_FSKDMIN1$0$0 == 0x410e
                           00410E  2272 _AX5043_FSKDMIN1	=	0x410e
                           004309  2273 G$AX5043_GPADC13VALUE0$0$0 == 0x4309
                           004309  2274 _AX5043_GPADC13VALUE0	=	0x4309
                           004308  2275 G$AX5043_GPADC13VALUE1$0$0 == 0x4308
                           004308  2276 _AX5043_GPADC13VALUE1	=	0x4308
                           004300  2277 G$AX5043_GPADCCTRL$0$0 == 0x4300
                           004300  2278 _AX5043_GPADCCTRL	=	0x4300
                           004301  2279 G$AX5043_GPADCPERIOD$0$0 == 0x4301
                           004301  2280 _AX5043_GPADCPERIOD	=	0x4301
                           004101  2281 G$AX5043_IFFREQ0$0$0 == 0x4101
                           004101  2282 _AX5043_IFFREQ0	=	0x4101
                           004100  2283 G$AX5043_IFFREQ1$0$0 == 0x4100
                           004100  2284 _AX5043_IFFREQ1	=	0x4100
                           00400B  2285 G$AX5043_IRQINVERSION0$0$0 == 0x400b
                           00400B  2286 _AX5043_IRQINVERSION0	=	0x400b
                           00400A  2287 G$AX5043_IRQINVERSION1$0$0 == 0x400a
                           00400A  2288 _AX5043_IRQINVERSION1	=	0x400a
                           004007  2289 G$AX5043_IRQMASK0$0$0 == 0x4007
                           004007  2290 _AX5043_IRQMASK0	=	0x4007
                           004006  2291 G$AX5043_IRQMASK1$0$0 == 0x4006
                           004006  2292 _AX5043_IRQMASK1	=	0x4006
                           00400D  2293 G$AX5043_IRQREQUEST0$0$0 == 0x400d
                           00400D  2294 _AX5043_IRQREQUEST0	=	0x400d
                           00400C  2295 G$AX5043_IRQREQUEST1$0$0 == 0x400c
                           00400C  2296 _AX5043_IRQREQUEST1	=	0x400c
                           004310  2297 G$AX5043_LPOSCCONFIG$0$0 == 0x4310
                           004310  2298 _AX5043_LPOSCCONFIG	=	0x4310
                           004317  2299 G$AX5043_LPOSCFREQ0$0$0 == 0x4317
                           004317  2300 _AX5043_LPOSCFREQ0	=	0x4317
                           004316  2301 G$AX5043_LPOSCFREQ1$0$0 == 0x4316
                           004316  2302 _AX5043_LPOSCFREQ1	=	0x4316
                           004313  2303 G$AX5043_LPOSCKFILT0$0$0 == 0x4313
                           004313  2304 _AX5043_LPOSCKFILT0	=	0x4313
                           004312  2305 G$AX5043_LPOSCKFILT1$0$0 == 0x4312
                           004312  2306 _AX5043_LPOSCKFILT1	=	0x4312
                           004319  2307 G$AX5043_LPOSCPER0$0$0 == 0x4319
                           004319  2308 _AX5043_LPOSCPER0	=	0x4319
                           004318  2309 G$AX5043_LPOSCPER1$0$0 == 0x4318
                           004318  2310 _AX5043_LPOSCPER1	=	0x4318
                           004315  2311 G$AX5043_LPOSCREF0$0$0 == 0x4315
                           004315  2312 _AX5043_LPOSCREF0	=	0x4315
                           004314  2313 G$AX5043_LPOSCREF1$0$0 == 0x4314
                           004314  2314 _AX5043_LPOSCREF1	=	0x4314
                           004311  2315 G$AX5043_LPOSCSTATUS$0$0 == 0x4311
                           004311  2316 _AX5043_LPOSCSTATUS	=	0x4311
                           004214  2317 G$AX5043_MATCH0LEN$0$0 == 0x4214
                           004214  2318 _AX5043_MATCH0LEN	=	0x4214
                           004216  2319 G$AX5043_MATCH0MAX$0$0 == 0x4216
                           004216  2320 _AX5043_MATCH0MAX	=	0x4216
                           004215  2321 G$AX5043_MATCH0MIN$0$0 == 0x4215
                           004215  2322 _AX5043_MATCH0MIN	=	0x4215
                           004213  2323 G$AX5043_MATCH0PAT0$0$0 == 0x4213
                           004213  2324 _AX5043_MATCH0PAT0	=	0x4213
                           004212  2325 G$AX5043_MATCH0PAT1$0$0 == 0x4212
                           004212  2326 _AX5043_MATCH0PAT1	=	0x4212
                           004211  2327 G$AX5043_MATCH0PAT2$0$0 == 0x4211
                           004211  2328 _AX5043_MATCH0PAT2	=	0x4211
                           004210  2329 G$AX5043_MATCH0PAT3$0$0 == 0x4210
                           004210  2330 _AX5043_MATCH0PAT3	=	0x4210
                           00421C  2331 G$AX5043_MATCH1LEN$0$0 == 0x421c
                           00421C  2332 _AX5043_MATCH1LEN	=	0x421c
                           00421E  2333 G$AX5043_MATCH1MAX$0$0 == 0x421e
                           00421E  2334 _AX5043_MATCH1MAX	=	0x421e
                           00421D  2335 G$AX5043_MATCH1MIN$0$0 == 0x421d
                           00421D  2336 _AX5043_MATCH1MIN	=	0x421d
                           004219  2337 G$AX5043_MATCH1PAT0$0$0 == 0x4219
                           004219  2338 _AX5043_MATCH1PAT0	=	0x4219
                           004218  2339 G$AX5043_MATCH1PAT1$0$0 == 0x4218
                           004218  2340 _AX5043_MATCH1PAT1	=	0x4218
                           004108  2341 G$AX5043_MAXDROFFSET0$0$0 == 0x4108
                           004108  2342 _AX5043_MAXDROFFSET0	=	0x4108
                           004107  2343 G$AX5043_MAXDROFFSET1$0$0 == 0x4107
                           004107  2344 _AX5043_MAXDROFFSET1	=	0x4107
                           004106  2345 G$AX5043_MAXDROFFSET2$0$0 == 0x4106
                           004106  2346 _AX5043_MAXDROFFSET2	=	0x4106
                           00410B  2347 G$AX5043_MAXRFOFFSET0$0$0 == 0x410b
                           00410B  2348 _AX5043_MAXRFOFFSET0	=	0x410b
                           00410A  2349 G$AX5043_MAXRFOFFSET1$0$0 == 0x410a
                           00410A  2350 _AX5043_MAXRFOFFSET1	=	0x410a
                           004109  2351 G$AX5043_MAXRFOFFSET2$0$0 == 0x4109
                           004109  2352 _AX5043_MAXRFOFFSET2	=	0x4109
                           004164  2353 G$AX5043_MODCFGA$0$0 == 0x4164
                           004164  2354 _AX5043_MODCFGA	=	0x4164
                           004160  2355 G$AX5043_MODCFGF$0$0 == 0x4160
                           004160  2356 _AX5043_MODCFGF	=	0x4160
                           004010  2357 G$AX5043_MODULATION$0$0 == 0x4010
                           004010  2358 _AX5043_MODULATION	=	0x4010
                           004025  2359 G$AX5043_PINFUNCANTSEL$0$0 == 0x4025
                           004025  2360 _AX5043_PINFUNCANTSEL	=	0x4025
                           004023  2361 G$AX5043_PINFUNCDATA$0$0 == 0x4023
                           004023  2362 _AX5043_PINFUNCDATA	=	0x4023
                           004022  2363 G$AX5043_PINFUNCDCLK$0$0 == 0x4022
                           004022  2364 _AX5043_PINFUNCDCLK	=	0x4022
                           004024  2365 G$AX5043_PINFUNCIRQ$0$0 == 0x4024
                           004024  2366 _AX5043_PINFUNCIRQ	=	0x4024
                           004026  2367 G$AX5043_PINFUNCPWRAMP$0$0 == 0x4026
                           004026  2368 _AX5043_PINFUNCPWRAMP	=	0x4026
                           004021  2369 G$AX5043_PINFUNCSYSCLK$0$0 == 0x4021
                           004021  2370 _AX5043_PINFUNCSYSCLK	=	0x4021
                           004020  2371 G$AX5043_PINSTATE$0$0 == 0x4020
                           004020  2372 _AX5043_PINSTATE	=	0x4020
                           004233  2373 G$AX5043_PKTACCEPTFLAGS$0$0 == 0x4233
                           004233  2374 _AX5043_PKTACCEPTFLAGS	=	0x4233
                           004230  2375 G$AX5043_PKTCHUNKSIZE$0$0 == 0x4230
                           004230  2376 _AX5043_PKTCHUNKSIZE	=	0x4230
                           004231  2377 G$AX5043_PKTMISCFLAGS$0$0 == 0x4231
                           004231  2378 _AX5043_PKTMISCFLAGS	=	0x4231
                           004232  2379 G$AX5043_PKTSTOREFLAGS$0$0 == 0x4232
                           004232  2380 _AX5043_PKTSTOREFLAGS	=	0x4232
                           004031  2381 G$AX5043_PLLCPI$0$0 == 0x4031
                           004031  2382 _AX5043_PLLCPI	=	0x4031
                           004039  2383 G$AX5043_PLLCPIBOOST$0$0 == 0x4039
                           004039  2384 _AX5043_PLLCPIBOOST	=	0x4039
                           004182  2385 G$AX5043_PLLLOCKDET$0$0 == 0x4182
                           004182  2386 _AX5043_PLLLOCKDET	=	0x4182
                           004030  2387 G$AX5043_PLLLOOP$0$0 == 0x4030
                           004030  2388 _AX5043_PLLLOOP	=	0x4030
                           004038  2389 G$AX5043_PLLLOOPBOOST$0$0 == 0x4038
                           004038  2390 _AX5043_PLLLOOPBOOST	=	0x4038
                           004033  2391 G$AX5043_PLLRANGINGA$0$0 == 0x4033
                           004033  2392 _AX5043_PLLRANGINGA	=	0x4033
                           00403B  2393 G$AX5043_PLLRANGINGB$0$0 == 0x403b
                           00403B  2394 _AX5043_PLLRANGINGB	=	0x403b
                           004183  2395 G$AX5043_PLLRNGCLK$0$0 == 0x4183
                           004183  2396 _AX5043_PLLRNGCLK	=	0x4183
                           004032  2397 G$AX5043_PLLVCODIV$0$0 == 0x4032
                           004032  2398 _AX5043_PLLVCODIV	=	0x4032
                           004180  2399 G$AX5043_PLLVCOI$0$0 == 0x4180
                           004180  2400 _AX5043_PLLVCOI	=	0x4180
                           004181  2401 G$AX5043_PLLVCOIR$0$0 == 0x4181
                           004181  2402 _AX5043_PLLVCOIR	=	0x4181
                           004005  2403 G$AX5043_POWIRQMASK$0$0 == 0x4005
                           004005  2404 _AX5043_POWIRQMASK	=	0x4005
                           004003  2405 G$AX5043_POWSTAT$0$0 == 0x4003
                           004003  2406 _AX5043_POWSTAT	=	0x4003
                           004004  2407 G$AX5043_POWSTICKYSTAT$0$0 == 0x4004
                           004004  2408 _AX5043_POWSTICKYSTAT	=	0x4004
                           004027  2409 G$AX5043_PWRAMP$0$0 == 0x4027
                           004027  2410 _AX5043_PWRAMP	=	0x4027
                           004002  2411 G$AX5043_PWRMODE$0$0 == 0x4002
                           004002  2412 _AX5043_PWRMODE	=	0x4002
                           004009  2413 G$AX5043_RADIOEVENTMASK0$0$0 == 0x4009
                           004009  2414 _AX5043_RADIOEVENTMASK0	=	0x4009
                           004008  2415 G$AX5043_RADIOEVENTMASK1$0$0 == 0x4008
                           004008  2416 _AX5043_RADIOEVENTMASK1	=	0x4008
                           00400F  2417 G$AX5043_RADIOEVENTREQ0$0$0 == 0x400f
                           00400F  2418 _AX5043_RADIOEVENTREQ0	=	0x400f
                           00400E  2419 G$AX5043_RADIOEVENTREQ1$0$0 == 0x400e
                           00400E  2420 _AX5043_RADIOEVENTREQ1	=	0x400e
                           00401C  2421 G$AX5043_RADIOSTATE$0$0 == 0x401c
                           00401C  2422 _AX5043_RADIOSTATE	=	0x401c
                           004040  2423 G$AX5043_RSSI$0$0 == 0x4040
                           004040  2424 _AX5043_RSSI	=	0x4040
                           00422D  2425 G$AX5043_RSSIABSTHR$0$0 == 0x422d
                           00422D  2426 _AX5043_RSSIABSTHR	=	0x422d
                           00422C  2427 G$AX5043_RSSIREFERENCE$0$0 == 0x422c
                           00422C  2428 _AX5043_RSSIREFERENCE	=	0x422c
                           004105  2429 G$AX5043_RXDATARATE0$0$0 == 0x4105
                           004105  2430 _AX5043_RXDATARATE0	=	0x4105
                           004104  2431 G$AX5043_RXDATARATE1$0$0 == 0x4104
                           004104  2432 _AX5043_RXDATARATE1	=	0x4104
                           004103  2433 G$AX5043_RXDATARATE2$0$0 == 0x4103
                           004103  2434 _AX5043_RXDATARATE2	=	0x4103
                           004001  2435 G$AX5043_SCRATCH$0$0 == 0x4001
                           004001  2436 _AX5043_SCRATCH	=	0x4001
                           004000  2437 G$AX5043_SILICONREVISION$0$0 == 0x4000
                           004000  2438 _AX5043_SILICONREVISION	=	0x4000
                           00405B  2439 G$AX5043_TIMER0$0$0 == 0x405b
                           00405B  2440 _AX5043_TIMER0	=	0x405b
                           00405A  2441 G$AX5043_TIMER1$0$0 == 0x405a
                           00405A  2442 _AX5043_TIMER1	=	0x405a
                           004059  2443 G$AX5043_TIMER2$0$0 == 0x4059
                           004059  2444 _AX5043_TIMER2	=	0x4059
                           004227  2445 G$AX5043_TMGRXAGC$0$0 == 0x4227
                           004227  2446 _AX5043_TMGRXAGC	=	0x4227
                           004223  2447 G$AX5043_TMGRXBOOST$0$0 == 0x4223
                           004223  2448 _AX5043_TMGRXBOOST	=	0x4223
                           004226  2449 G$AX5043_TMGRXCOARSEAGC$0$0 == 0x4226
                           004226  2450 _AX5043_TMGRXCOARSEAGC	=	0x4226
                           004225  2451 G$AX5043_TMGRXOFFSACQ$0$0 == 0x4225
                           004225  2452 _AX5043_TMGRXOFFSACQ	=	0x4225
                           004229  2453 G$AX5043_TMGRXPREAMBLE1$0$0 == 0x4229
                           004229  2454 _AX5043_TMGRXPREAMBLE1	=	0x4229
                           00422A  2455 G$AX5043_TMGRXPREAMBLE2$0$0 == 0x422a
                           00422A  2456 _AX5043_TMGRXPREAMBLE2	=	0x422a
                           00422B  2457 G$AX5043_TMGRXPREAMBLE3$0$0 == 0x422b
                           00422B  2458 _AX5043_TMGRXPREAMBLE3	=	0x422b
                           004228  2459 G$AX5043_TMGRXRSSI$0$0 == 0x4228
                           004228  2460 _AX5043_TMGRXRSSI	=	0x4228
                           004224  2461 G$AX5043_TMGRXSETTLE$0$0 == 0x4224
                           004224  2462 _AX5043_TMGRXSETTLE	=	0x4224
                           004220  2463 G$AX5043_TMGTXBOOST$0$0 == 0x4220
                           004220  2464 _AX5043_TMGTXBOOST	=	0x4220
                           004221  2465 G$AX5043_TMGTXSETTLE$0$0 == 0x4221
                           004221  2466 _AX5043_TMGTXSETTLE	=	0x4221
                           004055  2467 G$AX5043_TRKAFSKDEMOD0$0$0 == 0x4055
                           004055  2468 _AX5043_TRKAFSKDEMOD0	=	0x4055
                           004054  2469 G$AX5043_TRKAFSKDEMOD1$0$0 == 0x4054
                           004054  2470 _AX5043_TRKAFSKDEMOD1	=	0x4054
                           004049  2471 G$AX5043_TRKAMPLITUDE0$0$0 == 0x4049
                           004049  2472 _AX5043_TRKAMPLITUDE0	=	0x4049
                           004048  2473 G$AX5043_TRKAMPLITUDE1$0$0 == 0x4048
                           004048  2474 _AX5043_TRKAMPLITUDE1	=	0x4048
                           004047  2475 G$AX5043_TRKDATARATE0$0$0 == 0x4047
                           004047  2476 _AX5043_TRKDATARATE0	=	0x4047
                           004046  2477 G$AX5043_TRKDATARATE1$0$0 == 0x4046
                           004046  2478 _AX5043_TRKDATARATE1	=	0x4046
                           004045  2479 G$AX5043_TRKDATARATE2$0$0 == 0x4045
                           004045  2480 _AX5043_TRKDATARATE2	=	0x4045
                           004051  2481 G$AX5043_TRKFREQ0$0$0 == 0x4051
                           004051  2482 _AX5043_TRKFREQ0	=	0x4051
                           004050  2483 G$AX5043_TRKFREQ1$0$0 == 0x4050
                           004050  2484 _AX5043_TRKFREQ1	=	0x4050
                           004053  2485 G$AX5043_TRKFSKDEMOD0$0$0 == 0x4053
                           004053  2486 _AX5043_TRKFSKDEMOD0	=	0x4053
                           004052  2487 G$AX5043_TRKFSKDEMOD1$0$0 == 0x4052
                           004052  2488 _AX5043_TRKFSKDEMOD1	=	0x4052
                           00404B  2489 G$AX5043_TRKPHASE0$0$0 == 0x404b
                           00404B  2490 _AX5043_TRKPHASE0	=	0x404b
                           00404A  2491 G$AX5043_TRKPHASE1$0$0 == 0x404a
                           00404A  2492 _AX5043_TRKPHASE1	=	0x404a
                           00404F  2493 G$AX5043_TRKRFFREQ0$0$0 == 0x404f
                           00404F  2494 _AX5043_TRKRFFREQ0	=	0x404f
                           00404E  2495 G$AX5043_TRKRFFREQ1$0$0 == 0x404e
                           00404E  2496 _AX5043_TRKRFFREQ1	=	0x404e
                           00404D  2497 G$AX5043_TRKRFFREQ2$0$0 == 0x404d
                           00404D  2498 _AX5043_TRKRFFREQ2	=	0x404d
                           004169  2499 G$AX5043_TXPWRCOEFFA0$0$0 == 0x4169
                           004169  2500 _AX5043_TXPWRCOEFFA0	=	0x4169
                           004168  2501 G$AX5043_TXPWRCOEFFA1$0$0 == 0x4168
                           004168  2502 _AX5043_TXPWRCOEFFA1	=	0x4168
                           00416B  2503 G$AX5043_TXPWRCOEFFB0$0$0 == 0x416b
                           00416B  2504 _AX5043_TXPWRCOEFFB0	=	0x416b
                           00416A  2505 G$AX5043_TXPWRCOEFFB1$0$0 == 0x416a
                           00416A  2506 _AX5043_TXPWRCOEFFB1	=	0x416a
                           00416D  2507 G$AX5043_TXPWRCOEFFC0$0$0 == 0x416d
                           00416D  2508 _AX5043_TXPWRCOEFFC0	=	0x416d
                           00416C  2509 G$AX5043_TXPWRCOEFFC1$0$0 == 0x416c
                           00416C  2510 _AX5043_TXPWRCOEFFC1	=	0x416c
                           00416F  2511 G$AX5043_TXPWRCOEFFD0$0$0 == 0x416f
                           00416F  2512 _AX5043_TXPWRCOEFFD0	=	0x416f
                           00416E  2513 G$AX5043_TXPWRCOEFFD1$0$0 == 0x416e
                           00416E  2514 _AX5043_TXPWRCOEFFD1	=	0x416e
                           004171  2515 G$AX5043_TXPWRCOEFFE0$0$0 == 0x4171
                           004171  2516 _AX5043_TXPWRCOEFFE0	=	0x4171
                           004170  2517 G$AX5043_TXPWRCOEFFE1$0$0 == 0x4170
                           004170  2518 _AX5043_TXPWRCOEFFE1	=	0x4170
                           004167  2519 G$AX5043_TXRATE0$0$0 == 0x4167
                           004167  2520 _AX5043_TXRATE0	=	0x4167
                           004166  2521 G$AX5043_TXRATE1$0$0 == 0x4166
                           004166  2522 _AX5043_TXRATE1	=	0x4166
                           004165  2523 G$AX5043_TXRATE2$0$0 == 0x4165
                           004165  2524 _AX5043_TXRATE2	=	0x4165
                           00406B  2525 G$AX5043_WAKEUP0$0$0 == 0x406b
                           00406B  2526 _AX5043_WAKEUP0	=	0x406b
                           00406A  2527 G$AX5043_WAKEUP1$0$0 == 0x406a
                           00406A  2528 _AX5043_WAKEUP1	=	0x406a
                           00406D  2529 G$AX5043_WAKEUPFREQ0$0$0 == 0x406d
                           00406D  2530 _AX5043_WAKEUPFREQ0	=	0x406d
                           00406C  2531 G$AX5043_WAKEUPFREQ1$0$0 == 0x406c
                           00406C  2532 _AX5043_WAKEUPFREQ1	=	0x406c
                           004069  2533 G$AX5043_WAKEUPTIMER0$0$0 == 0x4069
                           004069  2534 _AX5043_WAKEUPTIMER0	=	0x4069
                           004068  2535 G$AX5043_WAKEUPTIMER1$0$0 == 0x4068
                           004068  2536 _AX5043_WAKEUPTIMER1	=	0x4068
                           00406E  2537 G$AX5043_WAKEUPXOEARLY$0$0 == 0x406e
                           00406E  2538 _AX5043_WAKEUPXOEARLY	=	0x406e
                           004184  2539 G$AX5043_XTALCAP$0$0 == 0x4184
                           004184  2540 _AX5043_XTALCAP	=	0x4184
                           00401D  2541 G$AX5043_XTALSTATUS$0$0 == 0x401d
                           00401D  2542 _AX5043_XTALSTATUS	=	0x401d
                           004122  2543 G$AX5043_AGCAHYST0$0$0 == 0x4122
                           004122  2544 _AX5043_AGCAHYST0	=	0x4122
                           004132  2545 G$AX5043_AGCAHYST1$0$0 == 0x4132
                           004132  2546 _AX5043_AGCAHYST1	=	0x4132
                           004142  2547 G$AX5043_AGCAHYST2$0$0 == 0x4142
                           004142  2548 _AX5043_AGCAHYST2	=	0x4142
                           004152  2549 G$AX5043_AGCAHYST3$0$0 == 0x4152
                           004152  2550 _AX5043_AGCAHYST3	=	0x4152
                           004120  2551 G$AX5043_AGCGAIN0$0$0 == 0x4120
                           004120  2552 _AX5043_AGCGAIN0	=	0x4120
                           004130  2553 G$AX5043_AGCGAIN1$0$0 == 0x4130
                           004130  2554 _AX5043_AGCGAIN1	=	0x4130
                           004140  2555 G$AX5043_AGCGAIN2$0$0 == 0x4140
                           004140  2556 _AX5043_AGCGAIN2	=	0x4140
                           004150  2557 G$AX5043_AGCGAIN3$0$0 == 0x4150
                           004150  2558 _AX5043_AGCGAIN3	=	0x4150
                           004123  2559 G$AX5043_AGCMINMAX0$0$0 == 0x4123
                           004123  2560 _AX5043_AGCMINMAX0	=	0x4123
                           004133  2561 G$AX5043_AGCMINMAX1$0$0 == 0x4133
                           004133  2562 _AX5043_AGCMINMAX1	=	0x4133
                           004143  2563 G$AX5043_AGCMINMAX2$0$0 == 0x4143
                           004143  2564 _AX5043_AGCMINMAX2	=	0x4143
                           004153  2565 G$AX5043_AGCMINMAX3$0$0 == 0x4153
                           004153  2566 _AX5043_AGCMINMAX3	=	0x4153
                           004121  2567 G$AX5043_AGCTARGET0$0$0 == 0x4121
                           004121  2568 _AX5043_AGCTARGET0	=	0x4121
                           004131  2569 G$AX5043_AGCTARGET1$0$0 == 0x4131
                           004131  2570 _AX5043_AGCTARGET1	=	0x4131
                           004141  2571 G$AX5043_AGCTARGET2$0$0 == 0x4141
                           004141  2572 _AX5043_AGCTARGET2	=	0x4141
                           004151  2573 G$AX5043_AGCTARGET3$0$0 == 0x4151
                           004151  2574 _AX5043_AGCTARGET3	=	0x4151
                           00412B  2575 G$AX5043_AMPLITUDEGAIN0$0$0 == 0x412b
                           00412B  2576 _AX5043_AMPLITUDEGAIN0	=	0x412b
                           00413B  2577 G$AX5043_AMPLITUDEGAIN1$0$0 == 0x413b
                           00413B  2578 _AX5043_AMPLITUDEGAIN1	=	0x413b
                           00414B  2579 G$AX5043_AMPLITUDEGAIN2$0$0 == 0x414b
                           00414B  2580 _AX5043_AMPLITUDEGAIN2	=	0x414b
                           00415B  2581 G$AX5043_AMPLITUDEGAIN3$0$0 == 0x415b
                           00415B  2582 _AX5043_AMPLITUDEGAIN3	=	0x415b
                           00412F  2583 G$AX5043_BBOFFSRES0$0$0 == 0x412f
                           00412F  2584 _AX5043_BBOFFSRES0	=	0x412f
                           00413F  2585 G$AX5043_BBOFFSRES1$0$0 == 0x413f
                           00413F  2586 _AX5043_BBOFFSRES1	=	0x413f
                           00414F  2587 G$AX5043_BBOFFSRES2$0$0 == 0x414f
                           00414F  2588 _AX5043_BBOFFSRES2	=	0x414f
                           00415F  2589 G$AX5043_BBOFFSRES3$0$0 == 0x415f
                           00415F  2590 _AX5043_BBOFFSRES3	=	0x415f
                           004125  2591 G$AX5043_DRGAIN0$0$0 == 0x4125
                           004125  2592 _AX5043_DRGAIN0	=	0x4125
                           004135  2593 G$AX5043_DRGAIN1$0$0 == 0x4135
                           004135  2594 _AX5043_DRGAIN1	=	0x4135
                           004145  2595 G$AX5043_DRGAIN2$0$0 == 0x4145
                           004145  2596 _AX5043_DRGAIN2	=	0x4145
                           004155  2597 G$AX5043_DRGAIN3$0$0 == 0x4155
                           004155  2598 _AX5043_DRGAIN3	=	0x4155
                           00412E  2599 G$AX5043_FOURFSK0$0$0 == 0x412e
                           00412E  2600 _AX5043_FOURFSK0	=	0x412e
                           00413E  2601 G$AX5043_FOURFSK1$0$0 == 0x413e
                           00413E  2602 _AX5043_FOURFSK1	=	0x413e
                           00414E  2603 G$AX5043_FOURFSK2$0$0 == 0x414e
                           00414E  2604 _AX5043_FOURFSK2	=	0x414e
                           00415E  2605 G$AX5043_FOURFSK3$0$0 == 0x415e
                           00415E  2606 _AX5043_FOURFSK3	=	0x415e
                           00412D  2607 G$AX5043_FREQDEV00$0$0 == 0x412d
                           00412D  2608 _AX5043_FREQDEV00	=	0x412d
                           00413D  2609 G$AX5043_FREQDEV01$0$0 == 0x413d
                           00413D  2610 _AX5043_FREQDEV01	=	0x413d
                           00414D  2611 G$AX5043_FREQDEV02$0$0 == 0x414d
                           00414D  2612 _AX5043_FREQDEV02	=	0x414d
                           00415D  2613 G$AX5043_FREQDEV03$0$0 == 0x415d
                           00415D  2614 _AX5043_FREQDEV03	=	0x415d
                           00412C  2615 G$AX5043_FREQDEV10$0$0 == 0x412c
                           00412C  2616 _AX5043_FREQDEV10	=	0x412c
                           00413C  2617 G$AX5043_FREQDEV11$0$0 == 0x413c
                           00413C  2618 _AX5043_FREQDEV11	=	0x413c
                           00414C  2619 G$AX5043_FREQDEV12$0$0 == 0x414c
                           00414C  2620 _AX5043_FREQDEV12	=	0x414c
                           00415C  2621 G$AX5043_FREQDEV13$0$0 == 0x415c
                           00415C  2622 _AX5043_FREQDEV13	=	0x415c
                           004127  2623 G$AX5043_FREQUENCYGAINA0$0$0 == 0x4127
                           004127  2624 _AX5043_FREQUENCYGAINA0	=	0x4127
                           004137  2625 G$AX5043_FREQUENCYGAINA1$0$0 == 0x4137
                           004137  2626 _AX5043_FREQUENCYGAINA1	=	0x4137
                           004147  2627 G$AX5043_FREQUENCYGAINA2$0$0 == 0x4147
                           004147  2628 _AX5043_FREQUENCYGAINA2	=	0x4147
                           004157  2629 G$AX5043_FREQUENCYGAINA3$0$0 == 0x4157
                           004157  2630 _AX5043_FREQUENCYGAINA3	=	0x4157
                           004128  2631 G$AX5043_FREQUENCYGAINB0$0$0 == 0x4128
                           004128  2632 _AX5043_FREQUENCYGAINB0	=	0x4128
                           004138  2633 G$AX5043_FREQUENCYGAINB1$0$0 == 0x4138
                           004138  2634 _AX5043_FREQUENCYGAINB1	=	0x4138
                           004148  2635 G$AX5043_FREQUENCYGAINB2$0$0 == 0x4148
                           004148  2636 _AX5043_FREQUENCYGAINB2	=	0x4148
                           004158  2637 G$AX5043_FREQUENCYGAINB3$0$0 == 0x4158
                           004158  2638 _AX5043_FREQUENCYGAINB3	=	0x4158
                           004129  2639 G$AX5043_FREQUENCYGAINC0$0$0 == 0x4129
                           004129  2640 _AX5043_FREQUENCYGAINC0	=	0x4129
                           004139  2641 G$AX5043_FREQUENCYGAINC1$0$0 == 0x4139
                           004139  2642 _AX5043_FREQUENCYGAINC1	=	0x4139
                           004149  2643 G$AX5043_FREQUENCYGAINC2$0$0 == 0x4149
                           004149  2644 _AX5043_FREQUENCYGAINC2	=	0x4149
                           004159  2645 G$AX5043_FREQUENCYGAINC3$0$0 == 0x4159
                           004159  2646 _AX5043_FREQUENCYGAINC3	=	0x4159
                           00412A  2647 G$AX5043_FREQUENCYGAIND0$0$0 == 0x412a
                           00412A  2648 _AX5043_FREQUENCYGAIND0	=	0x412a
                           00413A  2649 G$AX5043_FREQUENCYGAIND1$0$0 == 0x413a
                           00413A  2650 _AX5043_FREQUENCYGAIND1	=	0x413a
                           00414A  2651 G$AX5043_FREQUENCYGAIND2$0$0 == 0x414a
                           00414A  2652 _AX5043_FREQUENCYGAIND2	=	0x414a
                           00415A  2653 G$AX5043_FREQUENCYGAIND3$0$0 == 0x415a
                           00415A  2654 _AX5043_FREQUENCYGAIND3	=	0x415a
                           004116  2655 G$AX5043_FREQUENCYLEAK$0$0 == 0x4116
                           004116  2656 _AX5043_FREQUENCYLEAK	=	0x4116
                           004126  2657 G$AX5043_PHASEGAIN0$0$0 == 0x4126
                           004126  2658 _AX5043_PHASEGAIN0	=	0x4126
                           004136  2659 G$AX5043_PHASEGAIN1$0$0 == 0x4136
                           004136  2660 _AX5043_PHASEGAIN1	=	0x4136
                           004146  2661 G$AX5043_PHASEGAIN2$0$0 == 0x4146
                           004146  2662 _AX5043_PHASEGAIN2	=	0x4146
                           004156  2663 G$AX5043_PHASEGAIN3$0$0 == 0x4156
                           004156  2664 _AX5043_PHASEGAIN3	=	0x4156
                           004207  2665 G$AX5043_PKTADDR0$0$0 == 0x4207
                           004207  2666 _AX5043_PKTADDR0	=	0x4207
                           004206  2667 G$AX5043_PKTADDR1$0$0 == 0x4206
                           004206  2668 _AX5043_PKTADDR1	=	0x4206
                           004205  2669 G$AX5043_PKTADDR2$0$0 == 0x4205
                           004205  2670 _AX5043_PKTADDR2	=	0x4205
                           004204  2671 G$AX5043_PKTADDR3$0$0 == 0x4204
                           004204  2672 _AX5043_PKTADDR3	=	0x4204
                           004200  2673 G$AX5043_PKTADDRCFG$0$0 == 0x4200
                           004200  2674 _AX5043_PKTADDRCFG	=	0x4200
                           00420B  2675 G$AX5043_PKTADDRMASK0$0$0 == 0x420b
                           00420B  2676 _AX5043_PKTADDRMASK0	=	0x420b
                           00420A  2677 G$AX5043_PKTADDRMASK1$0$0 == 0x420a
                           00420A  2678 _AX5043_PKTADDRMASK1	=	0x420a
                           004209  2679 G$AX5043_PKTADDRMASK2$0$0 == 0x4209
                           004209  2680 _AX5043_PKTADDRMASK2	=	0x4209
                           004208  2681 G$AX5043_PKTADDRMASK3$0$0 == 0x4208
                           004208  2682 _AX5043_PKTADDRMASK3	=	0x4208
                           004201  2683 G$AX5043_PKTLENCFG$0$0 == 0x4201
                           004201  2684 _AX5043_PKTLENCFG	=	0x4201
                           004202  2685 G$AX5043_PKTLENOFFSET$0$0 == 0x4202
                           004202  2686 _AX5043_PKTLENOFFSET	=	0x4202
                           004203  2687 G$AX5043_PKTMAXLEN$0$0 == 0x4203
                           004203  2688 _AX5043_PKTMAXLEN	=	0x4203
                           004118  2689 G$AX5043_RXPARAMCURSET$0$0 == 0x4118
                           004118  2690 _AX5043_RXPARAMCURSET	=	0x4118
                           004117  2691 G$AX5043_RXPARAMSETS$0$0 == 0x4117
                           004117  2692 _AX5043_RXPARAMSETS	=	0x4117
                           004124  2693 G$AX5043_TIMEGAIN0$0$0 == 0x4124
                           004124  2694 _AX5043_TIMEGAIN0	=	0x4124
                           004134  2695 G$AX5043_TIMEGAIN1$0$0 == 0x4134
                           004134  2696 _AX5043_TIMEGAIN1	=	0x4134
                           004144  2697 G$AX5043_TIMEGAIN2$0$0 == 0x4144
                           004144  2698 _AX5043_TIMEGAIN2	=	0x4144
                           004154  2699 G$AX5043_TIMEGAIN3$0$0 == 0x4154
                           004154  2700 _AX5043_TIMEGAIN3	=	0x4154
                           005114  2701 G$AX5043_AFSKCTRLNB$0$0 == 0x5114
                           005114  2702 _AX5043_AFSKCTRLNB	=	0x5114
                           005113  2703 G$AX5043_AFSKMARK0NB$0$0 == 0x5113
                           005113  2704 _AX5043_AFSKMARK0NB	=	0x5113
                           005112  2705 G$AX5043_AFSKMARK1NB$0$0 == 0x5112
                           005112  2706 _AX5043_AFSKMARK1NB	=	0x5112
                           005111  2707 G$AX5043_AFSKSPACE0NB$0$0 == 0x5111
                           005111  2708 _AX5043_AFSKSPACE0NB	=	0x5111
                           005110  2709 G$AX5043_AFSKSPACE1NB$0$0 == 0x5110
                           005110  2710 _AX5043_AFSKSPACE1NB	=	0x5110
                           005043  2711 G$AX5043_AGCCOUNTERNB$0$0 == 0x5043
                           005043  2712 _AX5043_AGCCOUNTERNB	=	0x5043
                           005115  2713 G$AX5043_AMPLFILTERNB$0$0 == 0x5115
                           005115  2714 _AX5043_AMPLFILTERNB	=	0x5115
                           005189  2715 G$AX5043_BBOFFSCAPNB$0$0 == 0x5189
                           005189  2716 _AX5043_BBOFFSCAPNB	=	0x5189
                           005188  2717 G$AX5043_BBTUNENB$0$0 == 0x5188
                           005188  2718 _AX5043_BBTUNENB	=	0x5188
                           005041  2719 G$AX5043_BGNDRSSINB$0$0 == 0x5041
                           005041  2720 _AX5043_BGNDRSSINB	=	0x5041
                           00522E  2721 G$AX5043_BGNDRSSIGAINNB$0$0 == 0x522e
                           00522E  2722 _AX5043_BGNDRSSIGAINNB	=	0x522e
                           00522F  2723 G$AX5043_BGNDRSSITHRNB$0$0 == 0x522f
                           00522F  2724 _AX5043_BGNDRSSITHRNB	=	0x522f
                           005017  2725 G$AX5043_CRCINIT0NB$0$0 == 0x5017
                           005017  2726 _AX5043_CRCINIT0NB	=	0x5017
                           005016  2727 G$AX5043_CRCINIT1NB$0$0 == 0x5016
                           005016  2728 _AX5043_CRCINIT1NB	=	0x5016
                           005015  2729 G$AX5043_CRCINIT2NB$0$0 == 0x5015
                           005015  2730 _AX5043_CRCINIT2NB	=	0x5015
                           005014  2731 G$AX5043_CRCINIT3NB$0$0 == 0x5014
                           005014  2732 _AX5043_CRCINIT3NB	=	0x5014
                           005332  2733 G$AX5043_DACCONFIGNB$0$0 == 0x5332
                           005332  2734 _AX5043_DACCONFIGNB	=	0x5332
                           005331  2735 G$AX5043_DACVALUE0NB$0$0 == 0x5331
                           005331  2736 _AX5043_DACVALUE0NB	=	0x5331
                           005330  2737 G$AX5043_DACVALUE1NB$0$0 == 0x5330
                           005330  2738 _AX5043_DACVALUE1NB	=	0x5330
                           005102  2739 G$AX5043_DECIMATIONNB$0$0 == 0x5102
                           005102  2740 _AX5043_DECIMATIONNB	=	0x5102
                           005042  2741 G$AX5043_DIVERSITYNB$0$0 == 0x5042
                           005042  2742 _AX5043_DIVERSITYNB	=	0x5042
                           005011  2743 G$AX5043_ENCODINGNB$0$0 == 0x5011
                           005011  2744 _AX5043_ENCODINGNB	=	0x5011
                           005018  2745 G$AX5043_FECNB$0$0 == 0x5018
                           005018  2746 _AX5043_FECNB	=	0x5018
                           00501A  2747 G$AX5043_FECSTATUSNB$0$0 == 0x501a
                           00501A  2748 _AX5043_FECSTATUSNB	=	0x501a
                           005019  2749 G$AX5043_FECSYNCNB$0$0 == 0x5019
                           005019  2750 _AX5043_FECSYNCNB	=	0x5019
                           00502B  2751 G$AX5043_FIFOCOUNT0NB$0$0 == 0x502b
                           00502B  2752 _AX5043_FIFOCOUNT0NB	=	0x502b
                           00502A  2753 G$AX5043_FIFOCOUNT1NB$0$0 == 0x502a
                           00502A  2754 _AX5043_FIFOCOUNT1NB	=	0x502a
                           005029  2755 G$AX5043_FIFODATANB$0$0 == 0x5029
                           005029  2756 _AX5043_FIFODATANB	=	0x5029
                           00502D  2757 G$AX5043_FIFOFREE0NB$0$0 == 0x502d
                           00502D  2758 _AX5043_FIFOFREE0NB	=	0x502d
                           00502C  2759 G$AX5043_FIFOFREE1NB$0$0 == 0x502c
                           00502C  2760 _AX5043_FIFOFREE1NB	=	0x502c
                           005028  2761 G$AX5043_FIFOSTATNB$0$0 == 0x5028
                           005028  2762 _AX5043_FIFOSTATNB	=	0x5028
                           00502F  2763 G$AX5043_FIFOTHRESH0NB$0$0 == 0x502f
                           00502F  2764 _AX5043_FIFOTHRESH0NB	=	0x502f
                           00502E  2765 G$AX5043_FIFOTHRESH1NB$0$0 == 0x502e
                           00502E  2766 _AX5043_FIFOTHRESH1NB	=	0x502e
                           005012  2767 G$AX5043_FRAMINGNB$0$0 == 0x5012
                           005012  2768 _AX5043_FRAMINGNB	=	0x5012
                           005037  2769 G$AX5043_FREQA0NB$0$0 == 0x5037
                           005037  2770 _AX5043_FREQA0NB	=	0x5037
                           005036  2771 G$AX5043_FREQA1NB$0$0 == 0x5036
                           005036  2772 _AX5043_FREQA1NB	=	0x5036
                           005035  2773 G$AX5043_FREQA2NB$0$0 == 0x5035
                           005035  2774 _AX5043_FREQA2NB	=	0x5035
                           005034  2775 G$AX5043_FREQA3NB$0$0 == 0x5034
                           005034  2776 _AX5043_FREQA3NB	=	0x5034
                           00503F  2777 G$AX5043_FREQB0NB$0$0 == 0x503f
                           00503F  2778 _AX5043_FREQB0NB	=	0x503f
                           00503E  2779 G$AX5043_FREQB1NB$0$0 == 0x503e
                           00503E  2780 _AX5043_FREQB1NB	=	0x503e
                           00503D  2781 G$AX5043_FREQB2NB$0$0 == 0x503d
                           00503D  2782 _AX5043_FREQB2NB	=	0x503d
                           00503C  2783 G$AX5043_FREQB3NB$0$0 == 0x503c
                           00503C  2784 _AX5043_FREQB3NB	=	0x503c
                           005163  2785 G$AX5043_FSKDEV0NB$0$0 == 0x5163
                           005163  2786 _AX5043_FSKDEV0NB	=	0x5163
                           005162  2787 G$AX5043_FSKDEV1NB$0$0 == 0x5162
                           005162  2788 _AX5043_FSKDEV1NB	=	0x5162
                           005161  2789 G$AX5043_FSKDEV2NB$0$0 == 0x5161
                           005161  2790 _AX5043_FSKDEV2NB	=	0x5161
                           00510D  2791 G$AX5043_FSKDMAX0NB$0$0 == 0x510d
                           00510D  2792 _AX5043_FSKDMAX0NB	=	0x510d
                           00510C  2793 G$AX5043_FSKDMAX1NB$0$0 == 0x510c
                           00510C  2794 _AX5043_FSKDMAX1NB	=	0x510c
                           00510F  2795 G$AX5043_FSKDMIN0NB$0$0 == 0x510f
                           00510F  2796 _AX5043_FSKDMIN0NB	=	0x510f
                           00510E  2797 G$AX5043_FSKDMIN1NB$0$0 == 0x510e
                           00510E  2798 _AX5043_FSKDMIN1NB	=	0x510e
                           005309  2799 G$AX5043_GPADC13VALUE0NB$0$0 == 0x5309
                           005309  2800 _AX5043_GPADC13VALUE0NB	=	0x5309
                           005308  2801 G$AX5043_GPADC13VALUE1NB$0$0 == 0x5308
                           005308  2802 _AX5043_GPADC13VALUE1NB	=	0x5308
                           005300  2803 G$AX5043_GPADCCTRLNB$0$0 == 0x5300
                           005300  2804 _AX5043_GPADCCTRLNB	=	0x5300
                           005301  2805 G$AX5043_GPADCPERIODNB$0$0 == 0x5301
                           005301  2806 _AX5043_GPADCPERIODNB	=	0x5301
                           005101  2807 G$AX5043_IFFREQ0NB$0$0 == 0x5101
                           005101  2808 _AX5043_IFFREQ0NB	=	0x5101
                           005100  2809 G$AX5043_IFFREQ1NB$0$0 == 0x5100
                           005100  2810 _AX5043_IFFREQ1NB	=	0x5100
                           00500B  2811 G$AX5043_IRQINVERSION0NB$0$0 == 0x500b
                           00500B  2812 _AX5043_IRQINVERSION0NB	=	0x500b
                           00500A  2813 G$AX5043_IRQINVERSION1NB$0$0 == 0x500a
                           00500A  2814 _AX5043_IRQINVERSION1NB	=	0x500a
                           005007  2815 G$AX5043_IRQMASK0NB$0$0 == 0x5007
                           005007  2816 _AX5043_IRQMASK0NB	=	0x5007
                           005006  2817 G$AX5043_IRQMASK1NB$0$0 == 0x5006
                           005006  2818 _AX5043_IRQMASK1NB	=	0x5006
                           00500D  2819 G$AX5043_IRQREQUEST0NB$0$0 == 0x500d
                           00500D  2820 _AX5043_IRQREQUEST0NB	=	0x500d
                           00500C  2821 G$AX5043_IRQREQUEST1NB$0$0 == 0x500c
                           00500C  2822 _AX5043_IRQREQUEST1NB	=	0x500c
                           005310  2823 G$AX5043_LPOSCCONFIGNB$0$0 == 0x5310
                           005310  2824 _AX5043_LPOSCCONFIGNB	=	0x5310
                           005317  2825 G$AX5043_LPOSCFREQ0NB$0$0 == 0x5317
                           005317  2826 _AX5043_LPOSCFREQ0NB	=	0x5317
                           005316  2827 G$AX5043_LPOSCFREQ1NB$0$0 == 0x5316
                           005316  2828 _AX5043_LPOSCFREQ1NB	=	0x5316
                           005313  2829 G$AX5043_LPOSCKFILT0NB$0$0 == 0x5313
                           005313  2830 _AX5043_LPOSCKFILT0NB	=	0x5313
                           005312  2831 G$AX5043_LPOSCKFILT1NB$0$0 == 0x5312
                           005312  2832 _AX5043_LPOSCKFILT1NB	=	0x5312
                           005319  2833 G$AX5043_LPOSCPER0NB$0$0 == 0x5319
                           005319  2834 _AX5043_LPOSCPER0NB	=	0x5319
                           005318  2835 G$AX5043_LPOSCPER1NB$0$0 == 0x5318
                           005318  2836 _AX5043_LPOSCPER1NB	=	0x5318
                           005315  2837 G$AX5043_LPOSCREF0NB$0$0 == 0x5315
                           005315  2838 _AX5043_LPOSCREF0NB	=	0x5315
                           005314  2839 G$AX5043_LPOSCREF1NB$0$0 == 0x5314
                           005314  2840 _AX5043_LPOSCREF1NB	=	0x5314
                           005311  2841 G$AX5043_LPOSCSTATUSNB$0$0 == 0x5311
                           005311  2842 _AX5043_LPOSCSTATUSNB	=	0x5311
                           005214  2843 G$AX5043_MATCH0LENNB$0$0 == 0x5214
                           005214  2844 _AX5043_MATCH0LENNB	=	0x5214
                           005216  2845 G$AX5043_MATCH0MAXNB$0$0 == 0x5216
                           005216  2846 _AX5043_MATCH0MAXNB	=	0x5216
                           005215  2847 G$AX5043_MATCH0MINNB$0$0 == 0x5215
                           005215  2848 _AX5043_MATCH0MINNB	=	0x5215
                           005213  2849 G$AX5043_MATCH0PAT0NB$0$0 == 0x5213
                           005213  2850 _AX5043_MATCH0PAT0NB	=	0x5213
                           005212  2851 G$AX5043_MATCH0PAT1NB$0$0 == 0x5212
                           005212  2852 _AX5043_MATCH0PAT1NB	=	0x5212
                           005211  2853 G$AX5043_MATCH0PAT2NB$0$0 == 0x5211
                           005211  2854 _AX5043_MATCH0PAT2NB	=	0x5211
                           005210  2855 G$AX5043_MATCH0PAT3NB$0$0 == 0x5210
                           005210  2856 _AX5043_MATCH0PAT3NB	=	0x5210
                           00521C  2857 G$AX5043_MATCH1LENNB$0$0 == 0x521c
                           00521C  2858 _AX5043_MATCH1LENNB	=	0x521c
                           00521E  2859 G$AX5043_MATCH1MAXNB$0$0 == 0x521e
                           00521E  2860 _AX5043_MATCH1MAXNB	=	0x521e
                           00521D  2861 G$AX5043_MATCH1MINNB$0$0 == 0x521d
                           00521D  2862 _AX5043_MATCH1MINNB	=	0x521d
                           005219  2863 G$AX5043_MATCH1PAT0NB$0$0 == 0x5219
                           005219  2864 _AX5043_MATCH1PAT0NB	=	0x5219
                           005218  2865 G$AX5043_MATCH1PAT1NB$0$0 == 0x5218
                           005218  2866 _AX5043_MATCH1PAT1NB	=	0x5218
                           005108  2867 G$AX5043_MAXDROFFSET0NB$0$0 == 0x5108
                           005108  2868 _AX5043_MAXDROFFSET0NB	=	0x5108
                           005107  2869 G$AX5043_MAXDROFFSET1NB$0$0 == 0x5107
                           005107  2870 _AX5043_MAXDROFFSET1NB	=	0x5107
                           005106  2871 G$AX5043_MAXDROFFSET2NB$0$0 == 0x5106
                           005106  2872 _AX5043_MAXDROFFSET2NB	=	0x5106
                           00510B  2873 G$AX5043_MAXRFOFFSET0NB$0$0 == 0x510b
                           00510B  2874 _AX5043_MAXRFOFFSET0NB	=	0x510b
                           00510A  2875 G$AX5043_MAXRFOFFSET1NB$0$0 == 0x510a
                           00510A  2876 _AX5043_MAXRFOFFSET1NB	=	0x510a
                           005109  2877 G$AX5043_MAXRFOFFSET2NB$0$0 == 0x5109
                           005109  2878 _AX5043_MAXRFOFFSET2NB	=	0x5109
                           005164  2879 G$AX5043_MODCFGANB$0$0 == 0x5164
                           005164  2880 _AX5043_MODCFGANB	=	0x5164
                           005160  2881 G$AX5043_MODCFGFNB$0$0 == 0x5160
                           005160  2882 _AX5043_MODCFGFNB	=	0x5160
                           005F5F  2883 G$AX5043_MODCFGPNB$0$0 == 0x5f5f
                           005F5F  2884 _AX5043_MODCFGPNB	=	0x5f5f
                           005010  2885 G$AX5043_MODULATIONNB$0$0 == 0x5010
                           005010  2886 _AX5043_MODULATIONNB	=	0x5010
                           005025  2887 G$AX5043_PINFUNCANTSELNB$0$0 == 0x5025
                           005025  2888 _AX5043_PINFUNCANTSELNB	=	0x5025
                           005023  2889 G$AX5043_PINFUNCDATANB$0$0 == 0x5023
                           005023  2890 _AX5043_PINFUNCDATANB	=	0x5023
                           005022  2891 G$AX5043_PINFUNCDCLKNB$0$0 == 0x5022
                           005022  2892 _AX5043_PINFUNCDCLKNB	=	0x5022
                           005024  2893 G$AX5043_PINFUNCIRQNB$0$0 == 0x5024
                           005024  2894 _AX5043_PINFUNCIRQNB	=	0x5024
                           005026  2895 G$AX5043_PINFUNCPWRAMPNB$0$0 == 0x5026
                           005026  2896 _AX5043_PINFUNCPWRAMPNB	=	0x5026
                           005021  2897 G$AX5043_PINFUNCSYSCLKNB$0$0 == 0x5021
                           005021  2898 _AX5043_PINFUNCSYSCLKNB	=	0x5021
                           005020  2899 G$AX5043_PINSTATENB$0$0 == 0x5020
                           005020  2900 _AX5043_PINSTATENB	=	0x5020
                           005233  2901 G$AX5043_PKTACCEPTFLAGSNB$0$0 == 0x5233
                           005233  2902 _AX5043_PKTACCEPTFLAGSNB	=	0x5233
                           005230  2903 G$AX5043_PKTCHUNKSIZENB$0$0 == 0x5230
                           005230  2904 _AX5043_PKTCHUNKSIZENB	=	0x5230
                           005231  2905 G$AX5043_PKTMISCFLAGSNB$0$0 == 0x5231
                           005231  2906 _AX5043_PKTMISCFLAGSNB	=	0x5231
                           005232  2907 G$AX5043_PKTSTOREFLAGSNB$0$0 == 0x5232
                           005232  2908 _AX5043_PKTSTOREFLAGSNB	=	0x5232
                           005031  2909 G$AX5043_PLLCPINB$0$0 == 0x5031
                           005031  2910 _AX5043_PLLCPINB	=	0x5031
                           005039  2911 G$AX5043_PLLCPIBOOSTNB$0$0 == 0x5039
                           005039  2912 _AX5043_PLLCPIBOOSTNB	=	0x5039
                           005182  2913 G$AX5043_PLLLOCKDETNB$0$0 == 0x5182
                           005182  2914 _AX5043_PLLLOCKDETNB	=	0x5182
                           005030  2915 G$AX5043_PLLLOOPNB$0$0 == 0x5030
                           005030  2916 _AX5043_PLLLOOPNB	=	0x5030
                           005038  2917 G$AX5043_PLLLOOPBOOSTNB$0$0 == 0x5038
                           005038  2918 _AX5043_PLLLOOPBOOSTNB	=	0x5038
                           005033  2919 G$AX5043_PLLRANGINGANB$0$0 == 0x5033
                           005033  2920 _AX5043_PLLRANGINGANB	=	0x5033
                           00503B  2921 G$AX5043_PLLRANGINGBNB$0$0 == 0x503b
                           00503B  2922 _AX5043_PLLRANGINGBNB	=	0x503b
                           005183  2923 G$AX5043_PLLRNGCLKNB$0$0 == 0x5183
                           005183  2924 _AX5043_PLLRNGCLKNB	=	0x5183
                           005032  2925 G$AX5043_PLLVCODIVNB$0$0 == 0x5032
                           005032  2926 _AX5043_PLLVCODIVNB	=	0x5032
                           005180  2927 G$AX5043_PLLVCOINB$0$0 == 0x5180
                           005180  2928 _AX5043_PLLVCOINB	=	0x5180
                           005181  2929 G$AX5043_PLLVCOIRNB$0$0 == 0x5181
                           005181  2930 _AX5043_PLLVCOIRNB	=	0x5181
                           005F08  2931 G$AX5043_POWCTRL1NB$0$0 == 0x5f08
                           005F08  2932 _AX5043_POWCTRL1NB	=	0x5f08
                           005005  2933 G$AX5043_POWIRQMASKNB$0$0 == 0x5005
                           005005  2934 _AX5043_POWIRQMASKNB	=	0x5005
                           005003  2935 G$AX5043_POWSTATNB$0$0 == 0x5003
                           005003  2936 _AX5043_POWSTATNB	=	0x5003
                           005004  2937 G$AX5043_POWSTICKYSTATNB$0$0 == 0x5004
                           005004  2938 _AX5043_POWSTICKYSTATNB	=	0x5004
                           005027  2939 G$AX5043_PWRAMPNB$0$0 == 0x5027
                           005027  2940 _AX5043_PWRAMPNB	=	0x5027
                           005002  2941 G$AX5043_PWRMODENB$0$0 == 0x5002
                           005002  2942 _AX5043_PWRMODENB	=	0x5002
                           005009  2943 G$AX5043_RADIOEVENTMASK0NB$0$0 == 0x5009
                           005009  2944 _AX5043_RADIOEVENTMASK0NB	=	0x5009
                           005008  2945 G$AX5043_RADIOEVENTMASK1NB$0$0 == 0x5008
                           005008  2946 _AX5043_RADIOEVENTMASK1NB	=	0x5008
                           00500F  2947 G$AX5043_RADIOEVENTREQ0NB$0$0 == 0x500f
                           00500F  2948 _AX5043_RADIOEVENTREQ0NB	=	0x500f
                           00500E  2949 G$AX5043_RADIOEVENTREQ1NB$0$0 == 0x500e
                           00500E  2950 _AX5043_RADIOEVENTREQ1NB	=	0x500e
                           00501C  2951 G$AX5043_RADIOSTATENB$0$0 == 0x501c
                           00501C  2952 _AX5043_RADIOSTATENB	=	0x501c
                           005F0D  2953 G$AX5043_REFNB$0$0 == 0x5f0d
                           005F0D  2954 _AX5043_REFNB	=	0x5f0d
                           005040  2955 G$AX5043_RSSINB$0$0 == 0x5040
                           005040  2956 _AX5043_RSSINB	=	0x5040
                           00522D  2957 G$AX5043_RSSIABSTHRNB$0$0 == 0x522d
                           00522D  2958 _AX5043_RSSIABSTHRNB	=	0x522d
                           00522C  2959 G$AX5043_RSSIREFERENCENB$0$0 == 0x522c
                           00522C  2960 _AX5043_RSSIREFERENCENB	=	0x522c
                           005105  2961 G$AX5043_RXDATARATE0NB$0$0 == 0x5105
                           005105  2962 _AX5043_RXDATARATE0NB	=	0x5105
                           005104  2963 G$AX5043_RXDATARATE1NB$0$0 == 0x5104
                           005104  2964 _AX5043_RXDATARATE1NB	=	0x5104
                           005103  2965 G$AX5043_RXDATARATE2NB$0$0 == 0x5103
                           005103  2966 _AX5043_RXDATARATE2NB	=	0x5103
                           005001  2967 G$AX5043_SCRATCHNB$0$0 == 0x5001
                           005001  2968 _AX5043_SCRATCHNB	=	0x5001
                           005000  2969 G$AX5043_SILICONREVISIONNB$0$0 == 0x5000
                           005000  2970 _AX5043_SILICONREVISIONNB	=	0x5000
                           00505B  2971 G$AX5043_TIMER0NB$0$0 == 0x505b
                           00505B  2972 _AX5043_TIMER0NB	=	0x505b
                           00505A  2973 G$AX5043_TIMER1NB$0$0 == 0x505a
                           00505A  2974 _AX5043_TIMER1NB	=	0x505a
                           005059  2975 G$AX5043_TIMER2NB$0$0 == 0x5059
                           005059  2976 _AX5043_TIMER2NB	=	0x5059
                           005227  2977 G$AX5043_TMGRXAGCNB$0$0 == 0x5227
                           005227  2978 _AX5043_TMGRXAGCNB	=	0x5227
                           005223  2979 G$AX5043_TMGRXBOOSTNB$0$0 == 0x5223
                           005223  2980 _AX5043_TMGRXBOOSTNB	=	0x5223
                           005226  2981 G$AX5043_TMGRXCOARSEAGCNB$0$0 == 0x5226
                           005226  2982 _AX5043_TMGRXCOARSEAGCNB	=	0x5226
                           005225  2983 G$AX5043_TMGRXOFFSACQNB$0$0 == 0x5225
                           005225  2984 _AX5043_TMGRXOFFSACQNB	=	0x5225
                           005229  2985 G$AX5043_TMGRXPREAMBLE1NB$0$0 == 0x5229
                           005229  2986 _AX5043_TMGRXPREAMBLE1NB	=	0x5229
                           00522A  2987 G$AX5043_TMGRXPREAMBLE2NB$0$0 == 0x522a
                           00522A  2988 _AX5043_TMGRXPREAMBLE2NB	=	0x522a
                           00522B  2989 G$AX5043_TMGRXPREAMBLE3NB$0$0 == 0x522b
                           00522B  2990 _AX5043_TMGRXPREAMBLE3NB	=	0x522b
                           005228  2991 G$AX5043_TMGRXRSSINB$0$0 == 0x5228
                           005228  2992 _AX5043_TMGRXRSSINB	=	0x5228
                           005224  2993 G$AX5043_TMGRXSETTLENB$0$0 == 0x5224
                           005224  2994 _AX5043_TMGRXSETTLENB	=	0x5224
                           005220  2995 G$AX5043_TMGTXBOOSTNB$0$0 == 0x5220
                           005220  2996 _AX5043_TMGTXBOOSTNB	=	0x5220
                           005221  2997 G$AX5043_TMGTXSETTLENB$0$0 == 0x5221
                           005221  2998 _AX5043_TMGTXSETTLENB	=	0x5221
                           005055  2999 G$AX5043_TRKAFSKDEMOD0NB$0$0 == 0x5055
                           005055  3000 _AX5043_TRKAFSKDEMOD0NB	=	0x5055
                           005054  3001 G$AX5043_TRKAFSKDEMOD1NB$0$0 == 0x5054
                           005054  3002 _AX5043_TRKAFSKDEMOD1NB	=	0x5054
                           005049  3003 G$AX5043_TRKAMPLITUDE0NB$0$0 == 0x5049
                           005049  3004 _AX5043_TRKAMPLITUDE0NB	=	0x5049
                           005048  3005 G$AX5043_TRKAMPLITUDE1NB$0$0 == 0x5048
                           005048  3006 _AX5043_TRKAMPLITUDE1NB	=	0x5048
                           005047  3007 G$AX5043_TRKDATARATE0NB$0$0 == 0x5047
                           005047  3008 _AX5043_TRKDATARATE0NB	=	0x5047
                           005046  3009 G$AX5043_TRKDATARATE1NB$0$0 == 0x5046
                           005046  3010 _AX5043_TRKDATARATE1NB	=	0x5046
                           005045  3011 G$AX5043_TRKDATARATE2NB$0$0 == 0x5045
                           005045  3012 _AX5043_TRKDATARATE2NB	=	0x5045
                           005051  3013 G$AX5043_TRKFREQ0NB$0$0 == 0x5051
                           005051  3014 _AX5043_TRKFREQ0NB	=	0x5051
                           005050  3015 G$AX5043_TRKFREQ1NB$0$0 == 0x5050
                           005050  3016 _AX5043_TRKFREQ1NB	=	0x5050
                           005053  3017 G$AX5043_TRKFSKDEMOD0NB$0$0 == 0x5053
                           005053  3018 _AX5043_TRKFSKDEMOD0NB	=	0x5053
                           005052  3019 G$AX5043_TRKFSKDEMOD1NB$0$0 == 0x5052
                           005052  3020 _AX5043_TRKFSKDEMOD1NB	=	0x5052
                           00504B  3021 G$AX5043_TRKPHASE0NB$0$0 == 0x504b
                           00504B  3022 _AX5043_TRKPHASE0NB	=	0x504b
                           00504A  3023 G$AX5043_TRKPHASE1NB$0$0 == 0x504a
                           00504A  3024 _AX5043_TRKPHASE1NB	=	0x504a
                           00504F  3025 G$AX5043_TRKRFFREQ0NB$0$0 == 0x504f
                           00504F  3026 _AX5043_TRKRFFREQ0NB	=	0x504f
                           00504E  3027 G$AX5043_TRKRFFREQ1NB$0$0 == 0x504e
                           00504E  3028 _AX5043_TRKRFFREQ1NB	=	0x504e
                           00504D  3029 G$AX5043_TRKRFFREQ2NB$0$0 == 0x504d
                           00504D  3030 _AX5043_TRKRFFREQ2NB	=	0x504d
                           005169  3031 G$AX5043_TXPWRCOEFFA0NB$0$0 == 0x5169
                           005169  3032 _AX5043_TXPWRCOEFFA0NB	=	0x5169
                           005168  3033 G$AX5043_TXPWRCOEFFA1NB$0$0 == 0x5168
                           005168  3034 _AX5043_TXPWRCOEFFA1NB	=	0x5168
                           00516B  3035 G$AX5043_TXPWRCOEFFB0NB$0$0 == 0x516b
                           00516B  3036 _AX5043_TXPWRCOEFFB0NB	=	0x516b
                           00516A  3037 G$AX5043_TXPWRCOEFFB1NB$0$0 == 0x516a
                           00516A  3038 _AX5043_TXPWRCOEFFB1NB	=	0x516a
                           00516D  3039 G$AX5043_TXPWRCOEFFC0NB$0$0 == 0x516d
                           00516D  3040 _AX5043_TXPWRCOEFFC0NB	=	0x516d
                           00516C  3041 G$AX5043_TXPWRCOEFFC1NB$0$0 == 0x516c
                           00516C  3042 _AX5043_TXPWRCOEFFC1NB	=	0x516c
                           00516F  3043 G$AX5043_TXPWRCOEFFD0NB$0$0 == 0x516f
                           00516F  3044 _AX5043_TXPWRCOEFFD0NB	=	0x516f
                           00516E  3045 G$AX5043_TXPWRCOEFFD1NB$0$0 == 0x516e
                           00516E  3046 _AX5043_TXPWRCOEFFD1NB	=	0x516e
                           005171  3047 G$AX5043_TXPWRCOEFFE0NB$0$0 == 0x5171
                           005171  3048 _AX5043_TXPWRCOEFFE0NB	=	0x5171
                           005170  3049 G$AX5043_TXPWRCOEFFE1NB$0$0 == 0x5170
                           005170  3050 _AX5043_TXPWRCOEFFE1NB	=	0x5170
                           005167  3051 G$AX5043_TXRATE0NB$0$0 == 0x5167
                           005167  3052 _AX5043_TXRATE0NB	=	0x5167
                           005166  3053 G$AX5043_TXRATE1NB$0$0 == 0x5166
                           005166  3054 _AX5043_TXRATE1NB	=	0x5166
                           005165  3055 G$AX5043_TXRATE2NB$0$0 == 0x5165
                           005165  3056 _AX5043_TXRATE2NB	=	0x5165
                           00506B  3057 G$AX5043_WAKEUP0NB$0$0 == 0x506b
                           00506B  3058 _AX5043_WAKEUP0NB	=	0x506b
                           00506A  3059 G$AX5043_WAKEUP1NB$0$0 == 0x506a
                           00506A  3060 _AX5043_WAKEUP1NB	=	0x506a
                           00506D  3061 G$AX5043_WAKEUPFREQ0NB$0$0 == 0x506d
                           00506D  3062 _AX5043_WAKEUPFREQ0NB	=	0x506d
                           00506C  3063 G$AX5043_WAKEUPFREQ1NB$0$0 == 0x506c
                           00506C  3064 _AX5043_WAKEUPFREQ1NB	=	0x506c
                           005069  3065 G$AX5043_WAKEUPTIMER0NB$0$0 == 0x5069
                           005069  3066 _AX5043_WAKEUPTIMER0NB	=	0x5069
                           005068  3067 G$AX5043_WAKEUPTIMER1NB$0$0 == 0x5068
                           005068  3068 _AX5043_WAKEUPTIMER1NB	=	0x5068
                           00506E  3069 G$AX5043_WAKEUPXOEARLYNB$0$0 == 0x506e
                           00506E  3070 _AX5043_WAKEUPXOEARLYNB	=	0x506e
                           005F11  3071 G$AX5043_XTALAMPLNB$0$0 == 0x5f11
                           005F11  3072 _AX5043_XTALAMPLNB	=	0x5f11
                           005184  3073 G$AX5043_XTALCAPNB$0$0 == 0x5184
                           005184  3074 _AX5043_XTALCAPNB	=	0x5184
                           005F10  3075 G$AX5043_XTALOSCNB$0$0 == 0x5f10
                           005F10  3076 _AX5043_XTALOSCNB	=	0x5f10
                           00501D  3077 G$AX5043_XTALSTATUSNB$0$0 == 0x501d
                           00501D  3078 _AX5043_XTALSTATUSNB	=	0x501d
                           005F00  3079 G$AX5043_0xF00NB$0$0 == 0x5f00
                           005F00  3080 _AX5043_0xF00NB	=	0x5f00
                           005F0C  3081 G$AX5043_0xF0CNB$0$0 == 0x5f0c
                           005F0C  3082 _AX5043_0xF0CNB	=	0x5f0c
                           005F18  3083 G$AX5043_0xF18NB$0$0 == 0x5f18
                           005F18  3084 _AX5043_0xF18NB	=	0x5f18
                           005F1C  3085 G$AX5043_0xF1CNB$0$0 == 0x5f1c
                           005F1C  3086 _AX5043_0xF1CNB	=	0x5f1c
                           005F21  3087 G$AX5043_0xF21NB$0$0 == 0x5f21
                           005F21  3088 _AX5043_0xF21NB	=	0x5f21
                           005F22  3089 G$AX5043_0xF22NB$0$0 == 0x5f22
                           005F22  3090 _AX5043_0xF22NB	=	0x5f22
                           005F23  3091 G$AX5043_0xF23NB$0$0 == 0x5f23
                           005F23  3092 _AX5043_0xF23NB	=	0x5f23
                           005F26  3093 G$AX5043_0xF26NB$0$0 == 0x5f26
                           005F26  3094 _AX5043_0xF26NB	=	0x5f26
                           005F30  3095 G$AX5043_0xF30NB$0$0 == 0x5f30
                           005F30  3096 _AX5043_0xF30NB	=	0x5f30
                           005F31  3097 G$AX5043_0xF31NB$0$0 == 0x5f31
                           005F31  3098 _AX5043_0xF31NB	=	0x5f31
                           005F32  3099 G$AX5043_0xF32NB$0$0 == 0x5f32
                           005F32  3100 _AX5043_0xF32NB	=	0x5f32
                           005F33  3101 G$AX5043_0xF33NB$0$0 == 0x5f33
                           005F33  3102 _AX5043_0xF33NB	=	0x5f33
                           005F34  3103 G$AX5043_0xF34NB$0$0 == 0x5f34
                           005F34  3104 _AX5043_0xF34NB	=	0x5f34
                           005F35  3105 G$AX5043_0xF35NB$0$0 == 0x5f35
                           005F35  3106 _AX5043_0xF35NB	=	0x5f35
                           005F44  3107 G$AX5043_0xF44NB$0$0 == 0x5f44
                           005F44  3108 _AX5043_0xF44NB	=	0x5f44
                           005122  3109 G$AX5043_AGCAHYST0NB$0$0 == 0x5122
                           005122  3110 _AX5043_AGCAHYST0NB	=	0x5122
                           005132  3111 G$AX5043_AGCAHYST1NB$0$0 == 0x5132
                           005132  3112 _AX5043_AGCAHYST1NB	=	0x5132
                           005142  3113 G$AX5043_AGCAHYST2NB$0$0 == 0x5142
                           005142  3114 _AX5043_AGCAHYST2NB	=	0x5142
                           005152  3115 G$AX5043_AGCAHYST3NB$0$0 == 0x5152
                           005152  3116 _AX5043_AGCAHYST3NB	=	0x5152
                           005120  3117 G$AX5043_AGCGAIN0NB$0$0 == 0x5120
                           005120  3118 _AX5043_AGCGAIN0NB	=	0x5120
                           005130  3119 G$AX5043_AGCGAIN1NB$0$0 == 0x5130
                           005130  3120 _AX5043_AGCGAIN1NB	=	0x5130
                           005140  3121 G$AX5043_AGCGAIN2NB$0$0 == 0x5140
                           005140  3122 _AX5043_AGCGAIN2NB	=	0x5140
                           005150  3123 G$AX5043_AGCGAIN3NB$0$0 == 0x5150
                           005150  3124 _AX5043_AGCGAIN3NB	=	0x5150
                           005123  3125 G$AX5043_AGCMINMAX0NB$0$0 == 0x5123
                           005123  3126 _AX5043_AGCMINMAX0NB	=	0x5123
                           005133  3127 G$AX5043_AGCMINMAX1NB$0$0 == 0x5133
                           005133  3128 _AX5043_AGCMINMAX1NB	=	0x5133
                           005143  3129 G$AX5043_AGCMINMAX2NB$0$0 == 0x5143
                           005143  3130 _AX5043_AGCMINMAX2NB	=	0x5143
                           005153  3131 G$AX5043_AGCMINMAX3NB$0$0 == 0x5153
                           005153  3132 _AX5043_AGCMINMAX3NB	=	0x5153
                           005121  3133 G$AX5043_AGCTARGET0NB$0$0 == 0x5121
                           005121  3134 _AX5043_AGCTARGET0NB	=	0x5121
                           005131  3135 G$AX5043_AGCTARGET1NB$0$0 == 0x5131
                           005131  3136 _AX5043_AGCTARGET1NB	=	0x5131
                           005141  3137 G$AX5043_AGCTARGET2NB$0$0 == 0x5141
                           005141  3138 _AX5043_AGCTARGET2NB	=	0x5141
                           005151  3139 G$AX5043_AGCTARGET3NB$0$0 == 0x5151
                           005151  3140 _AX5043_AGCTARGET3NB	=	0x5151
                           00512B  3141 G$AX5043_AMPLITUDEGAIN0NB$0$0 == 0x512b
                           00512B  3142 _AX5043_AMPLITUDEGAIN0NB	=	0x512b
                           00513B  3143 G$AX5043_AMPLITUDEGAIN1NB$0$0 == 0x513b
                           00513B  3144 _AX5043_AMPLITUDEGAIN1NB	=	0x513b
                           00514B  3145 G$AX5043_AMPLITUDEGAIN2NB$0$0 == 0x514b
                           00514B  3146 _AX5043_AMPLITUDEGAIN2NB	=	0x514b
                           00515B  3147 G$AX5043_AMPLITUDEGAIN3NB$0$0 == 0x515b
                           00515B  3148 _AX5043_AMPLITUDEGAIN3NB	=	0x515b
                           00512F  3149 G$AX5043_BBOFFSRES0NB$0$0 == 0x512f
                           00512F  3150 _AX5043_BBOFFSRES0NB	=	0x512f
                           00513F  3151 G$AX5043_BBOFFSRES1NB$0$0 == 0x513f
                           00513F  3152 _AX5043_BBOFFSRES1NB	=	0x513f
                           00514F  3153 G$AX5043_BBOFFSRES2NB$0$0 == 0x514f
                           00514F  3154 _AX5043_BBOFFSRES2NB	=	0x514f
                           00515F  3155 G$AX5043_BBOFFSRES3NB$0$0 == 0x515f
                           00515F  3156 _AX5043_BBOFFSRES3NB	=	0x515f
                           005125  3157 G$AX5043_DRGAIN0NB$0$0 == 0x5125
                           005125  3158 _AX5043_DRGAIN0NB	=	0x5125
                           005135  3159 G$AX5043_DRGAIN1NB$0$0 == 0x5135
                           005135  3160 _AX5043_DRGAIN1NB	=	0x5135
                           005145  3161 G$AX5043_DRGAIN2NB$0$0 == 0x5145
                           005145  3162 _AX5043_DRGAIN2NB	=	0x5145
                           005155  3163 G$AX5043_DRGAIN3NB$0$0 == 0x5155
                           005155  3164 _AX5043_DRGAIN3NB	=	0x5155
                           00512E  3165 G$AX5043_FOURFSK0NB$0$0 == 0x512e
                           00512E  3166 _AX5043_FOURFSK0NB	=	0x512e
                           00513E  3167 G$AX5043_FOURFSK1NB$0$0 == 0x513e
                           00513E  3168 _AX5043_FOURFSK1NB	=	0x513e
                           00514E  3169 G$AX5043_FOURFSK2NB$0$0 == 0x514e
                           00514E  3170 _AX5043_FOURFSK2NB	=	0x514e
                           00515E  3171 G$AX5043_FOURFSK3NB$0$0 == 0x515e
                           00515E  3172 _AX5043_FOURFSK3NB	=	0x515e
                           00512D  3173 G$AX5043_FREQDEV00NB$0$0 == 0x512d
                           00512D  3174 _AX5043_FREQDEV00NB	=	0x512d
                           00513D  3175 G$AX5043_FREQDEV01NB$0$0 == 0x513d
                           00513D  3176 _AX5043_FREQDEV01NB	=	0x513d
                           00514D  3177 G$AX5043_FREQDEV02NB$0$0 == 0x514d
                           00514D  3178 _AX5043_FREQDEV02NB	=	0x514d
                           00515D  3179 G$AX5043_FREQDEV03NB$0$0 == 0x515d
                           00515D  3180 _AX5043_FREQDEV03NB	=	0x515d
                           00512C  3181 G$AX5043_FREQDEV10NB$0$0 == 0x512c
                           00512C  3182 _AX5043_FREQDEV10NB	=	0x512c
                           00513C  3183 G$AX5043_FREQDEV11NB$0$0 == 0x513c
                           00513C  3184 _AX5043_FREQDEV11NB	=	0x513c
                           00514C  3185 G$AX5043_FREQDEV12NB$0$0 == 0x514c
                           00514C  3186 _AX5043_FREQDEV12NB	=	0x514c
                           00515C  3187 G$AX5043_FREQDEV13NB$0$0 == 0x515c
                           00515C  3188 _AX5043_FREQDEV13NB	=	0x515c
                           005127  3189 G$AX5043_FREQUENCYGAINA0NB$0$0 == 0x5127
                           005127  3190 _AX5043_FREQUENCYGAINA0NB	=	0x5127
                           005137  3191 G$AX5043_FREQUENCYGAINA1NB$0$0 == 0x5137
                           005137  3192 _AX5043_FREQUENCYGAINA1NB	=	0x5137
                           005147  3193 G$AX5043_FREQUENCYGAINA2NB$0$0 == 0x5147
                           005147  3194 _AX5043_FREQUENCYGAINA2NB	=	0x5147
                           005157  3195 G$AX5043_FREQUENCYGAINA3NB$0$0 == 0x5157
                           005157  3196 _AX5043_FREQUENCYGAINA3NB	=	0x5157
                           005128  3197 G$AX5043_FREQUENCYGAINB0NB$0$0 == 0x5128
                           005128  3198 _AX5043_FREQUENCYGAINB0NB	=	0x5128
                           005138  3199 G$AX5043_FREQUENCYGAINB1NB$0$0 == 0x5138
                           005138  3200 _AX5043_FREQUENCYGAINB1NB	=	0x5138
                           005148  3201 G$AX5043_FREQUENCYGAINB2NB$0$0 == 0x5148
                           005148  3202 _AX5043_FREQUENCYGAINB2NB	=	0x5148
                           005158  3203 G$AX5043_FREQUENCYGAINB3NB$0$0 == 0x5158
                           005158  3204 _AX5043_FREQUENCYGAINB3NB	=	0x5158
                           005129  3205 G$AX5043_FREQUENCYGAINC0NB$0$0 == 0x5129
                           005129  3206 _AX5043_FREQUENCYGAINC0NB	=	0x5129
                           005139  3207 G$AX5043_FREQUENCYGAINC1NB$0$0 == 0x5139
                           005139  3208 _AX5043_FREQUENCYGAINC1NB	=	0x5139
                           005149  3209 G$AX5043_FREQUENCYGAINC2NB$0$0 == 0x5149
                           005149  3210 _AX5043_FREQUENCYGAINC2NB	=	0x5149
                           005159  3211 G$AX5043_FREQUENCYGAINC3NB$0$0 == 0x5159
                           005159  3212 _AX5043_FREQUENCYGAINC3NB	=	0x5159
                           00512A  3213 G$AX5043_FREQUENCYGAIND0NB$0$0 == 0x512a
                           00512A  3214 _AX5043_FREQUENCYGAIND0NB	=	0x512a
                           00513A  3215 G$AX5043_FREQUENCYGAIND1NB$0$0 == 0x513a
                           00513A  3216 _AX5043_FREQUENCYGAIND1NB	=	0x513a
                           00514A  3217 G$AX5043_FREQUENCYGAIND2NB$0$0 == 0x514a
                           00514A  3218 _AX5043_FREQUENCYGAIND2NB	=	0x514a
                           00515A  3219 G$AX5043_FREQUENCYGAIND3NB$0$0 == 0x515a
                           00515A  3220 _AX5043_FREQUENCYGAIND3NB	=	0x515a
                           005116  3221 G$AX5043_FREQUENCYLEAKNB$0$0 == 0x5116
                           005116  3222 _AX5043_FREQUENCYLEAKNB	=	0x5116
                           005126  3223 G$AX5043_PHASEGAIN0NB$0$0 == 0x5126
                           005126  3224 _AX5043_PHASEGAIN0NB	=	0x5126
                           005136  3225 G$AX5043_PHASEGAIN1NB$0$0 == 0x5136
                           005136  3226 _AX5043_PHASEGAIN1NB	=	0x5136
                           005146  3227 G$AX5043_PHASEGAIN2NB$0$0 == 0x5146
                           005146  3228 _AX5043_PHASEGAIN2NB	=	0x5146
                           005156  3229 G$AX5043_PHASEGAIN3NB$0$0 == 0x5156
                           005156  3230 _AX5043_PHASEGAIN3NB	=	0x5156
                           005207  3231 G$AX5043_PKTADDR0NB$0$0 == 0x5207
                           005207  3232 _AX5043_PKTADDR0NB	=	0x5207
                           005206  3233 G$AX5043_PKTADDR1NB$0$0 == 0x5206
                           005206  3234 _AX5043_PKTADDR1NB	=	0x5206
                           005205  3235 G$AX5043_PKTADDR2NB$0$0 == 0x5205
                           005205  3236 _AX5043_PKTADDR2NB	=	0x5205
                           005204  3237 G$AX5043_PKTADDR3NB$0$0 == 0x5204
                           005204  3238 _AX5043_PKTADDR3NB	=	0x5204
                           005200  3239 G$AX5043_PKTADDRCFGNB$0$0 == 0x5200
                           005200  3240 _AX5043_PKTADDRCFGNB	=	0x5200
                           00520B  3241 G$AX5043_PKTADDRMASK0NB$0$0 == 0x520b
                           00520B  3242 _AX5043_PKTADDRMASK0NB	=	0x520b
                           00520A  3243 G$AX5043_PKTADDRMASK1NB$0$0 == 0x520a
                           00520A  3244 _AX5043_PKTADDRMASK1NB	=	0x520a
                           005209  3245 G$AX5043_PKTADDRMASK2NB$0$0 == 0x5209
                           005209  3246 _AX5043_PKTADDRMASK2NB	=	0x5209
                           005208  3247 G$AX5043_PKTADDRMASK3NB$0$0 == 0x5208
                           005208  3248 _AX5043_PKTADDRMASK3NB	=	0x5208
                           005201  3249 G$AX5043_PKTLENCFGNB$0$0 == 0x5201
                           005201  3250 _AX5043_PKTLENCFGNB	=	0x5201
                           005202  3251 G$AX5043_PKTLENOFFSETNB$0$0 == 0x5202
                           005202  3252 _AX5043_PKTLENOFFSETNB	=	0x5202
                           005203  3253 G$AX5043_PKTMAXLENNB$0$0 == 0x5203
                           005203  3254 _AX5043_PKTMAXLENNB	=	0x5203
                           005118  3255 G$AX5043_RXPARAMCURSETNB$0$0 == 0x5118
                           005118  3256 _AX5043_RXPARAMCURSETNB	=	0x5118
                           005117  3257 G$AX5043_RXPARAMSETSNB$0$0 == 0x5117
                           005117  3258 _AX5043_RXPARAMSETSNB	=	0x5117
                           005124  3259 G$AX5043_TIMEGAIN0NB$0$0 == 0x5124
                           005124  3260 _AX5043_TIMEGAIN0NB	=	0x5124
                           005134  3261 G$AX5043_TIMEGAIN1NB$0$0 == 0x5134
                           005134  3262 _AX5043_TIMEGAIN1NB	=	0x5134
                           005144  3263 G$AX5043_TIMEGAIN2NB$0$0 == 0x5144
                           005144  3264 _AX5043_TIMEGAIN2NB	=	0x5144
                           005154  3265 G$AX5043_TIMEGAIN3NB$0$0 == 0x5154
                           005154  3266 _AX5043_TIMEGAIN3NB	=	0x5154
                           00FC06  3267 Fmain$flash_deviceid$0$0 == 0xfc06
                           00FC06  3268 _flash_deviceid	=	0xfc06
                           00FC00  3269 Fmain$flash_calsector$0$0 == 0xfc00
                           00FC00  3270 _flash_calsector	=	0xfc00
                           004F00  3271 G$AX5043_0xF00$0$0 == 0x4f00
                           004F00  3272 _AX5043_0xF00	=	0x4f00
                           004F0C  3273 G$AX5043_0xF0C$0$0 == 0x4f0c
                           004F0C  3274 _AX5043_0xF0C	=	0x4f0c
                           004F10  3275 G$AX5043_0xF10$0$0 == 0x4f10
                           004F10  3276 _AX5043_0xF10	=	0x4f10
                           004F11  3277 G$AX5043_0xF11$0$0 == 0x4f11
                           004F11  3278 _AX5043_0xF11	=	0x4f11
                           004F18  3279 G$AX5043_0xF18$0$0 == 0x4f18
                           004F18  3280 _AX5043_0xF18	=	0x4f18
                           004F1C  3281 G$AX5043_0xF1C$0$0 == 0x4f1c
                           004F1C  3282 _AX5043_0xF1C	=	0x4f1c
                           004F21  3283 G$AX5043_0xF21$0$0 == 0x4f21
                           004F21  3284 _AX5043_0xF21	=	0x4f21
                           004F22  3285 G$AX5043_0xF22$0$0 == 0x4f22
                           004F22  3286 _AX5043_0xF22	=	0x4f22
                           004F23  3287 G$AX5043_0xF23$0$0 == 0x4f23
                           004F23  3288 _AX5043_0xF23	=	0x4f23
                           004F26  3289 G$AX5043_0xF26$0$0 == 0x4f26
                           004F26  3290 _AX5043_0xF26	=	0x4f26
                           004F30  3291 G$AX5043_0xF30$0$0 == 0x4f30
                           004F30  3292 _AX5043_0xF30	=	0x4f30
                           004F31  3293 G$AX5043_0xF31$0$0 == 0x4f31
                           004F31  3294 _AX5043_0xF31	=	0x4f31
                           004F32  3295 G$AX5043_0xF32$0$0 == 0x4f32
                           004F32  3296 _AX5043_0xF32	=	0x4f32
                           004F33  3297 G$AX5043_0xF33$0$0 == 0x4f33
                           004F33  3298 _AX5043_0xF33	=	0x4f33
                           004F34  3299 G$AX5043_0xF34$0$0 == 0x4f34
                           004F34  3300 _AX5043_0xF34	=	0x4f34
                           004F35  3301 G$AX5043_0xF35$0$0 == 0x4f35
                           004F35  3302 _AX5043_0xF35	=	0x4f35
                           004F44  3303 G$AX5043_0xF44$0$0 == 0x4f44
                           004F44  3304 _AX5043_0xF44	=	0x4f44
                           004F0D  3305 G$AX5043_REF$0$0 == 0x4f0d
                           004F0D  3306 _AX5043_REF	=	0x4f0d
                           004F08  3307 G$AX5043_POWCTRL1$0$0 == 0x4f08
                           004F08  3308 _AX5043_POWCTRL1	=	0x4f08
                           004F5F  3309 G$AX5043_MODCFGP$0$0 == 0x4f5f
                           004F5F  3310 _AX5043_MODCFGP	=	0x4f5f
                           004F10  3311 G$AX5043_XTALOSC$0$0 == 0x4f10
                           004F10  3312 _AX5043_XTALOSC	=	0x4f10
                           004F11  3313 G$AX5043_XTALAMPL$0$0 == 0x4f11
                           004F11  3314 _AX5043_XTALAMPL	=	0x4f11
                           000000  3315 G$txdata$0$0==.
      00029A                       3316 _txdata::
      00029A                       3317 	.ds 8
                                   3318 ;--------------------------------------------------------
                                   3319 ; absolute external ram data
                                   3320 ;--------------------------------------------------------
                                   3321 	.area XABS    (ABS,XDATA)
                                   3322 ;--------------------------------------------------------
                                   3323 ; external initialized ram data
                                   3324 ;--------------------------------------------------------
                                   3325 	.area XISEG   (XDATA)
                                   3326 	.area HOME    (CODE)
                                   3327 	.area GSINIT0 (CODE)
                                   3328 	.area GSINIT1 (CODE)
                                   3329 	.area GSINIT2 (CODE)
                                   3330 	.area GSINIT3 (CODE)
                                   3331 	.area GSINIT4 (CODE)
                                   3332 	.area GSINIT5 (CODE)
                                   3333 	.area GSINIT  (CODE)
                                   3334 	.area GSFINAL (CODE)
                                   3335 	.area CSEG    (CODE)
                                   3336 ;--------------------------------------------------------
                                   3337 ; interrupt vector 
                                   3338 ;--------------------------------------------------------
                                   3339 	.area HOME    (CODE)
      000000                       3340 __interrupt_vect:
      000000 02 02 DA         [24] 3341 	ljmp	__sdcc_gsinit_startup
      000003 32               [24] 3342 	reti
      000004                       3343 	.ds	7
      00000B 02 00 B1         [24] 3344 	ljmp	_wtimer_irq
      00000E                       3345 	.ds	5
      000013 32               [24] 3346 	reti
      000014                       3347 	.ds	7
      00001B 32               [24] 3348 	reti
      00001C                       3349 	.ds	7
      000023 02 12 EB         [24] 3350 	ljmp	_axradio_isr
      000026                       3351 	.ds	5
      00002B 32               [24] 3352 	reti
      00002C                       3353 	.ds	7
      000033 02 3D 2A         [24] 3354 	ljmp	_pwrmgmt_irq
      000036                       3355 	.ds	5
      00003B 32               [24] 3356 	reti
      00003C                       3357 	.ds	7
      000043 32               [24] 3358 	reti
      000044                       3359 	.ds	7
      00004B 32               [24] 3360 	reti
      00004C                       3361 	.ds	7
      000053 32               [24] 3362 	reti
      000054                       3363 	.ds	7
      00005B 32               [24] 3364 	reti
      00005C                       3365 	.ds	7
      000063 32               [24] 3366 	reti
      000064                       3367 	.ds	7
      00006B 32               [24] 3368 	reti
      00006C                       3369 	.ds	7
      000073 32               [24] 3370 	reti
      000074                       3371 	.ds	7
      00007B 32               [24] 3372 	reti
      00007C                       3373 	.ds	7
      000083 32               [24] 3374 	reti
      000084                       3375 	.ds	7
      00008B 32               [24] 3376 	reti
      00008C                       3377 	.ds	7
      000093 32               [24] 3378 	reti
      000094                       3379 	.ds	7
      00009B 32               [24] 3380 	reti
      00009C                       3381 	.ds	7
      0000A3 32               [24] 3382 	reti
      0000A4                       3383 	.ds	7
      0000AB 02 02 6C         [24] 3384 	ljmp	_dbglink_irq
                                   3385 ;--------------------------------------------------------
                                   3386 ; global & static initialisations
                                   3387 ;--------------------------------------------------------
                                   3388 	.area HOME    (CODE)
                                   3389 	.area GSINIT  (CODE)
                                   3390 	.area GSFINAL (CODE)
                                   3391 	.area GSINIT  (CODE)
                                   3392 	.globl __sdcc_gsinit_startup
                                   3393 	.globl __sdcc_program_startup
                                   3394 	.globl __start__stack
                                   3395 	.globl __mcs51_genXINIT
                                   3396 	.globl __mcs51_genXRAMCLEAR
                                   3397 	.globl __mcs51_genRAMCLEAR
                           000000  3398 	C$main.c$82$1$329 ==.
                                   3399 ;	main.c:82: uint8_t __data coldstart = 1; // caution: initialization with 1 is necessary! Variables are initialized upon _sdcc_external_startup returning 0 -> the coldstart value returned from _sdcc_external startup does not survive in the coldstart case
      000353 75 22 01         [24] 3400 	mov	_coldstart,#0x01
                                   3401 	.area GSFINAL (CODE)
      000356 02 00 AE         [24] 3402 	ljmp	__sdcc_program_startup
                                   3403 ;--------------------------------------------------------
                                   3404 ; Home
                                   3405 ;--------------------------------------------------------
                                   3406 	.area HOME    (CODE)
                                   3407 	.area HOME    (CODE)
      0000AE                       3408 __sdcc_program_startup:
      0000AE 02 41 7D         [24] 3409 	ljmp	_main
                                   3410 ;	return from main will return to caller
                                   3411 ;--------------------------------------------------------
                                   3412 ; code
                                   3413 ;--------------------------------------------------------
                                   3414 	.area CSEG    (CODE)
                                   3415 ;------------------------------------------------------------
                                   3416 ;Allocation info for local variables in function 'pwrmgmt_irq'
                                   3417 ;------------------------------------------------------------
                                   3418 ;pc                        Allocated to registers r7 
                                   3419 ;------------------------------------------------------------
                           000000  3420 	Fmain$pwrmgmt_irq$0$0 ==.
                           000000  3421 	C$main.c$123$0$0 ==.
                                   3422 ;	main.c:123: static void pwrmgmt_irq(void) __interrupt(INT_POWERMGMT)
                                   3423 ;	-----------------------------------------
                                   3424 ;	 function pwrmgmt_irq
                                   3425 ;	-----------------------------------------
      003D2A                       3426 _pwrmgmt_irq:
                           000007  3427 	ar7 = 0x07
                           000006  3428 	ar6 = 0x06
                           000005  3429 	ar5 = 0x05
                           000004  3430 	ar4 = 0x04
                           000003  3431 	ar3 = 0x03
                           000002  3432 	ar2 = 0x02
                           000001  3433 	ar1 = 0x01
                           000000  3434 	ar0 = 0x00
      003D2A C0 E0            [24] 3435 	push	acc
      003D2C C0 82            [24] 3436 	push	dpl
      003D2E C0 83            [24] 3437 	push	dph
      003D30 C0 07            [24] 3438 	push	ar7
      003D32 C0 D0            [24] 3439 	push	psw
      003D34 75 D0 00         [24] 3440 	mov	psw,#0x00
                           00000D  3441 	C$main.c$125$1$0 ==.
                                   3442 ;	main.c:125: uint8_t pc = PCON;
                           00000D  3443 	C$main.c$126$1$228 ==.
                                   3444 ;	main.c:126: if (!(pc & 0x80))
      003D37 E5 87            [12] 3445 	mov	a,_PCON
      003D39 FF               [12] 3446 	mov	r7,a
      003D3A 20 E7 02         [24] 3447 	jb	acc.7,00102$
                           000013  3448 	C$main.c$127$1$228 ==.
                                   3449 ;	main.c:127: return;
      003D3D 80 10            [24] 3450 	sjmp	00106$
      003D3F                       3451 00102$:
                           000015  3452 	C$main.c$128$1$228 ==.
                                   3453 ;	main.c:128: GPIOENABLE = 0;
      003D3F 90 70 0C         [24] 3454 	mov	dptr,#_GPIOENABLE
      003D42 E4               [12] 3455 	clr	a
      003D43 F0               [24] 3456 	movx	@dptr,a
                           00001A  3457 	C$main.c$129$1$228 ==.
                                   3458 ;	main.c:129: IE = EIE = E2IE = 0;
                                   3459 ;	1-genFromRTrack replaced	mov	_E2IE,#0x00
      003D44 F5 A0            [12] 3460 	mov	_E2IE,a
                                   3461 ;	1-genFromRTrack replaced	mov	_EIE,#0x00
      003D46 F5 98            [12] 3462 	mov	_EIE,a
                                   3463 ;	1-genFromRTrack replaced	mov	_IE,#0x00
      003D48 F5 A8            [12] 3464 	mov	_IE,a
      003D4A                       3465 00104$:
                           000020  3466 	C$main.c$131$1$228 ==.
                                   3467 ;	main.c:131: PCON |= 0x01;
      003D4A 43 87 01         [24] 3468 	orl	_PCON,#0x01
      003D4D 80 FB            [24] 3469 	sjmp	00104$
      003D4F                       3470 00106$:
      003D4F D0 D0            [24] 3471 	pop	psw
      003D51 D0 07            [24] 3472 	pop	ar7
      003D53 D0 83            [24] 3473 	pop	dph
      003D55 D0 82            [24] 3474 	pop	dpl
      003D57 D0 E0            [24] 3475 	pop	acc
                           00002F  3476 	C$main.c$132$1$228 ==.
                           00002F  3477 	XFmain$pwrmgmt_irq$0$0 ==.
      003D59 32               [24] 3478 	reti
                                   3479 ;	eliminated unneeded push/pop b
                                   3480 ;------------------------------------------------------------
                                   3481 ;Allocation info for local variables in function 'correct_ber'
                                   3482 ;------------------------------------------------------------
                                   3483 ;x                         Allocated to registers 
                                   3484 ;------------------------------------------------------------
                           000030  3485 	Fmain$correct_ber$0$0 ==.
                           000030  3486 	C$main.c$135$1$228 ==.
                                   3487 ;	main.c:135: static void correct_ber(void)
                                   3488 ;	-----------------------------------------
                                   3489 ;	 function correct_ber
                                   3490 ;	-----------------------------------------
      003D5A                       3491 _correct_ber:
                           000030  3492 	C$main.c$153$1$230 ==.
                                   3493 ;	main.c:153: }
                           000030  3494 	C$main.c$154$1$230 ==.
                           000030  3495 	XFmain$correct_ber$0$0 ==.
      003D5A 22               [24] 3496 	ret
                                   3497 ;------------------------------------------------------------
                                   3498 ;Allocation info for local variables in function 'process_ber'
                                   3499 ;------------------------------------------------------------
                                   3500 ;st                        Allocated to registers r6 r7 
                                   3501 ;fourfsk                   Allocated with name '_process_ber_fourfsk_1_234'
                                   3502 ;i                         Allocated to registers r3 
                                   3503 ;p                         Allocated to registers r6 r7 
                                   3504 ;databyte                  Allocated with name '_process_ber_databyte_6_240'
                                   3505 ;databyte                  Allocated to registers r4 
                                   3506 ;databyte                  Allocated to registers 
                                   3507 ;databyte                  Allocated to registers 
                                   3508 ;databyte                  Allocated to registers 
                                   3509 ;sloc0                     Allocated with name '_process_ber_sloc0_1_0'
                                   3510 ;sloc1                     Allocated with name '_process_ber_sloc1_1_0'
                                   3511 ;------------------------------------------------------------
                           000031  3512 	Fmain$process_ber$0$0 ==.
                           000031  3513 	C$main.c$157$1$230 ==.
                                   3514 ;	main.c:157: static void process_ber(struct axradio_status __xdata *st)
                                   3515 ;	-----------------------------------------
                                   3516 ;	 function process_ber
                                   3517 ;	-----------------------------------------
      003D5B                       3518 _process_ber:
      003D5B AE 82            [24] 3519 	mov	r6,dpl
      003D5D AF 83            [24] 3520 	mov	r7,dph
                           000035  3521 	C$main.c$159$1$234 ==.
                                   3522 ;	main.c:159: uint8_t fourfsk = (AX5043_MODULATION & 0x0F) == 9;
      003D5F 90 40 10         [24] 3523 	mov	dptr,#_AX5043_MODULATION
      003D62 E0               [24] 3524 	movx	a,@dptr
      003D63 FD               [12] 3525 	mov	r5,a
      003D64 53 05 0F         [24] 3526 	anl	ar5,#0x0f
      003D67 E4               [12] 3527 	clr	a
      003D68 BD 09 01         [24] 3528 	cjne	r5,#0x09,00176$
      003D6B 04               [12] 3529 	inc	a
      003D6C                       3530 00176$:
      003D6C F5 34            [12] 3531 	mov	_process_ber_fourfsk_1_234,a
                           000044  3532 	C$main.c$161$2$235 ==.
                                   3533 ;	main.c:161: uint8_t i = st->u.rx.pktlen;
      003D6E 74 06            [12] 3534 	mov	a,#0x06
      003D70 2E               [12] 3535 	add	a,r6
      003D71 FE               [12] 3536 	mov	r6,a
      003D72 E4               [12] 3537 	clr	a
      003D73 3F               [12] 3538 	addc	a,r7
      003D74 FF               [12] 3539 	mov	r7,a
      003D75 74 16            [12] 3540 	mov	a,#0x16
      003D77 2E               [12] 3541 	add	a,r6
      003D78 F5 82            [12] 3542 	mov	dpl,a
      003D7A E4               [12] 3543 	clr	a
      003D7B 3F               [12] 3544 	addc	a,r7
      003D7C F5 83            [12] 3545 	mov	dph,a
      003D7E E0               [24] 3546 	movx	a,@dptr
      003D7F FB               [12] 3547 	mov	r3,a
      003D80 A3               [24] 3548 	inc	dptr
      003D81 E0               [24] 3549 	movx	a,@dptr
                           000058  3550 	C$main.c$162$2$235 ==.
                                   3551 ;	main.c:162: bytes -= i;
      003D82 8B 00            [24] 3552 	mov	ar0,r3
      003D84 E4               [12] 3553 	clr	a
      003D85 F9               [12] 3554 	mov	r1,a
      003D86 FA               [12] 3555 	mov	r2,a
      003D87 FC               [12] 3556 	mov	r4,a
      003D88 E5 27            [12] 3557 	mov	a,_bytes
      003D8A C3               [12] 3558 	clr	c
      003D8B 98               [12] 3559 	subb	a,r0
      003D8C F5 27            [12] 3560 	mov	_bytes,a
      003D8E E5 28            [12] 3561 	mov	a,(_bytes + 1)
      003D90 99               [12] 3562 	subb	a,r1
      003D91 F5 28            [12] 3563 	mov	(_bytes + 1),a
      003D93 E5 29            [12] 3564 	mov	a,(_bytes + 2)
      003D95 9A               [12] 3565 	subb	a,r2
      003D96 F5 29            [12] 3566 	mov	(_bytes + 2),a
      003D98 E5 2A            [12] 3567 	mov	a,(_bytes + 3)
      003D9A 9C               [12] 3568 	subb	a,r4
      003D9B F5 2A            [12] 3569 	mov	(_bytes + 3),a
                           000073  3570 	C$main.c$163$2$235 ==.
                                   3571 ;	main.c:163: acquire_agc = (0 > (int32_t)bytes);
      003D9D A8 27            [24] 3572 	mov	r0,_bytes
      003D9F A9 28            [24] 3573 	mov	r1,(_bytes + 1)
      003DA1 AA 29            [24] 3574 	mov	r2,(_bytes + 2)
      003DA3 E5 2A            [12] 3575 	mov	a,(_bytes + 3)
      003DA5 FC               [12] 3576 	mov	r4,a
      003DA6 33               [12] 3577 	rlc	a
      003DA7 E4               [12] 3578 	clr	a
      003DA8 33               [12] 3579 	rlc	a
                           00007F  3580 	C$main.c$164$2$235 ==.
                                   3581 ;	main.c:164: if (acquire_agc) {
      003DA9 F5 33            [12] 3582 	mov	_acquire_agc,a
      003DAB 60 0E            [24] 3583 	jz	00102$
                           000083  3584 	C$main.c$165$3$236 ==.
                                   3585 ;	main.c:165: i += (uint8_t)bytes;
      003DAD E5 27            [12] 3586 	mov	a,_bytes
      003DAF FC               [12] 3587 	mov	r4,a
      003DB0 2B               [12] 3588 	add	a,r3
      003DB1 FB               [12] 3589 	mov	r3,a
                           000088  3590 	C$main.c$166$3$236 ==.
                                   3591 ;	main.c:166: bytes = 0;
      003DB2 E4               [12] 3592 	clr	a
      003DB3 F5 27            [12] 3593 	mov	_bytes,a
      003DB5 F5 28            [12] 3594 	mov	(_bytes + 1),a
      003DB7 F5 29            [12] 3595 	mov	(_bytes + 2),a
      003DB9 F5 2A            [12] 3596 	mov	(_bytes + 3),a
      003DBB                       3597 00102$:
                           000091  3598 	C$main.c$168$2$235 ==.
                                   3599 ;	main.c:168: if (i) {
      003DBB EB               [12] 3600 	mov	a,r3
      003DBC 70 03            [24] 3601 	jnz	00179$
      003DBE 02 3E 6B         [24] 3602 	ljmp	00126$
      003DC1                       3603 00179$:
                           000097  3604 	C$main.c$169$3$237 ==.
                                   3605 ;	main.c:169: const uint8_t __xdata *p = st->u.rx.pktdata;
      003DC1 74 14            [12] 3606 	mov	a,#0x14
      003DC3 2E               [12] 3607 	add	a,r6
      003DC4 F5 82            [12] 3608 	mov	dpl,a
      003DC6 E4               [12] 3609 	clr	a
      003DC7 3F               [12] 3610 	addc	a,r7
      003DC8 F5 83            [12] 3611 	mov	dph,a
      003DCA E0               [24] 3612 	movx	a,@dptr
      003DCB FE               [12] 3613 	mov	r6,a
      003DCC A3               [24] 3614 	inc	dptr
      003DCD E0               [24] 3615 	movx	a,@dptr
      003DCE FF               [12] 3616 	mov	r7,a
                           0000A5  3617 	C$main.c$172$4$238 ==.
                                   3618 ;	main.c:172: if (fourfsk) {
      003DCF E5 34            [12] 3619 	mov	a,_process_ber_fourfsk_1_234
      003DD1 60 65            [24] 3620 	jz	00143$
                           0000A9  3621 	C$main.c$173$1$234 ==.
                                   3622 ;	main.c:173: do {
      003DD3 8E 37            [24] 3623 	mov	_process_ber_sloc1_1_0,r6
      003DD5 8F 38            [24] 3624 	mov	(_process_ber_sloc1_1_0 + 1),r7
      003DD7 8B 36            [24] 3625 	mov	_process_ber_sloc0_1_0,r3
      003DD9                       3626 00104$:
                           0000AF  3627 	C$main.c$174$6$240 ==.
                                   3628 ;	main.c:174: uint8_t databyte = *p++;
      003DD9 85 37 82         [24] 3629 	mov	dpl,_process_ber_sloc1_1_0
      003DDC 85 38 83         [24] 3630 	mov	dph,(_process_ber_sloc1_1_0 + 1)
      003DDF E0               [24] 3631 	movx	a,@dptr
      003DE0 F5 35            [12] 3632 	mov	_process_ber_databyte_6_240,a
      003DE2 A3               [24] 3633 	inc	dptr
      003DE3 85 82 37         [24] 3634 	mov	_process_ber_sloc1_1_0,dpl
      003DE6 85 83 38         [24] 3635 	mov	(_process_ber_sloc1_1_0 + 1),dph
                           0000BF  3636 	C$main.c$176$6$240 ==.
                                   3637 ;	main.c:176: errors2 += hweight8(databyte ^ 0x87);
      003DE9 74 87            [12] 3638 	mov	a,#0x87
      003DEB 65 35            [12] 3639 	xrl	a,_process_ber_databyte_6_240
      003DED F5 82            [12] 3640 	mov	dpl,a
      003DEF 12 45 9E         [24] 3641 	lcall	_hweight8
      003DF2 AD 82            [24] 3642 	mov	r5,dpl
      003DF4 8D 00            [24] 3643 	mov	ar0,r5
      003DF6 E4               [12] 3644 	clr	a
      003DF7 F9               [12] 3645 	mov	r1,a
      003DF8 FC               [12] 3646 	mov	r4,a
      003DF9 FD               [12] 3647 	mov	r5,a
      003DFA E8               [12] 3648 	mov	a,r0
      003DFB 25 2F            [12] 3649 	add	a,_errors2
      003DFD F5 2F            [12] 3650 	mov	_errors2,a
      003DFF E9               [12] 3651 	mov	a,r1
      003E00 35 30            [12] 3652 	addc	a,(_errors2 + 1)
      003E02 F5 30            [12] 3653 	mov	(_errors2 + 1),a
      003E04 EC               [12] 3654 	mov	a,r4
      003E05 35 31            [12] 3655 	addc	a,(_errors2 + 2)
      003E07 F5 31            [12] 3656 	mov	(_errors2 + 2),a
      003E09 ED               [12] 3657 	mov	a,r5
      003E0A 35 32            [12] 3658 	addc	a,(_errors2 + 3)
      003E0C F5 32            [12] 3659 	mov	(_errors2 + 3),a
                           0000E4  3660 	C$main.c$177$6$240 ==.
                                   3661 ;	main.c:177: errors += hweight8(databyte ^ 0xe1);
      003E0E 74 E1            [12] 3662 	mov	a,#0xe1
      003E10 65 35            [12] 3663 	xrl	a,_process_ber_databyte_6_240
      003E12 F5 82            [12] 3664 	mov	dpl,a
      003E14 12 45 9E         [24] 3665 	lcall	_hweight8
      003E17 AD 82            [24] 3666 	mov	r5,dpl
      003E19 8D 01            [24] 3667 	mov	ar1,r5
      003E1B E4               [12] 3668 	clr	a
      003E1C FA               [12] 3669 	mov	r2,a
      003E1D FC               [12] 3670 	mov	r4,a
      003E1E FD               [12] 3671 	mov	r5,a
      003E1F E9               [12] 3672 	mov	a,r1
      003E20 25 2B            [12] 3673 	add	a,_errors
      003E22 F5 2B            [12] 3674 	mov	_errors,a
      003E24 EA               [12] 3675 	mov	a,r2
      003E25 35 2C            [12] 3676 	addc	a,(_errors + 1)
      003E27 F5 2C            [12] 3677 	mov	(_errors + 1),a
      003E29 EC               [12] 3678 	mov	a,r4
      003E2A 35 2D            [12] 3679 	addc	a,(_errors + 2)
      003E2C F5 2D            [12] 3680 	mov	(_errors + 2),a
      003E2E ED               [12] 3681 	mov	a,r5
      003E2F 35 2E            [12] 3682 	addc	a,(_errors + 3)
      003E31 F5 2E            [12] 3683 	mov	(_errors + 3),a
                           000109  3684 	C$main.c$178$5$239 ==.
                                   3685 ;	main.c:178: } while (--i);
      003E33 D5 36 A3         [24] 3686 	djnz	_process_ber_sloc0_1_0,00104$
                           00010C  3687 	C$main.c$179$5$239 ==.
                                   3688 ;	main.c:179: break;
                           00010C  3689 	C$main.c$181$1$234 ==.
                                   3690 ;	main.c:181: do {
      003E36 80 33            [24] 3691 	sjmp	00126$
      003E38                       3692 00143$:
      003E38 8B 05            [24] 3693 	mov	ar5,r3
      003E3A                       3694 00109$:
                           000110  3695 	C$main.c$182$5$241 ==.
                                   3696 ;	main.c:182: uint8_t databyte = *p++;
      003E3A 8E 82            [24] 3697 	mov	dpl,r6
      003E3C 8F 83            [24] 3698 	mov	dph,r7
      003E3E E0               [24] 3699 	movx	a,@dptr
      003E3F FC               [12] 3700 	mov	r4,a
      003E40 A3               [24] 3701 	inc	dptr
      003E41 AE 82            [24] 3702 	mov	r6,dpl
      003E43 AF 83            [24] 3703 	mov	r7,dph
                           00011B  3704 	C$main.c$183$5$241 ==.
                                   3705 ;	main.c:183: errors += hweight8(databyte ^ 0x55);
      003E45 74 55            [12] 3706 	mov	a,#0x55
      003E47 6C               [12] 3707 	xrl	a,r4
      003E48 F5 82            [12] 3708 	mov	dpl,a
      003E4A 12 45 9E         [24] 3709 	lcall	_hweight8
      003E4D AC 82            [24] 3710 	mov	r4,dpl
      003E4F 8C 01            [24] 3711 	mov	ar1,r4
      003E51 E4               [12] 3712 	clr	a
      003E52 FA               [12] 3713 	mov	r2,a
      003E53 FB               [12] 3714 	mov	r3,a
      003E54 FC               [12] 3715 	mov	r4,a
      003E55 E9               [12] 3716 	mov	a,r1
      003E56 25 2B            [12] 3717 	add	a,_errors
      003E58 F5 2B            [12] 3718 	mov	_errors,a
      003E5A EA               [12] 3719 	mov	a,r2
      003E5B 35 2C            [12] 3720 	addc	a,(_errors + 1)
      003E5D F5 2C            [12] 3721 	mov	(_errors + 1),a
      003E5F EB               [12] 3722 	mov	a,r3
      003E60 35 2D            [12] 3723 	addc	a,(_errors + 2)
      003E62 F5 2D            [12] 3724 	mov	(_errors + 2),a
      003E64 EC               [12] 3725 	mov	a,r4
      003E65 35 2E            [12] 3726 	addc	a,(_errors + 3)
      003E67 F5 2E            [12] 3727 	mov	(_errors + 3),a
                           00013F  3728 	C$main.c$184$4$238 ==.
                                   3729 ;	main.c:184: } while (--i);
      003E69 DD CF            [24] 3730 	djnz	r5,00109$
                           000141  3731 	C$main.c$218$2$235 ==.
                                   3732 ;	main.c:218: }
      003E6B                       3733 00126$:
                           000141  3734 	C$main.c$221$1$234 ==.
                                   3735 ;	main.c:221: if (!acquire_agc)
      003E6B E5 33            [12] 3736 	mov	a,_acquire_agc
                           000143  3737 	C$main.c$222$1$234 ==.
                                   3738 ;	main.c:222: return;
      003E6D 60 76            [24] 3739 	jz	00137$
                           000145  3740 	C$main.c$224$1$234 ==.
                                   3741 ;	main.c:224: if (errors > (((uint32_t)NUMBYTES) << 2))
      003E6F C3               [12] 3742 	clr	c
      003E70 74 88            [12] 3743 	mov	a,#0x88
      003E72 95 2B            [12] 3744 	subb	a,_errors
      003E74 74 13            [12] 3745 	mov	a,#0x13
      003E76 95 2C            [12] 3746 	subb	a,(_errors + 1)
      003E78 E4               [12] 3747 	clr	a
      003E79 95 2D            [12] 3748 	subb	a,(_errors + 2)
      003E7B E4               [12] 3749 	clr	a
      003E7C 95 2E            [12] 3750 	subb	a,(_errors + 3)
      003E7E 50 17            [24] 3751 	jnc	00130$
                           000156  3752 	C$main.c$225$1$234 ==.
                                   3753 ;	main.c:225: errors = (((uint32_t)NUMBYTES) << 3) - errors;
      003E80 74 10            [12] 3754 	mov	a,#0x10
      003E82 C3               [12] 3755 	clr	c
      003E83 95 2B            [12] 3756 	subb	a,_errors
      003E85 F5 2B            [12] 3757 	mov	_errors,a
      003E87 74 27            [12] 3758 	mov	a,#0x27
      003E89 95 2C            [12] 3759 	subb	a,(_errors + 1)
      003E8B F5 2C            [12] 3760 	mov	(_errors + 1),a
      003E8D E4               [12] 3761 	clr	a
      003E8E 95 2D            [12] 3762 	subb	a,(_errors + 2)
      003E90 F5 2D            [12] 3763 	mov	(_errors + 2),a
      003E92 E4               [12] 3764 	clr	a
      003E93 95 2E            [12] 3765 	subb	a,(_errors + 3)
      003E95 F5 2E            [12] 3766 	mov	(_errors + 3),a
      003E97                       3767 00130$:
                           00016D  3768 	C$main.c$226$1$234 ==.
                                   3769 ;	main.c:226: if (fourfsk) {
      003E97 E5 34            [12] 3770 	mov	a,_process_ber_fourfsk_1_234
      003E99 60 47            [24] 3771 	jz	00136$
                           000171  3772 	C$main.c$227$2$245 ==.
                                   3773 ;	main.c:227: if (errors2 > (((uint32_t)NUMBYTES) << 2))
      003E9B C3               [12] 3774 	clr	c
      003E9C 74 88            [12] 3775 	mov	a,#0x88
      003E9E 95 2F            [12] 3776 	subb	a,_errors2
      003EA0 74 13            [12] 3777 	mov	a,#0x13
      003EA2 95 30            [12] 3778 	subb	a,(_errors2 + 1)
      003EA4 E4               [12] 3779 	clr	a
      003EA5 95 31            [12] 3780 	subb	a,(_errors2 + 2)
      003EA7 E4               [12] 3781 	clr	a
      003EA8 95 32            [12] 3782 	subb	a,(_errors2 + 3)
      003EAA 50 17            [24] 3783 	jnc	00132$
                           000182  3784 	C$main.c$228$2$245 ==.
                                   3785 ;	main.c:228: errors2 = (((uint32_t)NUMBYTES) << 3) - errors2;
      003EAC 74 10            [12] 3786 	mov	a,#0x10
      003EAE C3               [12] 3787 	clr	c
      003EAF 95 2F            [12] 3788 	subb	a,_errors2
      003EB1 F5 2F            [12] 3789 	mov	_errors2,a
      003EB3 74 27            [12] 3790 	mov	a,#0x27
      003EB5 95 30            [12] 3791 	subb	a,(_errors2 + 1)
      003EB7 F5 30            [12] 3792 	mov	(_errors2 + 1),a
      003EB9 E4               [12] 3793 	clr	a
      003EBA 95 31            [12] 3794 	subb	a,(_errors2 + 2)
      003EBC F5 31            [12] 3795 	mov	(_errors2 + 2),a
      003EBE E4               [12] 3796 	clr	a
      003EBF 95 32            [12] 3797 	subb	a,(_errors2 + 3)
      003EC1 F5 32            [12] 3798 	mov	(_errors2 + 3),a
      003EC3                       3799 00132$:
                           000199  3800 	C$main.c$229$2$245 ==.
                                   3801 ;	main.c:229: if (errors2 < errors)
      003EC3 C3               [12] 3802 	clr	c
      003EC4 E5 2F            [12] 3803 	mov	a,_errors2
      003EC6 95 2B            [12] 3804 	subb	a,_errors
      003EC8 E5 30            [12] 3805 	mov	a,(_errors2 + 1)
      003ECA 95 2C            [12] 3806 	subb	a,(_errors + 1)
      003ECC E5 31            [12] 3807 	mov	a,(_errors2 + 2)
      003ECE 95 2D            [12] 3808 	subb	a,(_errors + 2)
      003ED0 E5 32            [12] 3809 	mov	a,(_errors2 + 3)
      003ED2 95 2E            [12] 3810 	subb	a,(_errors + 3)
      003ED4 50 0C            [24] 3811 	jnc	00136$
                           0001AC  3812 	C$main.c$230$2$245 ==.
                                   3813 ;	main.c:230: errors = errors2;
      003ED6 85 2F 2B         [24] 3814 	mov	_errors,_errors2
      003ED9 85 30 2C         [24] 3815 	mov	(_errors + 1),(_errors2 + 1)
      003EDC 85 31 2D         [24] 3816 	mov	(_errors + 2),(_errors2 + 2)
      003EDF 85 32 2E         [24] 3817 	mov	(_errors + 3),(_errors2 + 3)
      003EE2                       3818 00136$:
                           0001B8  3819 	C$main.c$232$1$234 ==.
                                   3820 ;	main.c:232: correct_ber();
      003EE2 12 3D 5A         [24] 3821 	lcall	_correct_ber
      003EE5                       3822 00137$:
                           0001BB  3823 	C$main.c$233$1$234 ==.
                           0001BB  3824 	XFmain$process_ber$0$0 ==.
      003EE5 22               [24] 3825 	ret
                                   3826 ;------------------------------------------------------------
                                   3827 ;Allocation info for local variables in function 'dump_pkt'
                                   3828 ;------------------------------------------------------------
                                   3829 ;st                        Allocated to registers r6 r7 
                                   3830 ;p                         Allocated to registers 
                                   3831 ;i                         Allocated to registers r6 
                                   3832 ;j                         Allocated to registers r7 
                                   3833 ;------------------------------------------------------------
                           0001BC  3834 	Fmain$dump_pkt$0$0 ==.
                           0001BC  3835 	C$main.c$235$1$234 ==.
                                   3836 ;	main.c:235: static void dump_pkt(struct axradio_status __xdata *st)
                                   3837 ;	-----------------------------------------
                                   3838 ;	 function dump_pkt
                                   3839 ;	-----------------------------------------
      003EE6                       3840 _dump_pkt:
      003EE6 AE 82            [24] 3841 	mov	r6,dpl
      003EE8 AF 83            [24] 3842 	mov	r7,dph
                           0001C0  3843 	C$main.c$238$1$247 ==.
                                   3844 ;	main.c:238: if (!(DBGLNKSTAT & 0x10))
      003EEA E5 E2            [12] 3845 	mov	a,_DBGLNKSTAT
      003EEC 20 E4 03         [24] 3846 	jb	acc.4,00102$
                           0001C5  3847 	C$main.c$239$1$247 ==.
                                   3848 ;	main.c:239: return;
      003EEF 02 3F 93         [24] 3849 	ljmp	00109$
      003EF2                       3850 00102$:
                           0001C8  3851 	C$main.c$241$2$248 ==.
                                   3852 ;	main.c:241: const uint8_t __xdata *p = st->u.rx.pktdata;
      003EF2 74 06            [12] 3853 	mov	a,#0x06
      003EF4 2E               [12] 3854 	add	a,r6
      003EF5 FE               [12] 3855 	mov	r6,a
      003EF6 E4               [12] 3856 	clr	a
      003EF7 3F               [12] 3857 	addc	a,r7
      003EF8 FF               [12] 3858 	mov	r7,a
      003EF9 74 14            [12] 3859 	mov	a,#0x14
      003EFB 2E               [12] 3860 	add	a,r6
      003EFC F5 82            [12] 3861 	mov	dpl,a
      003EFE E4               [12] 3862 	clr	a
      003EFF 3F               [12] 3863 	addc	a,r7
      003F00 F5 83            [12] 3864 	mov	dph,a
      003F02 E0               [24] 3865 	movx	a,@dptr
      003F03 FC               [12] 3866 	mov	r4,a
      003F04 A3               [24] 3867 	inc	dptr
      003F05 E0               [24] 3868 	movx	a,@dptr
      003F06 FD               [12] 3869 	mov	r5,a
                           0001DD  3870 	C$main.c$242$2$248 ==.
                                   3871 ;	main.c:242: uint8_t i = st->u.rx.pktlen, j;
      003F07 74 16            [12] 3872 	mov	a,#0x16
      003F09 2E               [12] 3873 	add	a,r6
      003F0A F5 82            [12] 3874 	mov	dpl,a
      003F0C E4               [12] 3875 	clr	a
      003F0D 3F               [12] 3876 	addc	a,r7
      003F0E F5 83            [12] 3877 	mov	dph,a
      003F10 E0               [24] 3878 	movx	a,@dptr
      003F11 FE               [12] 3879 	mov	r6,a
      003F12 A3               [24] 3880 	inc	dptr
      003F13 E0               [24] 3881 	movx	a,@dptr
                           0001EA  3882 	C$main.c$243$2$248 ==.
                                   3883 ;	main.c:243: for (j = 0; j < i; ++j) {
      003F14 7F 00            [12] 3884 	mov	r7,#0x00
      003F16                       3885 00107$:
      003F16 C3               [12] 3886 	clr	c
      003F17 EF               [12] 3887 	mov	a,r7
      003F18 9E               [12] 3888 	subb	a,r6
      003F19 50 72            [24] 3889 	jnc	00105$
                           0001F1  3890 	C$main.c$244$3$249 ==.
                                   3891 ;	main.c:244: if (!(j & 15)) {
      003F1B EF               [12] 3892 	mov	a,r7
      003F1C 54 0F            [12] 3893 	anl	a,#0x0f
      003F1E 60 02            [24] 3894 	jz	00127$
      003F20 80 32            [24] 3895 	sjmp	00104$
      003F22                       3896 00127$:
                           0001F8  3897 	C$main.c$245$4$250 ==.
                                   3898 ;	main.c:245: dbglink_tx('\n');
      003F22 75 82 0A         [24] 3899 	mov	dpl,#0x0a
      003F25 12 42 C1         [24] 3900 	lcall	_dbglink_tx
                           0001FE  3901 	C$main.c$246$4$250 ==.
                                   3902 ;	main.c:246: dbglink_writehex16(j, 4, WRNUM_PADZERO);
      003F28 8F 02            [24] 3903 	mov	ar2,r7
      003F2A 7B 00            [12] 3904 	mov	r3,#0x00
      003F2C C0 07            [24] 3905 	push	ar7
      003F2E C0 06            [24] 3906 	push	ar6
      003F30 C0 05            [24] 3907 	push	ar5
      003F32 C0 04            [24] 3908 	push	ar4
      003F34 74 08            [12] 3909 	mov	a,#0x08
      003F36 C0 E0            [24] 3910 	push	acc
      003F38 03               [12] 3911 	rr	a
      003F39 C0 E0            [24] 3912 	push	acc
      003F3B 8A 82            [24] 3913 	mov	dpl,r2
      003F3D 8B 83            [24] 3914 	mov	dph,r3
      003F3F 12 53 77         [24] 3915 	lcall	_dbglink_writehex16
      003F42 15 81            [12] 3916 	dec	sp
      003F44 15 81            [12] 3917 	dec	sp
      003F46 D0 04            [24] 3918 	pop	ar4
      003F48 D0 05            [24] 3919 	pop	ar5
      003F4A D0 06            [24] 3920 	pop	ar6
      003F4C D0 07            [24] 3921 	pop	ar7
                           000224  3922 	C$main.c$247$4$250 ==.
                                   3923 ;	main.c:247: dbglink_tx(':');
      003F4E 75 82 3A         [24] 3924 	mov	dpl,#0x3a
      003F51 12 42 C1         [24] 3925 	lcall	_dbglink_tx
      003F54                       3926 00104$:
                           00022A  3927 	C$main.c$249$3$249 ==.
                                   3928 ;	main.c:249: dbglink_tx(' ');
      003F54 75 82 20         [24] 3929 	mov	dpl,#0x20
      003F57 12 42 C1         [24] 3930 	lcall	_dbglink_tx
                           000230  3931 	C$main.c$250$3$249 ==.
                                   3932 ;	main.c:250: dbglink_writehex16(*p++, 2, WRNUM_PADZERO);
      003F5A 8C 82            [24] 3933 	mov	dpl,r4
      003F5C 8D 83            [24] 3934 	mov	dph,r5
      003F5E E0               [24] 3935 	movx	a,@dptr
      003F5F FB               [12] 3936 	mov	r3,a
      003F60 A3               [24] 3937 	inc	dptr
      003F61 AC 82            [24] 3938 	mov	r4,dpl
      003F63 AD 83            [24] 3939 	mov	r5,dph
      003F65 7A 00            [12] 3940 	mov	r2,#0x00
      003F67 C0 07            [24] 3941 	push	ar7
      003F69 C0 06            [24] 3942 	push	ar6
      003F6B C0 05            [24] 3943 	push	ar5
      003F6D C0 04            [24] 3944 	push	ar4
      003F6F 74 08            [12] 3945 	mov	a,#0x08
      003F71 C0 E0            [24] 3946 	push	acc
      003F73 74 02            [12] 3947 	mov	a,#0x02
      003F75 C0 E0            [24] 3948 	push	acc
      003F77 8B 82            [24] 3949 	mov	dpl,r3
      003F79 8A 83            [24] 3950 	mov	dph,r2
      003F7B 12 53 77         [24] 3951 	lcall	_dbglink_writehex16
      003F7E 15 81            [12] 3952 	dec	sp
      003F80 15 81            [12] 3953 	dec	sp
      003F82 D0 04            [24] 3954 	pop	ar4
      003F84 D0 05            [24] 3955 	pop	ar5
      003F86 D0 06            [24] 3956 	pop	ar6
      003F88 D0 07            [24] 3957 	pop	ar7
                           000260  3958 	C$main.c$243$2$248 ==.
                                   3959 ;	main.c:243: for (j = 0; j < i; ++j) {
      003F8A 0F               [12] 3960 	inc	r7
      003F8B 80 89            [24] 3961 	sjmp	00107$
      003F8D                       3962 00105$:
                           000263  3963 	C$main.c$252$2$248 ==.
                                   3964 ;	main.c:252: dbglink_tx('\n');
      003F8D 75 82 0A         [24] 3965 	mov	dpl,#0x0a
      003F90 12 42 C1         [24] 3966 	lcall	_dbglink_tx
      003F93                       3967 00109$:
                           000269  3968 	C$main.c$255$2$248 ==.
                           000269  3969 	XFmain$dump_pkt$0$0 ==.
      003F93 22               [24] 3970 	ret
                                   3971 ;------------------------------------------------------------
                                   3972 ;Allocation info for local variables in function 'display_ber'
                                   3973 ;------------------------------------------------------------
                                   3974 ;st                        Allocated to registers r6 r7 
                                   3975 ;freqoffs                  Allocated to registers r4 r5 r6 r7 
                                   3976 ;------------------------------------------------------------
                           00026A  3977 	Fmain$display_ber$0$0 ==.
                           00026A  3978 	C$main.c$257$2$248 ==.
                                   3979 ;	main.c:257: static void display_ber(struct axradio_status __xdata *st)
                                   3980 ;	-----------------------------------------
                                   3981 ;	 function display_ber
                                   3982 ;	-----------------------------------------
      003F94                       3983 _display_ber:
      003F94 AE 82            [24] 3984 	mov	r6,dpl
      003F96 AF 83            [24] 3985 	mov	r7,dph
                           00026E  3986 	C$main.c$259$1$252 ==.
                                   3987 ;	main.c:259: int32_t freqoffs = axradio_conv_freq_tohz(st->u.rx.phy.offset);
      003F98 74 06            [12] 3988 	mov	a,#0x06
      003F9A 2E               [12] 3989 	add	a,r6
      003F9B FE               [12] 3990 	mov	r6,a
      003F9C E4               [12] 3991 	clr	a
      003F9D 3F               [12] 3992 	addc	a,r7
      003F9E FF               [12] 3993 	mov	r7,a
      003F9F 8E 82            [24] 3994 	mov	dpl,r6
      003FA1 8F 83            [24] 3995 	mov	dph,r7
      003FA3 A3               [24] 3996 	inc	dptr
      003FA4 A3               [24] 3997 	inc	dptr
      003FA5 E0               [24] 3998 	movx	a,@dptr
      003FA6 FC               [12] 3999 	mov	r4,a
      003FA7 A3               [24] 4000 	inc	dptr
      003FA8 E0               [24] 4001 	movx	a,@dptr
      003FA9 FD               [12] 4002 	mov	r5,a
      003FAA A3               [24] 4003 	inc	dptr
      003FAB E0               [24] 4004 	movx	a,@dptr
      003FAC FE               [12] 4005 	mov	r6,a
      003FAD A3               [24] 4006 	inc	dptr
      003FAE E0               [24] 4007 	movx	a,@dptr
      003FAF 8C 82            [24] 4008 	mov	dpl,r4
      003FB1 8D 83            [24] 4009 	mov	dph,r5
      003FB3 8E F0            [24] 4010 	mov	b,r6
      003FB5 12 07 78         [24] 4011 	lcall	_axradio_conv_freq_tohz
      003FB8 AC 82            [24] 4012 	mov	r4,dpl
      003FBA AD 83            [24] 4013 	mov	r5,dph
      003FBC AE F0            [24] 4014 	mov	r6,b
      003FBE FF               [12] 4015 	mov	r7,a
                           000295  4016 	C$main.c$273$1$252 ==.
                                   4017 ;	main.c:273: if (DBGLNKSTAT & 0x10) {
      003FBF E5 E2            [12] 4018 	mov	a,_DBGLNKSTAT
      003FC1 30 E4 57         [24] 4019 	jnb	acc.4,00119$
                           00029A  4020 	C$main.c$274$2$261 ==.
                                   4021 ;	main.c:274: dbglink_writestr("BER = 0.");
      003FC4 90 5B C3         [24] 4022 	mov	dptr,#___str_0
      003FC7 75 F0 80         [24] 4023 	mov	b,#0x80
      003FCA C0 07            [24] 4024 	push	ar7
      003FCC C0 06            [24] 4025 	push	ar6
      003FCE C0 05            [24] 4026 	push	ar5
      003FD0 C0 04            [24] 4027 	push	ar4
      003FD2 12 4E CF         [24] 4028 	lcall	_dbglink_writestr
                           0002AB  4029 	C$main.c$275$2$261 ==.
                                   4030 ;	main.c:275: dbglink_writenum32(errors, BERDIGITS, WRNUM_PADZERO);
      003FD5 74 08            [12] 4031 	mov	a,#0x08
      003FD7 C0 E0            [24] 4032 	push	acc
      003FD9 03               [12] 4033 	rr	a
      003FDA C0 E0            [24] 4034 	push	acc
      003FDC 85 2B 82         [24] 4035 	mov	dpl,_errors
      003FDF 85 2C 83         [24] 4036 	mov	dph,(_errors + 1)
      003FE2 85 2D F0         [24] 4037 	mov	b,(_errors + 2)
      003FE5 E5 2E            [12] 4038 	mov	a,(_errors + 3)
      003FE7 12 56 07         [24] 4039 	lcall	_dbglink_writenum32
      003FEA 15 81            [12] 4040 	dec	sp
      003FEC 15 81            [12] 4041 	dec	sp
                           0002C4  4042 	C$main.c$276$2$261 ==.
                                   4043 ;	main.c:276: dbglink_writestr("\tFOFFS = ");
      003FEE 90 5B CC         [24] 4044 	mov	dptr,#___str_1
      003FF1 75 F0 80         [24] 4045 	mov	b,#0x80
      003FF4 12 4E CF         [24] 4046 	lcall	_dbglink_writestr
      003FF7 D0 04            [24] 4047 	pop	ar4
      003FF9 D0 05            [24] 4048 	pop	ar5
      003FFB D0 06            [24] 4049 	pop	ar6
      003FFD D0 07            [24] 4050 	pop	ar7
                           0002D5  4051 	C$main.c$277$2$261 ==.
                                   4052 ;	main.c:277: dbglink_writenum32(freqoffs, 6, WRNUM_SIGNED);
      003FFF 74 01            [12] 4053 	mov	a,#0x01
      004001 C0 E0            [24] 4054 	push	acc
      004003 74 06            [12] 4055 	mov	a,#0x06
      004005 C0 E0            [24] 4056 	push	acc
      004007 8C 82            [24] 4057 	mov	dpl,r4
      004009 8D 83            [24] 4058 	mov	dph,r5
      00400B 8E F0            [24] 4059 	mov	b,r6
      00400D EF               [12] 4060 	mov	a,r7
      00400E 12 56 07         [24] 4061 	lcall	_dbglink_writenum32
      004011 15 81            [12] 4062 	dec	sp
      004013 15 81            [12] 4063 	dec	sp
                           0002EB  4064 	C$main.c$278$2$261 ==.
                                   4065 ;	main.c:278: dbglink_tx('\n');
      004015 75 82 0A         [24] 4066 	mov	dpl,#0x0a
      004018 12 42 C1         [24] 4067 	lcall	_dbglink_tx
      00401B                       4068 00119$:
                           0002F1  4069 	C$main.c$281$1$252 ==.
                           0002F1  4070 	XFmain$display_ber$0$0 ==.
      00401B 22               [24] 4071 	ret
                                   4072 ;------------------------------------------------------------
                                   4073 ;Allocation info for local variables in function 'axradio_statuschange'
                                   4074 ;------------------------------------------------------------
                                   4075 ;st                        Allocated to registers r6 r7 
                                   4076 ;i                         Allocated to registers 
                                   4077 ;i                         Allocated to registers 
                                   4078 ;i                         Allocated to registers 
                                   4079 ;p                         Allocated to registers 
                                   4080 ;------------------------------------------------------------
                           0002F2  4081 	G$axradio_statuschange$0$0 ==.
                           0002F2  4082 	C$main.c$284$1$252 ==.
                                   4083 ;	main.c:284: void axradio_statuschange(struct axradio_status __xdata *st)
                                   4084 ;	-----------------------------------------
                                   4085 ;	 function axradio_statuschange
                                   4086 ;	-----------------------------------------
      00401C                       4087 _axradio_statuschange:
                           0002F2  4088 	C$main.c$286$1$263 ==.
                                   4089 ;	main.c:286: switch (st->status) {
      00401C AE 82            [24] 4090 	mov	r6,dpl
      00401E AF 83            [24] 4091 	mov  r7,dph
      004020 E0               [24] 4092 	movx	a,@dptr
      004021 FD               [12] 4093 	mov	r5,a
      004022 60 34            [24] 4094 	jz	00126$
      004024 BD 03 02         [24] 4095 	cjne	r5,#0x03,00183$
      004027 80 0D            [24] 4096 	sjmp	00105$
      004029                       4097 00183$:
      004029 BD 04 02         [24] 4098 	cjne	r5,#0x04,00184$
      00402C 80 0C            [24] 4099 	sjmp	00112$
      00402E                       4100 00184$:
      00402E BD 05 02         [24] 4101 	cjne	r5,#0x05,00185$
      004031 80 0B            [24] 4102 	sjmp	00118$
      004033                       4103 00185$:
      004033 02 40 B3         [24] 4104 	ljmp	00157$
                           00030C  4105 	C$main.c$288$2$264 ==.
                                   4106 ;	main.c:288: led0_on();
      004036                       4107 00105$:
      004036 D2 93            [12] 4108 	setb	_PORTC_3
                           00030E  4109 	C$main.c$289$2$264 ==.
                                   4110 ;	main.c:289: break;
                           00030E  4111 	C$main.c$292$2$264 ==.
                                   4112 ;	main.c:292: led0_off();
      004038 80 79            [24] 4113 	sjmp	00157$
      00403A                       4114 00112$:
      00403A C2 93            [12] 4115 	clr	_PORTC_3
                           000312  4116 	C$main.c$293$2$264 ==.
                                   4117 ;	main.c:293: break;
                           000312  4118 	C$main.c$302$3$269 ==.
                                   4119 ;	main.c:302: case 2:
      00403C 80 75            [24] 4120 	sjmp	00157$
      00403E                       4121 00118$:
                           000314  4122 	C$main.c$304$3$269 ==.
                                   4123 ;	main.c:304: axradio_transmit((void *)0, onepattern, sizeof(onepattern));
      00403E 75 0D BB         [24] 4124 	mov	_axradio_transmit_PARM_2,#_onepattern
      004041 75 0E 5B         [24] 4125 	mov	(_axradio_transmit_PARM_2 + 1),#(_onepattern >> 8)
      004044 75 0F 80         [24] 4126 	mov	(_axradio_transmit_PARM_2 + 2),#0x80
      004047 75 10 08         [24] 4127 	mov	_axradio_transmit_PARM_3,#0x08
      00404A 75 11 00         [24] 4128 	mov	(_axradio_transmit_PARM_3 + 1),#0x00
      00404D 90 00 00         [24] 4129 	mov	dptr,#0x0000
      004050 75 F0 00         [24] 4130 	mov	b,#0x00
      004053 12 37 3D         [24] 4131 	lcall	_axradio_transmit
                           00032C  4132 	C$main.c$305$3$269 ==.
                                   4133 ;	main.c:305: break;
                           00032C  4134 	C$main.c$334$2$264 ==.
                                   4135 ;	main.c:334: case AXRADIO_STAT_RECEIVE:
      004056 80 5B            [24] 4136 	sjmp	00157$
      004058                       4137 00126$:
                           00032E  4138 	C$main.c$336$3$274 ==.
                                   4139 ;	main.c:336: if (acquire_agc == 1) {
      004058 74 01            [12] 4140 	mov	a,#0x01
      00405A B5 33 0A         [24] 4141 	cjne	a,_acquire_agc,00134$
                           000333  4142 	C$main.c$338$6$277 ==.
                                   4143 ;	main.c:338: led0_off();
      00405D C2 93            [12] 4144 	clr	_PORTC_3
                           000335  4145 	C$main.c$339$4$275 ==.
                                   4146 ;	main.c:339: acquire_agc = 2;
      00405F 75 33 02         [24] 4147 	mov	_acquire_agc,#0x02
                           000338  4148 	C$main.c$340$4$275 ==.
                                   4149 ;	main.c:340: axradio_agc_freeze();
      004062 12 3A C1         [24] 4150 	lcall	_axradio_agc_freeze
                           00033B  4151 	C$main.c$341$4$275 ==.
                                   4152 ;	main.c:341: break;
      004065 80 4C            [24] 4153 	sjmp	00157$
      004067                       4154 00134$:
                           00033D  4155 	C$main.c$343$3$274 ==.
                                   4156 ;	main.c:343: if (acquire_agc == 2) {
      004067 74 02            [12] 4157 	mov	a,#0x02
      004069 B5 33 05         [24] 4158 	cjne	a,_acquire_agc,00146$
                           000342  4159 	C$main.c$345$4$278 ==.
                                   4160 ;	main.c:345: acquire_agc = 0;
      00406C 75 33 00         [24] 4161 	mov	_acquire_agc,#0x00
                           000345  4162 	C$main.c$365$4$278 ==.
                                   4163 ;	main.c:365: break;
                           000345  4164 	C$main.c$368$3$274 ==.
                                   4165 ;	main.c:368: led0_on();
      00406F 80 42            [24] 4166 	sjmp	00157$
      004071                       4167 00146$:
      004071 D2 93            [12] 4168 	setb	_PORTC_3
                           000349  4169 	C$main.c$369$3$274 ==.
                                   4170 ;	main.c:369: process_ber(st);
      004073 8E 82            [24] 4171 	mov	dpl,r6
      004075 8F 83            [24] 4172 	mov	dph,r7
      004077 C0 07            [24] 4173 	push	ar7
      004079 C0 06            [24] 4174 	push	ar6
      00407B 12 3D 5B         [24] 4175 	lcall	_process_ber
      00407E D0 06            [24] 4176 	pop	ar6
      004080 D0 07            [24] 4177 	pop	ar7
                           000358  4178 	C$main.c$373$3$274 ==.
                                   4179 ;	main.c:373: if (!acquire_agc)
      004082 E5 33            [12] 4180 	mov	a,_acquire_agc
      004084 60 2D            [24] 4181 	jz	00157$
                           00035C  4182 	C$main.c$375$3$274 ==.
                                   4183 ;	main.c:375: axradio_agc_thaw();
      004086 C0 07            [24] 4184 	push	ar7
      004088 C0 06            [24] 4185 	push	ar6
      00408A 12 3A C8         [24] 4186 	lcall	_axradio_agc_thaw
      00408D D0 06            [24] 4187 	pop	ar6
      00408F D0 07            [24] 4188 	pop	ar7
                           000367  4189 	C$main.c$376$3$274 ==.
                                   4190 ;	main.c:376: display_ber(st);
      004091 8E 82            [24] 4191 	mov	dpl,r6
      004093 8F 83            [24] 4192 	mov	dph,r7
      004095 12 3F 94         [24] 4193 	lcall	_display_ber
                           00036E  4194 	C$main.c$377$3$274 ==.
                                   4195 ;	main.c:377: bytes = NUMBYTES;
      004098 75 27 E2         [24] 4196 	mov	_bytes,#0xe2
      00409B 75 28 04         [24] 4197 	mov	(_bytes + 1),#0x04
      00409E E4               [12] 4198 	clr	a
      00409F F5 29            [12] 4199 	mov	(_bytes + 2),a
      0040A1 F5 2A            [12] 4200 	mov	(_bytes + 3),a
                           000379  4201 	C$main.c$378$3$274 ==.
                                   4202 ;	main.c:378: errors = 0;
      0040A3 F5 2B            [12] 4203 	mov	_errors,a
      0040A5 F5 2C            [12] 4204 	mov	(_errors + 1),a
      0040A7 F5 2D            [12] 4205 	mov	(_errors + 2),a
      0040A9 F5 2E            [12] 4206 	mov	(_errors + 3),a
                           000381  4207 	C$main.c$379$3$274 ==.
                                   4208 ;	main.c:379: errors2 = 0;
      0040AB F5 2F            [12] 4209 	mov	_errors2,a
      0040AD F5 30            [12] 4210 	mov	(_errors2 + 1),a
      0040AF F5 31            [12] 4211 	mov	(_errors2 + 2),a
      0040B1 F5 32            [12] 4212 	mov	(_errors2 + 3),a
                           000389  4213 	C$main.c$385$1$263 ==.
                                   4214 ;	main.c:385: }
      0040B3                       4215 00157$:
                           000389  4216 	C$main.c$386$1$263 ==.
                           000389  4217 	XG$axradio_statuschange$0$0 ==.
      0040B3 22               [24] 4218 	ret
                                   4219 ;------------------------------------------------------------
                                   4220 ;Allocation info for local variables in function 'set_cw'
                                   4221 ;------------------------------------------------------------
                                   4222 ;i                         Allocated to registers r6 
                                   4223 ;------------------------------------------------------------
                           00038A  4224 	G$set_cw$0$0 ==.
                           00038A  4225 	C$main.c$388$1$263 ==.
                                   4226 ;	main.c:388: void set_cw(void)
                                   4227 ;	-----------------------------------------
                                   4228 ;	 function set_cw
                                   4229 ;	-----------------------------------------
      0040B4                       4230 _set_cw:
                           00038A  4231 	C$main.c$390$1$285 ==.
                                   4232 ;	main.c:390: uint8_t i = axradio_set_mode(AXRADIO_MODE_CW_TRANSMIT);
      0040B4 75 82 03         [24] 4233 	mov	dpl,#0x03
      0040B7 12 30 4D         [24] 4234 	lcall	_axradio_set_mode
                           000390  4235 	C$main.c$391$1$285 ==.
                                   4236 ;	main.c:391: if (i != AXRADIO_ERR_NOERROR) {
      0040BA E5 82            [12] 4237 	mov	a,dpl
      0040BC FF               [12] 4238 	mov	r7,a
      0040BD FE               [12] 4239 	mov	r6,a
      0040BE 60 0A            [24] 4240 	jz	00120$
                           000396  4241 	C$main.c$394$2$286 ==.
                                   4242 ;	main.c:394: dbglink_display_radio_error(i);
      0040C0 8E 82            [24] 4243 	mov	dpl,r6
      0040C2 12 3B 6D         [24] 4244 	lcall	_dbglink_display_radio_error
      0040C5                       4245 00118$:
                           00039B  4246 	C$main.c$398$2$286 ==.
                                   4247 ;	main.c:398: enter_sleep();
      0040C5 12 55 8A         [24] 4248 	lcall	_enter_sleep
                           00039E  4249 	C$main.c$405$1$285 ==.
                                   4250 ;	main.c:405: display_writestr(AX5043_MODCFGA & 0x02 ? "SE " : "   ");
      0040C8 80 FB            [24] 4251 	sjmp	00118$
      0040CA                       4252 00120$:
                           0003A0  4253 	C$main.c$406$1$285 ==.
                           0003A0  4254 	XG$set_cw$0$0 ==.
      0040CA 22               [24] 4255 	ret
                                   4256 ;------------------------------------------------------------
                                   4257 ;Allocation info for local variables in function 'set_transmit'
                                   4258 ;------------------------------------------------------------
                                   4259 ;i                         Allocated to registers r6 
                                   4260 ;------------------------------------------------------------
                           0003A1  4261 	G$set_transmit$0$0 ==.
                           0003A1  4262 	C$main.c$408$1$285 ==.
                                   4263 ;	main.c:408: void set_transmit(void)
                                   4264 ;	-----------------------------------------
                                   4265 ;	 function set_transmit
                                   4266 ;	-----------------------------------------
      0040CB                       4267 _set_transmit:
                           0003A1  4268 	C$main.c$429$1$295 ==.
                                   4269 ;	main.c:429: i = axradio_set_mode(i);
      0040CB 75 82 18         [24] 4270 	mov	dpl,#0x18
      0040CE 12 30 4D         [24] 4271 	lcall	_axradio_set_mode
                           0003A7  4272 	C$main.c$430$1$295 ==.
                                   4273 ;	main.c:430: if (i != AXRADIO_ERR_NOERROR) {
      0040D1 E5 82            [12] 4274 	mov	a,dpl
      0040D3 FF               [12] 4275 	mov	r7,a
      0040D4 FE               [12] 4276 	mov	r6,a
      0040D5 60 0A            [24] 4277 	jz	00111$
                           0003AD  4278 	C$main.c$433$2$297 ==.
                                   4279 ;	main.c:433: dbglink_display_radio_error(i);
      0040D7 8E 82            [24] 4280 	mov	dpl,r6
      0040D9 12 3B 6D         [24] 4281 	lcall	_dbglink_display_radio_error
      0040DC                       4282 00138$:
                           0003B2  4283 	C$main.c$437$2$297 ==.
                                   4284 ;	main.c:437: enter_sleep();
      0040DC 12 55 8A         [24] 4285 	lcall	_enter_sleep
      0040DF 80 FB            [24] 4286 	sjmp	00138$
      0040E1                       4287 00111$:
                           0003B7  4288 	C$main.c$439$1$295 ==.
                                   4289 ;	main.c:439: scr.w = ~0U;
      0040E1 75 23 FF         [24] 4290 	mov	(_scr + 0),#0xff
      0040E4 75 24 FF         [24] 4291 	mov	(_scr + 1),#0xff
                           0003BD  4292 	C$main.c$465$1$295 ==.
                                   4293 ;	main.c:465: display_writestr(AX5043_MODCFGA & 0x02 ? "SE " : "   ");
                           0003BD  4294 	C$main.c$466$1$295 ==.
                           0003BD  4295 	XG$set_transmit$0$0 ==.
      0040E7 22               [24] 4296 	ret
                                   4297 ;------------------------------------------------------------
                                   4298 ;Allocation info for local variables in function 'set_receiveber'
                                   4299 ;------------------------------------------------------------
                                   4300 ;i                         Allocated to registers r6 
                                   4301 ;------------------------------------------------------------
                           0003BE  4302 	G$set_receiveber$0$0 ==.
                           0003BE  4303 	C$main.c$468$1$295 ==.
                                   4304 ;	main.c:468: void set_receiveber(void)
                                   4305 ;	-----------------------------------------
                                   4306 ;	 function set_receiveber
                                   4307 ;	-----------------------------------------
      0040E8                       4308 _set_receiveber:
                           0003BE  4309 	C$main.c$489$1$311 ==.
                                   4310 ;	main.c:489: i = axradio_set_mode(i);
      0040E8 75 82 28         [24] 4311 	mov	dpl,#0x28
      0040EB 12 30 4D         [24] 4312 	lcall	_axradio_set_mode
                           0003C4  4313 	C$main.c$490$1$311 ==.
                                   4314 ;	main.c:490: if (i != AXRADIO_ERR_NOERROR) {
      0040EE E5 82            [12] 4315 	mov	a,dpl
      0040F0 FF               [12] 4316 	mov	r7,a
      0040F1 FE               [12] 4317 	mov	r6,a
      0040F2 60 0A            [24] 4318 	jz	00112$
                           0003CA  4319 	C$main.c$493$2$313 ==.
                                   4320 ;	main.c:493: dbglink_display_radio_error(i);
      0040F4 8E 82            [24] 4321 	mov	dpl,r6
      0040F6 12 3B 6D         [24] 4322 	lcall	_dbglink_display_radio_error
      0040F9                       4323 00128$:
                           0003CF  4324 	C$main.c$497$2$313 ==.
                                   4325 ;	main.c:497: enter_sleep();
      0040F9 12 55 8A         [24] 4326 	lcall	_enter_sleep
                           0003D2  4327 	C$main.c$499$1$311 ==.
                                   4328 ;	main.c:499: display_clear(0x00, 16);
      0040FC 80 FB            [24] 4329 	sjmp	00128$
      0040FE                       4330 00112$:
                           0003D4  4331 	C$main.c$510$1$311 ==.
                                   4332 ;	main.c:510: bytes = NUMBYTES;
      0040FE 75 27 E2         [24] 4333 	mov	_bytes,#0xe2
      004101 75 28 04         [24] 4334 	mov	(_bytes + 1),#0x04
      004104 E4               [12] 4335 	clr	a
      004105 F5 29            [12] 4336 	mov	(_bytes + 2),a
      004107 F5 2A            [12] 4337 	mov	(_bytes + 3),a
                           0003DF  4338 	C$main.c$511$1$311 ==.
                                   4339 ;	main.c:511: errors = 0;
      004109 F5 2B            [12] 4340 	mov	_errors,a
      00410B F5 2C            [12] 4341 	mov	(_errors + 1),a
      00410D F5 2D            [12] 4342 	mov	(_errors + 2),a
      00410F F5 2E            [12] 4343 	mov	(_errors + 3),a
                           0003E7  4344 	C$main.c$512$1$311 ==.
                                   4345 ;	main.c:512: errors2 = 0;
      004111 F5 2F            [12] 4346 	mov	_errors2,a
      004113 F5 30            [12] 4347 	mov	(_errors2 + 1),a
      004115 F5 31            [12] 4348 	mov	(_errors2 + 2),a
      004117 F5 32            [12] 4349 	mov	(_errors2 + 3),a
                           0003EF  4350 	C$main.c$513$1$311 ==.
                                   4351 ;	main.c:513: acquire_agc = 1;
      004119 75 33 01         [24] 4352 	mov	_acquire_agc,#0x01
                           0003F2  4353 	C$main.c$514$1$311 ==.
                           0003F2  4354 	XG$set_receiveber$0$0 ==.
      00411C 22               [24] 4355 	ret
                                   4356 ;------------------------------------------------------------
                                   4357 ;Allocation info for local variables in function '_sdcc_external_startup'
                                   4358 ;------------------------------------------------------------
                                   4359 ;c                         Allocated to registers 
                                   4360 ;p                         Allocated to registers 
                                   4361 ;c                         Allocated to registers 
                                   4362 ;p                         Allocated to registers 
                                   4363 ;------------------------------------------------------------
                           0003F3  4364 	G$_sdcc_external_startup$0$0 ==.
                           0003F3  4365 	C$main.c$529$1$311 ==.
                                   4366 ;	main.c:529: uint8_t _sdcc_external_startup(void)
                                   4367 ;	-----------------------------------------
                                   4368 ;	 function _sdcc_external_startup
                                   4369 ;	-----------------------------------------
      00411D                       4370 __sdcc_external_startup:
                           0003F3  4371 	C$main.c$532$2$325 ==.
                                   4372 ;	main.c:532: wtimer0_setclksrc(CLKSRC_LPOSC, 1);
      00411D 75 82 09         [24] 4373 	mov	dpl,#0x09
      004120 12 45 C3         [24] 4374 	lcall	_wtimer0_setconfig
                           0003F9  4375 	C$main.c$533$2$326 ==.
                                   4376 ;	main.c:533: wtimer1_setclksrc(CLKSRC_FRCOSC, 7);
      004123 75 82 38         [24] 4377 	mov	dpl,#0x38
      004126 12 45 E1         [24] 4378 	lcall	_wtimer1_setconfig
                           0003FF  4379 	C$main.c$535$1$324 ==.
                                   4380 ;	main.c:535: coldstart = !(PCON & 0x40);
      004129 E5 87            [12] 4381 	mov	a,_PCON
      00412B A2 E6            [12] 4382 	mov	c,acc[6]
      00412D B3               [12] 4383 	cpl	c
      00412E 92 02            [24] 4384 	mov	__sdcc_external_startup_sloc0_1_0,c
      004130 E4               [12] 4385 	clr	a
      004131 33               [12] 4386 	rlc	a
      004132 F5 22            [12] 4387 	mov	_coldstart,a
                           00040A  4388 	C$main.c$537$1$324 ==.
                                   4389 ;	main.c:537: ANALOGA = 0x18; // PA[3,4] LPXOSC, other PA are used as digital pins
      004134 90 70 07         [24] 4390 	mov	dptr,#_ANALOGA
      004137 74 18            [12] 4391 	mov	a,#0x18
      004139 F0               [24] 4392 	movx	@dptr,a
                           000410  4393 	C$main.c$551$1$324 ==.
                                   4394 ;	main.c:551: PORTA = 0xC0 | (PINA & 0x25); // pull-up for PA[6,7] which are not bonded, no pull up for PA[3,4] (LPXOSC). Output 0 in PA[0,1,2,5] to prevent current consumption in all DIP switch states
      00413A 74 25            [12] 4395 	mov	a,#0x25
      00413C 55 C8            [12] 4396 	anl	a,_PINA
      00413E 44 C0            [12] 4397 	orl	a,#0xc0
      004140 F5 80            [12] 4398 	mov	_PORTA,a
                           000418  4399 	C$main.c$552$1$324 ==.
                                   4400 ;	main.c:552: PORTB = 0xFE; //PB[0,1]  (LCD RS, LCD RST) are overwritten by lcd2_portinit(), enable pull-ups for PB[2..7]  (PB[2,3] for buttons, PB[4..7] unused)
      004142 75 88 FE         [24] 4401 	mov	_PORTB,#0xfe
                           00041B  4402 	C$main.c$553$1$324 ==.
                                   4403 ;	main.c:553: PORTC = 0xF3 | (PINC & 0x08); // set PC0 = 1 (LCD SEL), PC1 = 1 (LCD SCK), PC2 = 0 (LCD MOSI), PC3 =0 (LED), enable pull-ups for PC[4..7] which are not bonded Mind: PORTC[0:1] is set to 0x3 by lcd2_portinit()
      004145 74 08            [12] 4404 	mov	a,#0x08
      004147 55 F8            [12] 4405 	anl	a,_PINC
      004149 44 F3            [12] 4406 	orl	a,#0xf3
      00414B F5 90            [12] 4407 	mov	_PORTC,a
                           000423  4408 	C$main.c$554$1$324 ==.
                                   4409 ;	main.c:554: PORTR = 0xCB; // overwritten by ax5043_reset, ax5043_comminit()
      00414D 75 8C CB         [24] 4410 	mov	_PORTR,#0xcb
                           000426  4411 	C$main.c$556$1$324 ==.
                                   4412 ;	main.c:556: DIRA = 0x27; // output 0 on PA[0,1,2,5] to prevent current consumption in all DIP switch states. Other PA are inputs, PA[3,4] (LPXOSC) must have disabled digital output drivers
      004150 75 89 27         [24] 4413 	mov	_DIRA,#0x27
                           000429  4414 	C$main.c$557$1$324 ==.
                                   4415 ;	main.c:557: DIRB = 0x03; // PB[0,1] are outputs (LCD RS, LCD RST), PB[2..7] are inputs (PB[2,3] for buttons,  PB[4..7]  unused)
      004153 75 8A 03         [24] 4416 	mov	_DIRB,#0x03
                           00042C  4417 	C$main.c$558$1$324 ==.
                                   4418 ;	main.c:558: DIRC = 0x0F; // PC[0..3] are outputs (LCD SEL, LCD,SCK, LCD MOSI, LED), PC[4..7] are inputs (not bonded).
      004156 75 8B 0F         [24] 4419 	mov	_DIRC,#0x0f
                           00042F  4420 	C$main.c$559$1$324 ==.
                                   4421 ;	main.c:559: DIRR = 0x15; // overwritten by ax5043_reset, ax5043_comminit()
      004159 75 8E 15         [24] 4422 	mov	_DIRR,#0x15
                           000432  4423 	C$main.c$562$1$324 ==.
                                   4424 ;	main.c:562: axradio_setup_pincfg1();
      00415C 12 06 88         [24] 4425 	lcall	_axradio_setup_pincfg1
                           000435  4426 	C$main.c$563$1$324 ==.
                                   4427 ;	main.c:563: DPS = 0;
      00415F 75 86 00         [24] 4428 	mov	_DPS,#0x00
                           000438  4429 	C$main.c$564$1$324 ==.
                                   4430 ;	main.c:564: IE = 0x40;
      004162 75 A8 40         [24] 4431 	mov	_IE,#0x40
                           00043B  4432 	C$main.c$565$1$324 ==.
                                   4433 ;	main.c:565: EIE = 0x00;
      004165 75 98 00         [24] 4434 	mov	_EIE,#0x00
                           00043E  4435 	C$main.c$566$1$324 ==.
                                   4436 ;	main.c:566: E2IE = 0x00;
      004168 75 A0 00         [24] 4437 	mov	_E2IE,#0x00
                           000441  4438 	C$main.c$568$1$324 ==.
                                   4439 ;	main.c:568: GPIOENABLE = 1; // unfreeze GPIO
      00416B 90 70 0C         [24] 4440 	mov	dptr,#_GPIOENABLE
      00416E 74 01            [12] 4441 	mov	a,#0x01
      004170 F0               [24] 4442 	movx	@dptr,a
                           000447  4443 	C$main.c$572$1$324 ==.
                                   4444 ;	main.c:572: return !coldstart; // coldstart -> return 0 -> var initialization; start from sleep -> return 1 -> no var initialization
      004171 E5 22            [12] 4445 	mov	a,_coldstart
      004173 B4 01 00         [24] 4446 	cjne	a,#0x01,00111$
      004176                       4447 00111$:
      004176 92 02            [24] 4448 	mov  __sdcc_external_startup_sloc0_1_0,c
      004178 E4               [12] 4449 	clr	a
      004179 33               [12] 4450 	rlc	a
      00417A F5 82            [12] 4451 	mov	dpl,a
                           000452  4452 	C$main.c$574$1$324 ==.
                           000452  4453 	XG$_sdcc_external_startup$0$0 ==.
      00417C 22               [24] 4454 	ret
                                   4455 ;------------------------------------------------------------
                                   4456 ;Allocation info for local variables in function 'main'
                                   4457 ;------------------------------------------------------------
                                   4458 ;i                         Allocated to registers r7 
                                   4459 ;x                         Allocated to registers r7 
                                   4460 ;flg                       Allocated to registers r7 
                                   4461 ;flg                       Allocated to registers r7 
                                   4462 ;------------------------------------------------------------
                           000453  4463 	G$main$0$0 ==.
                           000453  4464 	C$main.c$576$1$324 ==.
                                   4465 ;	main.c:576: void main(void)
                                   4466 ;	-----------------------------------------
                                   4467 ;	 function main
                                   4468 ;	-----------------------------------------
      00417D                       4469 _main:
                           000453  4470 	C$main.c$586$1$329 ==.
                                   4471 ;	main.c:586: __endasm;
                           000000  4472 	G$_start__stack$0$0	= __start__stack
                                   4473 	.globl	G$_start__stack$0$0
                           000453  4474 	C$main.c$590$1$329 ==.
                                   4475 ;	main.c:590: dbglink_init();
      00417D 12 4A 24         [24] 4476 	lcall	_dbglink_init
                           000456  4477 	C$main.c$593$1$329 ==.
                                   4478 ;	main.c:593: EA = 1;
      004180 D2 AF            [12] 4479 	setb	_EA
                           000458  4480 	C$main.c$595$1$329 ==.
                                   4481 ;	main.c:595: flash_apply_calibration();
      004182 12 4D 3A         [24] 4482 	lcall	_flash_apply_calibration
                           00045B  4483 	C$main.c$596$1$329 ==.
                                   4484 ;	main.c:596: CLKCON = 0;
      004185 75 C6 00         [24] 4485 	mov	_CLKCON,#0x00
                           00045E  4486 	C$main.c$597$1$329 ==.
                                   4487 ;	main.c:597: wtimer_init();
      004188 12 46 94         [24] 4488 	lcall	_wtimer_init
                           000461  4489 	C$main.c$602$2$332 ==.
                                   4490 ;	main.c:602: uint8_t i = axradio_init();
      00418B 12 2B 57         [24] 4491 	lcall	_axradio_init
                           000464  4492 	C$main.c$603$2$332 ==.
                                   4493 ;	main.c:603: if (i != AXRADIO_ERR_NOERROR) {
      00418E E5 82            [12] 4494 	mov	a,dpl
      004190 FF               [12] 4495 	mov	r7,a
      004191 60 1F            [24] 4496 	jz	00115$
                           000469  4497 	C$main.c$604$3$333 ==.
                                   4498 ;	main.c:604: if (i == AXRADIO_ERR_NOCHIP) {
      004193 BF 05 14         [24] 4499 	cjne	r7,#0x05,00111$
                           00046C  4500 	C$main.c$607$4$334 ==.
                                   4501 ;	main.c:607: if (DBGLNKSTAT & 0x10)
      004196 E5 E2            [12] 4502 	mov	a,_DBGLNKSTAT
      004198 20 E4 03         [24] 4503 	jb	acc.4,00192$
      00419B 02 42 42         [24] 4504 	ljmp	00149$
      00419E                       4505 00192$:
                           000474  4506 	C$main.c$608$4$334 ==.
                                   4507 ;	main.c:608: dbglink_writestr("No AX5043 RF\nchip found");
      00419E 90 5B D6         [24] 4508 	mov	dptr,#___str_2
      0041A1 75 F0 80         [24] 4509 	mov	b,#0x80
      0041A4 12 4E CF         [24] 4510 	lcall	_dbglink_writestr
                           00047D  4511 	C$main.c$610$4$334 ==.
                                   4512 ;	main.c:610: goto terminate_error;
      0041A7 02 42 42         [24] 4513 	ljmp	00149$
                           000480  4514 	C$main.c$612$3$333 ==.
                                   4515 ;	main.c:612: display_radio_error(i);
      0041AA                       4516 00111$:
                           000480  4517 	C$main.c$614$3$333 ==.
                                   4518 ;	main.c:614: dbglink_display_radio_error(i);
      0041AA 8F 82            [24] 4519 	mov	dpl,r7
      0041AC 12 3B 6D         [24] 4520 	lcall	_dbglink_display_radio_error
                           000485  4521 	C$main.c$616$3$333 ==.
                                   4522 ;	main.c:616: goto terminate_error;
      0041AF 02 42 42         [24] 4523 	ljmp	00149$
                           000488  4524 	C$main.c$618$2$332 ==.
                                   4525 ;	main.c:618: display_writestr("found AX5043\n");
      0041B2                       4526 00115$:
                           000488  4527 	C$main.c$620$2$332 ==.
                                   4528 ;	main.c:620: if (DBGLNKSTAT & 0x10)
      0041B2 E5 E2            [12] 4529 	mov	a,_DBGLNKSTAT
      0041B4 30 E4 09         [24] 4530 	jnb	acc.4,00118$
                           00048D  4531 	C$main.c$621$2$332 ==.
                                   4532 ;	main.c:621: dbglink_writestr("found AX5043\n");
      0041B7 90 5B EE         [24] 4533 	mov	dptr,#___str_3
      0041BA 75 F0 80         [24] 4534 	mov	b,#0x80
      0041BD 12 4E CF         [24] 4535 	lcall	_dbglink_writestr
      0041C0                       4536 00118$:
                           000496  4537 	C$main.c$627$1$329 ==.
                                   4538 ;	main.c:627: if(DBGLNKSTAT & 0x10) {
      0041C0 E5 E2            [12] 4539 	mov	a,_DBGLNKSTAT
      0041C2 30 E4 53         [24] 4540 	jnb	acc.4,00122$
                           00049B  4541 	C$main.c$628$2$338 ==.
                                   4542 ;	main.c:628: dbglink_writestr("RNG=");
      0041C5 90 5B FC         [24] 4543 	mov	dptr,#___str_4
      0041C8 75 F0 80         [24] 4544 	mov	b,#0x80
      0041CB 12 4E CF         [24] 4545 	lcall	_dbglink_writestr
                           0004A4  4546 	C$main.c$629$2$338 ==.
                                   4547 ;	main.c:629: dbglink_writenum16(axradio_get_pllrange(), 2, 0);
      0041CE 12 35 7A         [24] 4548 	lcall	_axradio_get_pllrange
      0041D1 AF 82            [24] 4549 	mov	r7,dpl
      0041D3 E4               [12] 4550 	clr	a
      0041D4 FE               [12] 4551 	mov	r6,a
      0041D5 C0 E0            [24] 4552 	push	acc
      0041D7 74 02            [12] 4553 	mov	a,#0x02
      0041D9 C0 E0            [24] 4554 	push	acc
      0041DB 8F 82            [24] 4555 	mov	dpl,r7
      0041DD 8E 83            [24] 4556 	mov	dph,r6
      0041DF 12 57 75         [24] 4557 	lcall	_dbglink_writenum16
      0041E2 15 81            [12] 4558 	dec	sp
      0041E4 15 81            [12] 4559 	dec	sp
                           0004BC  4560 	C$main.c$631$3$339 ==.
                                   4561 ;	main.c:631: uint8_t x = axradio_get_pllvcoi();
      0041E6 12 35 8F         [24] 4562 	lcall	_axradio_get_pllvcoi
                           0004BF  4563 	C$main.c$632$3$339 ==.
                                   4564 ;	main.c:632: if (x & 0x80) {
      0041E9 E5 82            [12] 4565 	mov	a,dpl
      0041EB FF               [12] 4566 	mov	r7,a
      0041EC 30 E7 20         [24] 4567 	jnb	acc.7,00120$
                           0004C5  4568 	C$main.c$633$4$340 ==.
                                   4569 ;	main.c:633: dbglink_writestr("\nVCOI=");
      0041EF 90 5C 01         [24] 4570 	mov	dptr,#___str_5
      0041F2 75 F0 80         [24] 4571 	mov	b,#0x80
      0041F5 C0 07            [24] 4572 	push	ar7
      0041F7 12 4E CF         [24] 4573 	lcall	_dbglink_writestr
      0041FA D0 07            [24] 4574 	pop	ar7
                           0004D2  4575 	C$main.c$634$4$340 ==.
                                   4576 ;	main.c:634: dbglink_writehex16(x, 2, 0);
      0041FC E4               [12] 4577 	clr	a
      0041FD FE               [12] 4578 	mov	r6,a
      0041FE C0 E0            [24] 4579 	push	acc
      004200 74 02            [12] 4580 	mov	a,#0x02
      004202 C0 E0            [24] 4581 	push	acc
      004204 8F 82            [24] 4582 	mov	dpl,r7
      004206 8E 83            [24] 4583 	mov	dph,r6
      004208 12 53 77         [24] 4584 	lcall	_dbglink_writehex16
      00420B 15 81            [12] 4585 	dec	sp
      00420D 15 81            [12] 4586 	dec	sp
      00420F                       4587 00120$:
                           0004E5  4588 	C$main.c$637$2$338 ==.
                                   4589 ;	main.c:637: dbglink_writestr("\n\n");
      00420F 90 5C 08         [24] 4590 	mov	dptr,#___str_6
      004212 75 F0 80         [24] 4591 	mov	b,#0x80
      004215 12 4E CF         [24] 4592 	lcall	_dbglink_writestr
      004218                       4593 00122$:
                           0004EE  4594 	C$main.c$654$1$329 ==.
                                   4595 ;	main.c:654: axradio_setup_pincfg2();
      004218 12 06 8E         [24] 4596 	lcall	_axradio_setup_pincfg2
                           0004F1  4597 	C$main.c$659$2$341 ==.
                                   4598 ;	main.c:659: set_cw();
      00421B 12 40 B4         [24] 4599 	lcall	_set_cw
                           0004F4  4600 	C$main.c$708$1$329 ==.
                                   4601 ;	main.c:708: }
      00421E                       4602 00147$:
                           0004F4  4603 	C$main.c$710$2$342 ==.
                                   4604 ;	main.c:710: wtimer_runcallbacks();
      00421E 12 47 C8         [24] 4605 	lcall	_wtimer_runcallbacks
                           0004F7  4606 	C$main.c$711$2$342 ==.
                                   4607 ;	main.c:711: EA = 0;
      004221 C2 AF            [12] 4608 	clr	_EA
                           0004F9  4609 	C$main.c$713$3$342 ==.
                                   4610 ;	main.c:713: uint8_t flg = WTFLAG_CANSTANDBY;
      004223 7F 02            [12] 4611 	mov	r7,#0x02
                           0004FB  4612 	C$main.c$715$3$343 ==.
                                   4613 ;	main.c:715: if (axradio_cansleep()
      004225 C0 07            [24] 4614 	push	ar7
      004227 12 30 3B         [24] 4615 	lcall	_axradio_cansleep
      00422A E5 82            [12] 4616 	mov	a,dpl
      00422C D0 07            [24] 4617 	pop	ar7
      00422E 60 09            [24] 4618 	jz	00137$
                           000506  4619 	C$main.c$717$3$343 ==.
                                   4620 ;	main.c:717: && dbglink_txidle()
      004230 12 4A 15         [24] 4621 	lcall	_dbglink_txidle
      004233 E5 82            [12] 4622 	mov	a,dpl
      004235 60 02            [24] 4623 	jz	00137$
                           00050D  4624 	C$main.c$720$3$343 ==.
                                   4625 ;	main.c:720: flg |= WTFLAG_CANSLEEP;
      004237 7F 03            [12] 4626 	mov	r7,#0x03
      004239                       4627 00137$:
                           00050F  4628 	C$main.c$722$3$343 ==.
                                   4629 ;	main.c:722: wtimer_idle(flg);
      004239 8F 82            [24] 4630 	mov	dpl,r7
      00423B 12 48 49         [24] 4631 	lcall	_wtimer_idle
                           000514  4632 	C$main.c$724$2$342 ==.
                                   4633 ;	main.c:724: EA = 1;
      00423E D2 AF            [12] 4634 	setb	_EA
                           000516  4635 	C$main.c$726$1$329 ==.
                                   4636 ;	main.c:726: terminate_error:
      004240 80 DC            [24] 4637 	sjmp	00147$
      004242                       4638 00149$:
                           000518  4639 	C$main.c$728$2$344 ==.
                                   4640 ;	main.c:728: wtimer_runcallbacks();
      004242 12 47 C8         [24] 4641 	lcall	_wtimer_runcallbacks
                           00051B  4642 	C$main.c$730$3$344 ==.
                                   4643 ;	main.c:730: uint8_t flg = WTFLAG_CANSTANDBY;
      004245 7F 02            [12] 4644 	mov	r7,#0x02
                           00051D  4645 	C$main.c$732$3$345 ==.
                                   4646 ;	main.c:732: if (axradio_cansleep()
      004247 C0 07            [24] 4647 	push	ar7
      004249 12 30 3B         [24] 4648 	lcall	_axradio_cansleep
      00424C E5 82            [12] 4649 	mov	a,dpl
      00424E D0 07            [24] 4650 	pop	ar7
      004250 60 09            [24] 4651 	jz	00143$
                           000528  4652 	C$main.c$734$3$345 ==.
                                   4653 ;	main.c:734: && dbglink_txidle()
      004252 12 4A 15         [24] 4654 	lcall	_dbglink_txidle
      004255 E5 82            [12] 4655 	mov	a,dpl
      004257 60 02            [24] 4656 	jz	00143$
                           00052F  4657 	C$main.c$737$3$345 ==.
                                   4658 ;	main.c:737: flg |= WTFLAG_CANSLEEP;
      004259 7F 03            [12] 4659 	mov	r7,#0x03
      00425B                       4660 00143$:
                           000531  4661 	C$main.c$739$3$345 ==.
                                   4662 ;	main.c:739: wtimer_idle(flg);
      00425B 8F 82            [24] 4663 	mov	dpl,r7
      00425D 12 48 49         [24] 4664 	lcall	_wtimer_idle
      004260 80 E0            [24] 4665 	sjmp	00149$
                           000538  4666 	C$main.c$742$1$329 ==.
                           000538  4667 	XG$main$0$0 ==.
      004262 22               [24] 4668 	ret
                                   4669 	.area CSEG    (CODE)
                                   4670 	.area CONST   (CODE)
                           000000  4671 G$txpattern$0$0 == .
      005BB3                       4672 _txpattern:
      005BB3 55                    4673 	.db #0x55	; 85	'U'
      005BB4 55                    4674 	.db #0x55	; 85	'U'
      005BB5 55                    4675 	.db #0x55	; 85	'U'
      005BB6 55                    4676 	.db #0x55	; 85	'U'
      005BB7 55                    4677 	.db #0x55	; 85	'U'
      005BB8 55                    4678 	.db #0x55	; 85	'U'
      005BB9 55                    4679 	.db #0x55	; 85	'U'
      005BBA 55                    4680 	.db #0x55	; 85	'U'
                           000008  4681 G$onepattern$0$0 == .
      005BBB                       4682 _onepattern:
      005BBB FF                    4683 	.db #0xff	; 255
      005BBC FF                    4684 	.db #0xff	; 255
      005BBD FF                    4685 	.db #0xff	; 255
      005BBE FF                    4686 	.db #0xff	; 255
      005BBF FF                    4687 	.db #0xff	; 255
      005BC0 FF                    4688 	.db #0xff	; 255
      005BC1 FF                    4689 	.db #0xff	; 255
      005BC2 FF                    4690 	.db #0xff	; 255
                           000010  4691 Fmain$__str_0$0$0 == .
      005BC3                       4692 ___str_0:
      005BC3 42 45 52 20 3D 20 30  4693 	.ascii "BER = 0."
             2E
      005BCB 00                    4694 	.db 0x00
                           000019  4695 Fmain$__str_1$0$0 == .
      005BCC                       4696 ___str_1:
      005BCC 09                    4697 	.db 0x09
      005BCD 46 4F 46 46 53 20 3D  4698 	.ascii "FOFFS = "
             20
      005BD5 00                    4699 	.db 0x00
                           000023  4700 Fmain$__str_2$0$0 == .
      005BD6                       4701 ___str_2:
      005BD6 4E 6F 20 41 58 35 30  4702 	.ascii "No AX5043 RF"
             34 33 20 52 46
      005BE2 0A                    4703 	.db 0x0a
      005BE3 63 68 69 70 20 66 6F  4704 	.ascii "chip found"
             75 6E 64
      005BED 00                    4705 	.db 0x00
                           00003B  4706 Fmain$__str_3$0$0 == .
      005BEE                       4707 ___str_3:
      005BEE 66 6F 75 6E 64 20 41  4708 	.ascii "found AX5043"
             58 35 30 34 33
      005BFA 0A                    4709 	.db 0x0a
      005BFB 00                    4710 	.db 0x00
                           000049  4711 Fmain$__str_4$0$0 == .
      005BFC                       4712 ___str_4:
      005BFC 52 4E 47 3D           4713 	.ascii "RNG="
      005C00 00                    4714 	.db 0x00
                           00004E  4715 Fmain$__str_5$0$0 == .
      005C01                       4716 ___str_5:
      005C01 0A                    4717 	.db 0x0a
      005C02 56 43 4F 49 3D        4718 	.ascii "VCOI="
      005C07 00                    4719 	.db 0x00
                           000055  4720 Fmain$__str_6$0$0 == .
      005C08                       4721 ___str_6:
      005C08 0A                    4722 	.db 0x0a
      005C09 0A                    4723 	.db 0x0a
      005C0A 00                    4724 	.db 0x00
                                   4725 	.area XINIT   (CODE)
                                   4726 	.area CABS    (ABS,CODE)
