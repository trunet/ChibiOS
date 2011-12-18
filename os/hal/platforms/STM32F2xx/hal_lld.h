/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    STM32F2xx/hal_lld.h
 * @brief   STM32F2xx HAL subsystem low level driver header.
 * @pre     This module requires the following macros to be defined in the
 *          @p board.h file:
 *          - STM32_LSECLK.
 *          - STM32_HSECLK.
 *          .
 *          One of the following macros must also be defined:
 *          - STM32F2XX for High-performance STM32 F-2 devices.
 *          .
 *
 * @addtogroup HAL
 * @{
 */

#ifndef _HAL_LLD_H_
#define _HAL_LLD_H_

/* Tricks required to make the TRUE/FALSE declaration inside the library
   compatible.*/
#undef FALSE
#undef TRUE
#include "stm32f2xx.h"
#define FALSE 0
#define TRUE (!FALSE)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Platform name.
 */
#define PLATFORM_NAME           "STM32F2 High performance"

#define STM32_HSICLK            16000000    /**< High speed internal clock. */
#define STM32_LSICLK            38000       /**< Low speed internal clock.  */

/* RCC_PLLCFGR register bits definitions.*/
#define STM32_PLLP_MASK			(3 << 16)	/**< PLLP mask.                 */
#define STM32_PLLP_DIV2			(0 << 16)	/**< PLL clock divided by 2.    */
#define STM32_PLLP_DIV4			(1 << 16)	/**< PLL clock divided by 4.    */
#define STM32_PLLP_DIV6			(2 << 16)   /**< PLL clock divided by 6.    */
#define STM32_PLLP_DIV8			(3 << 16)   /**< PLL clock divided by 8.    */

#define STM32_PLLSRC_HSI        (0 << 22)   /**< PLL clock source is HSI.   */
#define STM32_PLLSRC_HSE        (1 << 22)   /**< PLL clock source is HSE.   */

/* RCC_CFGR register bits definitions.*/
#define STM32_SW_MASK           (3 << 0)    /**< SW mask.                   */
#define STM32_SW_HSI            (0 << 0)    /**< SYSCLK source is HSI.      */
#define STM32_SW_HSE            (1 << 0)    /**< SYSCLK source is HSE.      */
#define STM32_SW_PLL            (2 << 0)    /**< SYSCLK source is PLL.      */

#define STM32_HPRE_MASK         (15 << 4)   /**< HPRE mask.                 */
#define STM32_HPRE_DIV1         (0 << 4)    /**< SYSCLK divided by 1.       */
#define STM32_HPRE_DIV2         (8 << 4)    /**< SYSCLK divided by 2.       */
#define STM32_HPRE_DIV4         (9 << 4)    /**< SYSCLK divided by 4.       */
#define STM32_HPRE_DIV8         (10 << 4)   /**< SYSCLK divided by 8.       */
#define STM32_HPRE_DIV16        (11 << 4)   /**< SYSCLK divided by 16.      */
#define STM32_HPRE_DIV64        (12 << 4)   /**< SYSCLK divided by 64.      */
#define STM32_HPRE_DIV128       (13 << 4)   /**< SYSCLK divided by 128.     */
#define STM32_HPRE_DIV256       (14 << 4)   /**< SYSCLK divided by 256.     */
#define STM32_HPRE_DIV512       (15 << 4)   /**< SYSCLK divided by 512.     */

#define STM32_PPRE1_MASK        (7 << 10)	/**< PPRE1 mask.                */
#define STM32_PPRE1_DIV1        (0 << 10)   /**< HCLK divided by 1.         */
#define STM32_PPRE1_DIV2        (4 << 10)   /**< HCLK divided by 2.         */
#define STM32_PPRE1_DIV4        (5 << 10)   /**< HCLK divided by 4.         */
#define STM32_PPRE1_DIV8        (6 << 10)   /**< HCLK divided by 8.         */
#define STM32_PPRE1_DIV16       (7 << 10)   /**< HCLK divided by 16.        */

#define STM32_PPRE2_MASK        (7 << 13)	/**< PPRE2 mask.                */
#define STM32_PPRE2_DIV1        (0 << 13)   /**< HCLK divided by 1.         */
#define STM32_PPRE2_DIV2        (4 << 13)   /**< HCLK divided by 2.         */
#define STM32_PPRE2_DIV4        (5 << 13)   /**< HCLK divided by 4.         */
#define STM32_PPRE2_DIV8        (6 << 13)   /**< HCLK divided by 8.         */
#define STM32_PPRE2_DIV16       (7 << 13)   /**< HCLK divided by 16.        */

#define STM32_RTCPRE_MASK       (31 << 16)  /**< RTCPRE mask.               */

#define STM32_MCO1SEL_MASK      (3 << 21)   /**< MCO1 mask.                 */
#define STM32_MCO1SEL_HSI       (0 << 21)   /**< HSI clock on MCO1 pin.     */
#define STM32_MCO1SEL_LSE       (1 << 21)   /**< LSE clock on MCO1 pin.     */
#define STM32_MCO1SEL_HSE       (2 << 21)   /**< HSE clock on MCO1 pin.     */
#define STM32_MCO1SEL_PLL       (3 << 21)   /**< PLL clock on MCO1 pin.     */

#define STM32_MCO1PRE_MASK      (7 << 24)   /**< MCO1PRE mask.              */
#define STM32_MCO1PRE_DIV1      (0 << 24)   /**< MCO1 divided by 1.         */
#define STM32_MCO1PRE_DIV2      (1 << 24)   /**< MCO1 divided by 2.         */
#define STM32_MCO1PRE_DIV3      (2 << 24)   /**< MCO1 divided by 3.         */
#define STM32_MCO1PRE_DIV4      (3 << 24)   /**< MCO1 divided by 4.         */
#define STM32_MCO1PRE_DIV5      (4 << 24)   /**< MCO1 divided by 5.         */

#define STM32_MCO2PRE_MASK      (7 << 27)   /**< MCO2PRE mask.              */
#define STM32_MCO2PRE_DIV1      (0 << 27)   /**< MCO2 divided by 1.         */
#define STM32_MCO2PRE_DIV2      (4 << 27)   /**< MCO2 divided by 2.         */
#define STM32_MCO2PRE_DIV3      (5 << 27)   /**< MCO2 divided by 3.         */
#define STM32_MCO2PRE_DIV4      (6 << 27)   /**< MCO2 divided by 4.         */
#define STM32_MCO2PRE_DIV5      (7 << 27)   /**< MCO2 divided by 5.         */

#define STM32_MCO2SEL_MASK      (3 << 30)   /**< MCO2 mask.                 */
#define STM32_MCO2SEL_SYSCLK    (0 << 30)   /**< SYSCLK clock on MCO2 pin.  */
#define STM32_MCO2SEL_PLLI2S    (1 << 30)   /**< PLLI2S clock on MCO2 pin.  */
#define STM32_MCO2SEL_HSE       (2 << 30)   /**< HSE clock on MCO2 pin.     */
#define STM32_MCO2SEL_PLL       (3 << 30)   /**< PLL clock on MCO2 pin.     */

/* RCC_PLLI2SCFGR register bits definitions.*/
#define STM32_PLLI2SN_MASK      (511 << 6)  /**< PLLI2SN mask.              */
#define STM32_PLLI2SR_MASK      (7 << 28)   /**< PLLI2SR mask.              */

/* STM32F2xx capabilities.*/
#define STM32_HAS_ADC1          TRUE
#define STM32_HAS_ADC2          TRUE
#define STM32_HAS_ADC3          TRUE

#define STM32_HAS_CAN1          TRUE
#define STM32_HAS_CAN2          TRUE

#define STM32_HAS_DAC           TRUE

#define STM32_HAS_DMA1          TRUE
#define STM32_HAS_DMA2          TRUE

#define STM32_HAS_ETH           TRUE

#define STM32_EXTI_NUM_CHANNELS 23

#define STM32_HAS_GPIOA         TRUE
#define STM32_HAS_GPIOB         TRUE
#define STM32_HAS_GPIOC         TRUE
#define STM32_HAS_GPIOD         TRUE
#define STM32_HAS_GPIOE         TRUE
#define STM32_HAS_GPIOF         TRUE
#define STM32_HAS_GPIOG         TRUE
#define STM32_HAS_GPIOH         TRUE
#define STM32_HAS_GPIOI         TRUE

/* I2C attributes.*/
#define STM32_HAS_I2C1          TRUE
#define STM32_I2C1_RX_DMA_MSK ((STM32_DMA_STREAM_ID_MSK(1, 0) |             \
                               STM32_DMA_STREAM_ID_MSK(1, 5)))
