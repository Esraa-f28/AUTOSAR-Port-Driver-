 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif


STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
STATIC const Port_ConfigType* Port_ConfigPtr = NULL_PTR;
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
void Port_Init(const Port_ConfigType* ConfigPtr){
 #if (PORT_DEV_ERROR_DETECT == STD_ON)
		if(ConfigPtr == NULL_PTR)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
		}
		else
		{	/* Do Nothing */	
                }
  #endif

	Port_Status = PORT_INITIALIZED;
	Port_ConfigPtr = ConfigPtr;
        Port_PinType PORT_PinCounter;
         volatile uint32 delay = 0;
 for (PORT_PinCounter = 0; PORT_PinCounter< PORT_NUMBER_OF_PINS ; PORT_PinCounter++)
  {
           volatile uint32 * PortGpio_Ptr = NULL_PTR;
    
           switch(ConfigPtr->Pins[PORT_PinCounter].port_num)
           {
              case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
		 break;
	      case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
		 break;
	      case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
		 break;
	      case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; 
		 break;
              case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
		 break;
              case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; 
		 break;
           }
    
    SYSCTL_REGCGC2_REG |= (1<<Port_ConfigPtr->Pins[PORT_PinCounter].port_num);
    delay = SYSCTL_REGCGC2_REG;
    
   if(((Port_ConfigPtr->Pins[PORT_PinCounter].port_num == PORT_PortD) && (Port_ConfigPtr->Pins[PORT_PinCounter].pin_num == 7)) || ((Port_ConfigPtr->Pins[PORT_PinCounter].port_num == PORT_PortF) && (Port_ConfigPtr->Pins[PORT_PinCounter].pin_num == 0))) 
    {
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                        
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr->Pins[PORT_PinCounter].pin_num);  
    }
   else if((Port_ConfigPtr->Pins[PORT_PinCounter].port_num == PORT_PortC) && (Port_ConfigPtr->Pins[PORT_PinCounter].pin_num <= 3)) 
    {
        /* Do Nothing..JTAG pins  */
    }
    else
    {
        /* Do Nothing */
    }
    
               if (Port_ConfigPtr->Pins[PORT_PinCounter].pin_mode == PORT_PIN_MODE_DIO)
		 {
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ConfigPtr->Pins[PORT_PinCounter].pin_num * 4));

			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
		 }
		else if (Port_ConfigPtr->Pins[PORT_PinCounter].pin_mode == PORT_PIN_MODE_ADC)
		 {
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ConfigPtr->Pins[PORT_PinCounter].pin_num * 4));

			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
		  }
		else 
		  {
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Port_ConfigPtr->Pins[PORT_PinCounter].pin_mode & 0x0000000F << (Port_ConfigPtr->Pins[PORT_PinCounter].pin_num * 4));

			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
		  }
   
   
               if(Port_ConfigPtr->Pins[PORT_PinCounter].direction == OUTPUT)
		  {
                                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

				if(Port_ConfigPtr->Pins[PORT_PinCounter].initial_value == LEVEL_HIGH)
				{
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
				}
				else
				{
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
				}
		 }
		else if(Port_ConfigPtr->Pins[PORT_PinCounter].direction == INPUT)
		 {
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

				if(Port_ConfigPtr->Pins[PORT_PinCounter].resistor == PULL_UP)
				{
				        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
				}
				else if(Port_ConfigPtr->Pins[PORT_PinCounter].resistor == PULL_DOWN)
				{
				        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
				}
				else
				{
				        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);

				        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
				}
		  }
		else
		 {
				/* Do Nothing */
		 }
  }

}
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
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction){

	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_UNINIT);
		}
		else
		{	/* Do Nothing */	}

		if(Pin >= PORT_NUMBER_OF_PINS)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_PARAM_PIN);
		}
		else
		{	/* Do Nothing */	}

		if(Port_ConfigPtr->Pins[Pin].ChangeableDirection == CHANGE_OFF)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		}
		else
		{	/* Do Nothing */	}
	#endif

	volatile uint32 * PortPtr = NULL_PTR; 

		 switch(Port_ConfigPtr->Pins[Pin]. port_num)
                {
                    case  PORT_PortA  : PortPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortB: PortPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortC  : PortPtr= (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortD  : PortPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortE  : PortPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortF  : PortPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; 
                                 break;
                }
	

	if( (Port_ConfigPtr->Pins[Pin].port_num== 2) && (Port_ConfigPtr->Pins[Pin].pin_num <= 3)) 
	{
		/* Do Nothing */
		return;
	}

	if(Direction == OUTPUT)
	{
		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPtr + PORT_DIR_REG_OFFSET) ,Port_ConfigPtr->Pins[Pin].pin_num);
	}
	else if(Direction == INPUT)
	{
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPtr + PORT_DIR_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);
	}
	else
	{	/* Do Nothing */	
        }
        
}


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
void Port_RefreshPortDirection(void){/* point to the required Port Registers base address */
        volatile uint32 * PortPtr = NULL_PTR;
        uint8 PORT_PinCounter;
        
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
	}
	else
