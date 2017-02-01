import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Top Processor")

    TextArea {
        id: textArea
        x: 10
        y: 10
        width: parent.width / 3
        height: parent.height * 2 / 3
        text: qsTr("")
    }

    Button {
        id: button
        x: 15
        y: textArea.height + 20
        width: textArea.width / 2 - 15
        text: qsTr("Сохранить")

        onClicked: {
            fileDialog.visible = true
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        selectExisting: false
        onAccepted: {
            topModel.saveResults(fileDialog.fileUrl)
            visible = false
        }
    }

    Button {
        id: button1
        x: textArea.width / 2 + 15
        y: textArea.height + 20
        width: textArea.width / 2 - 15
        text: qsTr("Подтвердить")

        onClicked: {
            topModel.addAlbumsFromTextArea(textArea.text)
            textArea.text = ""
        }
    }

    Button {
        id: button2
        x: 15
        y: button.y + button.height + 10
        width: textArea.width - 20
        text: qsTr("Поиск повторов по исполнителям")

        onClicked: {
            topModel.searchOverlapsByArtist()
        }
    }

    ListView {
        id: topView
        y: 10
        x: textArea.width + 20
        width: parent.width * 2 / 3 - 30
        height: parent.height - 20

        highlight: Rectangle {
            color: "teal";
            radius: 5
        }
        focus: true

        header: Item {
            width: topView.width
            height: 40

            Row {

                Frame {
                    width: topView.width / 6

                    Text {
                        width: parent.width
                        text: "Позиция"
                        font.bold: true
                        elide: Text.ElideRight
                    }
                }

                Frame {
                    width: topView.width * 2 / 6

                    Text {
                        width: parent.width
                        text: "Исполнитель"
                        font.bold: true
                        elide: Text.ElideRight
                    }
                }

                Frame {
                    width: topView.width * 2 / 6

                    Text {
                        width: parent.width
                        text: "Альбом"
                        font.bold: true
                        elide: Text.ElideRight
                    }
                }

                Frame {
                    width: topView.width / 6

                    Text {
                        width: parent.width
                        text: "Баллы"
                        font.bold: true
                        elide: Text.ElideRight
                    }
                }
            }
        }

        delegate: Item {
            width: topView.width
            height: 40
            Row {

                Frame {
                    width: topView.width / 6

                    Text {
                        width: parent.width
                        text: position
                        elide: Text.ElideRight
                    }
                }

                Frame {
                    width: topView.width * 2 / 6

                    Text {
                        width: parent.width
                        text: artist
                        elide: Text.ElideRight
                    }
                }

                Frame {
                    width: topView.width * 2 / 6

                    Text {
                        width: parent.width
                        text: album
                        elide: Text.ElideRight
                    }
                }

                Frame {
                    width: topView.width / 6

                    Text {
                        width: parent.width
                        text: score
                        elide: Text.ElideRight
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: topView.currentIndex = index
            }
        }

        model: topModel
    }

}