#define STM32_I2C1_RX_DMA_CHN 0x00100001
#define STM32_I2C1_TX_DMA_MSK ((STM32_DMA_STREAM_ID_MSK(1, 7)) |            \
                              (STM32_DMA_STREAM_ID_MSK(1, 6)))
#define STM32_I2C1_TX_DMA_CHN 0x10000000

#define STM32_HAS_I2C2          TRUE
#define STM32_I2C2_RX_DMA_MSK ((STM32_DMA_STREAM_ID_MSK(1, 2) |             \
                               STM32_DMA_STREAM_ID_MSK(1, 3)))
#define STM32_I2C2_RX_DMA_CHN 0x00007700
#define STM32_I2C2_TX_DMA_MSK (STM32_DMA_STREAM_ID_MSK(1, 7))
#define STM32_I2C2_TX_DMA_CHN 0x70000000

#define STM32_HAS_I2C3          TRUE
#define STM32_I2C3_RX_DMA_MSK (STM32_DMA_STREAM_ID_MSK(1, 2))
#define STM32_I2C3_RX_DMA_CHN 0x00000300
#define STM32_I2C3_TX_DMA_MSK (STM32_DMA_STREAM_ID_MSK(1, 4))
#define STM32_I2C3_TX_DMA_CHN 0x00030000

#define STM32_HAS_RTC           TRUE
#define STM32_RTC_HAS_SUBSECONDS FALSE

#define STM32_HAS_SDIO          TRUE

#define STM32_HAS_SPI1          TRUE
#define STM32_HAS_SPI2          TRUE
#define STM32_HAS_SPI3          TRUE

#define STM32_HAS_TIM1          TRUE
#define STM32_HAS_TIM2          TRUE
#define STM32_HAS_TIM3          TRUE
#define STM32_HAS_TIM4          TRUE
#define STM32_HAS_TIM5          TRUE
#define STM32_HAS_TIM6          FALSE
#define STM32_HAS_TIM7          FALSE
#define STM32_HAS_TIM8          TRUE
#define STM32_HAS_TIM9          TRUE
#define STM32_HAS_TIM10         TRUE
#define STM32_HAS_TIM11         TRUE
#define STM32_HAS_TIM12         TRUE
#define STM32_HAS_TIM13         TRUE
#define STM32_HAS_TIM14         TRUE
#define STM32_HAS_TIM15         FALSE
#define STM32_HAS_TIM16         FALSE
#define STM32_HAS_TIM17         FALSE

#define STM32_HAS_USART1        TRUE
#define STM32_HAS_USART2        TRUE
#define STM32_HAS_USART3        TRUE
#define STM32_HAS_UART4         TRUE
#define STM32_HAS_UART5         TRUE
#define STM32_HAS_USART6        TRUE

