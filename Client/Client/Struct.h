#pragma once


typedef struct tagVertexCol
{
	XMFLOAT3 vPosition;
	XMFLOAT4 vColor;
	tagVertexCol()
	{

	}

	tagVertexCol(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse)
	{
		vPosition =xmf3Position;
		vColor = xmf4Diffuse;
	}
}VTXCOL;


typedef struct tagVertex_Texture
{
	XMFLOAT3 vPosition;
	XMFLOAT2 vTexUV;
	tagVertex_Texture()
	{

	}

	tagVertex_Texture(XMFLOAT3 position, XMFLOAT2 TexUV)
	{
		vPosition = position;
		vTexUV = TexUV;
	}
}VTXTEX;


typedef struct tagCamera_Desc
{
	XMFLOAT3		vEye; // 카메라의 위치.In.WorldSpace
	XMFLOAT3		vAt; // 카메라가 바라보는 점.
	XMFLOAT3		vAxisY; // 내 좌표계상에서의 y축벡터의 방향.
}CAMERADESC;

typedef struct tagProjection_Desc
{
	float		fFovY; // 내 카메라의 시야 범위.
	float		fAspect; // 내 윈도우의 가로, 세로 비율.
	float		fNear;
	float		fFar;
}PROJDESC;


typedef struct tagShaderInfo
{
	XMFLOAT4X4						m_xmf4x4View;
	XMFLOAT4X4						m_xmf4x4Projection;
	XMFLOAT3						m_xmf3Position;
}SHADERINFO;


typedef struct tagPolygon16
{
	unsigned short		_0, _1, _2;
}POLYGON16;

typedef struct tagPolygon32
{
	unsigned int		_0, _1, _2;
}POLYGON32;