#pragma once

#include "config.h"
#include "tools\include\keys.h"

#include "tools\include\keys.h"
#include "tools\include\window_input.h"


namespace vkUtil {


	class WindowT
	{
	public:
		WindowT();

		WindowT(int windowWidth, int windowHeight, const std::string& name, bool isOrtho);

		bool CreateWindow(const std::string& name, int width, int height);

		float GetAspectRatio() const;

		void DelKeyComb(Keys key, Mods mod);
		void DelKeyComb(Keys key);

		void DelAABButton(std::string_view name);

		void SetWidth(int width) { _width = width; }

		void SetHeight(int height) { _height = height; }

		//template<class ... Args>
		//void AddMouseClick(Mouse mouse, std::function<bool(Args...)> function);
		//void DelMouseClick(Mouse mouse);


		template<class F, class ... Args>
		void AddAABButton(const AABButtonInput& input, F&& function, std::string_view str, Args&&... args);

		template<class F, class ... Args>
		void AddKeyComb(const KeyCombInput& input, F&& function, Args&&... args);

		void SetOrtho(float left, float right, float top, float bottom);

		void MakeWindowContextCurrent();

		void SetCursorLocked();
		void SetCursorNormal();

		int GetBufferWidth();
		int GetBufferHeight();
		inline GLFWwindow* GetWindow() const { return _mainWindow; }

		bool SetWindow(GLFWwindow* window);

		inline int GetWidth() const { return _width; }
		inline int GetHeight() const { return _height; }


		float GetLeftOrtho() const;
		float GetBottomOrtho() const;
		float GetTopOrtho() const;
		float GetRightOrtho() const;


		bool IsMouseButtonPressed() const;

		bool IsFirstClick() const;

		std::string GetName() const { return _name; }
		void SetName(const char* name) const { glfwSetWindowTitle(_mainWindow, name); }

		double GetMouseCurrentX() const { return _mouseCurrentX; }
		double GetMouseCurrentY() const { return _mouseCurrentY; }

		double GetMouseChangeX() const { return _mouseChangeX; }
		double GetMouseChangeY() const { return _mouseChangeY; }

		inline bool GetShouldClose() const { return glfwWindowShouldClose(_mainWindow); };

		void SetShouldClose(bool trueOrFalse);


		std::array<bool, 1024> GetKeys() { return _keys; }

		void SwapBuffers() const { glfwSwapBuffers(_mainWindow); }

		void ClearWindow();

		void pollEvents() const { glfwPollEvents(); }
		void waitEvents() const { glfwWaitEvents(); }

		~WindowT();

	private:

		//Window Vars

		static constexpr size_t KEY_CONST = 1024;

		static bool _calledBufferSize;

		static uint32_t g_numOfWindows;

		float _aspectRatio;

		GLFWwindow* _mainWindow = nullptr;

		int _width = 0, _height = 0;
		int _bufferWidth = 0, _bufferHeight = 0;

		std::optional<float> _leftOrtho, _rightOrtho, _topOrtho, _bottomOrtho;


		//Mouse Vars
		bool _isFirstClick = false;

		double _mouseChangeX = 0.0;
		double _mouseChangeY = 0.0;

		double _mouseCurrentX = 0.0;
		double _mouseCurrentY = 0.0;

		//double _mouseAfterX = 0.0;
		//double _mouseAfterY = 0.0;

		bool _mouseFirstMoved = true;

		bool _isMouseButtonPressed = false;


		std::array<bool, KEY_CONST> _keys{ false };


		std::string _name = "";

		std::array<std::unordered_map <std::pair<Keys, Mods>, std::unique_ptr<KeyCombB>>, SIZET(Action::Count)> _keyCombs;

		std::array <std::unordered_map <std::string_view, std::unique_ptr<AABButtonB>>, SIZET(Action::Count)> _AABButtons;

		//std::array<MouseButtonB, SIZET(Mouse::Count)> _mouseButtons; 

		//void setMouseBeforeX(double posX);
		//void setMouseBeforeY(double posY);

		//void setMouseAfterX(double posX);
		//void setMouseAfterY(double posY);
		//WindowButton& FindWindowButtonName(const std::string& name);

	private:

		void setKey(unsigned int key, bool val);

		//const std::string TranslateCoordinatesToNotation(uint32_t rank, uint32_t file);

		void HandleKeys(int key, int code, int action, int mode);
		void HandleMouseCursor(double posX, double posY);
		void HandleMouseButtons(int mouseButton, int action, int mods);

		void CreateCallbacks();
		static void m_HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void m_HandleMouseCursor(GLFWwindow* window, double posX, double posY);
		static void m_HandleMouseButtons(GLFWwindow* window, int button, int action, int mods);
	};

		template<class F, class ... Args>
		void WindowT::AddKeyComb(const KeyCombInput& input, F&& function, Args&&... args)
		{
			Mods val = (input.mod != Mods::None) ? input.mod : Mods::None;
			_keyCombs[SIZET(input.action)].emplace(
				std::pair(input.number, val),
				std::make_unique<KeyComb<Args...>>(input, std::forward<F>(function), std::forward<Args>(args)...)
			);
		}

		template<class F, class ... Args>
		void WindowT::AddAABButton(const AABButtonInput& input, F&& function, std::string_view str, Args&&... args) 
		{
			_AABButtons[SIZET(input.action)].emplace(
				str, std::make_unique<AABButton<Args...>>(input, std::forward<F>(function), std::forward<Args>(args)...)
			);
		}
}

namespace vkType
{
	using Window = vkUtil::WindowT;
}