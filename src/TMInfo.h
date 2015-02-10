#ifndef _TM_INFO_SUPPY
#define _TM_INFO_SUPPY

#include <string>
#include <vector>

typedef struct _tagRECT
{
	_tagRECT& operator=(const _tagRECT& NewRect)
	{
		left		= NewRect.left;
		top			= NewRect.top;
		right		= NewRect.right;
		bottom		= NewRect.bottom;
		return *this;
	}
	_tagRECT(int nNewLeft =0,int nNewTop=0,int nNewRight =0,int nNewBottom =0)
	{
		left	= nNewLeft;
		top		= nNewTop;
		right	= nNewRight;
		bottom	= nNewBottom;
	}
	int left;
	int top;
	int right;
	int bottom;
}RECT;

typedef enum
{
	TM_TYPE_NONE	= -1,	//无类型
	TM_TYPE_4X3		= 0,	//4：3普通屏
	TM_TYPE_16X9			//16：9宽屏
}HPTM_TM_TYPE;

typedef enum
{
	TM_SUBTYPE_0_NONE		= -1,
	TM_SUBTYPE_1_1X1		= 0,
	TM_SUBTYPE_2_1X2_SPACE,
	TM_SUBTYPE_2_1X2_FULL,
	TM_SUBTYPE_3_L1_R2,
	TM_SUBTYPE_4_2X2,
	TM_SUBTYPE_4_L1_R3,
	TM_SUBTYPE_6_LT1_RD5,
	TM_SUBTYPE_8_LT1_RD7,
	TM_SUBTYPE_9_3X3,
	TM_SUBTYPE_10_T2_B2X4,
	TM_SUBTYPE_13_IN1_RD12,
	TM_SUBTYPE_16_4X4,
	TM_SUBTYPE_2_PIC_IN_PIC,

	TM_SUBTYPE_4_B1_T3,
	TM_SUBTYPE_5_L1_R4,
	TM_SUBTYPE_5_B1_T4,
	TM_SUBTYPE_6_T2_B4,
	TM_SUBTYPE_7_L2X2_R3,
	TM_SUBTYPE_10_LT1_RD9,
	TM_SUBTYPE_12_3X4,
	TM_SUBTYPE_24_LT1_RD5_X4,
	TM_SUBTYPE_25_5X5,
	TM_SUBTYPE_36_6X6,

	TVWALL_TYPE_TEST		= 100,
}HPTM_TM_SUBTYPE;

#define MAX_SCREEN  4

typedef struct _tagSCREEINFO
{
	_tagSCREEINFO()
	{
		tm_type		= TM_TYPE_4X3;
		tm_subtype	= TM_SUBTYPE_4_L1_R3;
		nWidth		= 1920;
		nHeight		= 1080;
	}
	_tagSCREEINFO& operator=(const _tagSCREEINFO& NewScreen)
	{
		tm_type		= NewScreen.tm_type;
		tm_subtype	= NewScreen.tm_subtype;
		nWidth		= NewScreen.nWidth;
		nHeight		= NewScreen.nHeight;
		return *this;
	}

	HPTM_TM_TYPE		tm_type;
	HPTM_TM_SUBTYPE		tm_subtype;
	unsigned int		nWidth;
	unsigned int		nHeight;
}SCREE_INFO,*LPSCREE_INFO;


class TMInfo
{
public:
	static void dbgprint(const char* fmt, ...);
	//static bool GetTMWndPos(HPTM_TM_TYPE type,HPTM_TM_SUBTYPE subtype,int nWndIndex,int& x,int& y,int& cx,int& cy);
	static bool GetTMWndPos(int width, int height, HPTM_TM_TYPE type,HPTM_TM_SUBTYPE subtype,std::vector<RECT>& PosArray);
	static int  GetTMWndCount(int subtype);

private:
	static void SetOneFull(std::vector<RECT>& PosArray);
	static void SetL1_R1_Space(std::vector<RECT>& PosArray);
	static void SetL1_R1(std::vector<RECT>& PosArray);
	static void Set2X2(std::vector<RECT>& PosArray);
	static void SetL1_R2(std::vector<RECT>& PosArray);
	static void SetL1_R3(std::vector<RECT>& PosArray);
	static void SetLT1_Round5(std::vector<RECT>& PosArray);
	static void SetLT1_Round7(std::vector<RECT>& PosArray);
	static void Set3X3(std::vector<RECT>& PosArray);
	static void SetT2_B2X4(std::vector<RECT>& PosArray);
	static void SetIn1_Round12(std::vector<RECT>& PosArray);
	static void Set4X4(std::vector<RECT>& PosArray);
	static void SetPicInPic(std::vector<RECT>& PosArray);
	static void SetB1_T3(std::vector<RECT>& PosArray);
	static void SetL1_R4(std::vector<RECT>& PosArray);
	static void SetB1_T4(std::vector<RECT>& PosArray);
	static void SetT2_B4(std::vector<RECT>& PosArray);
	static void SetL2X2_R3(std::vector<RECT>& PosArray);
	static void SetLT1_Round9(std::vector<RECT>& PosArray);
	static void Set3X4(std::vector<RECT>& PosArray);
	static void Set5X5(std::vector<RECT>& PosArray);
	static void Set6X6(std::vector<RECT>& PosArray);
	static void SetLT1_Round5_X4(std::vector<RECT>& PosArray);
	static void SetFloatWindow(std::vector<RECT>& PosArray);
};
#endif
