#ifndef __MEMORIA__
#define __MEMORIA__  

#include "messaggi.h"
#include <string.h>

enum {LOW = 0, HIGH};

typedef struct {
	unsigned int TS :4;
	unsigned int ZERO :1; //BIT A 0
	unsigned int MON :1;
	unsigned int LWD :1;
	unsigned int HSS :1;
	unsigned int BIT :1;
	unsigned int MOD :1;
	unsigned int PAR :1;
	unsigned int TA :5;
} RT_ICW_TYPE;

typedef union {
	char raw[sizeof(RT_ICW_TYPE)];
	RT_ICW_TYPE RT_ICW;
} RT_ICW_UNION_TYPE;

typedef struct {
	unsigned int SAW :16;
} RT_SAW_TYPE;

typedef struct {
	unsigned int CWLP :16;
} RT_CWLP_TYPE;

typedef struct {
	unsigned int AMD :1;
	unsigned int TR :1;
	unsigned int AB :1;
	unsigned int UEX :1;
	unsigned int STE :1;
	unsigned int STC :1;
	unsigned int PCB :1;
	unsigned int BMR :1;
	unsigned int HST :1;
	unsigned int LWT :1;
	unsigned int SPI :1;
	unsigned int MR :1;
	unsigned int RE :1;
	unsigned int ZERO :3; // 3 BIT A 0
} RT_ISW_TYPE;

typedef struct {
	unsigned int ZERO4 :1; // 1 BIT A 0
	unsigned int DBA :1;
	unsigned int SY :1;
	unsigned int ZERO3 :1; // 1 BIT A 0
	unsigned int IST :1;
	unsigned int SH :1;
	unsigned int OSH :1;
	unsigned int ITF :1;
	unsigned int OTF :1;
	unsigned int RRT :1;
	unsigned int TVW :1;
	unsigned int SYW :1;
	unsigned int ZERO2 :1; // 1 BIT A 0
	unsigned int TBW :1;
	unsigned int ZERO1 :2; // 2 BIT A 0
} RT_IMW_TYPE;

typedef struct {
	unsigned int ERE :1;
	unsigned int DBA :1;
	unsigned int SY :1;
	unsigned int TSW :1;
	unsigned int IST :1;
	unsigned int SH :1;
	unsigned int OSH :1;
	unsigned int ITF :1;
	unsigned int OTF :1;
	unsigned int RRT :1;
	unsigned int TVW :1;
	unsigned int SYW :1;
	unsigned int TLC :1;
	unsigned int TBW :1;
	unsigned int RM :1;
	unsigned int TM :1;
} RT_MIW_TYPE;

typedef struct {
	unsigned int VW :16;
} RT_VW_TYPE;

typedef struct {
	unsigned int DMA :1;
	unsigned int SEQ :1;
	unsigned int TPA :1;
	unsigned int INF :1;
	unsigned int SSF :1;
	unsigned int ZERO :1; // 1 BIT A 0
	unsigned int SLP :1;
	unsigned int TAR :1;
	unsigned int NOR :1;
	unsigned int GAP :1;
	unsigned int INM :1;
	unsigned int ZCR :1;
	unsigned int PER :1;
	unsigned int SYN :1;
	unsigned int WCH :1;
	unsigned int WCL :1;
} RT_EBW_TYPE;

typedef struct {
	unsigned int MSW :16;
} RT_MSW_TYPE;

typedef struct {
	unsigned int MEW :16;
} RT_MEW_TYPE;

typedef struct {
	unsigned int WC :5;
	unsigned int SA :5;
	unsigned int TR :1;
	unsigned int TA :5;
} RT_CW_TYPE;

typedef struct {
	unsigned int WC :5;
	unsigned int ZERO1 :4; // 4 BIT A 0
	unsigned int RCN :1;
	unsigned int MDI :1;
	unsigned int SIL :1;
	unsigned int EDB :1;
	unsigned int ERI :1;
	unsigned int RCI :1;
	unsigned int MRE :1;
} RT_SCW_LS_TYPE;

typedef struct {
	unsigned int WC :5;
	unsigned int ZERO2 :4; // 4 BIT A 0
	unsigned int RCN :1;
	unsigned int MDI :1;
	unsigned int SIL :1;
	unsigned int ZERO1 :1; // 1 BIT A 0
	unsigned int ERI :1;
	unsigned int RCI :1;
	unsigned int MRE :1;
} RT_SCW_HS_TYPE;

typedef struct {
	unsigned int IDP :16;
} RT_IDP_TYPE;

typedef struct {
	unsigned int HDP :16;
} RT_HDP_TYPE;

typedef struct {
	unsigned int STT :16;
} RT_STT_TYPE;

typedef struct {
	unsigned int TF :1;
	unsigned int DBA :1;
	unsigned int SSF :1;
	unsigned int BSY :1;
	unsigned int ZERO2 :4; // 4 BIT A 0
	unsigned int SRQ :1;
	unsigned int ZERO1 :7; // 7 BIT A 0
} RT_STR_TYPE; // STATUS TEMPLATE REGISTER (ADDRESS 2)

typedef struct {
	unsigned int TS :4;
	unsigned int COE :1;
	unsigned int TVE :1;
	unsigned int DBE :1;
	unsigned int HSS :1;
	unsigned int BIT :1;
	unsigned int MOD :1;
	unsigned int ZERO :6; // 6 BIT A 0
} BC_ICW_TYPE;

typedef union {
	char raw[sizeof(BC_ICW_TYPE)];
	BC_ICW_TYPE BC_ICW;
} BC_ICW_UNION_TYPE;

typedef struct {
	unsigned int BAW :16;
} BC_BAW_TYPE;

typedef struct {
	unsigned int IAWLP :16;
} BC_IAWLP_TYPE;

typedef struct {
	unsigned int MDW :16;
} BC_MDW_TYPE;

