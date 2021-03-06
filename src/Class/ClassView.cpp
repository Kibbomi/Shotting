
// ClassView.cpp: CClassView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Class.h"
#include "Gun.h"
#include "Gunparts.h"
#include "SettingDlg.h"
#include "Statisticsgun.h"
#endif

#include "ClassDoc.h"
#include "ClassView.h"

#include <stdlib.h>
#include <time.h>
#include <atlimage.h>	//CImage
#include <windows.h>	//For Thread
#include <process.h>	//For Thread
#include <mmsystem.h>	//For sound.
#pragma comment(lib,"winmm")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClassView

IMPLEMENT_DYNCREATE(CClassView, CView)

BEGIN_MESSAGE_MAP(CClassView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(MENU_ID_CHANGE, &CClassView::OnIdChange)
	ON_COMMAND(999, &CClassView::Command_thread)
	ON_COMMAND(888, &CClassView::StopTargetGenerate)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CClassView 생성/소멸

bool CClassView::IsClick = 0;
int CClassView::p_Btn_clicked = 0;
double CClassView::m_weight = 1;
CPoint CClassView::m_targetpoint = (0, 0);

class Gun gun(42,5,10,85,30,1000,L"M416.wav",880);	//사용할 총 객체
class Gunparts parts(1, 1, 1, 1);
class Gunparts muzzle_parts(1, 1, 1, 1);
class Statisticsgun gun_stat(0,0,0,0,0,0);

static int initvalue = 0;
static int keyboard = 0;
CClassView::CClassView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_point = CPoint(-100, -100);
}

CClassView::~CClassView()
{

}

BOOL CClassView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	

	

	return CView::PreCreateWindow(cs);
}

// CClassView 그리기

void CClassView::OnDraw(CDC* pDC)
{
	CClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	/*이미지 추가 */
	if (initvalue == 0)
	{
		CClientDC dc(this);
		CImage Image;
		Image.Load(_T("background.jpg"));
		Image.BitBlt(dc.m_hDC, 0, 0);
		initvalue = 1;
	}
	


	ASSERT_VALID(pDoc);
	

	
}


// CClassView 인쇄

BOOL CClassView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CClassView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CClassView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CClassView 진단

#ifdef _DEBUG
void CClassView::AssertValid() const
{
	CView::AssertValid();
}

void CClassView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClassDoc* CClassView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClassDoc)));
	return (CClassDoc*)m_pDocument;
}
#endif //_DEBUG


// CClassView 메시지 처리기


void CClassView::OnLButtonDown(UINT nFlags, CPoint point)
{
	IsClick = TRUE;
	m_point = point;
	if (gun.m_bullet != 0)
	{
		//Draw_bullet();
		Sleep(gun.m_speed);
	}
	
	//Invalidate();
	//UpdateWindow();
	OnMouseMove(nFlags, point);

	CView::OnLButtonDown(nFlags, point);
}


