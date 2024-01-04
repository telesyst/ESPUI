const char CSS_STYLE[] PROGMEM = R"=====(
.container{position:relative;width:79%;margin:20px;box-sizing:border-box}.column,.columns{width:100%;float:left}.card{min-height:100px;border-radius:6px;box-shadow:0 4px 4px rgba(204,197,185,0.5);padding-left:20px;padding-right:20px;margin-bottom:40px;min-width:500px;color:#fff}@media(min-width:1205px){.wide.card{min-width:1075px}}@media(min-width:1790px){.wide.card{min-width:1650px}}@media(max-width:630px){.card{min-width:98%}}.sectionbreak.columns{color:black}.sectionbreak.columns hr{border:0;height:2px;background-color:#666}.turquoise{background:#1abc9c;border-bottom:#16a085 3px solid}.emerald{background:#2ecc71;border-bottom:#27ae60 3px solid}.peterriver{background:#3498db;border-bottom:#2980b9 3px solid}.wetasphalt{background:#34495e;border-bottom:#2c3e50 3px solid}.sunflower{background:#f1c40f;border-bottom:#e6bb0f 3px solid}.carrot{background:#e67e22;border-bottom:#d35400 3px solid}.alizarin{background:#e74c3c;border-bottom:#c0392b 3px solid}.dark{background:#444857;border-bottom:#444857 3px solid}.label{box-sizing:border-box;white-space:nowrap;border-radius:.2em;padding:.12em .4em .14em;text-align:center;color:#fff;font-weight:700;line-height:1.3;margin-bottom:5px;display:inline-block;white-space:nowrap;vertical-align:baseline;position:relative;top:-.15em;background-color:#999;margin-bottom:10px}.label-wrap{width:90%;white-space:pre-wrap;word-wrap:break-word}.label.color-blue{background-color:#6f9ad1}.label.color-red{background-color:#d37c7c}.label.color-green{background-color:#9bc268}.label.color-orange{background-color:#dea154}.label.color-yellow{background-color:#e9d641}.label.color-purple{background-color:#9f83d1}@media(min-width:400px){.container{width:84%}}@media(min-width:630px){.container{width:98%}.column,.columns{margin-right:35px}.column:first-child,.columns:first-child{margin-left:0}.one.column,.one.columns{width:4.66666666667%}.two.columns{width:13.3333333333%}.three.columns{width:22%}.four.columns{width:30.6666666667%}.five.columns{width:39.3333333333%}.six.columns{width:48%}.seven.columns{width:56.6666666667%}.eight.columns{width:65.3333333333%}.nine.columns{width:74%}.ten.columns{width:82.6666666667%}.eleven.columns{width:91.3333333333%}.twelve.columns{width:100%;margin-left:0}.one-third.column{width:30.6666666667%}.two-thirds.column{width:65.3333333333%}.one-half.column{width:48%}.offset-by-one.column,.offset-by-one.columns{margin-left:8.66666666667%}.offset-by-two.column,.offset-by-two.columns{margin-left:17.3333333333%}.offset-by-three.column,.offset-by-three.columns{margin-left:26%}.offset-by-four.column,.offset-by-four.columns{margin-left:34.6666666667%}.offset-by-five.column,.offset-by-five.columns{margin-left:43.3333333333%}.offset-by-six.column,.offset-by-six.columns{margin-left:52%}.offset-by-seven.column,.offset-by-seven.columns{margin-left:60.6666666667%}.offset-by-eight.column,.offset-by-eight.columns{margin-left:69.3333333333%}.offset-by-nine.column,.offset-by-nine.columns{margin-left:78%}.offset-by-ten.column,.offset-by-ten.columns{margin-left:86.6666666667%}.offset-by-eleven.column,.offset-by-eleven.columns{margin-left:95.3333333333%}.offset-by-one-third.column,.offset-by-one-third.columns{margin-left:34.6666666667%}.offset-by-two-thirds.column,.offset-by-two-thirds.columns{margin-left:69.3333333333%}.offset-by-one-half.column,.offset-by-one-half.columns{margin-left:52%}}html{font-size:62.5%}body{margin:0;font-size:1.5em;line-height:1;font-weight:400;font-family:"Open Sans",sans-serif;color:#222;background-color:#ecf0f1}h1,h2,h3,h4,h5,h6{margin-top:0;margin-bottom:.5rem;font-weight:300}h1{font-size:4rem;line-height:1.2;letter-spacing:-.1rem}h2{font-size:3.6rem;line-height:1.25;letter-spacing:-.1rem}h3{font-size:3rem;line-height:1.3;letter-spacing:-.1rem}h4{font-size:2.4rem;line-height:1.35;letter-spacing:-.08rem}h5{font-size:1.8rem;line-height:1.5;letter-spacing:-.05rem}h6{font-size:1.5rem;line-height:1.6;letter-spacing:0}@media(min-width:630px){h1{font-size:5rem}h2{font-size:4.2rem}h3{font-size:3.6rem}h4{font-size:3rem}h5{font-size:2rem}h6{font-size:1.5rem}}p{margin-top:0}a{color:#1eaedb}a:hover{color:#0fa0ce}button{display:inline-block;padding:10px;border-radius:3px;color:#fff;background-color:#999}button:enabled:active{background-color:#666;transform:translateX(4px) translateY(4px)}#mainHeader{display:inline-block}#conStatus{position:inherit;font-size:.75em}button,.button{margin-bottom:1rem;margin-left:.3rem;margin-right:.3rem}.u-full-width{width:100%;box-sizing:border-box}.u-max-full-width{max-width:100%;box-sizing:border-box}.u-pull-right{float:right}.u-pull-left{float:left}.tcenter{text-align:center}hr{margin-top:.5rem;margin-bottom:1.2rem;border-width:0;border-top:1px solid #e1e1e1}.container:after,.row:after,.u-cf{content:"";display:table;clear:both}.control{background-color:#ddd;background-image:linear-gradient(hsla(0,0%,0%,0.1),hsla(0,0%,100%,0.1));border-radius:50%;box-shadow:inset 0 1px 1px 1px hsla(0,0%,100%,0.5),0 0 1px 1px hsla(0,0%,100%,0.75),0 0 1px 2px hsla(0,0%,100%,0.25),0 0 1px 3px hsla(0,0%,100%,0.25),0 0 1px 4px hsla(0,0%,100%,0.25),0 0 1px 6px hsla(0,0%,0%,0.75);height:9em;margin:3em auto;position:relative;width:9em}.control ul{height:100%;padding:0;transform:rotate(45deg)}.control li{border-radius:100% 0 0 0;box-shadow:inset -1px -1px 1px hsla(0,0%,100%,0.5),0 0 1px hsla(0,0%,0%,0.75);display:inline-block;height:50%;overflow:hidden;width:50%}.control ul li:nth-child(2){transform:rotate(90deg)}.control ul li:nth-child(3){transform:rotate(-90deg)}.control ul li:nth-child(4){transform:rotate(180deg)}.control ul a{height:200%;position:relative;transform:rotate(-45deg);width:200%}.control a:hover,.control a:focus{background-color:hsla(0,0%,100%,0.25)}.control a{border-radius:50%;color:#333;display:block;font:bold 1em/3 sans-serif;text-align:center;text-decoration:none;text-shadow:0 1px 1px hsla(0,0%,100%,0.4);transition:.15s}.control .confirm{background-color:#ddd;background-image:linear-gradient(hsla(0,0%,0%,0.15),hsla(0,0%,100%,0.25));box-shadow:inset 0 1px 1px 1px hsla(0,0%,100%,0.5),0 0 1px 1px hsla(0,0%,100%,0.25),0 0 1px 2px hsla(0,0%,100%,0.25),0 0 1px 3px hsla(0,0%,100%,0.25),0 0 1px 4px hsla(0,0%,100%,0.25),0 0 1px 6px hsla(0,0%,0%,0.85);left:50%;line-height:3;margin:-1.5em;position:absolute;top:50%;width:3em}.control .confirm:hover,.control .confirm:focus{background-color:#eee}.control:not(.disabled) a.confirm:active{background-color:#777}.control:not(.disabled) li:active{background-color:#777}.switch{display:inline-block !important;background-color:#bebebe;border-radius:4px;box-shadow:inset 0 0 6px rgba(0,0,0,0.3);color:#fff;cursor:pointer;display:block;font-size:14px;height:26px;margin-left:.3rem;margin-right:.3rem;position:relative;width:60px;-webkit-transition:background-color .2s ease-in-out;-moz-transition:background-color .2s ease-in-out;-o-transition:background-color .2s ease-in-out;-ms-transition:background-color .2s ease-in-out;transition:background-color .2s ease-in-out}.switch.checked{background-color:#76d21d}.switch input[type="checkbox"]{display:none;cursor:pointer;height:10px;left:12px;position:absolute;top:8px;width:10px}.in{position:absolute;top:8px;left:12px;-webkit-transition:left .08s ease-in-out;-moz-transition:left .08s ease-in-out;-o-transition:left .08s ease-in-out;-ms-transition:left .08s ease-in-out;transition:left .08s ease-in-out}.switch.checked div{left:38px}.switch .in:before{background:#fff;background:-moz-linear-gradient(top,#fff 0,#f0f0f0 100%);background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#fff),color-stop(100%,#f0f0f0));background:-webkit-linear-gradient(top,#fff 0,#f0f0f0 100%);background:-o-linear-gradient(top,#fff 0,#f0f0f0 100%);background:-ms-linear-gradient(top,#fff 0,#f0f0f0 100%);background:linear-gradient(to bottom,#fff 0,#f0f0f0 100%);border:1px solid #fff;border-radius:2px;box-shadow:0 0 4px rgba(0,0,0,0.3);content:"";height:18px;position:absolute;top:-5px;left:-9px;width:26px}.switch .in:after{background:#f0f0f0;background:-moz-linear-gradient(top,#f0f0f0 0,#fff 100%);background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#f0f0f0),color-stop(100%,#fff));background:-webkit-linear-gradient(top,#f0f0f0 0,#fff 100%);background:-o-linear-gradient(top,#f0f0f0 0,#fff 100%);background:-ms-linear-gradient(top,#f0f0f0 0,#fff 100%);background:linear-gradient(to bottom,#f0f0f0 0,#fff 100%);border-radius:10px;content:"";height:12px;margin:-1px 0 0 -1px;position:absolute;width:12px}.rkmd-slider{display:block;position:relative;font-size:16px;font-family:"Roboto",sans-serif}.rkmd-slider input[type="range"]{overflow:hidden;position:absolute;width:1px;height:1px;opacity:0}.rkmd-slider input[type="range"]+.slider{display:block;position:relative;width:100%;height:27px;border-radius:13px;background-color:#bebebe}@media(pointer:fine){.rkmd-slider input[type="range"]+.slider{height:4px;border-radius:0}}.rkmd-slider input[type="range"]+.slider .slider-fill{display:block;position:absolute;width:0;height:100%;user-select:none;z-index:1}.rkmd-slider input[type="range"]+.slider .slider-handle{cursor:pointer;position:absolute;top:12px;left:0;width:15px;height:15px;margin-left:-8px;border-radius:50%;transition:all .2s ease;user-select:none;z-index:2}@media(pointer:fine){.rkmd-slider input[type="range"]+.slider .slider-handle{top:-5.5px}}.rkmd-slider input[type="range"]:disabled+.slider{background-color:#b0b0b0 !important}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle{cursor:default !important;background-color:#b0b0b0 !important}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill .slider-label,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle .slider-label{display:none;background-color:#b0b0b0 !important}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill.is-active,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle.is-active{top:-5.5px;width:15px;height:15px;margin-left:-8px}.rkmd-slider input[type="range"]:disabled+.slider .slider-fill.is-active .slider-label,.rkmd-slider input[type="range"]:disabled+.slider .slider-handle.is-active .slider-label{display:none;border-radius:50%;transform:none}.rkmd-slider input[type="range"]:disabled+.slider .slider-handle:active{box-shadow:none !important;transform:scale(1) !important}.rkmd-slider.slider-discrete .slider .slider-handle{position:relative;z-index:1}.rkmd-slider.slider-discrete .slider .slider-handle .slider-label{position:absolute;top:-17.5px;left:4px;width:30px;height:30px;-webkit-transform-origin:50% 100%;transform-origin:50% 100%;border-radius:50%;-webkit-transform:scale(1) rotate(-45deg);transform:scale(1) rotate(-45deg);-webkit-transition:all .2s ease;transition:all .2s ease}@media(pointer:fine){.rkmd-slider.slider-discrete .slider .slider-handle .slider-label{left:-2px;-webkit-transform:scale(0.5) rotate(-45deg);transform:scale(0.5) rotate(-45deg)}}.rkmd-slider.slider-discrete .slider .slider-handle .slider-label span{position:absolute;top:7px;left:0;width:100%;color:#fff;font-size:16px;text-align:center;-webkit-transform:rotate(45deg);transform:rotate(45deg);opacity:0;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none}@media(pointer:fine){.rkmd-slider.slider-discrete .slider .slider-handle .slider-label span{font-size:12px}}.rkmd-slider.slider-discrete .slider .slider-handle.is-active{top:0;margin-left:-2px;width:4px;height:4px}.rkmd-slider.slider-discrete .slider .slider-handle.is-active .slider-label{top:-15px;left:-2px;border-radius:15px 15px 15px 0;-webkit-transform:rotate(-45deg) translate(23px,-25px);transform:rotate(-45deg) translate(23px,-25px)}.rkmd-slider.slider-discrete .slider .slider-handle.is-active .slider-label span{opacity:1}.rkmd-slider.slider-discrete.slider-turquoise .slider-label{background-color:#16a085}.rkmd-slider.slider-discrete.slider-emerald .slider-label{background-color:#27ae60}.peterriver{background:#3498db;border-bottom:#2980b9 3px solid}.rkmd-slider.slider-discrete.slider-peterriver .slider-label{background-color:#2980b9}.wetasphalt{background:#34495e;border-bottom:#2c3e50 3px solid}.rkmd-slider.slider-discrete.slider-wetasphalt .slider-label{background-color:#2c3e50}.sunflower{background:#f1c40f;border-bottom:#e6bb0f 3px solid}.rkmd-slider.slider-discrete.slider-sunflower .slider-label{background-color:#e6bb0f}.carrot{background:#e67e22;border-bottom:#d35400 3px solid}.rkmd-slider.slider-discrete.slider-carrot .slider-label{background-color:#d35400}.alizarin{background:#e74c3c;border-bottom:#c0392b 3px solid}.rkmd-slider.slider-discrete.slider-alizarin .slider-label{background-color:#c0392b}input{margin:0 auto 1.2rem auto;padding:2px 5px;width:100%;box-sizing:border-box;border:0;border-radius:4px;box-shadow:inset 0 0 6px rgba(0,0,0,0.3);background:rgba(255,255,255,0.8)}select{margin:0 auto 1.2rem auto;padding:2px 5px;width:100%;box-sizing:border-box;border:0;border-radius:4px;box-shadow:inset 0 0 6px rgba(0,0,0,0.3);background:rgba(255,255,255,0.8)}input[id^="num"]{max-width:6em;width:auto;text-align:right;font-weight:bold;font-size:115%}body div>ul.navigation{margin:0;margin-bottom:30px;padding:0;border-bottom:3px solid #666;overflow:hidden}ul.navigation li{list-style:none;float:left;margin-right:4px}ul.navigation li.controls{float:right}ul.navigation li a{font-weight:bold;display:inline-block;padding:6px 12px;color:#888;outline:0;text-decoration:none;background:#f3f3f3;background:-webkit-gradient(linear,0 0,0 bottom,from(#eee),to(#e4e4e4));background:-moz-linear-gradient(#eee,#e4e4e4);background:linear-gradient(#eee,#e4e4e4);-pie-background:linear-gradient(#eee,#e4e4e4)}ul.navigation li.active a{pointer-events:none;color:white;background:#666;background:-webkit-gradient(linear,0 0,0 bottom,from(#888),to(#666));background:-moz-linear-gradient(#888,#666);background:linear-gradient(#888,#666);-pie-background:linear-gradient(#888,#666)}div.tabscontent>div{padding:0 15px}#tabsnav:empty{display:none}.range-slider{margin:0}.range-slider{width:100%}.range-slider__range{-webkit-appearance:none;width:calc(100% - (45px));height:10px;border-radius:5px;outline:0;padding:0;margin:0}.range-slider__value{display:inline-block;position:relative;width:30px;color:#fff;line-height:20px;text-align:center;border-radius:3px;padding:5px 5px;margin-left:2px}.range-slider__value:after{position:absolute;top:8px;left:-7px;width:0;height:0;content:""}::-moz-range-track{border:0}input::-moz-focus-inner,input::-moz-focus-outer{border:0}svg{display:block;width:100%;height:100%}.y-axis path,.x-axis path{stroke:gray;stroke-width:1;fill:none}.series{stroke:steelblue;stroke-width:3;fill:none}.data-points circle{stroke:steelblue;stroke-width:2;fill:white}.data-points text{display:none}.data-points circle:hover{fill:steelblue;stroke-width:6}.data-points circle:hover+text{display:inline-block}text{text-anchor:end}.vert-switcher{transform:rotate(270deg);margin-top:15px;margin-bottom:25px}.vert-slider{width:150px;transform:rotate(270deg);display:inline-block;margin:50px -42px 70px -42px}.vert-slider span{transform:rotate(90deg)}button:disabled{color:#333;background-color:#999}select:disabled{color:#333;background-color:#999}input:disabled{color:#333;background-color:#999}.range-slider__range:disabled{background-color:#999}.range-slider__range:disabled::-webkit-slider-thumb{background-color:#aaa}.range-slider__range:disabled::-moz-range-thumb{background-color:#aaa}.switch.disabled .in::before{background:#bbb;border:1px solid #ddd}.switch.disabled .in::after{background:#bbb}.switch.checked.disabled{background:#b1d092}.Alert{position:absolute;display:flex;flex-direction:row;justify-content:center;align-items:center;min-width:350px;max-width:20%;height:auto;margin:20px;padding-left:25px;padding-right:25px;border-radius:3px;font-size:20px;text-align:center;color:white;background-color:rgba(0,100,0,0.75);font-family:"Roboto";text-shadow:2px 2px 2px rgba(0,0,0,0.5);animation:ozFadeIn ease .25s;z-index:999999}.AlertIcon{position:absolute;left:25px}.AlertMessage{height:auto;width:80%;overflow-wrap:break-word}.AlertControls{margin-top:10px;margin-bottom:15px}.BtnConfirm{margin-right:30px;transition:.3s;border-radius:2px;border:0;padding:8px;padding-left:15px;padding-right:15px;outline:0;box-shadow:rgba(0,0,0,0.35) 0 5px 15px;cursor:pointer}.BtnConfirm:hover{background-color:rgba(37,155,53,0.75);color:white;text-shadow:2px 2px 2px rgba(0,0,0,0.5)}.BtnCancel{margin-left:30px;transition:.3s;border-radius:2px;border:0;padding:8px;padding-left:15px;padding-right:15px;outline:0;box-shadow:rgba(0,0,0,0.35) 0 5px 15px;cursor:pointer}.BtnCancel:hover{background-color:rgba(155,37,37,0.75);color:white;text-shadow:2px 2px 2px rgba(0,0,0,0.5)}
)=====";

