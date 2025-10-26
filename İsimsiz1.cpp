#include <windows.h>
#include <objidl.h>      //  sory butcab
#include <gdiplus.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdiplus.lib")

// ===== GDI Efektleri =====
#include <windows.h>

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} _RGBQUAD, *PRGBQUAD;

DWORD WINAPI shader1(LPVOID lpParam)  // rbg ooooooohhhhhhhhhhhhhh my ears 	BY SKÝDDERPANKOZA 2
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, x, y, PATINVERT);
		ReleaseDC(0, hdc);
		DeleteObject(brush);
		Sleep(10);
	}
}


DWORD WINAPI shader2(LPVOID lpParam) // BALLLLLLLLLLLLLLLLLLLLLLLLLLLL WHÝTE BALLL LOLOLOLOLOLOLOLOLOLOLOLOLOLLOLOLOLLOLOLOLOLÇOLOLOO
{
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);


	while (1)
	{
		HDC hdc = GetDC(0);
		int rand_num_x = rand() % w;
		int rand_num_y = rand() % h;

		int top_x = 0 + rand_num_x; // TLC
		int top_y = 0 + rand_num_y; // TRC

		int bottom_x = 100 + rand_num_x; // BLC
		int bottom_y = 100 + rand_num_y; // BLC

		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		Sleep(100);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader3(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    BITMAPINFO bmpi;
    HBITMAP bmp;
    DWORD* pixels = NULL; // 32-bit pixel buffer

    ZeroMemory(&bmpi, sizeof(bmpi));
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&pixels, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight,
                   hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        for (int y = 0; y < screenHeight; y++)
        {
            for (int x = 0; x < screenWidth; x++)
            {
                int index = y * screenWidth + x;

                // Orijinal shader mantýðýný basitleþtiriyoruz
                int fx = (int)((i ^ 4) + (i * 4) * pow((double)((x + y) % 256), 1.0 / 3.0));

                // RGB renkleri doðrudan deðiþtirelim
                int r = (fx + x) % 256;
                int g = (fx + y) % 256;
                int b = (fx) % 256;

                pixels[index] = (r) | (g << 8) | (b << 16);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, screenWidth, screenHeight,
                   hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);

        ReleaseDC(NULL, hdc);
    }

    return 0;
}


DWORD WINAPI shader4(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;

    while(1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        int x, y;

        for(x = 0; x < screenWidth; x++)
        {
            for(y = 0; y < screenHeight; y++)
            {
                int index = y * screenWidth + x;
                RGBQUAD pix = rgbquad[index];

                // Basit renk efekti: kýrmýzý, yeþil, maviyi deðiþtir
                int fx = (int)((i ^ 4) + (i * 4) * sqrt((i*x)&y));

                pix.rgbRed   = (unsigned char)((pix.rgbRed   + fx) % 256);
                pix.rgbGreen = (unsigned char)((pix.rgbGreen + y + i) % 256);
                pix.rgbBlue  = (unsigned char)((pix.rgbBlue  + x + i) % 256);

                rgbquad[index] = pix;
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }

    return 0;
}


DWORD WINAPI shader5(LPVOID lpParam)
{
    srand((unsigned int)time(NULL)); // rastgele baþlat

    while (1) 
    {
        HDC hdc = GetDC(0);

        int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int iconWidth    = GetSystemMetrics(SM_CXICON);
        int iconHeight   = GetSystemMetrics(SM_CYICON);

        int scaleX, scaleY;
        int posX, posY;

        // ERROR icon
        posX = rand() % screenWidth;
        posY = rand() % screenHeight;
        scaleX = (rand() % 5 + 1) * iconWidth;
        scaleY = (rand() % 5 + 1) * iconHeight;
        DrawIconEx(hdc, posX, posY, LoadIcon(0, IDI_ERROR), scaleX, scaleY, 0, NULL, DI_NORMAL);

        // INFORMATION icon
        posX = rand() % screenWidth;
        posY = rand() % screenHeight;
        scaleX = (rand() % 5 + 1) * iconWidth;
        scaleY = (rand() % 5 + 1) * iconHeight;
        DrawIconEx(hdc, posX, posY, LoadIcon(0, IDI_INFORMATION), scaleX, scaleY, 0, NULL, DI_NORMAL);

        // APPLICATION icon
        posX = rand() % screenWidth;
        posY = rand() % screenHeight;
        scaleX = (rand() % 5 + 1) * iconWidth;
        scaleY = (rand() % 5 + 1) * iconHeight;
        DrawIconEx(hdc, posX, posY, LoadIcon(0, IDI_APPLICATION), scaleX, scaleY, 0, NULL, DI_NORMAL);

        // QUESTION icon
        posX = rand() % screenWidth;
        posY = rand() % screenHeight;
        scaleX = (rand() % 5 + 1) * iconWidth;
        scaleY = (rand() % 5 + 1) * iconHeight;
        DrawIconEx(hdc, posX, posY, LoadIcon(0, IDI_QUESTION), scaleX, scaleY, 0, NULL, DI_NORMAL);

        // WARNING icon
        posX = rand() % screenWidth;
        posY = rand() % screenHeight;
        scaleX = (rand() % 5 + 1) * iconWidth;
        scaleY = (rand() % 5 + 1) * iconHeight;
        DrawIconEx(hdc, posX, posY, LoadIcon(0, IDI_WARNING), scaleX, scaleY, 0, NULL, DI_NORMAL);

        ReleaseDC(0, hdc);
        Sleep(1);
    }

    return 0;
}



DWORD WINAPI shader6(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    int x, y;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        for (x = 0; x < w; x++)
        {
            for (y = 0; y < h; y++)
            {
                int index = y * w + x;

                RGBQUAD pix = rgbquad[index];

                // Basit matematiksel renk efekti
                int fx = i * x + y;
                pix.rgbRed   = (unsigned char)((pix.rgbRed   + fx) % 256);
                pix.rgbGreen = (unsigned char)((pix.rgbGreen + fx / 2) % 256);
                pix.rgbBlue  = (unsigned char)((pix.rgbBlue  + fx / 3) % 256);

                rgbquad[index] = pix;
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }

    return 0;
}

DWORD WINAPI shader7(LPVOID lpParam)
{
    srand((unsigned int)time(NULL)); // Rastgele baþlat

    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);

    while (1)
    {
        int y = rand() % sh;
        int h = sh - rand() % sh - 1; // min 1 piksel yüksekliði garanti

        // Rastgele renkli fýrça
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 226, rand() % 226, rand() % 226));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

        // BitBlt ile ekran kaydýrma efekti
        BitBlt(hdc, 0, y, sw, h, hdc, rand() % 96 - 56, y, SRCCOPY);

        // PatBlt ile invert efekti
        PatBlt(hdc, 0, y, sw, h, PATINVERT);

        SelectObject(hdc, oldBrush);
        DeleteObject(brush);

        // Ara sýra ekraný yeniden çiz
        if ((rand() % 100 + 1) % 67 == 0)
            InvalidateRect(0, NULL, TRUE);

        Sleep(100);
    }

    ReleaseDC(0, hdc);
    return 0;
}

DWORD WINAPI shader8(LPVOID lpstart)
{
    srand((unsigned int)time(NULL));

    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(0);

    double i, wave;
    int xs, ys;
    int sel;

    while (1)
    {
        sel = rand() % 4 + 1;
        wave = 0.0;
        i = 0.0;

        if (sel == 1)
        {
            xs = 0;
            ys = rand() % y;
            for (; xs < x; xs += 3)
            {
                DrawIcon(hdc, xs, ys + (int)(wave * cos(i)), LoadIcon(0, IDI_ERROR));
                i += 0.05;
                wave += 0.32;
                Sleep(10);
            }
        }
        else if (sel == 2)
        {
            xs = x;
            ys = rand() % y;
            for (; xs > 0; xs -= 3)
            {
                DrawIcon(hdc, xs, ys + (int)(wave * cos(i)), LoadIcon(0, IDI_WARNING));
                i += 0.05;
                wave += 0.32;
                Sleep(10);
            }
        }
        else if (sel == 3)
        {
            xs = rand() % x;
            ys = 0;
            for (; ys < y; ys += 3)
            {
                DrawIcon(hdc, xs + (int)(wave * cos(i)), ys, LoadIcon(0, IDI_INFORMATION));
                i += 0.05;
                wave += 0.32;
                Sleep(10);
            }
        }
        else if (sel == 4)
        {
            xs = rand() % x;
            ys = y;
            for (; ys > 0; ys -= 3)
            {
                DrawIcon(hdc, xs + (int)(wave * cos(i)), ys, LoadIcon(0, IDI_QUESTION));
                i += 0.05;
                wave += 0.32;
                Sleep(10);
            }
        }
    }

    ReleaseDC(0, hdc);
    return 0;
}
DWORD WINAPI shader9(LPVOID lpstart)
{
    srand((unsigned int)time(NULL));

    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(0);
    CURSORINFO cur;

    int xs, ys, sel;

    while (1)
    {
        xs = 0;
        ys = 0;
        sel = rand() % 4 + 1;

        if (sel == 1)
        {
            xs = rand() % x;
            ys = 0;
            for (; ys < y; ys += 2)
            {
                cur.cbSize = sizeof(cur);
                GetCursorInfo(&cur);

                DrawIcon(hdc, xs, ys, cur.hCursor);
                xs += 2;
                if (xs >= x) ys = y;
                Sleep(1);
            }
        }
        else if (sel == 2)
        {
            xs = rand() % x;
            ys = y;
            for (; ys > 0; ys -= 2)
            {
                cur.cbSize = sizeof(cur);
                GetCursorInfo(&cur);

                DrawIcon(hdc, xs, ys, cur.hCursor);
                xs += 2;
                if (xs >= x) ys = 0;
                Sleep(1);
            }
        }
        else if (sel == 3)
        {
            xs = rand() % x;
            ys = 0;
            for (; ys < y; ys += 2)
            {
                cur.cbSize = sizeof(cur);
                GetCursorInfo(&cur);

                DrawIcon(hdc, xs, ys, cur.hCursor);
                xs -= 2;
                if (xs <= 0) ys = y;
                Sleep(1);
            }
        }
        else if (sel == 4)
        {
            xs = rand() % x;
            ys = y;
            for (; ys > 0; ys -= 2)
            {
                cur.cbSize = sizeof(cur);
                GetCursorInfo(&cur);

                DrawIcon(hdc, xs, ys, cur.hCursor);
                xs -= 2;
                if (xs <= 0) ys = 0;
                Sleep(1);
            }
        }
    }

    ReleaseDC(0, hdc);
    return 0;
}

DWORD WINAPI shader10(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp;

    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    int x, y, index;
    float fx;

    while (1)
    {
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        for (x = 0; x < w; x++)
        {
            for (y = 0; y < h; y++)
            {
                index = y * w + x;
                fx = (x + i) * (y + i);

                rgbquad[index].rgbRed   = (unsigned char)((rgbquad[index].rgbRed   + (int)fx) % 256);
                rgbquad[index].rgbGreen = (unsigned char)((rgbquad[index].rgbGreen + (int)fx) % 256);
                rgbquad[index].rgbBlue  = (unsigned char)((rgbquad[index].rgbBlue  + (int)fx) % 256);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        hdc = GetDC(NULL); // sonraki frame için DC tekrar al
    }

    return 0;
}

DWORD WINAPI shader11(LPVOID lpParam)
{
    srand((unsigned int)time(NULL));

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    int signX = 1;
    int signY = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;

    LPCSTR lpText = "tetrahubhubonawindowsTxp.exe";
    int textLen = (int)strlen(lpText);

    HDC hdc;
    HFONT font;
    HFONT oldFont;
    int top_x, top_y;
    int colR, colG, colB;

    while (1)
    {
        hdc = GetDC(0);

        x += incrementor * signX;
        y += incrementor * signY;

        top_x = x;
        top_y = y;

        SetBkMode(hdc, TRANSPARENT);

        colR = rand() % 256;
        colG = rand() % 256;
        colB = rand() % 256;
        SetTextColor(hdc, RGB(colR, colG, colB));

        // CreateFontA: height, width, escapement, orientation, weight, italic, underline, strikeout,
        // charset, outprecision, clipprecision, quality, pitchfamily, faceName
        font = CreateFontA(
            43,    // nHeight
            32,    // nWidth
            0,     // nEscapement
            0,     // nOrientation
            FW_NORMAL, // fnWeight
            0,     // fdwItalic
            0,     // fdwUnderline
            0,     // fdwStrikeOut
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            "Sen Nesin Be kardeþim"
        );

        oldFont = (HFONT)SelectObject(hdc, font);

        TextOutA(hdc, top_x, top_y, lpText, textLen);

        // restore and cleanup
        SelectObject(hdc, oldFont);
        DeleteObject(font);

        ReleaseDC(0, hdc);

        // boundary checks using cached screen size
        if (y >= h) signY = -1;
        if (x >= w) signX = -1;
        if (y <= 0) signY = 1;
        if (x <= 0) signX = 1;

        Sleep(4);
    }

    return 0;
}

DWORD WINAPI shader12(LPVOID lpvd)
{
    srand((unsigned int)time(NULL));

    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    HBITMAP bmp;
    BLENDFUNCTION blur;

    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, 0, NULL, 0);
    SelectObject(hdcCopy, bmp);

    blur.BlendOp = AC_SRC_OVER;
    blur.BlendFlags = 0;
    blur.AlphaFormat = 0;
    blur.SourceConstantAlpha = 10;

    int x;

    while (1)
    {
        hdc = GetDC(NULL);

        x = rand() % w;
        BitBlt(hdcCopy, x, 1, 10, h, hdc, x, 0, SRCCOPY);
        AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);

        ReleaseDC(NULL, hdc);
    }

    return 0;
}

DWORD WINAPI shader13(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp;

    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    int x, y, index;
    int fx;

    while (1)
    {
        hdc = GetDC(NULL);

        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        for (x = 0; x < w; x++)
        {
            for (y = 0; y < h; y++)
            {
                index = y * w + x;

                fx = x ^ y;

                rgbquad[index].rgbRed   = (unsigned char)((rgbquad[index].rgbRed   + fx) % 256);
                rgbquad[index].rgbGreen = (unsigned char)((rgbquad[index].rgbGreen + fx) % 256);
                rgbquad[index].rgbBlue  = (unsigned char)((rgbquad[index].rgbBlue  + fx) % 256);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
    }

    return 0;
}

DWORD WINAPI shader14(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp;

    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    int x, y, index, fx;
    double fractalX, fractalY, cx, cy, zx, zy, fczx, fczy;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

        fractalX = 2.5 / w;
        fractalY = 1.90 / h;

        for (x = 0; x < w; x++)
        {
            for (y = 0; y < h; y++)
            {
                index = y * w + x;

                cx = x * fractalX - 2.0;
                cy = y * fractalY - 0.95;

                zx = zy = 0;
                fx = 0;

                while ((zx * zx + zy * zy) < 10 && fx < 50)
                {
                    fczx = zx * zx - zy * zy + cx;
                    fczy = 2 * zx * zy + cy;
                    zx = fczx;
                    zy = fczy;
                    fx++;
                }

                // RGB kanallarýna basit efekt
                rgbquad[index].rgbRed   = (unsigned char)((fx * 5) % 256);
                rgbquad[index].rgbGreen = (unsigned char)((fx * 7) % 256);
                rgbquad[index].rgbBlue  = (unsigned char)((fx * 11) % 256);
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
    }

    return 0;
}
DWORD WINAPI shader15(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp;

    ZeroMemory(&bmpi, sizeof(BITMAPINFO));
    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    int x, y, index;
    int fx;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        for (x = 0; x < screenWidth; x++)
        {
            for (y = 0; y < screenHeight; y++)
            {
                index = y * screenWidth + x;
                fx = rand() % 360;

                rgbquad[index].rgbRed   = (unsigned char)((fx * 7) % 256);
                rgbquad[index].rgbGreen = (unsigned char)((fx * 5) % 256);
                rgbquad[index].rgbBlue  = (unsigned char)((fx * 3) % 256);
            }
        }

        i++;

        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
    }

    return 0;
}

DWORD WINAPI shader16(LPVOID lpParam)
{
    HDC hdcScreen = GetDC(0);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmi;
    PRGBQUAD rgbScreen = NULL;

    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;

    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, 0);
    SelectObject(hdcMem, hbmTemp);

    int i, x, y, cx, cy, zx, zy;
    int di, fx;

    while (1)
    {
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);

        for (i = 0; i < w * h; i++)
        {
            x = i % w;
            y = i / w;

            cx = x - (w / 2);
            cy = y - (h / 2);

            zx = cx * cx;
            zy = cy * cy;

            di = 128 + i;
            fx = di + int(di * sin(sqrt(double(zx + zy)) / 32.0));

            // Basit RGB efekt
            rgbScreen[i].r = (unsigned char)((fx + i) % 255);
            rgbScreen[i].g = (unsigned char)((fx * 10 + i) % 255);
            rgbScreen[i].b = (unsigned char)((fx * 8 + i) % 255);
        }

        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen);
    }

    return 0;
}


