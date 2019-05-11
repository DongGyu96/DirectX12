#include "stdafx.h"
#include "Rail.h"


Rail::Rail(float width, float height, float depth) : CMesh(9)
{
	float fHalfWidth = width * 0.5f;
	float fHalfHeight = height * 0.5f;
	float fHalfDepth = depth * 0.5f;

	CPolygon *leftline = new CPolygon(2);
	leftline->SetVertex(0, CVertex(-fHalfWidth, height, -fHalfDepth));
	leftline->SetVertex(1, CVertex(-fHalfWidth, height, +fHalfDepth));
	SetPolygon(0, leftline);

	CPolygon *rightline = new CPolygon(2);
	rightline->SetVertex(0, CVertex(+fHalfWidth, height, -fHalfDepth));
	rightline->SetVertex(1, CVertex(+fHalfWidth, height, +fHalfDepth));
	SetPolygon(1, rightline);

	CPolygon *railline1 = new CPolygon(2);
	railline1->SetVertex(0, CVertex(-fHalfWidth, height, -fHalfDepth));
	railline1->SetVertex(1, CVertex(+fHalfWidth, height, -fHalfDepth));
	SetPolygon(2, railline1);

	CPolygon *railline2 = new CPolygon(2);
	railline2->SetVertex(0, CVertex(-fHalfWidth, height, 0.0f));
	railline2->SetVertex(1, CVertex(+fHalfWidth, height, 0.0f));
	SetPolygon(3, railline2);

	CPolygon *railline3 = new CPolygon(2);
	railline3->SetVertex(0, CVertex(-fHalfWidth, height, +fHalfDepth));
	railline3->SetVertex(1, CVertex(+fHalfWidth, height, +fHalfDepth));
	SetPolygon(4, railline3);

	CPolygon *leftline1 = new CPolygon(2);
	leftline1->SetVertex(0, CVertex(-fHalfWidth, height + 1.5f, -fHalfDepth));
	leftline1->SetVertex(1, CVertex(-fHalfWidth, height + 1.5f, +fHalfDepth));
	SetPolygon(5, leftline1);

	CPolygon *rightline1 = new CPolygon(2);
	rightline1->SetVertex(0, CVertex(+fHalfWidth, height + 1.5f, -fHalfDepth));
	rightline1->SetVertex(1, CVertex(+fHalfWidth, height + 1.5f, +fHalfDepth));
	SetPolygon(6, rightline1);

	CPolygon *railline4 = new CPolygon(2);
	railline4->SetVertex(0, CVertex(-fHalfWidth + 0.5f, height, -fHalfDepth + 2.5f));
	railline4->SetVertex(1, CVertex(+fHalfWidth - 0.5f, height, -fHalfDepth + 2.5f));
	SetPolygon(7, railline4);

	CPolygon *railline5 = new CPolygon(2);
	railline5->SetVertex(0, CVertex(-fHalfWidth + 0.5f, height, fHalfDepth - 2.5f));
	railline5->SetVertex(1, CVertex(+fHalfWidth - 0.5f, height, fHalfDepth - 2.5f));
	SetPolygon(8, railline5);
}


Rail::~Rail()
{
}