void CClassView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	IsClick = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CClassView::OnMouseMove(UINT nFlags, CPoint point)
{
	int rand_x = 0, rand_y = 0;
	
	
	rand_x = rand() % (int)(gun.m_x_recoil*parts.m_control_x_recoil) - gun.m_x_recoil / 2;	//gun.m_x_recoil만큼의 범위
	rand_y = rand() % (int)(gun.m_y_recoil*parts.m_control_y_recoil) + gun.m_y_recoil;	//5<= y <= 15


	HANDLE weight_thread;


	weight_thread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)CalWeight, NULL, 0, NULL);
	if (weight_thread == 0)
	{
		MessageBox(L"Thread create error!", L"ERROR", MB_OK);
	}

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	/*test*/
	CDC *pdc;
	pdc = GetDC();
	CString cursorpos;
	CString temp;
	cursorpos.Format(L"%04d %04d", point.x, point.y);
	pdc->TextOut(1400, 0, cursorpos);
	temp.Format(L"피해량 : %d ", gun.m_damage);
	pdc->TextOut(1400, 30, temp);
	temp.Format(L"수평반동: %d  ", gun.m_x_recoil);
	pdc->TextOut(1400, 60, temp);
	temp.Format(L"수직반동: %d  ", gun.m_y_recoil);
	pdc->TextOut(1400, 90, temp);
	temp.Format(L"연사속도(m/s): %d  ", gun.m_speed);
	pdc->TextOut(1400, 120, temp);
	temp.Format(L"총알 수 : %d / %d  ", gun.m_bullet, gun.m_load);
	pdc->TextOut(1400, 150, temp);
	temp.Format(L" ----아이템---- ");
	pdc->TextOut(1400, 180, temp);
	temp.Format(L" 수평반동제어 : %f  ", parts.m_control_x_recoil);
	pdc->TextOut(1400, 210, temp);
	temp.Format(L" 수직반동제어 : %f  ",parts.m_control_y_recoil);
	pdc->TextOut(1400, 240, temp);
	temp.Format(L" 조준점제어 : %f  ", parts.m_control_aiming);
	pdc->TextOut(1400, 270, temp);
	temp.Format(L" 반동회복 : %f  ", parts.m_control_recoil_recovery);
	pdc->TextOut(1400, 300, temp);
	temp.Format(L" ----총구----  ");
	pdc->TextOut(1400, 330, temp);
	temp.Format(L" 수평반동제어 : %f  ", muzzle_parts.m_control_x_recoil);
	pdc->TextOut(1400, 360, temp);
	temp.Format(L" 수직반동제어 : %f  ", muzzle_parts.m_control_y_recoil);
	pdc->TextOut(1400, 390, temp);
	temp.Format(L" ----통계-----  ");
	pdc->TextOut(1400, 420, temp);
	temp.Format(L" 총 피해량 : %d    ", gun_stat.m_damage);
	pdc->TextOut(1400, 450, temp);
	temp.Format(L"명중률 : %f%%   ", gun_stat.m_hitrate * 100);
	pdc->TextOut(1400, 480, temp);
	temp.Format(L"헤드샷 : %f%%  ", gun_stat.m_headshotrate* 100);
	pdc->TextOut(1400, 510, temp);
	temp.Format(L"발사 총알 수 : %d  ", gun_stat.m_shoot);
	pdc->TextOut(1400, 540, temp);
	
	/*test*/


	if (IsClick == TRUE && gun.m_bullet != 0 )	//마우스를 클릭한채 쏠 때.
	{
		CRect ChildView;
		/*check.. mouse cursor*/
		

		GetWindowRect(ChildView);
		m_point = point;

		if ((point.y + (ChildView.top + 2) - rand_y - (int)m_weight) > 0)	//화면밖으로 넘어가지않게 하기 위함.
		{
			/*사격*/
			Draw_bullet();
			

			/*통계 계산*/
			
			if (((point.x - m_targetpoint.x <= 64) && (point.x - m_targetpoint.x >= 22)) &&
				((point.y - m_targetpoint.y <= 72) && (point.y - m_targetpoint.y >= 31)))
			{	
				//몸통 명중
				gun_stat.m_hit++;
				gun_stat.m_damage += gun.m_damage;
			}
			if (((point.x - m_targetpoint.x <= 56) && (point.x - m_targetpoint.x >= 29)) &&
				((point.y - m_targetpoint.y <= 31) && (point.y - m_targetpoint.y >= 04)))
			{
				//머리 명중
				gun_stat.m_hit++;
				gun_stat.m_headshot++;
				gun_stat.m_damage += gun.m_damage * 3;
			}
			gun_stat.m_hitrate = (float)gun_stat.m_hit / (float)gun_stat.m_shoot;
			gun_stat.m_headshotrate = (float)gun_stat.m_headshot / (float)gun_stat.m_shoot;
			/*통계 계산 끝*/

			
			SetCursorPos((point.x + (ChildView.left + 2)) + rand_x / parts.m_control_x_recoil/muzzle_parts.m_control_x_recoil ,
				point.y + (ChildView.top + 2) - rand_y / parts.m_control_y_recoil / muzzle_parts.m_control_y_recoil  - (int)m_weight);
			
			
			Sleep(gun.m_speed );	//밑의 지연 생각
		}
		else 
			IsClick = FALSE;

		
		
		//Invalidate();
		//UpdateWindow();
		
	}
	CView::OnMouseMove(nFlags, point);
}
void CClassView :: Draw_bullet(void)
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	CDC* pDC;
	CDC memDC;
	pDC = GetDC();
	memDC.CreateCompatibleDC(pDC); //복사를 위해 화면 DC와 호환되도록 생성
	memDC.SelectObject(&bmp); //메모리에 그림

	BITMAP bm;
	bmp.GetObject(sizeof(bm), &bm); //비트맵 관련 정보 획득
	

	/*투명화 처리 했을 때*/
	pDC->TransparentBlt(
		m_point.x,
		m_point.y,
		bm.bmWidth,
		bm.bmHeight,
		&memDC,
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		RGB(255, 255, 255));
	
	gun_stat.m_shoot++;
	gun.m_bullet--;	//총알 한발 발사

	
	PlaySound(gun.m_sound, NULL, SND_ASYNC);

	memDC.DeleteDC(); //메모리 DC 해제
	ReleaseDC(pDC);

}
void CClassView::CalWeight(void)
{
	int time = 0;

	while (IsClick)
	{
		if (time < 20)
		{
			m_weight *= 1.01;
			time++;
		}
		else
			m_weight *= 1.0001;

		Sleep(gun.m_speed-20);
	}
	m_weight = 1;
}
void CClassView:: Generatetarget(CClassView * arg)
{
	
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	CClassView * pt = arg;
	CDC *pDC = pt->GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC); //복사를 위해 화면 DC와 호환되도록 생성
	memDC.SelectObject(&bmp); //메모리에 그림
	BITMAP bm;
	bmp.GetObject(sizeof(bm), &bm); //비트맵 관련 정보 획득

	int value = rand() % 3 + 4;
	gun_stat.m_damage = 0;
	gun_stat.m_hit = 0;
	gun_stat.m_hitrate = 0;
	gun_stat.m_headshot = 0;
	gun_stat.m_shoot = 0;
	gun_stat.m_headshotrate = 0;
	//m_targetpoint.y = 100;

	

	CClientDC dc(arg);
	CImage Image;
	Image.Load(_T("background.jpg"));
	while (1)
	{

		pDC->TransparentBlt(
			m_targetpoint.x,
			m_targetpoint.y,
			bm.bmWidth,
			bm.bmHeight,
			&memDC,
			0,
			0,
			bm.bmWidth,
			bm.bmHeight,
			RGB(255, 255, 255));
		Sleep(1000/60);	//60Hz

		
		Image.BitBlt(dc.m_hDC, 0, 0);

		m_targetpoint.x +=value;
		if (m_targetpoint.x > 1300)
		{
			//m_targetpoint.x = 100;
			p_Btn_clicked = 0;
			return;
		}
	}
	memDC.DeleteDC(); //메모리 DC 해제
	//ReleaseDC(pDC);
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CDC *pDC;
	pDC = GetDC();

	
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_SPACE)
		{
			pDC->TextOut(1400, 30, L"space");
		}
		else if (pMsg->wParam == 0x41)
		{
			m_targetpoint.x-=5;
			keyboard = 1;
			StopTargetGenerate();
			keyboard = 0;
			pDC->TextOut(1400, 30, L"a");
		}
		else if (pMsg->wParam == 0x53)
		{
			m_targetpoint.y+= 5;
			keyboard = 1;
			StopTargetGenerate();
			keyboard = 0;
			pDC->TextOut(1400, 30, L"s");
		}
		else if (pMsg->wParam == 0x57)
		{
			m_targetpoint.y -= 5;
			keyboard = 1;
			StopTargetGenerate();
			keyboard = 0;
			pDC->TextOut(1400, 30, L"w");
		}
		else if (pMsg->wParam == 0x44)
		{
			m_targetpoint.x+=5;
			keyboard = 1;
			StopTargetGenerate();
			keyboard = 0;
			pDC->TextOut(1400, 30, L"d");
		}
		else if (pMsg->wParam == 0x52)
		{
			pDC->TextOut(1400, 30, L"r");

			gun.m_bullet = gun.m_load;	//재장전
		}
	}


	return CView::PreTranslateMessage(pMsg);
}


