#pragma once

#define UI_BASE_WIDTH	1024.0f
#define UI_BASE_HEIGHT	768.0f

struct CFontManager;
class CUICursor;


class CDeviceResetNotifier :public pureDeviceReset
{
public:
						CDeviceResetNotifier					()	{Device.seqDeviceReset.Add(this,REG_PRIORITY_NORMAL);};
	virtual				~CDeviceResetNotifier					()	{Device.seqDeviceReset.Remove(this);};
	virtual void		OnDeviceReset							()	{};

};



//---------------------------------------------------------------------------------------
// 2D Frustum & 2D Vertex
//---------------------------------------------------------------------------------------
struct S2DVert{
	Fvector2	pt;
	Fvector2	uv;
				S2DVert		(){}
				S2DVert		(float pX, float pY, float tU, float tV){pt.set(pX,pY);uv.set(tU,tV);}
	void		set			(float pt_x, float pt_y, float uv_x, float uv_y){pt.set(pt_x,pt_y);uv.set(uv_x,uv_y);}
	void		set			(const Fvector2& _pt, const Fvector2& _uv){pt.set(_pt);uv.set(_uv);}
	void		rotate_pt	(const Fvector2& pivot, float cosA, float sinA);
};
#define UI_FRUSTUM_SAFE			(12*4)
typedef svector<S2DVert,UI_FRUSTUM_SAFE>		sPoly2D;

class C2DFrustum{//only rect form
	svector<Fplane2,12> planes;
	Frect						m_rect;
public:
	void		CreateFromRect	(const Frect& rect);
	sPoly2D*	ClipPoly		(sPoly2D& S, sPoly2D& D) const;
};

class ui_core: public CDeviceResetNotifier
{
	C2DFrustum		m_2DFrustum;
	C2DFrustum		m_2DFrustumPP;
	bool			m_bPostprocess;

	CFontManager*	m_pFontManager;
	CUICursor*		m_pUICursor;

	Fvector2		m_pp_scale_;
	Fvector2		m_scale_;
	Fvector2*		m_current_scale;

	IC float		ClientToScreenScaledX			(float left)				{return left * m_current_scale->x;};
	IC float		ClientToScreenScaledY			(float top)					{return top * m_current_scale->y;};
public:
	xr_stack<Frect> m_Scissors;
	
					ui_core							();
					~ui_core						();
	CFontManager*	Font							()							{return m_pFontManager;}
	CUICursor*		GetUICursor						()							{return m_pUICursor;}

	void			ClientToScreenScaled			(Fvector2& dest, float left, float top);
	void			ClientToScreenScaled			(Fvector2& src_and_dest);
	void			ClientToScreenScaledWidth		(float& src_and_dest);
	void			ClientToScreenScaledHeight		(float& src_and_dest);

	Frect			ScreenRect						();
	const C2DFrustum& ScreenFrustum					(){return (m_bPostprocess)?m_2DFrustumPP:m_2DFrustum;}
	void			PushScissor						(const Frect& r, bool overlapped=false);
	void			PopScissor						();

	void			pp_start						();
	void			pp_stop							();
	void			RenderFont						();

	virtual void	OnDeviceReset					();
	enum class EAspectMode { Aspect_16_9, Aspect_16_10, Aspect_4_3, Aspect_5_4 };
	IC static EAspectMode get_aspect_mode			()
	{
		const float ar				= float(Device.dwWidth) / float(Device.dwHeight);
		if (ar > 1.7f)				return EAspectMode::Aspect_16_9;
		else if (ar > 1.5f)			return EAspectMode::Aspect_16_10;
		else if (ar > 1.3f)			return EAspectMode::Aspect_4_3;
		else						return EAspectMode::Aspect_5_4;
	}
	shared_str		get_xml_name					(LPCSTR fn);
};

extern CUICursor*	GetUICursor						();
extern ui_core*		UI								();
