#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <dwmapi.h>

#include "../External/Imgui/imgui_internal.h"
#include "../External/Imgui/imgui.h"
#include "../External/Imgui/imgui_impl_win32.h"
#include "../External/Imgui/imgui_impl_dx9.h"
#include "../features/globals.h"
#include "../features/menu/menu.h"
#include "../features/cheat.h"

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "Dwmapi.lib")

IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };

HWND own_hwnd = NULL;
HWND game_hwnd = NULL;
MSG Message = { NULL };

RECT game_rect = { NULL };
D3DPRESENT_PARAMETERS d3dpp;


struct screen_center {
	DWORD x, y;
};




WPARAM main_loop();
void render();

bool load_image_from_memory(void* data, size_t size, IDirect3DTexture9** out_texture)
{
	IDirect3DTexture9* texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(p_Device, data, size, D3DX_DEFAULT, D3DX_DEFAULT, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, &info, NULL, &texture);


	if (hr != D3D_OK)
		return false;

	*out_texture = texture;
	return true;
}

HRESULT init_wndparams(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = width;
	p_Params.BackBufferHeight = height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device))) {
		p_Object->Release();
		exit(4);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGuiStyle& s = ImGui::GetStyle();
	io.IniFilename = NULL;

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);
	return S_OK;
}

HWND get_process_wnd(uint32_t pid)
{
	std::pair<HWND, uint32_t> params = { 0, pid };
	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
		auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
		uint32_t processId = 0;

		if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
			SetLastError((uint32_t)-1);
			pParams->first = hwnd;
			return FALSE;
		}

		return TRUE;

		}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
		return params.first;

	return NULL;
}

void cleanup()
{
	if (p_Device) { p_Device->Release(); p_Device = NULL; }
	if (p_Object) { p_Object->Release(); p_Object = NULL; }
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(own_hwnd);
}

void set_window_target()
{
	while (true) {
		game_hwnd = get_process_wnd(processid);
		if (game_hwnd) {
			ZeroMemory(&game_rect, sizeof(game_rect));
			GetWindowRect(game_hwnd, &game_rect);
			GetWindowLong(game_hwnd, GWL_STYLE);

			screen_center sc = { width / 2, height / 2 };

			MoveWindow(own_hwnd, game_rect.left, game_rect.top, width, height, true);
		}
	}
}


void setup_window()
{
	HANDLE Windowthread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)set_window_target, 0, 0, 0);
	if (Windowthread != 0)
		CloseHandle(Windowthread);

	WNDCLASSEXA wcex = {
		sizeof(WNDCLASSEXA),
		0,
		DefWindowProcA,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		("infs"),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	GetWindowRect(GetDesktopWindow(), &Rect);

	RegisterClassExA(&wcex);

	own_hwnd = CreateWindowExA(NULL, ("infs"), ("infs"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);
	SetWindowLong(own_hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	SetLayeredWindowAttributes(own_hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);

	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(own_hwnd, &margin);


	ShowWindow(own_hwnd, SW_SHOW);

	UpdateWindow(own_hwnd);
}



void render() {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	entity_loop();
	draw_menu();

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}

	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}
WPARAM main_loop() {

#if _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif

	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, own_hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(0);

		if (hwnd_active == game_hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(own_hwnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(game_hwnd, &rc);
		ClientToScreen(game_hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = game_hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {

			old_rc = rc;

			width = rc.right;
			height = rc.bottom;

			p_Params.BackBufferWidth = width;
			p_Params.BackBufferHeight = height;
			SetWindowPos(own_hwnd, (HWND)0, xy.x, xy.y, width, height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();
	}


	cleanup();

	return Message.wParam;
}




