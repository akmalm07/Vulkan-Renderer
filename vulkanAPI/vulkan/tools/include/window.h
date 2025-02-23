#pragma once

#include "config.h"
#include "tools\include\keys.h"

#include "tools\include\window_input.h"


namespace tools {


	class WindowT
	{
	public:
		WindowT();

		WindowT(float windowWidth, float windowHeight, const std::string& name, bool isOrtho);

		bool CreateWindow(const std::string& name, int width, int height);

		float GetAspectRatio() const;

		void DelKeyComb(Keys key, Mods mod);
		void DelKeyComb(Keys key);

		std::shared_ptr<AABButtonB>& FindAABButton(std::string_view name);
		
		std::shared_ptr<KeyCombB>& FindKeyComb(Keys key, Mods mod);
		
		std::shared_ptr<KeyCombB>& FindKeyComb(Keys key);

		void DelAABButton(std::string_view name);

		void SetWidth(int width) { _width = width; }

		void SetHeight(int height) { _height = height; }

		//template<class ... Args>
		//void AddMouseClick(Mouse mouse, std::function<bool(Args...)> function);
		//void DelMouseClick(Mouse mouse);
		//MouseButton& FindMouseButtonName(Mouse mouse);
		//Planning to add a function to find the mouse button soon...

		template<class F, class ... Args>
		void AddAABButton(const AABButtonInput& input, F&& function, std::string_view str, Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddAABButton(const AABButtonInput& input, bool(T::*func)(Args...), std::string_view str, std::tuple<Args...>&& args);

		template<class ... Args>
		void AddAABButton(const AABButtonInput& input, std::function<bool(Args...)> func, std::string_view str, Args&&... args);

		template<vkType::IsClass T, class ...Args>
		void AddAABButton(const AABButtonInput& input, bool(T::* func)(Args...), std::string_view str, Args&&... args);




		template<class F, class ... Args>
		void AddKeyComb(const KeyCombInputOne& input, F&& function, Args&&... args);
		
		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(const KeyCombInputOne& input, bool(T::*func)(Args...), std::tuple<Args...>&& args);

		template<class ... Args>
		void AddKeyComb(const KeyCombInputOne& input, std::function<bool(Args...)> func, Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(const KeyCombInputOne& input, bool(T::* func)(Args...), Args&&... args);



		template<class F, class ... Args>
		void AddKeyComb(const KeyCombInputPoly &input, F&& function, Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(const KeyCombInputPoly& input, bool(T::* func)(Args...), Args&&... args);

		template<vkType::IsClass T, class ... Args>
		void AddKeyComb(const KeyCombInputPoly& input, bool(T::*func)(Args...), std::tuple<Args...>&& args);

		template<class ... Args>
		void AddKeyComb(const KeyCombInputPoly& input, std::function<bool(Args...)> func, Args&&... args);



		void SetOrtho(float left, float right, float top, float bottom);

		void MakeWindowContextCurrent();

		void SetCursorLocked();
		void SetCursorNormal();

		int GetBufferWidth();
		int GetBufferHeight();
		inline GLFWwindow* GetWindow() const { return _mainWindow; }

		bool SetWindow(GLFWwindow* window);

		inline float GetWidth() const { return _width; }
		inline float GetHeight() const { return _height; }


		float GetLeftOrtho() const;
		float GetBottomOrtho() const;
		float GetTopOrtho() const;
		float GetRightOrtho() const;

		bool IsKeyActive(Keys key, Action act) const;

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

		bool IsKeyPressed() const { return _keyPressed; }

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

		float _width = 0.0f, _height = 0.0f;
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

		bool _keyPressed = false;

		std::string _name = "";

		std::array<std::unordered_map <std::pair<Keys, Mods>, std::shared_ptr<KeyCombB>>, SIZET(Action::Count)> _keyCombs;

		std::unordered_map <std::pair<std::array<Keys, KEY_MAX>, Mods>, std::shared_ptr<KeyCombB>> _keyCombsPoly;

		std::array <std::unordered_map <std::string_view, std::shared_ptr<AABButtonB>>, SIZET(Action::Count)> _AABButtons;

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
		void WindowT::AddKeyComb(const KeyCombInputPoly& input, F&& function, Args&&... args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
			_keyCombsPoly.emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<F>(function), std::forward<Args>(args)...)
			);
		}

		template<vkType::IsClass T, class ...Args>
		inline void WindowT::AddKeyComb(const KeyCombInputPoly& input, bool(T::* func)(Args...), std::tuple<Args...>&& args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
			std::function<bool(Args...)> function = [this](Args&&... args)
				{
					return (this->*func)(std::forward<Args>(args)...);
				};
			_keyCombsPoly.emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<std::tuple<Args...>>(args))
			);
		}

