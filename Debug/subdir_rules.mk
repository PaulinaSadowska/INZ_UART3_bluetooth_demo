################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
UART3_conf.obj: ../UART3_conf.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/include" --include_path="C:/ti/TivaWare_C_Series-2.1.1.71" -g --gcc --undefine=PART_TM4C123GH6PM --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_wrap=off --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="UART3_conf.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

UART3_messages_control.obj: ../UART3_messages_control.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/include" --include_path="C:/ti/TivaWare_C_Series-2.1.1.71" -g --gcc --undefine=PART_TM4C123GH6PM --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_wrap=off --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="UART3_messages_control.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

current_sensing.obj: ../current_sensing.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/include" --include_path="C:/ti/TivaWare_C_Series-2.1.1.71" -g --gcc --undefine=PART_TM4C123GH6PM --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_wrap=off --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="current_sensing.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/include" --include_path="C:/ti/TivaWare_C_Series-2.1.1.71" -g --gcc --undefine=PART_TM4C123GH6PM --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_wrap=off --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_15.9.0.STS/include" --include_path="C:/ti/TivaWare_C_Series-2.1.1.71" -g --gcc --undefine=PART_TM4C123GH6PM --define=ccs="ccs" --define=PART_TM4C123GH6PM --display_error_number --diag_wrap=off --diag_warning=225 --abi=eabi --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


