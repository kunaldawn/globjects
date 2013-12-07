#version 430
#extension GL_ARB_shading_language_include : require

#include </transparency/abuffer.glsl>

layout(binding = 0) uniform atomic_uint counter;

layout(pixel_center_integer) in ivec4 gl_FragCoord;

in vec3 normal;
in float z;
in vec4 vertexColor;

layout(location = 0) out vec4 opaqueFragColorZ;

void main() {
	if (vertexColor.a < 0.9999) { // damned floats...
		int size = atomicAdd(headList[gl_FragCoord.y * screenSize.x + gl_FragCoord.x].size, 1) + 1;
		if (size > ABUFFER_SIZE) {
			discard;
		}

		int index = int(atomicCounterIncrement(counter));
		int previousHead = atomicExchange(headList[gl_FragCoord.y * screenSize.x + gl_FragCoord.x].startIndex, index);

		list[index].next = previousHead;
		list[index].color = vec4(vertexColor.rgb * vertexColor.a, vertexColor.a); // pre-multiply alpha
		list[index].z = z;

		discard; // translucent fragments go into the a buffer, but not in the color buffer
	}

	opaqueFragColorZ = vec4(vertexColor.rgb, z);
}