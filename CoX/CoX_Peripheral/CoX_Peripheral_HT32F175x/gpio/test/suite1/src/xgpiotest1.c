//*****************************************************************************
//
//! @page xgpio_testcase xgpio register test
//!
//! File: @ref xgpiotest.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xgpio sub component.<br><br>
//! - \p Board: HT32F175x/275x Development Board<br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xgpio_register
//! .
//! \file xgpiotest1.c
//! \brief xgpio test source file
//! \brief xgpio test header file <br>
//
//*****************************************************************************

#include "test.h"

//*****************************************************************************
//
//!\page test_xgpio_register test_xgpio_register
//!
//!<h2>Description</h2>
//!Test xgpio register. <br>
//!
//
//*****************************************************************************


//
// GPIO base value
//
static unsigned long ulGPIO[5] = {xGPIO_PORTA_BASE,xGPIO_PORTB_BASE,
                                  xGPIO_PORTC_BASE,xGPIO_PORTD_BASE,
								  xGPIO_PORTE_BASE};

//
// GPIO bit packed pin
//
static unsigned long ulPackedPin[16] = {xGPIO_PIN_0, xGPIO_PIN_1, xGPIO_PIN_2,
                                       xGPIO_PIN_3, xGPIO_PIN_4, xGPIO_PIN_5,
                                       xGPIO_PIN_6, xGPIO_PIN_7, xGPIO_PIN_8,
									   xGPIO_PIN_9, xGPIO_PIN_10, xGPIO_PIN_11,
                                       xGPIO_PIN_12, xGPIO_PIN_13, xGPIO_PIN_14,
                                       xGPIO_PIN_15};

//
// GPIO Pin Mode
//
static unsigned long ulPinMode[4] = {xGPIO_DIR_MODE_IN, xGPIO_DIR_MODE_OUT, 
                                     xGPIO_DIR_MODE_OD};

//
// GPIO interrupt type 
//
static unsigned long ulIntTypes[5] = {xGPIO_FALLING_EDGE, xGPIO_RISING_EDGE,
                                     xGPIO_BOTH_EDGES,    xGPIO_LOW_LEVEL, 
									 xGPIO_HIGH_LEVEL};

//
// EXTI lines 
//
static unsigned long ulEXTILines[3] = {EXTI_LINE_0, EXTI_LINE_8, EXTI_LINE_15};
static unsigned long ulEXTILineShift[3] = {0, 8, 15};
static unsigned long ulDeBounceTime[3] = {1, 1000, 1000000};

//
// EXTI wake up INT configure 
//
static unsigned long ulEXTIWakeUpInt[2] = {EXTI_WAKEUP_INT_ENABLE, 
                                           EXTI_WAKEUP_INT_DISABLE};

//
// EXTI lines wake up enable
//
static unsigned long ulEXTIWakeUp[2] = {EXTI_LINES_WAKEUP_ENABLE,
                                        EXTI_LINES_WAKEUP_DISABLE};

//
// EXTI wake up level
//
static unsigned long ulEXTIWakeUpLevel[2] = {EXTI_LINE_WAKEUP_LOW, 
                                             EXTI_LINE_WAKEUP_HIGH};

//
// GPIO pin
//
static unsigned long ulPinValue[3] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2};

//
// GPIO Pad configure
//
static unsigned long ulOpenDrain[2] = {GPIO_DIR_MODE_OD_EN, 
                                       GPIO_DIR_MODE_OD_DIS};
static unsigned long ulPullResistor[3] = {GPIO_PIN_TYPE_STD_WPU, 
                                          GPIO_PIN_TYPE_STD_WPD, 
										  GPIO_PR_DISABLE}; 
static unsigned long ulStrengthValue[2] = {GPIO_STRENGTH_4MA, 
                                           GPIO_STRENGTH_8MA};


//*****************************************************************************
//
//! \brief Get the Test description of xgpio001 register test.
//!
//! \return the desccription of the xgpio001 test.
//
//*****************************************************************************
const char* xgpio001GetTest(void)
{
    static const char * const pcName = "xgpio, 001, gpio register test";
    return pcName;
}

//*****************************************************************************
//
//! \brief Something should do before the test execute of xgpio001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001Setup(void)
{
    //xSysCtlClockSet(8000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
	xSysCtlPeripheralEnable(SYSCTL_PERIPH_EXTI);
}

//*****************************************************************************
//
//! \brief Something should do after the test execute of xgpio001 test.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001TearDown(void)
{
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOA);
	xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOB);
	xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOC);
	xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOD);
	xSysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOE);
	xSysCtlPeripheralDisable(SYSCTL_PERIPH_AFIO);
    xSysCtlPeripheralDisable(SYSCTL_PERIPH_EXTI);
}

