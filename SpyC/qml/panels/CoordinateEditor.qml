import QtQuick 2.5
import QtLocation 5.3
import QtQuick.Controls 1.4
import "../widgets"

Row {
    property variant coordinate
    signal latitudeChanged(double latitude)
    signal longitudeChanged(double longitude)
    signal altitudeChanged(double altitude)
    StandardText {
        text: "Latitude"
        width: 96
    }
    TextField {
        id: latTextField
        width: 96
        text: coordinate.latitude.toFixed(3)
        validator: DoubleValidator {
            bottom: -90
            top: 90
        }
        onAccepted: latitudeChanged(parseFloat(latTextField.text))
    }
    StandardText {
        text: "Longitude"
        width: 96
    }
    TextField {
        id: lonTextField
        width: 96
        text: coordinate.longitude.toFixed(3)
        validator: DoubleValidator {
            bottom: -180
            top: 180
        }
        onAccepted: longitudeChanged(parseFloat(lonTextField.text))
    }
    StandardText {
        text: "Altitude"
        width: 96
    }
    TextField {
        id: altTextField
        width: 96
        text: coordinate.altitude.toFixed(3)
        validator: DoubleValidator {
            bottom: 0
            top: 10000
        }
        onAccepted: altitudeChanged(parseFloat(altTextField.text))
    }
}
