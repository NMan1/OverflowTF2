#pragma once

class ITexture;
class c_viewsetup;
class CEngineSprite;
class IClientEntity;
class i_material;
class IClientRenderable;

#define MAX_VIS_LEAVES				32
#define MAX_AREA_STATE_BYTES        32
#define MAX_AREA_PORTAL_STATE_BYTES 24

#define	SIDE_FRONT					0
#define	SIDE_BACK					1
#define	SIDE_ON						2

#define FRUSTUM_NUMPLANES			6

#define VP_EPSILON					0.01f

class VPlane;
class vector;
class vector_2d;
class vmatrix;

//-----------------------------------------------------------------------------
// Flags used by DrawWorldLists
//-----------------------------------------------------------------------------
enum
{
	DRAWWORLDLISTS_DRAW_STRICTLYABOVEWATER = 0x001,
	DRAWWORLDLISTS_DRAW_STRICTLYUNDERWATER = 0x002,
	DRAWWORLDLISTS_DRAW_INTERSECTSWATER = 0x004,
	DRAWWORLDLISTS_DRAW_WATERSURFACE = 0x008,
	DRAWWORLDLISTS_DRAW_SKYBOX = 0x010,
	DRAWWORLDLISTS_DRAW_CLIPSKYBOX = 0x020,
	DRAWWORLDLISTS_DRAW_SHADOWDEPTH = 0x040,
	DRAWWORLDLISTS_DRAW_REFRACTION = 0x080,
	DRAWWORLDLISTS_DRAW_REFLECTION = 0x100,
	DRAWWORLDLISTS_DRAW_SSAO = 0x800,
};

enum
{
	MAT_SORT_GROUP_STRICTLY_ABOVEWATER = 0,
	MAT_SORT_GROUP_STRICTLY_UNDERWATER,
	MAT_SORT_GROUP_INTERSECTS_WATER_SURFACE,
	MAT_SORT_GROUP_WATERSURFACE,

	MAX_MAT_SORT_GROUPS
};

enum ERenderDepthMode
{
	DEPTH_MODE_NORMAL = 0,
	DEPTH_MODE_SHADOW = 1,
	DEPTH_MODE_SSA0 = 2,
	DEPTH_MODE_OVERRIDE = 3,

	DEPTH_MODE_MAX
};

typedef VPlane Frustum[FRUSTUM_NUMPLANES];

//-----------------------------------------------------------------------------
// Leaf index
//-----------------------------------------------------------------------------
typedef unsigned short LeafIndex_t;
typedef short LeafFogVolume_t;
enum
{
	INVALID_LEAF_INDEX = (LeafIndex_t)~0
};


//-----------------------------------------------------------------------------
// Describes the leaves to be rendered this view, set by BuildWorldLists
//-----------------------------------------------------------------------------
struct WorldListInfo_t
{
	int		m_ViewFogVolume;
	int		m_LeafCount;
	LeafIndex_t* m_pLeafList;
	LeafFogVolume_t* m_pLeafFogVolume;
};

class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};

class IWorldRenderList : public IRefCounted
{

};

//-----------------------------------------------------------------------------
// Describes the fog volume for a particular point
//-----------------------------------------------------------------------------
struct VisibleFogVolumeInfo_t
{
	int		m_nVisibleFogVolume;
	int		m_nVisibleFogVolumeLeaf;
	bool	m_bEyeInFogVolume;
	float	m_flDistanceToWater;
	float	m_flWaterHeight;
	i_material* m_pFogVolumeMaterial;
};

//-----------------------------------------------------------------------------
// Vertex format for brush models
//-----------------------------------------------------------------------------
struct BrushVertex_t
{
	vector		m_Pos;
	vector		m_Normal;
	vector		m_TangentS;
	vector		m_TangentT;
	vector_2d		m_TexCoord;
	vector_2d		m_LightmapCoord;

private:
	BrushVertex_t(const BrushVertex_t& src);
};

//-----------------------------------------------------------------------------
// Visibility data for area portal culling
//-----------------------------------------------------------------------------
struct VisOverrideData_t
{
	vector		m_vecVisOrigin;					// The point to to use as the viewpoint for area portal backface cull checks.
	float		m_fDistToAreaPortalTolerance;	// The distance from an area portal before using the full screen as the viewable portion.
};

