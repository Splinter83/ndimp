/*
 * global_types.h
 *
 *  Created on: 17/set/2012
 *  Author: Emanuele Galli
 */

#ifndef GLOBAL_TYPES_H_
#define GLOBAL_TYPES_H_

#include <string.h>
#include "global_definitions.h"
#include "Singleton.h"
#include "ConfigFile.h"

/* Type Definitions */

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long ULONG;
typedef char INT8;
typedef short INT16;
typedef int INT32;

typedef struct {
	UINT16 start_delimiter;
	UINT16 identifier;
	UINT32 msg_size;
}Header;

typedef enum {
	EN_MSG_BASE = 0xFF00,
	EN_MSG_CMD,
	EN_MSG_LOG,
	EN_MSG_DISCRETE,
	EN_MSG_CMD_RESULT,
	EN_MSG_UNK
}EN_MSG_IDENTFIER;

typedef enum{
	SIMP1 = 0,
	SIMP2,
	STIMP,
	NDIMP,
	OTHER
}BoardType;

typedef enum{
	CMP_NONE = 0,
	CMP_3838,
	CMP_3910,
	CMP_ODDL,
	CMP_EDDL
}ComponentType;

typedef enum{
	EN_CHANNEL_A = 0,
	EN_CHANNEL_B
} ChannelType;

typedef enum{
	SIMP1_AVIONIC_3910 = 0,
	SIMP1_BSD_EDDL,
	SIMP1_MDP_EDDL,
	SIMP1_CSMU_EDDL,
	SIMP2_ATTACK_3910,
	SIMP2_EMU1_EDDL,
	SIMP2_UCS_3838,
	SIMP2_EMU2_EDDL,
	STIMP_AVIONIC_3910,
	STIMP_ATTACK_3910,
	UNK_BOARD_TYPE
} BoardInterfaceType;

typedef enum{
    EN_OPTIMIZED_BUS = 0,
    EN_RAM,
    EN_SKELETON_3838,
    EN_HS_SELFTEST,
    EN_LOOPBACK_A,
    EN_LOOPBACK_B,
    EN_LOOPBACK_LS_A,
    EN_LOOPBACK_LS_B,
    EN_HS_INTERRUPT_POINTER,
    EN_LS_SELFTEST,
    EN_RT_ADDRESS,
    EN_RT_PARITY,
    EN_LS_RXTX,
    EN_SKELETON_BUS,
    EN_INTERRUPT,
    EN_BIT_HISTORY,
    CUSTOM_TEST
} CommonTestType;

typedef enum{
	EN_SIMP_WATCH_DOG = CUSTOM_TEST,
	EN_SIMP_WATCH_DOG_3910,
	EN_SIMP_DISCRETE_IF,
	EN_SIMP_LOOPBACK_CHAN_A_SIDE_B,
	EN_SIMP_DDL_ADDRESS_TEST
} SIMP_CustomTestype;

typedef enum{
	EN_STIMP_WATCH_DOG = CUSTOM_TEST,
	EN_STIMP_WATCH_DOG_3910,
	EN_STIMP_BC,
	EN_STMIP_BC_BUSY_U44,
	EN_STMIP_BC_BUSY_U22,
	EN_STMIP_DISCRETE_INPUT_CRTITICAL,
	EN_STMIP_DISCRETE_OUTPUT_CRTITICAL,
	EN_STMIP_DISCRETE_INPUT_NOT_CRTITICAL,
	EN_STMIP_DISCRETE_OUTPUT_NOT_CRTITICAL,
	EN_STIMP_HIACT_LODEM,
	EN_STIMP_ACT_DEM,
	EN_STIMP_ISNOGO,
	EN_STIMP_MOD_NOGO,
	EN_STIMP_NMI
} STIMP_CustomTestType;

typedef enum{
	READ = 0,
	WRITE,
	TEST,
	CONFIG,
	SGA
}CmdType;

enum EN_VME_READWRITE_SIZE{
	EN_VME_BYTE = 0,
	EN_VME_WORD,
	EN_VME_TRIPLE_BYTE,
	EN_VME_DOUBLE_WORD
};

typedef enum {
	EN_SGA_1 = 1,
	EN_SGA_2,
	EN_SGA_3
}EN_SGA_ADDRESS;