typedef struct {
	unsigned int DMA :1;
	unsigned int SEQ :1;
	unsigned int TMC :1;
	unsigned int RWC :1;
	unsigned int ILC :1;
	unsigned int ILR :1;
	unsigned int SLP :1;
	unsigned int TAR :1;
	unsigned int NOR :1;
	unsigned int GAP :1;
	unsigned int INM :1;
	unsigned int ZCR :1;
	unsigned int PER :1;
	unsigned int SYN :1;
	unsigned int WCH :1;
	unsigned int WCL :1;
} BC_EBW_TYPE;

typedef struct {
	unsigned int AEW :16;
} BC_AEW_TYPE;

typedef struct {
	unsigned int IAW :16;
} BC_IAW_TYPE;

typedef struct {
	unsigned int AMD :1;
	unsigned int TR :1;
	unsigned int AB :1;
	unsigned int UEX :1;
	unsigned int HST :1;
	unsigned int PCB :1;
	unsigned int SWX :1;
	unsigned int NSW :1;
	unsigned int RRT :1;
	unsigned int BOR :1;
	unsigned int POE :1;
	unsigned int TVW :1;
	unsigned int RE :1;
	unsigned int HIN :1;
	unsigned int PIN :1;
	unsigned int IIN :1;
} BC_ISW_TYPE;

typedef struct {
	unsigned int TF :1;
	unsigned int DBA :1;
	unsigned int SSF :1;
	unsigned int BSY :1;
	unsigned int BRC :1;
	unsigned int RS :3;
	unsigned int SRQ :1;
	unsigned int INS :1;
	unsigned int ME :1;
	unsigned int TA :5;
} BC_AB_TYPE;

typedef struct {
	unsigned int IDP :16;
} BC_IDP_TYPE;

typedef struct {
	unsigned int HDP :16;
} BC_HDP_TYPE;

typedef struct {
	unsigned int TF :1;
	unsigned int ME :1;
	unsigned int RXR :1;
	unsigned int RXA :1;
	unsigned int ZERO1 :7; // 7 BIT A ZERO
	unsigned int TXR :1;
	unsigned int TXA :1;
	unsigned int ZERO2 :3; // 3 BIT A ZERO
} HS_STATUS_WORD_TYPE;

typedef struct {
	unsigned int INUM :6; // in ADA il tipo era HS_QUEUE_RANGE_TYPE
	unsigned int RESERVED :10;
} HS_INTERRUPT_POINTER_TYPE;

typedef struct {
	unsigned short ACTION_WORD;
	unsigned short SPARE;
	unsigned short EFFECTIVE_DATA_ADDRESS;
	unsigned short TABLE_POINTER_ADDRESS;
	HS_STATUS_WORD_TYPE HS_STATUS_WORD;
	unsigned short HS_LAST_ACTION_WORD;
	unsigned short HS_BIT_WORD;
	HS_INTERRUPT_POINTER_TYPE INTERRUPT_POINTER;
	unsigned short PREAMBLE_S_B_WORD;
	unsigned short S_E_DELIMITER_FORMAT;
	unsigned short WRONG_BIT_ERROR;
	unsigned short BITE_DATA_ADDRESS;
} HS_CONTROL_BLOCK_TYPE;

typedef struct {
	unsigned int TFF :1;
	unsigned int BCA :1;
	unsigned int SUB :1;
	unsigned int BSY :1;
	unsigned int SPARE2 :4;
	unsigned int SRQ :1;
	unsigned int SPARE1 :7;
} RT_SKELETON_TYPE;

typedef struct {
	unsigned short HS_DUMMY_ARRAY_TYPE[18];
} HS_DUMMY_ARRAY_TYPE;
//typedef unsigned short[18] HS_DUMMY_ARRAY_TYPE;

enum B_FIELD_TYPE {
	LANE_A = 0, LANE_B = 1
};

enum T_R_TYPE {
	RT_RX = 0, RT_TX = 1
};

typedef struct {
	unsigned int ETR :1;
	unsigned int IST :1;
	unsigned int TXS :1;
	unsigned int OTS :1;
	unsigned int RES :1;
	unsigned int MER :1;
	unsigned int HWE :1;
	unsigned int MSG_ID :7;
	T_R_TYPE T_R :1;
	B_FIELD_TYPE BUS :1;
} HS_INTERRUPT_WORD_TYPE;

typedef struct {
	HS_INTERRUPT_WORD_TYPE ISW;
	unsigned short TPA;
} HS_QUEUE_ELEM_TYPE;

typedef struct {
	HS_QUEUE_ELEM_TYPE HS_QUEUE_TYPE[64];
} HS_QUEUE_TYPE;
//typedef HS_QUEUE_ELEM_TYPE[64] HS_QUEUE_TYPE;

typedef struct {
	RT_ICW_TYPE INTERFACE_CONTROL;
	unsigned short BASE_ADDRESS;
	unsigned short COMMAND_WORD_LIST_PTR;
	RT_ISW_TYPE INTERFACE_STATUS;
	unsigned short ILLEGAL_MODECODE_MASK;
	unsigned short INTERRUPT_MASK;
	short VECTOR; // in ADA è VECTOR_WORD cioè BUS_WORD
	unsigned short RESERVED;
	RT_EBW_TYPE ERROR_BITE;
	unsigned short RAM_AREA_INFO;
	unsigned short MONITOR_BUFFER_START_ADDRESS;
	unsigned short MONITOR_BUFFER_END_ADDRESS;
} LS_RT_CONTROL_BLOCK_TYPE;

typedef struct {
	BC_ICW_TYPE ICW;
	unsigned short BASE_ADDRESS;
	unsigned short IAWLP;
	unsigned short RESERVED[4]; // in ADA è diverso (è nell'heap)
	unsigned short MODE_DATA_WORD;
	BC_EBW_TYPE ERROR_BITE;
	unsigned short RESERVED1;
	unsigned short AEW;
} LS_BC_CONTROL_BLOCK_TYPE;