//-----------------------------------------------------------------------------
// interface for asking about the Brush surfaces from the client DLL
//-----------------------------------------------------------------------------
class IBrushSurface
{
public:
	// Computes texture coordinates + lightmap coordinates given a world position
	virtual void ComputeTextureCoordinate(vector const& worldPos, vector_2d& texCoord) = 0;
	virtual void ComputeLightmapCoordinate(vector const& worldPos, vector_2d& lightmapCoord) = 0;

	// Gets the vertex data for this surface
	virtual int  GetVertexCount() const = 0;
	virtual void GetVertexData(BrushVertex_t* pVerts) = 0;

	// Gets at the material properties for this surface
	virtual i_material* GetMaterial() = 0;
};

//-----------------------------------------------------------------------------
// interface for installing a new renderer for brush surfaces
//-----------------------------------------------------------------------------
class IBrushRenderer
{
public:
	// Draws the surface; returns true if decals should be rendered on this surface
	virtual bool RenderBrushModelSurface(IClientEntity* pBaseEntity, IBrushSurface* pBrushSurface) = 0;
};

//-----------------------------------------------------------------------------
// Purpose: Interface to client .dll to set up a rendering pass over world
//  The client .dll can call Render multiple times to overlay one or more world
//  views on top of one another
//-----------------------------------------------------------------------------
enum DrawBrushModelMode_t
{
	DBM_DRAW_ALL = 0,
	DBM_DRAW_OPAQUE_ONLY,
	DBM_DRAW_TRANSLUCENT_ONLY,
};

struct model_t;

class iv_render_view
{
public:

	// Draw normal brush model.
	// If pMaterialOverride is non-null, then all the faces of the bmodel will
	// set this material rather than their regular material.
	virtual void			DrawBrushModel(
		IClientEntity* baseentity,
		model_t* model,
		const vector& origin,
		const vector& angles,
		bool bUnused) = 0;

	// Draw brush model that has no origin/angles change ( uses identity transform )
	// FIXME, Material proxy IClientEntity *baseentity is unused right now, use DrawBrushModel for brushes with
	//  proxies for now.
	virtual void			DrawIdentityBrushModel(IWorldRenderList* pList, model_t* model) = 0;

	// Mark this dynamic light as having changed this frame ( so light maps affected will be recomputed )
	virtual void			TouchLight(struct dlight_t* light) = 0;
	// Draw 3D Overlays
	virtual void			Draw3DDebugOverlays(void) = 0;
	// Sets global blending fraction
	virtual void			set_blend(float blend) = 0;
	virtual float			get_blend(void) = 0;

	// Sets global color modulation
	virtual void			set_color_modulation(float const* blend) = 0;
	virtual void			get_color_modulation(float* blend) = 0;
	inline void                 set_color_modulation(float r, float g, float b)
	{
		float clr[3] = { r, g, b };
		set_color_modulation(clr);
	}
	// Wrap entire scene drawing
	virtual void			SceneBegin(void) = 0;
	virtual void			SceneEnd(void) = 0;

	// Gets the fog volume for a particular point
	virtual void			GetVisibleFogVolume(const vector& eyePoint, VisibleFogVolumeInfo_t* pInfo) = 0;

	// Wraps world drawing
	// If iForceViewLeaf is not -1, then it uses the specified leaf as your starting area for setting up area portal culling.
	// This is used by water since your reflected view origin is often in solid space, but we still want to treat it as though
	// the first portal we're looking out of is a water portal, so our view effectively originates under the water.
	virtual IWorldRenderList* CreateWorldList() = 0;

	virtual void			BuildWorldLists(IWorldRenderList* pList, WorldListInfo_t* pInfo, int iForceFViewLeaf, const VisOverrideData_t* pVisData = NULL, bool bShadowDepth = false, float* pReflectionWaterHeight = NULL) = 0;
	virtual void			DrawWorldLists(IWorldRenderList* pList, unsigned long flags, float waterZAdjust) = 0;

	// Optimization for top view
	virtual void			DrawTopView(bool enable) = 0;
	virtual void			TopViewBounds(vector_2d const& mins, vector_2d const& maxs) = 0;

	// Draw lights
	virtual void			DrawLights(void) = 0;
	// FIXME:  This function is a stub, doesn't do anything in the engine right now
	virtual void			DrawMaskEntities(void) = 0;

