//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "resource.h"
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "PathFinding.h"




#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

//Global Variables
static int s_iMouseX = 0;
static int s_iMouseY = 0;
bool g_mouseIsDown = false;
static ECHOICE s_currentChoice = NONE;
bool restart = false;
bool pathing = false;
int timer = 0;


LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	
	
	

    switch (_uiMsg)
    {
		case WM_CREATE:
		{
			// Do initialization stuff here.
			
			// Return Success.
			return (0);
		}
		break;
	
		case WM_MOUSEMOVE:
		{
			//int iMouseX = LOWORD(_lParam);
			s_iMouseX = static_cast<int>(LOWORD(_lParam));
			s_iMouseY = static_cast<int>(HIWORD(_lParam));
			
			
			
		}
		break;

		case WM_LBUTTONUP:
		{
			g_mouseIsDown = false;
		
		}
		break;
		
		case WM_LBUTTONDOWN:
		{
			g_mouseIsDown = true;
			

			switch (s_currentChoice)
			{

			case START:
			{
				
				

				break;
			}
			case END:
			{

				break;
			}
			case BLOCKER:
			{

				break;
			}
			default: break;
			}

			return (0);
		}
		break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);

            return(0);
        }
        break;

		case WM_COMMAND:
		{
			switch (LOWORD(_wParam))
			{
			case ID_FILE_EXIT:
			{
				PostQuitMessage(0);
				break;
			}
			case ID_ADD_STARTPOINT:
			{
				s_currentChoice = START;
				break;
			}
			case ID_ADD_ENDPOINT:
			{
				s_currentChoice = END;
				break;
			}
			case ID_ADD_BLOCKER:
			{
				s_currentChoice = BLOCKER;
				break;
			}
			case ID_EXECUTE:
			{
				
				pathing = true;
				
				break;
			}
			case ID_RESET:
			{
				restart = true;
				break;
			}
			case ID_HELP_INSTRUCTIONS:
			{
				MessageBox(_hWnd, L"Define a start point, an end point and add some blockers then press 'execute'. The program will not run if there is no path. Press 'reset' to start over", L"Instructions", MB_OK | MB_ICONINFORMATION);
				break;
			}

			default:
				break;
			}
			return(0);
		}
		break;

        default:break;
    } 



    return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND 
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
    WNDCLASSEX winclass;

    winclass.cbSize = sizeof(WNDCLASSEX);
    winclass.style = CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc = WindowProc;
    winclass.cbClsExtra = 0;
    winclass.cbWndExtra = 0;
    winclass.hInstance = _hInstance;
    winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);//static_cast<HMENU>(LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1)));
    winclass.lpszClassName = WINDOW_CLASS_NAME;
    winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&winclass))
    {
        // Failed to register.
        return (0);
    }

    HWND hwnd; 
    hwnd = CreateWindowEx(NULL,
                  WINDOW_CLASS_NAME,
                  _pcTitle,
              WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 
                  CW_USEDEFAULT, CW_USEDEFAULT,
                  _iWidth, _iHeight,
                  NULL,
                  NULL,
                  _hInstance,
                  NULL);
    
    if (!hwnd)
    {
        // Failed to create.
        return (0);
    }

    return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    const int kiWidth = 800;
    const int kiHeight = 800;

    HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"A* Path Finding");

    CGame& rGame = CGame::GetInstance();
	

    if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
    {
        // Failed
        return (0);
    }

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			
            rGame.ExecuteOneFrame(s_iMouseX, s_iMouseY, g_mouseIsDown, s_currentChoice, pathing);
			
        }

		if (pathing)
		{
			
			if (timer < 1)
			{
				timer += 1;
			}
			else if (timer >= 1)
			{
				pathing = false;
				timer = 0;
			}
		}

		if (restart == true)
		{
			pathing = false;
			rGame.RestartLevel(kiWidth, kiHeight);
			restart = false;
		}
    }


		CGame::DestroyInstance();
	

    return (static_cast<int>(msg.wParam));
}
