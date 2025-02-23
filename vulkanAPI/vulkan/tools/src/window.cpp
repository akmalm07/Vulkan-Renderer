#include "pch.h"

#include "tools\include\window_input.h"

#include "tools\include\keys.h"

#include "tools\include\window.h"


namespace tools {

	uint32_t WindowT::g_numOfWindows = 0;

	bool WindowT::_calledBufferSize = true;

	WindowT::WindowT()
	{

		_name = "Untitled Window";

		_mainWindow = nullptr;

		_width = 800.0f;
		_height = 800.0f;

		_leftOrtho = 0.0f;
		_rightOrtho = 0.0f;
		_topOrtho = 0.0f;
		_bottomOrtho = 0.0f;

		_aspectRatio = 1.0f;

		_keys.fill(false);
	
	}

	WindowT::WindowT(float windowWidth, float windowHeight, const std::string& name, bool isOrtho)
	{
		
		_name = name;

		_mainWindow = nullptr;

		_bufferWidth = 0;
		_bufferHeight = 0;

		_width = windowWidth;
		_height = windowHeight;


		_keys.fill(false);


		_aspectRatio = windowWidth / windowHeight;

		if (isOrtho)
		{
			if (_aspectRatio >= 1.0f)
			{
				_leftOrtho = -1.0f * _aspectRatio;
				_rightOrtho = 1.0f * _aspectRatio;
				_topOrtho = 1.0f;
				_bottomOrtho = -1.0f;
			}
			else
			{
				_leftOrtho = -1.0f;
				_rightOrtho = 1.0f;
				_topOrtho = 1.0f / _aspectRatio;
				_bottomOrtho = -1.0f / _aspectRatio;
			}
		}

	}


	bool WindowT::CreateWindow(const std::string& name, int width, int height)
	{
		if (g_numOfWindows == 0)
		{
			if (glfwInit() == GLFW_FALSE)
			{
				std::cerr << "Error Initializing GLFW! \n";
			}
			glfwSetErrorCallback([](int error, const char* description) 
				{
					fprintf(stderr, "GLFW Error: %s\n", description);
				});
		}

		_name = name;

		_width = width;

		_height = height;


		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		if (_mainWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr)) 
		{
			std::cout << "Successfully made a GLFW window called \"" << name << "\", windowWidth: " << width << 
						 ", windowHeight: " << height << ", name: " << name << '\n';
		}
		else 
		{
			throw std::runtime_error("GLFW window creation failed!");
		}

		g_numOfWindows++;

		glfwGetFramebufferSize(_mainWindow, &_bufferWidth, &_bufferHeight);
		

		int thewidth = (int)_width;
		int theheight = (int)_height;

		glfwGetWindowSize(_mainWindow, &thewidth, &theheight); 

		glfwSetCursorPos(_mainWindow, thewidth / 2, theheight / 2);

		glfwMakeContextCurrent(_mainWindow);

		CreateCallbacks();

		//glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetWindowUserPointer(_mainWindow, this);

