#pragma once

#include "pch.h"

#include "tools\include\keys.h"
#include "vkUtil\include\window_input_bundles.h"


namespace tools 
{
    class WindowT;

    template<class ... Args> struct MouseButton;
    template<class ... Args> struct AABButton;
    template<class ... Args> struct KeyComb;

    struct MouseButtonB
    {
    public:
        MouseButtonB();
        MouseButtonB(const MouseButtonInput& in);

        virtual bool execute() const = 0;

        template <class ... Args>
        void change_parameters(Args&&... args)
        {
            auto* derived = dynamic_cast<MouseButton<Args...>*>(this);
            if (!derived)
            {
                throw std::runtime_error("Invalid dynamic cast in change_parameters");
            }
            derived->change_parameter(std::forward<Args>(args)...);
        }

        bool getPressed() const;
        void setPressed(bool value);

        virtual ~MouseButtonB();

    protected:
        bool _pressed = false;
        Mouse _button;
        Action _action;
        mutable bool _result = false;
    };

    struct AABButtonB
    {
    public:
        AABButtonB();
        AABButtonB(const AABButtonInput& in);

        virtual bool execute() const = 0;

        bool is_clicked(float x, float y, Action action, Mouse button) const;

        template <class ... Args>
        void change_parameters(Args&&... args)
        {
            auto* derived = dynamic_cast<AABButton<Args...>*>(this);
            if (!derived)
            {
                throw std::runtime_error("Invalid dynamic cast in change_parameters");
            }
            derived->change_parameter(std::forward<Args>(args)...);
        }

        virtual ~AABButtonB();

    protected:
        float _x, _y, _width, _height;
        Action _action;
        Mouse _button;
        std::string_view _name;
        mutable bool _result = false;
    };

    struct KeyCombB
    {
    public:
        KeyCombB();
            
        KeyCombB(const KeyCombInputOne& in);
        KeyCombB(const KeyCombInputPoly& in);

        bool is_pressed(Keys number, Action action, Mods mod) const;
        
        bool is_pressed(int number, int mod) const;
        
        bool is_pressed(GLFWwindow* window, int mods) const;

        virtual bool execute() const = 0;

        template <class ... Args>
        void change_parameters(Args&&... args)
        {
            auto* derived = dynamic_cast<KeyComb<Args...>*>(this);
            if (!derived)
            {
                throw std::runtime_error("Invalid dynamic cast in change_parameters");
            }
            derived->change_parameter(std::forward<Args>(args)...);
        }

        virtual ~KeyCombB();

    protected:
        std::array<Keys, KEY_MAX> _charater;
        std::optional<Mods> _mode;
        Action _trigger;
        mutable bool _result = false;

    };

    //----------------------------------------------
    // Templated Derived Classes for User Input

    template<class ... Args>
    struct AABButton : AABButtonB
    {
    public:
        AABButton(const AABButtonInput& in, std::function<bool(Args...)> func, Args&&... args)
            : AABButtonB(in), _func(std::move(func)), _args(std::forward<Args>(args)...) {
        }
        

        AABButton(const AABButtonInput& in, std::function<bool(Args...)> func, std::tuple<Args...>&& args)
            : AABButtonB(in), _func(std::move(func)), _args(std::forward<std::tuple<Args...>>(args)) {
        }

        bool execute() const override
        {
            _result = std::apply(_func, _args);
            return _result;
        }

        void change_parameter(Args&&... args)
        {
            _args = std::tuple<Args...>(std::forward<Args>(args)...);
        }

        ~AABButton() override = default;

    private:
        std::function<bool(Args...)> _func;
        std::tuple<Args...> _args;
    };

    template<class ... Args>
    struct KeyComb : KeyCombB
    {
    public:
        KeyComb(const KeyCombInputOne& in, std::function<bool(Args...)> func, Args&&... args)
            : KeyCombB(in), _func(std::move(func)), _args(std::forward<Args>(args)...)
        {
        }

        KeyComb(const KeyCombInputOne& in, std::function<bool(Args...)> func, std::tuple<Args...>&& args)
            : KeyCombB(in), _func(std::move(func)), _args(std::forward<std::tuple<Args...>>(args))
        {
        }

        KeyComb(const KeyCombInputPoly& in, std::function<bool(Args...)> func, Args&&... args)
            : KeyCombB(in), _func(std::move(func)), _args(std::forward<Args>(args)...)
        {
        }

        KeyComb(const KeyCombInputPoly& in, std::function<bool(Args...)> func, std::tuple<Args...>&& args)
            : KeyCombB(in), _func(std::move(func)), _args(std::forward<std::tuple<Args...>>(args))
        {
        }

        bool execute() const override
        {
            _result = std::apply(_func, _args);
            return _result;
        }

        void change_parameter(Args&&... args)
        {
            _args = std::tuple<Args...>(std::forward<Args>(args)...);
        }

        ~KeyComb() override = default;

    private:
        std::function<bool(Args...)> _func;
        std::tuple<Args...> _args;
    };

    template<class ... Args>
    struct MouseButton : MouseButtonB
    {
    public:
        MouseButton(const MouseButtonInput& in, std::function<bool(Args...)> func, Args&&... args)
            : MouseButtonB(in), _func(std::move(func)), _args(std::forward<Args>(args)...) {
        }

        MouseButton(const MouseButtonInput& in, std::function<bool(Args...)> func, std::tuple<Args...>&& args)
            : MouseButtonB(in), _func(std::move(func)), _args(std::forward<std::tuple<Args...>>(args)) { //recent add
        }

        bool execute() const override
        {
            _result = std::apply(_func, _args);
            return _result;
        }

        void change_parameter(Args&&... args)
        {
            _args = std::tuple<Args...>(std::forward<Args>(args)...);
        }

        ~MouseButton() override = default;

    private:
        std::function<bool(Args...)> _func;
        std::tuple<Args...> _args;
    };



}