typedef enum{
	EN_DI_1 = 0,
	EN_DI_2,
	EN_DI_3,
	EN_DI_4,
	EN_DI_5,
	EN_DI_6,
	EN_DI_7,
	EN_DI_8,
	EN_DI_9,
	EN_DI_10,
	EN_DI_11,
	EN_DI_12,
	EN_DO_1,
	EN_DO_2,
	EN_DO_3,
	EN_DO_4,
	EN_DO_5,
	EN_DO_6,
	EN_DO_7,
	EN_DO_8,
	EN_DO_9,
	EN_DO_10,
	EN_DO_11,
	EN_DO_12,
	EN_DEM_NLTH,
	EN_DEM_ALTH, //Handover
	EN_ACT_NLTH,
	EN_ACT_ALTH,
	EN_LODEM_NLTH,
	EN_LOADM_ALTH,
	EN_HIACT_NLTH,
	EN_HIACT_ALTH,
	EN_CSMU_WIRE,
	EN_CSMU_WE_TTL
}EN_DISCRETE_STATUS;

//////////Strcut for Data Fields inside xml messages

struct TestStruct{
	UINT16 _testNumber;
	UINT16 _step;
	UINT32 _terminalNumber;
	BoardInterfaceType _configId;
	ChannelType _channel;
	bool _rci;
};

struct ResultStruct{
	int Result;
	int CurrentStep;
	bool IsTerminated;
	int CmdID; //CURRENTLY NOT USED
	CmdType Type;
	bool CommandSuccess;
	char ErrorStr[MAX_BUF_SIZE];

	ResultStruct(){
		memset(this,0,sizeof(ResultStruct));
	}
};

struct DiscreteStruct{
	UINT8 Status;
	char Name[MAX_BUF_SIZE];

	DiscreteStruct(){
		memset(this,0,sizeof(DiscreteStruct));
	}

	DiscreteStruct(const DiscreteStruct &discr){
		memset(this,0,sizeof(DiscreteStruct));
		memcpy(this,&discr,sizeof(DiscreteStruct));
	}

	void SetName(const char* name, const int &size){
		memset(Name,0,MAX_BUF_SIZE);
		memcpy(Name,name,size);
	}
};

typedef enum{
	AVIONIC = 0,
	BSD,
	MDP,
	CSMU,
	ATTACK,
	EMU1,
	EMU2,
	UCS,
	UNK
}InterfaceType;

struct ConfigStruct{
	UINT32 _baseAddress;
	BoardType _board;
	UINT32 _RamSize;
	ComponentType _device;
	UINT32 _arbiteredIO;
	UINT32 _directIO;
	UINT32 _restartHS;
	InterfaceType _interface;
	UINT8 _rtAddress;
	UINT32 _bitHistoryAddr;
	UINT32 _bitHistorySize;
	ConfigStruct(){
		memset(this,0,sizeof(ConfigStruct));
		_rtAddress = 0xFF;
	}
};

struct CmdResultField{
	struct tMsgParameters{
		int Result;
		int CurrentStep;
		int IsTerminated;
		char *Message;
		tMsgParameters(){
			memset(this,0,sizeof(tMsgParameters));
		}
		~tMsgParameters(){
			if(Message != 0)
				delete []Message;
		}
	};
};

struct DiscreteField{
	struct tMsgParameters{
		bool Status;
		char *Name;

		tMsgParameters(){
			memset(this,0,sizeof(tMsgParameters));
		}

		~tMsgParameters(){
			if(Name != 0)
				delete []Name;
		}
	};
};

struct CmdMessageField{
	struct tMsgParameters{
		UINT32 ID;


		BoardType Board;
		CmdType Command;
		//READ and WRITE command
		UINT32 Address;
		UINT32 Data;
		EN_VME_READWRITE_SIZE Alignment;

		//Configuration Command
		UINT32 BaseAddress;
		UINT32 RamSize;
		UINT32 Arbitered_IO;
		UINT32 Direct_IO;
		UINT32 Restart_HS;
		InterfaceType Interface;
		ComponentType Component;

		//Test command
		ChannelType Channel;

		EN_SGA_ADDRESS SGA;

