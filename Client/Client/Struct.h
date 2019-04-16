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
	XMFLOAT3		vEye; // ī�޶��� ��ġ.In.WorldSpace
	XMFLOAT3		vAt; // ī�޶� �ٶ󺸴� ��.
	XMFLOAT3		vAxisY; // �� ��ǥ��󿡼��� y�຤���� ����.
}CAMERADESC;

typedef struct tagProjection_Desc
{
	float		fFovY; // �� ī�޶��� �þ� ����.
	float		fAspect; // �� �������� ����, ���� ����.
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