#pragma once

#include "pch.h"
#include "vkUtil\include\keys.h"
#include "vkUtil\include\window_input.h"


namespace vkUtil {


	class Window
	{
	private:
		struct WindowButton;
		struct KeyComb;

	public:
		Window();

		Window(GLint windowWidth, GLint windowHeight, const std::string& namem, bool isOrtho);

		bool CreateWindow();

		//	void TransferLoop(std::function<void(GLFWwindow *)> newLoopHandler);  

		//	void RunTempLoop();
		template<class R, class ... Args>
		void AddKeyComb(Keys key, std::function<R(Args...)> function);
		void DelKeyComb(const std::string& keyNumber);

		template<class R, class ... Args>
		void AddMouseClick(Mouse mouse, std::function<R(Args...)> function);
		void DelMouseClick(Mouse mouse);

		template<class R, class ... Args>
		void AddAABButton(unsigned int posX, unsigned int posY, float width, float height,
			std::function<R(Args...)> function, const std::string& name);
		void DelAABButton(const std::string_view name);

		void MakeWindowContextCurrent();

		void SetCursorLocked();
		void SetCursorNormal();

		inline GLint GetBufferWidth() const { return bufferWidth; }

		inline GLint GetBufferHeight() const { return bufferHeight; }

		inline GLFWwindow* GetWindow() const { return mainWindow; }

		inline GLint GetWidth() const { return width; }

		inline GLint GetHeight() const { return height; }


		inline float GetLeftOrtho() const;
		inline float GetBottomOrtho() const;
		inline float GetTopOrtho() const;
		inline float GetRightOrtho() const;


		bool IsMouseButtonPressed(Mouse mouse) const;

		bool IsFirstClick() const;

		std::string GetName() const { return name; }

		double GetMouseBeforeX() const { return mouseBeforeX; }
		double GetMouseBeforeY() const { return mouseBeforeY; }

		double GetMouseAfterX() const { return mouseAfterX; }
		double GetMouseAfterY() const { return mouseAfterY; }

		inline bool GetShouldClose() const { return glfwWindowShouldClose(mainWindow); };

		void SetShouldClose(bool trueOrFalse);


		std::array<bool, 1024> GetKeys() { return keys; }

		void SwapBuffers() const { glfwSwapBuffers(mainWindow); }

		void ClearWindow();

		void HandleKeys(int key, int code, int action, int mode);
		void HandleMouseCursor(double posX, double posY);
		void HandleMouseButtons(int mouseButton, int action, int mods);

		~Window();

	private:

		//Window Vars

		static constexpr size_t KEY_CONST = 1024;

		static uint32_t numOfWindows; 

		GLFWwindow* mainWindow = nullptr;

		int width = 0, height = 0;
		int bufferWidth = 0, bufferHeight = 0;
		
		std::optional<float> leftOrtho, rightOrtho, topOrtho, bottomOrtho;


		//Mouse Vars
		bool isFirstClick = false;

		double mouseBeforeX = 0.0;
		double mouseBeforeY = 0.0;

		double mouseCurrentX = 0.0;
		double mouseCurrentY = 0.0;
		
		double mouseAfterX = 0.0;
		double mouseAfterY = 0.0;
		
		bool mouseFirstMoved = false;

		bool isMouseButtonPressed = false;


		std::array<bool, KEY_CONST> keys{false}; 

 
		std::string name = "";

		std::ordered_array <std::unordered_map <std::pair<Keys, Mods>, KeyCombB>, Action, 3> keyCombs;

		std::unordered_map <std::string, AABButtonB> AABButtons;

		std::pair<MouseButtonB, MouseButtonB> mouseButtons; 


		KeyComb* FindKeyComb(const std::string& keyNumber);


		Mods FindTheModeValue(unsigned int mode);

		void setMouseBeforeX(double posX);
		void setMouseBeforeY(double posY);

		void setMouseAfterX(double posX);
		void setMouseAfterY(double posY);
		WindowButton& FindWindowButtonName(const std::string& name);

		void setKey(unsigned int key, bool val);

		//const std::string TranslateCoordinatesToNotation(uint32_t rank, uint32_t file);

		void CreateCallbacks();
		static void m_HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void m_HandleMouseCursor(GLFWwindow* window, double posX, double posY);
		static void m_HandleMouseButtons(GLFWwindow* window, int button, int action, int mods);

		//	void RunTempLoop(std::promise<bool>& didTrans); 


	};




}

