
/*==========================================================================*
 *==========================================================================*
 * Vicon provide the software below “as is," and you use the software at your
 * own risk. Vicon makes no warranties as to performance, merchantability, 
 * fitness for a particular purpose, or any other warranties whether expressed 
 * or implied. No oral or written communication from or information provided 
 * by Vicon shall create a warranty. Under no circumstances shall Vicon be 
 * liable for direct, indirect, special, incidental, or consequential damages 
 * resulting from the use, misuse, or inability to use this software, even if 
 * Vicon has been advised of the possibility of such damages.
 *==========================================================================*
 *==========================================================================*/

/*==========================================================================*
 *==========================================================================*
 * This example will
 *     - Receive Data from Vicon Tracker UDP Stream, packet size = 256
 *     - Parse the data block received and display the object position of the
 *       object that matches the name specified in the block parameters
 * Port configuration should be set in the UDP Receive block to match the
 * parameters set in Tracker 
 *==========================================================================*
 *==========================================================================*/

/*=====================================*
 * Required setup for C MEX S-Function *
 *=====================================*/
#define S_FUNCTION_NAME  TrackerSingleObjectParser
#define S_FUNCTION_LEVEL 2

/*=====================================*
 * Error messages                      *
 *=====================================*/
#define ERR_INVALID_SET_INPUT_DTYPE_CALL  \
                "Invalid call to mdlSetInputPortDataType"

#define ERR_INVALID_SET_OUTPUT_DTYPE_CALL \
                "Invalid call to mdlSetOutputPortDataType"

#define ERR_INVALID_DTYPE \
                "Invalid input or output port data type"

/*
 * user macros fedeoli
 */
#define min(a, b) ((a) < (b) ? (a) : (b))

/*========================*
 * General Defines/macros *
 *========================*/

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h" 

#define TRUE 1
#define FALSE 0

/* total number of block parameters */
#define N_PAR   1        
                      
/* length of the input packet */
#define PACKET_SIZE   256   
              
/* max length of the object name string */
#define MAX_NAME_LENGTH 24  
                      
/* structure for parsing object definition/data */
#include "DataBlock.h"

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Initialize the sizes arrays for input/output ports and parameters
 */
static void mdlInitializeSizes( SimStruct *S )
{
    int i;
    
    /* Set and Check parameter count  */
    ssSetNumSFcnParams( S, N_PAR);

    if ( ssGetNumSFcnParams( S ) != ssGetSFcnParamsCount( S ) ) 
    {
        return;
    }

    /* input 0 is of size PACKET_SIZE and of type uint8 */
    /* input 1 is the status */
    if ( !ssSetNumInputPorts( S, 2 ) )
    {
        return;
    }
    
    ssSetInputPortWidth( S, 0, PACKET_SIZE );
    ssSetInputPortDataType( S, 0, SS_UINT8 );    
    ssSetInputPortDirectFeedThrough( S, 0, TRUE );
    ssSetInputPortRequiredContiguous( S, 0, TRUE );    
    
    ssSetInputPortWidth( S, 1, 1 );
    ssSetInputPortDataType( S, 1, SS_BOOLEAN );    
    ssSetInputPortDirectFeedThrough( S, 1, TRUE );
    ssSetInputPortRequiredContiguous( S, 1, TRUE );       
            
    /* outputs */
    if ( !ssSetNumOutputPorts( S, 9 ) ) 
        return;
    
    /* output 0 is the status pass through */
    ssSetOutputPortWidth(    S, 0, 1 );
    ssSetOutputPortDataType( S, 0, SS_DOUBLE );
    
    /* output 1 is the frame number */    
    ssSetOutputPortWidth(    S, 1, 1 );
    ssSetOutputPortDataType( S, 1, SS_UINT32 );

    /* output 2 is the object name */
    ssSetOutputPortWidth(    S, 2, 24 );
    ssSetOutputPortDataType( S, 2, SS_UINT8 );
    
    /* output 3 is TransX */
    /* output 4 is TransY */
    /* output 5 is TransZ */
    /* output 6 is RotX */
    /* output 7 is RotY */
    /* output 8 is RotZ */
    for( i=3; i<=8; i++)
    {
        ssSetOutputPortWidth(    S, i, 1 );
        ssSetOutputPortDataType( S, i, SS_DOUBLE );
    }
    
    /* sample times */
    ssSetNumSampleTimes( S, 1 );
    
    /* specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance( S, USE_DEFAULT_SIM_STATE );

    /* options */
    ssSetOptions( S,
                  SS_OPTION_WORKS_WITH_CODE_REUSE |
                  SS_OPTION_EXCEPTION_FREE_CODE |
                  SS_OPTION_USE_TLC_WITH_ACCELERATOR );
} /* end mdlInitializeSizes */


/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Initialize the sample times array.
 */