DWORD WINAPI shader17(LPVOID lpvd)
{
    HDC hdc = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
    SelectObject(hdcMem, hbm);

    int angle = 0;

    while (1)
    {
        hdc = GetDC(NULL);
        BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        XFORM xForm;
        float rad = angle * 3.14159f / 180.0f;
        float cx = w / 2.0f;
        float cy = h / 2.0f;

        SetGraphicsMode(hdc, GM_ADVANCED);
        xForm.eM11 = cos(rad);
        xForm.eM12 = sin(rad);
        xForm.eM21 = -sin(rad);
        xForm.eM22 = cos(rad);
        xForm.eDx = cx - (cx * xForm.eM11) - (cy * xForm.eM21);
        xForm.eDy = cy - (cx * xForm.eM12) - (cy * xForm.eM22);
        SetWorldTransform(hdc, &xForm);

        BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);

        // Yazý ayarlarý
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));

        HFONT font = CreateFontA(120, 60, 0, 0, FW_BLACK, FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH, "Impact");

        SelectObject(hdc, font);

        TextOutA(hdc, (w / 2) - 300, (h / 2) - 50, "WHAT ARE YOU DOÝNG!!!!!!", 13);

        DeleteObject(font);
        ModifyWorldTransform(hdc, NULL, MWT_IDENTITY);

        angle += 5;
        if (angle >= 360) angle = 0;

        Sleep(10);
        ReleaseDC(NULL, hdc);
    }

    return 0;
}

