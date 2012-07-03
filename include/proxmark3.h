//-----------------------------------------------------------------------------
// Jonathan Westhues, Mar 2006
//
// This code is licensed to you under the terms of the GNU GPL, version 2 or,
// at your option, any later version. See the LICENSE.txt file for the text of
// the license.
//-----------------------------------------------------------------------------
// Hardware and interface definitions
//-----------------------------------------------------------------------------

#ifndef __PROXMARK3_H
#define __PROXMARK3_H

// Might as well have the hardware-specific defines everywhere.
#include "at91sam7s512.h"
#include "config_gpio.h"
#include <usb_cmd.h>

#define WDT_HIT()								AT91C_BASE_WDTC->WDTC_WDCR = 0xa5000001

#define PWM_CH_MODE_PRESCALER(x)			((x)<<0)
#define PWM_CHANNEL(x)					(1<<(x))

#define TC_CMR_TCCLKS_TIMER_CLOCK1				(0<<0)
#define TC_CMR_TCCLKS_TIMER_CLOCK2				(1<<0)
#define TC_CMR_TCCLKS_TIMER_CLOCK3				(2<<0)
#define TC_CMR_TCCLKS_TIMER_CLOCK4				(3<<0)
#define TC_CMR_TCCLKS_TIMER_CLOCK5				(4<<0)

#define ADC_CHAN_LF								4
#define ADC_CHAN_HF								5
#define ADC_MODE_PRESCALE(x)				((x)<<8)
#define ADC_MODE_STARTUP_TIME(x)			((x)<<16)
#define ADC_MODE_SAMPLE_HOLD_TIME(x)			((x)<<24)
#define ADC_CHANNEL(x)					(1<<(x))
#define ADC_END_OF_CONVERSION(x)			(1<<(x))

#define SSC_CLOCK_MODE_START(x)				((x)<<8)
#define SSC_FRAME_MODE_WORDS_PER_TRANSFER(x)		((x)<<8)
#define SSC_CLOCK_MODE_SELECT(x)			((x)<<0)
#define SSC_FRAME_MODE_BITS_IN_WORD(x)			(((x)-1)<<0)

#define MC_FLASH_COMMAND_KEY				((0x5a)<<24)
#define MC_FLASH_STATUS_READY					(1<<0)
#define MC_FLASH_STATUS_LOCKE					(1<<2)
#define MC_FLASH_STATUS_PROGE					(1<<3)
#define MC_FLASH_MODE_FLASH_WAIT_STATES(x)		((x)<<8)
#define MC_FLASH_MODE_MASTER_CLK_IN_MHZ(x)		((x)<<16)
#define MC_FLASH_COMMAND_PAGEN(x)			((x)<<8)

#define RST_CONTROL_KEY					(0xa5<<24)

#define PMC_MAIN_OSC_ENABLE						(1<<0)
#define PMC_MAIN_OSC_STABILIZED					(1<<0)
#define PMC_MAIN_OSC_PLL_LOCK					(1<<2)
#define PMC_MAIN_OSC_MCK_READY					(1<<3)

#define PMC_MAIN_OSC_STARTUP_DELAY(x)			((x)<<8)
#define PMC_PLL_DIVISOR(x)				(x)
#define PMC_CLK_PRESCALE_DIV_2					(1<<2)
#define PMC_PLL_MULTIPLIER(x)				(((x)-1)<<16)
#define PMC_PLL_COUNT_BEFORE_LOCK(x)			((x)<<8)
#define PMC_PLL_FREQUENCY_RANGE(x)			((x)<<14)
#define PMC_PLL_USB_DIVISOR(x)				((x)<<28)

#define UDP_INTERRUPT_ENDPOINT(x)			(1<<(x))
#define UDP_CSR_BYTES_RECEIVED(x)			(((x) >> 16) & 0x7ff)
//**************************************************************

#define LOW(x)	AT91C_BASE_PIOA->PIO_CODR = (x)
#define HIGH(x)	AT91C_BASE_PIOA->PIO_SODR = (x)

