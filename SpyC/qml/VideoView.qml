import QtQuick 2.0
import QtMultimedia 5.2
import Components 1.0
import "./widgets"

// Video area
Rectangle {
    id: videoArea
    color: Theme.videoBkgColor
    signal maximizeVideo()

    // Play video
    function play()
    {
        video.play()
    }

    // Stop video
    function stop()
    {
        video.stop()
    }

    // Video
    Video {
        id: video
        anchors.fill: parent
        source: drone.videoUrl
        loops: MediaPlayer.Infinite
        focus: true
        opacity: drone.state === DroneBase.FLYING ? 1 : 0
        visible: opacity > 0
        Behavior on opacity {
            NumberAnimation {duration: 300}
        }
    }

    // No video image
    Item {
        id: noVideoImage
        anchors.fill: parent
        opacity: drone.state !== DroneBase.FLYING ? 1 : 0
        visible: opacity > 0
        Behavior on opacity {
            NumberAnimation {duration: 300}
        }
        Image {
            anchors.centerIn: parent
            source: "qrc:/images/img-novideo.jpg"
        }
    }

    // Display current lat/lon
    StandardText {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        text: drone.position.latitude.toFixed(2) + " / " + drone.position.longitude.toFixed(2)
        font.pixelSize: Theme.largeFontSize
        font.bold: true
    }
}
