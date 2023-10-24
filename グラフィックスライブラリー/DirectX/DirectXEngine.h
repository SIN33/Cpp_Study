#pragma once
#include <wtypes.h>
#include <string>
#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "d3dx12.h"
#include <stdexcept>
#include <vector>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
using Microsoft::WRL::ComPtr;

// ダミーのテクスチャ情報

class DirectXEngine
{
public:
	DirectXEngine(unsigned int width, unsigned int height, std::wstring title);
	void OnInit(HWND hwnd);
	//void OnUpdate();
	void OnRender();
	void OnDestroy();

	const WCHAR* GetTitle() const { return title_.c_str(); }
	unsigned int GetWindowWidth() const { return windowWidth_; }
	unsigned int GetWindowHeight() const { return windowHeight_; }

private:
	static const unsigned int kFrameCount = 2;

	std::wstring title_;
	unsigned int windowWidth_;
	unsigned int windowHeight_;

	// ★ポリゴン描画のため追加
	CD3DX12_VIEWPORT viewport_; // ビューポート
	CD3DX12_RECT scissorrect_;  // シザー短形

// パイプラインオブジェクト
	ComPtr<ID3D12Device> device_;
	ComPtr<ID3D12CommandAllocator> commandAllocator_;
	ComPtr<ID3D12GraphicsCommandList> commandList_;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	ComPtr<IDXGISwapChain4> swapchain_;
	ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	ComPtr<ID3D12DescriptorHeap> srvHeap_;
	ComPtr<ID3D12Resource> renderTargets_[kFrameCount];
	ComPtr<ID3D12PipelineState> pipelinestate_;
	ComPtr<ID3D12RootSignature> rootsignature_;

	// リソース
	ComPtr<ID3D12Resource> vertexBuffer_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	ComPtr<ID3D12Resource> indexBuffer_;
	D3D12_INDEX_BUFFER_VIEW indexBufferView_;
	ComPtr<ID3D12Resource> textureBuffer_;

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 uv;
	};

	// フェンス
	ComPtr<ID3D12Fence> fence_;
	UINT64 fenceValue_;
	HANDLE fenceEvent_;

	void LoadPipeline(HWND hwnd);
	void LoadAssets(); // ★ポリゴン描画のため追加

	void CreateD3D12Device(IDXGIFactory6* dxgiFactory, ID3D12Device** d3d12device);
	void ThrowIfFailed(HRESULT hr);

	//定数値
	static const UINT kDummyTextureWidth = 256;
	static const UINT kDummyTextureHeight = 256;
	static const UINT kDummyTexturePixelSize = 4;
	std::vector<UINT8> GenerateDummyTextureData();
};
