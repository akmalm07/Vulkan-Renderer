#pragma once

#include "config.h"
#include "tools\include\keys.h"

#include "tools\include\window_input.h"
#include "tools\include\thread.h"
#include "tools\include\key_control.h"
#include "tools\include\aabb_button_control.h"
#include "tools\include\mouse_control.h"


namespace tools {


	class WindowT : public KeyControl, public AABButtonControl, public MouseControl
	{
	public:
		WindowT();

		WindowT(float windowWidth, float windowHeight, const std::string& name);

		WindowT(WindowT&& other) noexcept;

		WindowT& operator=(WindowT&& other) noexcept;


		void SetOrtho();


		bool CreateWindow(bool disableCursor, bool isOrtho);
		
		
		bool CreateWindow(float windowWidth, float windowHeight, const std::string& name, bool disableCursor, bool isOrtho);


		void SetDisableCursor(bool disableCursor);


		float GetAspectRatio() const;


		void SetWidth(int width) { _width = width; }

		void SetHeight(int height) { _height = height; }


		void SetOrtho(float left, float right, float top, float bottom);


		void MakeWindowContextCurrent();

	
		void SetCursorLocked();
		
		void SetCursorNormal();


		int GetBufferWidth();

		int GetBufferHeight();
		
		
		inline GLFWwindow* GetWindow() const { return _mainWindow; }

		
		bool SetWindow(GLFWwindow* window, bool isOrtho);

		
		inline float GetWidth() const { return _width; }
		
		inline float GetHeight() const { return _height; }


		float GetLeftOrtho() const;
		
		float GetBottomOrtho() const;
		
		float GetTopOrtho() const;
		
		float GetRightOrtho() const;


		bool IsKeyActive(Keys key, Action act) const;

		
		std::string GetName() const { return _name; }
		
		void SetName(const char* name) const { glfwSetWindowTitle(_mainWindow, name); }

		
		inline bool GetShouldClose() const { return glfwWindowShouldClose(_mainWindow); };

		
		void SetShouldClose(bool trueOrFalse);

		
		inline void SwapBuffers() const { glfwSwapBuffers(_mainWindow); }

		
		void ClearWindow();

		
		inline void pollEvents() const { glfwPollEvents(); }
		
		inline void waitEvents() const { glfwWaitEvents(); }


		void SetEscapeButton(Keys key, std::optional<Mods> mod = std::nullopt);


		~WindowT();

	private:

		//Window Vars
		static bool _calledBufferSize;

		static uint32_t g_numOfWindows;

		float _aspectRatio;

		GLFWwindow* _mainWindow = nullptr;

		float _width = 0.0f, _height = 0.0f;
		int _bufferWidth = 0, _bufferHeight = 0;

		std::optional<float> _leftOrtho, _rightOrtho, _topOrtho, _bottomOrtho;

		std::string _name = "";



	private:
		void HandleKeys(int key, int code, int action, int mode);
		void HandleMouseCursor(double posX, double posY);
		void HandleMouseButtons(int mouseButton, int action, int mods);

		void CreateCallbacks();
		static void m_HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void m_HandleMouseCursor(GLFWwindow* window, double posX, double posY);
		static void m_HandleMouseButtons(GLFWwindow* window, int button, int action, int mods);

	};

}

namespace vkType
{
	using Window = tools::WindowT;
}




//------------------------------------------------


//PLANNING TO EXTEND
//void SetAsyncPollEvents(const ThreadControlInfo& cv);

//void AllowWindowToContinueAndWait();
//void WaitInitallyForSignal();
//template<class ... Args>
//void AddMouseClick(Mouse mouse, std::function<bool(Args...)> function);
//void DelMouseClick(Mouse mouse);
//MouseButton& FindMouseButtonName(Mouse mouse);
//Planning to add a function to find the mouse button soon...
//struct Async
//{
//public:
//	Async();
//	Async(const ThreadControlInfo& condition);
//	Async(Async&& other) noexcept;
//	Async& operator=(Async&& other) noexcept;

//	void notify_window();
//	void notify_change(bool needsChange);

//	void wait_for_window();
//	void wait_for_change();

//	bool get_state() const;

//	void wait_for_window();
//	void wait_for_change();

//private:
//	std::shared_ptr <ConditionalVariuble> windowInputWait;
//	std::shared_ptr <ConditionalVariuble> changingParamsWait;
//	std::shared_ptr <std::mutex> lock;
//	bool state;
//} _oneInputCurentlyActive;

//std::array<MouseButtonB, SIZET(Mouse::Count)> _mouseButtons; 

//void setMouseBeforeX(double posX);
//void setMouseBeforeY(double posY);

//void setMouseAfterX(double posX);
//void setMouseAfterY(double posY);
//WindowButton& FindWindowButtonName(const std::string& name);