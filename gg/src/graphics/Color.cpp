#include "graphics/Color.h"

namespace gg
{
	Color::Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{ }

	float Color::gray(void) const
	{
		return 0.299f * r + 0.587f * g + 0.114f * b;
	}

	Color Color::grayColor(void) const
	{
		float _gray = gray();
		return Color(_gray, _gray, _gray, 1);
	}

	Math::Vec2f Color::rg(void) const { return Math::Vec2f(r, g); }
	Math::Vec2f Color::rb(void) const { return Math::Vec2f(r, b); }
	Math::Vec2f Color::ra(void) const { return Math::Vec2f(r, a); }
	Math::Vec2f Color::gr(void) const { return Math::Vec2f(g, r); }
	Math::Vec2f Color::gb(void) const { return Math::Vec2f(g, b); }
	Math::Vec2f Color::ga(void) const { return Math::Vec2f(g, a); }
	Math::Vec2f Color::br(void) const { return Math::Vec2f(b, r); }
	Math::Vec2f Color::bg(void) const { return Math::Vec2f(b, g); }
	Math::Vec2f Color::ba(void) const { return Math::Vec2f(b, a); }
	Math::Vec2f Color::ar(void) const { return Math::Vec2f(a, r); }
	Math::Vec2f Color::ag(void) const { return Math::Vec2f(a, g); }
	Math::Vec2f Color::ab(void) const { return Math::Vec2f(a, b); }

	Math::Vec3f Color::rgb(void) const { return Math::Vec3f(r, g, b); }
	Math::Vec3f Color::rbg(void) const { return Math::Vec3f(r, b, g); }
	Math::Vec3f Color::rga(void) const { return Math::Vec3f(r, g, a); }
	Math::Vec3f Color::rag(void) const { return Math::Vec3f(r, a, g); }
	Math::Vec3f Color::rba(void) const { return Math::Vec3f(r, b, a); }
	Math::Vec3f Color::rab(void) const { return Math::Vec3f(r, a, b); }
	Math::Vec3f Color::grb(void) const { return Math::Vec3f(g, r, b); }
	Math::Vec3f Color::gbr(void) const { return Math::Vec3f(g, b, r); }
	Math::Vec3f Color::gra(void) const { return Math::Vec3f(g, r, a); }
	Math::Vec3f Color::gar(void) const { return Math::Vec3f(g, a, r); }
	Math::Vec3f Color::gba(void) const { return Math::Vec3f(g, b, a); }
	Math::Vec3f Color::gab(void) const { return Math::Vec3f(g, a, b); }
	Math::Vec3f Color::brg(void) const { return Math::Vec3f(b, r, g); }
	Math::Vec3f Color::bgr(void) const { return Math::Vec3f(b, g, r); }
	Math::Vec3f Color::bra(void) const { return Math::Vec3f(b, r, a); }
	Math::Vec3f Color::bar(void) const { return Math::Vec3f(b, a, r); }
	Math::Vec3f Color::bga(void) const { return Math::Vec3f(b, g, a); }
	Math::Vec3f Color::bag(void) const { return Math::Vec3f(b, a, g); }
	Math::Vec3f Color::arg(void) const { return Math::Vec3f(a, r, g); }
	Math::Vec3f Color::agr(void) const { return Math::Vec3f(a, g, r); }
	Math::Vec3f Color::arb(void) const { return Math::Vec3f(a, r, b); }
	Math::Vec3f Color::abr(void) const { return Math::Vec3f(a, b, r); }
	Math::Vec3f Color::agb(void) const { return Math::Vec3f(a, g, b); }
	Math::Vec3f Color::abg(void) const { return Math::Vec3f(a, b, g); }
} // namespace gg
