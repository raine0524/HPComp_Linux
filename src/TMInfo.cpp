#include <stdio.h>
#include <stdarg.h>
#include "TMInfo.h"

static RECT s_rect;
static float s_rate1 = 0.75f;
static float s_rate2 = 16.0f/9.0f;

void TMInfo::dbgprint(const char* fmt, ...)
{
	const int MAXBUFLEN = 1024;
	char buffer1[MAXBUFLEN]={0};
	int buflen1 = sizeof(buffer1)-1;

	va_list args;
	va_start(args, fmt);
#ifdef WIN32
	_vsnprintf(buffer1,buflen1,fmt,args);
#else
	vsnprintf(buffer1,buflen1,fmt,args);
#endif
	va_end(args);

	char buffer2[MAXBUFLEN*2]={0};
	int buflen2 = sizeof(buffer2)-1;

#ifdef WIN32
	snprintf(buffer2, buflen2, "[%s:%d] %s", __FILE__, __LINE__, buffer1);
#else
	snprintf(buffer2, buflen2, "[%s:%s:%d] %s", __func__, __FILE__, __LINE__, buffer1);
#endif

#ifdef WIN32
#ifdef _CONSOLE
	printf(buffer2);
#else
	TRACE(buffer2);
#endif
#else
	printf(buffer2);
#endif
}

 int TMInfo::GetTMWndCount(int subtype)
 {
	 int nRet = 0;
	 bool bFloat = false;
	 if (subtype >= 100)
	 {
		 bFloat	= true;
		 nRet	= -1;
		 subtype -= 100;
	 }

	 switch (subtype)
	 {
	 case TM_SUBTYPE_1_1X1:
		 nRet = 1;
		 break;
	 case TM_SUBTYPE_2_1X2_SPACE:
	 case TM_SUBTYPE_2_1X2_FULL:
	 case TM_SUBTYPE_2_PIC_IN_PIC:
		 nRet = 2;
		 break;
	 case TM_SUBTYPE_3_L1_R2:
		 nRet = 3;
		 break;
	 case TM_SUBTYPE_4_2X2:
	 case TM_SUBTYPE_4_L1_R3:
	 case TM_SUBTYPE_4_B1_T3:
		 nRet = 4;
		 break;
	 case TM_SUBTYPE_5_L1_R4:
	 case TM_SUBTYPE_5_B1_T4:
		 nRet = 5;
		 break;
	 case TM_SUBTYPE_6_LT1_RD5:
	 case TM_SUBTYPE_6_T2_B4:
		 nRet = 6;
		 break;
	 case TM_SUBTYPE_7_L2X2_R3:
		 nRet = 7;
		 break;
	 case TM_SUBTYPE_8_LT1_RD7:
		 nRet = 8;
		 break;
	 case TM_SUBTYPE_9_3X3:
		 nRet = 9;
		 break;
	 case TM_SUBTYPE_10_T2_B2X4:
	 case TM_SUBTYPE_10_LT1_RD9:
		 nRet = 10;
		 break;
	 case TM_SUBTYPE_12_3X4:
		 nRet = 12;
		 break;
	 case TM_SUBTYPE_13_IN1_RD12:
		 nRet = 13;
		 break;
	 case TM_SUBTYPE_16_4X4:
		 nRet = 16;
		 break;
	 case TM_SUBTYPE_24_LT1_RD5_X4:
		 nRet = 24;
		 break;
	 case TM_SUBTYPE_25_5X5:
		 nRet = 25;
		 break;
	 case TM_SUBTYPE_36_6X6:
		 nRet = 36;
		 break;
	 }
	 if (bFloat)
	 {
		 nRet++;
	 }
	 return nRet;
 }

 bool TMInfo::GetTMWndPos(int width, int height, HPTM_TM_TYPE type,HPTM_TM_SUBTYPE subtype,std::vector<RECT>& PosArray)
 {
	 PosArray.clear();
	 {
		 int nWidth		= width;
		 int nHeight	= height;
		 s_rect.left	= 0;
		 s_rect.top		= 0;
		 s_rect.right	= nWidth;
		 s_rect.bottom	= nHeight;
		 int nSubType      = (int)subtype;

		 bool bFloat = false;
		 if (subtype >= 100)
		 {
			 bFloat = true;
			 nSubType -= 100;
		 }
		 switch(nSubType)
		 {
		 case TM_SUBTYPE_1_1X1:
			 SetOneFull(PosArray);
			 break;
		 case TM_SUBTYPE_2_1X2_SPACE:
			 SetL1_R1_Space(PosArray);
			 break;
		 case TM_SUBTYPE_2_1X2_FULL:
			 SetL1_R1(PosArray);
			 break;
		 case TM_SUBTYPE_3_L1_R2:
			 SetL1_R2(PosArray);
			 break;
		 case TM_SUBTYPE_4_2X2:
			 Set2X2(PosArray);
			 break;
		 case TM_SUBTYPE_4_L1_R3:
			 SetL1_R3(PosArray);
			 break;
		 case TM_SUBTYPE_6_LT1_RD5:
			 SetLT1_Round5(PosArray);
			 break;
		 case TM_SUBTYPE_8_LT1_RD7:
			 SetLT1_Round7(PosArray);
			 break;
		 case TM_SUBTYPE_9_3X3:
			 Set3X3(PosArray);
			 break;
		 case TM_SUBTYPE_10_T2_B2X4:
			 SetT2_B2X4(PosArray);
			 break;
		 case TM_SUBTYPE_13_IN1_RD12:
			 SetIn1_Round12(PosArray);
			 break;
		 case TM_SUBTYPE_16_4X4:
			 Set4X4(PosArray);
			 break;
		 case TM_SUBTYPE_12_3X4:
			 Set3X4(PosArray);
			 break;
		 case TM_SUBTYPE_2_PIC_IN_PIC:
			 SetPicInPic(PosArray);
			 break;
		 case TM_SUBTYPE_4_B1_T3:
			 SetB1_T3(PosArray);
			 break;
		 case TM_SUBTYPE_5_L1_R4:
			 SetL1_R4(PosArray);
			 break;
		 case TM_SUBTYPE_5_B1_T4:
			 SetB1_T4(PosArray);
			 break;
		 case TM_SUBTYPE_6_T2_B4:
			 SetT2_B4(PosArray);
			 break;
		 case TM_SUBTYPE_7_L2X2_R3:
			 SetL2X2_R3(PosArray);
			 break;
		 case TM_SUBTYPE_10_LT1_RD9:
			 SetLT1_Round9(PosArray);
			 break;
		 case TM_SUBTYPE_25_5X5:
			 Set5X5(PosArray);
			 break;
		 case TM_SUBTYPE_36_6X6:
			 Set6X6(PosArray);
			 break;
		 case TM_SUBTYPE_24_LT1_RD5_X4:
			 SetLT1_Round5_X4(PosArray);
			 break;
		 default:
			 {
				 TMInfo::dbgprint("@@@@  TMInfo::GetTMWndPos Error [nType =%d] @@@@ \n",nSubType);
				 return false;
			 }
			 break;

		 }

		 if (bFloat)
		 {
			 //浮动模板暂时不加
			// SetFloatWindow(PosArray);
		 }
		 return true;
	 }

	 return false;
 }