DWORD WINAPI shader18(LPVOID lpvd)
{
    using namespace Gdiplus; // ?? GDI+ isim alanýný kullan

    // GDI+ baþlat
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    HDC hdc = GetDC(0);

    // PNG yükle
    Image* img = new Image(L"canacin.png");
    if (img->GetLastStatus() != Ok)
    {
        MessageBoxA(0, "canacin.png not found!", "Error", MB_ICONERROR);
        GdiplusShutdown(gdiplusToken);
        return 0;
    }

    int imgW = img->GetWidth();
    int imgH = img->GetHeight();

    // Baþlangýç konum ve hýz
    int x = rand() % (sw - imgW);
    int y = rand() % (sh - imgH);
    int dx = 7;
    int dy = 5;

    HFONT font = CreateFontA(
        100, 0, 0, 0, FW_BOLD,
        FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        VARIABLE_PITCH, "Impact");

    for (;;)
    {
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbm = CreateCompatibleBitmap(hdc, sw, sh);
        SelectObject(hdcMem, hbm);
        BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);

        // PNG çiz
        Graphics g(hdcMem);
        g.SetCompositingMode(CompositingModeSourceOver);
        g.DrawImage(img, x, y, imgW, imgH);

        // Yazý
        SetBkMode(hdcMem, TRANSPARENT);
        SetTextColor(hdcMem, RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdcMem, font);
        TextOutA(hdcMem, sw / 2 - 300, sh / 2 - 50, "THERE IS NO RELIEF FOR YOU TONIGHT... YOU WILL DIE!!!!!", 14);

        BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);

        DeleteObject(hbm);
        DeleteDC(hdcMem);

        // Duvar çarpmalarý
        x += dx;
        y += dy;
        if (x <= 0 || x + imgW >= sw) dx = -dx;
        if (y <= 0 || y + imgH >= sh) dy = -dy;

        Sleep(20);
    }

    delete img;
    GdiplusShutdown(gdiplusToken);
    ReleaseDC(0, hdc);
    return 0;
}

