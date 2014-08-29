#include <globjects/VertexArrayObject.h>

#include <cassert>

#include <glbinding/gl/functions.h>

#include <globjects/ObjectVisitor.h>
#include <globjects/VertexAttributeBinding.h>

#include "container_helpers.hpp"
#include "registry/ObjectRegistry.h"

#include "Resource.h"

namespace glo
{

VertexArrayObject::VertexArrayObject()
: Object(new VertexArrayObjectResource)
{
}

VertexArrayObject::VertexArrayObject(IDResource * resource)
: Object(resource)
{
}

VertexArrayObject * VertexArrayObject::fromId(gl::GLuint id)
{
    return new VertexArrayObject(new ExternalResource(id));
}

VertexArrayObject * VertexArrayObject::defaultVAO()
{
    return ObjectRegistry::current().defaultVAO();
}

VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::accept(ObjectVisitor & visitor)
{
	visitor.visitVertexArrayObject(this);
}

void VertexArrayObject::bind() const
{
	gl::glBindVertexArray(id());
}

void VertexArrayObject::unbind()
{
	gl::glBindVertexArray(0);
}

VertexAttributeBinding* VertexArrayObject::binding(gl::GLuint bindingIndex)
{
	if (!m_bindings[bindingIndex])
	{
        m_bindings[bindingIndex] = new VertexAttributeBinding(this, bindingIndex);
	}

	return m_bindings[bindingIndex];
}

const VertexAttributeBinding* VertexArrayObject::binding(gl::GLuint bindingIndex) const
{
    if (!m_bindings.count(bindingIndex))
    {
        return nullptr;
    }

    return m_bindings.at(bindingIndex);
}

void VertexArrayObject::enable(gl::GLint attributeIndex)
{
	bind();

    gl::glEnableVertexAttribArray(attributeIndex);
}

void VertexArrayObject::disable(gl::GLint attributeIndex)
{
    bind();

    gl::glDisableVertexAttribArray(attributeIndex);
}

void VertexArrayObject::setAttributeDivisor(gl::GLint attributeIndex, gl::GLuint divisor)
{
    bind();

    gl::glVertexAttribDivisor(attributeIndex, divisor);
}

std::vector<VertexAttributeBinding*> VertexArrayObject::bindings()
{
	std::vector<VertexAttributeBinding*> bindings;

    for (std::pair<gl::GLuint, ref_ptr<VertexAttributeBinding>> pair: m_bindings)
	{
		bindings.push_back(pair.second);
	}

	return bindings;
}

std::vector<const VertexAttributeBinding*> VertexArrayObject::bindings() const
{
    std::vector<const VertexAttributeBinding*> bindings;

    for (std::pair<gl::GLuint, ref_ptr<VertexAttributeBinding>> pair: m_bindings)
    {
        bindings.push_back(pair.second);
    }

    return bindings;
}

void VertexArrayObject::drawArrays(gl::GLenum mode, gl::GLint first, gl::GLsizei count) const
{
    bind();
    gl::glDrawArrays(mode, first, count);
}

void VertexArrayObject::drawArraysInstanced(gl::GLenum mode, gl::GLint first, gl::GLsizei count, gl::GLsizei instanceCount) const
{
    bind();
    gl::glDrawArraysInstanced(mode, first, count, instanceCount);
}

void VertexArrayObject::drawArraysInstancedBaseInstance(gl::GLenum mode, gl::GLint first, gl::GLsizei count, gl::GLsizei instanceCount, gl::GLuint baseInstance) const
{
    bind();
    gl::glDrawArraysInstancedBaseInstance(mode, first, count, instanceCount, baseInstance);
}

void VertexArrayObject::drawArraysIndirect(gl::GLenum mode, const void* indirect) const
{
    assert(indirect != nullptr);

    bind();
    gl::glDrawArraysIndirect(mode, indirect);
}

void VertexArrayObject::multiDrawArrays(gl::GLenum mode, gl::GLint* first, const gl::GLsizei* count, gl::GLsizei drawCount) const
{
    bind();
    gl::glMultiDrawArrays(mode, first, count, drawCount);
}

void VertexArrayObject::multiDrawArraysIndirect(gl::GLenum mode, const void* indirect, gl::GLsizei drawCount, gl::GLsizei stride) const
{
    bind();
    gl::glMultiDrawArraysIndirect(mode, indirect, drawCount, stride);
}

void VertexArrayObject::drawElements(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, const void * indices) const
{
    bind();
    gl::glDrawElements(mode, count, type, indices);
}

void VertexArrayObject::drawElementsBaseVertex(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, const void* indices, gl::GLint baseVertex) const
{
    bind();
    gl::glDrawElementsBaseVertex(mode, count, type, const_cast<void*>(indices), baseVertex);
}

void VertexArrayObject::drawElementsInstanced(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, const void* indices, gl::GLsizei primitiveCount) const
{
    bind();
    gl::glDrawElementsInstanced(mode, count, type, indices, primitiveCount);
}

void VertexArrayObject::drawElementsInstancedBaseInstance(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, const void* indices, gl::GLsizei instanceCount, gl::GLuint baseInstance) const
{
    bind();
    gl::glDrawElementsInstancedBaseInstance(mode, count, type, indices, instanceCount, baseInstance);
}

void VertexArrayObject::drawElementsInstancedBaseVertex(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, const void* indices, gl::GLsizei instanceCount, gl::GLint baseVertex) const
{
    bind();
    gl::glDrawElementsInstancedBaseVertex(mode, count, type, indices, instanceCount, baseVertex);
}

void VertexArrayObject::drawElementsInstancedBaseVertexBaseInstance(gl::GLenum mode, gl::GLsizei count, gl::GLenum type, const void* indices, gl::GLsizei instanceCount, gl::GLint baseVertex, gl::GLuint baseInstance) const
{
    bind();
    gl::glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instanceCount, baseVertex, baseInstance);
}