/*
 bool TMInfo::GetTMWndPos(HPTM_TM_TYPE type,HPTM_TM_SUBTYPE subtype,int nWndIndex,int& x,int& y,int& cx,int& cy)
 {

	 int nWndCount = GetTMWndCount(subtype);
	 std::vector<RECT> PosArray;
	 GetTMWndPos(type,subtype,PosArray);
	 if (nWndIndex<PosArray.size() && nWndIndex >=0)
	 {
		 x	= PosArray[nWndIndex].left;
		 y	= PosArray[nWndIndex].top;
		 cx	= PosArray[nWndIndex].right - PosArray[nWndIndex].left;
		 cy	= PosArray[nWndIndex].bottom - PosArray[nWndIndex].top;
		 return true;
	 }

	 return false;
 }
*/

  void TMInfo::SetOneFull(std::vector<RECT>& PosArray)
  {
	  RECT rc;
	  rc.left		= s_rect.left;
	  rc.top		= s_rect.top;
	  rc.right		= s_rect.right;
	  rc.bottom		= s_rect.bottom;
	  PosArray.push_back(rc);
  }

 void TMInfo::SetL1_R1_Space(std::vector<RECT>& PosArray)
{
	RECT rc;
	PosArray.assign(2, rc);
	int w = (int)(s_rect.right/2.0f);
	int h = (int)(w*3/4.0f);
	rc.left = s_rect.left;
	rc.right = rc.left + w;
	rc.top = s_rect.top + (int)((s_rect.bottom - h)/2.0f);
	rc.bottom = s_rect.bottom - (int)((s_rect.bottom - h)/2.0f);
	PosArray[0] = rc;
	rc.left = rc.right;
	rc.right = s_rect.right;
	PosArray[1] = rc;
}

