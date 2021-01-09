import QtQuick 2.0
import QtCharts 2.0
Item {
    anchors.fill: parent
    ChartView {
        id: chartView
        title: "speed"
        anchors.fill: parent
        antialiasing: true
        Timer {
            id: timer
            interval: 300
            repeat: true
            triggeredOnStart: true
            running: true
            onTriggered: {
                otcepsModel.getRndChart()
            }
        }
        Connections {
            target: otcepsModel
            onSetRndChart: {
                var lineSeries = chartView.series("speed");
                if (!lineSeries) {
                    lineSeries = chartView.createSeries(ChartView.SeriesTypeArea,"speed");
                    chartView.axisY().min = 0;
                    chartView.axisY().max = 10;
                    chartView.axisY().tickCount = 1;
                    chartView.axisY().titleText = "м/с";
                    chartView.axisX().titleText = "X";
                    chartView.axisX().labelFormat = "%.0f";
                }
                lineSeries.upperSeries.append(qmlX,qmlY);

                if (qmlX > 8) {
                    lineSeries.upperSeries.remove(0);
                    chartView.axisX().max = qmlX + 1;
                    chartView.axisX().min = chartView.axisX().max - 7;
                } else {
                    chartView.axisX().max = 5;
                    chartView.axisX().min = 0;
                }
                chartView.axisX().tickCount = chartView.axisX().max - chartView.axisX().min + 1;
            }
        }
    }
}
