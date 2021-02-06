/* Практичне завдання
 * Відстеження потоку людей у ТЦ
 * студентки ПІ-18-1
 * Кондратюк Наталії
 * Формування веб-сторінки
 * та надсилання її на веб-сервер,
 * що на ESP 8266
**************************************************************/

void HTTP_handleRoot( void ){
  // HTML web-page
  String out = "";
  out =
  "<html>\
    <head>\
      <meta charset=\"utf-8\">\
      <meta http-equiv=\"refresh\" content=\"10\">\
      <title>peopleCount</title>\
       <script src=\"https://cdn.anychart.com/releases/v8/js/anychart-base.min.js\"></script>\
       <script src=\"https://cdn.anychart.com/releases/v8/js/anychart-ui.min.js\"></script>\
       <script src=\"https://cdn.anychart.com/releases/v8/js/anychart-exports.min.js\"></script>\
       <link href=\"https://cdn.anychart.com/releases/v8/css/anychart-ui.min.css\" type=\"text/css\" rel=\"stylesheet\">\
       <link href=\"https://cdn.anychart.com/releases/v8/fonts/css/anychart-font.min.css\" type=\"text/css\" rel=\"stylesheet\">\
      <style>\
           #canvas{\
            border: 3px solid blue;\
            background: #C0C0C0;\
           }\
          #peopleCount{\
            width: 2000px;\
            height: 2100px;\
          }\
          #graph{\
            width: 1350px;\
            height: 1500px;\
            margin: 15px;\
            border: 3px solid black;\
            background: #808080;\
          }\
          #canvasDiv{\
            width: 860px;\
            heigth: 450px;\
            margin: 15px;\
            float: left;\
          }\
          #counter{\
            width: 405px;\
            height: 250px;\
            margin-left: 900px;\ 
            margin-top: 15px;\
            padding: 5px;\
            border: 3px solid black;\
            background: #C0C0C0;\
          }\
          #alert{\
            width: 390px;\
            height: 120px;\
            margin-left: 900px;\ 
            margin-top: 30px;\
            padding: 15px;\
            border: 3px solid black;\
            background: #C0C0C0;\
          }\
          #numberP{\
            font-family: \"Arial\", sans-serif;\
            font-size: 40px;\
            text-align: center;\
          }\
          #clock{\
            font-family: \"Courier\", monospace;\
            font-size: 40px;\
            font-weight: bold;\
            text-align: right;\
          }\
          #myAlert{\
            font-family: \"Arial\", sans-serif;\
            font-size: 30px;\
            text-align: center;\
          }\
          #container{\
            width: 1300px;\
            height: 690px;\
            margin: 20px;\
            border: 3px solid red;\
            background: #C0C0C0;\
          }\
      </style>\
  </head>\
    <body><h1>Відображення графіку потоку людей через веб-сервер</h1>\
    <div id=\"peopleCount\">\
      <div id=\"graph\">\
        <div id=\"canvasDiv\">\
          <canvas width=\"830\" height=\"440\" id=\"canvas\"></canvas>\
        </div>\
        <div id=\"counter\">\
          <p id=\"clock\">";
          out += outTimeWeb;
          out += "</p>\
          <p style=\"font-size: 20px; text-align: center;\">Кількість людей в приміщенні</p>\
          <p id=\"numberP\">";
          out += countPersons;
          out += "</p>\
        </div>\     
        <div id=\"alert\">\
          <p id=\"myAlert\"></p>\
        </div>\
        <div id=\"container\"></div>\
      </div>\
     </div>\
    <script>\
      let canvas = document.getElementById(\"canvas\");\
      let ctx = canvas.getContext('2d');\
      let x = 0;\
      let timer;\
      let s = 1;\
      let myAlert = document.getElementById(\"myAlert\");\
      let alertColor = document.getElementById(\"alert\");\
      let textColor = document.getElementById(\"myAlert\");\
      let greenZone = ";
      out += greenZone;
      out += ";\
      let yellowZone = ";
      out += yellowZone;
      out += ";\
      let redZone = ";
      out += redZone;
      out += ";\
      let curPeople = ";
      out += countPersons;
      out += ";\
      const canvasWidth = canvas.width;\
      const canvasHeight = canvas.height;\ 
      grid();\
      drawSin();\
      formAlert();\
      function formAlert(){\
        let message = \"\";\
        if ( curPeople < 100 ){\
          message += \"Прохід вільний\";\
          alertColor.style.background = \"#228B22\";\
          textColor.style.color = \"#F5DEB3\";\
        }\
        else if ( curPeople >= 100 && curPeople < 200 ){\
          message += \"Прохід обмежений\";\
          alertColor.style.background = \"#FF8C00\";\
        }\
        else if ( curPeople >= 200 ){\
          message += \"Звільнити приміщення\";\
          alertColor.style.background = \"#B22222\";\
          textColor.style.color = \"#F5DEB3\";\ 
        }\
        myAlert.innerHTML = message;\
      }\
      function drawSin() {\
      let personStr = \"";
      out += personStr;
      out += "\";\
      let personC = personStr.split( \",\" );\
      ctx.strokeStyle = \"#008000\";\
      ctx.lineWidth = 2;\
      ctx.moveTo ( 60, canvasHeight-50+0*( personC[0] ) );\
      ctx.beginPath();\
      for ( let i = 1; i < personC.length-1; i++ ){\
        ctx.lineTo ( (i+60)+3, canvasHeight-50+s*(personC[i]*-1) );\
      }\
      ctx.stroke();\
      ctx.closePath();\
      timer = setTimeout( drawSin, 1 );\
    }\
    function grid(){\
      let scaleX = 60;\
      let scaleY = 50;\
      const shift = 60;\
      const shiftSystem = 50;\
      const yAxis = canvasHeight-shiftSystem;\
      const xAxis = canvasWidth;\
      const startX = 10;\
      ctx.beginPath();\
      ctx.strokeStyle = \"#FFF8DC\";\
      ctx.font = \`${Math.round( scaleX / 2 )}px Arial\`;\
      ctx.textAlign = \"left\";\
      ctx.textBaseLine = \"top\";\
      let labelsX = [ \"09\", \"10\", \"11\", \"12\", \"13\", \"14\", \"15\", \"16\", \"17\", \"18\", \"19\", \"20\", \"21\", \"22\" ];\
      let labelsY = [ \"0\", \"50\", \"100\", \"150\", \"200\", \"250\", \"300\", \"350\" ];\
      console.log( \"labelsY.length = \" + labelsY.length );\
      let k = 0;\
      let z = 0;\
      for ( let i = 1; i < canvasWidth; i += scaleX ){\
        ctx.moveTo( i, 0 );\
        ctx.lineTo( i, canvasHeight );\
        ctx.fillText( labelsX[k], i + 45, canvasHeight-15 );\
        k++;\
      }\
      for ( let i = canvasHeight; i > 0; i -= scaleY ){\
        ctx.moveTo( 0, i );\
        ctx.lineTo( canvasWidth, i );\
        ctx.fillText( labelsY[z], 10, i-shiftSystem );\
        z++;\
      }\
      ctx.stroke();\
      ctx.closePath();\
      ctx.beginPath();\
      ctx.strokeStyle = \"#000\";\
      ctx.moveTo( shift, startX );\
      ctx.lineTo( shift, yAxis );\
      ctx.fillText( \"y\", 75, 20 );\
      ctx.moveTo( shift, yAxis );\
      ctx.lineTo( xAxis, yAxis );\
      ctx.fillText( \"x\", xAxis - 20, yAxis - 10 );\
      ctx.stroke();\
      ctx.closePath();\
    }\
    anychart.onDocumentReady(function(){\
        var data = [\
            { x: 'Прохід дозволено', value: greenZone,\
              normal:{\
                fill : \"#228B22\"\
              }\
          },\
        { x: 'Звільнити приміщення', value: redZone,\
          normal:{\
            fill : \"#B22222\"\
          }\
      },\
      { x: 'Прохід обмежено', value: yellowZone,\
        normal:{\
          fill : \"#FF8C00\"\
      }\
    }];\
    var chart = anychart.pie3d( data );\
    chart.legend().itemsLayout( \"vertical\" );\
    chart.legend().position( \"right\" );\
    chart.legend().fontSize( \"20\" );\
    chart.legend().iconSize( 20 );\
    chart.title( 'Діаграма завантаженості ТЦ' ).radius( '43%' );\
    chart.title().fontSize( \"50\" );\
    chart.container( 'container' );\
    chart.draw();\
    });\
    </script>\
   </html>";

  server.send(200, "text/html", out);
} // HTTP_handleRoot