DWORD WINAPI shader19(LPVOID lpParam)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    Gdiplus::Graphics gfx(hdc);

    double zoom = 1.0;
    double moveX = -0.5, moveY = 0.0;
    int maxIter = 120;

    while (1)
    {
        gfx.Clear(Gdiplus::Color(0, 0, 0)); // arka plan siyah

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                double pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
                double pi = (y - h / 2) / (0.5 * zoom * h) + moveY;

                double newRe = pr, newIm = pi, oldRe, oldIm;
                int i;
                for (i = 0; i < maxIter; i++)
                {
                    oldRe = newRe;
                    oldIm = newIm;
                    double denominator = oldRe * oldRe + oldIm * oldIm;
                    if (denominator == 0.0) denominator = 1.0; // division by zero korumasý
                    newRe = (oldRe * oldRe - oldIm * oldIm) / denominator + pr;
                    newIm = (2 * oldRe * oldIm) / denominator + pi;
                    if ((newRe * newRe + newIm * newIm) > 4) break;
                }

                int color = (i % 256);
                gfx.FillRectangle(
                    new Gdiplus::SolidBrush(Gdiplus::Color::MakeARGB(255, color, color * 2 % 255, 255 - color)),
                    x, y, 1, 1);
            }
        }

        zoom *= 1.01; // her frame’de yakýnlaþ
        moveX += 0.002; // yavaþ kayma efekti
        Sleep(10);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    ReleaseDC(NULL, hdc);
    return 0;
}







DWORD WINAPI shader20(LPVOID lpParam)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HDC hdc = GetDC(NULL);
    Gdiplus::Graphics gfx(hdc);

    double zoom = 1.0;
    double moveX = -0.5, moveY = 0.0;
    int maxIter = 120;

    while (1)
    {
        gfx.Clear(Gdiplus::Color(0, 0, 0)); // arka plan siyah

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                double pr = 1.5 * (x - w / 2) / (0.9 * zoom * w) + moveX;
                double pi = (y - h / 2) / (0.9 * zoom * h) + moveY;

                double newRe = pr, newIm = pi, oldRe, oldIm;
                int i;
                for (i = 0; i < maxIter; i++)
                {
                    oldRe = newRe;
                    oldIm = newIm;
                    double denominator = oldRe * oldRe + oldIm * oldIm;
                    if (denominator == 0.0) denominator = 1.0; // division by zero korumasý
                    newRe = (oldRe * oldRe - oldIm * oldIm) / denominator + pr;
                    newIm = (2 * oldRe * oldIm) / denominator + pi;
                    if ((newRe * newRe + newIm * newIm) > 4) break;
                }

                int color = (i % 256);
                gfx.FillRectangle(
                    new Gdiplus::SolidBrush(Gdiplus::Color::MakeARGB(255, color, color * 2 % 255, 255 - color)),
                    x, y, 1, 1);
            }
        }

        zoom *= 1.01; // her frame’de yakýnlaþ
        moveX += 0.002; // yavaþ kayma efekti
        Sleep(10);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    ReleaseDC(NULL, hdc);
    return 0;
}


DWORD WINAPI shader21(LPVOID lpvd) 
{
    //Credits to ArTicZera and Rekto
    HDC hdc = GetDC(NULL);
    HDC dcCopy = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi;
    memset(&bmpi, 0, sizeof(BITMAPINFO));
    BLENDFUNCTION blur;
    HBITMAP bmp;

    bmpi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, 0, 0, 0);
    SelectObject(dcCopy, bmp);

    blur.BlendOp = AC_SRC_OVER;
    blur.BlendFlags = 0;
    blur.AlphaFormat = 0;
    blur.SourceConstantAlpha = 10;

    while (1) 
    {
        hdc = GetDC(NULL);

        // Ekraný kopyala, kenarlardan 10 px boþluk býrak
        StretchBlt(dcCopy, 10, 10, w - 20, h - 20, hdc, 0, 0, w, h, SRCCOPY);

        // Alpha blend ile ekrana yansýt
        AlphaBlend(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);

        ReleaseDC(0, hdc);
        Sleep(4); // Daha stabil ve hýzlý
    }

    return 0x00;
}