		UINT32 StepNumber;
		UINT32 TestNumber;
		char *TestString;
		BoardInterfaceType ConfigurationType;
		UINT8 RT_Address;
		UINT8 RCI;
		UINT32 BIT_History_Addr;
		UINT32 BIT_History_Size;
		//DataSizeType DataSize;

		tMsgParameters(){
			memset(this,0,sizeof(tMsgParameters));
			TestString = new char[Singleton<ConfigFile, CreateThreadSafe>::instance()->getParameter<UINT16>("MAX_NAME_SIZE", hexadecimal)];
			RT_Address = 0xFF;
		}

		~tMsgParameters(){
			delete [] TestString;
		}
	};
};

///////Struct for All Discrete Signals

typedef struct{
	UINT32 OPT_RESET : 1;
	UINT32 SNOGO     : 1;
	UINT32 OVERRIDE  : 1;
	UINT32 MNOGO     : 1;
	UINT32 INTAHS    : 1;
	UINT32 INTALS    : 1;
	UINT32 TESTENL   : 1;
	UINT32 ENWDEXT   : 1;
	UINT32 ENWDLS    : 1;
	UINT32 RESEVED   : 23;
}GeneralConfigRegType;

typedef union{
	GeneralConfigRegType reg;
	UINT32 raw32;
}GeneralConfigReg;

typedef struct{
	UINT32 DI_1:  1;
	UINT32 DI_2:  1;
	UINT32 DI_3:  1;
	UINT32 DI_4:  1;//4
	UINT32 DI_5:  1;
	UINT32 DI_6:  1;
	UINT32 DI_7:  1;
	UINT32 DI_8:  1;//8
	UINT32 DI_9:  1;
	UINT32 DI_10: 1;
	UINT32 DI_11: 1;
	UINT32 DI_12: 1;//12
	UINT32 DO_1:  1;
	UINT32 DO_2:  1;
	UINT32 DO_3:  1;
	UINT32 DO_4:  1;//16
	UINT32 DO_5:  1;
	UINT32 DO_6:  1;
	UINT32 DO_7:  1;
	UINT32 DO_8:  1;//20
	UINT32 DO_9:  1;
	UINT32 DO_10: 1;
	UINT32 DO_11: 1;
	UINT32 DO_12: 1;//24
	UINT32 CSMU_WE_TTL:1;
	UINT32 CSMU_WIRE:1;
	UINT32 RESERVED: 6;
}DiscreteRegType;

typedef union{
	DiscreteRegType reg;
	UINT32 raw32;
}DiscreteReg;

typedef struct{
	UINT32 EFA_HSINT:     1;
	UINT32 EFA_LSINT:     1;
	UINT32 EMUIBSD_INT:   1;
	UINT32 HDLHS_INT:     1;
	UINT32 HDLLS_INT:     1;
	UINT32 EMU2CSMU_INT:  1;
	UINT32 RESERVED:     26;
}Mil1553RegType;

typedef union{
	Mil1553RegType reg;
	UINT32 raw32;
}Mil1553Reg;

typedef struct{
	UINT32 DEM_NLT:      1;
	UINT32 DEM_ALT:      1;
	UINT32 ACT_NLT:      1;
	UINT32 ACT_ALT:      1;
	UINT32 LODEM_NLT:    1;
	UINT32 LOADM_ALT:    1;
	UINT32 HIACT_NLT:    1;
	UINT32 HIACT_ALT:    1;
	UINT32 HANDOVER_EN:  1;
	UINT32 RESERVED:    23;
}HandoverRegType;

typedef union{
	HandoverRegType reg;
	UINT32 raw32;
}HandoverReg;

typedef struct{
	UINT32 SGA_0 : 1;
	UINT32 SGA_1 : 1;
	UINT32 SGA_2 : 1;
	UINT32 SGA_SEL: 1;
	UINT32 RESERVED : 28;
}SGARegType;

typedef union{
	SGARegType reg;
	UINT32 raw32;
}SGAReg;