typedef struct {
	unsigned int ENE :1;
	unsigned int ENM :1;
	unsigned int ILL :1;
	unsigned int NDE :1;
	unsigned int SIZE :7;
	unsigned int RESERVED2 :1;
	unsigned int ESC :1;
	unsigned int RESERVED1 :3;
} HS_MID_CW_DT_TYPE;

typedef union {
	char raw[sizeof(HS_MID_CW_DT_TYPE)];
	HS_MID_CW_DT_TYPE HS_MID_CW_DT;
} HS_MID_CW_DT_UNION_TYPE;

typedef struct {
	unsigned int WORD_COUNT :5;
	unsigned int ZERO :4;
	unsigned int RCN :1;
	unsigned int MDI :1;
	unsigned int SIL :1;
	unsigned int EDB :1;
	unsigned int ERI :1;
	unsigned int RCI :1;
	unsigned int MRE :1;
} SUBADDRESS_CONTROL_WORD_TYPE;

typedef union{
    char raw[sizeof(SUBADDRESS_CONTROL_WORD_TYPE)];
    SUBADDRESS_CONTROL_WORD_TYPE SUBADDRESS_CONTROL_WORD;
} SUBADDRESS_CONTROL_WORD_UNION_TYPE;

typedef struct {
	SUBADDRESS_CONTROL_WORD_TYPE SUBADDRESS_CONTROL;
	unsigned short ITF_DATA_PTR;
	unsigned short HOST_DATA_PTR;
	unsigned short TIME_TAG_WORD;
} SUBADDRESS_DESCRIPTOR_TYPE;

typedef struct {
	SUBADDRESS_DESCRIPTOR_TYPE LS_DESCRIPTOR_TABLE_TYPE[32];
} LS_DESCRIPTOR_TABLE_TYPE;
//typedef SUBADDRESS_DESCRIPTOR_TYPE[32] LS_DESCRIPTOR_TABLE_TYPE;

typedef struct {
	unsigned int WC_MC :5;
	unsigned int SUBADDR :5; // in ADA il tipo è BUS_SUBADDRESS_TYPE
	T_R_TYPE T_R;
	unsigned int ADDR :5; // in ADA il tipo è BUS_ADDRESS
} MIL_BUS_CMD_TYPE;

typedef struct {
	MIL_BUS_CMD_TYPE CW;
	RT_ISW_TYPE ISW;
} RT_QUEUE_ELEM_TYPE;

typedef struct {
	RT_QUEUE_ELEM_TYPE RT_QUEUE_TYPE[32];
} RT_QUEUE_TYPE;
//typedef RT_QUEUE_ELEM_TYPE[32] RT_QUEUE_TYPE;

typedef struct {
	unsigned short IAW;
	BC_ISW_TYPE ISW;
	unsigned short AW1;
	unsigned short AW2;
} BC_QUEUE_ELEM_TYPE;

typedef struct {
	BC_QUEUE_ELEM_TYPE BC_QUEUE_TYPE[32];
} BC_QUEUE_TYPE;
//typedef BC_QUEUE_ELEM_TYPE[32] BC_QUEUE_TYPE;

typedef struct {
	unsigned short ITF_DATA_PTR;
	unsigned short HOST_DATA_PTR;
} DATA_POINTER_TYPE;

typedef struct {
	DATA_POINTER_TYPE POINTER_TABLE_TYPE[4][512];
} POINTER_TABLE_TYPE;
//typedef DATA_POINTER_TYPE[4][512] POINTER_TABLE_TYPE;

typedef struct {
	unsigned int BIT_ID :3; // in ADA il tipo è BIT_ERROR_TYPE (non ho però trovato la definizione)
	unsigned int SPARE :13;
} BIT_IDENTITY_WORD_TYPE;

typedef struct {
	DATA_POINTER_TYPE MODE_CODE_PTR; // dei 128 cosi lo zero è usato per il modecode
	DATA_POINTER_TYPE NORM_PTR[127];
} HS_DESCRIPTOR_TABLE_TYPE;

typedef struct {
	unsigned short ID_CODE;
	unsigned short PAR1;
	unsigned short PAR2;
} FAIL_BLOCK_TYPE;

typedef struct {
	unsigned int PASS_FAIL :8;
	unsigned int TEST_COMPLETE :8;
	unsigned short TEST_BLOCK_LENGTH;
	BIT_IDENTITY_WORD_TYPE BIT_IDENTITY;
	unsigned short AFFECTED_MODULE;
	unsigned short ETI_READING;
	FAIL_BLOCK_TYPE FAIL[22]; // dimensione dedotta dagli indirizzi
} TIB1_TYPE;

typedef struct {
	unsigned short SPEC_PBIT_IND1;
	unsigned short SPEC_PBIT_IND2;
	unsigned short NEXT_AVAIL_ADDR_PTR;
	unsigned short CBIT_ERROR_FLAG;
	unsigned short GO_IBIT1;
	unsigned short GO_IBIT2;
	unsigned short BIT_RAM_SPARE[10];
	TIB1_TYPE TIB1;
} BIT_RAM_TYPE;

typedef struct {
	unsigned short CLR_STACK;
	unsigned short HALT;
} HALT_AREA_TYPE;

typedef struct {
	unsigned short CLR_STACK;
	unsigned short IW;
	unsigned short BUS_CMD;
} DBC_AREA_TYPE;

typedef struct {
	unsigned int ENE :1; // bit più significativi
	unsigned int ENM :1;
	unsigned int ILL :1;
	unsigned int RESERVED :13; // bit meno significativi
} HS_MID_CW_ST_TYPE;