struct HSL {
    double h; // 0..1
    double s; // 0..1
    double l; // 0..1
};

HSL rgb2hsl(RGBQUAD rgb) {
    double r = rgb.rgbRed / 255.0;
    double g = rgb.rgbGreen / 255.0;
    double b = rgb.rgbBlue / 255.0;

    double max = r; if(g > max) max = g; if(b > max) max = b;
    double min = r; if(g < min) min = g; if(b < min) min = b;

    HSL hsl;
    hsl.l = (max + min) / 2.0;

    if(max == min) {
        hsl.h = 0; hsl.s = 0;
    } else {
        double d = max - min;
        hsl.s = (hsl.l > 0.5) ? d / (2.0 - max - min) : d / (max + min);

        if(max == r) hsl.h = (g - b) / d + (g < b ? 6 : 0);
        else if(max == g) hsl.h = (b - r) / d + 2;
        else hsl.h = (r - g) / d + 4;

        hsl.h /= 6.0;
    }
    return hsl;
}

RGBQUAD hsl2rgb(HSL hsl) {
    double r, g, b;
    if(hsl.s == 0) {
        r = g = b = hsl.l;
    } else {
        double q = (hsl.l < 0.5) ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
        double p = 2 * hsl.l - q;
        double t[3] = {hsl.h + 1.0/3, hsl.h, hsl.h - 1.0/3};
        double c[3];
        for(int i = 0; i < 3; i++) {
            if(t[i] < 0) t[i] += 1;
            if(t[i] > 1) t[i] -= 1;
            if(t[i] < 1.0/6) c[i] = p + (q - p) * 6 * t[i];
            else if(t[i] < 0.5) c[i] = q;
            else if(t[i] < 2.0/3) c[i] = p + (q - p) * (2.0/3 - t[i]) * 6;
            else c[i] = p;
        }
        r = c[0]; g = c[1]; b = c[2];
    }
    RGBQUAD rgb;
    rgb.rgbRed = (BYTE)(r * 255);
    rgb.rgbGreen = (BYTE)(g * 255);
    rgb.rgbBlue = (BYTE)(b * 255);
    rgb.rgbReserved = 0;
    return rgb;
}

DWORD WINAPI shader22(LPVOID lpvd) {
    HDC hdc = GetDC(NULL);
    HDC hdcCopy = CreateCompatibleDC(hdc);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmpi = {0};
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = screenWidth;
    bmpi.bmiHeader.biHeight = screenHeight;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;

    RGBQUAD* rgbquad = NULL;
    HBITMAP bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    int i = 0;
    while(1) {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

        for(int x = 0; x < screenWidth; x++) {
            for(int y = 0; y < screenHeight; y++) {
                int index = y * screenWidth + x;
                int fx = (int)((i ^ 4) + (i * 4) * sqrt(x * i & i * y | x * i * y * i));
                RGBQUAD temp = rgbquad[index];

                HSL hslcolor = rgb2hsl(temp);
                hslcolor.h = fmod(fx / 400.0 + y / (double)screenHeight * 0.2, 1.0);
                rgbquad[index] = hsl2rgb(hslcolor);
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }

    return 0;
}

int randy() {
    return rand();
}

DWORD WINAPI shader23(LPVOID lpParam) {
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, 4 * h * w, data);

        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 10)
            byte = randy() % 0xff;

        for (int i = 0; i < w * h; ++i) {
            if (!(i % h) && !(randy() % 110))
                v = randy() % 24;
            *((BYTE*)data + 4 * i + v) -= 5;
        }

        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);

        DeleteObject(hbm);
        DeleteDC(hdcdc);
        ReleaseDC(NULL, desk);
    }

    VirtualFree(data, 0, MEM_RELEASE);
    return 0;
}

DWORD WINAPI shader24(LPVOID lpParam) {
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, w * h * 4, data);

        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 60000)
            byte = rand() % 0xff;

        for (int i = 0; i < w * h; i++) {
            int x = i % w;
            int y = i / w;  // düzeltilmiþ
            if (i % h == 0 && rand() % 110)
                v = rand() % 32;
            ((BYTE*)data)[4 * i + v] = x ^ y; // düzeltilmiþ
        }

        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);

        DeleteObject(hbm);
        DeleteDC(hdcdc);
        ReleaseDC(NULL, desk);
    }

    VirtualFree(data, 0, MEM_RELEASE);
    return 0;
}

DWORD WINAPI shader25(LPVOID lpParam) {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int signX = 1;
    int signY = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;

    HDC hdc = GetDC(NULL);

    while (1) {
        x += incrementor * signX;
        y += incrementor * signY;

        TRIVERTEX vertex[3];
        vertex[0].x = x + 100; vertex[0].y = y;         vertex[0].Red = 0xb000; vertex[0].Green = 0x9000; vertex[0].Blue = 0x0000; vertex[0].Alpha = 0x0000;
        vertex[1].x = x;       vertex[1].y = y + 100;   vertex[1].Red = 0x0000; vertex[1].Green = 0x8000; vertex[1].Blue = 0xff00; vertex[1].Alpha = 0x0000;
        vertex[2].x = x + 200; vertex[2].y = y + 100;   vertex[2].Red = 0xff00; vertex[2].Green = 0x8000; vertex[2].Blue = 0x0000; vertex[2].Alpha = 0x0000;

        GRADIENT_TRIANGLE gTriangle;
        gTriangle.Vertex1 = 0;
        gTriangle.Vertex2 = 1;
        gTriangle.Vertex3 = 2;

        GradientFill(hdc, vertex, 3, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);

        // Ekran sýnýrlarý kontrolü
        if (y + 100 > screenHeight) signY = -1;
        if (x + 200 > screenWidth)  signX = -1;
        if (y < 0) signY = 1;
        if (x < 0) signX = 1;

        Sleep(1);
    }

    ReleaseDC(NULL, hdc);
    return 0;
}