//*****************************************************************************
//
//! \brief xgpio001 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xgpio001Execute(void)
{
   
    unsigned long ulPin, ulPort;
    unsigned long ulvalue, ulTemp;  
    int i, j;

    //
    // GPIOA PIN mode test
    //
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");      
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTA_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTA_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioA, \" GPIODirModeSet or GPIODirModeGet()\" error"); 
    
    //
    // GPIOB pin mode test
    //
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioB, \" GPIODirModeSet or GPIODirModeGet()\" error");      
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioB, \" GPIODirModeSet or GPIODirModeGet()\" error");     
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioB, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTB_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTB_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioB, \" GPIODirModeSet or GPIODirModeGet()\" error");
	
    //
    // GPIOC pin mode test
    //			   
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTC_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTC_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    //
    // GPIOD pin mode test
    //			   			      
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTD_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTD_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
	
    //
    // GPIOE pin mode test
    //			       
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_0) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_0, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_0) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_IN);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_4) ;  
    TestAssert((ulvalue == xGPIO_DIR_MODE_IN), 
                "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
    xGPIODirModeSet(xGPIO_PORTE_BASE, xGPIO_PIN_4, xGPIO_DIR_MODE_OUT);
    ulvalue = xGPIODirModeGet(xGPIO_PORTE_BASE, xGPIO_PIN_4) ;    
    TestAssert((ulvalue == xGPIO_DIR_MODE_OUT), 
               "xgpioC, \" GPIODirModeSet or GPIODirModeGet()\" error");
       
    xIntDisable(xINT_GPIOA);
    xIntDisable(xINT_GPIOB);
    xIntDisable(xINT_GPIOC);
    xIntDisable(xINT_GPIOD);
    xIntDisable(xINT_GPIOE);
 
/*    
    //
    // GPIOA int enable test
    //
    for(i = 0; i < 5; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTA_BASE, xGPIO_PIN_0, ulIntTypes[i]);
        ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0) & EXTI_CFGR0_SRCTYPE_M;
        TestAssert(ulTemp == ulIntTypes[i],
                   "xgpio, \"xGPIOPinIntEnable \" error");
        ulTemp =  xHWREG(GPIO_AFIO_BASE + AFIO_ESSRO) & AFIO_ESSR0_EXTINPIN_M;
        TestAssert(ulTemp == 0,
                   "xgpio, \"xGPIOPinIntEnable \" error");
	    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_ICR) & 0x00000001;
        TestAssert(ulTemp == 0x00000001,
                   "xgpio, \"xGPIOPinIntEnable \" error");
    }
    
    //
    // GPIOB int enable test
    //
    for(i = 0; i < 5; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTB_BASE, xGPIO_PIN_9, ulIntTypes[i]);
        ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + 9*4) & EXTI_CFGR0_SRCTYPE_M;
        TestAssert(ulTemp == ulIntTypes[i],
                   "xgpio, \"xGPIOPinIntEnable \" error");  
        ulTemp =  xHWREG(GPIO_AFIO_BASE + AFIO_ESSR1) & (AFIO_ESSR0_EXTINPIN_M << 4);
        TestAssert(ulTemp == (1 << 4),
                   "xgpio, \"xGPIOPinIntEnable \" error");
	    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_ICR) & (0x00000001 << 9);
        TestAssert(ulTemp == (0x00000001 << 9),
                   "xgpio, \"xGPIOPinIntEnable \" error");
    }    

    //
    // GPIOC int enable test
    //
    for(i = 0; i < 5; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTC_BASE, xGPIO_PIN_1, ulIntTypes[i]);
        ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + 4) & EXTI_CFGR0_SRCTYPE_M;
        TestAssert(ulTemp == ulIntTypes[i],
                   "xgpio, \"xGPIOPinIntEnable \" error");
        ulTemp =  xHWREG(GPIO_AFIO_BASE + AFIO_ESSRO) & (AFIO_ESSR0_EXTINPIN_M << 4);
        TestAssert(ulTemp == 2 << 4,
                   "xgpio, \"xGPIOPinIntEnable \" error");
	    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_ICR) & 0x00000002;
        TestAssert(ulTemp == 0x00000002,
                   "xgpio, \"xGPIOPinIntEnable \" error");
    }

    //
    // GPIOD int enable test
    //
    for(i = 0; i < 5; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTD_BASE, xGPIO_PIN_9, ulIntTypes[i]);
        ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + 9*4) & EXTI_CFGR0_SRCTYPE_M;
        TestAssert(ulTemp == ulIntTypes[i],
                   "xgpio, \"xGPIOPinIntEnable \" error");  
        ulTemp =  xHWREG(GPIO_AFIO_BASE + AFIO_ESSR1) & (AFIO_ESSR0_EXTINPIN_M << 4);
        TestAssert(ulTemp == (3 << 4),
                   "xgpio, \"xGPIOPinIntEnable \" error");
	    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_ICR) & (0x00000001 << 9);
        TestAssert(ulTemp == (0x00000001 << 9),
                   "xgpio, \"xGPIOPinIntEnable \" error");
    }

    //
    // GPIOE int enable test
    //
    for(i = 0; i < 5; i++)
    {
        xGPIOPinIntEnable(xGPIO_PORTE_BASE, xGPIO_PIN_10, ulIntTypes[i]);
        ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0 + 10*4) & EXTI_CFGR0_SRCTYPE_M;
        TestAssert(ulTemp == ulIntTypes[i],
                   "xgpio, \"xGPIOPinIntEnable \" error");  
        ulTemp =  xHWREG(GPIO_AFIO_BASE + AFIO_ESSR1) & (AFIO_ESSR0_EXTINPIN_M << 8);
        TestAssert(ulTemp == (4 << 8),
                   "xgpio, \"xGPIOPinIntEnable \" error");
	    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_ICR) & (0x00000001 << 10);
        TestAssert(ulTemp == (0x00000001 << 10),
                   "xgpio, \"xGPIOPinIntEnable \" error");
    } 	 
*/	 
    //
	// Int Disable test
	//
    for(ulPin = 0; ulPin < 16; ulPin++)
    {
        xGPIOPinIntDisable(GPIO_AFIO_BASE, ulPackedPin[ulPin]);
	    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_ICR) & (0x00000001 << ulPin);
        TestAssert(ulTemp == 0,
                   "xgpio, \"Interrupt disable test \" error"); 
    }
 
    //
    // GPIOA out/in test
    //
    xGPIODirModeSet( xGPIO_PORTA_BASE, xGPIO_PIN_0, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTA_BASE, xGPIO_PIN_0, 1);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTA_BASE);
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"Output pin value set \" error");   

    xGPIOPinWrite(xGPIO_PORTA_BASE, xGPIO_PIN_0, 0);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTA_BASE);
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error");  
    
    //
    // GPIOB out/in test
    //
    xGPIODirModeSet( xGPIO_PORTB_BASE, xGPIO_PIN_2, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTB_BASE, xGPIO_PIN_2, 1);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTB_BASE) & xGPIO_PIN_2;
    TestAssert(ulTemp == xGPIO_PIN_2,
               "xgpio, \"Output pin value set \" error");

    xGPIOPinWrite(xGPIO_PORTB_BASE, xGPIO_PIN_2, 0);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTB_BASE) & xGPIO_PIN_2;
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error");

    GPIOPortWrite(xGPIO_PORTB_BASE, 0x00000004);
	ulTemp = GPIOPinPortDoutGet(xGPIO_PORTB_BASE) & xGPIO_PIN_2;
    TestAssert(ulTemp == 0x00000004,
               "xgpio, \"Output port value set \" error");
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
	ulTemp = GPIOPinPortDoutGet(xGPIO_PORTB_BASE) & xGPIO_PIN_2;
    TestAssert(ulTemp == 0,
               "xgpio, \"Output port value set2 \" error");

    //
    // GPIOC out/in test
    //
    xGPIODirModeSet( xGPIO_PORTC_BASE, xGPIO_PIN_0, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTC_BASE, xGPIO_PIN_0, 1);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTC_BASE);
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"Output pin value set \" error");   

    xGPIOPinWrite(xGPIO_PORTC_BASE, xGPIO_PIN_0, 0);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTC_BASE);
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error"); 

    //
    // GPIOD out/in test
    //
    xGPIODirModeSet( xGPIO_PORTD_BASE, xGPIO_PIN_0, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTD_BASE, xGPIO_PIN_0, 1);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTD_BASE);
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"Output pin value set \" error");   

    xGPIOPinWrite(xGPIO_PORTD_BASE, xGPIO_PIN_0, 0);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTD_BASE);
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error"); 

    //
    // GPIOE out/in test
    //
    xGPIODirModeSet( xGPIO_PORTE_BASE, xGPIO_PIN_0, GPIO_DIR_MODE_OUT );
    xGPIOPinWrite(xGPIO_PORTE_BASE, xGPIO_PIN_0, 1);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTE_BASE);
    TestAssert(ulTemp == xGPIO_PIN_0,
               "xgpio, \"Output pin value set \" error");   

    xGPIOPinWrite(xGPIO_PORTE_BASE, xGPIO_PIN_0, 0);
    ulTemp = GPIOPinPortDoutGet(xGPIO_PORTE_BASE);
    TestAssert(ulTemp == 0,
               "xgpio, \"Output pin value set \" error");
	    
    //
    // EXTI line De-bounce enable test
    //
    EXTILineDebounceEnable(xGPIO_PIN_0);
    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0) & EXTI_CFGR0_DBEN;
    TestAssert(ulTemp == EXTI_CFGR0_DBEN,
               "xgpio, \"De-bounce enable test \" error");  

	//
	// EXTI line De-bounce disable test
	//
    EXTILineDebounceDisable(xGPIO_PIN_0);
    ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_CFGR0) & EXTI_CFGR0_DBEN;
    TestAssert(ulTemp == 0,
               "xgpio, \"De-bounce disable test \" error"); 
	
	//
	// EXTI line De-bounce time set test
	//
	for(i = 0; i < 3; i++)
	{
	    for(j = 0; j < 3; j++)
		{
		    EXTIDebounceTimeSet(ulEXTILines[i], ulDeBounceTime[j]);
			ulTemp = EXTIDebounceTimeGet(ulEXTILines[i]);   
			TestAssert(ulTemp == ulDeBounceTime[j], 
			           "xgpio, \"De-bounce disable test \" error");  
		}  
	}	
	
	//
	// EXTI Wake Up Int configure test
	//
    EXTIWakeUpIntConfigure(ulEXTIWakeUpInt[0]);
	ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) & EXTI_WAKUPCR_EVWUPIEN;
    TestAssert(ulTemp == EXTI_WAKUPCR_EVWUPIEN,
               "xgpio, \"EXTI Wake Up Int Enable \" error");
	EXTIWakeUpIntConfigure(ulEXTIWakeUpInt[1]);
	ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) & EXTI_WAKUPCR_EVWUPIEN;
    TestAssert(ulTemp == 0,
               "xgpio, \"EXTI Wake Up Int Enable \" error");	   

	//
	// EXTI Wake up Configure test
	//
	for(i = 0; i < 3; i++)
	{	
		EXTILineWakeUpConfigure(ulEXTILines[i], ulEXTIWakeUpLevel[0],
			                    ulEXTIWakeUp[0]);
		ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPPOLR) & 
		               (1 << ulEXTILineShift[i]);
		TestAssert(ulTemp == (1 << ulEXTILineShift[i]),
                   "xgpio, \"EXTI Wake Up Level \" error");

		EXTILineWakeUpConfigure(ulEXTILines[i], ulEXTIWakeUpLevel[1],
			                    ulEXTIWakeUp[0]);
		ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPPOLR) & 
		               (1 << ulEXTILines[i]);
		TestAssert(ulTemp == 0,
                   "xgpio, \"EXTI Wake Up Level \" error");

		ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) & 
		               (1 << ulEXTILineShift[i]);
		TestAssert(ulTemp == (1 << ulEXTILineShift[i]),
                   "xgpio, \"EXTI Wake Up Enable \" error");

		EXTILineWakeUpConfigure(ulEXTILines[i], ulEXTIWakeUpLevel[0],
			                    ulEXTIWakeUp[1]);
		ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_WAKUPCR) & 
		               (1 << ulEXTILineShift[i]);
		TestAssert(ulTemp == 0,
                   "xgpio, \"EXTI Wake Up Disable \" error");
	}	  	   
	
	//
	// GPIO Pad configure
	//
    GPIOPadConfigSet(GPIO_PORTA_BASE, xGPIO_PIN_3, 
                     ulStrengthValue[0], ulOpenDrain[0] | ulPullResistor[0]);
    ulTemp =  xHWREG(GPIO_PORTA_BASE + GPIO_DRVR) & xGPIO_PIN_3;
    TestAssert(ulTemp ==0,
               "xgpio, \"Current drain Configure\" error");
    ulTemp = xHWREG(GPIO_PORTA_BASE + GPIO_PUR) & xGPIO_PIN_3;
    TestAssert(ulTemp == xGPIO_PIN_3,
               "xgpio, \"Pull up resistor Enable \" error");
    ulTemp = xHWREG(GPIO_PORTA_BASE + GPIO_PDR) & xGPIO_PIN_3;
    TestAssert(ulTemp == 0,
               "xgpio, \"Pull up resistor Enable \" error");
    ulTemp = xHWREG(ulPort + GPIO_ODR) & xGPIO_PIN_3;
    TestAssert(ulTemp == xGPIO_PIN_3,
               "xgpio, \"Open drain enable \" error");

    GPIOPadConfigSet(GPIO_PORTA_BASE, xGPIO_PIN_3, 
                     ulStrengthValue[1], ulOpenDrain[1] | ulPullResistor[1]);
    ulTemp =  xHWREG(GPIO_PORTA_BASE + GPIO_DRVR) & xGPIO_PIN_3;
    TestAssert(ulTemp == xGPIO_PIN_3,
               "xgpio, \"Current drain Configure\" error");
    ulTemp = xHWREG(GPIO_PORTA_BASE + GPIO_PUR) & xGPIO_PIN_3;
    TestAssert(ulTemp == 0,
               "xgpio, \"Pull up resistor Enable \" error");
    ulTemp = xHWREG(GPIO_PORTA_BASE + GPIO_PDR) & xGPIO_PIN_3;
    TestAssert(ulTemp == xGPIO_PIN_3,
               "xgpio, \"Pull up resistor Enable \" error");
    ulTemp = xHWREG(GPIO_PORTA_BASE + GPIO_ODR) & xGPIO_PIN_3;
    TestAssert(ulTemp == 0,
               "xgpio, \"Open drain disable \" error");	
			   
	//
	// Software Trigger test
	//
	for(i = 0; i < 3; i++)
	{		   		   			   	
	    EXTILineSoftwareTrigger(ulEXTILines[i]);
		ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_SSCR) &  ulEXTILines[i];
		TestAssert(ulTemp == ulEXTILines[i],
                   "xgpio, \"Software Trigger Set \" error");	
    }
	
	//
	// Software Trigger clear
	//	  
	for(i = 0; i < 3; i++)
	{
	    EXTILineSoftwareClear(ulEXTILines[i]);
		ulTemp = xHWREG(GPIO_EXTI_BASE + EXTI_SSCR) &  ulEXTILines[i];
		TestAssert(ulTemp == 0,
                   "xgpio, \"Software Trigger Clear \" error");
    }
    
    //
    // Short pin to pin test
    //
    ulTemp = xGPIOSPinToPin(PA0);
    TestAssert(ulTemp == ulPinValue[0],
               "xgpio, \" Short pin to pin test \" error");  
    ulTemp = xGPIOSPinToPin(PA1);
    TestAssert(ulTemp == ulPinValue[1],
               "xgpio, \" Short pin to pin test \" error");        
    ulTemp = xGPIOSPinToPin(PA2);
    TestAssert(ulTemp == ulPinValue[2],
               "xgpio, \" Short pin to pin test \" error");   
    
    
    //
    // Short pin write test
    //
    xGPIOSPinWrite(PA0, 1);
    ulTemp = GPIOSPinRead(PA0) & GPIO_PIN_0;
    TestAssert(ulTemp == GPIO_PIN_0,
               "xgpio, \"Short pin write test \" error"); 
 
   
    //
    // Ture pin to ADC function
    //    
    xSPinTypeADC(ADC0, PA0);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 0);
    TestAssert((ulTemp == (1 << 0 )),
               "xgpio, \"Turn pin to ADC AIN0 \" error");      
    
    xSPinTypeADC(ADC1, PA1);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 2);
    TestAssert((ulTemp == (1 << 2 )),
               "xgpio, \"Turn pin to ADC AIN1 \" error");  
    
    xSPinTypeADC(ADC2, PA2);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 4);
    TestAssert((ulTemp == (1 << 4 )),
               "xgpio, \"Turn pin to ADC AIN2 \" error");     

    xSPinTypeADC(ADC3, PA3);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 6);
    TestAssert((ulTemp == (1 << 6 )),
               "xgpio, \"Turn pin to ADC AIN3 \" error"); 
    
    xSPinTypeADC(ADC4, PA4);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 8);
    TestAssert((ulTemp == (1 << 8 )),
               "xgpio, \"Turn pin to ADC AIN4 \" error");  
    
    xSPinTypeADC(ADC5, PA5);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 10);
    TestAssert((ulTemp == (1 << 10 )),
               "xgpio, \"Turn pin to ADC AIN5 \" error"); 
    
    xSPinTypeADC(ADC6, PA6);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 12);
    TestAssert((ulTemp == (1 << 12 )),
               "xgpio, \"Turn pin to ADC AIN6 \" error");    
    
    xSPinTypeADC(ADC7, PA7);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 14);
    TestAssert((ulTemp == (1 << 14 )),
               "xgpio, \"Turn pin to ADC AIN7 \" error"); 

    
    //
    // Ture pin to I2C0 function
    //    
    xSPinTypeI2C(I2C0SDA, PC5);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 10);
    TestAssert((ulTemp == (2 << 10)),
               "xgpio, \"Turn pin to I2C SDA \" error");
    xSPinTypeI2C(I2C0SDA, PC12);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 24);
    TestAssert((ulTemp == (1 << 24)),
               "xgpio, \"Turn pin to I2C SDA \" error");
    xSPinTypeI2C(I2C0SDA, PD13);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 26);
    TestAssert((ulTemp == (2 << 26)),
               "xgpio, \"Turn pin to I2C SDA \" error");     			        			         
    
    xSPinTypeI2C(I2C0SCK, PC4);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 8);
    TestAssert((ulTemp == (2 << 8 )),
               "xgpio, \"Turn pin to I2C SCK \" error"); 
    xSPinTypeI2C(I2C0SCK, PC11);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 22);
    TestAssert((ulTemp == (1 << 22 )),
               "xgpio, \"Turn pin to I2C SCK \" error");
    xSPinTypeI2C(I2C0SCK, PD12);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 24);
    TestAssert((ulTemp == (2 << 24 )),
               "xgpio, \"Turn pin to I2C SCK \" error"); 

    //
    // Ture pin to I2C1 function
    //    
    xSPinTypeADC(I2C1SDA, PB7);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 14);
    TestAssert((ulTemp == (2 << 14 )),
               "xgpio, \"Turn pin to I2C1 SDA \" error");
    xSPinTypeADC(I2C1SDA, PC1);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 2);
    TestAssert((ulTemp == (3 << 2 )),
               "xgpio, \"Turn pin to I2C1 SDA \" error");
    xSPinTypeADC(I2C1SDA, PC7);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 14);
    TestAssert((ulTemp == (1 << 14 )),
               "xgpio, \"Turn pin to I2C1 SDA \" error"); 
    xSPinTypeADC(I2C1SDA, PE10);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 20);
    TestAssert((ulTemp == (3 << 20 )),
               "xgpio, \"Turn pin to I2C1 SDA \" error"); 

    xSPinTypeI2C(I2C1SCK, PC0);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 0);
    TestAssert((ulTemp == (3 << 0 )),
               "xgpio, \"Turn pin to I2C1 SCK \" error");
    xSPinTypeI2C(I2C1SCK, PC6);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 12);
    TestAssert((ulTemp == (1 << 12 )),
               "xgpio, \"Turn pin to I2C1 SCK \" error"); 
    xSPinTypeI2C(I2C1SCK, PE9);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 20);
    TestAssert((ulTemp == (3 << 20 )),
               "xgpio, \"Turn pin to I2C1 SCK \" error"); 			   			    			    
		      			     
