#include<Windows.h>
#include<iostream>
#include<string>
#include <stdlib.h>
//寻找WorkerW-2窗口并隐藏
BOOL CALLBACK EnumWinProc(HWND hwnd, LPARAM lParam)
{

    HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
    if (hDefView != 0) {
        HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
        ShowWindow(hWorkerw, SW_HIDE);

        return FALSE;
    }
    return TRUE;
}

int main(int argc, char* argv[])
{
    STARTUPINFO si{ 0 };
    PROCESS_INFORMATION pi{ 0 };
    //设置显示命令


    //LPCWSTR lpParam = L" D:\\video\\1.mp4 -noborder -x 2560 -y 1440 -loop 0";
//if (CreateProcess(L"D:\\sf\\ffmpeg\\bin\\ffplay.exe", (LPWSTR)lpParam, 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &si, &pi)) //创建视频窗口进程显示视频
    {
        //获取桌面窗口的句柄
        HWND hProgman = FindWindow(L"Progman", 0);
        //发送0x52c消息
        SendMessage(hProgman, 0x52c, 0, 0);
        //获取视频窗口的句柄
       // HWND hffplay = FindWindow(L"SDL_app", 0);
        //将视频窗口设置为桌面窗口的子窗口
        HWND neww = HWND(std::atoi(argv[1]));
        SetParent(neww, hProgman);
        RECT rect;
        GetWindowRect(hProgman, &rect);
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);       // 获取最大化的窗口大小
        SetWindowLongPtr(neww, GWL_STYLE, WS_VISIBLE | WS_POPUP); // 去掉标题栏
        std::cout << w;
        SetWindowPos(neww, HWND_TOP, -rect.left, -rect.top,w, h, SWP_SHOWWINDOW);
       // MoveWindow(neww,0, 300, 2200, 1000, true);
        //枚举窗口找到WorkerW-2并隐藏它
        EnumWindows(EnumWinProc, 0);
       
    }
    

    //  TerminateProcess(pi.hProcess, 0);//终止进程
    //  ::CloseHandle(pi.hThread);
    //  ::CloseHandle(pi.hProcess);


      //壁纸路径
     // char path[MAX_PATH] = "C:\\Users\\yam_l\\Pictures\\Camera Roll\\1.jpg";
      //添加壁纸
      //SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, path, SPIF_UPDATEINIFILE);

    return 0;
}