#define STM32_HAS_USB           FALSE
#define STM32_HAS_OTG1          TRUE

/*===========================================================================*/
/* Platform specific friendly IRQ names.                                     */
/*===========================================================================*/

#define WWDG_IRQHandler         Vector40    /**< Window Watchdog.           */
#define PVD_IRQHandler          Vector44    /**< PVD through EXTI Line
                                                 detect.                    */
#define TAMPER_IRQHandler       Vector48    /**< Tamper.                    */
#define RTC_IRQHandler          Vector4C    /**< RTC.                       */
#define FLASH_IRQHandler        Vector50    /**< Flash.                     */
#define RCC_IRQHandler          Vector54    /**< RCC.                       */
#define EXTI0_IRQHandler        Vector58    /**< EXTI Line 0.               */
#define EXTI1_IRQHandler        Vector5C    /**< EXTI Line 1.               */
#define EXTI2_IRQHandler        Vector60    /**< EXTI Line 2.               */
#define EXTI3_IRQHandler        Vector64    /**< EXTI Line 3.               */
#define EXTI4_IRQHandler        Vector68    /**< EXTI Line 4.               */
#define DMA1_Stream0_IRQHandler Vector6C    /**< DMA1 Stream 0.             */
#define DMA1_Stream1_IRQHandler Vector70    /**< DMA1 Stream 1.             */
#define DMA1_Stream2_IRQHandler Vector74    /**< DMA1 Stream 2.             */
#define DMA1_Stream3_IRQHandler Vector78    /**< DMA1 Stream 3.             */
#define DMA1_Stream4_IRQHandler Vector7C    /**< DMA1 Stream 4.             */
#define DMA1_Stream5_IRQHandler Vector80    /**< DMA1 Stream 5.             */
#define DMA1_Stream6_IRQHandler Vector84    /**< DMA1 Stream 6.             */
#define ADC1_2_3_IRQHandler     Vector88    /**< ADC1, ADC2 and ADC3.       */
#define CAN1_TX_IRQHandler      Vector8C    /**< CAN1 TX.                   */
#define CAN1_RX0_IRQHandler     Vector90    /**< CAN1 RX0.                  */
#define CAN1_RX1_IRQHandler     Vector94    /**< CAN1 RX1.                  */
#define CAN1_SCE_IRQHandler     Vector98    /**< CAN1 SCE.                  */
#define EXTI9_5_IRQHandler      Vector9C    /**< EXTI Line 9..5.            */
#define TIM1_BRK_IRQHandler     VectorA0    /**< TIM1 Break.                */
#define TIM1_UP_IRQHandler      VectorA4    /**< TIM1 Update.               */
#define TIM1_TRG_COM_IRQHandler VectorA8    /**< TIM1 Trigger and
                                                 Commutation.               */
#define TIM1_CC_IRQHandler      VectorAC    /**< TIM1 Capture Compare.      */
#define TIM2_IRQHandler         VectorB0    /**< TIM2.                      */
#define TIM3_IRQHandler         VectorB4    /**< TIM3.                      */
#define TIM4_IRQHandler         VectorB8    /**< TIM4.                      */
#define I2C1_EV_IRQHandler      VectorBC    /**< I2C1 Event.                */
#define I2C1_ER_IRQHandler      VectorC0    /**< I2C1 Error.                */
#define I2C2_EV_IRQHandler      VectorC4    /**< I2C2 Event.                */
#define I2C2_ER_IRQHandler      VectorC8    /**< I2C1 Error.                */
#define SPI1_IRQHandler         VectorCC    /**< SPI1.                      */
#define SPI2_IRQHandler         VectorD0    /**< SPI2.                      */
#define USART1_IRQHandler       VectorD4    /**< USART1.                    */
#define USART2_IRQHandler       VectorD8    /**< USART2.                    */
#define USART3_IRQHandler       VectorDC    /**< USART3.                    */
#define EXTI15_10_IRQHandler    VectorE0    /**< EXTI Line 15..10.          */
#define RTC_Alarm_IRQHandler    VectorE4    /**< RTC alarm through EXTI
                                                 line.                      */
#define OTG_FS_WKUP_IRQHandler  VectorE8    /**< USB OTG FS Wakeup through
                                                 EXTI line.                 */
#define TIM8_BRK_IRQHandler     VectorEC    /**< TIM8 Break.                */
#define TIM8_UP_IRQHandler      VectorF0    /**< TIM8 Update.               */
#define TIM8_TRG_COM_IRQHandler VectorF4    /**< TIM8 Trigger and
                                                 Commutation.               */
#define TIM8_CC_IRQHandler      VectorF8    /**< TIM8 Capture Compare.      */
#define DMA1_Stream7_IRQHandler VectorFC    /**< DMA1 Stream 7.             */
#define FSMC_IRQHandler         Vector100   /**< FSMC.                      */
#define TIM5_IRQHandler         Vector108   /**< TIM5.                      */
#define SPI3_IRQHandler         Vector10C   /**< SPI3.                      */
#define UART4_IRQHandler        Vector110   /**< UART4.                     */
#define UART5_IRQHandler        Vector114   /**< UART5.                     */
#define TIM6_IRQHandler         Vector118   /**< TIM6.                      */
#define TIM7_IRQHandler         Vector11C   /**< TIM7.                      */
#define DMA2_Stream0_IRQHandler Vector120   /**< DMA2 Stream0.              */
#define DMA2_Stream1_IRQHandler Vector124   /**< DMA2 Stream1.              */
#define DMA2_Stream2_IRQHandler Vector128   /**< DMA2 Stream2.              */
#define DMA2_Stream3_IRQHandler Vector12C   /**< DMA2 Stream3.              */
#define DMA2_Stream4_IRQHandler Vector130   /**< DMA2 Stream4.              */
#define ETH_IRQHandler          Vector134   /**< Ethernet.                  */
#define ETH_WKUP_IRQHandler     Vector138   /**< Ethernet Wakeup through
                                                 EXTI line.                 */
