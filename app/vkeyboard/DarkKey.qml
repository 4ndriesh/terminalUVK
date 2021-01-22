import QtQuick 2.14
import QtQuick.VirtualKeyboard 2.14

// Workaround to avoid writing a complete new keyboard style
Key {
    keyPanelDelegate: keyboard.style ? keyboard.style.symbolKeyPanel : undefined
}
