#pragma once

#include "Nitrogen/Renderer/Buffer.h"
#include <stdint.h>

namespace Nitrogen{

	/////////////////////////////////////////////////////////////////////
	/// INDEX-BUFFER ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_Count;
		uint32_t m_RendererID;
	};

	//////////////////////////////////////////////////////////////////////
	/// VERTEX-BUFFER ////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		
		virtual void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}