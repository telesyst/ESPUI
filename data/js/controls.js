const UI_INITIAL_GUI = 200;
const UI_BATCH_UPDATE = 201;
const UPDATE_OFFSET = 100;

const UI_TITEL = 0;

const UI_PAD = 1;
const UPDATE_PAD = 101;

const UI_CPAD = 2;
const UPDATE_CPAD = 102;

const UI_BUTTON = 3;
const UPDATE_BUTTON = 103;

const UI_LABEL = 4;
const UPDATE_LABEL = 104;

const UI_SWITCHER = 5;
const UPDATE_SWITCHER = 105;

const UI_SLIDER = 6;
const UPDATE_SLIDER = 106;

const UI_NUMBER = 7;
const UPDATE_NUMBER = 107;

const UI_TEXT_INPUT = 8;
const UPDATE_TEXT_INPUT = 108;

const UI_GRAPH = 9;
const ADD_GRAPH_POINT = 10;
const CLEAR_GRAPH = 109;

const UI_TAB = 11;
const UPDATE_TAB = 111;

const UI_SELECT = 12;
const UPDATE_SELECT = 112;

const UI_OPTION = 13;
const UPDATE_OPTION = 113;
const UI_MIN = 14;
const UPDATE_MIN = 114;
const UI_MAX = 15;
const UPDATE_MAX = 115;
const UI_STEP = 16;
const UPDATE_STEP = 116;

const UP = 0;
const DOWN = 1;
const LEFT = 2;
const RIGHT = 3;
const CENTER = 4;

// Colors
const C_TURQUOISE = 0;
const C_EMERALD = 1;
const C_PETERRIVER = 2;
const C_WETASPHALT = 3;
const C_SUNFLOWER = 4;
const C_CARROT = 5;
const C_ALIZARIN = 6;
const C_DARK = 7;
const C_NONE = 255;

function colorClass(colorId) {
  colorId = Number(colorId);
  switch (colorId) {
    case C_TURQUOISE:
      return "turquoise";

    case C_EMERALD:
      return "emerald";

    case C_PETERRIVER:
      return "peterriver";

    case C_WETASPHALT:
      return "wetasphalt";

    case C_SUNFLOWER:
      return "sunflower";

    case C_CARROT:
      return "carrot";

    case C_ALIZARIN:
      return "alizarin";

    case C_NONE:
      return "dark";
    default:
      return "";
  }
}

var websock;
var websockConnected = false;

var socketBuffer = "";

function restart() {
  $(document)
    .add("*")
    .off();
  $("#row").html("");
  websock.close();
  start();
}

function conStatusError() {
  websockConnected = false;
  $("#conStatus").removeClass("color-green");
  $("#conStatus").addClass("color-red");
  $("#conStatus").html("Error / No Connection &#8635;");
  $("#conStatus").off();
  $("#conStatus").on({
    click: restart
  });
}

function handleVisibilityChange() {
  if (!websockConnected && !document.hidden) {
    restart();
  }
}