#define CAN2_TX_IRQHandler      Vector13C   /**< CAN2 TX.                   */
#define CAN2_RX0_IRQHandler     Vector140   /**< CAN2 RX0.                  */
#define CAN2_RX1_IRQHandler     Vector144   /**< CAN2 RX1.                  */
#define CAN2_SCE_IRQHandler     Vector148   /**< CAN2 SCE.                  */
#define OTG_FS_IRQHandler       Vector14C   /**< USB OTG FS.                */
#define DMA2_Stream5_IRQHandler Vector150   /**< DMA2 Stream5.              */
#define DMA2_Stream6_IRQHandler Vector154   /**< DMA2 Stream6.              */
#define DMA2_Stream7_IRQHandler Vector158   /**< DMA2 Stream7.              */
#define USART6_IRQHandler       Vector15C   /**< USART6.                    */
#define I2C3_EV_IRQHandler      Vector160   /**< I2C3 Event.                */
#define I2C3_ER_IRQHandler      Vector164   /**< I2C3 Error.                */
#define OTG_HS_EP1_OUT_IRQHandler Vector168 /**< USB OTG HS End Point 1 Out.*/
#define OTG_HS_EP1_IN_IRQHandler Vector16C  /**< USB OTG HS End Point 1 In. */                                                 
#define OTG_HS_WKUP_IRQHandler  Vector170   /**< USB OTG HS Wakeup through
                                                 EXTI line.                 */
#define OTG_HS_IRQHandler       Vector174   /**< USB OTG HS.                */ 
#define DCMI_IRQHandler         Vector178   /**< DCMI.                      */ 
#define CRYP_IRQHandler         Vector17C   /**< CRYP.                      */ 
#define HASH_RNG_IRQHandler     Vector180   /**< Hash and Rng.              */ 

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   Disables the PWR/RCC initialization in the HAL.
 */
#if !defined(STM32_NO_INIT) || defined(__DOXYGEN__)
#define STM32_NO_INIT               FALSE
#endif

/**
 * @brief   Enables or disables the HSI clock source.
 */
#if !defined(STM32_HSI_ENABLED) || defined(__DOXYGEN__)
#define STM32_HSI_ENABLED           TRUE
#endif

/**
 * @brief   Enables or disables the LSI clock source.
 */
#if !defined(STM32_LSI_ENABLED) || defined(__DOXYGEN__)
#define STM32_LSI_ENABLED           FALSE
#endif

/**
 * @brief   Enables or disables the HSE clock source.
 */
#if !defined(STM32_HSE_ENABLED) || defined(__DOXYGEN__)
#define STM32_HSE_ENABLED           TRUE
#endif

/**
 * @brief   Enables or disables the LSE clock source.
 */
#if !defined(STM32_LSE_ENABLED) || defined(__DOXYGEN__)
#define STM32_LSE_ENABLED           FALSE
#endif

/**
 * @brief   ADC clock setting.
 */
#if !defined(STM32_ADC_CLOCK_ENABLED) || defined(__DOXYGEN__)
#define STM32_ADC_CLOCK_ENABLED     TRUE
#endif

/**
 * @brief   USB clock setting.
 */
#if !defined(STM32_USB_CLOCK_ENABLED) || defined(__DOXYGEN__)
#define STM32_USB_CLOCK_ENABLED     TRUE
#endif

/**
 * @brief   Main clock source selection.
 * @note    If the selected clock source is not the PLL then the PLL is not
 *          initialized and started.
 * @note    The default value is calculated for a 32MHz system clock from
 *          the internal 16MHz HSI clock.
 */
#if !defined(STM32_SW) || defined(__DOXYGEN__)
#define STM32_SW                    STM32_SW_PLL
#endif

/**
 * @brief   Clock source for the PLL.
 * @note    This setting has only effect if the PLL is selected as the
 *          system clock source.
 * @note    The default value is calculated for a 120MHz system clock from
 *          the external 25MHz HSE clock.
 */
#if !defined(STM32_PLLSRC) || defined(__DOXYGEN__)
#define STM32_PLLSRC                STM32_PLLSRC_HSE
#endif

/**
 * @brief   PLLM divider value.
 * @note    The allowed values are 2..63.
 * @note    The default value is calculated for a 120MHz system clock from
 *          an external 25MHz HSE clock.
 */
#if !defined(STM32_PLLM_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLM_VALUE          25
#endif

/**
 * @brief   PLLN multiplier value.
 * @note    The allowed values are 192..432.
 * @note    The default value is calculated for a 120MHz system clock from
 *          an external 25MHz HSE clock.
 */
#if !defined(STM32_PLLN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLN_VALUE          240
#endif

/**
 * @brief   PLLP multiplier value.
 * @note    The allowed values are DIV2, DIV4, DIV6, DIV8.
 * @note    The default value is calculated for a 120MHz system clock from
 *          an external 25MHz HSE clock.
 */
#if !defined(STM32_PLLP_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLP_VALUE          2
#endif

/**
 * @brief   PLLQ multiplier value.
 * @note    The allowed values are 4..15.
 * @note    The default value is calculated for a 120MHz system clock from
 *          an external 25MHz HSE clock.
 */
#if !defined(STM32_PLLQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLQ_VALUE          5
#endif

/**
 * @brief   AHB prescaler value.
 * @note    The default value is calculated for a 120MHz system clock from
 *          an external 25MHz HSE clock.
 */