static void mdlInitializeSampleTimes( SimStruct *S )
{
    ssSetSampleTime( S, 0, INHERITED_SAMPLE_TIME );
    ssSetOffsetTime( S, 0, FIXED_IN_MINOR_STEP_OFFSET );
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
} /* end mdlInitializeSampleTimes */

/* Function: mdlOutputs =======================================================
 * Abstract:
 *   Compute the outputs of the S-function.
 */
static void mdlOutputs( SimStruct *S, int_T tid )
{
    int_T     i;
    bool      HaveData = false;
    
    uint8_T  *pData        = (uint8_T *)ssGetInputPortSignal(S,0);
    
    bool     *pStatusIn    = (bool *)ssGetInputPortSignal(S,1);
    uint8_T  *pStatusOut   = (uint8_T *)ssGetOutputPortSignal(S,0);
    
    uint32_T *pFrameOut    = (uint32_T *)ssGetOutputPortSignal(S,1);
    uint8_T  *pNameOut     = (uint8_T *)ssGetOutputPortSignal(S,2);
    real_T   *pTransXOut   = (real_T *)ssGetOutputPortSignal(S,3);
    real_T   *pTransYOut   = (real_T *)ssGetOutputPortSignal(S,4);
    real_T   *pTransZOut   = (real_T *)ssGetOutputPortSignal(S,5);
    real_T   *pRotXOut     = (real_T *)ssGetOutputPortSignal(S,6);
    real_T   *pRotYOut     = (real_T *)ssGetOutputPortSignal(S,7);
    real_T   *pRotZOut     = (real_T *)ssGetOutputPortSignal(S,8);
    
    struct HeaderObject    HEADER;
    struct ItemHeader      ITEM;
    struct TrackerObject   OBJECT;    
    
    /* retrieve the object name parameter */
    char_T ObjectName[MAX_NAME_LENGTH];  
    memset( ObjectName, 0, MAX_NAME_LENGTH );  
    mxGetString( ssGetSFcnParam( S, 0 ), ObjectName, MAX_NAME_LENGTH );
   
    /* populate HEADER from received data block */
    memcpy( &HEADER.FrameNumber, pData, sizeof(HEADER.FrameNumber) );
    pData += sizeof(HEADER.FrameNumber);
    memcpy( &HEADER.ItemsInBlock, pData, sizeof(HEADER.ItemsInBlock) );
    pData += sizeof(HEADER.ItemsInBlock);
           
    /* look for the object we are tracking and populate OBJECT if found */
    for(i=0; i<HEADER.ItemsInBlock && !HaveData; ++i)
    {
        memcpy( &ITEM.ItemID, pData, sizeof(ITEM.ItemID) );
        pData += sizeof(ITEM.ItemID);
        memcpy( &ITEM.ItemDataSize, pData, sizeof(ITEM.ItemDataSize) );
        pData += sizeof(ITEM.ItemDataSize);        

        if( ITEM.ItemID == VICON_TRACKER_OBJECT_ITEM_ID )
        {
            memcpy( &OBJECT, pData, sizeof(OBJECT) );
            if( memcmp( OBJECT.ItemName, ObjectName, min(MAX_NAME_LENGTH, sizeof(OBJECT.ItemName) ) ) == 0 )            
            {
                HaveData = true;
            }
        }
        
        /* move to next item */
        pData += ITEM.ItemDataSize;
    }
    

    /* set our outputs */
    
    /* status */        
    if( pStatusIn )
    {
        if ( HaveData )
        {
            *pStatusOut = (uint8_T)*pStatusIn;
        }
        else
        {
            /* set to something other than zero or one to indicate that the object was not found */
            *pStatusOut = (uint8_T) 2;
        }
    }
    else
    {
        /* set to something other than zero or one to indicate error */
        *pStatusOut = (uint8_T) 3;
    }
    
    if ( HaveData )
    {
        *pFrameOut = HEADER.FrameNumber;
        memcpy( pNameOut, &OBJECT.ItemName[0], sizeof(OBJECT.ItemName) );
        *pTransXOut = OBJECT.TransX;
        *pTransYOut = OBJECT.TransY;
        *pTransZOut = OBJECT.TransZ;
        *pRotXOut   = OBJECT.RotX;
        *pRotYOut   = OBJECT.RotY;
        *pRotZOut   = OBJECT.RotZ; 
    }
    
} /* end mdlOutputs */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    Called when the simulation is terminated.
 */
static void mdlTerminate(SimStruct *S)
{
} /* end mdlTerminate */


#ifdef MATLAB_MEX_FILE

#define MDL_SET_INPUT_PORT_DATA_TYPE
/* Function: mdlSetInputPortDataType ==========================================
 *    This routine is called with the candidate data type for a dynamically
 *    typed port.  If the proposed data type is acceptable, the routine should
 *    go ahead and set the actual port data type using ssSetInputPortDataType.
 *    If the data type is unacceptable an error should generated via
 *    ssSetErrorStatus.  Note that any other dynamically typed input or
 *    output ports whose data types are implicitly defined by virtue of knowing
 *    the data type of the given port can also have their data types set via 
 *    calls to ssSetInputPortDataType or ssSetOutputPortDataType.
 */
