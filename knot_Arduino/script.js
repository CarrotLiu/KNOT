let source = new EventSource("/events");
let isRecordingOn = false;
let isLightingOn = false;
let links = [];
let passwords = [
  "200101191107",
  "200101191104",
  "20010119",
  "20010119",
  "200709070801",
  "20190526",
  "20190901",
  "20190907",
  "20200115",
  "20200814",
  "20210305",
  "202103140625",
  "20230206",
  "202303140323",
  "202303141219",
  "202303141231",
  "20230314",
  "20230314",
  "202303140625",
  "202303140617",
];
let names = [
  "mom",
  "dad",
  "grandma",
  "grandpa",
  "doudou",
  "julie",
  "tina",
  "meilin",
  "wuwei",
  "moon",
  "pan",
  "marcela",
  "pp",
  "ziyi",
  "sunny",
  "nadine",
  "lora",
  "helen",
  "jt",
];

source.onmessage = (event) => {
  //   console.log(event.data);
};

function friendLogin() {
  let inputName = document.getElementById('fname').value;
  let inputPassword = document.getElementById('psw').value;
  let isUserFound = false;
  for (let i = 0; i < names.length; i++) {
    if (inputName == names[i]) {
      isUserFound = true;
      if (inputPassword == passwords[i]) {
        window.location.href = "/" + names[i] + ".html";
      } else {
        alert("Wrong Password!");
      }
    }
  }
  if (!isUserFound) {
    alert("Wrong User Name!");
  }
}
