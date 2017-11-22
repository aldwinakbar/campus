# Component makefile for extras/lora_wrapper

# expected anyone using bmp driver includes it as 'lora_wrapper/lora_wrapper.h'
INC_DIRS += $(lora_wrapper_ROOT)..

# args for passing into compile rule generation
lora_wrapper_SRC_DIR =  $(lora_wrapper_ROOT)

$(eval $(call component_compile_rules,lora_wrapper))
