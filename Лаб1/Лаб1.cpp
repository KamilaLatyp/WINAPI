﻿// Лаб1.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Лаб1.h"
#include <Windows.h>
#include <tchar.h>

extern bool right = false;
extern bool left = false;
LRESULT APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This, // Дескриптор текущего приложения
	HINSTANCE Prev, // В современных системах всегда 0
	LPTSTR cmd, // Командная строка
	int mode) // Режим отображения окна
{
	HWND hWnd; // Дескриптор главного окна программы
	MSG msg; // Структура для хранения сообщения
	WNDCLASS wc; // Класс окна
	// Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; // Имя класса окна
	wc.lpfnWndProc = WndProc; // Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Стандартный курсор
	wc.lpszMenuName = NULL; // Нет меню
	wc.cbClsExtra = 0; // Нет дополнительных данных класса
	wc.cbWndExtra = 0; // Нет дополнительных данных окна
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 12); // Заполнение окна белым цветом

	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна
	hWnd = CreateWindow(WinName, // Имя класса окна
		_T("ИУ5-43Б Латыпова К.Н. ЛР1"), // Заголовок окна
		WS_OVERLAPPEDWINDOW, // Стиль окна
		CW_USEDEFAULT, // x
		CW_USEDEFAULT, // y Размеры окна
		CW_USEDEFAULT, // width
		CW_USEDEFAULT, // Height
		HWND_DESKTOP, // Дескриптор родительского окна
		NULL, // Нет меню
		This, // Дескриптор приложения
		NULL); // Дополнительной информации нет

	ShowWindow(hWnd, mode); // Показать окно

	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //создаем контекст 
	HBRUSH hBrush; //экземпляр структуры графического вывода
	PAINTSTRUCT ps;
	hdc = GetDC(hWnd);
	RECT rectPlace;
	GetClientRect(hWnd, &rectPlace);
	switch (message){
	
	case WM_PAINT:
	{

		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		EndPaint(hWnd, &ps);
		if (left) {
			InvalidateRect(hWnd, NULL, FALSE);
			hdc = BeginPaint(hWnd, &ps);
			hBrush = CreateSolidBrush(RGB(0, 0, 225));
			SelectObject(hdc, hBrush);
			Chord(hdc, 100, 100, 200, 200, 150, 100, 150, 200);
			DeleteObject(hBrush);
			EndPaint(hWnd, &ps);
		}
		if (right) {
			InvalidateRect(hWnd, NULL, FALSE);
			hdc = BeginPaint(hWnd, &ps);
			hBrush = CreateSolidBrush(RGB(0, 0, 225));
			SelectObject(hdc, hBrush);
			Chord(hdc, 100, 100, 200, 200, 150, 200, 150, 100);
			DeleteObject(hBrush);
			EndPaint(hWnd, &ps);
		}
	}
	return 0;
	case WM_LBUTTONDOWN:
	{
		left = true;
		InvalidateRect(hWnd, NULL, FALSE);
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		right = true;
		InvalidateRect(hWnd, NULL, FALSE);
	}
	return 0;
	case WM_CREATE:
	{
	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
};


