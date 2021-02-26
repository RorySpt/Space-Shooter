#include "sprite.h"

//void Sprite::Generate_fix(Sprite* s) {
//	Sprite* ptr = s->son_sprite;
//	while (ptr != NULL) {
//		if (ptr->son_sprite != NULL)Generate_fix(s->son_sprite);
//		ptr->Draw(&s->map);
//		ptr = ptr->next;
//	}
//}

void Sprite::Draw(IMAGE* pImgDst, const Transform& tf/*, Vec2D pos*/) {
	if (son_sprite != NULL) {
		Sprite* cur = son_sprite;
		//Ë÷¼ìµ½´®µ×
		while (cur->next != NULL) {
			cur = cur->next;
		}
		while (cur != NULL) {

			cur->Draw(pImgDst, { tf.p + site,tf.q });
			//cur->Draw(pImgDst, {tf.p + site,tf.q}/*, pos + site*/);
			if (cur == son_sprite) {
				Vec2D rpos = /*pos + */tf.p + tran.p + MulT(tf.q, site);
				transparentimage(pImgDst, (int)round(rpos.x), (int)round(rpos.y),
					&map.getFrame(TL::pHpte->getIntervals_int()), 1.0, tf.q.GetAngle()
				);
			}

			cur = cur->last;
		}
		

	}
	else {	//Ã»ÓÐ×Ó´®
		Vec2D rpos = /*pos + */tf.p + tran.p + MulT(tf.q,site);
		transparentimage(pImgDst, (int)round(rpos.x), (int)round(rpos.y), 
			&map.getFrame(TL::pHpte->getIntervals_int()), 1.0, tf.q.GetAngle()
		);
	}
}
void DrawAABB(const b2AABB& _box, const Transform& tf ) {
	b2AABB box(_box);

	Vec2D points_db[4] = {
		box.lowerBound,
		{box.lowerBound.x,box.upperBound.y},
		box.upperBound,
		{box.upperBound.x,box.lowerBound.y}
	};
	POINT points[4];
	for (int i = 0; i < 4; ++i) {
		points_db[i].RotateT(tf.q) += tf.p;
		points[i] = POINT_DB_TO_LONG(points_db[i]);
	}


	polygon(points, 4);
}
void DrawShape(const MgGeometryType2D::Polygon& _shape, const Transform& tf) {
	MgGeometryType2D::Polygon shape(_shape);
	if (shape.Extent() == 0)return;
	for (int i = 0; i < shape.Extent(); ++i) {
		shape[i].RotateT(tf.q) += tf.p;
	}
	int n = (int)shape.Extent();
	POINT* p = new POINT[n];

	for (int i = 0; i < n; ++i) {
		p[i].x = DB_TO_LONG_ROUND(shape[i].x);
		p[i].y = DB_TO_LONG_ROUND(shape[i].y);
	}

	polygon(p, n);

	delete[] p;
}
void SpriteBody::DrawNormal(IMAGE* pImgDst, const Transform& tf) {

	IMAGE* pWork = GetWorkingImage();
	SetWorkingImage(pImgDst);
	if (son_sprite != NULL) {
		Sprite* cur = son_sprite;
		//Ë÷¼ìµ½´®µ×
		while (cur->next != NULL) {
			cur = cur->next;
		}
		while (cur != NULL) {
			((SpriteBody*)cur)->DrawNormal(pImgDst, { tf.p + site,tf.q }/*, pos + site*/);
			if (cur == son_sprite) {
				Vec2D tpos = site;
				Transform xf(tf);
				xf.p = tf.p + (tpos).RotateT(tf.q);
				/*transparentimage(pImgDst, (int)round(rpos.x), (int)round(rpos.y),
					&map.getFrame(TL::pHpte->getIntervals_int()), 1.0, tf.q.GetAngle()
				);*/
				DrawAABB(OriginalBox, xf);
				DrawAABB(OriginalShapeBox, xf);
				DrawShape(SpriteShape, xf);
			}

			cur = cur->last;
		}


	}
	else {	//Ã»ÓÐ×Ó´®
		Transform xf(tf);
		xf.p = tf.p  + MulT(tf.q, site);
		DrawAABB(OriginalBox, xf);
		DrawAABB(OriginalShapeBox, xf);
		DrawShape(SpriteShape, xf);
	}
	SetWorkingImage(pWork);
}
b2AABB& SpriteBody::CalAABB(const Transform& _tf) {

	Vec2D Vertex[4] = {
		OriginalBox.lowerBound,
		{OriginalBox.lowerBound.x,OriginalBox.upperBound.y},
		OriginalBox.upperBound,
		{OriginalBox.upperBound.x,OriginalBox.lowerBound.y}
	};
	Transform tf(_tf);
	tf.q.s = -tf.q.s;
	Vec2D lower = Mul(tf, Vertex[0]);
	Vec2D upper = lower;
	for (int i = 1; i < 4; ++i) {
		Vec2D v = Mul(tf, Vertex[i]);
		lower = Min(lower, v);
		upper = Max(upper, v);
	}
	Vec2D r(polygonRadius, polygonRadius);
	TempBox.lowerBound = lower - r;
	TempBox.upperBound = upper + r;
	return TempBox;
}
b2AABB& SpriteBody::CalAABB() {

	Transform tf;
	tf.SetIdentity();
	SpriteShape.ComputeAABB(&OriginalShapeBox, tf, 0);
	OriginalBox = OriginalShapeBox;
	if (son_sprite != NULL) {
		b2AABB temp;
		Sprite* cur = son_sprite;
		//Ë÷¼ìµ½´®µ×
		while (cur->next != NULL) {
			cur = cur->next;
		}
		while (cur != NULL) {
			temp.Combine(((SpriteBody*)cur)->CalAABB());
			cur = cur->last;
		}
		OriginalBox.Combine(temp);
	}
	TempBox = OriginalBox;
	TempBox.lowerBound += site;
	TempBox.upperBound += site;
	return TempBox;

}