DWORD WINAPI shader26(LPVOID lpParam) {
    HWND wnd = GetDesktopWindow();
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);

    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = sw;
    bmi.bmiHeader.biHeight = sh;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    RGBTRIPLE* rgbtriple;

    int colorModifier = 0;

    for (;;) {
        HDC desk = GetDC(NULL);
        HDC deskMem = CreateCompatibleDC(desk);
        HBITMAP scr = CreateDIBSection(desk, &bmi, DIB_RGB_COLORS, (void**)&rgbtriple, NULL, 0);
        SelectObject(deskMem, scr);
        BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);

        for (int i = 0; i < sw * sh; i++) {
            int x = i % sw;
            int y = i / sw;

            rgbtriple[i].rgbtRed = (BYTE)((x & y) + colorModifier);
            rgbtriple[i].rgbtGreen = (BYTE)((x ^ y) - colorModifier);
            rgbtriple[i].rgbtBlue = (BYTE)((x ^ y) + colorModifier);

            colorModifier = (colorModifier + 1) % 40;
        }

        BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, SRCCOPY);

        ReleaseDC(NULL, desk);
        DeleteDC(deskMem);
        DeleteObject(scr);
    }

    return 0;
}

DWORD WINAPI shader27(LPVOID lpParam) 
{
    HWND wnd = GetDesktopWindow();
    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);
    double angle = 0.0;

    while (1) 
    {
        HDC hdc = GetDC(NULL);
        for (int i = 0; i < sw + sh; i++) 
        {
            int a = (int)(sin(angle) * 20);
            int y = i;

            // Saf þekilde BitBlt (kendisiyle yapýyor ama küçük test için kabul edilebilir)
            BitBlt(hdc, 0, y, sw, 1, hdc, a, y, SRCCOPY);
            BitBlt(hdc, i, 0, 1, sh, hdc, i, a, SRCCOPY);

            angle += M_PI / 40;
        }
        ReleaseDC(NULL, hdc);
        Sleep(1);
    }

    return 0;
}

DWORD WINAPI shader28(LPVOID lpParam)
{
    HDC hdc;
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        hdc = GetDC(0);
        BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCPAINT);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI shader29(LPVOID lpParam)
{
    // Rastgele sayý üretimi için seed
    srand((unsigned int)time(NULL));

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    while (1)
    {
        HDC hdc = GetDC(NULL);

        // BitBlt ile küçük kaymalar
        BitBlt(
            hdc,
            rand() % 2,       // x hedef
            rand() % 2,       // y hedef
            w,                // geniþlik
            h,                // yükseklik
            hdc,
            rand() % 2,       // x kaynak
            rand() % 2,       // y kaynak
            SRCAND             // raster operation
        );

        ReleaseDC(NULL, hdc);
        Sleep(10);
    }

    return 0;
}

DWORD WINAPI shader30(LPVOID lpParam)
{
    // Rastgele sayý üretimi için seed
    srand((unsigned int)time(NULL));

    while (1)
    {
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);

        HDC hdc = GetDC(NULL);

        // Kýrmýzý kalýn çizgi
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        // Kýrmýzý dolgulu fýrça
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        // Rastgele üçgen vertices
        POINT vertices[3];
        for (int i = 0; i < 3; i++)
        {
            vertices[i].x = rand() % w;
            vertices[i].y = rand() % h;
        }

        Polygon(hdc, vertices, 3);

        // Eski objeleri geri yükle ve temizle
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);

        SelectObject(hdc, hOldPen);
        DeleteObject(hPen);

        ReleaseDC(NULL, hdc);

        Sleep(1); // CPU yükünü hafifletmek için küçük bekleme
    }

    return 0;
}

DWORD WINAPI shader31(LPVOID lpParam) {
    HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double angle = 0;
    while (1) {
        desk = GetDC(0);
        for (float i = 0; i < sw + sh; i += 0.99f) {
            int a = sin(angle) * 20;
            BitBlt(desk, 0, i, sw, 1, desk, a, i, SRCCOPY);
            angle += 3.14159265358979323846 / 40;
        }
        ReleaseDC(wnd, desk);
    }
}

DWORD WINAPI shader32(LPVOID lpParam) {
    int y = GetSystemMetrics(SM_CYSCREEN);
    int x = GetSystemMetrics(SM_CXSCREEN);
    int yfull = GetSystemMetrics(SM_CYFULLSCREEN);
    int xfull = GetSystemMetrics(SM_CXFULLSCREEN);
    int rainbow = x - rand() % x - (x / 150 - 112) % 149;
    int inc = x / 100;
    while (1) {
        HDC hdc = GetDC(0);
        for (int yp = 0; yp < y; ++yp) {
            for (int xp = 0; xp < x; ++xp) {
                int xa = inc * xp;
                SetPixel(hdc, xp, yp, RGB(xa, xa, xa));
                SetPixel(hdc, yp, rainbow, RGB(yfull, xa, xfull));
                SetPixel(hdc, rainbow, rainbow, RGB(rainbow, rainbow, rainbow));
                SetPixel(hdc, rainbow, yp, RGB(xfull, yfull, xfull));
            }
        }
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI shader33(LPVOID lpParam) {
    HDC desk = GetDC(0);
    HWND wnd = GetDesktopWindow();
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);

    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = sw;
    bmi.bmiHeader.biHeight = sh;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24; // 24-bit RGB
    bmi.bmiHeader.biCompression = BI_RGB;

    RGBTRIPLE* rgbtriple = NULL;
    while (1) {
        desk = GetDC(0);
        HDC deskMem = CreateCompatibleDC(desk);
        HBITMAP scr = CreateDIBSection(desk, &bmi, DIB_RGB_COLORS, (void**)&rgbtriple, 0, 0);
        SelectObject(deskMem, scr);
        BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);

        for (int i = 0; i < sw * sh; i++) {
            int x = i % sw, y = i / sw; // burada sh yerine sw
            rgbtriple[i].rgbtRed += GetRValue(x ^ y);
            rgbtriple[i].rgbtGreen += GetGValue(x ^ y);
            rgbtriple[i].rgbtBlue += GetBValue(x ^ y);
        }

        BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, SRCCOPY);
        ReleaseDC(wnd, desk);
        DeleteDC(desk);
        DeleteDC(deskMem);
        DeleteObject(scr);
    }

    return 0;
}

DWORD WINAPI shader34(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), rx = rand() % w;
        BitBlt(hdc, rx, 10, 100, h, hdc, rx, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
    }
}