typedef union {
	char raw[sizeof(HS_MID_CW_ST_TYPE)];
	HS_MID_CW_ST_TYPE HS_MID_CW_ST;
} HS_MID_CW_ST_UNION_TYPE;

typedef struct {
	HS_MID_CW_ST_TYPE MID_CW;
	unsigned short INFO_TX_DATA;
	unsigned short INFO_RX_DATA;
} HS_BITE_BUFFER_TYPE;

typedef struct {
	unsigned short OPCODE;
	unsigned short OFFSET;
} BRANCH_TYPE;

typedef struct {
	BRANCH_TYPE SUB_GR[6]; // in ADA questo vettore è a sua volta un tipo che ha un nome
	BRANCH_TYPE SYS_AC;
	BRANCH_TYPE PERF_AC;
	unsigned short HOLD_INSTR;
} ONE_MINOR_LOOP_TYPE;

typedef struct {
	ONE_MINOR_LOOP_TYPE MAJOR_LOOPS_ARRAY_TYPE[4][32];
} MAJOR_LOOPS_ARRAY_TYPE;
//typedef ONE_MINOR_LOOP_TYPE[4][32] MAJOR_LOOPS_ARRAY_TYPE;

typedef struct {
	HS_MID_CW_DT_TYPE MID_CW;
	unsigned short FRAME_CONTROL;
	unsigned short DSTN_ADDRESS;
	unsigned short WORD_COUNT;
} HS_DUMMY_BUFFER_TYPE;

typedef struct {
	HS_MID_CW_DT_TYPE MID_CW;
	unsigned short FRAME_CONTROL;
	unsigned short DSTN_ADDRESS;
	unsigned short WORD_COUNT;
	unsigned short INFO[32]; // in ADA questo vettore è a sua volta un tipo che ha un nome
} HS_WR_AR_BUFFER_TYPE;

typedef struct {
	unsigned int IRES :1;
	unsigned int ITXS :1;
	unsigned int IOVTS :1;
	unsigned int IRESV :1;
	unsigned int ILLR :1;
	unsigned int ILLT :1;
	unsigned int ILLO :1;
	unsigned int ILLN :1;
	unsigned int RESERVED :8;
} HS_MID_CW_MC_TYPE;

typedef struct {
	BRANCH_TYPE CALL[10]; // in ADA questo vettore è a sua volta un tipo che ha un nome
	unsigned short RET_OPCODE;
} ACYCLIC_CALL_TYPE;

typedef struct {
	BRANCH_TYPE JUMP;
	unsigned short AREA[53]; // dimensione dedotta dagli indirizzi (in ADA è nell'heap)
} PERF_AC_INSTR_TYPE;

typedef struct {
	unsigned short BUFFER_TYPE[32];
} BUFFER_TYPE;
//typedef unsigned short[32] BUFFER_TYPE;

typedef struct {
	unsigned short MON_AREA_TYPE[4]; // in ADA è nell'heap
} MON_AREA_TYPE;
//typedef unsigned short[4] MON_AREA_TYPE;  // in ADA è nell'heap

typedef struct {
	unsigned int ACT :1;
	unsigned int DEM :1;
	unsigned int DWD :1;
	unsigned int EI0 :1;
	unsigned int EI1 :1;
	unsigned int EI2 :1;
	unsigned int BIT :1;
	unsigned int END_BIT :1;
	unsigned int ENA :1;
	unsigned int RESERVED :6;
	unsigned int TST :1;
} HAND_BC_CW_TYPE;

typedef struct {
	unsigned int ACT :1;
	unsigned int DEM :1;
	unsigned int DWD :1;
	unsigned int EI0 :1;
	unsigned int EI1 :1;
	unsigned int EI2 :1;
	unsigned int BIT :1;
	unsigned int END_BIT :1;
	unsigned int ENA :1;
	unsigned int WTO :1;
	unsigned int HIA :1;
	unsigned int LOA :1;
	unsigned int BAC :1;
	unsigned int GONOGO :1;
	unsigned int IP :2;
} HAND_BC_SW_TYPE;

typedef struct {
	HAND_BC_CW_TYPE INT0_CWORD;
	HAND_BC_CW_TYPE INT1;
	HAND_BC_CW_TYPE INT2;
	HAND_BC_CW_TYPE INT3;
	HAND_BC_SW_TYPE SWORD;
	unsigned short ML_TIMER;
	unsigned short DIS_ISNOGO;
	unsigned short ENA_ISNOGO;
	unsigned short* DONT_CARE; // new unsigned short[262136];
} BC_HAND_TYPE;

typedef struct {
	BC_HAND_TYPE BC_HAND_ARRAY_TYPE[2][1]; // la prima riga è AVIONICS, la seconda è ATTACK
} BC_HAND_ARRAY_TYPE;
//typedef BC_HAND_TYPE[2][1] BC_HAND_ARRAY_TYPE;   // la prima riga è AVIONICS, la seconda è ATTACK

typedef struct {
	unsigned short RESTART_HS;
	unsigned short* DONT_CARE; // new unsigned short[262143];
} RESTART_HS_TYPE;

typedef struct {
	RESTART_HS_TYPE RESTART_HS_ARRAY_TYPE[2][1]; // la prima riga è AVIONICS, la seconda è ATTACK
} RESTART_HS_ARRAY_TYPE;
//typedef RESTART_HS_TYPE[2][1] RESTART_HS_ARRAY_TYPE;  // la prima riga è AVIONICS, la seconda è ATTACK

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned short LS_RT_CONTROL_BLOCK_OFFSET = 8
		* sizeof(HS_CONTROL_BLOCK_TYPE) / 16 + // size of HS_CONTROL_BLOCK
		8 * sizeof(HS_DUMMY_ARRAY_TYPE) / 16 + // size of HS_DUMMY
		8 * sizeof(unsigned short) / 16 + // size of LS_CONTROL_BLOCK_POINTER
		8 * sizeof(unsigned short) / 16 + // size of LS_PROGRAM_POINTER
		8 * sizeof(HS_QUEUE_TYPE) / 16; // size of HS_QUEUE

