import QtQuick 2.0
import QtMultimedia 5.2

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
        Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
        Keys.onLeftPressed: video.seek(video.position - 5000)
        Keys.onRightPressed: video.seek(video.position + 5000)
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