static void mdlSetInputPortDataType( SimStruct *S, 
                                     int       port, 
                                     DTypeId   dataType )
{
    if ( port == 0 ) 
    {
        if( dataType == SS_UINT8 ) 
        {
            /*
             * Accept proposed data type if it is an unsigned integer type
             */
            ssSetInputPortDataType(  S, port, dataType );            
        } 
        else 
        {
            /* Reject proposed data type */
            ssSetErrorStatus( S, ERR_INVALID_DTYPE );
        }
    } 
    else if ( port == 1 ) 
    {
        if( dataType == SS_DOUBLE ) 
        {
            /*
             * Accept proposed data type if it is an unsigned integer type
             */
            ssSetInputPortDataType(  S, port, dataType );            
        } 
        else 
        {
            /* Reject proposed data type */
            ssSetErrorStatus( S, ERR_INVALID_DTYPE );
        }
    }     
    else 
    {
        /* 
         * Should not end up here.  Simulink will only call this function
         * for existing input ports whose data types are unknown.
         */
        ssSetErrorStatus( S, ERR_INVALID_SET_INPUT_DTYPE_CALL );
    }

    return;
} /* mdlSetInputPortDataType */


#define MDL_SET_OUTPUT_PORT_DATA_TYPE
/* Function: mdlSetOutputPortDataType =========================================
 *    This routine is called with the candidate data type for a dynamically
 *    typed port.  If the proposed data type is acceptable, the routine should
 *    go ahead and set the actual port data type using ssSetOutputPortDataType.
 *    If the data tyoe is unacceptable an error should generated via
 *    ssSetErrorStatus.  Note that any other dynamically typed input or
 *    output ports whose data types are implicitly defined by virtue of knowing
 *    the data type of the given port can also have their data types set via 
 *    calls to ssSetInputPortDataType or ssSetOutputPortDataType.
 */
static void mdlSetOutputPortDataType( SimStruct *S, 
                                      int       port, 
                                      DTypeId   dataType )
{
    if ( port == 1 ) 
    {
        if( dataType == SS_UINT32 ) 
        {
            /*
             * Accept proposed data type if it is an unsigned integer type
             * force all the ports to use this data type.
             */
            ssSetOutputPortDataType( S, port, dataType );            
        } 
        else 
        {
            /* reject proposed data type */
            ssSetErrorStatus( S, ERR_INVALID_DTYPE );
        }
    } 
    else if ( port == 2 ) 
    {
        if( dataType == SS_UINT8 ) 
        {
            /*
             * Accept proposed data type if it is an unsigned integer type
             * force all the ports to use this data type.
             */
            ssSetOutputPortDataType( S, port, dataType );            
        } 
        else 
        {
            /* reject proposed data type */
            ssSetErrorStatus( S, ERR_INVALID_DTYPE );
        }
    }     
    else /* all other output ports are SS_DOUBLE */
    {
        if ( dataType == SS_DOUBLE )
        {
            ssSetOutputPortDataType( S, port, dataType );   
        }
        else
        {
            /* reject proposed data type */
            ssSetErrorStatus( S, ERR_INVALID_DTYPE );
        }
    }

    return;

} /* mdlSetOutputPortDataType */

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
/* Function: mdlSetDefaultPortDataTypes ========================================
 *    This routine is called when Simulink is not able to find data type 
 *    candidates for dynamically typed ports. This function must set the data 
 *    type of all dynamically typed ports.
 */
static void mdlSetDefaultPortDataTypes( SimStruct *S )
{
    /* Set input port data type to uint8 */
    ssSetInputPortDataType(  S, 0, SS_UINT8 );  
    ssSetInputPortDataType(  S, 1, SS_DOUBLE ); 
    
    ssSetOutputPortDataType(  S, 0, SS_DOUBLE );  
    ssSetOutputPortDataType(  S, 1, SS_UINT32 );  
    ssSetOutputPortDataType(  S, 2, SS_UINT8 );  
    ssSetOutputPortDataType(  S, 3, SS_DOUBLE );  
    ssSetOutputPortDataType(  S, 4, SS_DOUBLE );  
    ssSetOutputPortDataType(  S, 5, SS_DOUBLE );  
    ssSetOutputPortDataType(  S, 6, SS_DOUBLE );  
    ssSetOutputPortDataType(  S, 7, SS_DOUBLE );  
    ssSetOutputPortDataType(  S, 8, SS_DOUBLE );  
    
} /* mdlSetDefaultPortDataTypes */

#endif /* MATLAB_MEX_FILE */



/*=======================================*
* Required closing for C MEX S-Function *
*=======================================*/

#ifdef    MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
# include "simulink.c"     /* MEX-file interface mechanism               */
#else
# include "cg_sfun.h"      /* Code generation registration function      */
#endif


/* [EOF] sfun_dtype_io.c */

