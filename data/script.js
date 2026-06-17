
var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
// Init web socket when the page loads
window.addEventListener('load', onload);

function onload(event) {
    initWebSocket();
}

function getReadings(){
    websocket.send("getReadings");
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

// When websocket is established, call the getReadings() function
function onOpen(event) {
    console.log('Connection opened');
    getReadings();
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}


// Function that receives the message from the ESP32 with the readings
function onMessage(event) {
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj);



    for (var i = 0; i < keys.length; i++){
        key = keys[i];
        //document.getElementById(key).innerHTML = myObj[key];
        //lineChart.updateSeries(UmidOp);
    }
    


// -------- Charts -------- //

// Dados de exemplo para o gráfico (substitua com os dados reais de umidade e timestamps)
var Historico = [
    [1698675600000, 50], // timestamp e umidade
    [1698679200000, 55],
    [1698682800000, 52],
    [1698686400000, 60],
    [1698690000000, 58],
    [1698696400000, 100]
];

var HistOp = {
    series: [{
        name: 'Umidade do Solo',
        data: Historico // Substitua "dates" pelos seus dados de umidade com timestamps
    }],
    chart: {
        type: 'area',
        height: 350,
        toolbar: {
            show: false
          }
     },
    dataLabels: {
        enabled: false
    },
    markers: {
        size: 0
    },
    fill: {
        type: 'gradient',
        gradient: {
            shadeIntensity: 1,
            inverseColors: false,
            opacityFrom: 0.5,
            opacityTo: 0,
            stops: [0, 90, 100]
        }
    },
    yaxis: {
        labels: {
            formatter: function (val) {
                return val.toFixed(0); // Remove o divisor por 1.000.000 para exibir a umidade diretamente
            }
        },
        title: {
            text: 'Umidade (%)'
        }
    },
    xaxis: {
        type: 'datetime',
        labels: {
            format: 'HH:mm' // Mostra apenas as horas e minutos
        }
    },
    tooltip: {
        shared: false,
        x: {
            format: 'HH:mm' // Formato da hora no tooltip
        },
        y: {
            formatter: function (val) {
                return val.toFixed(0) + '%'; // Mostra o valor da umidade como porcentagem
            }
        }
    }
};

var lineChart = new ApexCharts(document.querySelector("#grafico_historico_umidade"), HistOp);
lineChart.render();


//------ Gráfico de percentual de umidade -----//
 var UmidOp = {
          series: [myObj[key]],
          chart: {
          type: 'radialBar',
          offsetY: -20,
          sparkline: {
            enabled: true
          }
        },
        plotOptions: {
          radialBar: {
            startAngle: -90,
            endAngle: 90,
            track: {
              background: "#e7e7e7",
              strokeWidth: '97%',
              margin: 5, // margin is in pixels
              dropShadow: {
                enabled: true,
                top: 2,
                left: 0,
                color: '#999',
                opacity: 1,
                blur: 2
              }
            },
            dataLabels: {
              name: {
                show: false
              },
              value: {
                offsetY: -2,
                fontSize: '22px'
              }
            }
          }
        },
        grid: {
          padding: {
            top: -10
          }
        },
        fill: {
          type: 'gradient',
          gradient: {
            shade: 'light',
            shadeIntensity: 0.4,
            inverseColors: true,
            opacityFrom: 1,
            opacityTo: 1,
            stops: [0, 50, 53, 91]
          },
        },
        labels: ['Percentual'],
        };

        var chart = new ApexCharts(document.querySelector("#grafico_umidade"), UmidOp);
        chart.render();

}