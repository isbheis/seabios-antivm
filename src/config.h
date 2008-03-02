#ifndef __CONFIG_H
#define __CONFIG_H
// Configuration definitions.

#define CONFIG_FLOPPY_SUPPORT 1
#define CONFIG_PS2_MOUSE 1
#define CONFIG_ATA 1
#define CONFIG_KBD_CALL_INT15_4F 1
#define CONFIG_ELTORITO_BOOT 0

#define CONFIG_MAX_ATA_INTERFACES 4
#define CONFIG_MAX_ATA_DEVICES  (CONFIG_MAX_ATA_INTERFACES*2)

#define CONFIG_STACK_SEGMENT 0x00
#define CONFIG_STACK_OFFSET  0xfffe

#define CONFIG_MODEL_ID      0xFC
#define CONFIG_SUBMODEL_ID   0x00
#define CONFIG_BIOS_REVISION 0x01

#endif // config.h
