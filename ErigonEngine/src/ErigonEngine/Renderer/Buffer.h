#pragma once

namespace ErigonEngine
{

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ErigonEngine::ShaderDataType::Float:  return 4;
			case ErigonEngine::ShaderDataType::Float2: return 4*2;
			case ErigonEngine::ShaderDataType::Float3: return 4*3;
			case ErigonEngine::ShaderDataType::Float4: return 4*4;
			case ErigonEngine::ShaderDataType::Mat3:   return 4*3*3;
			case ErigonEngine::ShaderDataType::Mat4:   return 4*4*4;
			case ErigonEngine::ShaderDataType::Int:    return 4;
			case ErigonEngine::ShaderDataType::Int2:   return 4*2;
			case ErigonEngine::ShaderDataType::Int3:   return 4*3;
			case ErigonEngine::ShaderDataType::Int4:   return 4*4;
			case ErigonEngine::ShaderDataType::Bool:   return 1;
		}
		EE_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		uint32_t Offset;
		uint32_t Size;
		ShaderDataType Type;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), 
			Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ErigonEngine::ShaderDataType::Float:
				return 1;
			case ErigonEngine::ShaderDataType::Float2:
				return 2;
			case ErigonEngine::ShaderDataType::Float3:
				return 3;
			case ErigonEngine::ShaderDataType::Float4:
				return 4;
			case ErigonEngine::ShaderDataType::Mat3:
				return 9;
			case ErigonEngine::ShaderDataType::Mat4:
				return 16;
			case ErigonEngine::ShaderDataType::Int:
				return 1;
			case ErigonEngine::ShaderDataType::Int2:
				return 2;
			case ErigonEngine::ShaderDataType::Int3:
				return 3;
			case ErigonEngine::ShaderDataType::Int4:
				return 4;
			case ErigonEngine::ShaderDataType::Bool:
				return 1;
			}
			EE_CORE_ASSERT(false, "Unknown shader data type!");
			return 0;
		}

	};

	class BufferLayout
	{
	public:

		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) 
		{
			CalculateOffsetAndStride();
		}
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	
	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};
}