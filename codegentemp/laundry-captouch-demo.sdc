# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\doita\OneDrive\Documents\PSoC Creator\GEA-Hacking\laundry-captouch-demo.cydsn\laundry-captouch-demo.cyprj
# Date: Sat, 22 May 2021 23:45:48 GMT
#set_units -time ns
create_clock -name {Input_Capsense_ModClk(FFB)} -period 10625 -waveform {0 5312.5} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {Uart_Mc_SCBCLK(FFB)} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/ff_div_0}]]
create_clock -name {Uart_PowerStart_SCBCLK(FFB)} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/ff_div_1}]]
create_clock -name {CyILO} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 25000 -waveform {0 12500} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Input_Capsense_ModClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 255 511} [list]
create_generated_clock -name {Uart_Mc_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 9 17} [list]
create_generated_clock -name {Uart_PowerStart_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 9 17} [list]


# Component constraints for C:\Users\doita\OneDrive\Documents\PSoC Creator\GEA-Hacking\laundry-captouch-demo.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\doita\OneDrive\Documents\PSoC Creator\GEA-Hacking\laundry-captouch-demo.cydsn\laundry-captouch-demo.cyprj
# Date: Sat, 22 May 2021 23:45:46 GMT