DWORD WINAPI shader35(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, SRCCOPY);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI shader36(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI shader37(LPVOID lpParam) {
    RECT rect; GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
    while (1) {
        const int size = 1000;
        int x = rand()%(w+size)-size/2, y = rand()%(h+size)-size/2;
        for (int i = 0; i < size; i += 100) {
            HDC hdc = GetDC(0);
            HRGN hrgn = CreateEllipticRgn(x-i/2, y-i/2, x-i/2+i, y-i/2+i);
            SelectClipRgn(hdc, hrgn);
            BitBlt(hdc, x-i/2, y-i/2, i, i, hdc, x-i/2, y-i/2, NOTSRCCOPY);
            DeleteObject(hrgn);
            ReleaseDC(0, hdc);
            Sleep(25);
        }
    }
}

DWORD WINAPI shader38(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(0);
        int x = GetSystemMetrics(0), y = GetSystemMetrics(1);
        StretchBlt(hdc, -30, -11, x + 80, y + 20, hdc, 0, 0, x, y, SRCCOPY);
        StretchBlt(hdc, 10, 10, x - 20, y - 20, hdc, 0, 0, x, y, SRCCOPY);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI shader39(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 666, rand() % 666, w, h, hdc, rand() % 666, rand() % 666, NOTSRCERASE);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI shader40(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1), x;
    while (1) {
        HDC hdc = GetDC(0);
        x = rand() % w;
        BitBlt(hdc, x, 30, 60, h, hdc, x, 0, SRCCOPY);
        Sleep(2);
        ReleaseDC(0, hdc);
    }
}

// ===== Bytebeat Sesleri =====

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t^(t*(t>>1)*(t&t>>12)>>22)+(t*t>>16));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,11000,11000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[11000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t<<5|-t>>5);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,11000,11000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[11000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t*(53+4*((t>>14)&1))>>((t*(49+((t>>10)&3)*2+((t>>14)&1)*2)&5)+96*(1-((t>>9)&1))+70*(4/((t&4095)+1))))/2);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,60000,60000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[60000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t>>12)*(double)(sin((t>>3)*(t >> 14 & 7))));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,8000,8000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[8000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t>>8&t>>5)|t*(t>>6&t>>11));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t>>2&170)*((t>>11&1?5:1)+(t>>12&3)+(t>>13&7))*29);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound7() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,11000,11000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[11000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*5*(3+(3&t))>>(3&t>>9));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound8() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t*(0x63338172781)>>((t>>12)%32)>>6&95)*(10000/((t&12287)+1)));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound9() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t*(0x63338172781)>>((t>>12)%32)>>6&95)*(1000000/((t&12287)+1)));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound10() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t & t >> 6) + (t | t >> 8) + (t | t >> 7) + (t | t >> 9)*(t>>8&3));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound11() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((t^30-t^11)*t)>>6);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound12() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,22000,22000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[22000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t>>5&t>>7)+t*(t>>11&t>>9)|t>>(t>>11&7));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound13() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44100,44100,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t&t>>12|t&t>>6));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound14() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44100,44100,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t>>(t&t>>12)-t/19&128);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound15() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,11000,11000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[11000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t>>10&t>>9^t)-t*(t&t>>11));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound16() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,8000,8000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[11000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t>>(t&7)|t<<(t&42)|t*(t>>10^t));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound17() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,16000,16000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[16000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(20*(t+1>>0)*(t+1>>0)*(t>>11)/7);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound18() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,8000,8000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[8000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*t>>5|t>>5|t>>4|t*4);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound19() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((49+(t>>12&7))*t+(48+((t>>12)&1?8:2))*t)>>6);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}



VOID WINAPI sound20() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((( ( (t>>8)%64 * (t>>6) ) + (t >> (t * (t>>9 ^ 18)) ) ) & 255));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound21() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,8000,8000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[8000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((t*((t&4096?t%65536<59392?7:t>>6:16)+(1&t>>14))>>(3&-t>>(t&2048?2:10))|t>>(t&16384?t&4096?4:3:2))*t)>>6);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound22() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(11 * ((t >> 9) | t | (t >> (t >> 18)))*(t>>11));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}



VOID WINAPI sound23() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((-t & 4095) * (25 & t * (t & t >> 19))) + (127& t * (255 & t >> 6 & t >> 4) >> (3 & t >> 12)) - 1);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound24() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,11000,11000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[11000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(2*t*(t>>9|(t)<<(4)));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound25() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t>>10^t));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound26() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,22000,22000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[22000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t*(42&t>>10)^t)+(t*(t>>12)));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound27() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((t*(t&t>>9)>>11&64)+(t<<3*(t&t>>11)>>5));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound28() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,11000,11000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[11000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t>>t)|t>>5);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound29() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t&t>>7|t>>12));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound30() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((t>>7&t>>5)*t)>>4|t>>5);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound31() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}


VOID WINAPI sound32() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((t>>7&t>>5)*t)>>4|t>>5);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound33() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((((t*((t>>14^(t>>11)-1^1)%13)&255)/2 + ((t>>3|t<<(t>>12&2)) + (t>>4|t*(t^t+t/900)) & 255)/2)*(2+(t>>16)))));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound34() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(((t & t+t/25)-t));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}
VOID WINAPI sound35() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(-(t&t>>8)^t);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound36() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)((((t<<5)|t&t>>7)*t)>>14);
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound37() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,22050,22050,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[22050*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*t>>16|t*(t^t>>10));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound38() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*(t));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound39() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(t*((99)>>6|t/12|9));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}

