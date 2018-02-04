#ifndef		GG_MATERIAL_H
#define		GG_MATERIAL_H
#pragma once

#include <stack>
#include "math/Vec3f.h"
#include "math/Mat4f.h"

#include "core/Types.h"

namespace gg
{
	class Shader;
	class Material
	{
	private:
		friend class MeshRenderer;

	private:
		template<typename T>
		struct Data
		{
			std::string key;
			T val;
			Data(const std::string& key, T val)
				: key(key), val(val)
			{ }
		};
		
	public:
		Material(void);
		Material(Shader* shader);
		~Material(void);

		Shader* getShader(void) const;
		void setShader(Shader* shader);

		void setUniformi(const std::string& key, int val);
		void setUniformf(const std::string& key, float val);
		void setUniform(const std::string& key, Math::Vec3f val);
		void setUniform(const std::string& key, float x, float y, float z);
		void setUniform(const std::string& key, Math::Mat4f val);

	private:
		void bind(void);
		void unbind(void) const;

	private:
		Shader* m_Shader;

		std::stack<Data<int>> m_Ints;
		std::stack<Data<float>> m_Floats;
		std::stack<Data<Math::Vec3f>> m_Vec3fs;
		std::stack<Data<Math::Mat4f>> m_Mat4fs;

	}; // class Material
} // namespace gg

#endif
