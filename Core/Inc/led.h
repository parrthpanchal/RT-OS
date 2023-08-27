#ifndef __LED_H__
#define __LED_H__


#define LED_R	(1U << 11)
#define LED_G	(1U << 12)
#define LED_B	(1U << 13)


void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);
void config_ext_leds(void);

#endif
