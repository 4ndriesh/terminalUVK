/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.VirtualKeyboard 2.14
import QtQuick.VirtualKeyboard.Plugins 2.3
//import QtQuick.VirtualKeyboard.Styles 2.2
//import QtQuick.VirtualKeyboard.Settings 2.14
import ResourceProvider 1.0
import Components 1.0
import "qrc:/vkeyboard" as VKEYB

KeyboardLayout {
    inputMethod: PlainInputMethod {}
    inputMode: InputEngine.InputMode.Numeric

    KeyboardColumn {
        Layout.fillWidth: false
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: height*5/4            
        // Row1
        KeyboardRow {
            Key {
                key: Qt.Key_1
                onClicked: manageModel.textInput=1;
                text: "1"
            }
            Key {
                key: Qt.Key_2
                onClicked: manageModel.textInput=2;
                text: "2"
            }
            Key {
                key: Qt.Key_3
                onClicked: manageModel.textInput=3;
                text: "3"
            }
            EnterKey {
            }
            DelOtcep {
            }
        }
        // Row2
        KeyboardRow {
            Key {
                key: Qt.Key_7
                onClicked: manageModel.textInput=7;
                text: "7"
            }
            Key {
                key: Qt.Key_8
                onClicked: manageModel.textInput=8;
                text: "8"
            }
            Key {
                key: Qt.Key_9
                onClicked: manageModel.textInput=9;
                text: "9"
            }

            VKEYB.DarkKey {
                displayText: "\u2191"
                key: Qt.Key_Up
                onClicked: manageModel.keyUpDown(38);
                showPreview: false
                repeat: true
            }

            AddUpKey {
            }
        }
        // Row3
        KeyboardRow {
            Key {
                key: Qt.Key_4
                onClicked: manageModel.textInput=4;
                text: "4"
            }
            Key {
                key: Qt.Key_5
                onClicked: manageModel.textInput=5;
                text: "5"
            }
            Key {
                key: Qt.Key_6
                onClicked: manageModel.textInput=6;
                text: "6"
            }

            VKEYB.DarkKey {
                text: "\u2193"
                key: Qt.Key_Down
                onClicked: manageModel.keyUpDown(40);
                showPreview: false
                repeat: true
            }
            DownUpKey {
            }


        }
    }
}