#if !defined(STM32_HPRE) || defined(__DOXYGEN__)
#define STM32_HPRE                  STM32_HPRE_DIV1
#endif

/**
 * @brief   APB1 prescaler value.
 */
#if !defined(STM32_PPRE1) || defined(__DOXYGEN__)
#define STM32_PPRE1                 STM32_PPRE1_DIV4
#endif

/**
 * @brief   APB2 prescaler value.
 */
#if !defined(STM32_PPRE2) || defined(__DOXYGEN__)
#define STM32_PPRE2                 STM32_PPRE2_DIV2
#endif

/**
 * @brief   RTC prescaler value.
 */
#if !defined(STM32_RTCPRE_VALUE) || defined(__DOXYGEN__)
#define STM32_RTCPRE_VALUE          25
#endif

/**
 * @brief   MC01 clock source value.
 * @note    The default value outputs HSI clock on MC01 pin.
 */
#if !defined(STM32_MCO1SEL) || defined(__DOXYGEN__)
#define STM32_MCO1SEL               STM32_MCO1SEL_HSI
#endif

/**
 * @brief   MC01 prescaler value.
 * @note    The default value outputs HSI clock on MC01 pin.
 */
#if !defined(STM32_MCO1PRE) || defined(__DOXYGEN__)
#define STM32_MCO1PRE               STM32_MCO1PRE_DIV1
#endif

/**
 * @brief   MC02 clock source value.
 * @note    The default value outputs SYSCLK / 5 on MC02 pin.
 */
#if !defined(STM32_MCO2SEL) || defined(__DOXYGEN__)
#define STM32_MCO2SEL               STM32_MCO2SEL_SYSCLK
#endif

/**
 * @brief   MC02 prescaler value.
 * @note    The default value outputs SYSCLK / 5 on MC02 pin.
 */
#if !defined(STM32_MCO2PRE) || defined(__DOXYGEN__)
#define STM32_MCO2PRE               STM32_MCO2PRE_DIV5
#endif

/**
 * @brief   PLLI2SN multiplier value.
 * @note    The allowed values are 192..432.
 * @note    The default value is calculated for a 48000 I2S clock with
 *          I2SDIV = 12 and I2SODD = 1.
 */
#if !defined(STM32_PLLI2SN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLI2SN_VALUE         384
#endif

/**
 * @brief   PLLI2SR multiplier value.
 * @note    The allowed values are 2..7.
 * @note    The default value is calculated for a 48000 I2S clock with
 *          I2SDIV = 12 and I2SODD = 1.
 */
#if !defined(STM32_PLLI2SP_VALUE) || defined(__DOXYGEN__)
#define STM32_PLI2SLP_VALUE         5
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/**
 * @brief   Maximum HSECLK.
 */
#define STM32_HSECLK_MAX            32000000

/**
 * @brief   Maximum SYSCLK.
 */
#define STM32_SYSCLK_MAX            120000000

/**
 * @brief   Maximum frequency thresholds and wait states for flash access.
 * @note    The values are valid for 2.7V to 3.6V supply range.
 */
#define STM32_0WS_THRESHOLD         30000000
#define STM32_1WS_THRESHOLD         60000000
#define STM32_2WS_THRESHOLD         90000000
#define STM32_3WS_THRESHOLD         0
#define STM32_4WS_THRESHOLD         0
#define STM32_5WS_THRESHOLD         0
#define STM32_6WS_THRESHOLD         0
#define STM32_7WS_THRESHOLD         0

/* HSI related checks.*/
#if STM32_HSI_ENABLED
#else /* !STM32_HSI_ENABLED */
#if STM32_ADC_CLOCK_ENABLED ||                                              \
    (STM32_SW == STM32_SW_HSI) ||                                           \
    ((STM32_SW == STM32_SW_PLL) &&                                          \
     (STM32_PLLSRC == STM32_PLLSRC_HSI)) ||                                 \
    (STM32_MCO1SEL == STM32_MCO1SEL_HSI) ||                                 \
    ((STM32_MCO1SEL == STM32_MCO1SEL_PLL) &&                                \
     (STM32_PLLSRC == STM32_PLLSRC_HSI))
#error "required HSI clock is not enabled"
#endif
#endif /* !STM32_HSI_ENABLED */

/* HSE related checks.*/
#if STM32_HSE_ENABLED
#if STM32_HSECLK == 0
#error "impossible to activate HSE"
#endif
#if (STM32_HSECLK < 1000000) || (STM32_HSECLK > STM32_HSECLK_MAX)
#error "STM32_HSECLK outside acceptable range (1MHz...STM32_HSECLK_MAX)"
#endif
#else /* !STM32_HSE_ENABLED */
#if (STM32_SW == STM32_SW_HSE) ||                                           \
    ((STM32_SW == STM32_SW_PLL) &&                                          \
     (STM32_PLLSRC == STM32_PLLSRC_HSE)) ||                                 \
    (STM32_MCO1SEL == STM32_MCO1SEL_HSE) ||                                 \
    ((STM32_MCO1SEL == STM32_MCO1SEL_PLL) &&                                \
     (STM32_PLLSRC == STM32_PLLSRC_HSE)) ||                                 \
    (STM32_MCO2SEL == STM32_MCO2SEL_HSE) ||                                 \
    ((STM32_MCO2SEL == STM32_MCO2SEL_PLL) &&                                \
     (STM32_PLLSRC == STM32_PLLSRC_HSE)) ||                                 \
    (STM_RTC_SOURCE == STM32_RTCSEL_HSEDIV)
#error "required HSE clock is not enabled"
#endif
#endif /* !STM32_HSE_ENABLED */

/* LSI related checks.*/
#if STM32_LSI_ENABLED
#else /* !STM32_LSI_ENABLED */
#if STM_RTCCLK == STM32_LSICLK
#error "required LSI clock is not enabled"
#endif
#endif /* !STM32_LSI_ENABLED */

