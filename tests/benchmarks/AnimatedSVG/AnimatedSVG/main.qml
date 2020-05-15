import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

// advanced qt components
import Qt.labs.platform 1.1
import Qt.labs.folderlistmodel 2.1

// custom components
import WQtSVGImage 1.0

/**
* Main window
*@author JMR
*/
Window
{
    id: window
    visible: true
    width: 600
    height: 400
    title: qsTr("Animated SVG")

    /**
    * Background color dialog
    */
    ColorDialog
    {
        id: cdBgColor
        title: "Select a color"

        onAccepted:
        {
            paViewer.color = cdBgColor.color;
        }

        onRejected:
        {}

        Component.onCompleted: visible = false
    }

    /**
    * Image viewer
    */
    Rectangle
    {
        id: paViewer
        width: 400
        anchors.fill: parent
        color: "#505050"
        anchors.rightMargin: 200

        WQtSVGImage
        {
            id: imAnimSVG
            anchors.fill: parent
        }
    }

    /**
    * Navigation buttons
    */
    Rectangle
    {
        width: 200
        height: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        color: "#ffffff"
        border.color: "#00000000"
        border.width: 1

        Button
        {
            id: btChangeBgColor
            x: 128
            width: 70
            text: qsTr("Bg color")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            onClicked: cdBgColor.open();
        }
    }

    /**
    * File list view
    */
    ListView
    {
        id: lvFiles
        x: 400
        width: 200;
        leftMargin: 10
        clip: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        flickableDirection: Flickable.VerticalFlick

        model: FolderListModel
        {
            id: mlFolderModel
            nameFilters: ["*.svg"]
            folder: "Resources/Images/"
        }

        delegate: Component
        {
            id: cpItem

            Text
            {
                id: laItem
                text: fileName
                color: "#202020"

                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onEntered: laItem.color = "#389aff";
                    onExited: laItem.color = "#202020";
                    onClicked: imAnimSVG.sourceName = "Resources/Images/" + fileName;
                }
            }
        }

        ScrollBar.vertical: ScrollBar
        {
            id: sbFiles
            parent: lvFiles
            visible: true
            minimumSize: 0.1
        }
    }
}
