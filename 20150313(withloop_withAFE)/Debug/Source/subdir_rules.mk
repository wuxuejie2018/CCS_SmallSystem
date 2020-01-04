################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Source/ADC_all.obj: ../Source/ADC_all.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/ADC_all.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/Control.obj: ../Source/Control.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/Control.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_ADC_cal.obj: ../Source/DSP2833x_ADC_cal.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_ADC_cal.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_Adc.obj: ../Source/DSP2833x_Adc.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_Adc.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_CodeStartBranch.obj: ../Source/DSP2833x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_CodeStartBranch.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_CpuTimers.obj: ../Source/DSP2833x_CpuTimers.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_CpuTimers.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_DefaultIsr.obj: ../Source/DSP2833x_DefaultIsr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_DefaultIsr.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_EPwm.obj: ../Source/DSP2833x_EPwm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_EPwm.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_EQep.obj: ../Source/DSP2833x_EQep.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_EQep.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_GlobalVariableDefs.obj: ../Source/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_GlobalVariableDefs.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_PieCtrl.obj: ../Source/DSP2833x_PieCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_PieCtrl.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_PieVect.obj: ../Source/DSP2833x_PieVect.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_PieVect.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_Sci.obj: ../Source/DSP2833x_Sci.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_Sci.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_SysCtrl.obj: ../Source/DSP2833x_SysCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_SysCtrl.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_Xintf.obj: ../Source/DSP2833x_Xintf.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_Xintf.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/DSP2833x_usDelay.obj: ../Source/DSP2833x_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/DSP2833x_usDelay.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/EPwmSetup.obj: ../Source/EPwmSetup.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/EPwmSetup.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/Example_posspeed.obj: ../Source/Example_posspeed.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/Example_posspeed.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/MyDefine.obj: ../Source/MyDefine.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/MyDefine.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/main.obj: ../Source/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" --include_path="F:/workspaceccs6/DSP2833x_headers" --include_path="F:/CCS6.0/ccsv6/tools/compiler/c2000_6.2.5/include" --include_path="D:/_study/ccs/20150313(withloop_withAFE)/Source/headers" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Source/main.pp" --obj_directory="Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