const uint8_t CSS_STYLE_GZIP[3870] PROGMEM = { 31,139,8,0,116,182,150,101,2,255,213,27,217,110,227,200,241,87,24,27,6,44,44,201,240,212,65,97,23,73,22,8,178,15,65,128,236,75,130,96,51,104,145,77,139,49,69,42,36,53,182,71,224,191,167,250,32,217,23,45,249,88,4,59,158,241,72,205,170,234,186,187,186,186,233,166,117,213,161,162,194,205,249,88,183,69,87,212,85,210,224,18,117,197,87,188,125,42,178,110,159,172,54,119,219,3,106,30,138,42,9,188,227,243,118,87,63,59,109,241,173,168,30,146,93,221,100,184,113,96,164,119,211,186,60,29,42,155,255,223,158,25,178,239,121,119,219,188,172,81,151,148,56,239,0,12,53,217,249,80,84,206,30,23,15,251,142,0,80,154,148,80,131,178,226,212,38,203,97,150,61,202,234,167,196,179,162,227,51,253,215,60,236,208,125,224,69,182,191,89,217,254,58,182,61,55,94,108,143,40,203,128,27,135,76,192,88,28,70,26,58,5,29,98,18,0,171,93,87,31,146,136,14,193,119,198,101,76,153,0,206,235,38,185,205,243,188,255,195,1,103,5,186,159,32,252,192,139,143,207,139,179,11,95,241,36,196,32,228,10,30,246,6,172,213,198,155,199,90,198,158,136,133,158,249,131,101,200,144,20,248,205,250,174,239,221,22,167,196,72,187,6,163,199,81,215,140,243,93,137,210,71,51,132,181,111,206,76,199,137,183,229,154,15,136,150,1,227,161,169,79,85,230,112,233,151,203,101,239,118,167,230,191,167,186,104,241,121,2,72,110,125,180,75,55,233,118,52,58,213,228,173,191,68,222,58,182,66,48,79,91,151,69,214,187,248,128,27,84,102,18,110,128,211,116,229,171,184,193,10,225,165,39,226,30,113,135,155,6,156,175,145,208,195,104,179,206,118,26,250,102,237,237,54,34,250,19,238,80,123,220,163,178,83,208,163,77,140,53,244,52,196,177,52,123,123,170,192,87,159,148,201,115,63,141,188,92,197,198,203,221,206,203,69,108,176,87,83,203,19,227,229,10,7,129,138,154,133,113,228,73,19,163,178,248,134,154,162,146,145,87,81,26,106,250,78,189,112,19,236,68,228,12,53,143,18,98,20,69,235,120,165,34,178,81,17,177,68,59,92,158,141,241,188,125,218,23,29,118,218,35,74,113,82,213,79,13,58,42,65,234,6,248,48,4,90,226,250,240,205,114,35,242,203,135,223,219,14,63,119,14,72,245,80,37,41,174,192,166,66,116,109,115,200,57,206,19,243,194,149,231,109,75,200,63,99,62,112,67,37,86,33,180,182,89,209,30,75,244,146,20,21,133,221,149,117,250,104,98,17,252,166,43,82,84,242,169,119,168,197,4,97,171,231,182,174,62,38,142,235,199,192,171,30,4,155,205,70,97,194,39,161,202,20,230,144,153,120,122,219,64,118,19,217,56,54,152,62,222,62,129,174,232,167,132,198,161,67,190,115,124,151,78,2,50,156,196,240,26,227,47,223,160,204,151,65,27,156,25,32,179,112,149,174,82,25,242,161,193,184,50,192,110,118,105,176,92,203,176,117,131,170,7,19,11,25,70,126,28,201,192,47,184,132,192,48,0,227,77,182,140,20,126,143,167,230,88,154,40,111,242,117,8,194,105,121,50,242,120,198,27,23,35,54,190,142,238,12,89,117,204,143,10,52,73,144,218,50,196,205,200,86,130,144,164,105,254,40,201,139,166,237,156,116,95,148,217,8,46,14,14,168,116,89,241,122,183,174,240,72,125,250,60,44,116,145,187,28,255,172,128,143,238,169,86,151,194,208,13,199,63,4,98,15,198,82,96,130,0,30,228,245,169,81,198,67,207,149,168,231,224,194,42,200,70,38,223,22,207,42,139,68,63,45,254,138,43,229,65,188,148,169,211,72,84,96,150,177,76,190,42,52,21,172,34,34,149,70,125,29,40,212,75,3,11,27,95,81,206,19,46,53,17,105,49,161,91,197,233,246,69,147,113,216,25,133,129,57,24,88,43,195,169,98,17,114,176,124,228,50,20,213,92,157,231,45,238,156,221,139,35,121,130,97,180,149,92,103,173,120,198,132,49,249,136,109,28,149,233,248,43,133,213,9,67,240,36,123,102,92,166,21,44,37,2,130,199,217,230,97,25,61,140,220,25,145,4,199,180,205,195,50,165,40,156,19,106,242,95,219,56,42,211,137,3,25,89,112,49,123,102,92,38,176,244,230,68,18,163,193,158,25,87,104,109,230,132,18,162,198,54,15,203,148,86,178,227,117,70,161,186,25,145,214,203,89,145,202,25,253,40,177,41,82,219,196,115,66,169,33,104,191,242,236,90,63,210,226,213,126,237,225,181,234,87,162,219,158,127,164,123,87,191,239,14,229,153,150,46,80,45,225,100,25,184,241,93,191,171,179,23,14,10,149,245,244,212,119,73,101,33,21,54,82,217,3,43,30,251,158,163,67,81,190,36,55,127,59,226,202,250,25,85,237,141,221,194,111,240,212,166,200,135,162,41,32,53,164,190,244,166,185,151,251,253,222,183,247,129,189,15,237,125,100,239,99,123,191,28,88,39,37,142,167,212,49,110,220,0,95,34,39,161,231,1,9,65,176,168,81,57,119,131,109,137,59,40,226,104,149,67,234,61,168,156,0,170,223,7,2,94,232,46,13,152,241,28,106,40,162,234,136,225,28,94,36,224,5,174,129,217,208,48,165,183,166,184,241,89,180,208,90,199,53,161,198,20,117,41,161,198,58,234,82,69,245,102,43,23,73,221,177,166,200,200,13,116,13,81,229,202,210,135,154,76,193,12,171,125,127,148,156,162,71,124,203,120,235,99,132,179,93,143,146,125,77,246,92,124,212,203,145,151,226,126,119,2,159,169,206,198,226,123,168,252,125,125,251,30,74,123,105,115,121,205,105,39,184,66,187,18,103,9,74,73,85,126,54,238,71,183,29,84,170,109,94,55,135,132,126,130,10,30,255,227,62,2,77,90,227,247,127,210,239,253,237,1,10,194,191,96,4,220,24,217,238,111,161,104,252,185,67,221,169,157,250,29,69,181,135,96,235,132,232,117,87,16,189,156,69,219,229,106,80,54,4,196,3,196,28,225,134,194,8,43,55,233,80,239,158,156,252,84,150,204,5,196,74,102,166,145,114,114,72,43,64,64,153,58,3,175,163,29,9,10,157,249,204,58,46,244,243,248,132,112,121,22,91,49,29,219,153,157,181,189,90,191,111,68,119,97,222,174,136,79,125,116,48,60,227,206,27,190,18,36,127,216,102,90,183,216,39,63,253,84,175,39,40,135,89,108,183,169,159,134,143,39,39,205,207,4,0,24,72,110,110,198,13,95,71,220,99,155,150,24,53,32,109,183,103,84,154,186,52,237,91,178,76,116,182,226,128,30,112,66,108,143,200,198,8,124,19,104,223,239,193,93,238,61,219,187,163,127,93,127,97,79,35,68,189,116,108,161,120,116,60,168,157,53,164,138,10,22,13,203,179,136,140,195,63,141,74,188,176,61,1,70,123,190,18,0,2,19,64,32,0,132,151,0,162,75,0,75,9,96,224,96,232,5,109,70,3,39,33,236,225,209,169,171,183,115,253,192,13,241,105,110,5,235,84,158,167,70,222,221,152,21,60,33,102,155,26,226,13,223,71,113,134,31,22,19,102,89,156,101,37,19,2,22,97,215,211,117,237,16,17,156,107,116,109,144,209,152,191,56,215,196,178,36,243,145,182,79,178,47,178,12,87,219,161,39,120,39,138,9,252,38,85,183,103,91,195,251,96,113,214,4,220,120,178,128,42,78,104,192,113,46,33,69,6,36,127,173,35,161,193,12,1,53,131,222,238,208,102,102,246,224,194,18,172,137,30,95,13,108,97,32,175,83,72,153,90,204,153,92,78,160,115,214,195,136,199,42,84,102,163,93,152,65,72,246,133,16,47,51,203,199,135,223,135,150,80,5,233,205,36,58,146,225,180,110,16,149,179,130,242,141,13,142,61,227,89,103,137,22,76,27,76,67,174,31,183,19,199,228,67,94,52,135,207,202,46,177,33,189,128,138,22,159,158,77,130,255,123,54,89,67,164,177,98,25,172,44,150,70,67,63,47,113,88,81,60,58,39,218,193,2,113,234,88,47,142,96,241,173,187,152,95,6,131,168,30,57,142,207,56,230,45,198,120,164,2,238,209,221,187,224,110,180,214,88,88,104,196,158,45,59,86,171,213,44,58,4,232,235,120,237,83,209,165,123,99,1,98,253,174,56,28,235,166,67,85,103,40,140,118,152,252,40,139,79,36,159,134,12,238,226,81,35,208,19,17,48,2,249,113,195,133,88,119,165,167,166,133,207,199,186,160,33,163,71,27,175,16,9,253,33,121,44,167,147,146,87,139,154,217,197,97,73,202,65,216,90,236,30,139,206,17,194,76,149,213,114,131,214,194,168,197,14,16,174,79,221,214,57,212,223,222,134,80,191,145,126,251,38,248,55,192,14,6,119,211,61,78,31,141,189,218,213,50,11,252,108,0,180,138,234,120,234,254,213,189,28,241,247,55,20,9,236,123,243,203,232,48,52,155,41,230,27,87,89,208,47,107,7,145,243,27,115,44,173,225,201,80,48,146,134,103,81,157,231,1,39,98,6,179,145,135,22,236,158,94,183,213,12,84,125,13,165,246,50,208,37,0,85,255,86,86,124,61,179,254,194,154,136,207,149,14,106,72,118,24,214,64,249,84,75,222,162,36,84,54,53,173,131,174,108,2,104,121,240,159,71,126,44,146,20,23,18,34,215,222,136,196,136,216,148,101,66,128,126,96,229,179,205,250,228,45,12,223,123,148,242,66,28,162,9,151,79,180,48,78,242,46,6,235,247,161,129,137,222,131,167,227,12,194,155,49,217,233,164,176,109,160,134,145,50,97,160,158,11,123,211,169,176,148,3,199,109,196,16,53,235,217,88,113,226,33,6,156,205,24,54,36,15,74,126,67,119,41,178,219,80,230,175,244,28,38,40,179,244,231,122,14,243,17,131,243,128,75,189,193,115,46,48,88,191,15,109,214,115,94,199,123,205,115,76,152,202,46,130,118,31,52,15,8,198,149,45,161,251,8,226,60,228,131,193,45,134,19,127,226,3,205,227,33,115,90,240,71,161,161,192,27,32,218,10,40,172,169,100,29,149,218,123,127,175,65,132,90,236,237,73,180,165,21,129,158,203,193,114,160,238,75,102,57,157,22,112,242,177,38,253,167,238,133,28,142,92,152,225,59,247,74,201,132,238,195,80,41,172,180,182,143,31,26,47,20,176,154,102,232,133,241,229,44,201,193,198,139,243,213,12,242,89,35,109,82,175,191,90,74,139,255,239,228,69,89,206,137,172,168,214,219,138,187,219,83,75,218,123,184,196,105,199,214,232,111,176,2,101,248,57,241,223,206,196,30,85,89,137,207,202,42,111,206,81,212,121,217,129,215,96,138,88,176,121,172,20,109,206,90,83,19,169,174,133,101,20,149,229,88,196,204,75,21,124,204,104,170,168,44,219,186,244,166,204,37,26,201,80,109,143,30,96,112,44,143,252,8,5,245,219,169,74,46,97,191,31,93,54,102,134,115,116,42,187,11,165,254,39,115,63,126,161,7,241,31,150,69,38,39,87,166,191,190,48,110,209,58,108,139,245,97,65,38,82,130,3,94,27,69,159,38,198,39,91,103,142,176,98,39,115,10,160,93,32,2,208,127,148,141,113,27,60,213,100,132,174,232,248,211,140,109,138,74,124,239,47,230,188,100,32,13,115,166,13,238,70,201,212,32,211,87,39,115,22,190,146,158,162,192,153,34,209,95,185,99,157,24,141,254,67,78,115,6,255,9,181,141,47,145,218,169,97,211,12,37,7,40,159,86,43,219,249,39,186,181,52,106,147,14,149,38,222,101,8,195,222,78,90,4,102,198,47,175,0,239,83,51,139,176,192,164,50,46,2,105,121,93,18,211,0,211,127,220,7,172,246,136,230,54,204,43,109,33,246,166,158,230,120,181,109,170,1,245,206,165,46,175,212,31,159,235,155,79,85,221,72,65,91,183,233,6,196,48,218,234,131,234,192,175,100,103,166,74,65,39,129,186,248,95,73,86,201,226,158,156,169,131,49,34,133,94,86,164,164,239,55,207,164,184,44,203,3,211,110,49,208,11,224,152,116,103,199,95,222,188,173,185,179,78,199,151,247,1,20,207,182,19,144,59,198,219,183,129,127,166,144,204,94,131,171,189,158,79,135,239,227,93,97,69,95,122,149,192,110,10,95,69,148,95,33,190,72,146,93,32,254,240,181,225,43,56,154,102,184,204,20,165,255,225,203,200,87,48,53,205,112,153,41,74,255,163,87,156,175,224,105,156,224,34,75,140,252,135,238,77,95,193,15,163,126,145,25,70,251,131,55,177,175,96,103,160,127,145,33,70,189,167,101,217,120,195,136,158,204,90,236,240,157,159,210,242,19,87,114,232,35,84,182,179,23,5,182,227,107,0,31,56,101,16,116,195,94,201,136,99,123,248,231,185,235,69,207,150,150,223,28,219,172,6,46,178,127,127,127,83,157,14,55,191,8,87,47,150,248,192,153,164,252,11,11,59,61,22,145,174,84,145,83,76,177,18,240,249,69,49,210,152,254,225,84,186,21,250,90,60,208,131,203,233,234,152,124,189,34,20,222,98,153,100,30,30,78,61,82,114,59,70,105,19,245,210,4,228,152,189,44,90,224,164,123,41,49,91,252,167,59,32,242,201,14,89,49,85,228,225,12,172,149,174,148,168,80,22,58,107,242,191,122,107,136,88,135,118,53,184,179,175,215,235,109,125,234,8,36,185,59,96,58,221,149,210,85,72,126,174,233,161,146,94,161,55,180,15,243,166,62,220,147,147,193,133,221,213,240,33,34,63,74,155,212,212,196,37,40,246,0,254,90,167,82,6,116,142,5,200,125,37,180,174,121,190,64,163,51,47,202,28,114,53,179,107,249,233,16,213,27,125,245,64,210,12,113,136,247,169,5,76,192,212,2,36,174,209,9,192,219,20,246,85,133,76,80,23,181,49,130,246,16,38,110,7,117,55,111,227,254,64,206,115,198,96,160,197,85,127,75,158,131,190,18,124,56,118,47,210,190,23,210,48,217,190,14,93,219,33,194,148,225,41,225,200,15,190,124,97,175,69,12,154,67,199,35,176,137,170,148,7,15,195,131,237,71,74,59,237,150,99,65,133,14,101,216,66,58,161,83,54,115,164,43,59,122,247,20,214,102,214,190,124,249,138,200,187,33,230,0,154,233,205,134,242,11,108,210,1,60,125,255,77,223,137,232,151,246,6,206,98,158,148,165,27,227,180,156,214,217,228,71,35,23,206,23,157,213,152,227,199,150,170,39,180,233,251,132,121,25,155,0,234,220,244,113,124,95,141,101,101,14,64,143,251,97,191,95,225,198,214,199,65,201,120,122,209,173,111,191,62,40,125,94,189,145,205,60,224,197,65,207,69,107,29,81,183,183,221,231,233,203,185,133,228,247,136,19,240,210,151,45,251,60,92,197,219,146,14,15,119,56,210,208,199,237,0,220,118,24,151,228,245,30,25,35,20,49,50,212,33,135,6,118,107,165,69,147,150,248,2,118,192,176,105,196,203,232,196,178,74,0,232,212,249,253,78,74,99,102,134,229,60,222,119,210,28,210,133,74,250,132,57,87,149,238,193,253,112,5,133,16,121,15,203,97,231,103,228,130,161,186,161,9,86,244,6,211,86,184,100,40,246,223,248,58,23,208,183,117,24,41,41,104,99,234,208,115,68,141,113,195,67,141,96,90,78,68,170,142,213,248,81,154,131,109,129,230,46,119,241,91,171,67,95,236,44,220,102,50,95,115,229,123,236,235,17,152,83,95,15,111,74,94,19,250,59,112,146,113,209,24,54,120,251,211,97,103,160,132,16,186,72,73,136,233,215,168,240,243,251,1,145,30,185,154,206,234,119,187,157,225,160,56,203,178,25,18,250,177,45,80,80,175,11,184,6,109,1,160,159,121,155,160,119,255,88,130,111,24,210,219,224,101,121,137,159,183,228,23,84,250,13,123,243,22,124,230,105,251,159,83,219,21,249,139,51,228,56,158,116,105,6,118,32,134,15,237,48,52,93,15,15,99,246,166,242,80,115,6,83,154,162,69,167,248,22,182,252,210,115,172,191,244,28,27,239,101,11,119,197,205,171,130,185,176,224,214,226,5,53,228,76,90,82,147,203,149,166,83,78,233,38,94,192,111,164,5,106,65,14,200,168,42,14,172,196,171,191,253,25,101,248,167,138,118,29,45,55,136,219,177,173,187,161,127,184,37,126,2,125,26,172,49,106,129,131,253,21,183,45,130,85,92,212,30,127,27,77,184,240,169,191,160,73,145,127,28,74,94,49,61,233,239,144,211,58,196,253,83,87,253,200,239,12,202,175,26,142,57,138,223,51,12,91,227,109,6,190,171,25,150,222,181,106,90,95,55,173,47,215,19,194,246,71,222,240,196,11,216,7,13,237,40,229,62,145,200,56,95,27,204,214,14,87,182,15,219,163,56,228,246,22,253,227,74,51,179,185,72,9,85,202,111,255,252,22,84,68,217,126,85,67,68,61,160,37,248,251,126,13,253,15,213,21,78,154,135,65,0,0 };