/* LSE related checks.*/
#if STM32_LSE_ENABLED
#if (STM32_LSECLK == 0)
#error "impossible to activate LSE"
#endif
#if (STM32_LSECLK < 1000) || (STM32_LSECLK > 1000000)
#error "STM32_LSECLK outside acceptable range (1...1000KHz)"
#endif
#else /* !#if STM32_LSE_ENABLED */
#if STM_RTCCLK == STM32_LSECLK
#error "required LSE clock is not enabled"
#endif
#endif /* !#if STM32_LSE_ENABLED */

/* PLL related checks.*/
#if STM32_USB_CLOCK_ENABLED ||                                              \
    (STM32_SW == STM32_SW_PLL) ||                                           \
    (STM32_MCO1SEL == STM32_MCO1SEL_PLL) ||                                 \
    (STM32_MCO2SEL == STM32_MCO2SEL_PLL) ||                                 \
    defined(__DOXYGEN__)
/**
 * @brief   PLL activation flag.
 */
#define STM32_ACTIVATE_PLL          TRUE
#else
#define STM32_ACTIVATE_PLL          FALSE
#endif

/**
 * @brief   STM32_PLLM field.
 */
#if ((STM32_PLLM_VALUE >= 2) && (STM32_PLLM_VALUE <= 63)) ||                \
    defined(__DOXYGEN__)
#define STM32_PLLM                  STM32_PLLM_VALUE
#else
#error "invalid STM32_PLLM_VALUE value specified"
#endif

/**
 * @brief   STM32_PLLN field.
 */
#if ((STM32_PLLN_VALUE >= 192) && (STM32_PLLN_VALUE <= 432)) ||             \
    defined(__DOXYGEN__)
#define STM32_PLLN                  (STM32_PLLN_VALUE << 6)
#else
#error "invalid STM32_PLLN_VALUE value specified"
#endif

/**
 * @brief   STM32_PLLP field.
 */
#if (STM32_PLLP_VALUE == 2) || defined(__DOXYGEN__)
#define STM32_PLLP                  (0 << 16)
#elif STM32_PLLP_VALUE == 4
#define STM32_PLLP                  (1 << 16)
#elif STM32_PLLP_VALUE == 6
#define STM32_PLLP                  (2 << 16)
#elif STM32_PLLP_VALUE == 8
#define STM32_PLLP                  (3 << 16)
#else
#error "invalid STM32_PLLP_VALUE value specified"
#endif

/**
 * @brief   STM32_PLLQ field.
 */
#if ((STM32_PLLQ_VALUE >= 4) && (STM32_PLLQ_VALUE <= 15)) || \
    defined(__DOXYGEN__)
#define STM32_PLLQ                  (STM32_PLLQ_VALUE << 24)
#else
#error "invalid STM32_PLLQ_VALUE value specified"
#endif

/**
 * @brief   PLL input clock frequency.
 */
#if (STM32_PLLSRC == STM32_PLLSRC_HSE) || defined(__DOXYGEN__)
#define STM32_PLLCLKIN              STM32_HSECLK
#elif STM32_PLLSRC == STM32_PLLSRC_HSI
#define STM32_PLLCLKIN              STM32_HSICLK
#else
#error "invalid STM32_PLLSRC value specified"
#endif

/* PLL input frequency range check.*/
#if (STM32_PLLCLKIN < 4000000) || (STM32_PLLCLKIN > 26000000)
#error "STM32_PLLCLKIN outside acceptable range (4...26MHz)"
#endif

/**
 * @brief   PLL VCO frequency.
 */
#define STM32_PLLVCO              ((STM32_PLLCLKIN / STM32_PLLM_VALUE) *    \
                                    STM32_PLLN_VALUE)

/* PLL output frequency range check.*/
#if (STM32_PLLVCO < 192000000) || (STM32_PLLVCO > 432000000)
#error STM32_PLLVCO
#error "STM32_PLLVCO outside acceptable range (192...432MHz)"
#endif

/**
 * @brief   PLL output clock frequency.
 */
#define STM32_PLLCLKOUT             (STM32_PLLVCO / STM32_PLLP_VALUE)

/* PLL output frequency range check.*/
#if (STM32_PLLCLKOUT < 24000000) || (STM32_PLLCLKOUT > 120000000)
#error "STM32_PLLCLKOUT outside acceptable range (24...120MHz)"
#endif

/**
 * @brief   System clock source.
 */
#if STM32_NO_INIT || defined(__DOXYGEN__)
#define STM32_SYSCLK                96000000
#elif (STM32_SW == STM32_SW_HSI)
#define STM32_SYSCLK                STM32_HSICLK
#elif (STM32_SW == STM32_SW_HSE)
#define STM32_SYSCLK                STM32_HSECLK
#elif (STM32_SW == STM32_SW_PLL)
#define STM32_SYSCLK                STM32_PLLCLKOUT
#else
#error "invalid STM32_SW value specified"
#endif

/* Check on the system clock.*/
#if STM32_SYSCLK > STM32_SYSCLK_MAX
#error "STM32_SYSCLK above maximum rated frequency (STM32_SYSCLK_MAX)"
#endif

/**
 * @brief   AHB frequency.
 */