/*			               
    //
    // Turn pin to pwm mode
    //
    xSPinTypePWM(PWM0, PC2);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP2;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT2;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT2),
               "xgpio, \"Turn pin to PWM function \" error");    
   
    xSPinTypePWM(PWM1, PC3);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP3;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT3;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT3),
               "xgpio, \"Turn pin to PWM function \" error");
    
    xSPinTypePWM(PWM2, PC4);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP4;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT4;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT4),
               "xgpio, \"Turn pin to PWM function \" error");    
    
    xSPinTypePWM(PWM3, PC5);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT5;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT5),
               "xgpio, \"Turn pin to PWM function \" error");       
    
    xSPinTypePWM(PWM4, PC6);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP6;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT6;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT6),
               "xgpio, \"Turn pin to PWM function \" error");   

    xSPinTypePWM(PWM5, PA4);
    ulTemp = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_MFP5;
    ulTemp1 = xHWREG(GCR_GPCMFP) & GCR_GPCMFP_ALT5;
    TestAssert((ulTemp == 0) && (ulTemp1 == GCR_GPCMFP_ALT5),
               "xgpio, \"Turn pin to PWM function \" error"); 
*/			         

 
    //
    // Turn pin to spi function test
    //
    xSPinTypeSPI(SPI0CLK, PB1);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 2);
    TestAssert((ulTemp == (3 << 2)),
               "xgpio, \"Turn pin to SPI function \" error");   
    xSPinTypeSPI(SPI0CLK, PD1);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 2);
    TestAssert((ulTemp == (2 << 2)),
               "xgpio, \"Turn pin to SPI function \" error");
    xSPinTypeSPI(SPI0CLK, PD9);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 18);
    TestAssert((ulTemp == (1 << 18)),
               "xgpio, \"Turn pin to SPI function \" error"); 			      

    xSPinTypeSPI(SPI0MOSI, PB2);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 4);
    TestAssert((ulTemp == (3 << 4 )),
               "xgpio, \"Turn pin to SPI function \" error");   
    xSPinTypeSPI(SPI0MOSI, PD2);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 4);
    TestAssert((ulTemp == (2 << 4 )),
               "xgpio, \"Turn pin to SPI function \" error");
    xSPinTypeSPI(SPI0MOSI, PD10);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 20);
    TestAssert((ulTemp == (1 << 20 )),
               "xgpio, \"Turn pin to SPI function \" error");
			    			    

    xSPinTypeSPI(SPI0MISO, PB3);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 6);
    TestAssert((ulTemp == (3 << 6 )),
               "xgpio, \"Turn pin to SPI function \" error"); 
    xSPinTypeSPI(SPI0MISO, PD3);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 6);
    TestAssert((ulTemp == (2 << 6 )),
               "xgpio, \"Turn pin to SPI function \" error");
    xSPinTypeSPI(SPI0MISO, PD11);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 22);
    TestAssert((ulTemp == (1 << 22 )),
               "xgpio, \"Turn pin to SPI function \" error");			    
    
    xSPinTypeSPI(SPI0CS, PB0);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 0);
    TestAssert((ulTemp == (3 << 0 )),
               "xgpio, \"Turn pin to SPI function \" error");        
    xSPinTypeSPI(SPI0CS, PD0);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 0);
    TestAssert((ulTemp == (2 << 0)),
               "xgpio, \"Turn pin to SPI function \" error"); 
    xSPinTypeSPI(SPI0CS, PD8);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 16);
    TestAssert((ulTemp == (1 << 16)),
               "xgpio, \"Turn pin to SPI function \" error");
    
    //
    // Turn pin to timer function test
    //
    xSPinTypeTimer(TIMCCP0, PA0);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 0);
    TestAssert((ulTemp == (3 << 0)),
               "xgpio, \"Turn pin to TIMER function \" error"); 
    xSPinTypeTimer(TIMCCP0, PB0);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 0);
    TestAssert((ulTemp == (1 << 0)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP0, PD0);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 0);
    TestAssert((ulTemp == (1 << 0)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP0, PE5);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 10);
    TestAssert((ulTemp == (2 << 10)),
               "xgpio, \"Turn pin to TIMER function \" error"); 			    			    
			     
    xSPinTypeTimer(TIMCCP1, PA1);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 2);
    TestAssert((ulTemp == (3 << 2)),
               "xgpio, \"Turn pin to TIMER function \" error");		      
    xSPinTypeTimer(TIMCCP1, PB1);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 2);
    TestAssert((ulTemp == (1 << 2)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP1, PD1);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 2);
    TestAssert((ulTemp == (1 << 2)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP1, PE6);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 12);
    TestAssert((ulTemp == (2 << 12)),
               "xgpio, \"Turn pin to TIMER function \" error");
			    	
			   
    xSPinTypeTimer(TIMCCP2, PA2);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 4);
    TestAssert((ulTemp == (3 << 4)),
               "xgpio, \"Turn pin to TIMER function \" error");		      
    xSPinTypeTimer(TIMCCP2, PB2);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 4);
    TestAssert((ulTemp == (1 << 4)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP2, PD2);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 4);
    TestAssert((ulTemp == (1 << 4)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP2, PE7);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 14);
    TestAssert((ulTemp == (2 << 14)),
               "xgpio, \"Turn pin to TIMER function \" error"); 
			   
    xSPinTypeTimer(TIMCCP3, PA3);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 6);
    TestAssert((ulTemp == (3 << 6)),
               "xgpio, \"Turn pin to TIMER function \" error");		      
    xSPinTypeTimer(TIMCCP3, PB3);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 6);
    TestAssert((ulTemp == (1 << 6)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP3, PD3);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 6);
    TestAssert((ulTemp == (1 << 6)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(TIMCCP3, PE8);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 16);
    TestAssert((ulTemp == (2 << 16)),
               "xgpio, \"Turn pin to TIMER function \" error"); 
			   
    xSPinTypeTimer(TIMCCP4, PA12);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 24);
    TestAssert((ulTemp == (1 << 24)),
               "xgpio, \"Turn pin to TIMER function \" error");   
    xSPinTypeTimer(TIMCCP4, PC0);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 0);
    TestAssert((ulTemp == (2 << 0)),
               "xgpio, \"Turn pin to TIMER function \" error"); 
    xSPinTypeTimer(TIMCCP4, PD8);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 16);
    TestAssert((ulTemp == (3 << 16)),
               "xgpio, \"Turn pin to TIMER function \" error"); 			   	
			 
    xSPinTypeTimer(TIMCCP5, PA13);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 26);
    TestAssert((ulTemp == (1 << 26)),
               "xgpio, \"Turn pin to TIMER function \" error");   
    xSPinTypeTimer(TIMCCP5, PC1);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 2);
    TestAssert((ulTemp == (2 << 2)),
               "xgpio, \"Turn pin to TIMER function \" error"); 
    xSPinTypeTimer(TIMCCP5, PD9);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 18);
    TestAssert((ulTemp == (3 << 18)),
               "xgpio, \"Turn pin to TIMER function \" error"); 	
			   
    xSPinTypeTimer(TIMCCP6, PA14);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 28);
    TestAssert((ulTemp == (1 << 28)),
               "xgpio, \"Turn pin to TIMER function \" error");   
    xSPinTypeTimer(TIMCCP6, PC2);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 4);
    TestAssert((ulTemp == (2 << 4)),
               "xgpio, \"Turn pin to TIMER function \" error"); 
    xSPinTypeTimer(TIMCCP6, PD10);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 20);
    TestAssert((ulTemp == (3 << 20)),
               "xgpio, \"Turn pin to TIMER function \" error");	
			   
    xSPinTypeTimer(TIMCCP7, PA15);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 30);
    TestAssert((ulTemp == (1 << 30)),
               "xgpio, \"Turn pin to TIMER function \" error");   
    xSPinTypeTimer(TIMCCP7, PC3);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 6);
    TestAssert((ulTemp == (2 << 6)),
               "xgpio, \"Turn pin to TIMER function \" error"); 
    xSPinTypeTimer(TIMCCP7, PD11);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 22);
    TestAssert((ulTemp == (3 << 22)),
               "xgpio, \"Turn pin to TIMER function \" error");		   		   		   		    			   			   		     
    
    xSPinTypeTimer(T0EX, PC15);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 30);
    TestAssert((ulTemp == (2 << 30)),
               "xgpio, \"Turn pin to TIMER function \" error");  
    xSPinTypeTimer(T0EX, PD13);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 26);
    TestAssert((ulTemp == (3 << 26)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(T0EX, PE9);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 18);
    TestAssert((ulTemp == (2 << 18)),
               "xgpio, \"Turn pin to TIMER function \" error");			     
    
    xSPinTypeTimer(T1EX, PD12);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 24);
    TestAssert((ulTemp == (3 << 24)),
               "xgpio, \"Turn pin to TIMER function \" error");
    xSPinTypeTimer(T1EX, PE10);   
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 20);
    TestAssert((ulTemp == (2 << 20)),
               "xgpio, \"Turn pin to TIMER function \" error");
			   			    
    
    // 
    // Turn pin to uart function test
    //
    xSPinTypeUART(UART0RX, PA3);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 6);
    TestAssert((ulTemp == (2 << 6)),
               "xgpio, \"Turn pin to UART function \" error"); 
    xSPinTypeUART(UART0RX, PA11);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 22);
    TestAssert((ulTemp == (2 << 22)),
               "xgpio, \"Turn pin to UART function \" error");	
    xSPinTypeUART(UART0RX, PB13);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 26);
    TestAssert((ulTemp == (1 << 26)),
               "xgpio, \"Turn pin to UART function \" error");	
    xSPinTypeUART(UART0RX, PC10);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 20);
    TestAssert((ulTemp == (3 << 20)),
               "xgpio, \"Turn pin to UART function \" error");

    xSPinTypeUART(UART0TX, PA2);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 4);
    TestAssert((ulTemp == (2 << 4)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART0TX, PA10);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 20);
    TestAssert((ulTemp == (2 << 20)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART0TX, PB10);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 20);
    TestAssert((ulTemp == (1 << 20)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART0TX, PC8);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 16);
    TestAssert((ulTemp == (3 << 16)),
               "xgpio, \"Turn pin to UART function \" error");				             
    
    xSPinTypeUART(UART0RTS, PA8);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 16);
    TestAssert((ulTemp == (2 << 16)),
               "xgpio, \"Turn pin to UART function \" error");  
    xSPinTypeUART(UART0RTS, PB8);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 16);
    TestAssert((ulTemp == (1 << 16)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART0RTS, PC11);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 22);
    TestAssert((ulTemp == (3 << 22)),
               "xgpio, \"Turn pin to UART function \" error"); 
    
    xSPinTypeUART(UART0CTS, PA9);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 18);
    TestAssert((ulTemp == (2 << 18)),
               "xgpio, \"Turn pin to UART function \" error");  
    xSPinTypeUART(UART0CTS, PB9);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 18);
    TestAssert((ulTemp == (1 << 18)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART0CTS, PC12);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 24);
    TestAssert((ulTemp == (3 << 24)),
               "xgpio, \"Turn pin to UART function \" error"); 

    xSPinTypeUART(UART0DCD, PC3);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 6);
    TestAssert((ulTemp == (3 << 6)),
               "xgpio, \"Turn pin to UART function \" error");  
    xSPinTypeUART(UART0DCD, PD2);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 4);
    TestAssert((ulTemp == (3 << 4)),
               "xgpio, \"Turn pin to UART function \" error");
			   
    xSPinTypeUART(UART0DSR, PC15);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 30);
    TestAssert((ulTemp == (3 << 30)),
               "xgpio, \"Turn pin to UART function \" error");  			   
	
    xSPinTypeUART(UART0DTR, PB7);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 14);
    TestAssert((ulTemp == (3 << 14)),
               "xgpio, \"Turn pin to UART function \" error");  
    xSPinTypeUART(UART0DTR, PD0);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 0);
    TestAssert((ulTemp == (3 << 0)),
               "xgpio, \"Turn pin to UART function \" error"); 	
			   
    xSPinTypeUART(UART0RI, PC2);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 4);
    TestAssert((ulTemp == (3 << 4)),
               "xgpio, \"Turn pin to UART function \" error");  
    xSPinTypeUART(UART0RI, PD1);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPDCFGR) & (3 << 2);
    TestAssert((ulTemp == (3 << 2)),
               "xgpio, \"Turn pin to UART function \" error"); 
			   
    xSPinTypeUART(UART1RX, PA7);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 14);
    TestAssert((ulTemp == (2 << 14)),
               "xgpio, \"Turn pin to UART function \" error"); 
    xSPinTypeUART(UART1RX, PB3);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 6);
    TestAssert((ulTemp == (2 << 6)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART1RX, PC5);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 10);
    TestAssert((ulTemp == (1 << 10)),
               "xgpio, \"Turn pin to UART function \" error");	   			   		    

    xSPinTypeUART(UART1TX, PA6);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 12);
    TestAssert((ulTemp == (2 << 12)),
               "xgpio, \"Turn pin to UART function \" error"); 
    xSPinTypeUART(UART1TX, PB2);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 4);
    TestAssert((ulTemp == (2 << 4)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART1TX, PC4);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 8);
    TestAssert((ulTemp == (1 << 8)),
               "xgpio, \"Turn pin to UART function \" error");

    xSPinTypeUART(UART1RTS, PA4);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 8);
    TestAssert((ulTemp == (2 << 8)),
               "xgpio, \"Turn pin to UART function \" error"); 
    xSPinTypeUART(UART1RTS, PB0);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 0);
    TestAssert((ulTemp == (2 << 0)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART1RTS, PB15);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 30);
    TestAssert((ulTemp == (1 << 30)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART1RTS, PC13);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 26);
    TestAssert((ulTemp == (3 << 26)),
               "xgpio, \"Turn pin to UART function \" error");

    xSPinTypeUART(UART1CTS, PA5);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPACFGR) & (3 << 10);
    TestAssert((ulTemp == (2 << 10)),
               "xgpio, \"Turn pin to UART function \" error"); 
    xSPinTypeUART(UART1CTS, PB1);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 2);
    TestAssert((ulTemp == (2 << 2)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART1CTS, PB14);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPBCFGR) & (3 << 28);
    TestAssert((ulTemp == (1 << 28)),
               "xgpio, \"Turn pin to UART function \" error");
    xSPinTypeUART(UART1CTS, PC14);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPCCFGR) & (3 << 28);
    TestAssert((ulTemp == (3 << 28)),
               "xgpio, \"Turn pin to UART function \" error");

   
    //
    // Turn the pin to ACMP function
    //
    xSPinTypeACMP(CMP0P, PE6);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 12);
    TestAssert((ulTemp == (1 << 12)),
               "xgpio, \"Turn pin to ACMP function \" error");  
    
    xSPinTypeACMP(CMP0N, PE5);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 10);
    TestAssert((ulTemp == (1 << 10)),
               "xgpio, \"Turn pin to ACMP function \" error");       

    xSPinTypeACMP(CMP0O, PE7);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 14);
    TestAssert((ulTemp == (1 << 14)),
               "xgpio, \"Turn pin to ACMP function \" error");     

    xSPinTypeACMP(CMP1P, PE9);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 18);
    TestAssert((ulTemp == (1 << 18)),
               "xgpio, \"Turn pin to ACMP function \" error"); 

    xSPinTypeACMP(CMP1N, PE8);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 16);
    TestAssert((ulTemp == (1 << 16)),
               "xgpio, \"Turn pin to ACMP function \" error"); 

    xSPinTypeACMP(CMP1O, PE10);
    ulTemp = xHWREG(GPIO_AFIO_BASE + AFIO_GPECFGR) & (3 << 20);
    TestAssert((ulTemp == (1 << 20)),
               "xgpio, \"Turn pin to ACMP function \" error");

}   

//
// xgpio001 register test case struct.
//
const tTestCase sTestxGpio001Register = {
    xgpio001GetTest,
    xgpio001Setup,
    xgpio001TearDown,
    xgpio001Execute
};

//
// Xgpio test suits.
//
const tTestCase * const psPatternxgpio1[] =
{
    &sTestxGpio001Register,
    0
};