//左边一个，右边一个，不带上下空条
void  TMInfo::SetL1_R1(std::vector<RECT>& PosArray)
{
	RECT rc;
	PosArray.assign(2, rc);
	int w = (int)(s_rect.right/2.0f);
	int h = s_rect.bottom;

	rc.left		= s_rect.left;
	rc.right	= s_rect.left + w;
	rc.top		= s_rect.top;
	rc.bottom	= s_rect.bottom;
	PosArray[0]	= rc;

	rc.left		= rc.right;
	rc.right	= s_rect.right;
	PosArray[1]	= rc;
}

void TMInfo::Set2X2(std::vector<RECT>& PosArray)
{
	RECT rc;

	int h = (int)(s_rect.bottom/2.0f);
	int w = (int)(s_rect.right/2.0f);

	int i;
	for (i=0; i<2; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 1)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<2; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 1)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

}

//左一右三
void TMInfo::SetL1_R3(std::vector<RECT>& PosArray)
{
	RECT rc;

	PosArray.assign(4, rc);

	int h = (int)(s_rect.bottom/3.0f);
	int w = (int)(s_rect.right/3.0f);

	for (int i=0; i < 3; i++)
	{
		rc.left		= s_rect.right - w;
		rc.top		= s_rect.top + h*i;
		rc.right	= s_rect.right;
		rc.bottom	= rc.top + h;

		if (i == 2)
		{
			rc.bottom	= s_rect.bottom;
		}

		PosArray[i+1] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top;
	rc.right	= s_rect.right - w;
	rc.bottom	= s_rect.bottom;

	PosArray[0] = rc;

}

void TMInfo::SetL1_R2(std::vector<RECT>& PosArray)
{
	RECT rc;
	PosArray.assign(3, rc);

	int h = (int)(s_rect.bottom/2.0f);
	int w = (int)(s_rect.right/3.0f);

	rc.left		= s_rect.left;
	rc.top		= s_rect.top;
	rc.right	= s_rect.right-w;
	rc.bottom	= s_rect.bottom;
	PosArray[0] = rc;

	for (int i = 0; i < 2; i++)
	{
		rc.left		= s_rect.right-w;
		rc.top		= s_rect.top+h*i;
		rc.right	= s_rect.right;
		rc.bottom	= rc.top+h;
		if (i == 1)
			rc.bottom = s_rect.bottom;
		PosArray[i+1] = rc;
	}
}

//左上一大 L五小
void TMInfo::SetLT1_Round5(std::vector<RECT>& PosArray)
{
	RECT rc;
	int i;

	PosArray.assign(6, rc);

	int h = (int)(s_rect.bottom/3.0f);
	int w = (int)(s_rect.right/3.0f);

	for (i=0; i<2; i++)
	{
		rc.left		= s_rect.left + w*2;
		rc.top		= s_rect.top + h*i;
		rc.right	= s_rect.right;
		rc.bottom	= rc.top + h;

		PosArray[i+1] = rc;
	}

	for (i=0; i<3; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*2;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 2)
		{
			rc.right = s_rect.right;
		}

		PosArray[3+i] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top;
	rc.right	= rc.left + w*2;
	rc.bottom	= rc.top + h*2;

	PosArray[0] = rc;
}

//左上一大 L七小
void TMInfo::SetLT1_Round7(std::vector<RECT>& PosArray)
{
	RECT rc;
	int i;
	PosArray.assign(8, rc);

	int h = (int)(s_rect.bottom/4.0f);
	int w = (int)(s_rect.right/4.0f);

	for (i=0; i<3; i++)
	{
		rc.left		= s_rect.left + w*3;
		rc.top		= s_rect.top + h*i;
		rc.right	= s_rect.right;
		rc.bottom	= rc.top + h;

		PosArray[i+1] = rc;
	}

	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*3;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray[4+i] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top;
	rc.right	= rc.left + w*3;
	rc.bottom	= rc.top + h*3;

	PosArray[0] = rc;

}

//3*3九分屏
void TMInfo::Set3X3(std::vector<RECT>& PosArray)
{
	RECT rc;

	int h = (int)(s_rect.bottom/3.0f);
	int w = (int)(s_rect.right/3.0f);

	int i;
	for (i=0; i<3; i++) 
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 2)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<3; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 2)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<3; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*2;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 2)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	//CTempletBase::ResetBigWnd();
}

