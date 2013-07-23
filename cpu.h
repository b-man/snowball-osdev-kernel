#ifndef CPU_H
#define CPU_H

/* processor mode bits */
#define USRMODE 0x10
#define FIQMODE 0x11
#define IRQMODE 0x12
#define SVCMODE 0x13
#define ABTMODE 0x17
#define UNDMODE 0x1B
#define SYSMODE 0x1F

/* IRQ and FIQ flags */
#define IBIT    0x80
#define FBIT    0x40

#endif /* !CPU_H */
