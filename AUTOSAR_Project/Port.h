 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Esraa Fawzy
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

#define PORT_VENDOR_ID (1000U)


#define PORT_MODULE_ID (124U)

/*port instance ID*/
#define PORT_INSTANCE_ID (0U)

/*
 * MODULE VERSION 1.0.0
 */
#define PORT_SW_MAJOR_VERSION (1U)
#define PORT_SW_MINOR_VERSION (0U)
#define PORT_SW_PATCH_VERSION (0U)

/*
 * AUTOSAR VERSION 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_AR_RELEASE_PATCH_VERSION (3U)


#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

#include "Port_Regs.h"   
#include "Common_Macros.h"
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/ 
   
/* Service ID for Port Init */
#define PORT_INIT_SID                  (uint8)0x00
   
 /* Service ID for port Set Pin Direction */
#define PORT_SET_PIN_DIR_SID    (uint8)0x01

/* Service ID for Port Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID   (uint8)0x02

/* Service ID for Port get version info */
#define PORT_GET_VERSION_INFO_SID         (uint8)0x03

/* Service ID for Port set pin mode */
#define PORT_SET_PIN_MODE_SID             (uint8)0x04

   
   
/*******************************************************************************
 *                              DET Error                              *
 *******************************************************************************/
/* Incorrect Port Pin ID passed */
#define PORT_E_PARAM_PIN                        (uint8)0x0A

/* Port Pin not configured  as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)0x0B

/*API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                     (uint8)0x0C

/*API Port_SetPinMode service called when the mode Passed not valid  */
#define PORT_E_PARAM_INVALID_MODE               (uint8)0x0D

/*API Port_SetPinMode service called when the mode is unchangeable. */
#define PORT_E_MODE_UNCHANGEABLE                (uint8)0x0E

/*API service called Prior to module initialization */
#define PORT_E_UNINIT                           (uint8)0x0F
 
 /* APIs called with a Null Pointer Parameter */
#define PORT_E_PARAM_POINTER                    (uint8)0x10
   


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef uint8 Port_PinType;
/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;


typedef enum
{
  LEVEL_LOW,LEVEL_HIGH
} Port_PinLevelValue;

typedef enum
{
	PORT_PIN_MODE_ADC,
	PORT_PIN_MODE_ALT1,
	PORT_PIN_MODE_ALT2,
	PORT_PIN_MODE_ALT3,
	PORT_PIN_MODE_ALT4,
	PORT_PIN_MODE_ALT5,
	PORT_PIN_MODE_ALT6,
	PORT_PIN_MODE_ALT7,
	PORT_PIN_MODE_ALT8,
	PORT_PIN_MODE_ALT9,
	PORT_PIN_MODE_DIO,    
}Port_PinModeType;

typedef enum{
    CHANGE_OFF,CHANGE_ON
}Port_PinChangable;



/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct 
{
    uint8 port_num; 
    Port_PinType pin_num; 
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_PinLevelValue initial_value;
    Port_PinModeType pin_mode;
    Port_PinChangable ChangeableDirection;
    Port_PinChangable ChangeableMode;
   
}Port_ConfigTypePin;

typedef struct
{
  Port_ConfigTypePin Pins[PORT_NUMBER_OF_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver 
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr); 


/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number,Direction - Port Pin Direction 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Set port pin direction
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);


/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None     
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refresh Direction Of Port 
************************************************************************************/
void Port_RefreshPortDirection(void);


/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None     
* Parameters (inout): None
* Parameters (out): versioninfo -Pointer to where to store the version information of this module. 
* Return value: None
* Description: get the version information of module. 
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo); 


/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number, Mode - New Port Pin mode to be set on port pin. 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Set port pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
/*******************************************************************************
 *                       Extern Variables                                    *
 *******************************************************************************/
extern const Port_ConfigType Port_Config;

#endif /* PORT_H */