#endif  
	{
          for( PORT_PinCounter = 0;  PORT_PinCounter < PORT_NUMBER_OF_PINS;  PORT_PinCounter++)
          {
            if(CHANGE_OFF== Port_ConfigPtr->Pins[PORT_PinCounter].ChangeableDirection)
            {
                switch(Port_ConfigPtr->Pins[PORT_PinCounter]. port_num)
                {
                    case  PORT_PortA  : PortPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortB: PortPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortC  : PortPtr= (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortD  : PortPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortE  : PortPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
                                 break;
                    case  PORT_PortF  : PortPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; 
                                 break;
                }
                    if(Port_ConfigPtr->Pins[PORT_PinCounter].direction == OUTPUT)
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPtr + PORT_DIR_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
                       
                    }
                    else if(Port_ConfigPtr->Pins[PORT_PinCounter].direction == INPUT)
                    {
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPtr + PORT_DIR_REG_OFFSET) , Port_ConfigPtr->Pins[PORT_PinCounter].pin_num);
                    }
            }
            else
            {
               /* No Action*/
            }
          }
        }
}


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
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
		if(versioninfo == NULL_PTR)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
		}
		else
		{	/* Do Nothing */	}

		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
		}
		else
		{	/* Do Nothing */	}
	#endif

		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;

}


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
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
		if(Port_Status == PORT_NOT_INITIALIZED)
		 {
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
		 }
		else
		 {	/* Do Nothing */	}

		if(Pin >= PORT_NUMBER_OF_PINS)
		 {
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
		 }
		else
		 {	/* Do Nothing */	}

		if(Mode > PORT_PIN_MODE_DIO)
		 {
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
		 }
		else
		 {	/* Do Nothing */	}

		if(Port_ConfigPtr->Pins[Pin].ChangeableMode == STD_OFF)
		 {
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
		 }
		else
		 {	/* Do Nothing */	}
	#endif

	volatile uint32 * PortGpio_Ptr = NULL_PTR; 

	switch(Port_ConfigPtr->Pins[Pin].port_num)
	 {
		case  PORT_PortA : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; 
		 break;
		case  PORT_PortB: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
		 break;
		case  PORT_PortC : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
		 break;
		case  PORT_PortD: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; 
		 break;
		case  PORT_PortE : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
		 break;
		case  PORT_PortF : PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; 
		 break;
	 }

	if((Port_ConfigPtr->Pins[Pin].port_num == 2) && (Port_ConfigPtr->Pins[Pin].pin_num <= 3)) 
	 {
		/* JTAG pins */
		return;
	 }

	if (Mode == PORT_PIN_MODE_DIO)
	 {
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);

		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);

		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ConfigPtr->Pins[Pin].pin_num * 4));

		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);
	 }
	else if (Mode == PORT_PIN_MODE_ADC)
	 {
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);

		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);

		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ConfigPtr->Pins[Pin].pin_num * 4));

		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);
	 }
	else 
	 {
		CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);

		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);

		*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode & 0x0000000F << (Port_ConfigPtr->Pins[Pin].pin_num * 4));

		SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfigPtr->Pins[Pin].pin_num);
	 }

}