function start() {
  document.addEventListener("visibilitychange", handleVisibilityChange, false);
  websock = new WebSocket("ws://" + window.location.hostname + "/ws");
  websock.onopen = function (evt) {
    console.log("websock open");
    $("#conStatus").addClass("color-green");
    $("#conStatus").text("Connected");
    websockConnected = true;
  };

  websock.onclose = function (evt) {
    console.log("websock close");
    conStatusError();
  };

  websock.onerror = function (evt) {
    console.log(evt);
    conStatusError();
  };

  var handleEvent = function (evt) {
    //console.log(evt);
    socketBuffer += evt.data;
    if (/* evt.data.length < 1390 &&  */evt.data.slice(-1) == "}") {
      var data = JSON.parse(socketBuffer);
      socketBuffer = "";
      var e = document.body;
      var center = "";
      switch (data.t) {
        case UI_INITIAL_GUI:
          data.controls.forEach(element => {
            var fauxEvent = {
              data: JSON.stringify(element)
            };
            handleEvent(fauxEvent);
          });
          break;

        case UI_BATCH_UPDATE:
          data.controls.forEach(element => {
            var fauxEvent = {
              data: JSON.stringify(element)
            };
            handleEvent(fauxEvent);
          });
          break;

        case UI_TITEL:
          document.title = data.l;
          $("#mainHeader").html(data.l);
          break;

        case UI_LABEL:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='two columns card tcenter " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<span id='l" + data.i + "' class='label label-wrap'>" + data.v + "</span>" +
            "</div>"
          );
          break;

        case UI_BUTTON:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='one columns card tcenter " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<button id='btn" + data.i + "' " +
            "onmousedown='buttonclick(" + data.i + ", true)' " +
            "onmouseup='buttonclick(" + data.i + ", false)'>" +
            data.v +
            "</button></div>"
          );
          $("#btn" + data.i).on({
            touchstart: function (e) {
              e.preventDefault();
              buttonclick(data.i, true);
            },
            touchend: function (e) {
              e.preventDefault();
              buttonclick(data.i, false);
            }
          });
          break;

        case UI_SWITCHER:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='one columns card tcenter " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<label id='sl" + data.i + "' class='switch " + ((data.v == "1") ? "checked" : "") + "'>" +
            "<div class='in'><input type='checkbox' id='s" + data.i + "' onClick='switcher(" + data.i + ",null)' " + ((data.v == "1") ? "checked" : "") + "/></div>" +
            "</label>" +
            "</div>"
          );
          switcher(data.i, data.v);
          break;

        case UI_CPAD:
        case UI_PAD:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='two columns card tcenter " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<nav class='control'>" +
            "<ul>" +
            "<li><a onmousedown='padclick(UP, " + data.i + ", true)' onmouseup='padclick(UP, " + data.i + ", false)' id='pf" + data.i + "'>▲</a></li>" +
            "<li><a onmousedown='padclick(RIGHT, " + data.i + ", true)' onmouseup='padclick(RIGHT, " + data.i + ", false)' id='pr" + data.i + "'>▲</a></li>" +
            "<li><a onmousedown='padclick(LEFT, " + data.i + ", true)' onmouseup='padclick(LEFT, " + data.i + ", false)' id='pl" + data.i + "'>▲</a></li>" +
            "<li><a onmousedown='padclick(DOWN, " + data.i + ", true)' onmouseup='padclick(DOWN, " + data.i + ", false)' id='pb" + data.i + "'>▲</a></li>" +
            "</ul>" +
            ((data.t == UI_CPAD) ? "<a class='confirm' onmousedown='padclick(CENTER," + data.i + ", true)' onmouseup='padclick(CENTER, " + data.i + ", false)' id='pc" + data.i + "'>OK</a>" : "") +
            "</nav>" +
            "</div>"
          );

          $("#pf" + data.i).on({
            touchstart: function (e) {
              e.preventDefault();
              padclick(UP, data.i, true);
            },
            touchend: function (e) {
              e.preventDefault();
              padclick(UP, data.i, false);
            }
          });
          $("#pl" + data.i).on({
            touchstart: function (e) {
              e.preventDefault();
              padclick(LEFT, data.i, true);
            },
            touchend: function (e) {
              e.preventDefault();
              padclick(LEFT, data.i, false);
            }
          });
          $("#pr" + data.i).on({
            touchstart: function (e) {
              e.preventDefault();
              padclick(RIGHT, data.i, true);
            },
            touchend: function (e) {
              e.preventDefault();
              padclick(RIGHT, data.i, false);
            }
          });
          $("#pb" + data.i).on({
            touchstart: function (e) {
              e.preventDefault();
              padclick(DOWN, data.i, true);
            },
            touchend: function (e) {
              e.preventDefault();
              padclick(DOWN, data.i, false);
            }
          });
          $("#pc" + data.i).on({
            touchstart: function (e) {
              e.preventDefault();
              padclick(CENTER, data.i, true);
            },
            touchend: function (e) {
              e.preventDefault();
              padclick(CENTER, data.i, false);
            }
          });

          break;

        //https://codepen.io/seanstopnik/pen/CeLqA
        case UI_SLIDER:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='two columns card tcenter card-slider " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<div class='range-slider'>" +
            "<input id='sl" + data.i + "' type='range' min='0' max='100' value='" + data.v + "' class='range-slider__range'>" +
            "<span class='range-slider__value'>" + data.v + "</span>" +
            "</div>" +
            "</div>"
          );
          rangeSlider();
          break;

        case UI_NUMBER:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='two columns card tcenter " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<input style='color:black;' id='num" + data.i + "' type='number' value='" + data.v + "' onchange='numberchange(" + data.i + ")' />" +
            "</div>"
          );
          break;

        case UI_TEXT_INPUT:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='two columns card tcenter " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<input style='color:black;' id='text" + data.i + "' value='" + data.v + "' onchange='textchange(" + data.i + ")' />" +
            "</div>"
          );
          break;

        case UI_TAB:
          $("#tabsnav").append(
            "<li><a href='#tab" + data.i + "'>" + data.v + "</a></li>"
          );
          $("#tabscontent").append(
            "<div id='tab" + data.i + "'></div>"
          );

          tabs = $('.tabscontent').tabbedContent({ loop: true }).data('api');
          // switch to tab...
          $('a').filter(function () {
            return $(this).attr('href') === '#click-to-switch';
          }).on('click', function (e) {
            var tab = prompt('Tab to switch to (number or id)?');
            if (!tabs.switchTab(tab)) {
              alert('That tab does not exist :\\');
            }
            e.preventDefault();
          });
          break;

        case UI_SELECT:
          var parent;
          if (data.p) {
            parent = $("#tab" + data.p);
          } else {
            parent = $("#row")
          }
          parent.append(
            "<div id='id" + data.i + "' class='two columns card tcenter " + colorClass(data.c) + "'>" +
            "<h5>" + data.l + "</h5><hr/>" +
            "<select style='color:black;' id='select" + data.i + "' onchange='selectchange(" + data.i + ")' />" +
            "</div>"
          );
          break;

        case UI_OPTION:
          if (data.p) {
            var parent = $("#select" + data.p);
            parent.append(
              "<option id='option" + data.i + "' value='" + data.v + "' " + data.s + ">" + data.l + "</option>"
            );
          }
          break;

        case UI_MIN:
          if (data.p) {
            var parent = $("#id" + data.p + " input");
            if (parent.size()) {
              parent.attr("min", data.v);
            }
          }
          break;

        case UI_MAX:
          if (data.p) {
            var parent = $("#id" + data.p + " input");
            if (parent.size()) {
              parent.attr("max", data.v);
            }
          }
          break;

        case UI_STEP:
          if (data.p) {
            var parent = $("#id" + data.p + " input");
            if (parent.size()) {
              parent.attr("step", data.v);
            }
          }
          break;

        case UPDATE_LABEL:
          $("#l" + data.i).html(data.v);
          break;

        case UPDATE_SWITCHER:
          switcher(data.i, (data.v == "0") ? 0 : 1);
          break;

        case UPDATE_SLIDER:
          slider_move($("#sl" + data.i), data.v, "100", false);
          break;

        case UPDATE_NUMBER:
          $("#num" + data.i).val(data.v);
          break;

        case UPDATE_TEXT_INPUT:
          $("#text" + data.i).val(data.v);
          break;

        case UPDATE_SELECT:
          $("#select" + data.i).val(data.v);
          break;

        case UPDATE_BUTTON:
        case UPDATE_PAD:
        case UPDATE_CPAD:
          break;

        default:
          console.error("Unknown type or event");
          break;
      }

      if (data.t >= UPDATE_OFFSET && data.t < UI_INITIAL_GUI) {
        var element = $('#id' + data.i);
        //       if(data.t == UPDATE_SLIDER) {
        //         element.removeClass("slider-turquoise slider-emerald slider-peterriver slider-wetasphalt slider-sunflower slider-carrot slider-alizarin");
        //         element.addClass("slider-" + colorClass(data.c));
        //       } else {
        element.removeClass("turquoise emerald peterriver wetasphalt sunflower carrot alizarin");
        element.addClass(colorClass(data.c));
        //       }
      }
    }
  };

  websock.onmessage = handleEvent;
}

