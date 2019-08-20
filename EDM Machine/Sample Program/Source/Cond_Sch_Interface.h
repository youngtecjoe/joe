// 
// Create:       che.z.l 2009.11.06 for changing of condition search interface(@R11007)
//

// change:
//					che.z.l 2010.05.24 for R11128(If SFCC2 data is not exist than output "SFCC00000000")(@R11128)
//					yao.x.c 2011.07.22 add for @11168

#ifndef Cond_Sch_Interface_h
#define Cond_Sch_Interface_h


#ifdef _AFXDLL
	#define DLL_FUNCTION __declspec(dllexport) 
#else
	#define DLL_FUNCTION __declspec(dllimport) 
#endif

typedef struct {
    char            lquid[32];          /* 加工液種類                    */
    char            wirem[32];          /* ﾜｲﾔ材質                       */
    double          wrdiam;             /* ﾜｲﾔ径                         */
    char            kind[32];           /* 加工形態                      */
    char            lqknd[32];          /* 液処理                        */
    char            mater[32];          /* ﾜｰｸ材質                       */
    double          thick;              /* 板厚                          */
    double          rough;              /* 面粗さ                        */
    /*for HI:51649 short*/long           cutn;               /* ｶｯﾄ回数                       */
	double			ofstajst;			/*オフセット調整データ*/
	/*for HI:51649 char*/long			aicon;				/*AIC出力するしない（１：mm 　２：inch その他：出力しない*/
    char            bson[32];           /* BS ON/OFF                     */
    char            comment[64];        /* ｺﾒﾝﾄ                          */
    /*for HI:51649 short*/long           cndflg;             /* 加工条件確定ﾌﾗｸﾞ         [@1] */
	long		SFCCFlag;	//SFCC出力するしない（１：mm２：inch ０：出力しない // @OutputSFCC
} SWF_CONDITION;

//++@10917
typedef struct {
    char            lquid[32];          /* 加工液種類                    */
    char            wirem[32];          /* ﾜｲﾔ材質                       */
    double          wrdiam;             /* ﾜｲﾔ径                         */
    char            kind[32];           /* 加工形態                      */
    char            lqknd[32];          /* 液処理                        */
    char            mater[32];          /* ﾜｰｸ材質                       */
    double          thick;              /* 板厚                          */
    double          rough;              /* 面粗さ                        */
    /*for HI:51649 short*/long           cutn;               /* ｶｯﾄ回数                       */
	double			ofstajst;			/*オフセット調整データ*/
	/*for HI:51649 char*/long			aicon;				/*AIC出力するしない（１：mm 　２：inch その他：出力しない*/
    char            bson[32];           /* BS ON/OFF                     */
    char            comment[64];        /* ｺﾒﾝﾄ                          */
    /*for HI:51649 short*/long           cndflg;             /* 加工条件確定ﾌﾗｸﾞ         [@1] */
	long		SFCCFlag;	//SFCC出力するしない（１：mm２：inch ０：出力しない // @OutputSFCC
	long           precision;
} SWF_CONDITION_GE;
//--@10917

/* 加工条件情報ﾊﾟﾗﾒｰﾀ */
typedef struct {
    long            MC_Code;            /* 加工条件ｺｰﾄﾞ                  */
    long            MC_FN_Code;         /* 仕上げ条件ｺｰﾄﾞ                */
    long            MC_Offset;          /* ｵﾌｾｯﾄ番号                     */
    double          MC_Offset_V;        /* ｵﾌｾｯﾄ量                       */
    double          MC_Sfs_Rgh;         /* 面粗さ                        */
    double          MC_Abt_Mch_Max;     /* 加工能力最大                  */
    double          MC_Abt_Mch_Min;     /* 加工能力最小                  */
    double          MC_Vlt;             /* 電圧                          */
    double          MC_Amp;             /* 電流                          */
    long            MC_MCB_Code;        /* 加工条件内容ﾘﾝｸｺｰﾄﾞ           */
} SWF_MchCon_SU;