	// Draw surfaces with alpha
	virtual void			DrawTranslucentSurfaces(IWorldRenderList* pList, int sortIndex, unsigned long flags, bool bShadowDepth) = 0;

	// Draw Particles ( just draws the linefine for debugging map leaks )
	virtual void			DrawLineFile(void) = 0;
	// Draw lightmaps
	virtual void			DrawLightmaps(IWorldRenderList* pList, int pageId) = 0;
	// Wraps view render sequence, sets up a view
	virtual void			ViewSetupVis(bool novis, int numorigins, const vector origin[]) = 0;

	// Return true if any of these leaves are visible in the current PVS.
	virtual bool			AreAnyLeavesVisible(int* leafList, int nLeaves) = 0;

	virtual	void			VguiPaint(void) = 0;
	// Sets up view fade parameters
	virtual void			ViewDrawFade(byte* color, i_material* pMaterial) = 0;
	// Sets up the projection matrix for the specified field of view
	virtual void			OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	// Determine lighting at specified position
	virtual color			GetLightAtPoint(vector& pos) = 0;
	// Whose eyes are we looking through?
	virtual int				GetViewEntity(void) = 0;
	// Get engine field of view setting
	virtual float			GetFieldOfView(void) = 0;
	// 1 == ducking, 0 == not
	virtual unsigned char** GetAreaBits(void) = 0;

	// Set up fog for a particular leaf
	virtual void			SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;

	// Installs a brush surface draw override method, null means use normal renderer
	virtual void			InstallBrushSurfaceRenderer(IBrushRenderer* pBrushRenderer) = 0;

	// Draw brush model shadow
	virtual void			DrawBrushModelShadow(IClientRenderable* pRenderable) = 0;

	// Does the leaf contain translucent surfaces?
	virtual	bool			LeafContainsTranslucentSurfaces(IWorldRenderList* pList, int sortIndex, unsigned long flags) = 0;

	virtual bool			DoesBoxIntersectWaterVolume(const vector& mins, const vector& maxs, int leafWaterDataID) = 0;

	virtual void			SetAreaState(
		unsigned char chAreaBits[MAX_AREA_STATE_BYTES],
		unsigned char chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES]) = 0;

	// See i
	virtual void			VGui_Paint(int mode) = 0;

	// Push, pop views (see PushViewFlags_t above for flags)
	virtual void			push_3d_view(const c_viewsetup& view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
	virtual void			push_2d_view(const c_viewsetup& view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
	virtual void			pop_view(Frustum frustumPlanes) = 0;

	// Sets the main view
	virtual void			set_main_view(const vector& vecOrigin, const vector& angles) = 0;

	enum
	{
		VIEW_SETUP_VIS_EX_RETURN_FLAGS_USES_RADIAL_VIS = 0x00000001
	};

	// Wraps view render sequence, sets up a view
	virtual void			view_setup_vis_ex(bool novis, int numorigins, const vector origin[], unsigned int& returnFlags) = 0;

	//replaces the current view frustum with a rhyming replacement of your choice
	virtual void			override_view_frustum(Frustum custom) = 0;

	virtual void			draw_brush_model_shadow_depth(IClientEntity* pBaseEnt, model_t* oModel, const vector& vOrigin, const vector& vAngles, ERenderDepthMode DepthMode) = 0;
	virtual void			update_brush_model_lightmap(model_t* pModel, IClientRenderable* pRenderable) = 0;
	virtual void			begin_update_lightmaps(void) = 0;
	virtual void			end_update_lightmaps(void) = 0;
	virtual void			OLD_SetOffCenterProjectionMatrix(float fov, float zNear, float zFar, float flAspectRatio, float flBottom, float flTop, float flLeft, float flRight) = 0;
	virtual void			old_set_projection_matrix_ortho(float left, float top, float right, float bottom, float zNear, float zFar) = 0;
	virtual void			push3_d_view(const c_viewsetup& view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes, ITexture* pDepthTexture) = 0;
	virtual void			get_matrices_for_view(const c_viewsetup& view, vmatrix* pWorldToView, vmatrix* pViewToProjection, vmatrix* pWorldToProjection, vmatrix* pWorldToPixels) = 0;
	virtual void			draw_brush_model_ex(IClientEntity* baseentity, model_t* model, const vector& origin, const vector& angles, DrawBrushModelMode_t mode) = 0;
};
