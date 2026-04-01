#pragma once
#include <vector>
#include <cctype>
#include <cstring>
#include <string>
#include <unordered_map>

class Input
{
private:
    bool keys[256];
    bool previousKeys[256];
    bool specialKeys[256];
    bool previousSpecialKeys[256];

    bool shiftPressed = false;
    bool ctrlPressed = false;
    bool altPressed = false;

    std::unordered_map<std::string, int> keyMap;
    std::unordered_map<std::string, int> specialKeyMap;

    void initMapping()
    {
        keyMap["space"] = 32;
        keyMap["enter"] = 13;
        keyMap["return"] = 13;
        keyMap["escape"] = 27;
        keyMap["esc"] = 27;
        keyMap["backspace"] = 8;
        keyMap["tab"] = 9;
        keyMap["delete"] = 127;

        specialKeyMap["up"] = 101;
        specialKeyMap["down"] = 103;
        specialKeyMap["left"] = 100;
        specialKeyMap["right"] = 102;
        specialKeyMap["page_up"] = 104;
        specialKeyMap["page_down"] = 105;
        specialKeyMap["home"] = 106;
        specialKeyMap["end"] = 107;
        specialKeyMap["insert"] = 108;

        specialKeyMap["f1"] = 1;
        specialKeyMap["f2"] = 2;
        specialKeyMap["f3"] = 3;
        specialKeyMap["f4"] = 4;
        specialKeyMap["f5"] = 5;
        specialKeyMap["f6"] = 6;
        specialKeyMap["f7"] = 7;
        specialKeyMap["f8"] = 8;
        specialKeyMap["f9"] = 9;
        specialKeyMap["f10"] = 10;
        specialKeyMap["f11"] = 11;
        specialKeyMap["f12"] = 12;
    }

public:
    Input()
    {
        for (int i = 0; i < 256; i++)
        {
            keys[i] = false;
            previousKeys[i] = false;
            specialKeys[i] = false;
            previousSpecialKeys[i] = false;
        }
        initMapping();
    }

    void update()
    {
        for (int i = 0; i < 256; i++)
        {
            previousKeys[i] = keys[i];
            previousSpecialKeys[i] = specialKeys[i];
        }
    }

    bool isKeyDown(std::string name)
    {
        if (name.length() == 1)
            return keys[static_cast<unsigned char>(tolower(name[0]))];
        if (keyMap.count(name))
            return keys[keyMap[name]];
        if (specialKeyMap.count(name))
            return specialKeys[specialKeyMap[name]];
        return false;
    }

    bool isKeyJustPressed(std::string name)
    {
        if (name.length() == 1)
        {
            unsigned char k = static_cast<unsigned char>(tolower(name[0]));
            return keys[k] && !previousKeys[k];
        }
        if (keyMap.count(name))
        {
            int k = keyMap[name];
            return keys[k] && !previousKeys[k];
        }
        if (specialKeyMap.count(name))
        {
            int k = specialKeyMap[name];
            return specialKeys[k] && !previousSpecialKeys[k];
        }
        return false;
    }

    bool isKeyPressed(std::string name) { return isKeyJustPressed(name); }

    void setKeyState(unsigned char key, bool state)
    {
        keys[static_cast<unsigned char>(tolower(key))] = state;
    }

    void setSpecialKeyState(int key, bool state)
    {
        if (key >= 0 && key < 256)
        {
            specialKeys[key] = state;
        }
    }

    void updateModifiers(int glutModifiers)
    {
        shiftPressed = (glutModifiers & 1);
        ctrlPressed = (glutModifiers & 2);
        altPressed = (glutModifiers & 4);
    }

    bool isShiftDown() const { return shiftPressed; }
    bool isCtrlDown() const { return ctrlPressed; }
    bool isAltDown() const { return altPressed; }
};