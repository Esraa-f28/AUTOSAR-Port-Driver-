/******************************************************************************
 *
 * Module: port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Esraa Fawzy
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

const Port_ConfigType Port_Config = {
                PORT_PortA , PORT_Pin0, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortA , PORT_Pin1, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortA , PORT_Pin2, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortA , PORT_Pin3, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortA , PORT_Pin4, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortA , PORT_Pin5, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortA , PORT_Pin6, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO ,CHANGE_ON,CHANGE_ON,
                PORT_PortA , PORT_Pin7, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,

                PORT_PortB , PORT_Pin0, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortB , PORT_Pin1, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortB , PORT_Pin2, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortB , PORT_Pin3, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortB , PORT_Pin4, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortB , PORT_Pin5, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortB , PORT_Pin6, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortB , PORT_Pin7, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,

                PORT_PortC , PORT_Pin0, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortC , PORT_Pin1, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortC, PORT_Pin2, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortC , PORT_Pin3, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortC , PORT_Pin4, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortC , PORT_Pin5, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortC , PORT_Pin6, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortC , PORT_Pin7, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,

		PORT_PortD , PORT_Pin0, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortD , PORT_Pin1, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortD, PORT_Pin2, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortD , PORT_Pin3, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortD , PORT_Pin4, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortD, PORT_Pin5, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortD, PORT_Pin6, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortD, PORT_Pin7, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,

	        PORT_PortE , PORT_Pin0, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortE , PORT_Pin1, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortE, PORT_Pin2, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortE , PORT_Pin3, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortE , PORT_Pin4, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortE , PORT_Pin5, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                

                PORT_PortF, PORT_Pin0, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortF, PORT_Pin1, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortF, PORT_Pin2, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortF , PORT_Pin3, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                PORT_PortF , PORT_Pin4, INPUT , OFF, LEVEL_LOW , PORT_PIN_MODE_DIO , CHANGE_ON,CHANGE_ON,
                
				         };