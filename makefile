JO_COMPILE_WITH_VIDEO_MODULE = 0
JO_COMPILE_WITH_BACKUP_MODULE = 0
JO_COMPILE_WITH_TGA_MODULE = 0
JO_COMPILE_WITH_AUDIO_MODULE = 1
JO_COMPILE_WITH_3D_MODULE = 1
JO_COMPILE_WITH_PSEUDO_MODE7_MODULE = 0
JO_COMPILE_WITH_EFFECTS_MODULE = 0
JO_PSEUDO_SATURN_KAI_SUPPORT = 1
JO_COMPILE_WITH_DUAL_CPU_MODULE = 0
JO_DEBUG = 0
JO_NTSC = 1
JO_COMPILE_USING_SGL = 1
JO_COMPILE_WITH_FAST_BUT_LESS_ACCURATE_MATH = 1
SRCS=main.c collision.c gameplay.c pause.c ssmtf_logo.c state.c title_screen.c util.c assets/alien.c assets/assets.c assets/audio.c assets/disasteroid.c assets/font.c assets/ship.c assets/star.c objects/alien.c objects/disasteroid.c objects/explosion.c objects/objects.c objects/projectile.c objects/ship.c objects/star.c
JO_ENGINE_SRC_DIR=../../jo_engine
COMPILER_DIR=../../Compiler
include $(COMPILER_DIR)/COMMON/jo_engine_makefile
