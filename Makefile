#
# DDS Sine Sweeper
#
# Copyright 2013 Al Brown
#
# http://eartoearoak.com/software/dds-sine-sweeper
#
# This file is part of DDS Sine Sweeper.
#
# DDS Sine Sweeper is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# DDS Sine Sweeper is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with DDS Sine Sweeper.  If not, see <http://www.gnu.org/licenses/>.


#
# User definitions
#

ToolsetRoot=C:\PROGRA~2\RAISON~1\Ride
StdPeriphRoot = ..\..\libraries\stm8s_stdperiph_driver_2_1_0
FlashTool = C:\Progra~2\STMicroelectronics\st_toolset\stvp\STVP_CmdLine.exe
OutputPath = "."


#
# End User Definitions
#

Device = STM8S105x6
ToolsetBin=$(ToolsetRoot)\bin
ToolsetInc=$(ToolsetRoot)\inc\STM8;$(ToolsetRoot)\inc
ToolsetLib=$(ToolsetRoot)\Lib\ST7
StdPeriphInc=$(StdPeriphRoot)\inc
StdPeriphSrc=$(StdPeriphRoot)\src
InputName=$(basename $(notdir $<))


flash :
	$(FlashTool) -BoardName=ST-LINK -Device=$(Device) -Port=USB -ProgMode=SWIM -no_loop -no_log -no_verif -FileProg=firmware\$(TargetSName).hex


OutputPath=Release
ProjectSFile=dds_sine_sweeper
TargetSName=$(ProjectSFile)
TargetFName=$(TargetSName).elf
IntermPath=$(dir $@)
CFLAGS_PRJ=$(ToolsetBin)\rcstm8  $< OBJECT($(IntermPath)$(InputName).o) PIN("$(ToolsetInc)") WRV(0) STM8(SMALL) DGC(data) AUTO  OT(6,SPEED) PR($(IntermPath)$(InputName).lst) CD CO SB LAOB PIN(src) PIN(src\ad9850) PIN(src\lcd) PIN($(StdPeriphInc))

all : $(OutputPath) $(TargetFName)

$(OutputPath) : 
	if not exist $(OutputPath)/ mkdir $(OutputPath)

Release\ad9850.o : src\ad9850\ad9850.c src\stm8s_conf.h src\stm8s.h src\stm8s_conf.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h src\ad9850\ad9850.h src\delay.h src\stm8s.h src\main.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\config.o : src\config.c src\config.h src\stm8s_conf.h src\stm8s.h src\stm8s_conf.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h src\sweep.h src\stm8s_conf.h $(ToolsetRoot)\inc\string.h $(ToolsetRoot)\inc\st7\main_st7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\delay.o : src\delay.c src\stm8s_conf.h src\stm8s.h src\stm8s_conf.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h src\delay.h src\stm8s.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\lcd.o : src\lcd\lcd.c src\stm8s_conf.h src\stm8s.h src\stm8s_conf.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\stdio.h $(ToolsetRoot)\inc\stdarg.h $(ToolsetRoot)\inc\st7\main_st7.h $(ToolsetRoot)\inc\st7\main_st7.h src\delay.h src\stm8s.h src\lcd\lcd.h src\main.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\main.o : src\main.c $(ToolsetRoot)\inc\stdio.h $(ToolsetRoot)\inc\stdarg.h $(ToolsetRoot)\inc\st7\main_st7.h $(ToolsetRoot)\inc\st7\main_st7.h $(ToolsetRoot)\inc\string.h $(ToolsetRoot)\inc\st7\main_st7.h src\stm8s_conf.h src\stm8s.h src\stm8s_conf.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h src\ad9850\ad9850.h src\delay.h src\stm8s.h src\config.h src\stm8s_conf.h src\lcd\lcd.h src\main.h src\screen.h src\sweep.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\screen.o : src\screen.c $(ToolsetRoot)\inc\string.h $(ToolsetRoot)\inc\st7\main_st7.h src\stm8s_conf.h src\stm8s.h src\stm8s_conf.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h src\ad9850\ad9850.h src\config.h src\stm8s_conf.h src\delay.h src\stm8s.h src\lcd\lcd.h src\main.h src\screen.h src\sweep.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\sweep.o : src\sweep.c src\stm8s_conf.h src\stm8s.h src\stm8s_conf.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h src\ad9850\ad9850.h src\config.h src\stm8s_conf.h src\main.h src\screen.h src\sweep.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_clk.o : $(StdPeriphSrc)\stm8s_clk.c $(StdPeriphInc)\stm8s_clk.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_exti.o : $(StdPeriphSrc)\stm8s_exti.c $(StdPeriphInc)\stm8s_exti.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_flash.o : $(StdPeriphSrc)\stm8s_flash.c $(StdPeriphInc)\stm8s_flash.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_gpio.o : $(StdPeriphSrc)\stm8s_gpio.c $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_itc.o : $(StdPeriphSrc)\stm8s_itc.c $(StdPeriphInc)\stm8s_itc.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_tim2.o : $(StdPeriphSrc)\stm8s_tim2.c $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_tim3.o : $(StdPeriphSrc)\stm8s_tim3.c $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

