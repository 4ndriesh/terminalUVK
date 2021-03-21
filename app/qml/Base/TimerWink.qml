import QtQuick 2.0
import SettingsModule 1.0

Timer {
    id: _timerwink
    interval: Settings.highlight.timeWink
    onTriggered: {
        manageModel.qmlRegim(11);
        manageModel.qmlRegim(10);
    }
}

