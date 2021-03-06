
// ClassView.h: CClassView 클래스의 인터페이스
//

#pragma once
#define WM_SHOT WM_USER+1

class CClassView : public CView
{
protected: // serialization에서만 만들어집니다.
	CClassView();
	DECLARE_DYNCREATE(CClassView)

// 특성입니다.
public:
	CClassDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	CButton *p_Btn_move;
	CButton *p_Btn_stop;
	static int p_Btn_clicked;

public:
	virtual ~CClassView();
	CPoint m_point;
	static CPoint m_targetpoint;
	static bool IsClick;	//Is mouse clicked?
	static double m_weight; //the time that mouse is clicked 

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void Draw_bullet(void);
	static void CalWeight(void );	//마우스 클릭 시간에 따른 가중치 계산 스레드
	 void Generatetarget(CClassView *);	//움직이는 표적 생성 스레드
	
	void Command_thread(void);	//움직이는 표적 생성
	void StopTargetGenerate(void);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnIdChange();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // ClassView.cpp의 디버그 버전
inline CClassDoc* CClassView::GetDocument() const
   { return reinterpret_cast<CClassDoc*>(m_pDocument); }
#endif