void VertexArrayObject::multiDrawElements(gl::GLenum mode, const gl::GLsizei* count, gl::GLenum type, const void** indices, gl::GLsizei drawCount) const
{
    bind();
    gl::glMultiDrawElements(mode, count, type, indices, drawCount);
}

void VertexArrayObject::multiDrawElementsBaseVertex(gl::GLenum mode, const gl::GLsizei* count, gl::GLenum type, const void** indices, gl::GLsizei drawCount, gl::GLint* baseVertex) const
{
    bind();
    gl::glMultiDrawElementsBaseVertex(mode, const_cast<gl::GLsizei*>(count), type, const_cast<void**>(indices), drawCount, baseVertex);
}

void VertexArrayObject::multiDrawElementsIndirect(gl::GLenum mode, gl::GLenum type, const void* indirect, gl::GLsizei drawCount, gl::GLsizei stride) const
{
    bind();
    gl::glMultiDrawElementsIndirect(mode, type, indirect, drawCount, stride);
}

void VertexArrayObject::drawRangeElements(gl::GLenum mode, gl::GLuint start, gl::GLuint end, gl::GLsizei count, gl::GLenum type, const void* indices) const
{
    bind();
    gl::glDrawRangeElements(mode, start, end, count, type, indices);
}

void VertexArrayObject::drawRangeElementsBaseVertex(gl::GLenum mode, gl::GLuint start, gl::GLuint end, gl::GLsizei count, gl::GLenum type, const void* indices, gl::GLint baseVertex) const
{
    bind();
    gl::glDrawRangeElementsBaseVertex(mode, start, end, count, type, const_cast<void*>(indices), baseVertex);
}

void VertexArrayObject::multiDrawArrays(gl::GLenum mode, const std::vector<VertexArrayObject::MultiDrawArraysRange> & ranges) const
{
    std::vector<gl::GLint> firsts = collect_member(ranges, MultiDrawArraysRange, first);
    std::vector<gl::GLsizei> counts = collect_member(ranges, MultiDrawArraysRange, count);

    multiDrawArrays(mode, firsts.data(), counts.data(), static_cast<gl::GLsizei>(ranges.size()));
}

void VertexArrayObject::multiDrawElements(gl::GLenum mode, gl::GLenum type, const std::vector<VertexArrayObject::MultiDrawElementsRange> & ranges) const
{
    std::vector<gl::GLsizei> counts = collect_member(ranges, MultiDrawElementsRange, count);
    std::vector<const void*> indices = collect_type_member(const void*, ranges, MultiDrawElementsRange, indices);

    multiDrawElements(mode, counts.data(), type, indices.data(), static_cast<gl::GLsizei>(ranges.size()));
}

void VertexArrayObject::multiDrawElementsBaseVertex(gl::GLenum mode, gl::GLenum type, const std::vector<VertexArrayObject::MultiDrawElementsBaseVertexRange> & ranges) const
{
    std::vector<gl::GLsizei> counts = collect_member(ranges, MultiDrawElementsBaseVertexRange, count);
    std::vector<const void*> indices = collect_type_member(const void*, ranges, MultiDrawElementsBaseVertexRange, indices);
    std::vector<gl::GLint> baseVertices = collect_member(ranges, MultiDrawElementsBaseVertexRange, baseVertex);

    multiDrawElementsBaseVertex(mode, counts.data(), type, indices.data(), static_cast<gl::GLsizei>(ranges.size()), baseVertices.data());
}

gl::GLenum VertexArrayObject::objectType() const
{
    return gl::GL_VERTEX_ARRAY;
}

} // namespace glo
