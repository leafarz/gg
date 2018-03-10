#ifndef		GG_COLOR_H
#define		GG_COLOR_H
#pragma once

#include "math/Vec2f.h"
#include "math/Vec3f.h"
namespace gg { namespace Math {
	struct Color
	{
		/* Red component */
		float r;
		/* Green component */
		float g;
		/* Blue component */
		float b;
		/* Alpha component */
		float a;

		/* Creates color with default r,g,b=0 and a=1 unless defined. */
		Color(float r = 0, float g = 0, float b = 0, float a = 1);

		/* Gets the computed scalar gray value of this color. */
		float gray(void) const;
		/* Gets the computed gray color value of this color. */
		Color grayColor(void) const;

		/* Gets the r,g values in Vec2f form. */
		Math::Vec2f rg(void) const;
		/* Gets the r,b values in Vec2f form. */
		Math::Vec2f rb(void) const;
		/* Gets the r,a values in Vec2f form. */
		Math::Vec2f ra(void) const;

		/* Gets the g,r values in Vec2f form. */
		Math::Vec2f gr(void) const;
		/* Gets the g,b values in Vec2f form. */
		Math::Vec2f gb(void) const;
		/* Gets the g,a values in Vec2f form. */
		Math::Vec2f ga(void) const;

		/* Gets the b,r values in Vec2f form. */
		Math::Vec2f br(void) const;
		/* Gets the b,g values in Vec2f form. */
		Math::Vec2f bg(void) const;
		/* Gets the b,a values in Vec2f form. */
		Math::Vec2f ba(void) const;

		/* Gets the a,r values in Vec2f form. */
		Math::Vec2f ar(void) const;
		/* Gets the a,g values in Vec2f form. */
		Math::Vec2f ag(void) const;
		/* Gets the a,b values in Vec2f form. */
		Math::Vec2f ab(void) const;

		/* Gets the r,g,b values in Vec3f form. */
		Math::Vec3f rgb(void) const;
		/* Gets the r,b,g values in Vec3f form. */
		Math::Vec3f rbg(void) const;
		/* Gets the r,g,a values in Vec3f form. */
		Math::Vec3f rga(void) const;
		/* Gets the r,a,g values in Vec3f form. */
		Math::Vec3f rag(void) const;
		/* Gets the r,b,a values in Vec3f form. */
		Math::Vec3f rba(void) const;
		/* Gets the r,a,b values in Vec3f form. */
		Math::Vec3f rab(void) const;

		/* Gets the g,r,b values in Vec3f form. */
		Math::Vec3f grb(void) const;
		/* Gets the g,b,r values in Vec3f form. */
		Math::Vec3f gbr(void) const;
		/* Gets the g,r,a values in Vec3f form. */
		Math::Vec3f gra(void) const;
		/* Gets the g,a,r values in Vec3f form. */
		Math::Vec3f gar(void) const;
		/* Gets the g,b,a values in Vec3f form. */
		Math::Vec3f gba(void) const;
		/* Gets the g,a,b values in Vec3f form. */
		Math::Vec3f gab(void) const;

		/* Gets the b,r,g values in Vec3f form. */
		Math::Vec3f brg(void) const;
		/* Gets the b,g,r values in Vec3f form. */
		Math::Vec3f bgr(void) const;
		/* Gets the b,r,a values in Vec3f form. */
		Math::Vec3f bra(void) const;
		/* Gets the b,a,r values in Vec3f form. */
		Math::Vec3f bar(void) const;
		/* Gets the b,g,a values in Vec3f form. */
		Math::Vec3f bga(void) const;
		/* Gets the b,a,g values in Vec3f form. */
		Math::Vec3f bag(void) const;

		/* Gets the a,r,g values in Vec3f form. */
		Math::Vec3f arg(void) const;
		/* Gets the a,g,r values in Vec3f form. */
		Math::Vec3f agr(void) const;
		/* Gets the a,r,b values in Vec3f form. */
		Math::Vec3f arb(void) const;
		/* Gets the a,b,r values in Vec3f form. */
		Math::Vec3f abr(void) const;
		/* Gets the a,g,b values in Vec3f form. */
		Math::Vec3f agb(void) const;
		/* Gets the a,b,g values in Vec3f form. */
		Math::Vec3f abg(void) const;
	}; // struct Color
}/*namespace Math*/ }// namespace gg

#endif