typedef struct{
	UINT32 RTP_B_W     : 1;
	UINT32 RTA_B0_W	   : 1;
	UINT32 RTA_B1_W	   : 1;
	UINT32 RTA_B2_W	   : 1;
	UINT32 RTA_B3_W	   : 1;
	UINT32 RTA_B4_W	   : 1;
	UINT32 RTA_B_SEL_W : 1;
	UINT32 RTP_A_W	   : 1;
	UINT32 RTA_A0_W	   : 1;
	UINT32 RTA_A1_W	   : 1;
	UINT32 RTA_A2_W	   : 1;
	UINT32 RTA_A3_W	   : 1;
	UINT32 RTA_A4_W	   : 1;
	UINT32 RTA_A_SEL_W : 1; //Bit 14
	UINT32 RESERVED_1  : 2;
	UINT32 RTA_B0_R	   : 1; //Bit 17
	UINT32 RTA_B1_R	   : 1;
	UINT32 RTA_B2_R	   : 1;
	UINT32 RTA_B3_R	   : 1;
	UINT32 RTA_B4_R	   : 1;
	UINT32 RTP_B_R     : 1;
	UINT32 RTA_A0_R	   : 1;
	UINT32 RTA_A1_R	   : 1;
	UINT32 RTA_A2_R	   : 1;
	UINT32 RTA_A3_R	   : 1;
	UINT32 RTA_A4_R	   : 1;
	UINT32 RTP_A_R	   : 1;
	UINT32 RESERVED_2  : 4;
}RT_RegType;

typedef union{
	RT_RegType reg;
	UINT32 raw32;
}RT_Reg;

typedef struct{
	UINT32 DI12_INT :1;
	UINT32 DI10_INT :1;
	UINT32 DI6_INT :1;
	UINT32 DI4_INT :1;
	UINT32 DI2_INT :1;
	UINT32 AH_INT :1;
	UINT32 DI11_INT :1;
	UINT32 DI7_INT :1;
	UINT32 AL_INT :1;
	UINT32 DI5_INT :1;
	UINT32 DI8_INT :1;
	UINT32 DI3_INT :1;
	UINT32 DI1_INT :1;
	UINT32 NL_INT :1;
	UINT32 NH_INT :1;
	UINT32 DI9_INT :1;
	UINT32 EFA_HSINT :1;
	UINT32 EFA_LSINT :1;
	UINT32 EMU1BSD_INT :1;
	UINT32 HDLHS_INT :1;
	UINT32 HDLLS_INT :1;
	UINT32 EMU2CSMU_INT :1;
	UINT32 RESERVED:10;

}Interrupt_RegType;

typedef union{
	Interrupt_RegType reg;
	UINT32 raw32;
}Interrupt_Reg;

typedef struct{
	UINT32	FOFE_SEL1	:1;
	UINT32	FOFE_SEL2	:1;
	UINT32	FOFE_SEL3	:1;
	UINT32	FOFE_SEL4	:1;
	UINT32	FOFE_SEL5	:1;
	UINT32	FOFE_SEL6	:1;
	UINT32	FOFE_SEL7	:1;
	UINT32	FOFE_SEL8	:1;
	UINT32	FOFE_SEL9	:1;
	UINT32	FOFE_SEL10	:1;
	UINT32	FOFE_SEL11	:1;
	UINT32	FOFE_SEL12	:1;
	UINT32	FOFE_SEL13	:1;
	UINT32	FOFE_SEL14	:1;
	UINT32	FOFE_SEL15	:1;
	UINT32	FOFE_SEL16	:1;
	UINT32	FOFE_SEL17	:1;
	UINT32	FOFE_SEL18	:1;
	UINT32	FOFE_SEL19	:1;
	UINT32	FOFE_SEL20	:1;
    UINT32  RESERVED    :7;
    UINT32  SEL_1553_0  :1;
    UINT32  SEL_1553_1  :1;
    UINT32  SEL_1553_2  :1;
    UINT32  SEL_1553_3  :1;
    UINT32  SEL_1553_4  :1;
}FOFERegType;

typedef union{
	FOFERegType reg;
	UINT32 raw32;
}FOFE_Reg;

typedef struct{
	GeneralConfigReg general_config_reg;
	DiscreteReg discrete_reg;
	Mil1553Reg mil1553_reg;
	HandoverReg handover_reg;
	SGAReg sga_reg;
	RT_Reg rt_reg;
	FOFE_Reg fofe_reg;
} AllDiscreteType;


#endif /* GLOBAL_TYPES_H_ */
