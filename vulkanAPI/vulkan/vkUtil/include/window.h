#pragma once

#include "config.h"
#include "vkUtil\include\keys.h"

#include "vkUtil\include\keys.h"
#include "vkUtil\include\window_input.h"


namespace vkUtil {


	class Window
	{
	public:
		Window();

		Window(GLint windowWidth, GLint windowHeight, const std::string& name, bool isOrtho);

		bool CreateWindow(const std::string& name, int width, int height); 

		template<class ... Args>
		void AddKeyComb(Keys key, Action action, std::function<bool(Args...)> function, std::tuple<Args...> args);
		template<class ... Args>
		void AddKeyComb(Keys key, Action action, Mods mod, std::function<bool(Args...)> function, std::tuple<Args...> args);

		void DelKeyComb(Keys key, Mods mod); 
		void DelKeyComb(Keys key); 

		void SetBufferWidth(int width) { _bufferWidth = width; }

		void SetBufferHeight(int height) { _bufferHeight = height; } 

		void SetWidth(int width) { _width = width; }
		
		void SetHeight(int height) { _height = height; }
		
		//template<class ... Args>
		//void AddMouseClick(Mouse mouse, std::function<bool(Args...)> function);
		//void DelMouseClick(Mouse mouse);

		template<class ... Args>
		void AddAABButton(float cordX, float cordY, float width, float height, Action action, Mouse button,
			std::function<bool(Args...)> function, std::string_view str, std::tuple<Args...> args);
		
		void DelAABButton(std::string_view name);


		void SetOrtho(float left, float right, float top, float bottom);

		void MakeWindowContextCurrent();

		void SetCursorLocked();
		void SetCursorNormal();

		inline GLint GetBufferWidth() const { return _bufferWidth; }
		inline GLint GetBufferHeight() const { return _bufferHeight; }

		inline GLFWwindow* GetWindow() const { return _mainWindow; }
		
		bool SetWindow(GLFWwindow* window);

		inline GLint GetWidth() const { return _width; }
		inline GLint GetHeight() const { return _height; }


		float GetLeftOrtho() const;
		float GetBottomOrtho() const;
		float GetTopOrtho() const;
		float GetRightOrtho() const;


		bool IsMouseButtonPressed(Mouse mouse) const;

		bool IsFirstClick() const;

		std::string GetName() const { return _name; }

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

		~Window();

	private:

		//Window Vars

		static constexpr size_t KEY_CONST = 1024;

		static uint32_t g_numOfWindows; 

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


		std::array<bool, KEY_CONST> _keys{false}; 

 
		std::string _name = "";

		std::array<std::unordered_map <std::pair<Keys, Mods>, std::unique_ptr<KeyCombB>>, SIZET(Action::Count)> _keyCombs;

		std::array <std::unordered_map <std::string_view, std::unique_ptr<AABButtonB>>, SIZET(Action::Count)> _AABButtons;

		//std::array<MouseButtonB, SIZET(Mouse::Count)> _mouseButtons; 

		//void setMouseBeforeX(double posX);
		//void setMouseBeforeY(double posY);

		//void setMouseAfterX(double posX);
		//void setMouseAfterY(double posY);
		//WindowButton& FindWindowButtonName(const std::string& name);

		void setKey(unsigned int key, bool val);

		//const std::string TranslateCoordinatesToNotation(uint32_t rank, uint32_t file);

		void HandleKeys(int key, int code, int action, int mode);
		void HandleMouseCursor(double posX, double posY);
		void HandleMouseButtons(int mouseButton, int action, int mods);

		void CreateCallbacks();
		static void m_HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void m_HandleMouseCursor(GLFWwindow* window, double posX, double posY);
		static void m_HandleMouseButtons(GLFWwindow* window, int button, int action, int mods);

		//	void RunTempLoop(std::promise<bool>& didTrans); 


	};

}// Namespace vkUtil



	template<class ... Args>
	void vkUtil::Window::AddKeyComb(Keys key, Action action, std::function<bool(Args...)> function, std::tuple<Args...> args)
	{
		_keyCombs[SIZET(action)].emplace(std::make_pair(key, Mods::None), key, action);
	}

	template<class ... Args>
	void vkUtil::Window::AddKeyComb(Keys key, Action action, Mods mod, std::function<bool(Args...)> function, std::tuple<Args...> args)
	{
		_keyCombs[SIZET(action)].emplace(std::make_pair(key, Mods::None), std::unique_ptr<KeyComb<Args...>>(key, action, function, std::forward<Args>(args)...));
	}


	template<class ... Args>
	void vkUtil::Window::AddAABButton(float cordX, float cordY, float width, float height, Action action, Mouse button, 
		std::function<bool(Args...)> function, std::string_view str, std::tuple<Args...> args) 
	{
		_AABButtons[SIZET(action)].emplace(str, std::unique_ptr<AABButton<Args...>>(cordX, cordY, width, height, action, button, function, std::forward<Args>(args)...));

	}


