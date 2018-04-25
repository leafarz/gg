#include "math/Color.h"

namespace gg { namespace math {
	const Color Color::black	= Color(0.0f,				0.0f,				0.0f,				255.0f / 255.0f);
	const Color Color::blue		= Color(0.0f,				0.0f,				255.0f / 255.0f,	255.0f / 255.0f);
	const Color Color::brown	= Color(165.0f / 255.0f,	42.0f/255.0f,		42.0f / 255.0f,		255.0f / 255.0f);
	const Color Color::cyan		= Color(0.0f,				255.0f / 255.0f,	255.0f / 255.0f,	255.0f / 255.0f);
	const Color Color::gray		= Color(128.0f / 255.0f,	128.0f / 255.0f,	128.0f / 255.0f,	255.0f / 255.0f);
	const Color Color::green	= Color(0.0f,				255.0f / 255.0f,	0.0f,				255.0f / 255.0f);
	const Color Color::magenta	= Color(255.0f / 255.0f,	0.0f,				255.0f / 255.0f,	255.0f / 255.0f);
	const Color Color::orange	= Color(255.0f / 255.0f,	165.0f / 255.0f,	0.0f,				255.0f / 255.0f);
	const Color Color::purple	= Color(128.0f / 255.0f,	0.0f,				128.0f / 255.0f,	255.0f / 255.0f);
	const Color Color::red		= Color(255.0f / 255.0f,	0.0f,				0.0f,				255.0f / 255.0f);
	const Color Color::yellow	= Color(255.0f / 255.0f,	255.0f / 255.0f,	0.0f,				255.0f / 255.0f);
	const Color Color::white	= Color(255.0f / 255.0f,	255.0f / 255.0f,	255.0f / 255.0f,	255.0f / 255.0f);

	Color::Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{ }

	float Color::getGray(void) const
	{
		return 0.299f * r + 0.587f * g + 0.114f * b;
	}

	Color Color::grayColor(void) const
	{
		float _gray = getGray();
		return Color(_gray, _gray, _gray, 1);
	}

	math::Vec2f Color::rg(void) const { return math::Vec2f(r, g); }
	math::Vec2f Color::rb(void) const { return math::Vec2f(r, b); }
	math::Vec2f Color::ra(void) const { return math::Vec2f(r, a); }
	math::Vec2f Color::gr(void) const { return math::Vec2f(g, r); }
	math::Vec2f Color::gb(void) const { return math::Vec2f(g, b); }
	math::Vec2f Color::ga(void) const { return math::Vec2f(g, a); }
	math::Vec2f Color::br(void) const { return math::Vec2f(b, r); }
	math::Vec2f Color::bg(void) const { return math::Vec2f(b, g); }
	math::Vec2f Color::ba(void) const { return math::Vec2f(b, a); }
	math::Vec2f Color::ar(void) const { return math::Vec2f(a, r); }
	math::Vec2f Color::ag(void) const { return math::Vec2f(a, g); }
	math::Vec2f Color::ab(void) const { return math::Vec2f(a, b); }

	math::Vec3f Color::rgb(void) const { return math::Vec3f(r, g, b); }
	math::Vec3f Color::rbg(void) const { return math::Vec3f(r, b, g); }
	math::Vec3f Color::rga(void) const { return math::Vec3f(r, g, a); }
	math::Vec3f Color::rag(void) const { return math::Vec3f(r, a, g); }
	math::Vec3f Color::rba(void) const { return math::Vec3f(r, b, a); }
	math::Vec3f Color::rab(void) const { return math::Vec3f(r, a, b); }
	math::Vec3f Color::grb(void) const { return math::Vec3f(g, r, b); }
	math::Vec3f Color::gbr(void) const { return math::Vec3f(g, b, r); }
	math::Vec3f Color::gra(void) const { return math::Vec3f(g, r, a); }
	math::Vec3f Color::gar(void) const { return math::Vec3f(g, a, r); }
	math::Vec3f Color::gba(void) const { return math::Vec3f(g, b, a); }
	math::Vec3f Color::gab(void) const { return math::Vec3f(g, a, b); }
	math::Vec3f Color::brg(void) const { return math::Vec3f(b, r, g); }
	math::Vec3f Color::bgr(void) const { return math::Vec3f(b, g, r); }
	math::Vec3f Color::bra(void) const { return math::Vec3f(b, r, a); }
	math::Vec3f Color::bar(void) const { return math::Vec3f(b, a, r); }
	math::Vec3f Color::bga(void) const { return math::Vec3f(b, g, a); }
	math::Vec3f Color::bag(void) const { return math::Vec3f(b, a, g); }
	math::Vec3f Color::arg(void) const { return math::Vec3f(a, r, g); }
	math::Vec3f Color::agr(void) const { return math::Vec3f(a, g, r); }
	math::Vec3f Color::arb(void) const { return math::Vec3f(a, r, b); }
	math::Vec3f Color::abr(void) const { return math::Vec3f(a, b, r); }
	math::Vec3f Color::agb(void) const { return math::Vec3f(a, g, b); }
	math::Vec3f Color::abg(void) const { return math::Vec3f(a, b, g); }
}/*namespace math*/ }// namespace gg
