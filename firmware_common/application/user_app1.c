/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */

AntAssignChannelInfoType UserApp1_sChannelInfo;
static  u32  UserApp_u32Timeout;
/**********************************************************************************************************************
Functiotn Definitions
**********************************************************************************************************************/
extern u32 G_u32AntApiCurrentMessageTimeStamp;                             /* Current read message's G_u32SystemTime1ms */
extern AntApplicationMessageType G_eAntApiCurrentMessageClass;     /* Type of data */
extern u8 G_au8AntApiCurrentMessageBytes[ANT_APPLICATION_MESSAGE_BYTES];       /* Array for message payload data */
extern AntExtendedDataType G_sAntApiCurrentMessageExtData;   
/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 
  
  UserApp1_sChannelInfo.AntChannel=ANT_CHANNEL_0;
  UserApp1_sChannelInfo.AntChannelType=UserApiAnt_ChannelType;
  UserApp1_sChannelInfo.AntDeviceIdLo=UserApiAnt_IdLo;
  UserApp1_sChannelInfo.AntDeviceIdHi=UserApiAnt_IdHi;
  UserApp1_sChannelInfo.AntDeviceType=UserApiAnt_DeviceType;
  UserApp1_sChannelInfo.AntTransmissionType=UserApiAnt_TransmissionType;
  UserApp1_sChannelInfo.AntChannelPeriodHi=UserApiAnt_AntChannelPeriodHi;
  UserApp1_sChannelInfo.AntChannelPeriodLo=UserApiAnt_AntChannelPeriodLo;
  UserApp1_sChannelInfo.AntFrequency=UserApiAnt_Frequency;
  UserApp1_sChannelInfo.AntTxPower=UserApiAnt_TxPower;
  UserApp1_sChannelInfo.AntNetwork=UserApiAnt_Network;
  for(u8 i=0;i<8;i++){ 
      
    UserApp1_sChannelInfo.AntNetworkKey[i]=0x00;
  
  }
  if(AntAssignChannel(&UserApp1_sChannelInfo)){
    
   UserApp_u32Timeout= G_u32SystemTime1ms;
   UserApp1_StateMachine=UserApp1SM_AntChannelAssign;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

static void UserApp1SM_AntChannelAssign(void){
  
  if(AntRadioStatusChannel(ANT_CHANNEL_0)==ANT_CONFIGURED){
  
         AntOpenChannelNumber(ANT_CHANNEL_0);
         UserApp1_StateMachine=UserApp1SM_Idle;
         return;
  }
  if(IsTimeUp(&UserApp_u32Timeout,3000)){
    
    UserApp1_StateMachine = UserApp1SM_Error;
  }
  
}
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  
  static u32  u32AntData_count=0;
  static u32  u32AntTick_count=0;
  if(AntReadAppMessageBuffer()){
    
    if(G_eAntApiCurrentMessageClass == ANT_DATA){
      
       u32AntData_count++;
    }
    
    if(G_eAntApiCurrentMessageClass == ANT_TICK){
      
       u32AntTick_count++;
    }
    
    
    
  }
} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