#if (STM32_HPRE == STM32_HPRE_DIV1) || defined(__DOXYGEN__)
#define STM32_HCLK                  (STM32_SYSCLK / 1)
#elif STM32_HPRE == STM32_HPRE_DIV2
#define STM32_HCLK                  (STM32_SYSCLK / 2)
#elif STM32_HPRE == STM32_HPRE_DIV4
#define STM32_HCLK                  (STM32_SYSCLK / 4)
#elif STM32_HPRE == STM32_HPRE_DIV8
#define STM32_HCLK                  (STM32_SYSCLK / 8)
#elif STM32_HPRE == STM32_HPRE_DIV16
#define STM32_HCLK                  (STM32_SYSCLK / 16)
#elif STM32_HPRE == STM32_HPRE_DIV64
#define STM32_HCLK                  (STM32_SYSCLK / 64)
#elif STM32_HPRE == STM32_HPRE_DIV128
#define STM32_HCLK                  (STM32_SYSCLK / 128)
#elif STM32_HPRE == STM32_HPRE_DIV256
#define STM32_HCLK                  (STM32_SYSCLK / 256)
#elif STM32_HPRE == STM32_HPRE_DIV512
#define STM32_HCLK                  (STM32_SYSCLK / 512)
#else
#error "invalid STM32_HPRE value specified"
#endif

/* AHB frequency check.*/
#if STM32_HCLK > STM32_SYSCLK_MAX
#error "STM32_HCLK exceeding maximum frequency (STM32_SYSCLK_MAX)"
#endif

/**
 * @brief   APB1 frequency.
 */
#if (STM32_PPRE1 == STM32_PPRE1_DIV1) || defined(__DOXYGEN__)
#define STM32_PCLK1                 (STM32_HCLK / 1)
#elif STM32_PPRE1 == STM32_PPRE1_DIV2
#define STM32_PCLK1                 (STM32_HCLK / 2)
#elif STM32_PPRE1 == STM32_PPRE1_DIV4
#define STM32_PCLK1                 (STM32_HCLK / 4)
#elif STM32_PPRE1 == STM32_PPRE1_DIV8
#define STM32_PCLK1                 (STM32_HCLK / 8)
#elif STM32_PPRE1 == STM32_PPRE1_DIV16
#define STM32_PCLK1                 (STM32_HCLK / 16)
#else
#error "invalid STM32_PPRE1 value specified"
#endif

/* APB1 frequency check.*/
#if STM32_PCLK2 > STM32_SYSCLK_MAX
#error "STM32_PCLK1 exceeding maximum frequency (STM32_SYSCLK_MAX)"
#endif

/**
 * @brief   APB2 frequency.
 */
#if (STM32_PPRE2 == STM32_PPRE2_DIV1) || defined(__DOXYGEN__)
#define STM32_PCLK2                 (STM32_HCLK / 1)
#elif STM32_PPRE2 == STM32_PPRE2_DIV2
#define STM32_PCLK2                 (STM32_HCLK / 2)
#elif STM32_PPRE2 == STM32_PPRE2_DIV4
#define STM32_PCLK2                 (STM32_HCLK / 4)
#elif STM32_PPRE2 == STM32_PPRE2_DIV8
#define STM32_PCLK2                 (STM32_HCLK / 8)
#elif STM32_PPRE2 == STM32_PPRE2_DIV16
#define STM32_PCLK2                 (STM32_HCLK / 16)
#else
#error "invalid STM32_PPRE2 value specified"
#endif

/* APB2 frequency check.*/
#if STM32_PCLK2 > STM32_SYSCLK_MAX
#error "STM32_PCLK2 exceeding maximum frequency (STM32_SYSCLK_MAX)"
#endif

/**
 * @brief   RTC frequency.
 */
#if ((STM32_RTCPRE_VALUE >= 2) && (STM32_RTCPRE_VALUE <= 31)) ||             \
    defined(__DOXYGEN__)
#define STM32_RTCPRE                  (STM32_RTCPRE_VALUE << 16)
#else
#error "invalid STM32_RTCPRE value specified"
#endif

/**
 * @brief   MCO1 divider clock.
 */
#if (STM32_MCO1SEL == STM32_MCO1SEL_HSI) || defined(__DOXYGEN__)
#define STM_MCO1DIVCLK               STM32_HSICLK
#elif STM32_MCO1SEL == STM32_MCO1SEL_LSE
#define STM_MCO1DIVCLK               STM32_LSECLK
#elif STM32_MCO1SEL == STM32_MCO1SEL_HSE
#define STM_MCO1DIVCLK               STM32_HSECLK
#elif STM32_MCO1SEL == STM32_MCO1SEL_PLL
#define STM_MCO1DIVCLK               STM32_PLLCLKOUT
#else
#error "invalid STM32_MCO1SEL value specified"
#endif

/**
 * @brief   MCO1 output pin clock.
 */
#if (STM32_MCO1PRE == STM32_MCO1PRE_DIV1) || defined(__DOXYGEN__)
#define STM_MCO1CLK                  STM_MCO1DIVCLK
#elif STM32_MCO1PRE == STM32_MCO1PRE_DIV2
#define STM_MCO1CLK                  (STM_MCO1DIVCLK / 2)
#elif STM32_MCO1PRE == STM32_MCO1PRE_DIV3
#define STM_MCO1CLK                  (STM_MCO1DIVCLK / 3)
#elif STM32_MCO1PRE == STM32_MCO1PRE_DIV4
#define STM_MCO1CLK                  (STM_MCO1DIVCLK / 4)
#elif STM32_MCO1PRE == STM32_MCO1PRE_DIV5
#define STM_MCO1CLK                  (STM_MCO1DIVCLK / 5)
#else
#error "invalid STM32_MCO1PRE value specified"
#endif

/**
 * @brief   MCO2 divider clock.
 */
#if (STM32_MCO2SEL == STM32_MCO2SEL_HSE) || defined(__DOXYGEN__)
#define STM_MCO2DIVCLK               STM32_HSECLK
#elif STM32_MCO2SEL == STM32_MCO2SEL_PLL
#define STM_MCO2DIVCLK               STM32_PLLCLKOUT
#elif STM32_MCO2SEL == STM32_MCO2SEL_SYSCLK
#define STM_MCO2DIVCLK               STM32_SYSCLK
#elif STM32_MCO2SEL == STM32_MCO2SEL_PLLI2S
#define STM_MCO2DIVCLK               STM32_PLLI2S

