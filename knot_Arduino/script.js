let source = new EventSource("/events");
let isRecordingOn = false; 
let isLightingOn = false;
let links = [];
let names = ["mom", "dad", "grandma", "grandpa", "doudou", "tina", "julie", "meilin", "moon", "pan", "wuwei", "marcela", "pp", "ziyi", "sunny", "nadine", "lora", "helen", "shuazi"];

source.onmessage = (event) => {
  //   console.log(event.data);
};

