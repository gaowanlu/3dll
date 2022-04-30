/******************************************************
 * EasyX Library for C++ (Ver:20220116)
 * https://easyx.cn
 *
 * graphics.h
 *		Based on easyx.h and retaining several old API.
 ******************************************************/

#pragma once

#include <easyx.h>



// ��ͼ���ڳ�ʼ���������ѷ�������ʹ���µĺ궨�壩
#define SHOWCONSOLE		1		// ����ͼ�δ���ʱ����������̨����ʾ
#define NOCLOSE			2		// û�йرչ���
#define NOMINIMIZE		4		// û����С������



// �����ʽ���ѷ�������ʹ���µĺ궨�壩
#define	NULL_FILL			BS_NULL
#define	EMPTY_FILL			BS_NULL
#define	SOLID_FILL			BS_SOLID
// ��ͨһ��
#define	BDIAGONAL_FILL		BS_HATCHED, HS_BDIAGONAL					// /// ���
#define CROSS_FILL			BS_HATCHED, HS_CROSS						// +++ ���
#define DIAGCROSS_FILL		BS_HATCHED, HS_DIAGCROSS					// xxx ��� (heavy cross hatch fill)
#define DOT_FILL			(BYTE*)"\x80\x00\x08\x00\x80\x00\x08\x00"	// xxx ���
#define FDIAGONAL_FILL		BS_HATCHED, HS_FDIAGONAL					// \\\ ���
#define HORIZONTAL_FILL		BS_HATCHED, HS_HORIZONTAL					// === ���
#define VERTICAL_FILL		BS_HATCHED, HS_VERTICAL						// ||| ���
// �ܼ�һ��
#define BDIAGONAL2_FILL		(BYTE*)"\x44\x88\x11\x22\x44\x88\x11\x22"
#define CROSS2_FILL			(BYTE*)"\xff\x11\x11\x11\xff\x11\x11\x11"
#define DIAGCROSS2_FILL		(BYTE*)"\x55\x88\x55\x22\x55\x88\x55\x22"
#define DOT2_FILL			(BYTE*)"\x88\x00\x22\x00\x88\x00\x22\x00"
#define FDIAGONAL2_FILL		(BYTE*)"\x22\x11\x88\x44\x22\x11\x88\x44"
#define HORIZONTAL2_FILL	(BYTE*)"\x00\x00\xff\x00\x00\x00\xff\x00"
#define VERTICAL2_FILL		(BYTE*)"\x11\x11\x11\x11\x11\x11\x11\x11"
// ����һ��
#define BDIAGONAL3_FILL		(BYTE*)"\xe0\xc1\x83\x07\x0e\x1c\x38\x70"
#define CROSS3_FILL			(BYTE*)"\x30\x30\x30\x30\x30\x30\xff\xff"
#define DIAGCROSS3_FILL		(BYTE*)"\xc7\x83\xc7\xee\x7c\x38\x7c\xee"
#define DOT3_FILL			(BYTE*)"\xc0\xc0\x0c\x0c\xc0\xc0\x0c\x0c"
#define FDIAGONAL3_FILL		(BYTE*)"\x07\x83\xc1\xe0\x70\x38\x1c\x0e"
#define HORIZONTAL3_FILL	(BYTE*)"\xff\xff\x00\x00\xff\xff\x00\x00"
#define VERTICAL3_FILL		(BYTE*)"\x33\x33\x33\x33\x33\x33\x33\x33"
// ����
#define INTERLEAVE_FILL		(BYTE*)"\xcc\x33\xcc\x33\xcc\x33\xcc\x33"



///////////////////////////////////////////////////////////////////////////////////
// ���º�����Ϊ�������� EasyX �Ľӿڣ�������ʹ�á���ʹ������º����滻��
//
#if _MSC_VER > 1200 && _MSC_VER < 1900
	#define _EASYX_DEPRECATE					__declspec(deprecated("This function is deprecated."))
	#define _EASYX_DEPRECATE_WITHNEW(_NewFunc)	__declspec(deprecated("This function is deprecated. Instead, use this new function: " #_NewFunc ". See https://docs.easyx.cn/" #_NewFunc " for details."))
	#define _EASYX_DEPRECATE_OVERLOAD(_Func)	__declspec(deprecated("This overload is deprecated. See https://docs.easyx.cn/" #_Func " for details."))
#else
	#define _EASYX_DEPRECATE
	#define _EASYX_DEPRECATE_WITHNEW(_NewFunc)
	#define _EASYX_DEPRECATE_OVERLOAD(_Func)
#endif

