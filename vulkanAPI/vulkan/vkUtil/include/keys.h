#include "pch.h"


namespace vkUtil {

	enum class Mods
	{
		None = 0,
		Shift = GLFW_MOD_SHIFT,
		Control = GLFW_MOD_CONTROL,
		Alt = GLFW_MOD_ALT
	};

	enum class Keys
	{
		None = GLFW_KEY_UNKNOWN,
		Space = GLFW_KEY_SPACE, 
		Apost = GLFW_KEY_APOSTROPHE, 
		Comma = GLFW_KEY_COMMA, 
		Minus = GLFW_KEY_MINUS, 
		Period = GLFW_KEY_PERIOD, 
		Slash = GLFW_KEY_SLASH, 
		Zero = GLFW_KEY_0, 
		One = GLFW_KEY_1, 
		Two = GLFW_KEY_2, 
		Three = GLFW_KEY_3, 
		Four = GLFW_KEY_4, 
		Five = GLFW_KEY_5, 
		Six = GLFW_KEY_6, 
		Seven = GLFW_KEY_7, 
		Eight = GLFW_KEY_8, 
		Nine = GLFW_KEY_9, 
		Semicol = GLFW_KEY_SEMICOLON, 
		Equal = GLFW_KEY_EQUAL, 
		A = GLFW_KEY_A, 
		B = GLFW_KEY_B, 
		C = GLFW_KEY_C, 
		D = GLFW_KEY_D, 
		E = GLFW_KEY_E, 
		F = GLFW_KEY_F, 
		G = GLFW_KEY_G, 
		H = GLFW_KEY_H, 
		I = GLFW_KEY_I, 
		J = GLFW_KEY_J, 
		K = GLFW_KEY_K, 
		L = GLFW_KEY_L, 
		M = GLFW_KEY_M, 
		N = GLFW_KEY_N, 
		O = GLFW_KEY_O, 
		P = GLFW_KEY_P, 
		Q = GLFW_KEY_Q, 
		R = GLFW_KEY_R, 
		S = GLFW_KEY_S, 
		T = GLFW_KEY_T, 
		U = GLFW_KEY_U, 
		V = GLFW_KEY_V, 
		W = GLFW_KEY_W, 
		X = GLFW_KEY_X, 
		Y = GLFW_KEY_Y, 
		Z = GLFW_KEY_Z, 
		Backsl = GLFW_KEY_BACKSLASH, 
		Rbracket = GLFW_KEY_RIGHT_BRACKET,
		Lbracket = GLFW_KEY_LEFT_BRACKET,
		GravAcc = GLFW_KEY_GRAVE_ACCENT,
	};


	enum class Mouse
	{
		None = GLFW_KEY_UNKNOWN,
		Left = GLFW_MOUSE_BUTTON_1,
		Right = GLFW_MOUSE_BUTTON_2,
	};

	enum class Action
	{
		None = GLFW_KEY_UNKNOWN,
		Release = GLFW_RELEASE, 
		Press = GLFW_PRESS,
		Repeat = GLFW_REPEAT
	};


	template<class T> 
	int toInt(T type) 
	{
		return static_cast<int>(type);
	}
}