//上面二大  下面八小
void TMInfo::SetT2_B2X4(std::vector<RECT>& PosArray)
{
	int h = (int)(s_rect.bottom/4.0f);
	int w = (int)(s_rect.right/4.0f);

	RECT rc;
	int i;

	for (i=0 ;i<2; i++)
	{
		rc.left		= s_rect.left + w*i*2;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w*2;
		rc.bottom	= rc.top + h*2;

		if (i == 1)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*2;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*3;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 3)
		{
			rc.right	= s_rect.right;
		}

		PosArray.push_back(rc);
	}

}

//中间一个大窗口 周围一圈12小
void TMInfo::SetIn1_Round12(std::vector<RECT>& PosArray)
{
	RECT rc;
	PosArray.assign(13, rc);

	int h = (int)(s_rect.bottom/4.0f);
	int w = (int)(s_rect.right/4.0f);

	int i;
	for (i = 0; i < 4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray[i+1] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top + h;
	rc.right	= rc.left + w;
	rc.bottom	= rc.top + h;
	PosArray[5]	= rc;

	rc.left		= s_rect.left + w*3;
	rc.right	= s_rect.right;
	PosArray[6]	= rc;

	rc.left		= s_rect.left;
	rc.top		= s_rect.top + h*2;
	rc.right	= rc.left + w;
	rc.bottom	= rc.top + h;
	PosArray[7]	= rc;

	rc.left		= s_rect.left + w*3;
	rc.right	= s_rect.right;
	PosArray[8]	= rc;

	for (i = 0; i < 4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*3;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray[i+9] = rc;
	}

	rc.left		= s_rect.left + w;
	rc.top		= s_rect.top + h;
	rc.right	= rc.left + w*2;
	rc.bottom	= rc.top + h*2;
	PosArray[0]	= rc;

}

//4*4十六分屏
void TMInfo::Set4X4(std::vector<RECT>& PosArray)
{
	RECT rc;

	int h = (int)(s_rect.bottom/4.0f);
	int w = (int)(s_rect.right/4.0f);

	int i;
	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*2;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<4; i++)
	{
		rc.left = s_rect.left + w*i;
		rc.top = s_rect.top + h*3;
		rc.right = rc.left + w;
		rc.bottom = s_rect.bottom;

		if (i==3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	//CTempletBase::ResetBigWnd();
}

void TMInfo::Set3X4(std::vector<RECT>& PosArray)
{
	RECT rc;
	PosArray.clear();
	int h = (int)(s_rect.bottom/3.0f);
	int w = (int)(s_rect.right/4.0f);

	int i;
	for (i=0; i<4; i++) 
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*2;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}
}


//画中画
void TMInfo::SetPicInPic(std::vector<RECT>& PosArray)
{
	RECT rc;
	PosArray.assign(2, rc);
	PosArray[0] = s_rect;

	int h = (int)(s_rect.bottom/4.0f);
	//int w = (int)h/m_curScale;
	int w = (int)(h*s_rate2);

	rc.top		= s_rect.bottom - h;
	rc.bottom	= s_rect.bottom;
	rc.left		= s_rect.right - w;
	rc.right	= s_rect.right;

	PosArray[1] = rc;

	//m_bIsPictureInPicture = TRUE;
}

//下一上三
void TMInfo::SetB1_T3(std::vector<RECT>& PosArray)
{
	RECT rc;

	PosArray.assign(4, rc);

	int h = (int)(s_rect.bottom/3.0f);
	int w = (int)(s_rect.right/3.0f);

	for (int i=0; i < 3; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 2)
		{
			rc.right	= s_rect.right;
		}

		PosArray[i+1] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top + h;
	rc.right	= s_rect.right;
	rc.bottom	= s_rect.bottom;

	PosArray[0] = rc;

}

//左一右四
void TMInfo::SetL1_R4(std::vector<RECT>& PosArray)
{
	RECT rc;

	PosArray.assign(5, rc);

	int h = (int)(s_rect.bottom/4.0f);
	int w = (int)(s_rect.right/4.0f);

	for (int i=0; i < 4; i++)
	{
		rc.left		= s_rect.right - w;
		rc.top		= s_rect.top + h*i;
		rc.right	= s_rect.right;
		rc.bottom	= rc.top + h;

		if (i == 3)
		{
			rc.bottom	= s_rect.bottom;
		}

		PosArray[i+1] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top;
	rc.right	= s_rect.right - w;
	rc.bottom	= s_rect.bottom;

	PosArray[0] = rc;

}

//下一上四
void TMInfo::SetB1_T4(std::vector<RECT>& PosArray)
{
	RECT rc;

	PosArray.assign(5, rc);

	int h = (int)(s_rect.bottom/4.0f);
	int w = (int)(s_rect.right/4.0f);

	for (int i=0; i < 4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i == 3)
		{
			rc.right	= s_rect.right;
		}

		PosArray[i+1] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top + h;
	rc.right	= s_rect.right;
	rc.bottom	= s_rect.bottom;

	PosArray[0] = rc;

}

//上边2个大的 下边4个小的
void TMInfo::SetT2_B4(std::vector<RECT>& PosArray)
{
	RECT rc;

	int h = (int)(s_rect.bottom/4.0f);
	int w = (int)(s_rect.right/4.0f);

	//上边两个
	int i;
	for (i=0; i<2; i++)
	{
		rc.left		= s_rect.left + w*2*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w*2;
		rc.bottom	= rc.top + h*3;

		if (i == 1)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	//下边四个
	for (i=0; i<4; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*3;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i == 3)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}
}

//左边2*2四分屏 右边3个小的
void TMInfo::SetL2X2_R3(std::vector<RECT>& PosArray)
{
	RECT rc;

	PosArray.assign(7, rc);

	int h = (int)(s_rect.bottom/3.0f);
	int wr = h*4/3;
	//右边三个
	int i;
	rc.left		= s_rect.right - wr;
	rc.right	= s_rect.right;
	for (i=0; i<3; i++)
	{
		rc.top		= s_rect.top + h*i;
		rc.bottom	= rc.top + h;

		if (i == 2)
		{
			rc.bottom = s_rect.bottom;
		}

		PosArray[i+4] = rc;
	}

	h = (int)(s_rect.bottom/2.0f);
	int wl = (s_rect.right - wr)/2;
	//左上边两个
	rc.top		= s_rect.top;
	rc.bottom	= rc.top + h;
	for (i=0; i<2; i++)
	{
		rc.left		= s_rect.left + wl*i;
		rc.right	= rc.left + wl;

		if (i == 1)
		{
			rc.right = s_rect.right - wr;
		}

		PosArray[i] = rc;
	}

	//左下边两个
	rc.top		= s_rect.top + h;
	rc.bottom	= s_rect.bottom;
	for (i=0; i<2; i++)
	{
		rc.left		= s_rect.left + wl*i;
		rc.right	= rc.left + wl;

		if (i == 1)
		{
			rc.right = s_rect.right - wr;
		}

		PosArray[i+2] = rc;
	}
}

//左上一大 L九小
void TMInfo::SetLT1_Round9(std::vector<RECT>& PosArray)
{
	RECT rc;
	int i;
	PosArray.assign(10, rc);

	int h = (int)(s_rect.bottom/5.0f);
	int w = (int)(s_rect.right/5.0f);

	rc.left		= s_rect.left + w*4;
	rc.right	= s_rect.right;
	for (i=0; i<4; i++)
	{
		rc.top		= s_rect.top + h*i;
		rc.bottom	= rc.top + h;

		PosArray[i+1] = rc;
	}

	rc.top		= s_rect.top + h*4;
	rc.bottom	= s_rect.bottom;
	for (i=0; i<5; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.right	= rc.left + w;

		if (i == 4)
		{
			rc.right = s_rect.right;
		}

		PosArray[5+i] = rc;
	}

	rc.left		= s_rect.left;
	rc.top		= s_rect.top;
	rc.right	= rc.left + w*4;
	rc.bottom	= rc.top + h*4;

	PosArray[0] = rc;
}

//5*5二十五分屏
void TMInfo::Set5X5(std::vector<RECT>& PosArray)
{
	RECT rc;

	int h = (int)(s_rect.bottom/5.0f);
	int w = (int)(s_rect.right/5.0f);

	int i;
	for (i=0; i<5; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==4)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<5; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==4)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<5; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*2;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==4)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<5; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*3;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==4)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<5; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*4;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i==4)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	//CTempletBase::ResetBigWnd();
}