/* 加工条件内容ﾊﾟﾗﾒｰﾀ */
typedef struct {
    long            MCB_Code;           /* 加工条件ｺｰﾄﾞ                  */
    long            MCB_ON;             /* ON                            */
    long            MCB_OFF;            /* OFF                           */
    long            MCB_IP;             /* IP                            */
    long            MCB_HRP;            /* HRP                           */
    long            MCB_MAO;            /* MAO                           */
    long            MCB_SV;             /* SV                            */
    long            MCB_V;              /* V                             */
    long            MCB_SF;             /* SF                            */
    long            MCB_C;              /* C                             */
    long            MCB_WT;             /* WT                            */
    long            MCB_WS;             /* WS                            */
    long            MCB_WP;             /* WP                            */
    long            MCB_WK;             /* WC                            */
	BOOL			MCB_PIK_FLAG;		/* Pika Flag                     */ // Add for @R010587
	long            MCB_PIK;
	long            MCB_CTRL;
} SWF_MCB_SU;

//add by huang.y @LQ33WS New struct for condition
typedef struct {
    long            MCB_Code;           /* 加工条件ｺｰﾄﾞ                  */
    long            MCB_ON;             /* ON                            */
    long            MCB_OFF;            /* OFF                           */
    long            MCB_IP;             /* IP                            */
    long            MCB_HRP;            /* HRP                           */
    long            MCB_MAO;            /* MAO                           */
    double			MCB_SV;             /* SV                            */
    double	        MCB_V;              /* V                             */
    long            MCB_SF;             /* SF                            */
    long            MCB_C;              /* C                             */
    long            MCB_WT;             /* WT                            */
    long            MCB_WS;             /* WS                            */
    long            MCB_WP;             /* WP                            */
    long            MCB_WK;             /* WC                            */
	BOOL			MCB_PIK_FLAG;		/* Pika Flag                     */ // Add for @R010587
	long            MCB_PIK;
	long            MCB_CTRL;
	long			MCB_PC;				/* PC							 */
	long			MCB_SK;				/* SK							 */
} SWF_MCB_SU_WS;
//end add

//begin: @BSA-HeartNc
typedef struct
{
	double	FN_UD_dm;
	double	FN_LD_dm;
	double	FN_UN_dm;
	double	FN_DN_dm;
	double	FN_UN_pos;
	double	FN_DN_pos;
	double	FN_1st_pls;
	double	FN_2nd_pls;
	double	FN_1st_UN;
	double	FN_2nd_UN;
	double	FN_1st_DN;
	double	FN_2nd_DN;
	double	FN_Wtr_Qty;
	double	FN_Ad_Tp;
}S_FINISH;
//end: @BSA-HeartNc

/*AICコード*/
typedef struct{
	long lnGroupFunction; // 出力のコードの種類：AICC : 0, SFCC : 1 // @OutputSFCC2
	/*for HI:51649 char*/long			code_inf;			/*0:ヘッダーのすぐ後ろに挿入するブロック　１：１ｓｔ加工の直前に挿入するブロック（QAICは、１をセットする*/
	char			NC_code[256];
	// long	SFCC_inf;   // 0:SFCC出力しない　１：SFCC出力する // @OutputSFCC // @OutputSFCC2
	// char	SFCC_NC_code[256];	// SFCCのNCコード // @OutputSFCC // @OutputSFCC2
} SWF_NC_PROC;


typedef struct tagTHDCOLOR {
							UINT nHT;	//  ｸﾟ ﾁﾁ ﾑﾕ ﾉｫ
							UINT nSHW;	//  ﾒ・ﾓｰ ﾑﾕ ﾉｫ
							UINT nBK;	//  ｱｳ ｾｰ ﾑﾕ ﾉｫ
							UINT nABK;	//  ｼ､ ｻ・ﾊｱ ｱｳ ｾｰ ﾑﾕ ﾉｫ
							UINT nTEXT;	//  ﾎﾄ ｱｾ ﾑﾕ ﾉｫ
					       } THDCOLOR;

	

