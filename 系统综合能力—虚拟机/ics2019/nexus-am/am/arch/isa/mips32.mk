CROSS_COMPILE := mips-linux-gnu-
COMMON_FLAGS  := -march=mips32 -fno-pic -fno-delayed-branch -mno-abicalls -mno-check-zero-division -EL
CFLAGS        += $(COMMON_FLAGS) -static -mno-llsc -mno-imadd -mno-mad
ASFLAGS       += $(COMMON_FLAGS) -O0
LDFLAGS       += -EL