//6*6三十六分屏
void TMInfo::Set6X6(std::vector<RECT>& PosArray)
{
	RECT rc;

	int h = (int)(s_rect.bottom/6.0f);
	int w = (int)(s_rect.right/6.0f);

	int i;
	for (i=0; i<6; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==5)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<6; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==5)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<6; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*2;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==5)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<6; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*3;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==5)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<6; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*4;
		rc.right	= rc.left + w;
		rc.bottom	= rc.top + h;

		if (i==5)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	for (i=0; i<6; i++)
	{
		rc.left		= s_rect.left + w*i;
		rc.top		= s_rect.top + h*5;
		rc.right	= rc.left + w;
		rc.bottom	= s_rect.bottom;

		if (i==5)
		{
			rc.right = s_rect.right;
		}

		PosArray.push_back(rc);
	}

	//CTempletBase::ResetBigWnd();
}

//由4个（左上一大 L五小）组成的
void TMInfo::SetLT1_Round5_X4(std::vector<RECT>& PosArray)
{
	RECT rc;
	int i;

	PosArray.assign(24, rc);

	int h = (int)(s_rect.bottom/6.0f);
	int w = (int)(s_rect.right/6.0f);

	for (int j = 0; j < 4; j++)
	{
		int nStartLeft = (j%2)*w*3;
		int nStartTop = (j>1?1:0)*h*3;

		for (i = 0; i < 2; i++)
		{
			rc.left		= s_rect.left + w*2 + nStartLeft;
			rc.top		= s_rect.top + h*i + nStartTop;
			rc.right	= rc.left + w;
			rc.bottom	= rc.top + h;

			if (j%2)
			{
				rc.right = s_rect.right;
			}

			PosArray[i+1+6*j] = rc;
		}

		for (i = 0; i < 3; i++)
		{
			rc.left		= s_rect.left + w*i + nStartLeft;
			rc.top		= s_rect.top + h*2 + nStartTop;
			rc.right	= rc.left + w;
			rc.bottom	= rc.top + h;

			if (j>1)
			{
				rc.bottom = s_rect.bottom;
			}

			if (i == 2 && (j%2))
			{
				rc.right = s_rect.right;
			}

			PosArray[3+i+6*j] = rc;
		}

		rc.left		= s_rect.left + nStartLeft;
		rc.top		= s_rect.top + nStartTop;
		rc.right	= rc.left + w*2;
		rc.bottom	= rc.top + h*2;

		PosArray[0+6*j] = rc;
	}
}

void TMInfo::SetFloatWindow(std::vector<RECT>& PosArray)
{
	int w = s_rect.right/4;
	int h = s_rect.bottom/4;

	RECT rc;
	rc.left		= s_rect.right - w - 2;
	rc.top		= s_rect.bottom - h - 20;
	rc.right	= s_rect.right;
	rc.bottom	= s_rect.bottom;
	PosArray.push_back(rc);
}

//#endif // USE_MPS

 