const unsigned short LS_BC_CONTROL_BLOCK_OFFSET = LS_RT_CONTROL_BLOCK_OFFSET + // offset of LS_RT_CONTROL_BLOCK
		8 * sizeof(LS_RT_CONTROL_BLOCK_TYPE) / 16; // size of LS_RT_CONTROL_BLOCK

const unsigned short HS_ILL_INTR_MID_CW_OFFSET = LS_BC_CONTROL_BLOCK_OFFSET + // offset of LS_BC_CONTROL_BLOCK
		8 * sizeof(LS_BC_CONTROL_BLOCK_TYPE) / 16; // size of LS_BC_CONTROL_BLOCK

const unsigned short RT_QUEUE_LOWER_BOUND = HS_ILL_INTR_MID_CW_OFFSET + // offset of HS_ILL_INTR_MID_CW
		8 * sizeof(HS_MID_CW_DT_TYPE) / 16 + // size of HS_ILL_INTR_MID_CW
		8 * sizeof(LS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of LS_RT_DESC_TABLE_RX
		8 * sizeof(LS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of LS_RT_DESC_TABLE_TX
		8 * sizeof(LS_DESCRIPTOR_TABLE_TYPE) / 16; // size of LS_RT_DESC_TABLE_BROAD

const unsigned short BC_QUEUE_LOWER_BOUND = RT_QUEUE_LOWER_BOUND + // offset of RT_QUEUE
		8 * sizeof(RT_QUEUE_TYPE) / 16; // size of RT_QUEUE

const unsigned short HS_ILL_NO_INTR_MID_CW_OFFSET = BC_QUEUE_LOWER_BOUND + // offset of BC_QUEUE
		8 * sizeof(BC_QUEUE_TYPE) / 16 + // size of BC_QUEUE
		8 * sizeof(BUFFER_TYPE) / 16 + // size of LS_WR_AR_BUFFER
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_RX
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_TX
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_RX_BROAD
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_TX_BROAD
		8 * sizeof(BIT_RAM_TYPE) / 16 + // size of BIT_RAM
		8 * sizeof(HALT_AREA_TYPE) / 16 + // size of HALT_AREA
		8 * sizeof(HALT_AREA_TYPE) / 16 + // size of NEW_MODE_AREA
		8 * sizeof(MON_AREA_TYPE) / 16 + // size of MON_BUFFER
		8 * sizeof(DBC_AREA_TYPE) / 16 + // size of DBC_AREA
		8 * sizeof(HS_BITE_BUFFER_TYPE) / 16 + // size of HS_BITE_BUFFER
		8 * sizeof(MAJOR_LOOPS_ARRAY_TYPE) / 16; // size of MAJOR_LOOP

const unsigned short ACYCLIC_CALL_LOWER_BOUND = HS_ILL_NO_INTR_MID_CW_OFFSET + // offset of HS_ILL_NO_INTR_MID_CW
		8 * sizeof(HS_MID_CW_DT_TYPE) / 16 + // size of HS_ILL_NO_INTR_MID_CW
		8 * sizeof(HS_DUMMY_BUFFER_TYPE) / 16 + // size of HS_DUMMY_BUFFER
		8 * sizeof(POINTER_TABLE_TYPE) / 16 + // size of BC_POINTER_TABLE
		8 * sizeof(HS_WR_AR_BUFFER_TYPE) / 16 + // size of HS_WR_AR_BUFFER
		8 * sizeof(HS_MID_CW_MC_TYPE) / 16 + // size of HS_MODE_CMD_NRX_MID_CW
		8 * sizeof(HS_MID_CW_MC_TYPE) / 16 + // size of HS_MODE_CMD_NTX_MID_CW
		8 * sizeof(HS_MID_CW_MC_TYPE) / 16 + // size of HS_MODE_CMD_BRX_MID_CW
		8 * sizeof(HS_MID_CW_MC_TYPE) / 16; // size of HS_MODE_CMD_BTX_MID_CW

const unsigned short ACYCLIC_INSTR_LOWER_BOUND = ACYCLIC_CALL_LOWER_BOUND + // offset of ACYCLIC_CALL
		8 * sizeof(ACYCLIC_CALL_TYPE) / 16; // size of ACYCLIC_CALL

const unsigned short SYS_AC_INSTR_SIZE = 60; // size of ACYCLIC_INSTR

//-- start position (within 64 Kword of LINC) of the PERF_INSTR (excluding the jump at the top);
const unsigned short PERF_AC_INSTR_LOWER_BOUND = ACYCLIC_INSTR_LOWER_BOUND + // offset of ACYCLIC_INSTR
		SYS_AC_INSTR_SIZE + // size of ACYCLIC_INSTR
		8 * sizeof(BRANCH_TYPE) / 16; // size of PERF_INSTR.JUMP

typedef struct {
	/*
	 size  offset  offset
	 DEC    HEX     HEX
	 word   word    byte
	 */
	HS_CONTROL_BLOCK_TYPE HS_CONTROL_BLOCK; //  12      0      0
	HS_DUMMY_ARRAY_TYPE HS_DUMMY; //  18      C     18
	unsigned short LS_CONTROL_BLOCK_POINTER; //   1     1E     3C
	unsigned short LS_PROGRAM_POINTER; //   1     1F     3E
	HS_QUEUE_TYPE HS_QUEUE; // 128     20     40
	LS_RT_CONTROL_BLOCK_TYPE LS_RT_CONTROL_BLOCK; //  12     A0    140
	LS_BC_CONTROL_BLOCK_TYPE LS_BC_CONTROL_BLOCK; //  11     AC    158
	HS_MID_CW_DT_TYPE HS_ILL_INTR_MID_CW; //   1     B7    16E
	LS_DESCRIPTOR_TABLE_TYPE LS_RT_DESC_TABLE_RX; // 128     B8    170
	LS_DESCRIPTOR_TABLE_TYPE LS_RT_DESC_TABLE_TX; // 128    138    270
	LS_DESCRIPTOR_TABLE_TYPE LS_RT_DESC_TABLE_BROAD; // 128    1B8    370
	RT_QUEUE_TYPE RT_QUEUE; //  64    238    470
	BC_QUEUE_TYPE BC_QUEUE; // 128    278    4F0
	BUFFER_TYPE LS_WR_AR_BUFFER; //  32    2F8    5F0
	HS_DESCRIPTOR_TABLE_TYPE HS_RT_DESC_TABLE_RX; // 256    318    630
	HS_DESCRIPTOR_TABLE_TYPE HS_RT_DESC_TABLE_TX; // 256    418    830
	HS_DESCRIPTOR_TABLE_TYPE HS_RT_DESC_TABLE_RX_BROAD; // 256    518    A30
	HS_DESCRIPTOR_TABLE_TYPE HS_RT_DESC_TABLE_TX_BROAD; // 256    618    C30
	BIT_RAM_TYPE BIT_RAM; //  87    718    E30
	HALT_AREA_TYPE HALT_AREA; //   2    76F    EDE
	HALT_AREA_TYPE NEW_MOD_AREA; //   2    771    EE2
	MON_AREA_TYPE MON_BUFFER; //   4    773    EE6
	DBC_AREA_TYPE DBC_AREA; //   3    777    EEE
	HS_BITE_BUFFER_TYPE HS_BITE_BUFFER; //   3    77A    EF4
	MAJOR_LOOPS_ARRAY_TYPE MAJOR_LOOP; // 544    77D    EFA
									   // 544    99D   133A
	// 544    BBD   177A
	// 544    DDD   1BBA
	HS_MID_CW_DT_TYPE HS_ILL_NO_INTR_MID_CW; //   1    FFD   1FFA
	HS_DUMMY_BUFFER_TYPE HS_DUMMY_BUFFER; //   4    FFE   1FFC
	POINTER_TABLE_TYPE BC_POINTER_TABLE; //1024   1002   2004
	//1024   1402   2804
	//1024   1802   3004
	//1024   1C02   3804
	HS_WR_AR_BUFFER_TYPE HS_WR_AR_BUFFER; //  36   2002   4004
	HS_MID_CW_MC_TYPE HS_MODE_CMD_NRX_MID_CW; //   1   2026   404C
	HS_MID_CW_MC_TYPE HS_MODE_CMD_NTX_MID_CW; //   1   2027   404E
	HS_MID_CW_MC_TYPE HS_MODE_CMD_BRX_MID_CW; //   1   2028   4050
	HS_MID_CW_MC_TYPE HS_MODE_CMD_BTX_MID_CW; //   1   2029   4052
	ACYCLIC_CALL_TYPE ACYCLIC_CALL; //  21   202A   4054
	// l'offset del primo elemento del vettore ACYCLIC_INSTR è ACYCLIC_INSTR_LOWER_BOUND
	unsigned short ACYCLIC_INSTR[60]; //  60   203F   407E
	// l'offset di PERF_INSTR è PERF_AC_INSTR_LOWER_BOUND
	PERF_AC_INSTR_TYPE PERF_INSTR; //  55   207B   40F6
	// l'offset del primo elemento del vettore PERF_FAST_INSTR è PERF_FAST_OFFSET
	unsigned short PERF_FAST_INSTR[12]; //  12   20B2   4164
} FIXED_AREA_TYPE;

//const unsigned short DYNAMIC_AREA_LOWER_BOUND = unsigned short(sizeof(FIXED_AREA_TYPE)/16);
const unsigned short DYNAMIC_AREA_LOWER_BOUND = sizeof(FIXED_AREA_TYPE) / 16;

typedef struct {
	/*
	 offset  offset  offset
	 DEC     HEX     HEX
	 word    word    byte
	 */
	FIXED_AREA_TYPE FIXED; //    0       0       0
	// l'offset del primo elemento del vettore DYNAMIC è DYNAMIC_AREA_LOWER_BOUND
	unsigned short* DYNAMIC; // new unsigned short[57154];                                         // 8382    20BE    417C
	unsigned short* DONT_CARE1; // new unsigned short[2031616];                                    //65536   10000   20000
	unsigned short RESTART_LS; //       200000  400000
	unsigned short TIME_TAG_COUNTER; //       200001  400002
	RT_SKELETON_TYPE RT_SKELETON_REGISTER; //       200002  400004
	unsigned short* DONT_CARE2; // new unsigned short[2097149];                                    //       200003  400006
	unsigned short* EEPROM; // new unsigned short[8192];                                           //       400000  800000
	unsigned short* DONT_CARE3; // new unsigned short[2088960];                                    //       402000  804000
	unsigned short SET_NOGO; //       600000  C00000
	unsigned short* DONT_CARE4; // new unsigned short[262143];                                     //       600001  C00002
	unsigned short RESET_NOGO; //       640000  C80000
	unsigned short* DONT_CARE5; // new unsigned short[131071];                                     //       640001  C80002
	unsigned short ENABLE_3909_NMI; //       660000  CC0000
	unsigned short* DONT_CARE6; // new unsigned short[131071];                                     //       660001  CC0002
	unsigned short CRIT_DISCR_IN_OUT; //       680000  D00000
	unsigned short* DONT_CARE7; // new unsigned short[262143];                                     //       680001  D00002
	BC_HAND_ARRAY_TYPE BC_HAND; //       6C0000  D80000
								//       700000  E00000
	unsigned short NOT_CRIT_DISCR_IN_OUT; //       740000  E80000
	unsigned short NOT_CRIT_DISCR_OUT_BIT; //       740001  E80002
	unsigned short* DONT_CARE8; // new unsigned short[262142];                                     //       740002  E80004
	RESTART_HS_ARRAY_TYPE RESTART_HS; //       780000  F00000
									  //       7C0000  F80000
} STIM_MEM_TYPE;

const int AVIONICS_BASE_ADDRESS = 0x28000000; // DA LEVARE
const int ATTACK_BASE_ADDRESS = 0x29000000;   // DA LEVARE

const unsigned int AVIONICS_BASE_ADDRESS_STIMP = 0x28000000; // start address of the STIM memory   // DA TOGLIERE
const unsigned int ATTACK_BASE_ADDRESS_STIMP = 0x29000000;     // DA TOGLIERE
const unsigned int SIDE_A_BASE_ADDRESS_SIMP1 = 0x00000000;     // DA TOGLIERE
const unsigned int SIDE_B_BASE_ADDRESS_SIMP1 = 0x11111111;     // DA TOGLIERE
const unsigned int SIDE_A_BASE_ADDRESS_SIMP2 = 0x22222222;     // DA TOGLIERE
const unsigned int SIDE_B_BASE_ADDRESS_SIMP2 = 0x33333333;     // DA TOGLIERE

typedef struct struct_interface{
	char board_name[24];  // STIMP, SIMP1 or SIMP2
	unsigned int type;   // 0=NONE   1=3910   2=3838
	unsigned int base_address;
	unsigned int arbitered_io;
	unsigned int direct_io;
	unsigned int restart_hs;
	unsigned int memory_size;
	unsigned int bit_history_addr;
	unsigned int bit_history_size;
	unsigned char side;
	struct_interface(){
		memset(this,0,sizeof(struct_interface));
	}

} interfaccia;

//STIM_MEM_TYPE STIM_MEM_ARRAY_TYPE[2][1];     // la prima riga è AVIONICS, la seconda è ATTACK

// Word offset for most used LS locations

const unsigned short LS_RT_CB_OFFSET = LS_RT_CONTROL_BLOCK_OFFSET;
const unsigned short LS_BC_CB_OFFSET = LS_BC_CONTROL_BLOCK_OFFSET;

const unsigned short PERF_FAST_OFFSET = 0x20B2; // offset of PERF_FAST_INSTR

const unsigned short HALT_AREA_OFFSET = BC_QUEUE_LOWER_BOUND + // offset of BC_QUEUE
		8 * sizeof(BC_QUEUE_TYPE) / 16 + // size of BC_QUEUE
		8 * sizeof(BUFFER_TYPE) / 16 + // size of LS_WR_AR_BUFFER
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_RX
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_TX
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_RX_BROAD
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 + // size of HS_RT_DESC_TABLE_TX_BROAD
		8 * sizeof(BIT_RAM_TYPE) / 16; // size of BIT_RAM

const unsigned short NEW_MOD_AREA_OFFSET = HALT_AREA_OFFSET + // offset of HALT_AREA
		8 * sizeof(HALT_AREA_TYPE) / 16; // size of HALT_AREA

const unsigned short DBC_AREA_OFFSET = NEW_MOD_AREA_OFFSET + // offset of NEW_MOD_AREA
		8 * sizeof(HALT_AREA_TYPE) / 16 + // size of NEW_MOD_AREA
		8 * sizeof(MON_AREA_TYPE) / 16; // size of MON_BUFFER

const unsigned short DBC_INSTR_OFFSET = DBC_AREA_OFFSET + 1;

const unsigned short ACYCLIC_CALL_OFFSET = ACYCLIC_CALL_LOWER_BOUND;

const unsigned short ACYCLIC_INSTR_OFFSET = ACYCLIC_INSTR_LOWER_BOUND;

const unsigned short ACYCLIC_INSTR_LAST_OFFSET = ACYCLIC_INSTR_LOWER_BOUND
		+ SYS_AC_INSTR_SIZE - 1;

const unsigned short RT_QUEUE_OFFSET = RT_QUEUE_LOWER_BOUND;

const unsigned short BC_QUEUE_OFFSET = BC_QUEUE_LOWER_BOUND;

const unsigned short RT_QUEUE_LAST_OFFSET =
		RT_QUEUE_LOWER_BOUND
				+ (8 * sizeof(RT_QUEUE_TYPE) / 16
						- 8 * sizeof(RT_QUEUE_ELEM_TYPE) / 16);

const unsigned short BC_QUEUE_LAST_OFFSET =
		BC_QUEUE_LOWER_BOUND
				+ (8 * sizeof(BC_QUEUE_TYPE) / 16
						- 8 * sizeof(BC_QUEUE_ELEM_TYPE) / 16);

const unsigned short LS_WR_AR_BUFFER_OFFSET = BC_QUEUE_LOWER_BOUND + // offset of BC_QUEUE
		8 * sizeof(BC_QUEUE_TYPE) / 16; // size of BC_QUEUE

const unsigned short PERF_AREA_OFFSET = PERF_AC_INSTR_LOWER_BOUND;

const unsigned short FIRST_MAJOR_LOOP_OFFSET = DBC_AREA_OFFSET + // offset of DBC_AREA
		8 * sizeof(DBC_AREA_TYPE) / 16 + // size of DBC_AREA
		8 * sizeof(HS_BITE_BUFFER_TYPE) / 16; // size of HS_BITE_BUFFER

const unsigned short MAJOR_LOOPS_OFFSET[4] = { FIRST_MAJOR_LOOP_OFFSET,
		FIRST_MAJOR_LOOP_OFFSET
				+ (8 * sizeof(ONE_MINOR_LOOP_TYPE) / 16) * 32 * 1,
		FIRST_MAJOR_LOOP_OFFSET
				+ (8 * sizeof(ONE_MINOR_LOOP_TYPE) / 16) * 32 * 2,
		FIRST_MAJOR_LOOP_OFFSET
				+ (8 * sizeof(ONE_MINOR_LOOP_TYPE) / 16) * 32 * 3 };

const unsigned short HS_DUMMY_BUFFER_OFFSET = MAJOR_LOOPS_OFFSET[0] + // offset of MAJOR_LOOP
		8 * sizeof(MAJOR_LOOPS_ARRAY_TYPE) / 16 + // size of MAJOR_LOOP
		8 * sizeof(HS_MID_CW_DT_TYPE) / 16; // size of HS_ILL_NO_INTR_MID_CW

const unsigned short BC_POINTER_TABLE_OFFSET[4] = { HS_DUMMY_BUFFER_OFFSET + // offset of HS_DUMMY_BUFFER
		8 * sizeof(HS_DUMMY_BUFFER_TYPE) / 16, // size of HS_DUMMY_BUFFER
HS_DUMMY_BUFFER_OFFSET + 8 * sizeof(HS_DUMMY_BUFFER_TYPE) / 16
		+ 8 * sizeof(DATA_POINTER_TYPE) / 16 * 512, HS_DUMMY_BUFFER_OFFSET
		+ 8 * sizeof(HS_DUMMY_BUFFER_TYPE) / 16
		+ 8 * sizeof(DATA_POINTER_TYPE) / 16 * 512 * 2, HS_DUMMY_BUFFER_OFFSET
		+ 8 * sizeof(HS_DUMMY_BUFFER_TYPE) / 16
		+ 8 * sizeof(DATA_POINTER_TYPE) / 16 * 512 * 3 };

// Word offset for most used HS locations

const unsigned short HS_WR_AR_BUFFER_OFFSET = BC_POINTER_TABLE_OFFSET[0] + // offset of BC_POINTER_TABLE
		8 * sizeof(POINTER_TABLE_TYPE) / 16; // size of BC_POINTER_TABLE

const unsigned short HS_DESCR_TABLE_RX_OFFSET = LS_WR_AR_BUFFER_OFFSET + // offset of LS_WR_AR_BUFFER
		8 * sizeof(BUFFER_TYPE) / 16; // size of LS_WR_AR_BUFFER

const unsigned short HS_DESCR_TABLE_BROAD_OFFSET = HS_DESCR_TABLE_RX_OFFSET + // offset of HS_RT_DESC_TABLE_RX
		8 * sizeof(HS_DESCRIPTOR_TABLE_TYPE) / 16 * 2; // size of HS_RT_DESC_TABLE_RX/TX

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ACTION_WORD_OFFSET 0x0
#define EFFECTIVE_DATA_ADDRESS_OFFSET 0x4
#define TABLE_POINTER_ADDRESS_OFFSET 0x6
#define PRSIZE_WORD_OFFSET 0x10
#define START_END_DELIMITER_FORMAT_OFFSET 0x12
#define BITE_DATA_ADDRESS_OFFSET 0x16
//#define MID_CONTROL_WORD_OFFSET 0xEF4
#define DATA_TX_OFFSET 0x2
#define DATA_RX_OFFSET 0x4
#define HS_STATUS_WORD_OFFSET 0x8
#define LAST_ACTION_WORD_OFFSET 0xA
#define HS_BIT_WORD_OFFSET 0xC
#define HS_POINTER_NUM_OFFSET 0xE
#define INTERRUPT_QUEUE_AREA 0x40
#define INTERRUPT_WORD_1_OFFSET 0x40
#define CB_POINTER_OFFSET 0x003C
#define PROGRAM_POINTER_OFFSET 0x003E
#define LS_RT_INTERFACE_CONTROL_WORD_OFFSET 0x0
#define LS_RT_SELFTEST_PROCEDURE_MASK_OFFSET 0x2
#define RESTART_LOW_SPEED_OFFSET 0x400000
#define INTERFACE_STATUS_WORD_OFFSET 0x6
#define LS_RT_BASE_ADDRESS_WORD_OFFSET 0x2
#define HS_WR_AR_BUFFER_TYPE_OFFSET 0x2000
#define LS_RT_DESC_TABLE_TX_SUB26_OFFSET 0x3A0
#define LS_RT_ERROR_BITE_WORD_OFFSET 0x10
#define LS_RT_RAM_BLOCK_INDEX_OFFSET 0x12
#define LS_RT_COMMAND_WORD_LIST_POINTER 0x4
//#define LS_RT_DESC_TABLE_RX_OFFSET 0x170
//#define LS_RT_DESC_TABLE_TX_OFFSET 0x270
#define BUFFER_TYPE_OFFSET 0x5F0
#define RT_SKELETON_REGISTER_OFFSET 0x400004
#define LS_BC_CONTROL_BLOCK_OFFSET 0x0
#define BC_POINTER_TABLE_OFFSET 0x2004
#define BC_QUEUE_TYPE_OFFSET 0x4F0
#define IDB_OFFSET 0xD00000
//RT LS SUBADDRESS DESCRIPTOR BLOCK OFFSET
#define SA_CONTROL_WORD_OFFSET 0x0
#define SA_INTERFACE_DATA_PNTR_OFFSET 0x2
#define SA_HOST_DATA_PNTR_OFFSET 0x4
#define SA_TIME_TAG_WORD_OFFSET 0x6

#define ICW_SELFTEST_VALUE 0x100
#define SELFTEST_PROCEURE_MASK_OFFSET 0x2

#define HS_IF_INTERFACE_DATA_PNTR_OFFSET 0x0
#define HS_IF_HOST_DATA_PNTR_OFFSET 0x2

#endif

