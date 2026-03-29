#ifndef BEEP_H
# define BEEP_H

/* Including necessary headers. */
# include <asm/io.h>
# include <linux/i8253.h>
# include <linux/init.h>
# include <linux/input.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/platform_device.h>
# include <linux/timex.h>

# define BEEP_REGION 0x61
# define PIT_REGION1 0x42
# define PIT_REGION2 0x43
# define PIT_SETTING 0xB6
# define PIT_FREQUENCY 1193180
# define BEEP_FREQUENCY 1000
# define MIN_RATE 20
# define MAX_RATE 32767

/* Module information */
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("yrakcaz <zackaryayoun@gmail.com>");
MODULE_DESCRIPTION("Little pc speaker beep driver.");
MODULE_ALIAS("platform:beep");

/* Module function declarations */
int beep_init(void);
void beep_exit(void);
int beep_suspend(struct device *dev);
int beep_probe(struct platform_device *dev);
void beep_remove(struct platform_device *dev);
void beep_shutdown(struct platform_device *dev);

/* Structure representing the device. */
struct platform_device beep_dev =
{
    .name = "beep",
};

/* Structures which declare driver operations */
struct dev_pm_ops beep_ops =
{
    .suspend = beep_suspend,
};

struct platform_driver beep_funcs =
{
    .driver =
    {
        .name = "beep",
        .owner = THIS_MODULE,
        .pm = &beep_ops,
    },
    .probe = beep_probe,
    .remove = beep_remove,
    .shutdown = beep_shutdown,
};

/* Module init and exit declaration */
module_init(beep_init);
module_exit(beep_exit);

#endif /* !BEEP_H */