		return true;
	}

	float WindowT::GetAspectRatio() const
	{
		return _aspectRatio;
	}


	void WindowT::SetShouldClose(bool trueOrFalse)
	{
		return glfwSetWindowShouldClose(_mainWindow, (trueOrFalse ? GLFW_TRUE : GLFW_FALSE));
	}


	float WindowT::GetLeftOrtho() const 
	{ 
		return (_leftOrtho.has_value() ? _leftOrtho.value() : throw std::runtime_error("_leftOrtho has not VALUE!")); 
	}

	float WindowT::GetBottomOrtho() const 
	{ 
		return (_bottomOrtho.has_value() ? _bottomOrtho.value() : throw std::runtime_error("_bottomOrtho has not VALUE!")); 
	}

	float WindowT::GetTopOrtho() const 
	{ 
		return (_topOrtho.has_value() ? _topOrtho.value() : throw std::runtime_error("_topOrtho has not VALUE!")); 
	}

	float WindowT::GetRightOrtho() const 
	{ 
		return (_rightOrtho.has_value() ? _rightOrtho.value() : throw std::runtime_error("_rightOrtho has not VALUE!")); 
	}

	bool WindowT::IsKeyActive(Keys key, Action action) const
	{
		if (glfwGetKey(_mainWindow, INT(key)) == INT(action))
		{
			return true;
		}
		return false;
	}


	void WindowT::SetCursorLocked()
	{
		glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void WindowT::SetCursorNormal()
	{
		glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}



	int WindowT::GetBufferWidth() 
	{ 
		if (_calledBufferSize)
		{
			glfwGetFramebufferSize(_mainWindow, &_bufferWidth, &_bufferHeight);
			_calledBufferSize = false;
		}
		return _bufferWidth; 
	}

	int WindowT::GetBufferHeight() 
	{ 
		_calledBufferSize = true;

		glfwGetFramebufferSize(_mainWindow, &_bufferWidth, &_bufferHeight); 
		return _bufferHeight; 
	}


	bool WindowT::SetWindow(GLFWwindow* window) 
	{ 
		if (!window)
		{
			fprintf(stderr, "\nThe Window provided was nullptr!\n");
			return false;
		}
		_mainWindow = std::move(window); 


		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); 
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); 


		glfwGetFramebufferSize(_mainWindow, &_bufferWidth, &_bufferHeight); 

		int width = (int)_width;
		int height = (int)_height;

		glfwGetWindowSize(_mainWindow, &width, &height); 

		glfwSetCursorPos(_mainWindow, width / 2, height / 2); 

		glfwMakeContextCurrent(_mainWindow); 
		  
		CreateCallbacks(); 

		//glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetWindowUserPointer(_mainWindow, this); 

		return true;

	}


	void WindowT::DelAABButton(std::string_view name)
	{
		for (auto& item : _AABButtons)
		{
			auto it = item.find(name);
			if (it == item.end()) 
			{
				fprintf(stderr, "Entered invalid window name ( Window.cpp : DelWindowButton )");
				return;
			}
			item.erase(it);  
		}

	}

	void WindowT::DelKeyComb(Keys name, Mods mod)
	{
		for (auto& item : _keyCombs)
		{
			auto it = item.find(std::make_pair(name, mod));
			if (it == item.end())
			{
				fprintf(stderr, "Entered invalid window name ( Window.cpp : DelWindowButton )");
				return;
			}
			item.erase(it);
		}
	}	

	void WindowT::DelKeyComb(Keys name)
	{
		for (auto& item : _keyCombs)
		{
			auto it = item.find(std::make_pair(name, Mods::None));
			if (it == item.end())
			{
				fprintf(stderr, "Entered invalid window name ( Window.cpp : DelWindowButton )");
				return;
			}
			item.erase(it);
		}
	}

	std::shared_ptr<AABButtonB>& WindowT::FindAABButton(std::string_view name)
	{
		for (auto& item : _AABButtons)
		{
			for (auto& [key, val] : item)
			{
				if (key == name)
				{
					return val;
				}
			}
		}
		throw std::runtime_error("Could not find the AABButton with the name: " + std::string(name));
	}

	std::shared_ptr<KeyCombB>& WindowT::FindKeyComb(Keys key, Mods mod)
	{		
		for (auto& keys : _keyCombs)
		{
			for (auto& [ky, val] : keys)
			{
				if (ky.first == key && ky.second == mod)
				{
					return val;
				}
			}
		}
	}
	

	std::shared_ptr<KeyCombB>& WindowT::FindKeyComb(Keys key)
	{		
		for (auto& keys : _keyCombs)
		{
			for (auto& [ky, val] : keys)
			{
				if (ky.first == key && ky.second == Mods::None)
				{
					return val;
				}
			}
		}
	}


	void WindowT::SetOrtho(float left, float right, float top, float bottom)
	{
		_leftOrtho = left;
		_rightOrtho = right;
		_topOrtho = top;
		_bottomOrtho = bottom;
	}


	void WindowT::setKey(unsigned int key, bool val)
	{
		_keys[key] = val;
	}


	bool WindowT::IsMouseButtonPressed() const
	{
		return _isMouseButtonPressed; 
	}


	bool WindowT::IsFirstClick() const
	{
		return _isFirstClick;
	}

	void WindowT::MakeWindowContextCurrent()
	{
		glfwMakeContextCurrent(_mainWindow);
	}


	void WindowT::ClearWindow()
	{

		if (!_mainWindow)
		{
			_mainWindow = nullptr;
			glfwDestroyWindow(_mainWindow);
		}

		g_numOfWindows--;

		//GraphicsHandlerAPI::DeleteWindow(_mainWindow);
	}

	WindowT::~WindowT()
	{
		ClearWindow();
	}


	//Private Functions

	void WindowT::CreateCallbacks()
	{
		//glfwSetWindowUserPointer(_mainWindow, this); 
		glfwSetKeyCallback(_mainWindow, m_HandleKeys);
		glfwSetCursorPosCallback(_mainWindow, m_HandleMouseCursor);
		glfwSetMouseButtonCallback(_mainWindow, m_HandleMouseButtons);
	}


	void WindowT::m_HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
	{
		WindowT* instance = static_cast<WindowT*>(glfwGetWindowUserPointer(window));

		instance->HandleKeys(key, code, action, mode);
	}


	void WindowT::m_HandleMouseCursor(GLFWwindow* window, double posX, double posY)
	{
		WindowT* instance = static_cast<WindowT*>(glfwGetWindowUserPointer(window));

		instance->HandleMouseCursor(posX, posY);
	}


	void WindowT::m_HandleMouseButtons(GLFWwindow* window, int button, int action, int mods)
	{
		WindowT* instance = static_cast<WindowT*>(glfwGetWindowUserPointer(window));

		instance->HandleMouseButtons(button, action, mods);
	}


	void WindowT::HandleKeys(int key, int code, int action, int mode)
	{

		switch (action)
		{
		case GLFW_PRESS:
		{
			_keyPressed = false;
			auto& act = _keyCombs[SIZET(Action::Press)];

			for (const auto& [ky, val] : act)
			{

				if (val->is_pressed(INT(key), INT(mode)))
				{
					_keyPressed = true;
					val->execute();
				}
			}
			
		}
		break;
		case GLFW_RELEASE:
		{
			_keyPressed = false;
			auto& act = _keyCombs[SIZET(Action::Release)];


			for (const auto& [ky, val] : act)
			{
				if (val->is_pressed(INT(key), INT(mode)))
				{
					_keyPressed = true;
					val->execute();
				}
			}
			
		}
		break;
		case GLFW_REPEAT:
		{
			_keyPressed = true;
			auto& act = _keyCombs[SIZET(Action::Repeat)];

			for (const auto& [ky, val] : act)
			{

				if (val->is_pressed(INT(key), INT(mode)))
				{
					_keyPressed = true;
					val->execute();
				}
			}
		
		}
		break;
		}//switch statement


		//Poly
		if (!_keyCombsPoly.empty())
		{

			for (const auto& [ky, val] : _keyCombsPoly)
			{
				if (val->is_pressed(_mainWindow, mode))
				{
					val->execute();
				}
			}
		}
	}

	


	void WindowT::HandleMouseCursor(double posX, double posY)
	{
		_mouseChangeX = posX - _mouseCurrentX;
		_mouseChangeY = _mouseCurrentY - posY;

		_mouseCurrentX = posX;
		_mouseCurrentY = posY;


	}

	void WindowT::HandleMouseButtons(int mouseButton, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS: {
			auto& act = _AABButtons[SIZET(Action::Press)];
			Mouse mouse = (mouseButton == GLFW_MOUSE_BUTTON_LEFT ? Mouse::Left : Mouse::Right);


			for (const auto& [key, val] : act)
			{
				if (val->is_clicked(_mouseCurrentX, _mouseCurrentY, Action::Press, mouse))
				{
					val->execute();
				}
			}

			//_mouseButtons[SIZET(mouse)]->setPressed(true);
			break;
		}//case of press

		case GLFW_RELEASE:
		{

			auto& act = _AABButtons[SIZET(Action::Release)];
			Mouse mouse = (mouseButton == GLFW_MOUSE_BUTTON_LEFT ? Mouse::Left : Mouse::Right);


			for (const auto& [key, val] : act)
			{
				if (val->is_clicked(_mouseCurrentX, _mouseCurrentY, Action::Release, mouse))
				{
					val->execute();
				}
			}
			//_mouseButtons[SIZET(mouse)]->setPressed(false); 
			break;
		}//case of release

		case GLFW_REPEAT:
		{

			auto& act = _AABButtons[SIZET(Action::Repeat)];
			Mouse mouse = (mouseButton == GLFW_MOUSE_BUTTON_LEFT ? Mouse::Left : Mouse::Right);


			for (const auto& [key, val] : act)
			{
				if (val->is_clicked(_mouseCurrentX, _mouseCurrentY, Action::Repeat, mouse))
				{
					val->execute();
				}
			}
			//_mouseButtons[SIZET(mouse)]->setPressed(false); 
			break;
		}//case of release
		}//switch statement

	}


} //Namespace tools