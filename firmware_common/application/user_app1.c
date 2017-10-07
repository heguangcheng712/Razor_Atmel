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
/* Existing variables in ant_api.c*/
extern u8 G_au8AntApiCurrentMessageBytes[ANT_APPLICATION_MESSAGE_BYTES];
extern AntApplicationMessageType G_eAntApiCurrentMessageClass;

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
                      


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/
/* set  Channel  parameters     */
static AntAssignChannelInfoType   user_Assign_test;
//static u32 UserApp1_u32Timeout;
static u32  u32user_test_timeout;
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
  LedOff(RED);
  LedOff(GREEN);
  /*set  the  value  into  the  user_Assign_test */
  user_Assign_test.AntChannel=user_Channel;
  user_Assign_test.AntChannelPeriodHi=user_CPLH;
  user_Assign_test.AntChannelPeriodLo=user_CPLo;
  user_Assign_test.AntChannelType=user_CType;
  user_Assign_test.AntDeviceIdHi=user_DHi;
  user_Assign_test.AntDeviceIdLo=user_DLo;
  user_Assign_test.AntDeviceType=user_DType;
  user_Assign_test.AntFrequency=user_Fre;
  user_Assign_test.AntNetwork=user_Net;
  user_Assign_test.AntTransmissionType=user_Tran;
  user_Assign_test.AntTxPower=user_TPower;
  for(u8 i=0;i<8;i++){
     
     user_Assign_test.AntNetworkKey[i]=user_NKey;
    
  }
  /* If save parameters ok, set state to user_Assign_test */
  if( 1 )
  {
    if(AntAssignChannel(&user_Assign_test)){
      
       u32user_test_timeout=G_u32SystemTime1ms;
       UserApp1_StateMachine=User_assignment_set;
       
      
    }
    
    
   // UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
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
static void  User_assignment_set(void){
  
  
  /*if config  ok,set state to UserApp1SM_Idle*/
  if(AntRadioStatusChannel(user_Channel)==ANT_CONFIGURED){
      /*Open  the Channel */
      AntOpenChannelNumber(user_Channel);
      UserApp1_StateMachine = UserApp1SM_Idle;
    
  }
  /*if time is out(config fail),set state to UserApp1SM_Error*/
  if(IsTimeUp(&u32user_test_timeout,3000)){
    
      UserApp1_StateMachine = UserApp1SM_Error;
    
  }
  
}
/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static  u8  au8messtest[8]={0x5b,0,0,0,0xff,0,0,0};
  static  u8  u8messtype=AntToSendAck;
  static  bool  bIsNeedToRecvAck=FALSE; 
  static  u32 u32time1=0;
  static  u32 u32time2=0;
  /*If BUTTON0 was pressed,change to SendBroad*/
  /*Test  only*/
  if(WasButtonPressed(BUTTON0)){
    
      ButtonAcknowledge(BUTTON0);
      u8messtype=AntToSendBroad;
      //au8messtest[0]=0x7f;
    
  }
  /*If BUTTON0 was pressed,change to SendAck*/
  /*Test  only*/
  if(WasButtonPressed(BUTTON1)){
    
      ButtonAcknowledge(BUTTON1);
      u8messtype=AntToSendAck;
      //au8messtest[0]=0xf7;
    
  }
  /*If no data  are read,return to mainloop. */
  if(AntReadAppMessageBuffer()==FALSE){
    
      return;
  }
  /*Messsage are DATA,RED is on*/
  if(G_eAntApiCurrentMessageClass==ANT_DATA){
      LedOn(RED);
      LedOff(GREEN);
  }
   /*Messsage are TICK*/
  if(G_eAntApiCurrentMessageClass==ANT_TICK){
    
    /*if last data is ack,adj the ackment state*/
    if(bIsNeedToRecvAck){
      
         bIsNeedToRecvAck=FALSE;
         if(G_au8AntApiCurrentMessageBytes[ANT_TICK_MSG_EVENT_CODE_INDEX]==EVENT_TRANSFER_TX_COMPLETED){
             
             /*record the timestamp*/  
             u32time2=G_u32SystemTime1ms;
             /*fail account*/
             au8messtest[3]++;
             if(au8messtest[3]==0){
                 au8messtest[2]++;
                 if(au8messtest[2]==0){
                    au8messtest[1]++; 
                 }
             }
             LedOff(RED);
             LedOn(GREEN);
             return;
         }
    }
    
    
    /*data account*/
    au8messtest[7]++;
    if(au8messtest[7]==0){
      
       au8messtest[6]++;
       if(au8messtest[6]==0){
         
             au8messtest[5]++; 
       }
    }
      
    if(u8messtype==AntToSendAck){
    
         AntQueueAcknowledgedMessage(user_Channel,au8messtest);
         bIsNeedToRecvAck=TRUE;
         /*record the timestamp*/  
         u32time1=G_u32SystemTime1ms;
    }

    if(u8messtype==AntToSendBroad){
    
         AntQueueBroadcastMessage(user_Channel,au8messtest);
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