#else
#error "invalid STM32_MCO2SEL value specified"
#endif

/**
 * @brief   MCO2 output pin clock.
 */
#if (STM32_MCO2PRE == STM32_MCO2PRE_DIV1) || defined(__DOXYGEN__)
#define STM_MCO2CLK                  STM_MCO2DIVCLK
#elif STM32_MCO2PRE == STM32_MCO2PRE_DIV2
#define STM_MCO2CLK                  (STM_MCO2DIVCLK / 2)
#elif STM32_MCO2PRE == STM32_MCO2PRE_DIV3
#define STM_MCO2CLK                  (STM_MCO2DIVCLK / 3)
#elif STM32_MCO2PRE == STM32_MCO2PRE_DIV4
#define STM_MCO2CLK                  (STM_MCO2DIVCLK / 4)
#elif STM32_MCO2PRE == STM32_MCO2PRE_DIV5
#define STM_MCO2CLK                  (STM_MCO2DIVCLK / 5)
#else
#error "invalid STM32_MCO2PRE value specified"
#endif

/**
 * @brief   HSE divider toward RTC clock.
 */
#if ((STM32_RTCPRE_VALUE >= 2) && (STM32_RTCPRE_VALUE <= 31))  ||                 \
    defined(__DOXYGEN__)
#define STM32_HSEDIVCLK             (HSECLK / STM32_RTCPRE_VALUE)
#else
#error "invalid STM32_RTCPRE value specified"
#endif

/**
 * @brief   RTC clock.
 */
#if (STM32_RTCSEL == STM32_RTCSEL_NOCLOCK) || defined(__DOXYGEN__)
#define STM_RTCCLK                  0
#elif STM32_RTCSEL == STM32_RTCSEL_LSE
#define STM_RTCCLK                  STM32_LSECLK
#elif STM32_RTCSEL == STM32_RTCSEL_LSI
#define STM_RTCCLK                  STM32_LSICLK
#elif STM32_RTCSEL == STM32_RTCSEL_HSEDIV
#define STM_RTCCLK                  STM32_HSEDIVCLK
#else
#error "invalid STM32_RTCSEL value specified"
#endif

/**
 * @brief   ADC frequency.
 */
#if (STM32_ADCPRE == STM32_ADCPRE_DIV2) || defined(__DOXYGEN__)
#define STM32_ADCCLK                (STM32_PCLK2 / 2)
#elif STM32_ADCPRE == STM32_ADCPRE_DIV4
#define STM32_ADCCLK                (STM32_PCLK2 / 4)
#elif STM32_ADCPRE == STM32_ADCPRE_DIV6
#define STM32_ADCCLK                (STM32_PCLK2 / 6)
#elif STM32_ADCPRE == STM32_ADCPRE_DIV8
#define STM32_ADCCLK                (STM32_PCLK2 / 8)
#else
#error "invalid STM32_ADCPRE value specified"
#endif

/* ADC frequency check.*/
#if STM32_ADCCLK > 30000000
#error "STM32_ADCCLK exceeding maximum frequency (30MHz)"
#endif

/**
 * @brief   OTG frequency.
 */
#if (STM32_OTGFSPRE == STM32_OTGFSPRE_DIV3) || defined(__DOXYGEN__)
#define STM32_OTGFSCLK              (STM32_PLLVCO / 3)
#elif (STM32_OTGFSPRE == STM32_OTGFSPRE_DIV2)
#define STM32_OTGFSCLK              (STM32_PLLVCO / 2)
#else
#error "invalid STM32_OTGFSPRE value specified"
#endif

/**
 * @brief   Timers 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14 clock.
 */
#if (STM32_PPRE1 == STM32_PPRE1_DIV1) || defined(__DOXYGEN__)
#define STM32_TIMCLK1               (STM32_PCLK1 * 1)
#else
#define STM32_TIMCLK1               (STM32_PCLK1 * 2)
#endif

/**
 * @brief   Timers 1, 8 clock.
 */
#if (STM32_PPRE2 == STM32_PPRE2_DIV1) || defined(__DOXYGEN__)
#define STM32_TIMCLK2               (STM32_PCLK2 * 1)
#else
#define STM32_TIMCLK2               (STM32_PCLK2 * 2)
#endif

/**
 * @brief   Flash settings.
 */
#if (STM32_HCLK <= STM32_0WS_THRESHOLD) || defined(__DOXYGEN__)
#define STM32_FLASHBITS             0x00000000
#elif STM32_HCLK <= STM32_1WS_THRESHOLD
#define STM32_FLASHBITS             0x00000001
#elif STM32_HCLK <= STM32_2WS_THRESHOLD
#define STM32_FLASHBITS             0x00000002
#elif STM32_HCLK <= STM32_3WS_THRESHOLD
#define STM32_FLASHBITS             0x00000003
#elif STM32_HCLK <= STM32_4WS_THRESHOLD
#define STM32_FLASHBITS             0x00000004
#elif STM32_HCLK <= STM32_5WS_THRESHOLD
#define STM32_FLASHBITS             0x00000005
#elif STM32_HCLK <= STM32_6WS_THRESHOLD
#define STM32_FLASHBITS             0x00000006
#else
#define STM32_FLASHBITS             0x00000007
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/* STM32 DMA support code.*/
//#include "stm32_dma.h"

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void stm32_clock_init(void);
#ifdef __cplusplus
}
#endif

#endif /* _HAL_LLD_H_ */

/** @} */