Release\stm8s_tim4.o : $(StdPeriphSrc)\stm8s_tim4.c $(StdPeriphInc)\stm8s_tim4.h src\stm8s.h src\stm8s_conf.h src\stm8s.h $(StdPeriphInc)\stm8s_clk.h src\stm8s.h $(StdPeriphInc)\stm8s_exti.h src\stm8s.h $(StdPeriphInc)\stm8s_flash.h src\stm8s.h $(StdPeriphInc)\stm8s_gpio.h src\stm8s.h $(StdPeriphInc)\stm8s_itc.h src\stm8s.h $(StdPeriphInc)\stm8s_tim2.h src\stm8s.h $(StdPeriphInc)\stm8s_tim3.h src\stm8s.h $(StdPeriphInc)\stm8s_tim4.h $(ToolsetRoot)\inc\intrins.h $(ToolsetRoot)\inc\st7\intrist7.h 
	@if not exist $(dir $@)  mkdir $(dir $@)
	$(CFLAGS_PRJ)

 $(TargetFName) :  $(OutputPath)\ad9850.o $(OutputPath)\config.o $(OutputPath)\delay.o $(OutputPath)\lcd.o $(OutputPath)\main.o $(OutputPath)\screen.o $(OutputPath)\sweep.o $(OutputPath)\stm8s_clk.o $(OutputPath)\stm8s_exti.o $(OutputPath)\stm8s_flash.o $(OutputPath)\stm8s_gpio.o $(OutputPath)\stm8s_itc.o $(OutputPath)\stm8s_tim2.o $(OutputPath)\stm8s_tim3.o $(OutputPath)\stm8s_tim4.o
	$(ToolsetBin)\rlstm8  -P "Release\ad9850.o","Release\config.o","Release\delay.o","Release\lcd.o","Release\main.o","Release\screen.o","Release\sweep.o","Release\stm8s_clk.o","Release\stm8s_exti.o","Release\stm8s_flash.o","Release\stm8s_gpio.o","Release\stm8s_itc.o","Release\stm8s_tim2.o","Release\stm8s_tim3.o","Release\stm8s_tim4.o" TO($(OutputPath)\$(TargetSName).aof) LIBPATH("$(ToolsetLib)") NODEBUGLINES NODEBUGPUBLICS NODEBUGSYMBOLS NOPR SCINAME(STM8) DATASTART(0x0) RAMSIZE(0x800) CODESTART(0x8000) CODESIZE(0x8000) STACKTOP(0x800) STACKSIZE(0x200) EEPROMSTART(0x4000) EEPROMSIZE(0x400) 
	$(ToolsetBin)\omf2elf  $(OutputPath)\$(TargetSName).aof -t0x8000,4 -e0x4000,0x400

	$(ToolsetBin)\omf2hex  $(OutputPath)\$(TargetSName).aof hexext
	cmd  /c copy "$(OutputPath)\$(TargetSName).hex" firmware\
	
clean : 
	-@erase $(OutputPath)\ad9850.o
	-@erase $(OutputPath)\config.o
	-@erase $(OutputPath)\delay.o
	-@erase $(OutputPath)\lcd.o
	-@erase $(OutputPath)\main.o
	-@erase $(OutputPath)\screen.o
	-@erase $(OutputPath)\sweep.o
	-@erase $(OutputPath)\stm8s_clk.o
	-@erase $(OutputPath)\stm8s_exti.o
	-@erase $(OutputPath)\stm8s_flash.o
	-@erase $(OutputPath)\stm8s_gpio.o
	-@erase $(OutputPath)\stm8s_itc.o
	-@erase $(OutputPath)\stm8s_tim2.o
	-@erase $(OutputPath)\stm8s_tim3.o
	-@erase $(OutputPath)\stm8s_tim4.o
	-@erase $(OutputPath)\ad9850.lst
	-@erase $(OutputPath)\config.lst
	-@erase $(OutputPath)\delay.lst
	-@erase $(OutputPath)\lcd.lst
	-@erase $(OutputPath)\main.lst
	-@erase $(OutputPath)\screen.lst
	-@erase $(OutputPath)\sweep.lst
	-@erase $(OutputPath)\stm8s_clk.lst
	-@erase $(OutputPath)\stm8s_exti.lst
	-@erase $(OutputPath)\stm8s_flash.lst
	-@erase $(OutputPath)\stm8s_gpio.lst
	-@erase $(OutputPath)\stm8s_itc.lst
	-@erase $(OutputPath)\stm8s_tim2.lst
	-@erase $(OutputPath)\stm8s_tim3.lst
	-@erase $(OutputPath)\stm8s_tim4.lst
	-@erase $(OutputPath)\$(TargetFName)
	-@erase $(OutputPath)\$(TargetSName).hex
	-@erase $(OutputPath)\$(TargetSName).map
	-@erase $(OutputPath)\$(TargetSName).cseg
	-@erase $(OutputPath)\$(TargetSName).aof
	-@erase $(OutputPath)\$(TargetSName).areloc
	
	