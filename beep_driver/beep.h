#ifndef BEEP_H
# define BEEP_H

/* Including necessary headers. */
# include <linux/platform_device.h>
# include <linux/init.h>
# include <linux/module.h>
# include <linux/kernel.h> /* printk() */
# include <asm/io.h>
# include <linux/i8253.h>
# include <linux/timex.h>
# include <linux/input.h>

# define BEEP_REGION 0x61
# define PIT_REGION1 0x42
# define PIT_REGION2 0x43
# define PIT_SETTING 0xB6
# define PIT_FREQUEN 1193180
# define BEEP_FREQUE 1000

/* Module informations */
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Zackary Ayoun <zackaryayoun@gmail.com>");
MODULE_DESCRIPTION("Little pc speaker beep driver.");

/* Module function declarations */
int __init beep_init(void);
void __init beep_exit(void);
int beep_suspend(struct device *dev);
int __devinit beep_probe(struct platform_device *dev);
int __devexit beep_remove(struct platform_device *dev);
void beep_shutdown(struct platform_device *dev);

/* Structures which declare driver operations */
struct dev_pm_ops beep_ops =
{
    .suspend = beep_suspend,
};

struct platform_driver beep_funcs =
{
    .probe = beep_probe,
    .remove = beep_remove,
    .shutdown = beep_shutdown,
    .driver =
    {
        .name = "beep",
        .owner = THIS_MODULE,
        .pm = &beep_ops,
    },
};

/* Module init and exit declaration */
module_init(beep_init);
module_exit(beep_exit);

#endif /* !BEEP_H */
