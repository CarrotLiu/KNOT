let source = new EventSource("/events");
let isDisinfectionOn = false; 
let isLightingOn = false;
let names = ["mom", "dad", "grandma", "grandpa", "pp", "ziyi", "tina", "jt", "julie"];

source.onmessage = (event) => {
  //   console.log(event.data);
};

// source.addEventListener("test", (event) => {
//   alert(`test message: ${event.data}`);
// });
source.addEventListener("time", (event) => {
  document.getElementById("time-display").textContent = `${event.data}`;
});
source.addEventListener("pause", (event) => {
  document.getElementById("time-display").textContent = `${event.data}`;
});

source.addEventListener("finish", (event) => {
  isDisinfectionOn = false;
  document.getElementById("time-display").textContent = `${event.data}`;
});

function toggleRecord() {
  let btn = document.getElementById("recordBtn");
  if (isDisinfectionOn) {
    btn.textContent = "Start Recording";
    fetch("/recordingStop"); 
  } else {
    btn.textContent = "Stop Recording";
    fetch("/recordingStart"); 
  }
  isDisinfectionOn = !isDisinfectionOn;
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


function checkID(){
  for(let i = 0; i < names.length; i ++){
    if(document.title == names[i]){   
      console.log("/light" + names[i]);
      fetch("/light" + names[i]);
    }
  }
  
}