DLL_FUNCTION int SearchWnd_PreTransMessage(MSG *pMsg);
DLL_FUNCTION void DoConditionSearch( char* str, CRect& rect, THDCOLOR* pCol, HWND hWnd, char *ss_in, UINT calling,UINT uint , UINT nativeflag , double SetteiData , INT iCondType , WORD Settei_Digital = 0 , long nTotalFileSize = 0, char * lpDataBasePathInitFile = NULL);//@R11128//@R011154
DLL_FUNCTION void DoOnceSearch( char * str, CRect& rect, THDCOLOR* pCol, HWND hWnd, char *ss_in, UINT calling, UINT uint , UINT nativeflag , double SetteiData , long outputaic , BOOL bOutputSFCC , char * searchNumber, BOOL& rtn, INT iCondType , WORD Settei_Digital = 0 , long nTotalFileSize = 0, char* lpDataBasePathInitFile = NULL);//@R11128//@R011154

DLL_FUNCTION int CondStringToStructure( char * lpString, SWF_CONDITION &swf, int &nDatabaseType );
DLL_FUNCTION int CondStringToStructure( char * lpString, SWF_CONDITION_GE &swf, int &nDatabaseType );

DLL_FUNCTION void CleanupConditionSearch();

DLL_FUNCTION int	CreateNC_Cond(SWF_CONDITION cnd, SWF_MchCon_SU *mchcon, SWF_MCB_SU *mcb, int type, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, char* lpDataBasePathInitFile = NULL, int nCondSchMode = 0);//@11168
DLL_FUNCTION int	CreateNC_Cond(SWF_CONDITION cnd, SWF_MchCon_SU *mchcon, SWF_MCB_SU_WS *mcb, int type, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, char* lpDataBasePathInitFile = NULL, int nCondSchMode = 0);//@11168
DLL_FUNCTION int	CreateNC_Cond(SWF_CONDITION_GE cnd, SWF_MchCon_SU *mchcon, SWF_MCB_SU *mcb, int type, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, char* lpDataBasePathInitFile = NULL, int nCondSchMode = 0);//@11168
DLL_FUNCTION int	CreateNC_Cond(SWF_CONDITION_GE cnd, SWF_MchCon_SU *mchcon, SWF_MCB_SU_WS *mcb, int type, SWF_NC_PROC* nc_proc , long *plnNcProcNum, S_FINISH *fin, char * lpDataBasePathInitFile = NULL, int nCondSchMode = 0);//@11168
DLL_FUNCTION void   RegisterWNFManualMessage();
DLL_FUNCTION void   DeleteMcdb();

//++@R011154
DLL_FUNCTION int   ConditionSearchConfig(IN DWORD dwSettingID,IN DWORD dwTypeID,IN LPVOID pValue);

#define	SETTINGID_IGNORE_NULL_SFCC			101 //Maruhi_R&D HI[27]
#define	SETTINGID_ANCSSETTING				102 //Maruhi_47
#define	SETTINGID_HECW_OPTION				103 //Maruhi_62

#define	ERROR_SUCCESS				0L
#define	ERROR_INVALID_SETTING_ID	-1L
#define	ERROR_INVALID_SETTING_TYPE	-2L
#define	ERROR_TYPE_MISMATCH			-3L
#define	ERROR_BAD_READ_POINT		-4L

#define	TYPE_DWORD		1
#define	TYPE_INT		2
#define	TYPE_DOUBLE		3
#define	TYPE_STRING		4

#define MIN_MTRL_CODE_NUM	0  //@R011154
#define MAX_MTRL_CODE_NUM	15  //@R011154
//--@R011154


#define	WNFM_CONDITION_SEARCH_OK	30608
#define	WNFM_DESTROY_CONDITION		30609

//++@11168
#define	COND_SCH_MODE_OCX		1

// -1: other error
#define CONDSCH_ERR_OTHER_CONDSCHING	-2// other conditions are searching
#define CONDSCH_ERR_FILENOTFIND			-3// condition file not find
#define CONDSCH_ERR_FILEOPENERROR 		-4// condition file open error
#define CONDSCH_ERR_COND_ERROR			-5// COND_COND Database error
#define CONDSCH_ERR_FORMATERROR			-6// Can't write error input data in database.
#define CONDSCH_ERR_MSGNOTFOUND			-7// MSG_COND.DAT not found. 

DLL_FUNCTION int	OutputMTRL(int nDatabaseType, int ncondType, char * chWirem);
//--@11168

#endif