#include "beep.h"

int __init beep_init(void)
{
    int ret = platform_driver_register(&beep_funcs);
    if (ret)
        printk(KERN_ALERT "beep: error while registering platform driver.\n");
    else
        printk(KERN_INFO "beep: module initialized!\n");
    return ret;
}

void __init beep_exit(void)
{
    platform_driver_unregister(&beep_funcs);
    printk(KERN_INFO "beep: driver removed!\n");
}

static void make_beep(unsigned int freq)
{
    unsigned char beep_cur;
    unsigned int pit_val;

    pit_val = PIT_FREQUEN / freq;
    outb(PIT_REGION2, PIT_SETTING);
    outb(PIT_REGION1, (unsigned char)pit_val);
    outb(PIT_REGION1, (unsigned char)(pit_val >> 8));

    beep_cur = inb(BEEP_REGION);
    if (beep_cur != (beep_cur | 3))
        outb(BEEP_REGION, beep_cur | 3);
}

static void shutup_beep(void)
{
    unsigned char beep_cur = inb(BEEP_REGION) & 0xFC;
    outb(BEEP_REGION, beep_cur);
}

static int treat_beep(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
}
