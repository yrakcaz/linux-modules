#include "beep.h"

int beep_init(void)
{
    int ret;
    ret = platform_device_register(&beep_dev);
    if (ret)
    {
        printk(KERN_ALERT "beep: error while registering platform device.\n");
        return ret;
    }
    ret = platform_driver_register(&beep_funcs);
    if (ret)
        printk(KERN_ALERT "beep: error while registering platform driver.\n");
    else
        printk(KERN_INFO "beep: module initialized!\n");
    return ret;
}

void beep_exit(void)
{
    platform_device_unregister(&beep_dev);
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
    unsigned long flags;
    unsigned int count = 0;
    if (type != EV_SND)
    {
        printk(KERN_ALERT "beep: wrong beep type!\n");
        return -1;
    }
    if (code == SND_BELL && value)
        value = BEEP_FREQUE;
    if (value > MIN_RATE && value < MAX_RATE)
        count = PIT_TICK_RATE / value;

    raw_spin_lock_irqsave(&i8253_lock, flags);

    if (count)
        make_beep(count);
    else
        shutup_beep();

    raw_spin_unlock_irqrestore(&i8253_lock, flags);

    return 0;
}

int beep_suspend(struct device *dev)
{
    printk(KERN_INFO "beep: suspend!\n");
    return treat_beep(NULL, EV_SND, SND_BELL, 0);
}

int beep_probe(struct platform_device *dev)
{
    int err;

    struct input_dev *beep_dev = input_allocate_device();
    if (!beep_dev)
    {
        printk(KERN_ALERT "beep: error while allocating memory.\n");
        return -ENOMEM;
    }

    beep_dev->name = "PC Speaker";
    beep_dev->phys = "isa0061/input0";
    beep_dev->id.bustype = BUS_ISA;
    beep_dev->id.vendor = 0x001F;
    beep_dev->id.product = 0x0001;
    beep_dev->id.version = 0x0100;
    beep_dev->dev.parent = &dev->dev;
    beep_dev->evbit[0] = BIT_MASK(EV_SND);
    beep_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);
    beep_dev->event = treat_beep;

    err = input_register_device(beep_dev);
    if (err)
    {
        input_free_device(beep_dev);
        printk(KERN_ALERT "beep: error while registering device.\n");
        return err;
    }

    platform_set_drvdata(dev, beep_dev);

    printk(KERN_INFO "beep: probe!\n");
    return 0;
}

int beep_remove(struct platform_device *dev)
{
    struct input_dev *beep_dev = platform_get_drvdata(dev);
    input_unregister_device(beep_dev);
    platform_set_drvdata(dev, NULL);

    printk(KERN_INFO "beep: remove!\n");
    return treat_beep(NULL, EV_SND, SND_BELL, 0);
}

void beep_shutdown(struct platform_device *dev)
{
    printk(KERN_INFO "beep: shutdown!\n");
    treat_beep(NULL, EV_SND, SND_BELL, 0);
}