		template<vkType::IsClass T, class ...Args>
		inline void WindowT::AddKeyComb(const KeyCombInputPoly& input, bool(T::* func)(Args...), Args&&... args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
			std::function<bool(Args...)> function = [this](Args&&... args)
				{
					return (this->*func)(std::forward<Args>(args)...);
				};
			_keyCombsPoly.emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<Args>(args)...)
			);
		}

		template<class ...Args>
		inline void WindowT::AddKeyComb(const KeyCombInputPoly& input, std::function<bool(Args...)> func, Args && ...args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
			_keyCombsPoly.emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(func), std::forward<Args>(args)...)
			);

		}

	//----------------------------------------------//

		template<class F, class ... Args>
		void WindowT::AddKeyComb(const KeyCombInputOne& input, F&& function, Args&&... args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None); 
			_keyCombs[SIZET(input.action)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<F>(function), std::forward<Args>(args)...)
			);
		}

		template<vkType::IsClass T, class ...Args>
		inline void WindowT::AddKeyComb(const KeyCombInputOne& input, bool(T::*func)(Args...), std::tuple<Args...>&& args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
			std::function<bool(Args...)> function = [this](Args&&... args) 
				{
					return (this->*func)(std::forward<Args>(args)...);
				};
			_keyCombs[SIZET(input.action)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<std::tuple<Args...>>(args))
			);
		}

		template<vkType::IsClass T, class ...Args>
		inline void WindowT::AddKeyComb(const KeyCombInputOne& input, bool(T::*func)(Args...), Args&&... args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
			std::function<bool(Args...)> function = [this](Args&&... args) 
				{
					return (this->*func)(std::forward<Args>(args)...);
				};
			_keyCombs[SIZET(input.action)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<Args>(args)...)
			);
		}

		template<class ...Args>
		inline void WindowT::AddKeyComb(const KeyCombInputOne& input, std::function<bool(Args...)> func, Args && ...args)
		{
			Mods val = ((input.mod != Mods::None) ? input.mod : Mods::None);
			_keyCombs[SIZET(input.action)].emplace(
				std::pair(input.number, val),
				std::make_shared<KeyComb<Args...>>(input, std::forward<std::function<bool(Args...)>>(func), std::forward<Args>(args)...)
			);

		}



		template<vkType::IsClass T, class ...Args>
		inline void WindowT::AddAABButton(const AABButtonInput& input, bool(T::*func)(Args...), std::string_view str, std::tuple<Args...>&& args)
		{
			std::function<bool(Args...)> function = [this](Args&&... args) 
				{
					return (this->*func)(std::forward<Args>(args)...);
				};
			_AABButtons[SIZET(input.action)].emplace(
				str, std::make_shared<AABButton<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<std::tuple<Args...>>(args))
			);
		}

		template<vkType::IsClass T, class ...Args>
		inline void WindowT::AddAABButton(const AABButtonInput& input, bool(T::*func)(Args...), std::string_view str, Args&&... args)
		{
			std::function<bool(Args...)> function = [this](Args&&... args) 
				{
					return (this->*func)(std::forward<Args>(args)...);
				};
			_AABButtons[SIZET(input.action)].emplace(
				str, std::make_shared<AABButton<Args...>>(input, std::forward<std::function<bool(Args...)>>(function), std::forward<Args>(args)...)
			);
		}

		template<class F, class ... Args>
		void WindowT::AddAABButton(const AABButtonInput& input, F&& function, std::string_view str, Args&&... args) 
		{
			_AABButtons[SIZET(input.action)].emplace(
				str, std::make_shared<AABButton<Args...>>(input, std::forward<F>(function), std::forward<Args>(args)...)
			);
		}

		template<class ...Args>
		inline void WindowT::AddAABButton(const AABButtonInput& input, std::function<bool(Args...)> func, std::string_view str, Args && ...args)
		{
			_AABButtons[SIZET(input.action)].emplace(
				str, std::make_shared<AABButton<Args...>>(input, std::forward<std::function<bool(Args...)>>(func), std::forward<Args>(args)...)
			);
		}

}

namespace vkType
{
	using Window = tools::WindowT;
}