VOID WINAPI sound40() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM,1,44000,44000,1,8,0 };
    waveOutOpen(&hWaveOut,WAVE_MAPPER,&wfx,0,0,CALLBACK_NULL);
    char buffer[44000*30] = {};
    for (DWORD t=0;t<sizeof(buffer);++t)
        buffer[t]=(char)(20*(t&t/1000|t&t>>12));
    WAVEHDR header={buffer,sizeof(buffer)};
    waveOutPrepareHeader(hWaveOut,&header,sizeof(header));
    waveOutWrite(hWaveOut,&header,sizeof(header));
}
// ===== Main =====
int main () {

    
HANDLE th1 = CreateThread(0, 0, shader1, 0, 0, 0);
sound1(); Sleep(30000); TerminateThread(th1, 0);

HANDLE th2 = CreateThread(0, 0, shader2, 0, 0, 0);
sound2(); Sleep(30000); TerminateThread(th2, 0);

HANDLE th3 = CreateThread(0, 0, shader3, 0, 0, 0);
sound3(); Sleep(30000); TerminateThread(th3, 0);

HANDLE th4 = CreateThread(0, 0, shader4, 0, 0, 0);
sound4(); Sleep(30000); TerminateThread(th4, 0);

HANDLE th5 = CreateThread(0, 0, shader5, 0, 0, 0);
sound5(); Sleep(30000); TerminateThread(th5, 0);

HANDLE th6 = CreateThread(0, 0, shader6, 0, 0, 0);
sound6(); Sleep(30000); TerminateThread(th6, 0);

HANDLE th7 = CreateThread(0, 0, shader7, 0, 0, 0);
sound7(); Sleep(30000); TerminateThread(th7, 0);

HANDLE th8 = CreateThread(0, 0, shader8, 0, 0, 0);
sound8(); Sleep(30000); TerminateThread(th8, 0);

HANDLE th9 = CreateThread(0, 0, shader9, 0, 0, 0);
sound9(); Sleep(30000); TerminateThread(th9, 0);

HANDLE th10 = CreateThread(0, 0, shader10, 0, 0, 0);
sound10(); Sleep(30000); TerminateThread(th10, 0);

HANDLE th11 = CreateThread(0, 0, shader11, 0, 0, 0);
sound11(); Sleep(30000); TerminateThread(th11, 0);

HANDLE th12 = CreateThread(0, 0, shader12, 0, 0, 0);
sound12(); Sleep(30000); TerminateThread(th12, 0);

HANDLE th13 = CreateThread(0, 0, shader13, 0, 0, 0);
sound13(); Sleep(30000); TerminateThread(th13, 0);

HANDLE th14 = CreateThread(0, 0, shader14, 0, 0, 0);
sound14(); Sleep(30000); TerminateThread(th14, 0);


HANDLE th15 = CreateThread(0, 0, shader15, 0, 0, 0);
sound15(); Sleep(30000); TerminateThread(th15, 0);


HANDLE th16 = CreateThread(0, 0, shader16, 0, 0, 0);
sound16(); Sleep(30000); TerminateThread(th16, 0);



HANDLE th17 = CreateThread(0, 0, shader17, 0, 0, 0);
sound17(); Sleep(30000); TerminateThread(th17, 0);


HANDLE th18 = CreateThread(0, 0, shader18, 0, 0, 0);
sound18(); Sleep(30000); TerminateThread(th18, 0);








HANDLE th19 = CreateThread(0, 0, shader19, 0, 0, 0);
sound19(); Sleep(30000); TerminateThread(th19, 0);




HANDLE th20 = CreateThread(0, 0, shader20, 0, 0, 0);
sound20(); Sleep(30000); TerminateThread(th20, 0);





HANDLE th21 = CreateThread(0, 0, shader21, 0, 0, 0);
sound21(); Sleep(30000); TerminateThread(th21, 0);



HANDLE th22 = CreateThread(0, 0, shader22, 0, 0, 0);
sound22(); Sleep(30000); TerminateThread(th22, 0);



HANDLE th23 = CreateThread(0, 0, shader23, 0, 0, 0);
sound23(); Sleep(30000); TerminateThread(th23, 0);


HANDLE th24 = CreateThread(0, 0, shader24, 0, 0, 0);
sound24(); Sleep(30000); TerminateThread(th24, 0);


HANDLE th25 = CreateThread(0, 0, shader25, 0, 0, 0);
sound25(); Sleep(30000); TerminateThread(th25, 0);



HANDLE th26 = CreateThread(0, 0, shader26, 0, 0, 0);
sound26(); Sleep(30000); TerminateThread(th26, 0);





HANDLE th27 = CreateThread(0, 0, shader27, 0, 0, 0);
sound27(); Sleep(30000); TerminateThread(th27, 0);



HANDLE th28 = CreateThread(0, 0, shader28, 0, 0, 0);
sound28(); Sleep(30000); TerminateThread(th28, 0);

HANDLE th29 = CreateThread(0, 0, shader29, 0, 0, 0);
sound29(); Sleep(30000); TerminateThread(th29, 0);

HANDLE th30 = CreateThread(0, 0, shader30, 0, 0, 0);
sound30(); Sleep(30000); TerminateThread(th30, 0);

   HANDLE th31 = CreateThread(0, 0, shader31, 0, 0, 0);
    sound31(); Sleep(30000); TerminateThread(th31, 0);

    HANDLE th32 = CreateThread(0, 0, shader32, 0, 0, 0);
    sound32(); Sleep(30000); TerminateThread(th32, 0);

    HANDLE th33 = CreateThread(0, 0, shader33, 0, 0, 0);
    sound33(); Sleep(30000); TerminateThread(th33, 0);

    HANDLE th34 = CreateThread(0, 0, shader34, 0, 0, 0);
    sound34(); Sleep(30000); TerminateThread(th34, 0);

    HANDLE th35 = CreateThread(0, 0, shader35, 0, 0, 0);
    sound35(); Sleep(30000); TerminateThread(th35, 0);

    HANDLE th36 = CreateThread(0, 0, shader36, 0, 0, 0);
    sound36(); Sleep(30000); TerminateThread(th36, 0);

    HANDLE th37 = CreateThread(0, 0, shader37, 0, 0, 0);
    sound37(); Sleep(30000); TerminateThread(th37, 0);

    HANDLE th38 = CreateThread(0, 0, shader38, 0, 0, 0);
    sound38(); Sleep(30000); TerminateThread(th38, 0);

    HANDLE th39 = CreateThread(0, 0, shader39, 0, 0, 0);
    sound39(); Sleep(30000); TerminateThread(th39, 0);

    HANDLE th40 = CreateThread(0, 0, shader40, 0, 0, 0);
    sound40(); Sleep(30000); TerminateThread(th40, 0);

   return 0; 
}



