/**********************************************************************************************************************
File: user_app1.h                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
1. Follow the instructions at the top of user_app1.c
2. Use ctrl-h to find and replace all instances of "user_app1" with "yournewtaskname"
3. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
4. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
5. Add #include yournewtaskname.h" to configuration.h
6. Add/update any special configurations required in configuration.h (e.g. peripheral assignment and setup values)
7. Delete this text (between the dashed lines)
----------------------------------------------------------------------------------------------------------------------

Description:
Header file for user_app1.c

**********************************************************************************************************************/

#ifndef __USER_APP1_H
#define __USER_APP1_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void UserApp1Initialize(void);
void UserApp1RunActiveState(void);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
#define   user_Channel   (u8)0x00
#define   user_CType     CHANNEL_TYPE_MASTER
#define   user_Net       (u8)0x00
#define   user_NKey      (u8)0x00
#define   user_DLo       (u8)0x76
#define   user_DHi       (u8)0x52
#define   user_DType     (u8)0x01
#define   user_Tran      (u8)0x01
#define   user_CPLo      (u8)0x00
#define   user_CPLH      (u8)0x20
#define   user_Fre       (u8)0x32
#define   user_TPower    RADIO_TX_POWER_4DBM


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void UserApp1SM_Idle(void);    

static void UserApp1SM_Error(void);         


#endif /* __USER_APP1_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
