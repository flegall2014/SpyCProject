import QtQuick 2.5
import QtMultimedia 5.8

// Snapshot
ImageButton {
    anchors.left: parent.left
    anchors.leftMargin: Theme.standardMargin
    anchors.bottom: parent.bottom
    anchors.bottomMargin: Theme.standardMargin
    source: "qrc:/icons/ico-snapshot.svg"

    // Sound effect
    SoundEffect {
        id: playSound
        source: "file:///D:/projects/SpyCProject/SpyC/sounds/sound_take_pic.mp3"
    }

    onClicked: {
        console.log("playing: ", playSound.source)
        playSound.play()
    }
}