#define PWMC_EnableChannel(x) AT91C_BASE_PWMC->PWMC_ENA = (1 << x)
#define PWMC_DisableChannel(x) AT91C_BASE_PWMC->PWMC_DIS = (1 << x)

#define TRUE 1
#define FALSE 0

#define SPI_FPGA_MODE	(0)
#define SPI_LCD_MODE	(1)
#define SPI_MSD_MODE	(2)
#define SPI_SPARE_MODE	(3)

//#define PACKED __attribute__((__packed__))

#define USB_D_PLUS_PULLUP_ON() { \
		HIGH(GPIO_USB_PU); \
		AT91C_BASE_PIOA->PIO_OER = GPIO_USB_PU; \
	}
#define USB_D_PLUS_PULLUP_OFF() AT91C_BASE_PIOA->PIO_ODR = GPIO_USB_PU

#define LCD_CS_ON();	HIGH(AT91C_PIO_PA10);
#define LCD_CS_OFF();	LOW(AT91C_PIO_PA10);

#define LED_A_ON()		HIGH(GPIO_LED_A)
#define LED_A_OFF()		LOW(GPIO_LED_A)
#define LED_B_ON()		LOW(GPIO_LED_B)
#define LED_B_OFF()		LOW(GPIO_LED_B)
#define LED_C_ON()		LOW(GPIO_LED_C)
#define LED_C_OFF()		LOW(GPIO_LED_C)
#define LED_D_ON()		LOW(GPIO_LED_D)
#define LED_D_OFF()		LOW(GPIO_LED_D)
#define RELAY_ON()		HIGH(GPIO_RELAY)
#define RELAY_OFF()		LOW(GPIO_RELAY)
#define BUTTON_PRESS()	!(AT91C_BASE_PIOA->PIO_PDSR & GPIO_BUTTON)
#define BUTTON_UP()		!(AT91C_BASE_PIOA->PIO_PDSR & GPIO_BUTTON_U)
#define BUTTON_DOWN()	!(AT91C_BASE_PIOA->PIO_PDSR & GPIO_BUTTON_D)
#define BUTTON_LEFT()	!(AT91C_BASE_PIOA->PIO_PDSR & GPIO_BUTTON_L)
#define BUTTON_RIGHT()	!(AT91C_BASE_PIOA->PIO_PDSR & GPIO_BUTTON_R)

//--------------------------------
// USB declarations

void UsbSendPacket(uint8_t *packet, int len);
int UsbConnected();
int UsbPoll(int blinkLeds);
void UsbStart(void);

// This function is provided by the apps/bootrom, and called from UsbPoll
// if data are available.
void UsbPacketReceived(uint8_t *packet, int len);

#define VERSION_INFORMATION_MAGIC 0x56334d50
struct version_information {
	int magic; /* Magic sequence to identify this as a correct version information structure. Must be VERSION_INFORMATION_MAGIC */
	char versionversion; /* Must be 1 */
	char present; /* 1 if the version information could be created at compile time, otherwise 0 and the remaining fields (except for magic) are empty */
	char clean; /* 1: Tree was clean, no local changes. 0: Tree was unclean. 2: Couldn't be determined */
	char gitversion[15]; /* String with the GIT revision */
	char buildtime[30]; /* string with the build time */
} __attribute__((packed));

#define COMMON_AREA_MAGIC 0x43334d50
#define COMMON_AREA_COMMAND_NONE 0
#define COMMON_AREA_COMMAND_ENTER_FLASH_MODE 1
struct common_area {
	int magic; /* Magic sequence, to distinguish against random uninitialized memory */
	char version; /* Must be 1 */
	char command;
	struct {
		unsigned int bootrom_present:1; /* Set when a bootrom that is capable of parsing the common area is present */
		unsigned int osimage_present:1; /* Set when a osimage that is capable of parsing the common area is present */
	} __attribute__((packed)) flags;
	int arg1, arg2;
} __attribute__((packed));

#endif