void CClassView::OnIdChange()
{
	CSettingDlg dlg;
	
	dlg.DoModal();
	
	gun = dlg.m_selectGun;
	parts = dlg.m_selectParts;
	muzzle_parts = dlg.m_seleteMuzzleParts;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CClientDC dc(this);
	
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	srand(time(NULL));
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	p_Btn_move = new CButton();
	p_Btn_move->Create(
		L"움직이는 표적 생성",
		WS_VISIBLE | WS_CHILD,
		CRect(1400, 600, 1600, 700), this, 999);

	p_Btn_stop = new CButton();
	p_Btn_stop->Create(
		L"멈춰있는 표적 생성",
		WS_VISIBLE | WS_CHILD,
		CRect(1400, 700, 1600, 800), this, 888);

	

	return 0;
}
void CClassView :: Command_thread(void)
{
	m_targetpoint.x = rand() % 100 + 100;
	m_targetpoint.y = rand() % 501 + 200;
	
	if (p_Btn_clicked == 0)
	{
		p_Btn_clicked = 1;
		HANDLE Generate_thread;

		Generate_thread = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Generatetarget, (CClassView *)this, 0, NULL);
		if (Generate_thread == 0)
		{
			MessageBox(L"Thread create error!", L"ERROR", MB_OK);
		}
	}
	return ;
}
void CClassView::StopTargetGenerate(void)
{

	
	gun_stat.m_damage = 0;
	gun_stat.m_hit = 0;
	gun_stat.m_hitrate = 0;
	gun_stat.m_headshot = 0;
	gun_stat.m_headshotrate = 0;
	gun_stat.m_shoot = 0;

	if (p_Btn_clicked == 0)
	{
		p_Btn_clicked = 1;
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP2);
		CDC *pDC = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(pDC); //복사를 위해 화면 DC와 호환되도록 생성
		memDC.SelectObject(&bmp); //메모리에 그림
		BITMAP bm;
		bmp.GetObject(sizeof(bm), &bm); //비트맵 관련 정보 획득
		if (keyboard == 0)
		{
			m_targetpoint.x = rand() % 1001 + 300;
			m_targetpoint.y = rand() % 401 + 200;
		}
		/*이미지 추가 */
		CClientDC dc(this);
		CImage Image;
		Image.Load(_T("background.jpg"));
		Image.BitBlt(dc.m_hDC, 0, 0);

		pDC->TransparentBlt(
			m_targetpoint.x,
			m_targetpoint.y,
			bm.bmWidth,
			bm.bmHeight,
			&memDC,
			0,
			0,
			bm.bmWidth,
			bm.bmHeight,
			RGB(255, 255, 255));

		p_Btn_clicked = 0;
	}
}