// ������غ���
//		nHeight: �ַ���ƽ���߶ȣ�
//		nWidth: �ַ���ƽ�����(0 ��ʾ����Ӧ)��
//		lpszFace: �������ƣ�
//		nEscapement: �ַ�������д�Ƕ�(��λ 0.1 ��)��
//		nOrientation: ÿ���ַ�����д�Ƕ�(��λ 0.1 ��)��
//		nWeight: �ַ��ıʻ���ϸ(0 ��ʾĬ�ϴ�ϸ)��
//		bItalic: �Ƿ�б�壻
//		bUnderline: �Ƿ��»��ߣ�
//		bStrikeOut: �Ƿ�ɾ���ߣ�
//		fbCharSet: ָ���ַ�����
//		fbOutPrecision: ָ�����ֵ�������ȣ�
//		fbClipPrecision: ָ�����ֵļ������ȣ�
//		fbQuality: ָ�����ֵ����������
//		fbPitchAndFamily: ָ���Գ��淽ʽ�������������ϵ�С�
_EASYX_DEPRECATE_WITHNEW(settextstyle) void setfont(int nHeight, int nWidth, LPCTSTR lpszFace);
_EASYX_DEPRECATE_WITHNEW(settextstyle) void setfont(int nHeight, int nWidth, LPCTSTR lpszFace, int nEscapement, int nOrientation, int nWeight, bool bItalic, bool bUnderline, bool bStrikeOut);
_EASYX_DEPRECATE_WITHNEW(settextstyle) void setfont(int nHeight, int nWidth, LPCTSTR lpszFace, int nEscapement, int nOrientation, int nWeight, bool bItalic, bool bUnderline, bool bStrikeOut, BYTE fbCharSet, BYTE fbOutPrecision, BYTE fbClipPrecision, BYTE fbQuality, BYTE fbPitchAndFamily);
_EASYX_DEPRECATE_WITHNEW(settextstyle) void setfont(const LOGFONT *font);	// ���õ�ǰ������ʽ
_EASYX_DEPRECATE_WITHNEW(gettextstyle) void getfont(LOGFONT *font);			// ��ȡ��ǰ������ʽ

// ��ͼ��غ���
void bar(int left, int top, int right, int bottom);		// ���ޱ߿�������
void bar3d(int left, int top, int right, int bottom, int depth, bool topflag);	// ���б߿���ά������

void drawpoly(int numpoints, const int *polypoints);	// �������
void fillpoly(int numpoints, const int *polypoints);	// �����Ķ����

int getmaxx();					// ��ȡ���Ŀ��ֵ
int getmaxy();					// ��ȡ���ĸ߶�ֵ

COLORREF getcolor();			// ��ȡ��ǰ��ͼǰ��ɫ
void setcolor(COLORREF color);	// ���õ�ǰ��ͼǰ��ɫ

void setwritemode(int mode);	// ����ǰ���Ķ�Ԫ��դ����ģʽ

// ����ǰ�㡱��غ���
_EASYX_DEPRECATE	int	getx();								// ��ȡ��ǰ x ����
_EASYX_DEPRECATE	int	gety();								// ��ȡ��ǰ y ����
_EASYX_DEPRECATE	void moveto(int x, int y);				// �ƶ���ǰ��(��������)
_EASYX_DEPRECATE	void moverel(int dx, int dy);			// �ƶ���ǰ��(�������)
_EASYX_DEPRECATE	void lineto(int x, int y);				// ����(����������)
_EASYX_DEPRECATE	void linerel(int dx, int dy);			// ����(���������)
_EASYX_DEPRECATE	void outtext(LPCTSTR str);				// �ڵ�ǰλ������ַ���
_EASYX_DEPRECATE	void outtext(TCHAR c);					// �ڵ�ǰλ������ַ�

// ������������غ���
// �����Ϣ
// ֧��������Ϣ��
//		WM_MOUSEMOVE		����ƶ�
//		WM_MOUSEWHEEL		�����ֲ���
//		WM_LBUTTONDOWN		�������
//		WM_LBUTTONUP		�������
//		WM_LBUTTONDBLCLK	���˫��
//		WM_MBUTTONDOWN		�м�����
//		WM_MBUTTONUP		�м�����
//		WM_MBUTTONDBLCLK	�м�˫��
//		WM_RBUTTONDOWN		�Ҽ�����
//		WM_RBUTTONUP		�Ҽ�����
//		WM_RBUTTONDBLCLK	�Ҽ�˫��
struct MOUSEMSG
{
	UINT uMsg;				// ��ǰ�����Ϣ
	bool mkCtrl		:1;		// Ctrl ���Ƿ���
	bool mkShift	:1;		// Shift ���Ƿ���
	bool mkLButton	:1;		// �������Ƿ���
	bool mkMButton	:1;		// ����м��Ƿ���
	bool mkRButton	:1;		// ����Ҽ��Ƿ���
	short x;				// ��ǰ��� x ����
	short y;				// ��ǰ��� y ����
	short wheel;			// �����ֹ���ֵ (120 �ı���)
};
_EASYX_DEPRECATE							bool MouseHit();			// ����Ƿ���������Ϣ
_EASYX_DEPRECATE_WITHNEW(getmessage)		MOUSEMSG GetMouseMsg();		// ��ȡһ�������Ϣ�����û�У��͵ȴ�
_EASYX_DEPRECATE_WITHNEW(peekmessage)		bool PeekMouseMsg(MOUSEMSG *pMsg, bool bRemoveMsg = true);	// ��ȡһ�������Ϣ������������
_EASYX_DEPRECATE_WITHNEW(flushmessage)		void FlushMouseMsgBuffer();	// ��������Ϣ

typedef ExMessage EASYXMSG;	// ���ݾɵ���Ϣ�ṹ������