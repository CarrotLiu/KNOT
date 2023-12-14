let source = new EventSource("/events");
let isRecordingOn = false; 
let isLightingOn = false;
let links = [];

source.onmessage = (event) => {
  //   console.log(event.data);
};

// source.addEventListener("test", (event) => {
//   alert(`test message: ${event.data}`);
// });


// source.addEventListener("finish", (event) => {
//   recordingStart = false;
//   document.getElementById("light").textContent = `${event.data}`;
// });

function toggleRecord() {
  let btn = document.getElementById("recordBtn");
  if (isRecordingOn) {
    btn.textContent = "Start Recording";
    fetch("/recordingStop"); 
  } else {
    btn.textContent = "Stop Recording";
    fetch("/recordingStart"); 
  }
  isRecordingOn = !isRecordingOn;
}

function toggleLighting() {
  let btn = document.getElementById("lightingBtn");
  if (isLightingOn) {
    btn.textContent = "Start Lighting";
    fetch("/offLighting");
  } else {
    btn.textContent = "Stop Lighting";
    fetch("/onLighting"); 
  }
  isLightingOn = !isLightingOn; 
}
function setup(){
  let cnv = createCanvas(windowWidth, windowHeight);
  cnv.parent("cnv-container");
  cnv.position(0, 0);
  cnv.style('z-index', '-1');
  links.push(createA('/mom.html', 'mom', '_blank'));
  links.push(createA('/dad.html', 'dad', '_blank'));
  
}
function draw(){
  background("#B76A62");
  noStroke();
  translate(width / 2, height / 2);
  for(let i = 0; i < 2 * PI; i += PI / 10){
    push();
    translate(sin(i) * (150 + i * 30), cos(i) * (150 + i * 30));
    fill("#FEECEA");
    circle(0, 0, 50);
    pop();
    links[i / (PI / 10)].position();
  }
  push();
  fill("#A0D4BD");
  circle(0, 0, 50);
  pop();
}