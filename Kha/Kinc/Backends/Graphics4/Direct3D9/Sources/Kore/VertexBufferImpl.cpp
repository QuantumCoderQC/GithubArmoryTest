#include "pch.h"

#include "Direct3D9.h"
#include "VertexBufferImpl.h"

#include <Kore/Graphics4/Graphics.h>
#include <Kore/SystemMicrosoft.h>

using namespace Kore;

Graphics4::VertexBuffer* VertexBufferImpl::_current = nullptr;

VertexBufferImpl::VertexBufferImpl(int count, int instanceDataStepRate) : myCount(count), instanceDataStepRate(instanceDataStepRate) {}

Graphics4::VertexBuffer::VertexBuffer(int count, const VertexStructure& structure, Usage usage, int instanceDataStepRate) : VertexBufferImpl(count, instanceDataStepRate) {
	DWORD usageFlags = D3DUSAGE_WRITEONLY;
	if (usage == Kore::Graphics4::DynamicUsage){
		usageFlags = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
	}
	
	myStride = 0;
	for (int i = 0; i < structure.size; ++i) {
		switch (structure.elements[i].data) {
		case Float1VertexData:
			myStride += 4 * 1;
			break;
		case Float2VertexData:
			myStride += 4 * 2;
			break;
		case Float3VertexData:
			myStride += 4 * 3;
			break;
		case Float4VertexData:
			myStride += 4 * 4;
			break;
		case ColorVertexData:
			myStride += 4;
			break;
		case Float4x4VertexData:
			myStride += 4 * 4 * 4;
			break;
		}
	}

	Microsoft::affirm(device->CreateVertexBuffer(stride() * count, usageFlags, 0, D3DPOOL_DEFAULT, &vb, 0));
}

Graphics4::VertexBuffer::~VertexBuffer() {
	vb->Release();
}

float* Graphics4::VertexBuffer::lock() {
	return lock(0, count());
}

float* Graphics4::VertexBuffer::lock(int start, int count) {
	float* vertices;
	unset();
	Microsoft::affirm(vb->Lock(start, count * stride(), (void**)&vertices, D3DLOCK_DISCARD));
	return vertices;
}

void Graphics4::VertexBuffer::unlock() {
	Microsoft::affirm(vb->Unlock());
}

int Graphics4::VertexBuffer::_set(int offset) {
	_offset = offset;
	if (instanceDataStepRate == 0) {
		_current = this;
	}
	else {
		Microsoft::affirm(device->SetStreamSourceFreq(offset, (D3DSTREAMSOURCE_INSTANCEDATA | instanceDataStepRate)));
	}
	Microsoft::affirm(device->SetStreamSource(offset, vb, 0, stride()));
	return 0;
}

void VertexBufferImpl::unset() {
	if (_current == (Graphics4::VertexBuffer*)this) {
		Microsoft::affirm(device->SetStreamSource(0, nullptr, 0, 0));
		_current = nullptr;
	}
}

int Graphics4::VertexBuffer::count() {
	return myCount;
}

int Graphics4::VertexBuffer::stride() {
	return myStride;
}