function sliderchange(number) {
  var val = $("#sl" + number).val();
  console.log("slvalue:" + val + ":" + number);
  websock.send("slvalue:" + val + ":" + number);
}

function numberchange(number) {
  var val = $("#num" + number).val();
  websock.send("nvalue:" + val + ":" + number);
}

function textchange(number) {
  var val = $("#text" + number).val();
  websock.send("tvalue:" + val + ":" + number);
}

function selectchange(number) {
  var val = $("#select" + number).val();
  websock.send("svalue:" + val + ":" + number);
}

function buttonclick(number, isdown) {
  if (isdown) websock.send("bdown:" + number);
  else websock.send("bup:" + number);
}

function padclick(type, number, isdown) {
  switch (type) {
    case CENTER:
      if (isdown) websock.send("pcdown:" + number);
      else websock.send("pcup:" + number);
      break;
    case UP:
      if (isdown) websock.send("pfdown:" + number);
      else websock.send("pfup:" + number);
      break;
    case DOWN:
      if (isdown) websock.send("pbdown:" + number);
      else websock.send("pbup:" + number);
      break;
    case LEFT:
      if (isdown) websock.send("pldown:" + number);
      else websock.send("plup:" + number);
      break;
    case RIGHT:
      if (isdown) websock.send("prdown:" + number);
      else websock.send("prup:" + number);
      break;
  }
}

function switcher(number, state) {
  if (state == null) {
    if ($("#s" + number).is(":checked")) {
      websock.send("sactive:" + number);
      $("#sl" + number).addClass("checked");
    } else {
      websock.send("sinactive:" + number);
      $("#sl" + number).removeClass("checked");
    }
  } else if (state == 1) {
    $("#sl" + number).addClass("checked");
    $("#sl" + number).prop("checked", true);
  } else if (state == 0) {
    $("#sl" + number).removeClass("checked");
    $("#sl" + number).prop("checked", false);
  }
}

var rangeSlider = function () {
  var slider = $('.range-slider'),
    range = $('.range-slider__range'),
    value = $('.range-slider__value');

  slider.each(function () {

    value.each(function () {
      var value = $(this).prev().attr('value');
      $(this).html(value);
    });

    range.on({
      'input': function () {
        $(this).next().html(this.value);
      },
      'change': function () {
        sliderchange($(this).attr('id').replace(/^\D+/g, ''));
      }
    });
  });
};
